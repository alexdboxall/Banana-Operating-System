#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/computer.hpp" 
#include "core/terminal.hpp"
#include "core/prcssthr.hpp"
#include "fs/vfs.hpp"

#define PS2_COMMAND_REG 0x64
#define PS2_STATUS_REG	0x64
#define PS2_DATA_PORT	0x60

#define PS2_STATUS_BIT_OUT_FULL		1
#define PS2_STATUS_BIT_IN_FULL		2
#define PS2_STATUS_BIT_SYSFLAG		4
#define PS2_STATUS_BIT_CONTROLLER	8
#define PS2_STATUS_BIT_TIMEOUT		64
#define PS2_STATUS_BIT_PARITY		128

#define PS2_CMD_READ_RAM		0x20
#define PS2_CMD_WRITE_RAM		0x60
#define PS2_CMD_DISABLE_PORT_2	0xA7
#define PS2_CMD_ENABLE_PORT_2	0xA8
#define PS2_CMD_TEST_PORT_2		0xA9
#define PS2_CMD_TEST_CONTROLLER	0xAA
#define PS2_CMD_TEST_PORT_1		0xAB
#define PS2_CMD_DISABLE_PORT_1	0xAD
#define PS2_CMD_ENABLE_PORT_1	0xAE
#define PS2_CMD_READ_CONTROLLER_OUTPUT_PORT		0xD0
#define PS2_CMD_WRITE_CONTROLLER_OUTPUT_PORT	0xD1
#define PS2_CMD_WRITE_NEXT_TO_PORT_2_INPUT		0xD4

#define PS2_CONFIG_BIT_PORT_1_IRQ_ENABLE	1
#define PS2_CONFIG_BIT_PORT_2_IRQ_ENABLE	2
#define PS2_CONFIG_BIT_SYSFLAG				4
#define PS2_CONFIG_BIT_PORT_1_CLOCK_DISABLE	16
#define PS2_CONFIG_BIT_PORT_2_CLOCK_DISABLE	32
#define PS2_CONFIG_TRANSLATION_ENABLE		64

#define PS2_OUTPORT_BIT_RESET			1
#define PS2_OUTPORT_BIT_A20				2
#define PS2_OUTPORT_BIT_PORT_2_CLOCK	4
#define PS2_OUTPORT_BIT_PORT_2_DATA		8
#define PS2_OUTPORT_BIT_BUFFER_FULL_FROM_PORT_1	16
#define PS2_OUTPORT_BIT_BUFFER_FULL_FROM_PORT_2	32
#define PS2_OUTPORT_BIT_PORT_1_CLOCK	64
#define PS2_OUTPORT_BIT_PORT_1_DATA		128

#define PS2_DEV_CMD_IDENTIFY			0xF2
#define PS2_DEV_CMD_ENABLE_SCANNING		0xF4
#define PS2_DEV_CMD_DISABLE_SCANNING	0xF5
#define PS2_DEV_CMD_RESET				0xFF
#define PS2_DEV_CMD_RESEND				0xFE


extern "C" {
	#include "libk/string.h"
}

void start(Device* parent)
{
	PS2* dev = new PS2();
	parent->addChild(dev);
	dev->open(0, 0, nullptr);
}

char deviceNameString[] = "PS/2 Controller";
char device2NameString[] = "PS/2 Port";

char errTimeout[] = "PS/2 controller: hard timeout\n";
char errParity[] = "PS/2 controller: parity error\n";
char errSoftTimeout[] = "PS/2 controller: soft timeout\n";


PS2Port::PS2Port() : Bus(device2NameString)
{

}

int PS2Port::open(int p2, int b, void* parent)
{
	port2 = p2;
	ctrl = (PS2*) parent;

	detect();

	return 0;
}

int PS2Port::close(int a, int b, void* c)
{
	return 0;
}


#define WRITE_COMMAND_TO_DEVICE(COMMAND_TO_SEND) {\
uint8_t ack = 0xFE;\
int timeout = 0;\
while (ack != 0xFA) {\
	++timeout;\
	if (timeout == 500) {\
		break;\
	}\
	if (ack == 0xFE) {\
		write(COMMAND_TO_SEND);\
	}\
	ack = read();\
}\
}

char todoremovedev[] = "TODO: @@@ PS/2 REMOVE DEVICE\n";

