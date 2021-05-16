#include "hw/diskphys/satapi.hpp"
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

SATAPI::SATAPI(): PhysicalDisk("SATAPI Disk", 2048)
{

}

void SATAPI::diskRemoved()
{
	kprintf("SATAPI: Disk removed.\n");
	diskIn = false;

	kprintf("unmounting...\n");
	logi->unmount();
	kprintf("unmounted...\n");

	cache->writeWriteBuffer();
	cache->invalidateReadBuffer();

}

void SATAPI::diskInserted()
{	
	//sbus->portRebase(&sbus->abar->ports[deviceNum], deviceNum);

	kprintf("SATAPI: Disk inserted.\n");
	diskIn = true;

	//eject the disk
	uint8_t packet[12] = { ATAPI_CMD_EJECT, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
	sendPacket(packet, 2, false, nullptr, 0);

	//acknowledge the removed disk
	if (diskIn) {
		diskRemoved();
	}
}

int SATAPI::sendPacket(uint8_t* packet, int maxTransferSize, uint64_t lba, uint16_t* data, int count)
{
	kprintf("sending satapi packet...\n");
	SATABus::HBA_PORT* port = &sbus->abar->ports[deviceNum];

	port->is = (uint32_t) -1;
	int spin = 0;
	int slot = sbus->findCmdslot(port);
	if (slot == -1) {
		return 1;
	}

	uint32_t startl = lba & 0xFFFFFFFF;
	uint32_t starth = lba >> 32;

	uint8_t* spot = (uint8_t*) (((size_t) port->clb) - sbus->AHCI_BASE_PHYS + sbus->AHCI_BASE_VIRT);
	SATABus::HBA_CMD_HEADER* cmdheader = (SATABus::HBA_CMD_HEADER*) spot;
	cmdheader += slot;
	cmdheader->cfl = sizeof(SATABus::FIS_REG_H2D) / sizeof(uint32_t);
	cmdheader->w = 0;				// Read from device
	cmdheader->prdtl = 1;			// PRDT entries count
	cmdheader->a = true;			// ATAPI

	spot = (uint8_t*) (((size_t) cmdheader->ctba) - sbus->AHCI_BASE_PHYS + sbus->AHCI_BASE_VIRT);
	SATABus::HBA_CMD_TBL* cmdtbl = (SATABus::HBA_CMD_TBL*) spot;

	memset(cmdtbl, 0, sizeof(SATABus::HBA_CMD_TBL) +
		   (cmdheader->prdtl - 1) * sizeof(SATABus::HBA_PRDT_ENTRY));
	memcpy(cmdtbl->acmd, packet, 12);

	cmdtbl->prdt_entry[0].dba = sataPhysAddr;			//data base address
	cmdtbl->prdt_entry[0].dbc = maxTransferSize - 1;	
	cmdtbl->prdt_entry[0].i = 1;						//interrupt when done

	// Setup command
	SATABus::FIS_REG_H2D* cmdfis = (SATABus::FIS_REG_H2D*) (&cmdtbl->cfis);

	cmdfis->fis_type = SATABus::FIS_TYPE_REG_H2D;
	cmdfis->c = 1;
	cmdfis->command = ATA_CMD_PACKET;

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

	int times = 0;
	// Wait for completion
	while (1) {
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			kprintf("satapi disk error\n");
			return 1;
		}
	
		++times;
		if (times > 1000 && times < 1015) {
			milliTenthSleep(200);
		}
		if (times > 2000 && times < 2015) {
			milliTenthSleep(600);
		}
		if (times > 3000 && times < 3015) {
			milliTenthSleep(1500);
		}
		if (times > 7000 && times < 7015) {
			milliTenthSleep(2500);
		}
		if (times > 10000) {
			kprintf("SATAPI time out...\n");
			return 1;
		}
	}

	// Check again
	if (port->is & HBA_PxIS_TFES) {
		kprintf("satapi disk error 2\n");
		return 1;
	}

	if (maxTransferSize && data) {
		memcpy(data, (const void*) sataVirtAddr, maxTransferSize);
	}
	return 0;
}

