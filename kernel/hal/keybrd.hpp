#ifndef _KEYBRD_HPP_
#define _KEYBRD_HPP_

#include <stdint.h>
#include <stddef.h>

#ifndef _USER_WSBE_WANT_KEYBRD_
#include "hal/device.hpp"
extern bool keystates[0x400];
enum class KeyboardSpecialKeys
#else
enum KeyboardSpecialKeys
#endif 
{
	Ctrl = 0x100,
	Alt = 0x101,
	Windows = 0x102,
	Function = 0x103,
	Shift = 0x104,

	RightCtrl = 0x110,
	RightAlt = 0x111,
	RightWindows = 0x112,
	RightFunction = 0x113,
	RightShift = 0x114,

	Backspace = (int) '\b',
	Enter = (int) '\n',
	Tab = (int) '\t',

	Home = 0x200,
	End = 0x201,
	Insert = 0x202,
	Delete = 0x203,
	PageUp = 0x204,
	PageDown = 0x205,
	PrintScr = 0x206,
	SysReq = 0x207,
	Pause = 0x208,
	Break = 0x209,
	Escape = 0x20A,
	Up = 0x20B,
	Down = 0x20C,
	Left = 0x20D,
	Right = 0x20E,

	CapsLock = 0x280,
	NumLock = 0x281,
	ScrollLock = 0x282,

	F1 = 0x300,
	F2 = 0x301,
	F3 = 0x302,
	F4 = 0x303,
	F5 = 0x304,
	F6 = 0x305,
	F7 = 0x306,
	F8 = 0x307,
	F9 = 0x308,
	F10 = 0x309,
	F11 = 0x30A,
	F12 = 0x30B,
	F13 = 0x30C,
	F14 = 0x30D,
	F15 = 0x30E,
	F16 = 0x30F,
	F17 = 0x310,
	F18 = 0x311,
	F19 = 0x312,
	F20 = 0x313,
	F21 = 0x314,
	F22 = 0x315,
	F23 = 0x316,
	F24 = 0x317,

	Keypad0,
	Keypad1,
	Keypad2,
	Keypad3,
	Keypad4,
	Keypad5,
	Keypad6,
	Keypad7,
	Keypad8,
	Keypad9,
	KeypadPeriod,
	KeypadPlus,
	KeypadMinus,
	KeypadEnter,
	KeypadMultiply,
	KeypadDivide,
};

struct KeyboardToken
{
	uint16_t halScancode;
	bool release;
	bool numlock;
	bool scrolllock;
	bool capslock;
};

#ifndef _USER_WSBE_WANT_KEYBRD_
void sendKeyboardToken(KeyboardToken kt);

class Keyboard : public Device
{
private:

protected:
	bool capsLock;
	bool numLock;
	bool scrollLock;

public:
	Keyboard(const char* name);
	virtual ~Keyboard();

	virtual void setRepeatRate(int t) = 0;
	virtual void setRepeatDelay(int t) = 0;
};

#include "core/terminal.hpp"

extern bool keyboardSetupYet;
int readKeyboard(VgaText* terminal, char* buf, size_t count);
void clearInternalKeybuffer(VgaText* terminal);
#endif

#endif