void PS2Port::detect()
{
	disableIRQs();

	//WRITE_COMMAND_TO_DEVICE(PS2_DEV_CMD_DISABLE_SCANNING);

	WRITE_COMMAND_TO_DEVICE(PS2_DEV_CMD_IDENTIFY);

	DetectType type = DetectType::Nothing;

	uint8_t resp1 = read();
	if (resp1 == 0xFA) {
		resp1 = read();
	}
	if (resp1 == 0xFF) {
		type = DetectType::Nothing;
	} else if (resp1 == 0x00) {
		type = DetectType::Nothing;
	} else if (resp1 == 0x03) {
		type = DetectType::Nothing;
	} else if (resp1 == 0x04) {
		type = DetectType::Nothing;
	} else if (resp1 == 0xAB) {
		type = DetectType::Keyboard;
		read();
	} else {
		type = DetectType::Nothing;
	}

	WRITE_COMMAND_TO_DEVICE(PS2_DEV_CMD_ENABLE_SCANNING);

	if (type != previousType) {
		previousType = type;

		if (dev) {
			dev = nullptr;
		}

		if (type == DetectType::Keyboard) {
			PS2Keyboard* port2 = new PS2Keyboard();
			addChild(port2);
			dev = port2;
			WRITE_COMMAND_TO_DEVICE(PS2_DEV_CMD_RESET);
			port2->open(0, 0, (void*) this);
		}
	}

	enableIRQs();
}

uint8_t PS2Port::read()
{
	return ctrl->readController();
}

void PS2Port::write(uint8_t arg)
{
	if (port2) {
		ctrl->writeController(PS2_CMD_WRITE_NEXT_TO_PORT_2_INPUT);
	}

	int timeout = 0;
	while (1) {
		uint8_t status = inb(PS2_STATUS_REG);
		if (!(status & PS2_STATUS_BIT_IN_FULL)) {
			break;
		}
		++timeout;
		if (status & PS2_STATUS_BIT_TIMEOUT) {
			timeout = 800;
		}
		if (status & PS2_STATUS_BIT_PARITY) {
			timeout = 800;
		}
		if (timeout == 800) {
			outb(PS2_DATA_PORT, (uint8_t) arg);
			return;
		}
	}

	outb(PS2_DATA_PORT, (uint8_t) arg);
}

PS2::PS2(): Bus(deviceNameString)
{
	ports[noPorts].rangeStart = 0x60;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = 0x64;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
}

char wrongSelftest[] = "Self test byte isn't 0x55, it is 0x%X\n";
char twoch[] = "Two channels on PS/2 controller\n";
char onech[] = "One channel on PS/2 controller\n";
char ps2done[] = "PS/2 has been setup.\n";

int PS2::open(int, int, void*)
{
	disableIRQs();
 
	/*//step 3 - disable devices
	writeController(PS2_CMD_DISABLE_PORT_1);
	writeController(PS2_CMD_DISABLE_PORT_2);
*/

	//step 4 - flush the output buffer
	inb(PS2_DATA_PORT);
	inb(PS2_DATA_PORT);

	//step 5 - set the controller configuration byte
	uint8_t cfg = readConfigByte();
	//cfg &= ~PS2_CONFIG_BIT_PORT_1_IRQ_ENABLE;
	//cfg &= ~PS2_CONFIG_BIT_PORT_2_IRQ_ENABLE;
	cfg &= ~PS2_CONFIG_TRANSLATION_ENABLE;
	writeConfigByte(cfg);

	/*bool singleChannel = !(cfg & PS2_CONFIG_BIT_PORT_2_CLOCK_DISABLE);

	//step 6 - controller self test
	writeController(PS2_CMD_TEST_CONTROLLER);
	uint8_t checkVal = readController();

	if (checkVal != 0x55) {
		kprintf(wrongSelftest, checkVal);
		enableIRQs();
		return 1;
	}

	//step 7 - check for 2 channels
	bool twoChannels = false;
	if (!singleChannel) {
		writeController(PS2_CMD_ENABLE_PORT_2);

		uint8_t cfg = readConfigByte();
		twoChannels = !(cfg & PS2_CONFIG_BIT_PORT_2_CLOCK_DISABLE);

		if (twoChannels) {
			writeController(PS2_CMD_DISABLE_PORT_2);
		}
	}

	if (twoChannels) kprintf(twoch);
	else kprintf(onech);

	//step 8 - perform interface tests
	channel1 = false;
	channel2 = false;

	writeController(PS2_CMD_TEST_PORT_1);
	uint8_t res = readController();
	channel1 = res == 0;

	if (twoChannels) {
		writeController(PS2_CMD_TEST_PORT_2);
		res = readController();
		channel2 = res == 0;
	}*/


	channel1 = true;

	//step 9 - enable devices
	if (channel1) {
		writeController(PS2_CMD_ENABLE_PORT_1);
		uint8_t cfg = readConfigByte();
		cfg |= PS2_CONFIG_BIT_PORT_1_IRQ_ENABLE;
		writeConfigByte(cfg);

		PS2Port* port1 = new PS2Port();
		addChild(port1);
		port1->open(0, 0, (void*) this);
	}

	if (channel2) {
		writeController(PS2_CMD_ENABLE_PORT_2);
		uint8_t cfg = readConfigByte();
		cfg |= PS2_CONFIG_BIT_PORT_2_IRQ_ENABLE;
		writeConfigByte(cfg);

		PS2Port* port2 = new PS2Port();
		addChild(port2);
		port2->open(1, 0, (void*) this);
	}

	enableIRQs();

	return 0;
}