int SATAPI::open(int _deviceNum, int b, void* _ide)
{
	//save parameters
	sbus = (SATABus*) _ide;
	deviceNum = _deviceNum;
	sizeInKBs = 64 * 1024;
	sectorSize = 2048;
	removable = true;

	//allocate 2 contiguous pages
	sataPhysAddr = Phys::allocatePage();
	size_t prev = sataPhysAddr;
	for (int i = 1; i < 2; ++i) {
		size_t got = Phys::allocatePage();
		if (got != prev + 4096) {
			panic("SATAPI NOT CONTIGUOUS");
		}
		prev = got;
	}

	sataVirtAddr = Virt::allocateKernelVirtualPages(2);
	Virt::getAKernelVAS()->mapPage(sataPhysAddr, sataVirtAddr, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);

	//detect if disk is in
	LogicalDisk* ld = new LogicalDisk("SATAPI CD-ROM", this, 0, 0x7FFFFFFF);		//parititon with basically no size limit
	char letter = ld->assignDriveLetter();
	kprintf("letter = %c\n", letter);
	this->addChild(ld);
	logi = ld;
	startCache();
	diskIn = false;
	detectMedia();

	return 0;
}

int SATAPI::read(uint64_t lba, int count, void* buffer)
{
	kprintf("SATAPI::read A.\n");
	//check that there is a disk and it hasn't changed
	if (!diskIn) {
		detectMedia();
		if (!diskIn) {
			kprintf("SATAPI::read C!\n");
			return (int) DiskError::NotReady;
		}
	}
	kprintf("SATAPI::read B.\n");

	if (count > 4) {
		panic("UNIMPLEMENTED SATAPI::read with count > 4");
	}

	//create the packet
	uint8_t packet[12] = { ATAPI_CMD_READ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	packet[2] = (lba >> 24) & 0xFF;
	packet[3] = (lba >> 16) & 0xFF;
	packet[4] = (lba >> 8) & 0xFF;
	packet[5] = (lba >> 0) & 0xFF;
	packet[9] = count;

	//send the packet
	return sendPacket(packet, 2048 * count, lba, (uint16_t*) buffer, count);
}

int SATAPI::write(uint64_t lba, int count, void* buffer)
{
	return (int) DiskError::WriteProtected;
}

int SATAPI::close(int a, int b, void* c)
{
	delete cache;
	return 0;
}

void SATAPI::detectMedia()
{
	kprintf("detecting media...\n");

	bool retried = false;
retry:

	//create a TEST UNIT READY packet
	uint8_t packet[12];
	memset(packet, 0, 12);

	//send it
	int res = sendPacket(packet, 0, false, nullptr, 0);
	if (res == 1) {
		kprintf("err 1...\n");
		if (!retried) {
			retried = true;
			goto retry;
		}
		//drive not ready, probably no disk
		if (diskIn) {
			diskRemoved();
			return;
		}
	}

	//create a REQUEST SENSE packet
	memset(packet, 0, 12);
	packet[0] = ATAPI_CMD_REQUEST_SENSE;
	packet[4] = 18;

	//send it
	uint8_t senseData[18];
	res = sendPacket(packet, 18, false, (uint16_t*) senseData, 1);
	if (res == 1) {
		kprintf("err 2...\n");

		//drive not ready, probably no disk
		if (diskIn) {
			diskRemoved();
			return;
		}
	}

	//check there is actually error data
	if ((senseData[0] & 0x7F) != 0x70) {
		kprintf("in 1...\n");

		if (!diskIn) {
			diskInserted();
		}
	}

	//parse the response
	uint8_t senseKey = senseData[2] & 0xF;
	uint8_t additionalSenseCode = senseData[12];

	//check for NO MEDIA
	if (senseKey == 0x02 && additionalSenseCode == 0x3A) {
		kprintf("in 2...\n");
		if (diskIn) {
			diskRemoved();
		}

		//check for success (meaning there is a disk)
	} else if (senseKey == 0x00) {
		kprintf("out 1...\n");
		if (!diskIn) {
			diskInserted();
		}
	}
}

int SATAPI::eject()
{
	//eject the disk
	uint8_t packet[12] = { ATAPI_CMD_EJECT, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };
	sendPacket(packet, 2, false, nullptr, 0);

	//acknowledge the removed disk
	if (diskIn) {
		diskRemoved();
	}

	return 0;
}