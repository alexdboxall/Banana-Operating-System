#include <stdint.h>
#include <hal/diskctrl.hpp>
#include <hal/logidisk.hpp>

int isoReadDiscSectorHelper(uint8_t* buffer, uint32_t sector, int count, char drvLetter)
{
	int success = disks[drvLetter - 'A']->read(sector, count, buffer);
	if (success) {
		return count * 2048;
	}
	return 0;
}