void PS2::detect()
{

}

int PS2::close(int, int, void*)
{
	return 0;
}

void PS2::writeController(uint8_t command)
{
	outb(PS2_COMMAND_REG, command);
}

void PS2::writeController(uint8_t command, uint8_t arg)
{
	writeController(command);

	int timeout = 0;
	while (1) {
		uint8_t status = inb(PS2_STATUS_REG);
		if (!(status & PS2_STATUS_BIT_IN_FULL)) {
			break;
		}
		++timeout;
		if (status & PS2_STATUS_BIT_TIMEOUT) {
			timeout = 800;
		}
		if (status & PS2_STATUS_BIT_PARITY) {
			timeout = 800;
		}
		if (timeout == 800) {
			outb(PS2_DATA_PORT, (uint8_t) arg);
			return;
		}
	}

	outb(PS2_DATA_PORT, (uint8_t) arg);
}

uint8_t PS2::readController()
{
	uint32_t timeout = 0;

	while (1) {
		uint8_t status = inb(PS2_STATUS_REG);

		if ((status & PS2_STATUS_BIT_OUT_FULL)) {
			break;
		}
		++timeout;
		if (status & PS2_STATUS_BIT_TIMEOUT) {
			timeout = 800;
		}
		if (status & PS2_STATUS_BIT_PARITY) {
			timeout = 800;
		}
		if (timeout == 800) {
			return 0xFF;
		}
	}

	return inb(PS2_DATA_PORT);
}

uint8_t PS2::readConfigByte()
{
	writeController(PS2_CMD_READ_RAM);
	uint8_t val = readController();
	return val;
}

void PS2::writeConfigByte(uint8_t data)
{
	writeController(PS2_CMD_WRITE_RAM, data);
}

bool PS2::translationOn()
{
	return (readConfigByte() & PS2_CONFIG_TRANSLATION_ENABLE) ? true : false;
}


#include "core/main.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/intctrl.hpp"
#include "hal/keybrd.hpp"
#include "core/prcssthr.hpp"

extern "C" {
#include "libk/string.h"
}

constexpr uint8_t PS2Keyboard::internalMapperLower[256];// = "              `      q1   zsaw2  cxde43   vftr5  nbhgy6   mju78  ,kio09  ./l;p-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
constexpr uint8_t PS2Keyboard::internalMapperUpper[256];// = "              ~      Q!   ZSAW@  CXDE$#   VFTR%  NBHGY^   MJU&*  <KIO)(  >?L:P_   \" {+     } |           1 47   0.2568   +3-*9              ";
constexpr uint8_t PS2Keyboard::internalMapCapLower[256];// = "              `      Q1   ZSAW2  CXDE43   VFTR5  NBHGY6   MJU78  ,KIO09  ./L;P-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
constexpr uint8_t PS2Keyboard::internalMapCapUpper[256];// = "              ~      Q!   zsaw@  cxde$#   vftr%  nbhgy^   mju&*  <kio)(  >?l:p_   \" {+     } |           1 47   0.2568   +3-*9              ";

constexpr uint8_t PS2Keyboard::internalMapperLowerBad[256];// = "              `      q1   zsaw2  cxde43   vftr5  nbhgy6   mju78  ,kio09  ./l;p-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
constexpr uint8_t PS2Keyboard::internalMapperUpperBad[256];// = "              ~      Q!   ZSAW@  CXDE$#   VFTR%  NBHGY^   MJU&*  <KIO)(  >?L:P_   \" {+     } |           1 47   0.2568   +3-*9              ";
constexpr uint8_t PS2Keyboard::internalMapCapLowerBad[256];// = "              `      Q1   ZSAW2  CXDE43   VFTR5  NBHGY6   MJU78  ,KIO09  ./L;P-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
constexpr uint8_t PS2Keyboard::internalMapCapUpperBad[256];// = "              ~      Q!   zsaw@  cxde$#   vftr%  nbhgy^   mju&*  <kio)(  >?l:p_   \" {+     } |           1 47   0.2568   +3-*9              ";


