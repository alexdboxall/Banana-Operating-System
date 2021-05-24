#include "lgcyfont.hpp"
#include <fs/vfs.hpp>
#include <thr/prcssthr.hpp>
#include <core/common.hpp>

extern "C" {
#include <libk/string.h>
}

#define CHARS 255
#define FONTS 7

#define CELLH 14

uint8_t reverse(uint8_t b);

typedef uint8_t fontrow_t;

extern int System;            //the system font
extern int nextfont_;
extern fontrow_t Fonts[FONTS][CHARS][CELLH];
extern char FontNames[FONTS][255];
extern uint8_t FontWidths[FONTS][CHARS];

struct FONTDATA1
{
	char chr;
	uint8_t font[14];
	uint8_t size;
};

struct FONTDATA2
{
	char signature[16];
	struct FONTDATA1 FONTD[256];
};

extern struct FONTDATA2 FONT;

void loadFontWithName(char* name);
void loadfonts();
void loadbuiltinfonts();

uint8_t reverse(uint8_t b)
{
	return b;

	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

int System = 0;            //the system font
int nextfont_ = 0;
fontrow_t Fonts[FONTS][CHARS][CELLH];
char FontNames[FONTS][255];
uint8_t FontWidths[FONTS][CHARS];

struct FONTDATA2 FONT;

void loadFontWithName(char* name)
{
	kprintf("LOADING LEGACY FONT WITH NAME '%s'\n", name);

	int br;

	File* fil = new File(name, kernelProcess);
	FileStatus st = fil->open(FILE_OPEN_READ);
	if (st != FileStatus::Success) {
		panic("CANNOT LOAD FONTS");
	}
	fil->read(sizeof(FONT), (uint8_t*) &FONT, &br);
	fil->close();
	delete fil;

	for (int i = 32; i < 128; ++i) {
		char current = FONT.FONTD[i].chr;
		FontWidths[nextfont_][(int) current] = FONT.FONTD[i].size;
		for (int c = 0; c < CELLH; ++c) {
			Fonts[nextfont_][(int) current][c] = reverse(FONT.FONTD[i].font[(int) c]);
		}
	}
	uint16_t wh = 0;

	while (*name++);

	while (*name != '/' && *name != '\\') {
		--name;
	}
	++name;

	while (*name != '.') {
		char c = *name++;
		if (c >= 'a' && c <= 'z') {
			c -= 'a';
			c += 'A';
		}
		FontNames[nextfont_][wh++] = c;
	}

	FontNames[nextfont_][wh] = 0;
	kprintf("FontNames[%d] = %s\n", nextfont_, FontNames[nextfont_]);
	++nextfont_;
}

void loadbuiltinfonts()
{
	nextfont_ = 0;
	for (int inc = 0; inc < FONTS; ++inc) {
		for (int inc2 = 0; inc2 < CHARS; ++inc2) {
			Fonts[inc][inc2][0] = 0;
			for (int i = 1; i < 13; ++i) {
				Fonts[inc][inc2][i] = 0b01100110;
			}
			Fonts[inc][inc2][13] = 0;
			FontWidths[inc][inc2] = 8;
		}
	}

	char* name = (char*) "SYSTEM.";
	for (int i = 32; i < 128; ++i) {
		char current = FONT.FONTD[i].chr;
		FontWidths[nextfont_][(int) current] = FONT.FONTD[i].size;
		for (int c = 0; c < CELLH; ++c) {
			Fonts[nextfont_][(int) current][c] = reverse(FONT.FONTD[i].font[(int) c]);
		}
	}
	uint16_t wh = 0;

	strcpy(FontNames[nextfont_], "SYSTEM");
	kprintf("FontNames[%d] = %s\n", nextfont_, FontNames[nextfont_]);
	++nextfont_;
	nextfont_ = 0;
}

void loadfonts()
{
	Directory* dir = new Directory("C:/BANANA/FONTS/LEGACY", kernelProcess);
	dir->open();

	while (1) {
		dirent p;
		FileStatus st = dir->read(&p);

		kprintf("dir->read. st = %d\n", (int) st);
		
		if (st != FileStatus::Success || p.d_name == 0 || p.d_name[0] == 0) break;
		if (p.d_type & DT_DIR) {
		} else {
			char fname[256];
			strcpy(fname, "C:/BANANA/FONTS/LEGACY/");
			strcat(fname, p.d_name);
			kprintf("dp name = %s\n", p.d_name);
			loadFontWithName(fname);
		}
	}
	dir->close();
	delete dir;
}

LegacyFont getLegacyFont(const char* name)
{
	char path[256];
	strcpy(path, "C:/Banana/Fonts/Legacy/");
	strcat(path, name);
	strcat(path, ".FNT");

	for (int i = 0; i < nextfont_; ++i) {
		kprintf("%s vs. %s\n", FontNames[i], name);
		if (!strcmp(FontNames[i], name)) {
			kprintf("FOUND LEGACY FONT '%s' WITH ID %d.\n", name, i);
			return i;
		}
	}

	int onf = nextfont_;
	loadFontWithName((char*) name);
	if (onf == nextfont_) {
		kprintf("COULD NOT LOAD LEGACY FONT.\n");
		return -1;
	}
	kprintf("LOADED LEGACY FONT %s TO ID %d.\n", name, nextfont_ - 1);
	return nextfont_ - 1;
}

LegacyFont getLegacyFont(LegacyFontType type)
{
	switch (type) {
	case LegacyFontType::System:
		return getLegacyFont("SYSTEM");
	case LegacyFontType::Mono:
		return getLegacyFont("COURIER");
	case LegacyFontType::Mono2:
		return getLegacyFont("COURIERX");
	case LegacyFontType::Serif:
		return getLegacyFont("TIMESNR");
	case LegacyFontType::SansSerif:
		return getLegacyFont("ARIAL");
	case LegacyFontType::Comic:
		return getLegacyFont("COMICSAN");
	default:
		break;
	}
	return -1;
}

void legacyDraw(GDO* obj)
{
	int xx = obj->dataLegacyText.x;
	int bx = xx;
	int yy = obj->dataLegacyText.y;

	for (int i = 0; obj->dataLegacyText.text[i]; ++i) {
		if (!obj->dataLegacyText.text[i]) {
			xx = bx;
			yy += CELLH;
			continue;
		}
		int w = FontWidths[obj->dataLegacyText.font][obj->dataLegacyText.text[i]];
		obj->context->drawBitmap1(Fonts[obj->dataLegacyText.font][obj->dataLegacyText.text[i]], xx, yy, w, CELLH, obj->dataLegacyText.colour);
		xx += w;
	}
}

LegacyTextObject::LegacyTextObject(const char* string, int x, int y, uint32_t colour, Context* ctxt): GDO(GDOType::LegacyText, ctxt)
{
	dataLegacyText.x = x;
	dataLegacyText.y = y;
	dataLegacyText.colour = colour;
	dataLegacyText.font = System;
	dataLegacyText.text = (char*) malloc(strlen(string) + 1);
	strcpy(dataLegacyText.text, string);

	contextDrawFunc = legacyDraw;
}

LegacyTextObject::LegacyTextObject(LegacyFont fnt, const char* string, int x, int y, uint32_t colour, Context* ctxt): GDO(GDOType::LegacyText, ctxt)
{
	dataLegacyText.x = x;
	dataLegacyText.y = y;
	dataLegacyText.colour = colour;
	dataLegacyText.font = fnt;
	dataLegacyText.text = (char*) malloc(strlen(string) + 1);
	strcpy(dataLegacyText.text, string);

	contextDrawFunc = legacyDraw;
}

void legacyFontInit()
{
	nextfont_ = 0;
	loadbuiltinfonts();
	loadfonts();
	System = getLegacyFont(LegacyFontType::System);

}