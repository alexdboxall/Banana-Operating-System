#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
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

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

SATABus::SATABus() : HardDiskController("Advanced Host Controller Interface")
{

}

int SATABus::open(int, int, void*)
{
	return 0;
}

int SATABus::close(int, int, void*)
{
	return 0;
}

void SATABus::detect()
{

}

void SATABus::probePort(HBA_MEM* abar)
{
	uint32_t pi = abar->pi;

	for (int i = 0; i < 32; ++i) {
		if (pi & 1) {
			int dt = checkType(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA) {
				kprintf("SATA drive at port %d\n", i);
			} else if (dt == AHCI_DEV_SATA) {
				kprintf("SATAPI drive at port %d\n", i);
			} else if (dt == AHCI_DEV_SATA) {
				kprintf("SEMB drive at port %d\n", i);
			} else if (dt == AHCI_DEV_SATA) {
				kprintf("PM drive at port %d\n", i);
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