#define PS2_SCANCODE_backspace 0x66
#define PS2_SCANCODE_tab 0x0D
#define PS2_SCANCODE_capslock 0x58
#define PS2_SCANCODE_numberlock 0x77
#define PS2_SCANCODE_scrolllock 0x7E
#define PS2_SCANCODE_newline 0x5A
#define PS2_SCANCODE_f1 0x05
#define PS2_SCANCODE_f2 0x06
#define PS2_SCANCODE_f3 0x04
#define PS2_SCANCODE_f4 0x0C
#define PS2_SCANCODE_f5 0x03
#define PS2_SCANCODE_f6 0x0B
#define PS2_SCANCODE_f7 0x83
#define PS2_SCANCODE_f8 0x0A
#define PS2_SCANCODE_f9 0x01
#define PS2_SCANCODE_f10 0x09
#define PS2_SCANCODE_f11 0x78
#define PS2_SCANCODE_f12 0x07
#define PS2_SCANCODE_extension 0xE0
#define PS2_SCANCODE_breakcode 0xF0

#define PS2_SCANCODE_leftctrl 0x14
#define PS2_SCANCODE_leftshift 0x12
#define PS2_SCANCODE_rightshift 0x59
#define PS2_SCANCODE_leftalt 0x11

#define PS2_SCANCODE_up 0x75
#define PS2_SCANCODE_down 0x72
#define PS2_SCANCODE_left 0x6B
#define PS2_SCANCODE_right 0x74

#define PS2_SCANCODE_keypad0 0x70
#define PS2_SCANCODE_keypad1 0x69
#define PS2_SCANCODE_keypad2 0x72
#define PS2_SCANCODE_keypad3 0x7A
#define PS2_SCANCODE_keypad4 0x6B
#define PS2_SCANCODE_keypad5 0x73
#define PS2_SCANCODE_keypad6 0x74
#define PS2_SCANCODE_keypad7 0x6C
#define PS2_SCANCODE_keypad8 0x75
#define PS2_SCANCODE_keypad9 0x7D
#define PS2_SCANCODE_keypadPeriod 0x71
#define PS2_SCANCODE_keypadMinus 0x7B
#define PS2_SCANCODE_keypadPlus 0x79
#define PS2_SCANCODE_keypadMultiply 0x7C

#define PS2_SCANCODE_escape 0x76

//with ext.
#define PS2_SCANCODE_keypadEnter 0x5A			
#define PS2_SCANCODE_keypadDivide 0x4A
#define PS2_SCANCODE_home 0x6C
#define PS2_SCANCODE_end 0x69
#define PS2_SCANCODE_insert 0x70
#define PS2_SCANCODE_delete 0x71
#define PS2_SCANCODE_pageup 0x49
#define PS2_SCANCODE_pagedown 0x51



#define PS2_STUPID_backspace 0x0E
#define PS2_STUPID_tab 0x0F
#define PS2_STUPID_capslock 0x3A
#define PS2_STUPID_numberlock 0x45
#define PS2_STUPID_scrolllock 0x46
#define PS2_STUPID_newline 0x1C
#define PS2_STUPID_f1 0x3B
#define PS2_STUPID_f2 0x3C
#define PS2_STUPID_f3 0x3D
#define PS2_STUPID_f4 0x3E
#define PS2_STUPID_f5 0x3F
#define PS2_STUPID_f6 0x40
#define PS2_STUPID_f7 0x41
#define PS2_STUPID_f8 0x42
#define PS2_STUPID_f9 0x43
#define PS2_STUPID_f10 0x44
#define PS2_STUPID_f11 0x00
#define PS2_STUPID_f12 0x00
#define PS2_STUPID_extension 0xE0

#define PS2_STUPID_leftctrl 0x1D
#define PS2_STUPID_leftshift 0x2A
#define PS2_STUPID_rightshift 0x36
#define PS2_STUPID_leftalt 0x38

#define PS2_STUPID_up 0x48
#define PS2_STUPID_down 0x50
#define PS2_STUPID_left 0x4B
#define PS2_STUPID_right 0x4D

#define PS2_STUPID_keypad0 0x52
#define PS2_STUPID_keypad1 0x4F
#define PS2_STUPID_keypad2 0x50
#define PS2_STUPID_keypad3 0x51
#define PS2_STUPID_keypad4 0x4B
#define PS2_STUPID_keypad5 0x4C
#define PS2_STUPID_keypad6 0x4D
#define PS2_STUPID_keypad7 0x47
#define PS2_STUPID_keypad8 0x48
#define PS2_STUPID_keypad9 0x49
#define PS2_STUPID_keypadPeriod 0x53
#define PS2_STUPID_keypadMinus 0x4A
#define PS2_STUPID_keypadPlus 0x4E
#define PS2_STUPID_keypadMultiply 0x37

#define PS2_STUPID_escape 0x01

