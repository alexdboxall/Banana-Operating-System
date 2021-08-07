#include <stdint.h>

uint16_t LWIP_PLATFORM_HTONS(uint16_t x)
{
	return (x >> 8) | ((x & 0xFF) << 8);
}

uint32_t LWIP_PLATFORM_HTONL(uint32_t x)
{
	return (x >> 24) | ((x & 0xFF0000) >> 8) | ((x & 0xFF00) << 8) | ((x & 0xFF) << 24);
}