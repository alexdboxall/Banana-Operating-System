#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <stdint.h>
#include "hal/bus.hpp"

enum class DetectType
{
	Nothing,
	Mouse,
	Keyboard,
};

class Device;
class PS2;
class PS2Port;

#include "hal/keybrd.hpp"

class PS2Keyboard: public Keyboard
{
private:

protected:
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

	static constexpr uint8_t internalMapperLower[256] = "              `      q1   zsaw2  cxde43   vftr5  nbhgy6   mju78  ,kio09  ./l;p-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
	static constexpr uint8_t internalMapperUpper[256] = "              ~      Q!   ZSAW@  CXDE$#   VFTR%  NBHGY^   MJU&*  <KIO)(  >?L:P_   \" {+     } |           1 47   0.2568   +3-*9              ";
	static constexpr uint8_t internalMapCapLower[256] = "              `      Q1   ZSAW2  CXDE43   VFTR5  NBHGY6   MJU78  ,KIO09  ./L;P-   ' [=     ] \\           1 47   0.2568   +3-*9             -";
	static constexpr uint8_t internalMapCapUpper[256] = "              ~      Q!   zsaw@  cxde$#   vftr%  nbhgy^   mju&*  <kio)(  >?l:p_   \" {+     } |           1 47   0.2568   +3-*9              ";

	static constexpr uint8_t internalMapperLowerBad[256] = "  1234567890-=  qwertyuiop[]  asdfghjkl;'` \\zxcvbnm,./ *               789-456+1230.                                                         ";
	static constexpr uint8_t internalMapperUpperBad[256] = "  !@#$%^&*()_+  QWERTYUIOP{}  ASDFGHJKL:\"~ |ZXCVBNM<>? *               789-456+1230.                                                         ";
	static constexpr uint8_t internalMapCapLowerBad[256] = "  1234567890-=  QWERTYUIOP[]  ASDFGHJKL;'` \\ZXCVBNM,./ *               789-456+1230.                                                         ";
	static constexpr uint8_t internalMapCapUpperBad[256] = "  !@#$%^&*()_+  qwertyuiop{}  asdfghjkl:\"~ |zxcvbnm<>? *               789-456+1230.                                                         ";

	void sendKey(uint16_t halScancode, bool release);
	void sendKey(KeyboardSpecialKeys halScancode, bool release);

	PS2Port* port;

public:
	PS2Keyboard();

	void handler();

	void updateKeyboardLEDs();

	virtual int open(int, int, void*);
	virtual int close(int, int, void*);

	void setRepeatRate(int t);
	void setRepeatDelay(int t);
};

class PS2Port: public Bus
{
private:

protected:
	Device* dev = nullptr;

	DetectType previousType = DetectType::Nothing;

public:
	PS2* ctrl = nullptr;

	PS2Port();
	bool port2 = false;

	uint8_t read();
	void write(uint8_t cmd);

	int open(int port2, int, void* parent);		
	int close(int, int, void*);			
	void detect();
};

class PS2: public Bus
{
private:

protected:
	bool channel1 = false;
	bool channel2 = false;

	PS2Port* port1 = nullptr;
	PS2Port* port2 = nullptr;

public:
	PS2();

	void detect();

	int open(int, int, void*);
	int close(int, int, void*);

	void writeController(uint8_t command);
	void writeController(uint8_t command, uint8_t arg);
	uint8_t readController();

	void writeDevice(bool ch2, uint8_t command);

	uint8_t readConfigByte();
	void writeConfigByte(uint8_t data);

	bool translationOn();
};

#endif