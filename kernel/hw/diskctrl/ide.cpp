#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hw/diskphys/ata.hpp"
#include "hw/diskphys/atapi.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "hal/device.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-Wcast-align"

IDE::IDE(): HardDiskController("Standard IDE Controller")
{

}

void IDE::prepareInterrupt(uint8_t channel)
{
	irqInvoked[channel] = false;
}

bool IDE::waitInterrupt(uint8_t channel)
{
	int timeout = 0;
	while (!irqInvoked[channel]) {
		uint8_t status = read(channel, ATA_REG_ALTSTATUS);
		if ((status & ATA_SR_ERR)) {
			return false;
		}
		if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) {
			//return true;
		}

		if ((timeout & 4) == 0 && timeout > 50) milliTenthSleep(100);		//10ms but may be longer (other tasks will run)
		if (timeout >= 60) {												//25ms but may be much longer (other tasks will run)
			return false;
		}
		++timeout;
	}

	irqInvoked[channel] = false;
	return true;
}

void ideChannel0IRQHandler(regs* r, void* context)
{
	IDE* ide = (IDE*) context;
	ide->irqInvoked[0] = true;

	ide->read(0, ATA_REG_STATUS);
}

void ideChannel1IRQHandler(regs* r, void* context)
{
	IDE* ide = (IDE*) context;
	ide->irqInvoked[1] = true;

	ide->read(1, ATA_REG_STATUS);
}

int IDE::open(int a, int, void*)
{
	KeDisablePreemption();

	channels[0].busMastering = 0;
	channels[1].busMastering = 0;
	legacyIRQs = false;

	if (detectionType == DetectionType::PCI) {
		if ((pci.info.progIF & 0x7F) == 0x05 || (pci.info.progIF & 0x7F) == 0x0F) {
			channels[0].base = pci.info.bar[0] & ~3;
			channels[0].ctrl = pci.info.bar[1] & ~3;
			channels[1].base = pci.info.bar[2] & ~3;
			channels[0].ctrl = pci.info.bar[3] & ~3;

		} else {
			channels[0].base = 0x1F0;
			channels[0].ctrl = 0x3F6;
			channels[1].base = 0x170;
			channels[1].ctrl = 0x376;
		}

		outl(0xCF8, (1 << 31) | (pci.info.bus << 16) | (pci.info.slot << 11) | (pci.info.function << 8) | 8);			// Send the parameters.
		if ((inl(0xCFC) >> 16) != 0xFFFF) {																				// If device exists (class isn't 0xFFFF)
			// Check if this device needs an IRQ assignment:
			outl(0xCF8, (1 << 31) | (pci.info.bus << 16) | (pci.info.slot << 11) | (pci.info.function << 8) | 0x3C);		// Read the interrupt line field
			outb(0xCFC, 0xFE);																								// Change the IRQ field to 0xFE
			outl(0xCF8, (1 << 31) | (pci.info.bus << 16) | (pci.info.slot << 11) | (pci.info.function << 8) | 0x3C);		// Read the interrupt line field
			if ((inl(0xCFC) & 0xFF) == 0xFE) {
				// This device needs an IRQ assignment.

				if (computer->features.hasAPIC) {
					interrupt = computer->root->getPCIIRQAssignment(pci.info.bus, pci.info.slot, pci.info.intPIN + 1).interrupt;

				} else {
					interrupt = 14;
				}

				outl(0xCF8, (1 << 31) | (pci.info.bus << 16) | (pci.info.slot << 11) | (pci.info.function << 8) | 0x3C);		// Read the interrupt line field
				outb(0xCFC, interrupt);

				outl(0xCF8, (1 << 31) | (pci.info.bus << 16) | (pci.info.slot << 11) | (pci.info.function << 8) | 0x3C);
				if ((inl(0xCFC) & 0xFF) != interrupt) {
					KePanic("BADNESS");
				}

			} else {
				// The device doesn't use IRQs, check if this is an Parallel IDE:
				if (pci.info.classCode == 0x01 && pci.info.subClass == 0x01 && (pci.info.progIF == 0x8A || pci.info.progIF == 0x80)) {
					legacyIRQs = true;
				} else {
					KePanic("IDE DOESN'T HAVE ANY CLUE WHAT ITS IRQ NUMBER IS");
				}
			}
		} else {
			KePanic("THE EXISITNG PCI IDE DEVICE DOESN'T EXIST");
		}

		if (pci.info.progIF & 0x80) {
			channels[0].busMastering = pci.info.bar[4] & ~3;
			channels[1].busMastering = channels[0].busMastering + 8;
		}

	} else {
		channels[0].base = isaprobe.probeBaseA;
		channels[0].ctrl = isaprobe.probeBaseA + 0x206;
		channels[1].base = isaprobe.probeBaseB;
		channels[1].ctrl = isaprobe.probeBaseB + 0x206;

		legacyIRQs = true;
	}

	for (int i = 0; i < 2; ++i) {
		if ((channels[i].ctrl & 0xF) == 0x8) {
			channels[i].ctrl -= 2;
		}
	}

	ports[noPorts].rangeStart = channels[0].base;
	ports[noPorts].rangeLength = 8;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = channels[1].base;
	ports[noPorts].rangeLength = 8;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = channels[0].ctrl;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = channels[1].ctrl;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
	
	if (channels[0].busMastering) {
		ports[noPorts].rangeStart = channels[0].busMastering;
		ports[noPorts].rangeLength = 16;
		ports[noPorts++].width = 0;
	}

	prepareInterrupt(0);
	prepareInterrupt(1);

	//disable IRQs
	enableIRQs(0, false);
	enableIRQs(1, false);

	if (legacyIRQs) {
		interrupt = addIRQHandler(14, ideChannel0IRQHandler, true, this);
		interrupt2 = addIRQHandler(15, ideChannel1IRQHandler, true, this);
	} else {
		interrupt2 = 15;
		addIRQHandler(interrupt, ideChannel0IRQHandler, false, this);
		addIRQHandler(interrupt2, ideChannel1IRQHandler, false, this);
	}

	detect();

	read(0, ATA_REG_STATUS);
	read(1, ATA_REG_STATUS);

	enableIRQs(0, true);
	enableIRQs(1, true);

	KeRestorePreemption();

	return 0;
}

