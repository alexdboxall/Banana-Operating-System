#pragma once

#include <stdint.h>
#include "LinkedList.hpp"
#include "Region.hpp"

extern "C" {
#include <libk/string.h>
}

extern int SYSTEM_FONT_HANDLE;

struct Font
{
	char name[128];
	int size;
	int flags;

	bool legacy;
	int legacyFontID;

	int cachedW[128];
	int cachedH[128];

	void* ssfnData;

	Region* regionCache[128];
};

#define FONT_FLAG_REGULAR		0
#define FONT_FLAG_BOLD			1
#define FONT_FLAG_ITALIC		2
#define FONT_FLAG_UNDERLINE		4
#define FONT_FLAG_STRIKETHROUGH	8

struct FontStyle
{
	char name[128];
	int size;
	int flags;

	FontStyle(const char* name_, int size_, int flags_ = FONT_FLAG_REGULAR)
	{
		strcpy(name, name_);
		size = size_;
		flags = flags_;
	}
};

Font* getFontFromHandle(int handleIn);
int lookupInFontTableByNameOnly(const char* name, int exclude);
int getFontHandle(FontStyle style);
int loadFont(FontStyle style);
void initFonts();
Region getFontRegion(int handle, int c, bool* needsToBeFreed, int* realW, int* realH);
