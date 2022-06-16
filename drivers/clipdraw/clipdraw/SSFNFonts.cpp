
#include "SSFNFonts.hpp"

#include <dbg/kconsole.hpp>
#include <fs/vfs.hpp>
#include <thr/prcssthr.hpp>

extern "C" {
#include "libk/string.h"

#pragma GCC optimize ("Os")
#define SSFN_IMPLEMENTATION
#include "ssfn.h"
}

#pragma GCC optimize ("Os")

bool loadSSFNFont(Font* font, int handle)
{
	int existingHandle = lookupInFontTableByNameOnly(font->name, handle);

	if (existingHandle == -1) {
		char filepath[256];
		strcpy(filepath, "C:/Banana/Fonts/SFN/");
		strcat(filepath, font->name);
		strcat(filepath, ".SFN");

		kprintf("Loading font '%s'\n", filepath);

		File* file = new File(filepath, kernelProcess);
		if (!file) {
			kprintf("cannot create file.\n");
			return false;
		}

		FileStatus res = file->open(FileOpenMode::Read);
		if (res != FileStatus::Success) {
			kprintf("cannot create read.\n");
			delete file;
			return file;
		}

		uint64_t siz;
		bool dir;
		file->stat(&siz, &dir);

		uint8_t* data = (uint8_t*) malloc(siz);
		int br;
		file->read(siz, data, &br);
		file->close();

		if (br != siz) {
			kprintf("but we only read %d bytes.\n", br);
			return false;
		}

		ssfn_t* ctxt = (ssfn_t*) malloc(sizeof(ssfn_t));
		memset(ctxt, 0, sizeof(ssfn_t));

		font->ssfnData = (void*) ctxt;

		ssfn_load(ctxt, data);
		
		free(data);

	} else {
		kprintf("existing handle = %d\n", existingHandle);
		Font* existingFont = getFontFromHandle(existingHandle);
		kprintf("existing font = 0x%X\n", existingFont);
		font->ssfnData = (void*) existingFont->ssfnData;
		kprintf("existingFont->ssfnData = 0x%X\n", existingFont->ssfnData);
	}

	return true;
}

Region getSSFNFontRegion(Font* font, int c, int* realW, int* realH)
{
	int ssfnFlags = 0;

	if (font->flags & FONT_FLAG_BOLD) {
		ssfnFlags |= FONT_FLAG_BOLD;
	}

	if (font->flags & FONT_FLAG_ITALIC) {
		ssfnFlags |= SSFN_STYLE_ITALIC;
	}

	if (font->flags & FONT_FLAG_UNDERLINE) {
		ssfnFlags |= SSFN_STYLE_UNDERLINE;
	}

	if (font->flags & FONT_FLAG_STRIKETHROUGH) {
		ssfnFlags |= SSFN_STYLE_STHROUGH;
	}

	char str[2];
	str[0] = c;
	str[1] = 0;


	//HalDisableInterrupts();

	// we cache the regions anyway (which is a better cache anyway because it saves recomputing the region)
	// so we disable SSFN's font cache to save memory
	ssfn_select((ssfn_t*) font->ssfnData, SSFN_FAMILY_ANY, NULL, ssfnFlags | SSFN_STYLE_NOAA | SSFN_STYLE_NOCACHE, font->size);

	int left, top;
	ssfn_bbox((ssfn_t*) font->ssfnData, str, realW, realH, &left, &top);

	uint32_t* scrBuffer = (uint32_t*) malloc(*realW * *realH * 4);
	memset(scrBuffer, 0, *realW * *realH * 4);

	ssfn_buf_t bf;
	bf.x = 0;
	bf.y = top;
	bf.w = *realW;
	bf.p = *realW * 4;
	bf.h = *realH;
	bf.bg = 0;
	bf.fg = 0xFF202020;
	bf.ptr = (uint8_t*) scrBuffer;

	ssfn_render((ssfn_t*) font->ssfnData, &bf, str);

	//HalEnableInterrupts();

	uint8_t* decompressed = (uint8_t*) malloc(*realW * *realH);
	int j = 0;
	for (int y = 0; y < bf.h; ++y) {
		for (int x = 0; x < bf.w; ++x) {
			decompressed[y * *realW + x] = scrBuffer[y * *realW + x] ? 1 : 0;
		}
	}

	Region rgn = createTightFontRegion(0, 0, decompressed, *realW, *realH);
	free(decompressed);
	free(scrBuffer);
	return rgn;
}