void IDE::enableIRQs(uint8_t channel, bool on)
{
	KeDisablePreemption();

	channels[channel].nIEN = on ? 0 : 2;
	write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
	for (int i = 0; i < 4; ++i) {
		read(channel, ATA_REG_ALTSTATUS);
	}

	KeRestorePreemption();
}

void selectDrive(uint8_t channel, uint8_t drive) {

}

uint16_t IDE::getBase(uint8_t channel)
{
	return channels[channel].base;
}

int IDE::close(int a, int b, void* c)
{
	return -1;
}

uint8_t IDE::read(uint8_t channel, uint8_t reg)
{
	uint8_t result = 0;
	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
	}
	
	if (reg < 0x08) {
		result = inb(channels[channel].base + reg - 0x00);

	} else if (reg < 0x0C) {
		result = inb(channels[channel].base + reg - 0x06);

	} else if (reg < 0x0E) {
		result = inb(channels[channel].ctrl + reg - 0x0C);	//0x0C

	} else if (reg < 0x16) {
		result = inb(channels[channel].busMastering + reg - 0x0E);
	}

	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
	}

	return result;
}

void IDE::write(uint8_t channel, uint8_t reg, uint8_t data)
{
	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
	}

	if (reg < 0x08) {
		outb(channels[channel].base + reg - 0x00, data);

	} else if (reg < 0x0C) {
		outb(channels[channel].base + reg - 0x06, data);

	} else if (reg < 0x0E) {
		outb(channels[channel].ctrl + reg - 0x0C, data);

	} else if (reg < 0x16) {
		outb(channels[channel].busMastering + reg - 0x0E, data);
	}

	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
	}
}

void IDE::readBuffer(uint8_t channel, uint8_t reg, uint32_t buffer,
					 uint32_t quads)
{
	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
	}
	if (reg < 0x08) {
		insl(channels[channel].base + reg - 0x00, (void*) (size_t) buffer, quads);
	} else if (reg < 0x0C) {
		insl(channels[channel].base + reg - 0x06, (void*) (size_t) buffer, quads);
	} else if (reg < 0x0E) {
		insl(channels[channel].ctrl + reg - 0x0C, (void*) (size_t) buffer, quads);
	} else if (reg < 0x16) {
		insl(channels[channel].busMastering + reg - 0x0E, (void*) (size_t) buffer, quads);
	}
	if (reg > 0x07 && reg < 0x0C) {
		write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
	}
}

