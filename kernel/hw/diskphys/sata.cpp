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

SATA::SATA() : PhysicalDisk("SATA Hard Drive", 512)
{

}

int SATA::open(int _deviceNum, int b, void* _ide)
{
	//save parameters
	sbus = (SATABus*) _ide;
	deviceNum = _deviceNum;
	sectorSize = 512;
	sizeInKBs = 0;

	//reset the drive


	//set up logical disks
	startCache();
	createPartitionsForDisk(this);

	return 0;
}

int SATA::access(uint64_t lba, int count, void* buffer, bool write)
{
	return 0;
}

int SATA::read(uint64_t lba, int count, void* buffer)
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

int SATA::write(uint64_t lba, int count, void* buffer)
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

int SATA::close(int a, int b, void* c)
{
	delete cache;
	return 0;
}

void SATA::powerSaving(PowerSavingLevel level)
{
	if (level == PowerSavingLevel::Active) {

	} else if (level == PowerSavingLevel::Standby) {

	} else if (level == PowerSavingLevel::Sleep) {

	}
}