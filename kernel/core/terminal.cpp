
/*

Something not working? Check:

	80s and 25s are around the right way
	You've added 0 (96) to calculations using 'displayData'
	You get uint16_t math correct (e.g. dividing by two, 80 vs. 160, 25 vs. 50)

*/

#include "core/common.hpp"
#include "core/terminal.hpp"
#include "core/kheap.hpp"
#include "hal/keybrd.hpp"
#include "hal/buzzer.hpp"
#include "hw/ports.hpp"
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
	terminalCycle = terminalCycle->next;
	setActiveTerminal(terminalCycle);
}

void addToTerminalCycle(VgaText* terminal)
{
	if (terminalCycle == nullptr) {
		terminal->next = terminal;
		terminalCycle = terminal;
		return;
	}

	VgaText* oldNext = terminalCycle->next;
	terminalCycle->next = terminal;
	terminal->next = oldNext;
}

void setActiveTerminal(VgaText* terminal)
{
	if (!terminal) {
		panic("NULL TERMINAL");
		return;
	}

	kprintf("setActiveTerminal 0x%X\n", terminal);

	if (activeTerminal) {
		activeTerminal->updateCursor();
	}

	activeTerminal = terminal; 
	kprintf("active terminal now = 0x%X\n", activeTerminal);

	//reload the cursor for this terminal
	terminal->setCursor(terminal->cursorX, terminal->cursorY);

	//reload blink
	terminal->disableBlink(terminal->isBlinkDisabled());

	//reload cursor height
	terminal->setCursorHeight(terminal->getCursorHeight());

	if (!terminal->scrollLock) {
		terminal->scrollPoint = 0;
	}

	terminal->load();
}

VgaTextImplementation textModeImplementation;

void installVgaTextImplementation()
{
	memset(&textModeImplementation, 0, sizeof(textModeImplementation));
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
	char title[80];
	for (int i = 0; i < 80; ++i) title[i] = ' ';

	for (int i = 0; name[i]; ++i) {
		title[i] = name[i];
	}

	if (implementation.loadInTitle) {
		implementation.loadInTitle(this, title);
	}

	updateDiskUsage();
}

void VgaText::load()
{
	char title[80];
	for (int i = 0; i < 80; ++i) title[i] = ' ';

	for (int i = 0; name[i]; ++i) {
		title[i] = name[i];
	}

	if (implementation.loadInTitle) {
		implementation.loadInTitle(this, title);
	}
	if (implementation.loadInData) {
		implementation.loadInData(this);
	}
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
			if (implementation.scrollScreen) {
				implementation.scrollScreen(this);
			}
		}
	}

	updateCursor();
}

void VgaText::writeCharacter(char c, enum VgaColour fg, enum VgaColour bg, int x, int y) {
	
	uint16_t word = combineCharAndColour(c, combineColours((uint8_t) fg, (uint8_t) bg));
    
    uint16_t pos = (y * VgaText::width + x);
    
    uint16_t* ptr = (uint16_t*) this->displayData;
    ptr += pos;
    *ptr = word;

	if (this == activeTerminal) {
		if (implementation.writeCharacter) {
			implementation.writeCharacter(this, c, fg, bg, x, y);
		}
	}	
}

void VgaText::puts(const char* c, enum VgaColour fg, enum VgaColour bg) {
	noUpdate = true;

	bool needsRepainting = false;

	uint8_t cols = combineColours((uint8_t) fg, (uint8_t) bg);
    
	uint16_t pos =  (cursorY * VgaText::width + cursorX);
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
			if (implementation.writeCharacter) {
				implementation.writeCharacter(this, c[i], fg, bg, cursorX, cursorY);
			}
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
	if (this == activeTerminal) {
		if (implementation.updateCursor) {
			implementation.updateCursor(this);
		}
	}
}

void VgaText::showCursor(bool show)
{
	if (this == activeTerminal) {
		if (implementation.showCursor) {
			//implementation.showCursor(this, show);
		}
	}

	cursorEnabled = show;
}

void VgaText::disableBlink(bool v)
{
	if (this == activeTerminal) {
		if (implementation.disableBlink) {
			implementation.disableBlink(this, v);
		}
	}

	blinkEnabled = !v;
}

