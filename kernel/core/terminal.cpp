
/*

Something not working? Check:

	80s and 25s are around the right way
	You've added 0 (96) to calculations using 'displayData'
	You get uint16_t math correct (e.g. dividing by two, 80 vs. 160, 25 vs. 50)

*/

#include "core/common.hpp"
#include "core/terminal.hpp"
#include "core/kheap.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"
#include "hal/keybrd.hpp"
#include "hal/buzzer.hpp"
#include "krnl/hal.hpp"
#include "fs/vfs.hpp"
#include "libk/string.h"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

VgaColour ansiToVGAMappings[16] = {
	VgaColour::Black,
	VgaColour::Maroon,
	VgaColour::Green,
	VgaColour::Brown,
	VgaColour::Blue,
	VgaColour::Magenta,
	VgaColour::Teal,
	VgaColour::LightGrey,
	VgaColour::DarkGrey,
	VgaColour::Red,
	VgaColour::Lime,
	VgaColour::Yellow,
	VgaColour::Sky,
	VgaColour::Pink,
	VgaColour::Cyan,
	VgaColour::White,
};

bool VgaText::graphicMode = false;
bool VgaText::hiddenOut = true;

VgaText* activeTerminal;
VgaText* terminalCycle = nullptr;

void setTerminalScrollLock(bool state)
{

}

void doTerminalCycle()
{

}

void addToTerminalCycle(VgaText* terminal)
{
	
}

void setActiveTerminal(VgaText* terminal)
{
	if (!terminal) {
		panic("NULL TERMINAL");
		return;
	}

	if (activeTerminal) {
		activeTerminal->updateCursor();
	}

	activeTerminal = terminal;
	//reload the cursor for this terminal
	terminal->setCursor(terminal->cursorX, terminal->cursorY);
}


//START HARDWARE SPECIFIC

void scrollTerminalScrollLock(int amount)
{
	/*activeTerminal->scrollPoint += amount;
	if (activeTerminal->scrollPoint > 0) activeTerminal->scrollPoint = 0;
	if (activeTerminal->scrollPoint < -VgaText::bufferHeight) activeTerminal->scrollPoint = VgaText::bufferHeight;

	if (activeTerminal->implementation.loadInData) {
		//activeTerminal->implementation.loadInData(activeTerminal);
	}*/
}

void VgaText::updateTitle()
{
	
}

void VgaText::putx(uint32_t num)
{
	char table[] = "0123456789ABCDEF";

	for (int i = 0; i < 8; ++i) {
		putchar(table[(num & 0xF0000000U) >> 28]);
		num <<= 4;
	}
}

void VgaText::load()
{

}

void VgaText::scrollScreen()
{
	for (int y = 1; y < VgaText::bufferHeight; ++y) {
		for (int x = 0; x < 160; ++x) {
			displayData[y * 160 + x - 160] = displayData[y * 160 + x];
			if (y == VgaText::bufferHeight - 1) {
				if (x & 1) {
					this->displayData[y * 160 + x] = combineColours((uint8_t) currentFg, (uint8_t) currentBg);
				} else {
					this->displayData[y * 160 + x] = ' ';
				}
			}
		}
	}

	if (this == activeTerminal) {
		if (scrollLock) {
			scrollPoint--;
		} else {
			Hal::consoleScroll((uint8_t) currentFg, (uint8_t) currentBg);
		}
	}

	updateCursor();
}

void VgaText::writeCharacter(char c, enum VgaColour fg, enum VgaColour bg, int x, int y)
{
	uint16_t word = combineCharAndColour(c, combineColours((uint8_t) fg, (uint8_t) bg));

	uint16_t pos = (y * VgaText::width + x);

	uint16_t* ptr = (uint16_t*) this->displayData;
	ptr += pos;
	*ptr = word;

	if (this == activeTerminal) {
		Hal::consoleWriteCharacter(c, (int) fg, (int) bg, x, y);
	}
}

