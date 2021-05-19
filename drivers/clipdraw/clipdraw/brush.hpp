#pragma once

#include <stdint.h>

enum class BrushType
{
	StockBlack,
	StockDarkGrey,
	StockGrey,
	StockLightGrey,
	StockWhite,
	StockNull,
	HatchForwardDiagonal,
	HatchBackwardDiagonal,
	HatchCross,
	HatchDiagonalCross,
	HatchHorizontal,
	HatchVertical,
	DitherHalf,
	DitherQuarter,
	DitherThreeQuarters,
	DitherDouble,
};

struct Brush
{
	uint32_t fg;
	uint32_t bg;

	int originX;
	int originY;
	
	uint8_t pattern[8];

	int width;
	int height;

	Brush(uint32_t fg = 0, uint32_t bg = 0xFFFFFFFF);
	Brush(BrushType type);
};