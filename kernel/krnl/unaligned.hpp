#include <stdint.h>

static inline __attribute__((always_inline)) uint16_t readUnaligned16(uint16_t* _ptr)
{
	uint8_t* p = (uint8_t*) _ptr;
	return ((uint16_t) p[0]) | ((uint16_t) p[1]);
}
