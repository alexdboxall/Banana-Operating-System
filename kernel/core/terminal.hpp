
#ifndef _VGA_TEXT_HPP_
#define _VGA_TEXT_HPP_

#include <stdint.h>
#include "core/unixfile.hpp"

constexpr int TERMINAL_KEYBUFFER_IN_SIZE = 150;
constexpr int TERMINAL_KEYBUFFER_OUT_SIZE = 300;

enum class VgaColour
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Teal = 3,
	Maroon = 4,
	Magenta = 5,
	Brown = 6,
	LightGrey = 7,
	DarkGrey = 8,
	Sky = 9,
	Lime = 10,
	Cyan = 11,
	Red = 12,
	Pink = 13,
	Yellow = 14,
	White = 15,

};

class VgaText;
struct VgaTextImplementation
{
	void (*loadInTitle)(VgaText* terminal, char* title);
	void (*loadInData)(VgaText* terminal);
	void (*update)(VgaText* terminal);
	void (*scrollScreen)(VgaText* terminal);
	void (*updateCursor)(VgaText* terminal);
	void (*showCursor)(VgaText* terminal, bool show);
	void (*disableBlink)(VgaText* terminal, bool disabled);
	void (*writeCharacter)(VgaText* terminal, char c, enum VgaColour fg, enum VgaColour bg, int x, int y);
};

class VgaText : public UnixFile {
private:
    
protected:

public:	
	uint8_t displayData[4000];

	int terminalDisplayHeight;

	int cursorX;
	int cursorY;
	int cursorHeight;
	bool cursorEnabled;
	bool blinkEnabled;

	VgaText* next;		//used to cycle through the terminals

	enum VgaColour defaultBg;
	enum VgaColour defaultFg;
	enum VgaColour currentBg;
	enum VgaColour currentFg;
	enum VgaColour titleCol = VgaColour::Blue;
	enum VgaColour titleFg = VgaColour::White;

	static bool mono = false;

	bool asciiEscape = false;
	bool csiEscape = false;
	char escapeCode[16];
	int escapeCodePtr = 0;

	void doANSI_SGR(int code);

	static uint8_t combineColours(uint8_t fg, uint8_t bg);
	static uint16_t combineCharAndColour(char c, uint8_t col);

	friend void setActiveTerminal(VgaText* terminal);
	friend void doTerminalCycle();
	friend void addToTerminalCycle(VgaText* terminal);
	friend void scrollTerminalScrollLock(int amount);
	friend void setTerminalScrollLock(bool state);

	bool scrollLock;
	int scrollPoint = 0;

	static bool graphicMode;

	VgaTextImplementation implementation;

	static bool hiddenOut;

	bool unbufferedKeyboard = false;

	bool noUpdate = false;
	void doUpdate();

	//called by syscalls
	virtual FileStatus read(uint64_t bytes, void* data, int* b);
	virtual FileStatus write(uint64_t bytes, void* data, int* b);

	void load();
	
	virtual bool isAtty();

    static const int width = 80;
    static const int height = 24;
	static const int bufferHeight = 24;

	char name[128];
    
	char keybufferInternal[TERMINAL_KEYBUFFER_IN_SIZE];			//for holding what's currently been written, gets copied to the other one when a newline is encountered, handles backspace, etc.
	char keybufferSent[TERMINAL_KEYBUFFER_OUT_SIZE];			//applications read from this one

	VgaText(const char* name);
	~VgaText();
    
	void updateTitle();
	void updateCursor();

	void setTitle(char* text);

    void setDefaultBgColour (enum VgaColour bg);
    void setTitleColour (enum VgaColour bg);
    void setTitleTextColour (enum VgaColour bg);
    void setDefaultFgColour (enum VgaColour fg);
    void setDefaultColours (enum VgaColour fg, enum VgaColour bg);

    void writeCharacter(char c, enum VgaColour fg, enum VgaColour bg, int x, int y);
    void putchar(char c, enum VgaColour fg, enum VgaColour bg);
    void putchar(char c);
    void puts(const char* c, enum VgaColour fg, enum VgaColour bg);
    void puts(const char* c);
	void putx(uint32_t num);
    void clearScreen();
    
    int getCursorX();
    int getCursorY();
    void setCursorX (int x);
    void setCursorY (int y);
    void setCursor (int x, int y);
    void incrementCursor (bool update = true);
    void decrementCursor (bool update = true);
    
    void showCursor (bool w = true);
    void disableBlink (bool v = true);
    bool isShowingCursor();
    bool isBlinkDisabled();
    
    void setCursorHeight (int h);
    int getCursorHeight();

	static void updateDiskUsage();
	static void updateRAMUsageDisplay(int percent);

    void scrollScreen();
	void receiveKey(uint8_t key);
};


extern VgaTextImplementation textModeImplementation;

extern VgaText* activeTerminal;

void setActiveTerminal(VgaText* terminal);
void doTerminalCycle();
void addToTerminalCycle(VgaText* terminal);
void setTerminalScrollLock(bool state);
void scrollTerminalScrollLock(int amount);

#endif
