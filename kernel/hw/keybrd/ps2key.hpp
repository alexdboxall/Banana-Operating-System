#ifndef _PS2KEYBRD_HPP_
#define _PS2KEYBRD_HPP_

#include <stdint.h>
#include "hal/keybrd.hpp"

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

#define PS2_STUPID_keypadEnter 0x1C			
#define PS2_STUPID_keypadDivide 0x35
#define PS2_STUPID_home 0x47
#define PS2_STUPID_end 0x4F
#define PS2_STUPID_insert 0x52
#define PS2_STUPID_delete 0x53
#define PS2_STUPID_pageup 0x49
#define PS2_STUPID_pagedown 0x51


class PS2Keyboard: public Keyboard
{
private:

protected:
	PS2* controller;
	PS2Port* port;

public:
	bool extended = false;
	bool ignoreNext = false;
	bool nextIsARelease = false;
	bool caps = 0;
	bool ctrl = 0;
	bool capslk = 0;
	bool numberLock = 0;
	bool scrollLock = 0;
	bool alt = 0;
	bool altR = 0;

	bool badTranslation = false;

	//MUST KEEP THESE IN ORDER
	static constexpr uint8_t internalMapperLower[256]	 = "              `      q1   zsaw2  cxde43   vftr5  nbhgy6   mju78  ,kio09  ./l;p-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
	static constexpr uint8_t internalMapperUpper[256]	 = "              ~      Q!   ZSAW@  CXDE$#   VFTR%  NBHGY^   MJU&*  <KIO)(  >?L:P_   \" {+     } |           1 47   0.2568   +3-*9              ";
	static constexpr uint8_t internalMapCapLower[256]	 = "              `      Q1   ZSAW2  CXDE43   VFTR5  NBHGY6   MJU78  ,KIO09  ./L;P-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
	static constexpr uint8_t internalMapCapUpper[256]	 = "              ~      Q!   zsaw@  cxde$#   vftr%  nbhgy^   mju&*  <kio)(  >?l:p_   \" {+     } |           1 47   0.2568   +3-*9              ";
	
	static constexpr uint8_t internalMapperLowerBad[512] = \
"  1234567890-=  qwertyuiop[]  asdfghjkl;'` \\zxcvbnm,./ *               789-456+1230.                                           "
"  !@#$%^&*()_+  QWERTYUIOP{}  ASDFGHJKL:\"~ |ZXCVBNM<>? *               789-456+1230.                                           " \
"  1234567890-=  QWERTYUIOP[]  ASDFGHJKL;'` \\ZXCVBNM,./ *               789-456+1230.                                           " \
"  !@#$%^&*()_+  qwertyuiop{}  asdfghjkl:\"~ |zxcvbnm<>? *               789-456+1230.                                           ";

	/*static constexpr uint8_t internalMapperUpperBad[256] = "  !@#$%^&*()_+  QWERTYUIOP{}  ASDFGHJKL:\"~ |ZXCVBNM<>? *               789-456+1230.                                                        ";
	static constexpr uint8_t internalMapCapLowerBad[256] = "  1234567890-=  QWERTYUIOP[]  ASDFGHJKL;'` \\ZXCVBNM,./ *               789-456+1230.                                                        ";
	static constexpr uint8_t internalMapCapUpperBad[256] = "  !@#$%^&*()_+  qwertyuiop{}  asdfghjkl:\"~ |zxcvbnm<>? *               789-456+1230.                                                        ";*/

	PS2Keyboard();
	virtual ~PS2Keyboard();

	int open(int, int, void* ctrl);
	int close(int, int, void*);

	void setRepeatRate(int t);
	void setRepeatDelay(int t);

	void sendKey(uint16_t halScancode, bool release);
	void sendKey(KeyboardSpecialKeys halScancode, bool release);
	void updateKeyboardLEDs();
	void handler();
};


#endif