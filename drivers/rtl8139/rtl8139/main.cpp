#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/common.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "hw/bus/pci.hpp"

#include <net/ethernet.hpp>

extern "C" {
	#include "libk/string.h"
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define REG_MAC_BASE		0x00
#define REG_MAR_BASE		0x08
#define REG_TRANS_STATUS	0x10
#define REG_TRANS_START		0x20
#define REG_RBSTART			0x30
#define REG_COMMAND			0x37
#define REG_IMR				0x3C
#define REG_ISR				0x3E
#define REG_RCR				0x44
#define REG_CONFIG1			0x52



void start(Device* _dvl)
{
	Device* driverless = _dvl;
	Device* parent = driverless->getParent();

	RTL8139* dev = new RTL8139();
	parent->addChild(dev);
	dev->preOpenPCI(driverless->pci.info);
	dev->open_(0, 0, nullptr);

}

RTL8139::RTL8139(): NIC ("RTL8139 Ethernet Controller")
{
	kprintf("RTL8139 E\n");

}

void RTL8139::reset()
{
	thePCI->writeBAR8(base, 0x10, REG_COMMAND);

	int timeout = 0;
	while ((thePCI->readBAR8(base, REG_COMMAND) & 0x10) != 0) {
		++timeout;

		if (timeout > 80000) {
			KePanic("[BROKEN] RTL8139");
			break;
		}
	}

	transmitCycle = 0;
}

#define R_OK	1
#define R_ERR	2
#define T_OK	4
#define T_ERR	8

void rtl8139IRQHandler(regs* r, void* ctxt)
{
	RTL8139* rtl = (RTL8139*) ctxt;

	uint8_t status = thePCI->readBAR16(rtl->base, REG_ISR);

	if (status & R_OK) {
		kprintf("Received a packet!\n");

		uint16_t* buffer = rtl->rxBufferVirt + currentPacketPointer;

		uint16_t length = buffer[1];
		uint8_t* packet = (uint8_t*) malloc(length);
		memcpy(packet, buffer + 2, length);
		EthernetReceivedPacket(packet, length);

		free(packet);

	} else if (status & T_OK) {
		kprintf("Sent a packet!\n");

	} else if (status & R_ERR) {
		kprintf("Failed to receive a packet!\n");

	} else if (status & T_ERR) {
		kprintf("Failed to send a packet!\n");
	}

	thePCI->writeBAR16(rtl->base, 0x0001, REG_ISR);
}

int RTL8139::open(int a, int b, void* c)
{
	return 0;
}

int RTL8139::open_(int a, int b, void* c)
{
	//set bit 2 in the PCI command register

	uint16_t w = thePCI->pciReadWord(pci.info.bus, pci.info.slot, pci.info.function, 0x4);
	thePCI->pciWriteWord(pci.info.bus, pci.info.slot, pci.info.function, 0x4, w | 4);

	base = this->pci.info.bar[0];

	thePCI->writeBAR8(base, 0x00, REG_CONFIG1);
	reset();

	mac = thePCI->readBAR8(base, REG_MAC_BASE + 0);
	mac <<= 8;
	mac |= thePCI->readBAR8(base, REG_MAC_BASE + 1);
	mac <<= 8;
	mac |= thePCI->readBAR8(base, REG_MAC_BASE + 2);
	mac <<= 8;
	mac |= thePCI->readBAR8(base, REG_MAC_BASE + 3);
	mac <<= 8;
	mac |= thePCI->readBAR8(base, REG_MAC_BASE + 4);
	mac <<= 8;
	mac |= thePCI->readBAR8(base, REG_MAC_BASE + 5);

	kprintf("MAC ADDRESS (BIG ENDIAN) = 0x%X\n", mac);

	rxBufferPhys = 0;
	rxBufferVirt = 0;

	thePCI->writeBAR32(base, rxBufferPhys, REG_RBSTART);
	thePCI->writeBAR16(base, 0x0005, REG_IMR);
	thePCI->writeBAR32(base, 0x008F, REG_RCR);
	thePCI->writeBAR8(base, 0x0C, REG_COMMAND);

	installIRQHandler(pci.info.interrrupt, rtl8139IRQHandler, false, (void*) this);

	return 0;
}

int RTL8139::close(int, int, void*)
{
	return 0;
}

uint64_t RTL8139::getMAC()
{
	return mac;
}


int RTL8139::write(int len, uint8_t* data, int* br)
{
	int timeout = 0;
	while (!(thePCI->readBAR32(base, REG_TRANS_STATUS + transmitCycle * 4) & (1 << 13))) {
		if (++timeout == 100000) {
			return NS_TIMEOUT;
		}
	}

	size_t physAddr = 0;		//need data physical address, also lock this memory range

	size_t status = len & 0x1FFF;

	thePCI->writeBAR32(base, physAddr, REG_TRANS_START + transmitCycle * 4);
	thePCI->writeBAR32(base, status, REG_TRANS_STATUS + transmitCycle * 4);

	transmitCycle = (transmitCycle + 1) & 3;

	return 0;
}
