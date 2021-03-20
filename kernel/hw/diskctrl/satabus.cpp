#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hw/diskphys/sata.hpp"
#include "hal/device.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM		0x96690101	// Port multiplier

#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM 3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE		1
#define HBA_PORT_DET_PRESENT	3

#define HBA_PxCMD_ST    0x0001
#define HBA_PxCMD_FRE   0x0010
#define HBA_PxCMD_FR    0x4000
#define HBA_PxCMD_CR    0x8000

SATABus::SATABus() : HardDiskController("Advanced Host Controller Interface")
{
	//AHCI systems usually aren't that memory constrained
	//so this allocation shouldn't much matter
	AHCI_BASE = (uint32_t) malloc(303104 + 4096);
	AHCI_BASE = (AHCI_BASE + 4095) & ~0xFFF;
	AHCI_BASE = 0x60000;
	kprintf("AHCI BASE at 0x%X\n", AHCI_BASE);
}

int SATABus::open(int, int, void*)
{
	abar = (HBA_MEM*) (size_t) pci.info.bar[5];
	probePort(abar);

	return 0;
}

int SATABus::close(int, int, void*)
{
	return 0;
}

void SATABus::detect()
{

}

int SATABus::findCmdslot(HBA_PORT* port)
{
	uint32_t slots = (port->sact | port->ci);
	int cmdslots = (abar->cap & 0x0f00) >> 8; // Bit 8-12

	for (int i = 0; i < cmdslots; i++) {
		if ((slots & 1) == 0) {
			return i;
		}
		slots >>= 1;
	}
	panic("Cannot find free command list entry\n");
	return -1;
}

void SATABus::probePort(HBA_MEM* abar)
{
	uint32_t pi = abar->pi;

	for (int i = 0; i < 32; ++i) {
		if (pi & 1) {
			int dt = checkType(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA) {
				kprintf("SATA drive at port %d\n", i);
				portRebase(&abar->ports[i], i);

				SATA* dev = new SATA();
				addChild(dev);
				dev->open(i, 0, this);

			} else if (dt == AHCI_DEV_SATAPI) {
				kprintf("SATAPI drive at port %d\n", i);
				portRebase(&abar->ports[i], i);

			} else if (dt == AHCI_DEV_SATA) {
				kprintf("SEMB drive at port %d\n", i);
				portRebase(&abar->ports[i], i);

			} else if (dt == AHCI_DEV_SATA) {
				kprintf("PM drive at port %d\n", i);
				portRebase(&abar->ports[i], i);

			} else {
				kprintf("No drive at port %d\n", i);
			}
		}

		pi >>= 1;
	}
}

int SATABus::checkType(HBA_PORT* port)
{
	uint32_t ssts = port->ssts;
	uint8_t ipm = (ssts >> 8) & 0x0F;
	uint8_t det = (ssts >> 0) & 0x0F;

	if (det != HBA_PORT_DET_PRESENT) {
		return AHCI_DEV_NULL;
	}

	if (ipm != HBA_PORT_IPM_ACTIVE) {
		return AHCI_DEV_NULL;
	}

	switch (port->sig) {
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;

	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;

	case AHCI_DEV_PM:
		return AHCI_DEV_PM;

	default:
		return AHCI_DEV_SATA;
	}
}

void SATABus::portRebase(HBA_PORT* port, int portNo)
{
	// Stop command engine
	stopCmd(port);	

	// Command list offset: 1K*portNo
	// Command list entry size = 32
	// Command list entry maxim count = 32
	// Command list maxim size = 32*32 = 1K per port
	port->clb = AHCI_BASE + (portNo << 10);
	port->clbu = 0;
	kprintf("port->clb = 0x%X\n", port->clb);
	memset((void*) (port->clb), 0, 1024);

	// FIS offset: 32K+256*portNo
	// FIS entry size = 256 bytes per port
	port->fb = AHCI_BASE + (32 << 10) + (portNo << 8);
	port->fbu = 0;
	memset((void*) (port->fb), 0, 256);

	// Command table offset: 40K + 8K*portNo
	// Command table size = 256*32 = 8K per port
	HBA_CMD_HEADER* cmdheader = (HBA_CMD_HEADER*) (port->clb);
	for (int i = 0; i < 32; i++) {
		cmdheader[i].prdtl = 8;	// 8 prdt entries per command table
					// 256 bytes per command table, 64+16+48+16*8
		// Command table offset: 40K + 8K*portNo + cmdheader_index*256
		cmdheader[i].ctba = AHCI_BASE + (40 << 10) + (portNo << 13) + (i << 8);
		cmdheader[i].ctbau = 0;
		memset((void*) cmdheader[i].ctba, 0, 256);
	}

	startCmd(port);	// Start command engine
}

void SATABus::startCmd(HBA_PORT* port)
{
	// Wait until CR (bit15) is cleared
	while (port->cmd & HBA_PxCMD_CR) {
		;
	}

	// Set FRE (bit4) and ST (bit0)
	port->cmd |= HBA_PxCMD_FRE;
	port->cmd |= HBA_PxCMD_ST;
}

void SATABus::stopCmd(HBA_PORT* port)
{
	// Clear ST (bit0)
	port->cmd &= ~HBA_PxCMD_ST;

	// Clear FRE (bit4)
	port->cmd &= ~HBA_PxCMD_FRE;

	// Wait until FR (bit14), CR (bit15) are cleared
	while (1) {
		if (port->cmd & HBA_PxCMD_FR) {
			continue;
		}
		if (port->cmd & HBA_PxCMD_CR) {
			continue;
		}
		break;
	}
}