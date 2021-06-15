#include <stdint.h>
#include <hal/diskctrl.hpp>
#include <hal/logidisk.hpp>
#include <core/terminal.hpp>

extern "C" int isoReadDiscSectorHelper(uint8_t* buffer, uint32_t sector, int count, char drvLetter)
{
	int success = disks[drvLetter - 'A']->read(sector, count, buffer);
	if (success) {
		return count * 2048;
	}
	return 0;
}

extern "C" void iso_kprintf(char* str)
{
	kprintf("%s\n", str);
	//activeTerminal->puts(str);
}

extern "C" void iso_kprintfd(int d)
{
	kprintf("0x%X\n", d);
	/*activeTerminal->puts("0x");
	activeTerminal->putx(d);
	activeTerminal->puts("\n");*/
}