#include "arch/cc.h"

u16_t LWIP_PLATFORM_HTONS(u16_t x)
{
	return (x >> 8) | ((x & 0xFF) << 8);
}

u32_t LWIP_PLATFORM_HTONL(u32_t x)
{
	return (x >> 24) | ((x & 0xFF0000) >> 8) | ((x & 0xFF00) << 8) | ((x & 0xFF) << 24);
}