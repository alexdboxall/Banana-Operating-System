#include "core/common.hpp"
#include "hal/keybrd.hpp"
#include "hal/device.hpp"
#include "core/terminal.hpp"
#include "libk/string.h"
#include "core/prcssthr.hpp"
#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

bool keystates[0x400];

bool keyboardSetupYet = false;

ThreadControlBlock* keyboardWaitingTaskList = nullptr;

void sendKeyToTerminal(uint8_t code)
{
	activeTerminal->receiveKey(code);

	if (code == (uint8_t) '\n') {
		ThreadControlBlock* next_task;
		ThreadControlBlock* this_task;

		lockStuff();

		next_task = keyboardWaitingTaskList;
		keyboardWaitingTaskList = nullptr;

		while (next_task != nullptr) {
			this_task = next_task;
			next_task = (ThreadControlBlock*) this_task->next;

			unblockTask(this_task);
		}

		unlockStuff();
	}
}

#include "hw/video/vga.hpp"
#include "hal/video.hpp"
#include "core/prcssthr.hpp"
#include "core/elf.hpp"

void sendKeyboardToken(KeyboardToken kt)
{
	keystates[kt.halScancode] = !kt.release;
	//userUsedKeyboardOrMouse();

	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Delete && keystates[(uint16_t) KeyboardSpecialKeys::Ctrl] && keystates[(uint16_t) KeyboardSpecialKeys::Alt]) {
		//sleepMode();
	}

	bool keypadNum = false;

	static bool globalScrolllock = 0;
	static int buffering = 0;

	if (kt.scrolllock != globalScrolllock) {
		globalScrolllock = kt.scrolllock;

		setTerminalScrollLock(globalScrolllock);
	}
	
	if (kt.numlock) {
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad0) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Insert;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad1) kt.halScancode = (uint16_t) KeyboardSpecialKeys::End;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad2) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Down;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad3) kt.halScancode = (uint16_t) KeyboardSpecialKeys::PageDown;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad4) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Left;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad5) kt.halScancode = (uint16_t) '5';
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad6) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Right;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad7) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Home;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad8) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Up;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad9) kt.halScancode = (uint16_t) KeyboardSpecialKeys::PageUp;
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadPeriod) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Delete;
	} else {
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad0) { kt.halScancode = (uint16_t) '0'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad1) { kt.halScancode = (uint16_t) '1'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad2) { kt.halScancode = (uint16_t) '2'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad3) { kt.halScancode = (uint16_t) '3'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad4) { kt.halScancode = (uint16_t) '4'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad5) { kt.halScancode = (uint16_t) '5'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad6) { kt.halScancode = (uint16_t) '6'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad7) { kt.halScancode = (uint16_t) '7'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad8) { kt.halScancode = (uint16_t) '8'; keypadNum = true; }
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Keypad9) { kt.halScancode = (uint16_t) '9'; keypadNum = true; }
	}

	if (globalScrolllock) {
		/*if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Up) scrollTerminalScrollLock(-1);
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Down) scrollTerminalScrollLock(1);
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::PageUp) scrollTerminalScrollLock(-24);
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::PageDown) scrollTerminalScrollLock(24);*/
	}

	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::F12) {
		extern Video* screen;
		VGAVideo* vga = new VGAVideo();
		addChild(vga);
		vga->open(0, 0, nullptr);
		screen = vga;
		executeDLL(loadDLL("C:/Banana/System/wsbe.sys"), this);
	}

	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadEnter) kt.halScancode = (uint16_t) KeyboardSpecialKeys::Enter;
	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadMinus) kt.halScancode = (uint16_t) '-';
	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadPlus) kt.halScancode = (uint16_t) '+';
	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadMultiply) kt.halScancode = (uint16_t) '*';
	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadDivide) kt.halScancode = (uint16_t) '/';
	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::KeypadPeriod) kt.halScancode = (uint16_t) '.';

	bool noMoreSend = false;
	if (!kt.release) {
		if (keystates[(uint16_t) KeyboardSpecialKeys::Alt]) {
			noMoreSend = true;
			if (keypadNum) {
				buffering *= 10;
				buffering += kt.halScancode - '0';
			} else {
				buffering = 0;
			}

		} else {
			if (buffering) {
				sendKeyToTerminal(buffering);
				noMoreSend = true;

			}
			buffering = 0;
		}

	} else {
		if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Alt) {
			if (buffering) {
				sendKeyToTerminal(buffering);
				noMoreSend = true;

			}
			buffering = 0;
		}
	}

	//add to buffer if it is a normal character on press (not release) (e.g. A-Z, a-z, 0-9, symbols, space, tab, newline, etc.)
	//OR if it is a printable character and the control key (doesn't *nix map things like Ctrl-C or Ctrl-Z to an ASCII character?)

	if (!noMoreSend && !kt.release && !keystates[(int) KeyboardSpecialKeys::Ctrl] && ((kt.halScancode >= 32 && kt.halScancode < 127) \
		|| kt.halScancode == (uint16_t) KeyboardSpecialKeys::Enter \
		|| kt.halScancode == (uint16_t) KeyboardSpecialKeys::Backspace)) {

		sendKeyToTerminal(kt.halScancode);
	}

	if (!noMoreSend && !kt.release && keystates[(int) KeyboardSpecialKeys::Ctrl] && (kt.halScancode >= 64 && kt.halScancode < 128)) {
		//also deals with lowercase instead of uppercase
		sendKeyToTerminal(kt.halScancode - '@' - (kt.halScancode >= 96 ? 32 : 0));
	}

	if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::F1 && !kt.release) {
		doTerminalCycle();
	}

	//also set event states, such as 'released L' or 'pressed W' for GUI apps
}

//should be called by read(), if it is stdin
//e.g.
//
// if (file == stdinFileDescForThisTask) {
//		return readKeyboard(currentTCB, currentTCB->terminal, buffer, count)
// }
//

void clearInternalKeybuffer(VgaText* terminal)
{
	memset(terminal->keybufferSent, 0, strlen(terminal->keybufferSent));
}

int readKeyboard(VgaText* terminal, char* buf, size_t count)
{
	asm("sti");
	int charsRead = 0;
	//bool blocked = false;
	while (count) {
		//block as much as we need to to get our first character
		/*while (terminal->keybufferSent[0] == 0) {
			if (!blocked) {
				currentTaskTCB->next = (ThreadControlBlock*) keyboardWaitingTaskList;
				keyboardWaitingTaskList = (ThreadControlBlock*) currentTaskTCB;
				blockTask(TaskState::WaitingForKeyboard);
			} else {
				return charsRead;
			}
		}	
		*/

		while (terminal->keybufferSent[0] == 0) {
			
		}

		//we shouldn't block twice on keyboard, we should just return if we don't get enough characters
		//blocked = true;

		//put in the buffer
		*buf++ = terminal->keybufferSent[0];

		char key = terminal->keybufferSent[0];

		//remove first char from that buffer
		memmove(terminal->keybufferSent, terminal->keybufferSent + 1, strlen(terminal->keybufferSent));

		--count;
		++charsRead;

		if (key == '\n') {
			return charsRead;
		}
	}

	return charsRead;
}

Keyboard::Keyboard(const char* name) : Device(name)
{
	deviceType = DeviceType::Keyboard;

	keyboardSetupYet = true;
}

Keyboard::~Keyboard()
{

}
