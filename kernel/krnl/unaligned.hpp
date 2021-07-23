#include <stdint.h>

static inline __attribute__((always_inline)) uint16_t readUnaligned16(uint16_t* _ptr)
{
	uint8_t* p = (uint8_t*) _ptr;
	return ((uint16_t) p[0]) | (((uint16_t) p[1]) << 8);
}

static inline __attribute__((always_inline)) uint32_t readUnaligned32(uint32_t* _ptr)
{
	uint8_t* p = (uint8_t*) _ptr;
	return ((uint32_t) p[0]) | (((uint32_t) p[1]) << 8) | (((uint32_t) p[2]) << 16) | (((uint32_t) p[3]) << 24);
}