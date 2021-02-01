#include "hw/diskphys/atapi.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/common.hpp"
#include "core/prcssthr.hpp"
#include "hal/vcache.hpp"
#include "hal/logidisk.hpp"
#include "hal/partition.hpp"

#pragma GCC optimize ("Os")

ATAPI::ATAPI() : PhysicalDisk("ATAPI Disk", 2048)
{

}

int ATAPI::sendPacket(uint8_t* packet, int maxTransferSize, bool write, uint16_t* data, int count)
{
	kprintf("Sending ATAPI packet.\n");

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

		kprintf("H %d.\n", words);

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
		if (timeout >= 100) {
			nanoSleep(1000 * 1000);
		}
		if (timeout == 2000) {
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

	//reset the drive
	ide->write(channel, ATA_REG_CONTROL, 4);
	asm("nop; nop");
	ide->write(channel, ATA_REG_CONTROL, 0);

	//detect if disk is in
	diskIn = false;
	detectMedia();

	//DEBUG
	eject();

	return 0;
}

void ATAPI::eject()
{
	uint8_t packet[12] = {ATAPI_CMD_EJECT, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };
	sendPacket(packet, 2, false, nullptr, 0);
}

void ATAPI::diskRemoved()
{
	diskIn = false;
}

void ATAPI::diskInserted()
{
	diskIn = true;
}

void ATAPI::detectMedia()
{
	kprintf("ATAPI detect media.\n");
	//create a TEST UNIT READY packet
	uint8_t packet[12];
	memset(packet, 0, 12);
	kprintf("created TEST UNIT READY\n");

	//send it
	sendPacket(packet, 0, false, nullptr, 0);
	kprintf("sent TEST UNIT READY\n");

	//create a REQUEST SENSE packet
	memset(packet, 0, 12);
	packet[0] = ATAPI_CMD_REQUEST_SENSE;
	packet[4] = 18;
	kprintf("created REQUEST SENSE\n");

	//send it
	uint8_t senseData[18];
	sendPacket(packet, 18, false, (uint16_t*) senseData, 1);
	kprintf("sent REQUEST SENSE\n");

	//check there is actually error data
	if ((senseData[0] & 0x7F) != 0x70) {
		kprintf("RQ: A\n");

		if (!diskIn) {
			kprintf("RQ: B\n");
			diskInserted();
			kprintf("RQ: C\n");
		}

		kprintf("RQ: D\n");
	}

	kprintf("RQ: E\n");

	//parse the response
	uint8_t senseKey = senseData[2] & 0xF;
	uint8_t additionalSenseCode = senseData[12];
	kprintf("RQ: F\n");

	//check for NO MEDIA
	if (senseKey == 0x02 && additionalSenseCode == 0x3A) {
		kprintf("RQ: G\n");
		if (diskIn) {
			kprintf("RQ: H\n");
			diskRemoved();
			kprintf("RQ: I\n");
		}
		kprintf("RQ: J\n");

	//check for success (meaning there is a disk)
	} else if (senseKey == 0x00) {
		kprintf("RQ: K\n");
		if (!diskIn) {
			kprintf("RQ: L\n");
			diskInserted();
			kprintf("RQ: M\n");
		}
		kprintf("RQ: N\n");
	}

	kprintf("RQ: O\n");
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