// END HARDWARE SPECIFIC


void VgaText::putchar(char c, enum VgaColour fg, enum VgaColour bg)
{
	if (c == '\a') {
		systemBuzzer->beep(440, 500, false);
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

void VgaText::puts(const char* c) {
	for (int i = 0; c[i]; ++c) {
		putchar(c[i]);
	}
}

void VgaText::clearScreen() {
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

void VgaText::setDefaultBgColour (enum VgaColour bg) {
    defaultBg = bg;
	currentBg = bg;
}

void VgaText::setDefaultFgColour (enum VgaColour fg) {
    defaultFg = fg;
	currentFg = fg;
}

void VgaText::setDefaultColours (enum VgaColour fg, enum VgaColour bg) {
    setDefaultBgColour (bg);
    setDefaultFgColour (fg);
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
	strcpy(name, text);
	updateTitle();
}

uint8_t VgaText::combineColours(uint8_t fg, uint8_t bg) {
    return (fg & 0xF) | ((bg & 0xF) << 4);
}

uint16_t VgaText::combineCharAndColour (char c, uint8_t col) {
    return ((uint8_t) c) | (((uint16_t)col) << 8);
}

int VgaText::getCursorX() {
    return cursorX;
}

int VgaText::getCursorY() {
    return cursorY;
}

void VgaText::setCursor (int x, int y) {
    cursorX = x;
    cursorY = y;
    
    updateCursor();
}

void VgaText::setCursorX (int x) {
    setCursor(x, cursorY);
}

void VgaText::setCursorY (int y) {
    setCursor(cursorX, y);
}

void VgaText::incrementCursor (bool update) {
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

size_t VGA_TEXT_MODE_ADDRESS = 0xC20B8000;

void VgaText::updateRAMUsageDisplay(int percent)
{
	uint16_t* p = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	p += 75;

	*p++ = combineCharAndColour(percent / 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour(percent % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour('%', combineColours((uint8_t) 0, (uint8_t) 15));
}

void VgaText::putx(uint32_t num)
{
	char table[] = "0123456789ABCDEF";

	for (int i = 0; i < 8; ++i) {
		putchar(table[(num & 0xF0000000U) >> 28]);
		num <<= 4;
	}
}

void VgaText::updateDiskUsage() {
	uint16_t* p = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	p += 63;
	extern int ataSectorsRead;
	extern int ataSectorsWritten;

	*p++ = combineCharAndColour((ataSectorsRead / 10000) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsRead / 1000) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsRead / 100) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsRead / 10) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsRead / 1) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	p++;
	*p++ = combineCharAndColour((ataSectorsWritten / 10000) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsWritten / 1000) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsWritten / 100) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsWritten / 10) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
	*p++ = combineCharAndColour((ataSectorsWritten / 1) % 10 + '0', combineColours((uint8_t) 0, (uint8_t) 15));
}

void VgaText::decrementCursor (bool update) {
    if (cursorX != 0) {
        cursorX--;
    }
    
    if (update) updateCursor();
}

bool VgaText::isShowingCursor() {
    return cursorEnabled;
}

bool VgaText::isBlinkDisabled() {
    return !blinkEnabled;
}

void VgaText::setCursorHeight (int h) {
    cursorHeight = h;
    
    showCursor(cursorEnabled);      //refresh cursor
}

int VgaText::getCursorHeight() {
    return cursorHeight;
}

VgaText::~VgaText()
{
	
}


VgaText::VgaText (const char* n) {
	if (((*((uint16_t*) 0x410)) & 0x30) != 0x30) {
		VGA_TEXT_MODE_ADDRESS -= 0x8000;
	}

	implementation = textModeImplementation;

	strcpy(name, n);

	terminalDisplayHeight = bufferHeight;
	memset(displayData, 0, bufferHeight * width * 2);

    setDefaultColours(VgaColour::LightGrey, VgaColour::Black);
    setCursorHeight(2);
    setCursor(0, 0);
    showCursor(true);
    disableBlink(true);
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
	if (implementation.update) {
		implementation.update(this);
	}
}

FileStatus VgaText::write(uint64_t bytes, void* data, int *bw)
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