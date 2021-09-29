#include "NFont.hpp"

#define SSFN_IMPLEMENTATION
#define SSFN_CONSOLEBITMAP_TRUECOLOR
extern "C" {
#include "ssfn.h"
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


NFont::NFont()
{

}

int NFont::loadFont(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long length = ftell(f);
	rewind(f);

	uint8_t* data = (uint8_t*) malloc(length);
	fread(data, length, 1, f);
	fclose(f);

	return ssfn_load(&ctx, data);
}

int NFont::setFont(int size, int style)
{
	return ssfn_select(&ctx, SSFN_FAMILY_ANY, nullptr, style, size);
}

int NFont::getBBox(const char* str, int* w, int* h, int* base)
{
	int left;
	return ssfn_bbox(&ctx, str, w, h, &left, base);
}

int NFont::render(const char* text, int x, int y, NRegion* rgn)
{
	ssfn_buf_t dst;
	dst.w = rgn->getContext()->width;
	dst.h = rgn->getContext()->height;
	dst.bg = 0xFF0000FF;
	dst.fg = 0xFFFF0000;
	dst.p = rgn->getContext()->width * 4;
	dst.ptr = ((uint8_t*)rgn->getContext()->buffer);
	dst.x = x;
	dst.y = y;
	return ssfn_render(&ctx, &dst, text);
}