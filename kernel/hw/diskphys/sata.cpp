#include "hw/diskphys/sata.hpp"
#include "hw/diskphys/ata.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hal/vcache.hpp"
#include "hal/logidisk.hpp"
#include "hw/cpu.hpp"

extern int ataSectorsRead;
extern int ataSectorsWritten;

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
	kprintf("Starting up a SATA drive!\n");

	//set up logical disks
	startCache();
	createPartitionsForDisk(this);

	return 0;
}

int SATA::access(uint64_t lba, int count, void* buf, bool write)
{
	uint32_t startl = lba & 0xFFFFFFFF;
	uint32_t starth = lba >> 32;

	SATABus::HBA_PORT* port = &sbus->abar->ports[deviceNum];

	port->is = (uint32_t) -1;

	int spin = 0;
	int slot = sbus->findCmdslot(port);
	if (slot == -1) {
		return 1;
	}

	SATABus::HBA_CMD_HEADER* cmdheader = (SATABus::HBA_CMD_HEADER*) port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(SATABus::FIS_REG_H2D) / sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = (uint16_t) ((count - 1) >> 4) + 1;	// PRDT entries count

	SATABus::HBA_CMD_TBL* cmdtbl = (SATABus::HBA_CMD_TBL*) (cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(SATABus::HBA_CMD_TBL) +
		   (cmdheader->prdtl - 1) * sizeof(SATABus::HBA_PRDT_ENTRY));

	// 8K bytes (16 sectors) per PRDT
	for (int i = 0; i < cmdheader->prdtl - 1; i++) {
		cmdtbl->prdt_entry[i].dba = (uint32_t) buf;
		cmdtbl->prdt_entry[i].dbc = 8 * 1024 - 1;	// 8K bytes (this value should always be set to 1 less than the actual value)
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;	// 4K words
		count -= 16;	// 16 sectors
	}
	// Last entry
	cmdtbl->prdt_entry[i].dba = (uint32_t) buf;
	cmdtbl->prdt_entry[i].dbc = (count << 9) - 1;	// 512 bytes per sector
	cmdtbl->prdt_entry[i].i = 1;

	// Setup command
	FIS_REG_H2D* cmdfis = (SATABus::FIS_REG_H2D*) (&cmdtbl->cfis);

	cmdfis->fis_type = SATABus::FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = ATA_CMD_READ_DMA_EX;

	cmdfis->lba0 = (uint8_t) startl;
	cmdfis->lba1 = (uint8_t) (startl >> 8);
	cmdfis->lba2 = (uint8_t) (startl >> 16);
	cmdfis->device = 1 << 6;	// LBA mode

	cmdfis->lba3 = (uint8_t) (startl >> 24);
	cmdfis->lba4 = (uint8_t) starth;
	cmdfis->lba5 = (uint8_t) (starth >> 8);

	cmdfis->countl = count & 0xFF;
	cmdfis->counth = (count >> 8) & 0xFF;

	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000) {
		spin++;
	}
	if (spin == 1000000) {
		panic("Port is hung\n");
		return 1;
	}

	port->ci = 1 << slot;	// Issue command

	// Wait for completion
	while (1) {
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			panic("Read disk error\n");
			return FALSE;
		}
	}

	// Check again
	if (port->is & HBA_PxIS_TFES) {
		panic("Read disk error\n");
		return 1;
	}

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