uint8_t IDE::printError(uint8_t channel, uint8_t drive, uint8_t err)
{
	if (err == 0) {
		return err;
	}

	drive |= channel << 1;

	kprintf("IDE ERROR: ");
	if (err == 1) {
		err = 19;

	} else if (err == 2) {
		unsigned char st = read(devices[drive].channel, ATA_REG_ERROR);
		if (st & ATA_ER_AMNF) {
			err = 7;
		}
		if (st & ATA_ER_TK0NF) {
			err = 3;
		}
		if (st & ATA_ER_ABRT) {
			err = 20;
		}
		if (st & ATA_ER_MCR) {
			err = 3;
		}
		if (st & ATA_ER_IDNF) {
			err = 21;
		}
		if (st & ATA_ER_MC) {
			err = 3;
		}
		if (st & ATA_ER_UNC) {
			err = 22;
		}
		if (st & ATA_ER_BBK) {
			err = 13;
		}

	} else if (err == 3) { 
		err = 23;
	} else if (err == 4) { 
		err = 8; 
	}

	return err;
}

uint8_t IDE::polling(uint8_t channel, uint32_t advanced_check)
{
	// Delay 400 nanosecond for BSY to be set:
	for (int i = 0; i < 4; i++) {
		read(channel, ATA_REG_ALTSTATUS);		// Reading the Alternate Status port wastes 100ns; loop four times.
	}
	
	uint8_t statusReg;
	int timeout = 0;
	while (1) {
		statusReg = read(channel, ATA_REG_ALTSTATUS);
		if (statusReg & ATA_SR_ERR) {
			return 2;
		}
		if (statusReg & ATA_SR_DF) {
			return 1;
		}

		++timeout;
		if (timeout >= 100000) {
			return 2;
		}

		if (!(statusReg & ATA_SR_BSY) && (statusReg & ATA_SR_DRQ)) {
			break;
		}
	}

	return 0;
}

void IDE::detect()
{
	extern int getIRQNestingLevel();

	if (detectDone) return;
	detectDone = true;

	KeDisablePreemption();

	int deviceCount = 0;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {

			uint8_t err = 0;
			uint8_t type = IDE_ATA;
			uint8_t status = 0;

			devices[deviceCount].reserved = 0;

			write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);

			write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);
			read(i, ATA_REG_ALTSTATUS);

			if (read(i, ATA_REG_ALTSTATUS) == 0) {
				continue;
			}

			int timeout = 0;
			while (1) {
				status = read(i, ATA_REG_ALTSTATUS);
				if ((status & ATA_SR_ERR)) {
					err = 1;
					break;
				}
				if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) {
					break;
				}
				++timeout;
				if (timeout >= 280) {
					milliTenthSleep(50);
				}
				if (timeout == 300) {
					err = 1;
					break;
				}
			}

			if (err != 0) {
				uint8_t cl = read(i, ATA_REG_LBA1);
				uint8_t ch = read(i, ATA_REG_LBA2);

				if (cl == 0x14 && ch == 0xEB) {
					type = IDE_ATAPI;
				} else if (cl == 0x69 && ch == 0x96) {
					type = IDE_ATAPI;
				} else {
					continue;
				}

				write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
				milliTenthSleep(10);
			}

			uint8_t ideBuf[512];
			readBuffer(i, ATA_REG_DATA, (size_t) ideBuf, 128);

			devices[deviceCount].reserved = 1;
			devices[deviceCount].type = type;
			devices[deviceCount].channel = i;
			devices[deviceCount].drive = j;
			devices[deviceCount].signature = *((uint16_t*) (ideBuf + ATA_IDENT_DEVICETYPE));
			devices[deviceCount].capabilities = *((uint16_t*) (ideBuf + ATA_IDENT_CAPABILITIES));
			devices[deviceCount].commandSets = *((uint8_t*) (ideBuf + ATA_IDENT_COMMANDSETS));

			if (devices[deviceCount].commandSets & (1 << 26)) {
				devices[deviceCount].size = *((uint32_t*) (ideBuf + ATA_IDENT_MAX_LBA_EXT));
			} else {
				devices[deviceCount].size = *((uint32_t*) (ideBuf + ATA_IDENT_MAX_LBA));
			}

			for (int k = 0; k < 40; k += 2) {
				devices[deviceCount].model[k] = ideBuf[ATA_IDENT_MODEL + k + 1];
				devices[deviceCount].model[k + 1] = ideBuf[ATA_IDENT_MODEL + k];
			}
			devices[deviceCount].model[40] = 0;

			devices[deviceCount].hasLBA = devices[deviceCount].capabilities & 0x200;

			if (type == IDE_ATA && devices[deviceCount].size) {
				ATA* dev = new ATA();
				addChild(dev);
				dev->open(0, deviceCount, this);

			} else if (type == IDE_ATAPI) {
				ATAPI* dev = new ATAPI();
				addChild(dev);
				dev->open(0, deviceCount, this);
			}

			deviceCount++;
		}
	}

	KeRestorePreemption();
}

#pragma GCC diagnostic pop