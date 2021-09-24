
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "gifdec.h"

#include "D:\Users\Alex\Desktop\Banana\kernel\sys\syscalls.hpp"
#include "D:\Users\Alex\Desktop\Banana\drivers\clipdraw\clipdraw\userlink.h"

extern uint64_t SystemCall(size_t, size_t, size_t, size_t);

typedef struct
{
	uint8_t magic1;
	uint8_t colormap;
	uint8_t encoding;
	uint16_t cmaporig;
	uint16_t cmaplen;
	uint8_t cmapent;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t bpp;
	uint8_t pixeltype;
} __attribute__((packed)) tga_header_t;

uint32_t* tgaParse(uint8_t* ptr, int size, int* widthOut, int* heightOut)
{
	int w = (ptr[13] << 8) + ptr[12];
	int h = (ptr[15] << 8) + ptr[14];

	uint32_t* data = (uint32_t*) malloc((w * h + 2) * sizeof(uint32_t));
	tga_header_t* header = (tga_header_t*) ptr;

	if (!data) {
		return NULL;
	}

	bool reverse = !(header->pixeltype & 0x20);

	int j, k;
	int o = header->y;
	int imageDataOffset = ((header->colormap ? (header->cmapent >> 3) * header->cmaplen : 0) + 18);

	if (w < 1 || h < 1) {
		return NULL;
	}

	switch (ptr[2]) {
	case 2:
	{
		if (header->cmaplen != 0 || header->colormap != 0 || (header->bpp != 24 && header->bpp != 32)) {
			free(data);
			return NULL;
		}
		j = imageDataOffset;
		int i = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				if (reverse && !(i % w)) {		//flip image vertically
					i = (h - (i / w) - 1) * w;
				}
				data[i++] = ((header->bpp == 32 ? ptr[j + 3] : 0) << 24) | (ptr[j + 2] << 16) | (ptr[j + 1] << 8) | ptr[j];

				j += header->bpp >> 3;
			}
		}
		break;
	}
	case 10:
	{
		if (header->cmaplen != 0 || header->colormap != 0 || (header->bpp != 24 && header->bpp != 32)) {
			free(data);
			return NULL;
		}
		int m = imageDataOffset;
		int i = 0;
		int y = 0;
		for (int x = 0; x < w * h && m < size;) {
			//packet header
			int k = ptr[m++];

			if (k >= 128) {
				//RLE packet
				int numRepeats = (k & 0x7F) + 1;
				uint32_t val = ((header->bpp == 32 ? ptr[m + 3] : 0) << 24) | (ptr[m + 2] << 16) | (ptr[m + 1] << 8) | ptr[m];
				for (int z = 0; z < numRepeats; ++z) {
					if (reverse && !(i % w)) {		//flip image vertically
						i = (h - y - 1) * w;
						++y;
					}
					data[i++] = val;
				}
				x += numRepeats;
				m += header->bpp >> 3;

			} else {
				//raw packet

				int numPixels = k + 1;
				for (int z = 0; z < numPixels; ++z) {
					if (reverse && !(i % w)) {		//flip image vertically
						i = (h - y - 1) * w;
						++y;
					}
					data[i++] = ((header->bpp == 32 ? ptr[m + 3] : 0xFF) << 24) | (ptr[m + 2] << 16) | (ptr[m + 1] << 8) | ptr[m];
					m += header->bpp >> 3;
				}
				x += numPixels;
			}
		}
		break;
	}

	default:
		free(data); 
		return NULL;
	}

	*widthOut = w;
	*heightOut = h;
	return data;
}

void putTGAFromData(int baseX, int baseY, uint8_t* tgaData, int tgaLen, uint32_t* framebuffer, int pitch)
{
	int tgaWidth;
	int tgaHeight;
	uint32_t* parsed = tgaParse(tgaData, tgaLen, &tgaWidth, &tgaHeight);

	if (!parsed) {
		return;
	}

	uint32_t* ogParsed = parsed;

	for (int y = baseY; y < baseY + tgaHeight; ++y) {
		for (int x = baseX; x < baseX + tgaWidth; ++x) {
			uint32_t px = *parsed++;
			if (px == 0x0) {

			} else if (px) {
				framebuffer[y * pitch + x] = px & 0xFFFFFF;
			}
		}
	}

	free(ogParsed);
}

void putTGAFromFile(int x, int y, const char* name, uint32_t* framebuffer, int pitch)
{
	FILE* f = fopen(name, "rb");
	fseek(f, 0, SEEK_END);
	long tgaLen = ftell(f);
	rewind(f);
	uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
	fread(tgaData, tgaLen, 1, f);
	putTGAFromData(x, y, tgaData, tgaLen, framebuffer, pitch);
	fclose(f);
	free(tgaData);
}

void repaint(NiLinkWindowStruct* win)
{
	win->buffer = (uint32_t*) realloc(win->buffer, win->w * win->h * 4);
	int spot = 0;
	for (int y = 0; y < win->h; ++y) {
		for (int x = 0; x < win->w; ++x) {
			win->buffer[spot + x] = (y < 25 || (y >= 78 && y < win->h - 10 && x >= 10 && x < win->w - 10)) ? 0xFFFFFF : 0xD4D4D4;
		}
		spot += win->w;
	}

	int x = 1;

	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/new.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/open.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/save.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/print.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/preview.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/copy.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/paste.tga", win->buffer, win->w);
	++x; 
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/undo.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/redo.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/table.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/columns.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 34, "C:/Banana/Icons/Office/paragraph.tga", win->buffer, win->w);
	++x;
	
	x = 1;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/smallfont.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/bigfont.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/bold.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/italic.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/underline.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/left.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/centre.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/right.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/justify.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/subscr.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/superscr.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/numpnt.tga", win->buffer, win->w);
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/dotpnt.tga", win->buffer, win->w);
	++x;
	putTGAFromFile((x++) * 25 - 15, 56, "C:/Banana/Icons/Office/colour.tga", win->buffer, win->w);
	++x;

	SystemCall(WSBE, LINKCMD_RESUPPLY_FRAMEBUFFER, 0, (size_t) win);
}

extern int appMain();
int main (int argc, char *argv[])
{
	appMain();
	return 0;

	NiLinkWindowStruct win;
	win.x = 200;
	win.y = 200;
	win.w = 600;
	win.h = 400;
	win.flags[0] = WIN_FLAGS_DEFAULT_0;
	win.flags[0] |= WIN_FLAGS_0_HIDE_ON_INVALIDATE | WIN_FLAGS_0_DRAW_OUTLINE_INSTEAD_OF_SHADOW | WIN_FLAGS_0_FORCE_RECTANGULAR;
	win.buffer = (uint32_t*) malloc(win.w * win.h * 4);
	strcpy(win.name, "This is a test!");
	memset(win.buffer, 0xFF, win.w * win.h * 4);
	SystemCall(WSBE, LINKCMD_CREATE_WINDOW, 0, (size_t) &win);
	win.flags[0] &= ~WIN_FLAGS_0_HIDDEN;
	SystemCall(WSBE, LINKCMD_UPDATE_FLAGS, 0, (size_t) &win);
	SystemCall(WSBE, LINKCMD_REDRAW, 0, (size_t) &win);

	repaint(&win);

	while (1) {
		int events = SystemCall(WSBE, LINKCMD_GET_EVENTS, 0, (size_t) &win);
		if (events < 0) continue;

		if (win.evnt.needsRedraw) {
			repaint(&win);
		}
	}

	return 0;
}