#pragma once

#include <stdint.h>

struct Region
{
	uint32_t* data;
	int width;
	int height;
	int dataSize;
	int relX;
	int relY;
	bool dotted;
	Region()
	{
		width = -111111111;
		height = -222222222;
		data = nullptr;
		dataSize = -333333333;
		relX = -444444444;
		relY = -555555555;
		dotted = false;
	}

	Region(int x, int y, int w, int h)
	{
		width = w;
		height = h;
		data = nullptr;
		dataSize = 0;
		relX = x;
		relY = y;
		dotted = false;
	}
};

enum class RegionOperation
{
	Union,
	Intersection,
	Difference,
	XOR
};

Region createSlowRoundedRectangleRegion(int x, int y, int w, int h, int r);
Region createRectangleRegion(int x, int y, int w, int h);
Region createAntRegion(int x, int y, int w, int h, int r);
Region createBorderRegion(int x, int y, int w, int h, int r);
Region createPolygonRegion(int* x, int* y, int num);
Region createEllipseRegion(int x, int y, int w, int h);
Region createTightCursorRegion(int x, int y, uint32_t* cursor);
Region createTightFontRegion(int x, int y, uint8_t* font, int fontWidth, int fontHeight);

Region performRegionOperation(Region a, Region b, RegionOperation operation);
Region getRegionUnion(Region a, Region b);
Region getRegionDifference(Region a, Region b);
Region getRegionIntersection(Region a, Region b);
Region getRegionXOR(Region a, Region b);

bool isPointInRegion(Region r, int x, int y);
