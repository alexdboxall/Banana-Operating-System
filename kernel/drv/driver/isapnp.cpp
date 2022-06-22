#pragma once

#include <drv/driver/isapnp.hpp>
#include <dbg/kconsole.hpp>
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>
#include <krnl/hal.hpp>
#include <drv/unknown.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define READ_DATA_LOWEST_PORT	0x0203
#define READ_DATA_HIGHEST_PORT	0x03F3

#define CMD_SET_READ_DATA			0
#define CMD_SERIAL_ISOLATION		1
#define CMD_CONFIG_CONTROL			2
#define CMD_WAKE_CSN				3
#define CMD_RESOURCE_DATA			4
#define CMD_STATUS					5
#define CMD_CARD_SELECT_NUMBER		6
#define CMD_SELECT_LOGICAL_DEVICE	7

void ISAPnPDriver::changeReadPortBase()
{
	kprintf("Changing PnP base.\n");
	for (int i = READ_DATA_PORT + 4; i < READ_DATA_HIGHEST_PORT; i += 4) {
		kprintf("checking port 0x%X (PnP)\n", i);
		if (!KeIsPortInUse(i, 1)) {
			READ_DATA_PORT = i;
			kprintf("Setting ISA PnP read port to 0x%X\n", READ_DATA_PORT);

			writeRegister(CMD_SET_READ_DATA, (READ_DATA_PORT >> 3));
			//milliTenthSleep(25);

			return;
		}
		kprintf(".\n");
	}
	kprintf("port base changed.\n");
}

void ISAPnPDriver::resetAllCards()
{
	writeRegister(CMD_CONFIG_CONTROL, 0b101);
	//milliTenthSleep(25);
}

void ISAPnPDriver::sendInitiationKey()
{
	const uint8_t key[] = {
		0x6A,0xB5,0xDA,0xED,0xF6,0xFB,0x7D,0xBE,
	    0xDF,0x6F,0x37,0x1B,0x0D,0x86,0xC3,0x61,
        0xB0,0x58,0x2C,0x16,0x8B,0x45,0xA2,0xD1,
        0xE8,0x74,0x3A,0x9D,0xCE,0xE7,0x73,0x39,
	};

	HalDisableInterrupts();

	// AMD recommends we do it twice in case it fails
	for (int i = 0; i < 2; ++i) {
		// clear anything already in ADDRESS
		outb(ADDRESS_PORT, 0x0);
		outb(ADDRESS_PORT, 0x0);

		// the actual key
		for (int j = 0; j < 32; ++j) {
			outb(ADDRESS_PORT, key[j]);
		}
	}

	HalEnableInterrupts();

	//milliTenthSleep(25);
}

uint64_t ISAPnPDriver::isolateCard()
{
	kprintf("Isolating ISA PnP card.\n -- WARNING: we might be shifting the wrong way! If you get bit reversed values to what you expect,\n       you should fix this code!\n");
	uint64_t value = 0;

	for (int i = 0; i < 64; ++i) {
		uint8_t v1 = inb(READ_DATA_PORT);
		uint8_t v2 = inb(READ_DATA_PORT);

		value <<= 1;
		if ((v1 == 0x55 && v2 == 0xAA) || (v1 == 0xAA && v2 == 0x55)) {
			value |= 1;
		}
	}

	// TODO: compute checksum

	uint8_t expectedChecksum = 0;
	uint8_t actualChecksum = 0;

	for (int i = 0; i < 8; ++i) {
		uint8_t v1 = inb(READ_DATA_PORT);
		uint8_t v2 = inb(READ_DATA_PORT);

		actualChecksum <<= 1;
		if ((v1 == 0x55 && v2 == 0xAA) || (v1 == 0xAA && v2 == 0x55)) {
			actualChecksum |= 1;
		}
	}

	kprintf("DEBUG!! IGNORING ISA PnP CHECKSUM\n");

	if (1 || expectedChecksum == actualChecksum) {
		return value;

	} else {
		// zero is never a valid value for the vendor ID / serial number
		// so use this as an error code
		return 0;
	}
}

void ISAPnPDriver::initialise()
{
	kprintf("@\n");

	// we can't trust the BIOS
	resetAllCards();

	kprintf("A\n");

	// after this, cards will listen to our commands
	sendInitiationKey();

	kprintf("B\n");

	// this sends all cards into the isolation state, and sets the
	// serial data pointer to the beginning
	writeRegister(CMD_WAKE_CSN, 0x0);

	kprintf("C\n");

	// READ_DATA is uninitialised after reset
	// 
	//	  "The first time the cards enter the Isolation state it is necessary 
	//	  to set the READ_DATA port address... "
	//
	READ_DATA_PORT = READ_DATA_LOWEST_PORT;
	changeReadPortBase();

	kprintf("D\n");

	// isolate all possible cards
	int cardsDetected = 0;
	int conflicts = 0;
	while (true) {
		uint64_t value = isolateCard();
		if (value == 0) {
			if (cardsDetected == 0) {
				// we probably have a conflict, so rebase
				changeReadPortBase();
				++conflicts;

				// if everything conflicts, it is more likely
				// that the PnP bus just doesn't exist on this machine
				if (conflicts >= 20) {
					kprintf("No ISA PnP found.\n");
					return;
				}

			} else {
				// no more data means all cards detected
				break;
			}

		} else {
			++cardsDetected;
			kprintf("Found an ISA PnP with value 0x%X (high) and 0x%X (low)\n", (uint32_t) (value >> 32), (uint32_t) value);
		
			uint8_t csn = readRegister(CMD_CARD_SELECT_NUMBER);
			kprintf("The CSN is 0x%X\n\n", csn);

			UnknownHardware* deviceChild = new UnknownHardware();
			deviceChild->setISAPnPDetection(csn, value);
			hw->addChild(deviceChild);


			// we can now access this card by calling Wake[CSN]
			
			// but we want to keep detecting, so call Wake[0] again
			// this will put our card to sleep, but not isolation
			// (all other cards will go to isolation)

			writeRegister(CMD_WAKE_CSN, 0x0);
		}
	}
	
	// we can only register READ_DATA_PORT after we have
	// found its final position (there is no hw->deregisterPortRange()... yet)
	hw->registerPortRange(WRITE_DATA_PORT, 1, 1);
	hw->registerPortRange(ADDRESS_PORT, 1, 1);
	hw->registerPortRange(READ_DATA_PORT, 1, 1);

}

void ISAPnPDriver::writeRegister(uint8_t address, uint8_t value)
{
	outb(ADDRESS_PORT, address);
	outb(WRITE_DATA_PORT, value);
}

uint8_t ISAPnPDriver::readRegister(uint8_t address)
{
	outb(ADDRESS_PORT, address);
	return inb(READ_DATA_PORT);
}

void ISAPnPDriver::detect()
{

}

void ISAPnPDriver::deinitialise()
{

}

void ISAPnPDriver::setPowerState(DevicePowerState state)
{

}

const char* ISAPnPDriver::getHumanReadableName()
{
	return ISA_PNP_DRIVER_NAME;
}