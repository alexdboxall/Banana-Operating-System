#ifndef _WSBE_PEN_HPP
#define _WSBE_PEN_HPP

#include <stdint.h>

enum class PenStyle : uint32_t
{
	Solid,
	Dash,
	Dot,
	DashDot,
	DashDashDot,			
	Invisible,
};

uint32_t Pen(uint32_t rgb, PenStyle style, int width);

#endif