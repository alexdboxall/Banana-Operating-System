#pragma once

#include <stdint.h>
#include "LinkedList.hpp"
#include "Region.hpp"

extern int SYSTEM_FONT_HANDLE;

struct Font
{
	char name[64];
	int size;
	bool legacy;
	int legacyFontID;

	int cachedW[128];
	int cachedH[128];

	Region* regionCache[128];
};

int getFontHandle(char* name, int size);
void initFonts();
Region getFontRegion(int handle, int c, bool* needsToBeFreed, int* realW, int* realH);
