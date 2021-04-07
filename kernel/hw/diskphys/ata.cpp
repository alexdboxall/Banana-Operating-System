#include "hw/diskphys/ata.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hal/vcache.hpp"
#include "hal/logidisk.hpp"
#include "hw/cpu.hpp"

int ataSectorsRead = 0;
int ataSectorsWritten = 0;

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

ATA::ATA() : PhysicalDisk("ATA Hard Drive", 512)
{

}

void ATA::flush(bool lba48)
{
	//send a flush command to the drive
	ide->write(channel, ATA_REG_COMMAND, lba48 ? ATA_CMD_CACHE_FLUSH_EXT : ATA_CMD_CACHE_FLUSH);
	ide->polling(channel, 0);
}

bool ATA::readyForCommand()
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

#define MODE_CHS	0
#define MODE_LBA28	1
#define MODE_LBA48	2

int ATA::access(uint64_t lba, int count, void* buffer, bool write)
{	
	uint8_t lbaIO[6];
	uint8_t lbaMode;
	uint8_t head;
	uint8_t command;

	bool hasLBA = ide->devices[ideDeviceNum].hasLBA;

	//sort out the what LBA values will be sent depending on
	//the features supported by this drive
	if (hasLBA && (lba >> 28)) {
		//LBA48
		lbaMode = MODE_LBA48;

		for (int i = 0; i < 6; ++i) {
			lbaIO[i] = (lba >> (i << 3)) & 0xFF;
		}

		head = 0;

	} else if (hasLBA) {
		//LBA28
		lbaMode = MODE_LBA28;

		lbaIO[0] = (lba >> 0) & 0xFF;
		lbaIO[1] = (lba >> 8) & 0xFF;
		lbaIO[2] = (lba >> 16) & 0xFF;
		lbaIO[3] = 0;
		lbaIO[4] = 0;
		lbaIO[5] = 0;

		head = (lba >> 24) & 0xF;
	
	} else {
		//CHS
		lbaMode = MODE_CHS;

		uint8_t sect = (lba % 63) + 1;
		uint16_t cyl = lba / (16 * 63);

		lbaIO[0] = sect;
		lbaIO[1] = (cyl >> 0) & 0xFF;
		lbaIO[2] = (cyl >> 8) & 0xFF;
		lbaIO[3] = 0;
		lbaIO[4] = 0;
		lbaIO[5] = 0;

		head = (lba / 63) % 16;	
	}

	//disable IRQs
	ide->enableIRQs(channel, false);

	//wait for the drive to be not busy
	if (!readyForCommand()) {
		return 1;
	}

	//select the drive
	if (lbaMode == MODE_CHS) {
		ide->write(channel, ATA_REG_HDDEVSEL, 0xA0 | (drive << 4) | head);

	} else {
		ide->write(channel, ATA_REG_HDDEVSEL, 0xE0 | (drive << 4) | head);
	}

	//set PIO mode
	ide->write(channel, ATA_REG_FEATURES, 0);

	//write LBA48 data
	if (lbaMode == MODE_LBA48) {
		ide->write(channel, ATA_REG_SECCOUNT1, 0);
		ide->write(channel, ATA_REG_LBA3, lbaIO[3]);
		ide->write(channel, ATA_REG_LBA4, lbaIO[4]);
		ide->write(channel, ATA_REG_LBA5, lbaIO[5]);
	}

	//write sector count and LBA (or CHS)
	ide->write(channel, ATA_REG_SECCOUNT0, count);
	ide->write(channel, ATA_REG_LBA0, lbaIO[0]);
	ide->write(channel, ATA_REG_LBA1, lbaIO[1]);
	ide->write(channel, ATA_REG_LBA2, lbaIO[2]);

	//determine which command to send
	if (write && lbaMode == MODE_LBA48) command = ATA_CMD_WRITE_PIO_EXT;
	else if (write && lbaMode != MODE_LBA48) command = ATA_CMD_WRITE_PIO;
	else if (!write && lbaMode == MODE_LBA48) command = ATA_CMD_READ_PIO_EXT;
	else if (!write && lbaMode != MODE_LBA48) command = ATA_CMD_READ_PIO;
	else {
		return 1;
	}
		
	//send the command
	ide->write(channel, ATA_REG_COMMAND, command);

	//for each sector
	int ogcount = count;
	while (count--) {
		uint16_t* buffer16 = (uint16_t*) buffer;

		//wait for the device to be ready
		uint8_t err = ide->polling(channel, 1);
		if (err) {
			ide->printError(channel, drive, err);
			kprintf("ata error\n");
			return err;
		}

		//read/write data
		if (write) {
			for (int i = 0; i < 256; ++i) {
				outw(ide->getBase(channel), *buffer16++);
			}

		} else {
			asm("cld; rep insw" : : "c"(256), "d"(ide->getBase(channel)), "D"(buffer16) : "flags", "memory");
		}

		buffer = (void*) (((uint8_t*) buffer) + 512);
	}

	if (write) {
		flush(lbaMode == MODE_LBA48);
	}

	return 0;
}

void ATA::detectCHS()
{
	ide->devices[ideDeviceNum].size = 0;
	panic("ENTER CHS VALUES!");
}

int ATA::open(int __a, int _ideDeviceNum, void* _ide)
{
	//save parameters
	ide = (IDE*) _ide;
	ideDeviceNum = _ideDeviceNum;
	channel = ide->devices[ideDeviceNum].channel;
	drive = ide->devices[ideDeviceNum].drive;
	sectorSize = 512;
	removable = false;

	//set disk size
	if (!ide->devices[ideDeviceNum].hasLBA) {
		detectCHS();
	}
	sizeInKBs = ide->devices[ideDeviceNum].size / 2;

	//reset the drive
	ide->write(channel, ATA_REG_CONTROL, 4);
	asm("nop; nop");
	ide->write(channel, ATA_REG_CONTROL, 0);

	//set up logical disks
	startCache();
	createPartitionsForDisk(this);

	return 0;
}

int ATA::read(uint64_t lba, int count, void* buffer)
{
	//check for sane values
	if (count > 255 || count <= 0) {
		return (int) DiskError::BadSectorCount;
	}
	if (buffer == nullptr) {
		return (int) DiskError::BadBuffer;
	}

	//perform the read operation
	int err = access(lba, count, buffer, false);

	//error checking
	if (err) {
		return (int) DiskError::Failure;
	}

#ifdef KERNEL_DEBUG
	//update debug information
	ataSectorsRead += count;
	VgaText::updateDiskUsage();
#endif

	return (int) DiskError::Success;
}

int ATA::write(uint64_t lba, int count, void* buffer)
{
	//check for sane values
	if (count > 255 || count <= 0) {
		return (int) DiskError::BadSectorCount;
	}
	if (buffer == nullptr) {
		return (int) DiskError::BadBuffer;
	}

	//perform the read operation
	int err = access(lba, count, buffer, true);

	//error checking
	if (err) {
		return (int) DiskError::Failure;
	}

#ifdef KERNEL_DEBUG
	//update debug information
	ataSectorsWritten += count;
	VgaText::updateDiskUsage();
#endif

	return (int) DiskError::Success;
}

int ATA::close(int a, int b, void* c)
{
	delete cache;
	return 0;
}

void ATA::powerSaving(PowerSavingLevel level)
{
	if (level == PowerSavingLevel::Active) {

	} else if (level == PowerSavingLevel::Standby) {

	} else if (level == PowerSavingLevel::Sleep) {

	}
}