void VgaText::puts(const char* c, enum VgaColour fg, enum VgaColour bg)
{
	noUpdate = true;

	bool needsRepainting = false;

	uint8_t cols = combineColours((uint8_t) fg, (uint8_t) bg);

	uint16_t pos = (cursorY * VgaText::width + cursorX);
	uint16_t* ptr = (uint16_t*) this->displayData;
	ptr += pos;

	for (int i = 0; c[i]; ++i) {
		if (c[i] == '\r') {
			cursorX = 0;
			continue;
		}

		if (c[i] == '\n') {
			//doRepaint = true;
			needsRepainting = false;

			cursorX = 0;
			cursorY++;

			if (cursorY == terminalDisplayHeight) {
				cursorY--;
				scrollScreen();
			}

			updateCursor();

			pos = (cursorY * VgaText::width + cursorX);
			ptr = (uint16_t*) this->displayData;
			ptr += pos;
			continue;
		}

		if (c[i] == '\b') {
			decrementCursor();
			writeCharacter(' ', currentFg, currentBg, cursorX, cursorY);

			pos = (cursorY * VgaText::width + cursorX);
			ptr = (uint16_t*) this->displayData;
			ptr += pos;
			continue;
		}

		*ptr++ = combineCharAndColour(c[i], cols);
		if (this == activeTerminal) {
			Hal::consoleWriteCharacter(c[i], (int) fg, (int) bg, cursorX, cursorY);
		}
		needsRepainting = true;

		incrementCursor(false);
		//recalculate positions because a scroll might have happened
		if (cursorX == 0) {
			pos = (cursorY * VgaText::width + cursorX);
			ptr = (uint16_t*) this->displayData;
			ptr += pos;
		}
	}

	updateCursor();
	if (needsRepainting) {
		doUpdate();
	}
	noUpdate = false;
}

void VgaText::updateCursor()
{
	Hal::consoleCursorUpdate(cursorX, cursorY);
}

// END HARDWARE SPECIFIC


void VgaText::putchar(char c, enum VgaColour fg, enum VgaColour bg)
{
	if (c == '\a') {
		Krnl::beep(440, 500, false);
		return;
	}
	if (c == '\r') {
		cursorX = 0;
		updateCursor();
		return;
	}

	if (c == '\n') {
		cursorX = 0;
		cursorY++;

		if (cursorY == terminalDisplayHeight) {
			cursorY--;
			scrollScreen();
		}

		updateCursor();
		return;
	}

	if (c == '\b') {
		decrementCursor();
		writeCharacter(' ', currentFg, currentBg, cursorX, cursorY);
		return;
	}

	writeCharacter(c, fg, bg, cursorX, cursorY);
	incrementCursor();
}

void VgaText::doANSI_SGR(int code)
{
	if (code == 0) {			//RESET
		currentFg = defaultFg;
		currentBg = defaultBg;

	} else if (code == 7) {		//INVERT COLOURS
		VgaColour cfg = currentFg;
		currentFg = currentBg;
		currentBg = cfg;

	} else if (code == 27) {	//RESTORE COLOURS
		currentFg = defaultFg;
		currentBg = defaultBg;

	} else if (code >= 30 && code <= 37) {		//FG COLOUR
		currentFg = ansiToVGAMappings[code - 30];

	} else if (code >= 40 && code <= 47) {		//BG COLOUR
		currentBg = ansiToVGAMappings[code - 40];

	} else if (code >= 90 && code <= 97) {		//BRIGHT FG COLOUR
		currentFg = ansiToVGAMappings[code - 90 + 8];

	} else if (code >= 100 && code <= 107) {	//BRIGHT BG COLOUR
		currentBg = ansiToVGAMappings[code - 100 + 8];
	}
}

void VgaText::putchar(char c)
{
	if (c == '[' && asciiEscape) {
		csiEscape = true;
		asciiEscape = false;
		escapeCodePtr = 0;
		return;
	}
	if (c == 0x1B) {
		asciiEscape = true;
		return;
	}

	if (csiEscape && c >= 0x40 && c <= 0x7E) {
		if (c == 'm') {
			int code = 0;
			bool hasCode = false;
			for (int i = 0; i < escapeCodePtr; ++i) {
				if (escapeCode[i] == ';') {
					hasCode = false;
					doANSI_SGR(code);
					code = 0;

				} else {
					hasCode = true;
					code *= 10;
					code += escapeCode[i] - '0';
				}
			}

			if (hasCode) {
				doANSI_SGR(code);
			}
		} else if (c == 'J') {
			if (escapeCode[0] == '2') {
				clearScreen();
				setCursor(0, 0);
			}
		}

		csiEscape = false;
		asciiEscape = false;
		return;

	} else if (csiEscape) {
		if (escapeCodePtr < 15) {
			escapeCode[escapeCodePtr++] = c;
		}
		return;
	}

	putchar(c, currentFg, currentBg);
}

void VgaText::puts(const char* c)
{
	for (int i = 0; c[i]; ++c) {
		putchar(c[i]);
	}
}

void VgaText::clearScreen()
{
	setCursor(0, 0);

	noUpdate = true;

	for (int y = 0; y < terminalDisplayHeight; ++y) {
		for (int x = 0; x < VgaText::width; ++x) {
			writeCharacter(' ', currentFg, currentBg, x, y);
		}
	}

	doUpdate();

	noUpdate = false;
}

void VgaText::setDefaultBgColour(enum VgaColour bg)
{
	defaultBg = bg;
	currentBg = bg;
}

