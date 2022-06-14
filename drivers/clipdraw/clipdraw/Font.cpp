
#include "Font.hpp"
#include "LegacyFonts.hpp"

#include <krnl/panic.hpp>

extern "C" {
	#include <libk/string.h>
}

LinkedList2<Font*>* fontTable;

int SYSTEM_FONT_HANDLE = 0;

int lookupInFontTable(char* name, int size)
{
	int handle = 0;
	auto iterator = fontTable->head_;
	while (iterator) {
		auto const& child = iterator->data;
		iterator = iterator->next;

		if (child) {
			if (child->size == size && !strcmp(child->name, name)) {
				return handle;
			}
		} else {
			break;
		}

		++handle;
	}

	return -1;
}

int getFontHandle(char* name, int size)
{
	if (fontTable == nullptr) {
		fontTable = new LinkedList2<Font*>;
	}

	int handle = lookupInFontTable(name, size);
	if (handle != -1) {
		return handle;
	}

	Font* newFont = new Font();
	strcpy(newFont->name, name);
	newFont->size = size;
	newFont->legacy = name[0] = '*';
	newFont->legacyFontID = 0;

	for (int i = 0; i < 128; ++i) {
		newFont->regionCache[i] = nullptr;
	}

	handle = fontTable->length();
	fontTable->appendNode(newFont);

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
		rgn = getLegacyFontRegion(font->legacyFontID, c, realW, realH);
	} else {
		KePanic("NON-LEGACY FONTS NOT IMPLEMENTED YET");
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