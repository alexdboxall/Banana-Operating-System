
#include "Font.hpp"
#include "LegacyFonts.hpp"
#include "SSFNFonts.hpp"

#include <krnl/panic.hpp>

extern "C" {
	#include <libk/string.h>
}

LinkedList2<Font*>* fontTable;

int SYSTEM_FONT_HANDLE = 0;

int lookupInFontTableByNameOnly(const char* name, int exclude)
{
	int handle = 0;
	auto iterator = fontTable->head_;
	while (iterator) {
		auto const& child = iterator->data;
		iterator = iterator->next;

		if (child) {
			if (!strcmp(child->name, name) && handle != exclude) {
				return handle;
			}
		} else {
			break;
		}

		++handle;
	}

	return -1;
}

int lookupInFontTable(FontStyle style)
{
	int handle = 0;
	auto iterator = fontTable->head_;
	while (iterator) {
		auto const& child = iterator->data;
		iterator = iterator->next;

		if (child) {
			if (child->size == style.size && !strcmp(child->name, style.name) && child->flags == style.flags) {
				return handle;
			}
		} else {
			break;
		}

		++handle;
	}

	return -1;
}

int getFontHandle(FontStyle style)
{
	if (fontTable == nullptr) {
		fontTable = new LinkedList2<Font*>;
	}

	int handle = lookupInFontTable(style);
	if (handle != -1) {
		return handle;
	}

	Font* newFont = new Font();
	strcpy(newFont->name, style.name);
	newFont->size = style.size;
	newFont->flags = style.flags;
	newFont->legacy = style.name[0] == '*';
	newFont->legacyFontID = 0;

	for (int i = 0; i < 128; ++i) {
		newFont->regionCache[i] = nullptr;
	}

	handle = fontTable->length();
	fontTable->appendNode(newFont);

	if (!newFont->legacyFontID) {
		loadSSFNFont(newFont, handle);
	}

	return handle;
}

Font* getFontFromHandle(int handleIn)
{
	int handle = 0;
	auto iterator = fontTable->head_;
	while (iterator) {
		auto const& child = iterator->data;
		iterator = iterator->next;

		if (handle == handleIn) {
			return child;
		}

		++handle;
	}

	return nullptr;
}

Region getFontRegion(int handle, int c, bool* needsToBeFreed, int* realW, int* realH)
{
	Font* font = getFontFromHandle(handle);
	Region* cached = font->regionCache[c];
	*needsToBeFreed = false;

	if (cached) {
		*realW = font->cachedW[c];
		*realH = font->cachedH[c];
		return *cached;
	}

	Region rgn;
	
	if (font->legacy) {
		rgn = getLegacyFontRegion(font, c, realW, realH);
	} else {
		rgn = getSSFNFontRegion(font, c, realW, realH);
	}

	if (c < 128) {
		font->regionCache[c] = new Region(0, 0, 0, 0);
		*font->regionCache[c] = rgn;
		font->cachedW[c] = *realW;
		font->cachedH[c] = *realH;
	} else {
		*needsToBeFreed = true;
	}
	return rgn;
}

void initFonts()
{
	loadLegacyFonts();
}

int loadFont(FontStyle style)
{
	return getFontHandle(style);
}