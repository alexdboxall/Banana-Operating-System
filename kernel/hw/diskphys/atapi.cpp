#include "hw/diskphys/atapi.hpp"
#include "hw/diskctrl/ide.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "krnl/common.hpp"
#include "thr/prcssthr.hpp"
#include "hal/vcache.hpp"
#include "hal/logidisk.hpp"
#include "hal/partition.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-Wcast-align"

ATAPI::ATAPI() : PhysicalDisk("ATAPI Disk", 2048)
{

}

int ATAPI::sendPacket(uint8_t* packet, int maxTransferSize, bool write, uint16_t* data, int count)
{
	//enable IRQs
	ide->enableIRQs(channel, true);
	ide->prepareInterrupt(channel);

	//wait for the drive to be not busy
	if (!readyForCommand()) {
		return 1;
	}

	//select the drive
	ide->write(channel, ATA_REG_HDDEVSEL, drive << 4);

	//set PIO mode
	ide->write(channel, ATA_REG_FEATURES, 0);

	//set maximum transfer size
	ide->write(channel, ATA_REG_LBA1, maxTransferSize & 0xFF);
	ide->write(channel, ATA_REG_LBA2, maxTransferSize >> 8);

	//send the command
	ide->write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);

	//poll
	uint8_t err = ide->polling(channel, 1);
	if (err) {
		ide->printError(channel, drive, err);
		return err;
	}

	//send the packet
	outsw(ide->getBase(channel), (uint16_t*) packet, 6);

	while (count--) {
		//wait for the interrupt
		bool gotIRQ = ide->waitInterrupt(channel);
		if (!gotIRQ) {
			return 1;
		}

		ide->prepareInterrupt(channel);

		//get actual transfer size
		uint16_t low = ide->read(channel, ATA_REG_LBA1);
		uint16_t high = ide->read(channel, ATA_REG_LBA2);

		int words = (low | (high << 8)) / 2;

		if (write) {
			for (int i = 0; i < words; ++i) {
				outw(ide->getBase(channel), *data++);
			}

		} else {
			for (int i = 0; i < words; ++i) {
				*data++ = inw(ide->getBase(channel));
			}
		}
	}

	//wait for the interrupt
	bool gotIRQ = ide->waitInterrupt(channel);
	if (!gotIRQ) {
		return 1;
	}
	ide->prepareInterrupt(channel);

	//wait for BSY and DRQ to clear
	uint8_t status;
	int timeout = 0;
	while ((status = inb(ide->getBase(channel) + ATA_REG_COMMAND)) & 0x88) {
		++timeout;
		if (timeout == 100000) {
			return 2;
		}
	}

	return 0;
}

bool ATAPI::readyForCommand()
{
	//wait for the device to be ready
	int timeout = 0;
	while (ide->read(channel, ATA_REG_ALTSTATUS) & (ATA_SR_BSY | ATA_SR_DRQ)) {
		++timeout;
		if (timeout >= 1440) {
			milliTenthSleep(350);
		}
		if (timeout == 1500) {
			return false;
		}
	}

	return true;
}

int ATAPI::open(int __a, int _ideDeviceNum, void* _ide)
{
	//save parameters
	ide = (IDE*) _ide;
	ideDeviceNum = _ideDeviceNum;
	channel = ide->devices[ideDeviceNum].channel;
	drive = ide->devices[ideDeviceNum].drive;
	sectorSize = 2048;
	removable = true;

	//reset the drive
	ide->write(channel, ATA_REG_CONTROL, 4);
	asm("nop; nop");
	ide->write(channel, ATA_REG_CONTROL, 0);

	//detect if disk is in
	LogicalDisk* ld = new LogicalDisk("ATAPI CD-ROM", this, 0, 0x7FFFFFFF);		//parititon with basically no size limit
	char letter = ld->assignDriveLetter();
	kprintf("letter = %c\n", letter);
	this->addChild(ld);
	logi = ld;
	startCache();
	diskIn = false;
	detectMedia();

	return 0;
}

int ATAPI::eject()
{
	//eject the disk
	uint8_t packet[12] = {ATAPI_CMD_EJECT, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };
	sendPacket(packet, 2, false, nullptr, 0);

	//acknowledge the removed disk
	diskRemoved();

	return 0;
}

void ATAPI::diskRemoved()
{
	diskIn = false;

	logi->unmount();

	cache->writeWriteBuffer();
	cache->invalidateReadBuffer();
}

void ATAPI::diskInserted()
{
	diskIn = true;
}

void ATAPI::detectMedia()
{
	//create a TEST UNIT READY packet
	uint8_t packet[12];
	memset(packet, 0, 12);

	//send it
	sendPacket(packet, 0, false, nullptr, 0);

	//create a REQUEST SENSE packet
	memset(packet, 0, 12);
	packet[0] = ATAPI_CMD_REQUEST_SENSE;
	packet[4] = 18;

	//send it
	uint8_t senseData[18];
	sendPacket(packet, 18, false, (uint16_t*) senseData, 1);

	//check there is actually error data
	if ((senseData[0] & 0x7F) != 0x70) {
		if (!diskIn) {
			diskInserted();
		}
	}

	//parse the response
	uint8_t senseKey = senseData[2] & 0xF;
	uint8_t additionalSenseCode = senseData[12];

	//check for NO MEDIA
	if (senseKey == 0x02 && additionalSenseCode == 0x3A) {
		if (diskIn) {
			diskRemoved();
		}

	//check for success (meaning there is a disk)
	} else if (senseKey == 0x00) {
		if (!diskIn) {
			diskInserted();
		}
	}
}

int ATAPI::read(uint64_t lba, int count, void* buffer)
{
	//check that there is a disk and it hasn't changed
	if (!diskIn) {
		detectMedia();
		if (!diskIn) {
			return (int) DiskError::NotReady;
		}
	}

	//create the packet
	uint8_t packet[12] = { ATAPI_CMD_READ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	packet[2] = (lba >> 24) & 0xFF;
	packet[3] = (lba >> 16) & 0xFF;
	packet[4] = (lba >> 8) & 0xFF;
	packet[5] = (lba >> 0) & 0xFF;
	packet[9] = count;

	//send the packet
	return sendPacket(packet, 2048 * count, false, (uint16_t*) buffer, count);
}

int ATAPI::write(uint64_t lba, int count, void* buffer)
{
	return (int) DiskError::WriteProtected;
}

int ATAPI::close(int a, int b, void* c)
{
	delete cache;
	return 0;
}

#pragma GCC diagnostic pop