//with ext.
#define PS2_STUPID_keypadEnter 0x1C			
#define PS2_STUPID_keypadDivide 0x35
#define PS2_STUPID_home 0x47
#define PS2_STUPID_end 0x4F
#define PS2_STUPID_insert 0x52
#define PS2_STUPID_delete 0x53
#define PS2_STUPID_pageup 0x49
#define PS2_STUPID_pagedown 0x51

char dev3[] = "PS/2 Keyboard";

PS2Keyboard::PS2Keyboard(): Keyboard(dev3)
{
	
}

void PS2Keyboard::setRepeatRate(int t)
{

}

void PS2Keyboard::setRepeatDelay(int t)
{

}

void PS2Keyboard::sendKey(uint16_t halScancode, bool release)
{
	KeyboardToken k;
	k.release = release;
	k.halScancode = halScancode;
	k.numlock = numberLock;
	k.scrolllock = scrollLock;
	k.capslock = capslk;
	sendKeyboardToken(k);
}

void PS2Keyboard::sendKey(KeyboardSpecialKeys halScancode, bool release)
{
	KeyboardToken k;
	k.release = release;
	k.halScancode = (uint16_t) halScancode;
	k.numlock = numberLock;
	k.scrolllock = scrollLock;
	k.capslock = capslk;
	sendKeyboardToken(k);
}

void PS2Keyboard::updateKeyboardLEDs()
{
	uint8_t v = capslk << 2;
	v |= scrollLock << 1;
	v |= numberLock;

	/*((PS2Port*) this->parent)->write(0xED, 0, nullptr);
	((PS2Port*) this->parent)->ioctl(0, 0, nullptr);
	((PS2Port*) this->parent)->write(v, 0, nullptr);
	((PS2Port*) this->parent)->ioctl(0, 0, nullptr);*/
}
 
void ps2KeyboardHandler(regs* r, void* context)
{
	((PS2Keyboard*) context)->handler();
}