void VgaText::setDefaultFgColour(enum VgaColour fg)
{
	defaultFg = fg;
	currentFg = fg;
}

void VgaText::setDefaultColours(enum VgaColour fg, enum VgaColour bg)
{
	setDefaultBgColour(bg);
	setDefaultFgColour(fg);
}

void VgaText::setTitleTextColour(enum VgaColour fg)
{
	titleFg = fg;
	updateTitle();
}

void VgaText::setTitleColour(enum VgaColour bg)
{
	titleCol = bg;
	updateTitle();
}

void VgaText::setTitle(char* text)
{
	updateTitle();
}

uint8_t VgaText::combineColours(uint8_t fg, uint8_t bg)
{
	return (fg & 0xF) | ((bg & 0xF) << 4);
}

uint16_t VgaText::combineCharAndColour(char c, uint8_t col)
{
	return ((uint8_t) c) | (((uint16_t) col) << 8);
}

int VgaText::getCursorX()
{
	return cursorX;
}

int VgaText::getCursorY()
{
	return cursorY;
}

void VgaText::setCursor(int x, int y)
{
	cursorX = x;
	cursorY = y;

	updateCursor();
}

void VgaText::setCursorX(int x)
{
	setCursor(x, cursorY);
}

void VgaText::setCursorY(int y)
{
	setCursor(cursorX, y);
}

void VgaText::incrementCursor(bool update)
{
	++cursorX;
	if (cursorX == VgaText::width) {
		cursorX = 0;
		++cursorY;

		if (cursorY == terminalDisplayHeight) {
			cursorY--;
			scrollScreen();
		}
	}

	if (update) updateCursor();
}

void VgaText::decrementCursor(bool update)
{
	if (cursorX != 0) {
		cursorX--;
	}

	if (update) updateCursor();
}

VgaText::~VgaText()
{
	
}

VgaText::VgaText(const char* n)
{
	terminalDisplayHeight = bufferHeight;

	displayData = (uint8_t*) Virt::allocateKernelVirtualPages(1);
	Virt::getAKernelVAS()->mapPage(Phys::allocatePage(), (size_t) displayData, PAGE_PRESENT | PAGE_USER | PAGE_ALLOCATED | PAGE_SWAPPABLE);
	memset(displayData, 0, bufferHeight * width * 2);

	setDefaultColours(VgaColour::LightGrey, VgaColour::Black);
	setCursor(0, 0);
	clearScreen();
	scrollLock = false;

	memset(keybufferInternal, 0, TERMINAL_KEYBUFFER_IN_SIZE);
	memset(keybufferSent, 0, TERMINAL_KEYBUFFER_OUT_SIZE);
}

void VgaText::receiveKey(uint8_t key)
{
	//a null will ruin the keybuffer
	if (key == 0) {
		return;
	}

	if (key == (uint8_t) '\b') {

		//check that backspace can actually be used
		if (strlen(keybufferInternal)) {

			//terminal driver handles this one
			this->putchar('\b');

			//clear a character off the buffer
			keybufferInternal[strlen(keybufferInternal) - 1] = 0;
		}

	} else {
		//display the character
		this->putchar((char) key);

		//generate string from character
		char addon[2];
		addon[0] = (char) key;
		addon[1] = 0;

		//add to the buffer
		strcat(keybufferInternal, addon);
	}

	if (unbufferedKeyboard || key == (uint8_t) '\n') {
		if (strlen(keybufferSent) + strlen(keybufferInternal) + 4 > TERMINAL_KEYBUFFER_OUT_SIZE) {
			panic("TODO: HANDLE OVERFLOWS FOR KEYBUFFERS (terminal.cpp, VgaText::receiveKey)");
		}

		//copy it to the read buffer
		strcat(keybufferSent, keybufferInternal);

		//clear the internal buffer
		memset(keybufferInternal, 0, TERMINAL_KEYBUFFER_IN_SIZE);
	}

	doUpdate();
}

FileStatus VgaText::read(uint64_t bytes, void* data, int* br)
{
	*br = readKeyboard(this, (char*) data, bytes);
	return FileStatus::Success;
}

void VgaText::doUpdate()
{

}

FileStatus VgaText::write(uint64_t bytes, void* data, int* bw)
{
	//slD.lock();
	noUpdate = true;
	for (uint64_t i = 0; i < bytes; ++i) {
		this->putchar(((char*) data)[i]);
	}
	noUpdate = false;

	doUpdate();

	//slD.unlock();
	*bw = bytes;
	return FileStatus::Success;
}

bool VgaText::isAtty()
{
	return true;
}

VgaText* newTerminal(char* name)
{
	return new VgaText(name);
}