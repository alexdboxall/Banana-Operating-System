#include "hw/diskphys/sata.hpp"
#include "hw/diskphys/ata.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hal/vcache.hpp"
#include "hal/logidisk.hpp"
#include "hw/cpu.hpp"

extern int ataSectorsRead;
extern int ataSectorsWritten;

#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08

#define HBA_PxCMD_ST    0x0001
#define HBA_PxCMD_FRE   0x0010
#define HBA_PxCMD_FR    0x4000
#define HBA_PxCMD_CR    0x8000
#define HBA_PxIS_TFES   (1 << 30)

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
	sizeInKBs = 64 * 1024;
	removable = false;

	//allocate 2 contiguous pages
	sataPhysAddr = Phys::allocatePage();
	size_t prev = sataPhysAddr;
	for (int i = 1; i < 2; ++i) {
		size_t got = Phys::allocatePage();
		if (got != prev + 4096) {
			panic("SATA NOT CONTIGUOUS");
		}
		prev = got;
	}

	sataVirtAddr = Virt::allocateKernelVirtualPages(2);
	Virt::getAKernelVAS()->mapPage(sataPhysAddr, sataVirtAddr, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);

	//set up logical disks
	startCache();
	createPartitionsForDisk(this);

	return 0;
}

int SATA::access(uint64_t lba, int count, void* buffer, bool write)
{
	while (count > 16) {
		int ret = access(lba, 16, buffer, write);
		count -= 16;
		lba += 16;
		buffer = (void*) (((uint8_t*) buffer) + 512 * 16);
		if (count == 0) {
			kprintf("ending early, count = 0, lba = 0x%X\n", (uint32_t) lba);
			return ret;
		}
	}

	uint32_t startl = lba & 0xFFFFFFFF;
	uint32_t starth = lba >> 32;

	SATABus::HBA_PORT* port = &sbus->abar->ports[deviceNum];

	port->is = (uint32_t) -1;
	int spin = 0;
	int slot = sbus->findCmdslot(port);
	if (slot == -1) {
		return 1;
	}

	if (write) {
		memcpy((void*) sataVirtAddr, buffer, 512 * count);
	}

	uint8_t* spot = (uint8_t*) (((size_t) port->clb) - sbus->AHCI_BASE_PHYS + sbus->AHCI_BASE_VIRT);
	SATABus::HBA_CMD_HEADER* cmdheader = (SATABus::HBA_CMD_HEADER*) spot;
	cmdheader += slot;
	cmdheader->cfl = sizeof(SATABus::FIS_REG_H2D) / sizeof(uint32_t);
	cmdheader->w = write;			// Read from device
	cmdheader->prdtl = 1;			// PRDT entries count

	spot = (uint8_t*) (((size_t) cmdheader->ctba) - sbus->AHCI_BASE_PHYS + sbus->AHCI_BASE_VIRT);
	SATABus::HBA_CMD_TBL* cmdtbl = (SATABus::HBA_CMD_TBL*) spot;
	memset(cmdtbl, 0, sizeof(SATABus::HBA_CMD_TBL) +
		   (cmdheader->prdtl - 1) * sizeof(SATABus::HBA_PRDT_ENTRY));

	cmdtbl->prdt_entry[0].dba = sataPhysAddr;		//data base address
	cmdtbl->prdt_entry[0].dbc = 512 * count - 1;	// 512 bytes per sector
	cmdtbl->prdt_entry[0].i = 1;					//interrupt when done

	// Setup command
	SATABus::FIS_REG_H2D* cmdfis = (SATABus::FIS_REG_H2D*) (&cmdtbl->cfis);

	cmdfis->fis_type = SATABus::FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = write ? ATA_CMD_WRITE_DMA_EXT : ATA_CMD_READ_DMA_EXT;

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

	if (!write) {
		memcpy(buffer, (const void*) sataVirtAddr, 512 * count);
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
	//int err = access(lba, count, buffer, true);
	int err = 0;

	uint8_t* bf = (uint8_t*) buffer;
	for (int i = 0; i < count; ++i) {
		access(lba++, 1, bf, true);
		bf += 512;
	}

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