void PS2Keyboard::handler()
{
	/*uint8_t status = inb(0x64);
	if ((status & 1) == 0) return;	//no data

	if (port->port2) {
		if (!(status & 0x20)) return;	//mouse data
	} else {
		if ((status & 0x20)) return;	//mouse data
	}*/

	uint8_t c = inb(0x60);

	if (badTranslation) {
		if (c == PS2_STUPID_extension) {
			extended = true;
			return;
		}
		if (c & 0x80) {
			nextIsARelease = true;
			c &= 0x7F;
		}

	} else {
		if (c == PS2_SCANCODE_extension) {
			extended = true;
			return;
		}
		if (c == PS2_SCANCODE_breakcode) {
			nextIsARelease = true;
			return;
		}
	}

	//a lot of code in here...
	if (badTranslation) {
		switch (c) {
		case PS2_STUPID_leftctrl:
			ctrl = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Ctrl, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;

		case PS2_STUPID_leftshift:                    //SHIFT
		case PS2_STUPID_rightshift:                    //RIGHT SHIFT
			caps = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Shift, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;

		case PS2_STUPID_leftalt:
			altR = nextIsARelease ^ 1;
			alt = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Alt, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;
		}

		if (extended) {
			switch (c) {
			case PS2_STUPID_up:		//Up
				sendKey(KeyboardSpecialKeys::Up, nextIsARelease);
				break;

			case PS2_STUPID_down:		//Down
				sendKey(KeyboardSpecialKeys::Down, nextIsARelease);
				break;

			case PS2_STUPID_left:		//Left
				sendKey(KeyboardSpecialKeys::Left, nextIsARelease);
				break;

			case PS2_STUPID_right:		//Right
				sendKey(KeyboardSpecialKeys::Right, nextIsARelease);
				break;

			case PS2_STUPID_pageup:
				sendKey(KeyboardSpecialKeys::PageUp, nextIsARelease);
				break;

			case PS2_STUPID_pagedown:
				sendKey(KeyboardSpecialKeys::PageDown, nextIsARelease);
				break;

			case PS2_STUPID_home:
				sendKey(KeyboardSpecialKeys::Home, nextIsARelease);
				break;

			case PS2_STUPID_end:
				sendKey(KeyboardSpecialKeys::End, nextIsARelease);
				break;

			case PS2_STUPID_delete:
				sendKey(KeyboardSpecialKeys::Delete, nextIsARelease);
				break;

			case PS2_STUPID_insert:
				sendKey(KeyboardSpecialKeys::Insert, nextIsARelease);
				break;

			case PS2_STUPID_keypadEnter:
				sendKey(KeyboardSpecialKeys::KeypadEnter, nextIsARelease);
				break;

			case PS2_STUPID_keypadDivide:
				sendKey(KeyboardSpecialKeys::KeypadDivide, nextIsARelease);
				break;
			}
			nextIsARelease = false;
			extended = false;
			return;
		}


		if (c == PS2_STUPID_backspace) {
			sendKey(KeyboardSpecialKeys::Backspace, nextIsARelease);

		} else if (c == PS2_STUPID_tab) {        //tab
			sendKey(KeyboardSpecialKeys::Tab, nextIsARelease);

		} else if (c == PS2_STUPID_capslock) {       //CAPS
			if (!nextIsARelease) {		//only toggle on press, not release
				capslk ^= 1;
				updateKeyboardLEDs();
			}
			sendKey(KeyboardSpecialKeys::CapsLock, nextIsARelease);

		} else if (c == PS2_STUPID_numberlock) {
			if (!nextIsARelease) {		//only toggle on press, not release
				numberLock ^= 1;
				updateKeyboardLEDs();
			}
			sendKey(KeyboardSpecialKeys::NumLock, nextIsARelease);

		} else if (c == PS2_STUPID_scrolllock) {
			if (!nextIsARelease) {		//only toggle on press, not release
				scrollLock ^= 1;
				updateKeyboardLEDs();
			}
			sendKey(KeyboardSpecialKeys::ScrollLock, nextIsARelease);

		} else if (c == PS2_STUPID_f1) {
			sendKey(KeyboardSpecialKeys::F1, nextIsARelease);

		} else if (c == PS2_STUPID_f2) {
			sendKey(KeyboardSpecialKeys::F2, nextIsARelease);

		} else if (c == PS2_STUPID_f3) {
			sendKey(KeyboardSpecialKeys::F3, nextIsARelease);

		} else if (c == PS2_STUPID_f4) {
			sendKey(KeyboardSpecialKeys::F4, nextIsARelease);

		} else if (c == PS2_STUPID_f5) {
			sendKey(KeyboardSpecialKeys::F5, nextIsARelease);

		} else if (c == PS2_STUPID_f6) {
			sendKey(KeyboardSpecialKeys::F6, nextIsARelease);

		} else if (c == PS2_STUPID_f7) {
			sendKey(KeyboardSpecialKeys::F7, nextIsARelease);

		} else if (c == PS2_STUPID_f8) {
			sendKey(KeyboardSpecialKeys::F8, nextIsARelease);

		} else if (c == PS2_STUPID_f9) {
			sendKey(KeyboardSpecialKeys::F9, nextIsARelease);

		} else if (c == PS2_STUPID_f10) {
			sendKey(KeyboardSpecialKeys::F10, nextIsARelease);

		} else if (c == PS2_STUPID_f11) {
			sendKey(KeyboardSpecialKeys::F11, nextIsARelease);

		} else if (c == PS2_STUPID_f12) {
			sendKey(KeyboardSpecialKeys::F12, nextIsARelease);

		} else if (c == PS2_STUPID_newline) {
			sendKey(KeyboardSpecialKeys::Enter, nextIsARelease);

		} else if (c == PS2_STUPID_escape) {
			sendKey(KeyboardSpecialKeys::Escape, nextIsARelease);

		} else if (c == PS2_STUPID_keypad0) {
			sendKey(KeyboardSpecialKeys::Keypad0, nextIsARelease);
		} else if (c == PS2_STUPID_keypad1) {
			sendKey(KeyboardSpecialKeys::Keypad1, nextIsARelease);
		} else if (c == PS2_STUPID_keypad2) {
			sendKey(KeyboardSpecialKeys::Keypad2, nextIsARelease);
		} else if (c == PS2_STUPID_keypad3) {
			sendKey(KeyboardSpecialKeys::Keypad3, nextIsARelease);
		} else if (c == PS2_STUPID_keypad4) {
			sendKey(KeyboardSpecialKeys::Keypad4, nextIsARelease);
		} else if (c == PS2_STUPID_keypad5) {
			sendKey(KeyboardSpecialKeys::Keypad5, nextIsARelease);
		} else if (c == PS2_STUPID_keypad6) {
			sendKey(KeyboardSpecialKeys::Keypad6, nextIsARelease);
		} else if (c == PS2_STUPID_keypad7) {
			sendKey(KeyboardSpecialKeys::Keypad7, nextIsARelease);
		} else if (c == PS2_STUPID_keypad8) {
			sendKey(KeyboardSpecialKeys::Keypad8, nextIsARelease);
		} else if (c == PS2_STUPID_keypad9) {
			sendKey(KeyboardSpecialKeys::Keypad9, nextIsARelease);
		} else if (c == PS2_STUPID_keypadPeriod) {
			sendKey(KeyboardSpecialKeys::KeypadPeriod, nextIsARelease);
		} else if (c == PS2_STUPID_keypadMinus) {
			sendKey(KeyboardSpecialKeys::KeypadMinus, nextIsARelease);
		} else if (c == PS2_STUPID_keypadPlus) {
			sendKey(KeyboardSpecialKeys::KeypadPlus, nextIsARelease);
		} else if (c == PS2_STUPID_keypadMultiply) {
			sendKey(KeyboardSpecialKeys::KeypadMultiply, nextIsARelease);

		} else {
			sendKey(caps && capslk ? internalMapCapUpperBad[c] :
					caps && !capslk ? internalMapperUpperBad[c] :
					!caps && capslk ? internalMapCapLowerBad[c] :
					internalMapperLowerBad[c], nextIsARelease);
		}

	} else {
		switch (c) {
		case PS2_SCANCODE_leftctrl:
			ctrl = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Ctrl, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;

		case PS2_SCANCODE_leftshift:                    //SHIFT
		case PS2_SCANCODE_rightshift:                    //RIGHT SHIFT
			caps = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Shift, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;

		case PS2_SCANCODE_leftalt:
			altR = nextIsARelease ^ 1;
			alt = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Alt, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;
		}

		if (extended) {
			switch (c) {
			case PS2_SCANCODE_up:		//Up
				sendKey(KeyboardSpecialKeys::Up, nextIsARelease);
				break;

			case PS2_SCANCODE_down:		//Down
				sendKey(KeyboardSpecialKeys::Down, nextIsARelease);
				break;

			case PS2_SCANCODE_left:		//Left
				sendKey(KeyboardSpecialKeys::Left, nextIsARelease);
				break;

			case PS2_SCANCODE_right:		//Right
				sendKey(KeyboardSpecialKeys::Right, nextIsARelease);
				break;

			case PS2_SCANCODE_pageup:
				sendKey(KeyboardSpecialKeys::PageUp, nextIsARelease);
				break;

			case PS2_SCANCODE_pagedown:
				sendKey(KeyboardSpecialKeys::PageDown, nextIsARelease);
				break;

			case PS2_SCANCODE_home:
				sendKey(KeyboardSpecialKeys::Home, nextIsARelease);
				break;

			case PS2_SCANCODE_end:
				sendKey(KeyboardSpecialKeys::End, nextIsARelease);
				break;

			case PS2_SCANCODE_delete:
				sendKey(KeyboardSpecialKeys::Delete, nextIsARelease);
				break;

			case PS2_SCANCODE_insert:
				sendKey(KeyboardSpecialKeys::Insert, nextIsARelease);
				break;

			case PS2_SCANCODE_keypadEnter:
				sendKey(KeyboardSpecialKeys::KeypadEnter, nextIsARelease);
				break;

			case PS2_SCANCODE_keypadDivide:
				sendKey(KeyboardSpecialKeys::KeypadDivide, nextIsARelease);
				break;
			}
			nextIsARelease = false;
			extended = false;
			return;
		}


		if (c == PS2_SCANCODE_backspace) {
			sendKey(KeyboardSpecialKeys::Backspace, nextIsARelease);

		} else if (c == PS2_SCANCODE_tab) {        //tab
			sendKey(KeyboardSpecialKeys::Tab, nextIsARelease);

		} else if (c == PS2_SCANCODE_capslock) {       //CAPS
			if (!nextIsARelease) {		//only toggle on press, not release
				capslk ^= 1;
				updateKeyboardLEDs();
			} 
			sendKey(KeyboardSpecialKeys::CapsLock, nextIsARelease);

		} else if (c == PS2_SCANCODE_numberlock) {
			if (!nextIsARelease) {		//only toggle on press, not release
				numberLock ^= 1;
				updateKeyboardLEDs();
			}
			sendKey(KeyboardSpecialKeys::NumLock, nextIsARelease);

		} else if (c == PS2_SCANCODE_scrolllock) {
			if (!nextIsARelease) {		//only toggle on press, not release
				scrollLock ^= 1;
				updateKeyboardLEDs();
			}
			sendKey(KeyboardSpecialKeys::ScrollLock, nextIsARelease);

		} else if (c == PS2_SCANCODE_f1) {
			sendKey(KeyboardSpecialKeys::F1, nextIsARelease);

		} else if (c == PS2_SCANCODE_f2) {
			sendKey(KeyboardSpecialKeys::F2, nextIsARelease);

		} else if (c == PS2_SCANCODE_f3) {
			sendKey(KeyboardSpecialKeys::F3, nextIsARelease);

		} else if (c == PS2_SCANCODE_f4) {
			sendKey(KeyboardSpecialKeys::F4, nextIsARelease);

		} else if (c == PS2_SCANCODE_f5) {
			sendKey(KeyboardSpecialKeys::F5, nextIsARelease);

		} else if (c == PS2_SCANCODE_f6) {
			sendKey(KeyboardSpecialKeys::F6, nextIsARelease);

		} else if (c == PS2_SCANCODE_f7 || c == 0x02) {						//for some reason, my test laptop gives '0x2' for F7
			sendKey(KeyboardSpecialKeys::F7, nextIsARelease);

		} else if (c == PS2_SCANCODE_f8) {
			sendKey(KeyboardSpecialKeys::F8, nextIsARelease);

		} else if (c == PS2_SCANCODE_f9) {
			sendKey(KeyboardSpecialKeys::F9, nextIsARelease);

		} else if (c == PS2_SCANCODE_f10) {
			sendKey(KeyboardSpecialKeys::F10, nextIsARelease);

		} else if (c == PS2_SCANCODE_f11) {
			sendKey(KeyboardSpecialKeys::F11, nextIsARelease);

		} else if (c == PS2_SCANCODE_f12) {
			sendKey(KeyboardSpecialKeys::F12, nextIsARelease);

		} else if (c == PS2_SCANCODE_newline) {
			sendKey(KeyboardSpecialKeys::Enter, nextIsARelease);

		} else if (c == PS2_SCANCODE_escape) {
			sendKey(KeyboardSpecialKeys::Escape, nextIsARelease);

		} else if (c == PS2_SCANCODE_keypad0) {
			sendKey(KeyboardSpecialKeys::Keypad0, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad1) {
			sendKey(KeyboardSpecialKeys::Keypad1, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad2) {
			sendKey(KeyboardSpecialKeys::Keypad2, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad3) {
			sendKey(KeyboardSpecialKeys::Keypad3, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad4) {
			sendKey(KeyboardSpecialKeys::Keypad4, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad5) {
			sendKey(KeyboardSpecialKeys::Keypad5, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad6) {
			sendKey(KeyboardSpecialKeys::Keypad6, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad7) {
			sendKey(KeyboardSpecialKeys::Keypad7, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad8) {
			sendKey(KeyboardSpecialKeys::Keypad8, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypad9) {
			sendKey(KeyboardSpecialKeys::Keypad9, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypadPeriod) {
			sendKey(KeyboardSpecialKeys::KeypadPeriod, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypadMinus) {
			sendKey(KeyboardSpecialKeys::KeypadMinus, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypadPlus) {
			sendKey(KeyboardSpecialKeys::KeypadPlus, nextIsARelease);
		} else if (c == PS2_SCANCODE_keypadMultiply) {
			sendKey(KeyboardSpecialKeys::KeypadMultiply, nextIsARelease);

		} else if (c == 0xF0) {		//if a release scancode slips through somehow, catch it here

		} else {
			sendKey(caps && capslk ? internalMapCapUpper[c] :
					caps && !capslk ? internalMapperUpper[c] :
					!caps && capslk ? internalMapCapLower[c] :
					internalMapperLower[c], nextIsARelease);
		}
	}

	nextIsARelease = false;
	extended = false;
}

char ps2keysetup[] = "PS/2 keyboard setup, scancode set 0x%X\n";
char configByted[] = "config byte = 0x%X\n";

int PS2Keyboard::open(int a, int, void* prnt)
{
	port = (PS2Port*) prnt;
	parent = (Device*) prnt;

	//set the translation
	extern uint32_t sysBootSettings;
	badTranslation = (sysBootSettings & 4) ? false : true;
	
	/*port->write(0xF0);
	port->read();
	port->write(0);
	port->read();
	uint8_t currentset = port->read();
	if (currentset == 0xFA) {
		currentset = port->read();
	}
	if (currentset == 1) {
		badTranslation = true;
	} else {
		uint8_t cfg = port->ctrl->readConfigByte();
		if (cfg & (1 << 6)) {
			badTranslation = true;
		}
	}*/

	/*disableIRQs();*/
	//port->write(PS2_DEV_CMD_DISABLE_SCANNING);

	/*port->write(0xF0);
	port->read();
	port->write(2);
	port->read();

	*/

	interrupt = addIRQHandler(1, ps2KeyboardHandler, true, (void*) this);
	
	/*kprintf(configByted, port->ctrl->readConfigByte());*/

	/*inb(0x60);
	inb(0x60);
	inb(0x60);
	inb(0x60);
	port->write(PS2_DEV_CMD_ENABLE_SCANNING);*/

	/*kprintf(ps2keysetup, currentset);
	enableIRQs();*/

	return 0;
}

int PS2Keyboard::close(int a, int b, void* c)
{
	return -1;
}
