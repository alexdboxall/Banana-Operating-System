#include "core/main.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/intctrl.hpp"
#include "core/prcssthr.hpp"
#include "hw/bus/ps2.hpp"
#include "hw/bus/ps2port.hpp"
#include "hw/keybrd/ps2key.hpp"

extern "C" {
#include "libk/string.h"
}

constexpr uint8_t PS2Keyboard::set1TranslationTable[1024];

constexpr uint8_t PS2Keyboard::internalMapperLower[256];
constexpr uint8_t PS2Keyboard::internalMapperUpper[256];
constexpr uint8_t PS2Keyboard::internalMapCapLower[256];
constexpr uint8_t PS2Keyboard::internalMapCapUpper[256];

/*
constexpr uint8_t PS2Keyboard::internalMapperLowerBad[256];
constexpr uint8_t PS2Keyboard::internalMapperUpperBad[256];
constexpr uint8_t PS2Keyboard::internalMapCapLowerBad[256];
constexpr uint8_t PS2Keyboard::internalMapCapUpperBad[256];*/

PS2Keyboard::PS2Keyboard(): Keyboard("PS/2 Keyboard")
{

}


PS2Keyboard::~PS2Keyboard()
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
	//build the packet
	KeyboardToken k;
	k.release = release;
	k.halScancode = halScancode;
	k.numlock = numberLock;
	k.scrolllock = scrollLock;
	k.capslock = capslk;

	//send it
	sendKeyboardToken(k);
}

void PS2Keyboard::sendKey(KeyboardSpecialKeys halScancode, bool release)
{
	//build the packet
	KeyboardToken k;
	k.release = release;
	k.halScancode = (uint16_t) halScancode;
	k.numlock = numberLock;
	k.scrolllock = scrollLock;
	k.capslock = capslk;

	//send it
	sendKeyboardToken(k);
}

void PS2Keyboard::updateKeyboardLEDs()
{
	uint8_t v = capslk << 2;
	v |= scrollLock << 1;
	v |= numberLock;

	port->deviceWrite(0xED);
	port->deviceRead();			//ACK
	port->deviceWrite(v);
	port->deviceRead();			//ACK
}

void ps2KeyboardHandler(regs* r, void* context)
{
	((PS2Keyboard*) context)->handler();
}

void PS2Keyboard::handler()
{
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

	if (badTranslation) {
		switch (c) {
		case PS2_STUPID_leftctrl:
			ctrl = nextIsARelease ^ 1;
			sendKey(KeyboardSpecialKeys::Ctrl, nextIsARelease);
			nextIsARelease = false;
			extended = false;
			return;

		case PS2_STUPID_leftshift:						//SHIFT
		case PS2_STUPID_rightshift:						//RIGHT SHIFT
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
			case PS2_STUPID_up:			//Up
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
			uint8_t x = 0;
			asm("int3; hlt");
			/*x = caps && capslk ? internalMapCapUpperBad[c] :
				caps && !capslk ? internalMapperUpperBad[c] :
				!caps && capslk ? internalMapCapLowerBad[c] :
				internalMapperLowerBad[c];*/
			asm("cmc");
			sendKey(x, nextIsARelease);
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

int PS2Keyboard::open(int, int, void* ctrl)
{
	//store parents
	port = (PS2Port*) parent;
	controller = (PS2*) ctrl;

	//install interrupt handler
	interrupt = addIRQHandler(1, ps2KeyboardHandler, true, (void*) this);

	//set the translation
	extern uint32_t sysBootSettings;
	badTranslation = (sysBootSettings & 4) ? false : true;

	return 0;
}

int PS2Keyboard::close(int a, int b, void* c)
{
	return -1;
}
