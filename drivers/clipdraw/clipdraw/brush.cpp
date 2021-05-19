#include "brush.hpp"

extern "C" {
#include "libk/string.h"
}

Brush::Brush(uint32_t fg_, uint32_t bg_)
{
	fg = fg_;
	bg = bg_;
	memset(pattern, 0xFF, sizeof(pattern));
	width = 1;
	height = 1;
}

Brush::Brush(BrushType type)
{
	fg = 0;
	bg = 0xFFFFFFFF;
	pattern[0] = 0xFF;
	width = 1;
	height = 1;
	originX = 0;
	originY = 0;

	switch (type) {
	case BrushType::StockBlack:
		break;
	case BrushType::StockDarkGrey:
		fg = 0xAAAAAA;
		break;
	case BrushType::StockGrey:
		fg = 0x808080;
		break;
	case BrushType::StockLightGrey:
		fg = 0x555555;
		break;
	case BrushType::StockWhite:
		fg = 0xFFFFFF;
		break;
	case BrushType::StockNull:
		pattern[0] = 0;
		break;
	case BrushType::HatchForwardDiagonal:
		pattern[0] = 0b0001;
		pattern[1] = 0b1000;
		pattern[2] = 0b0100;
		pattern[3] = 0b0010;
		width = 4;
		height = 4;
		break;
	case BrushType::HatchBackwardDiagonal:
		pattern[0] = 0b0001;
		pattern[1] = 0b0010;
		pattern[2] = 0b0100;
		pattern[3] = 0b1000;
		width = 4;
		height = 4;
		break;
	case BrushType::HatchCross:
		pattern[0] = 0b0001;
		pattern[1] = 0b0001;
		pattern[2] = 0b0001;
		pattern[3] = 0b1111;
		width = 4;
		height = 4;
		break;
	case BrushType::HatchDiagonalCross:
		pattern[0] = 0b001000;
		pattern[1] = 0b010100;
		pattern[2] = 0b100010;
		pattern[3] = 0b000001;
		pattern[4] = 0b100010;
		pattern[5] = 0b010100;
		width = 6;
		height = 6;
		break;
	case BrushType::HatchHorizontal:
		pattern[0] = 0b0;
		pattern[1] = 0b0;
		pattern[2] = 0b0;
		pattern[3] = 0b1;
		height = 4;
		break;
	case BrushType::HatchVertical:
		pattern[0] = 0b0010;
		width = 4;
		break;
	case BrushType::DitherHalf:
		pattern[0] = 0b10;
		pattern[1] = 0b01;
		width = 2;
		height = 2;
		break;
	case BrushType::DitherQuarter:
		pattern[0] = 0b10;
		pattern[1] = 0b00;
		width = 2;
		height = 2;
		break;
	case BrushType::DitherThreeQuarters:
		pattern[0] = 0b11;
		pattern[1] = 0b10;
		width = 2;
		height = 2; 
		break;
	case BrushType::DitherDouble:
		pattern[0] = 0b1100;
		pattern[1] = 0b1100;
		pattern[2] = 0b0011;
		pattern[3] = 0b0011;
		width = 4;
		height = 4;
		break;
		break;
	default:
		break;
	}
}