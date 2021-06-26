#include "context.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

#define SSFN_IMPLEMENTATION
#include "ssfn.h"

ssfn_t ssfn_ctx;

void NIContext::drvPutpixel4(int x, int y, uint32_t col)
{
	screen->putpixel(x, y, col);
}

void NIContext::drvDarken4(int x, int y, int amount)
{
	uint32_t og = screen->readPixelApprox(x, y);

	uint32_t r = (og >> 16) & 0xFF;
	uint32_t g = (og >>  8) & 0xFF;
	uint32_t b = (og >>  0) & 0xFF;

	r = (r * amount) >> 7;
	g = (g * amount) >> 7;
	b = (b * amount) >> 7;

	uint32_t s = (r << 16) | (g << 8) | b;
	
	screen->putpixel(x, y, s);
}

int NIContext::renderTTF(int x, int y, uint32_t col, char* str, int* chars)
{
	memset(glyphRenderBuffer, 0xFF, 64 * 64 * 4);

	if (!chars) {
		KePanic("NIContext::drvRenderTTF4");
	}
	
	int ww, hh, lleft, ttop;
	ssfn_bbox(&ssfn_ctx, str, &ww, &hh, &lleft, &ttop);
	
	ssfn_buf_t ssfn_buf;
	ssfn_buf.ptr = (uint8_t*) glyphRenderBuffer;
	ssfn_buf.w = 64;
	ssfn_buf.h = 64;
	ssfn_buf.p = 64 * 4;
	ssfn_buf.x = 0;
	ssfn_buf.y = ttop;
	ssfn_buf.fg = 0xFF000000ULL | col;

	*chars = ssfn_render(&ssfn_ctx, &ssfn_buf, str);

	int k = 0;
	for (int j = 0; j < hh; ++j) {
		for (int i = 0; i < ssfn_buf.x; ++i) {
			if (glyphRenderBuffer[k] != 0xFFFFFFFFU) {
				screen->putpixel(x + i, y + j, glyphRenderBuffer[k] & 0xFFFFFF);
			}
			++k;
		}
		k += 64 - ssfn_buf.x;
	}

	return ssfn_buf.x;
}

NIContext::~NIContext()
{
	ssfn_free(&ssfn_ctx);
}


#include <fs/vfs.hpp>
extern "C" {
#include <libk/string.h>
}

NIContext::NIContext(Video* vid, int w, int h, int p, int _bitsPerPixel)
{
	screen = vid;
	width = w;
	height = h;
	pitch = p;
	bitsPerPixel = _bitsPerPixel;

	memset(&ssfn_ctx, 0, sizeof(ssfn_ctx));
	glyphRenderBuffer = (uint32_t*) malloc(64 * 64 * 4);

	nextFont = 0;

	Directory* dir = new Directory("C:/Banana/Fonts/SFN", kernelProcess);
	
	if (!dir) {
	fail:
		KePanic("CANNOT LOAD FONT DIRECTORY");
	}

	FileStatus res = dir->open();
	if (res != FileStatus::Success) {
		goto fail;
	}

	while (1) {
		struct dirent de;
		int br;
		FileStatus status = dir->read(sizeof(struct dirent), (void*) &de, &br);
		if (status != FileStatus::Success || br != sizeof(struct dirent)) {
			break;
		}

		fontNames[nextFont] = (char*) malloc(strlen(de.d_name) + 1);
		strcpy(fontNames[nextFont++], de.d_name);

		char f[256];
		strcpy(f, "C:/Banana/Fonts/SFN/");
		strcat(f, de.d_name);

		File* fil = new File(f, kernelProcess);
		if (!fil) {
			continue;
		}

		status = fil->open(FileOpenMode::Read);
		if (status != FileStatus::Success) {
			delete fil;
			continue;
		}

		uint64_t siz;
		bool dir;
		fil->stat(&siz, &dir);

		if (dir) {
			fil->close();
			delete fil;
			continue;
		}

		uint8_t* ptr = (uint8_t*) malloc(siz);
		status = fil->read(siz, ptr, &br);
		kprintf("font is of size %d\n", siz);
		if (status != FileStatus::Success || br != siz) {
			fil->close();
			free(ptr);
			delete fil;
			continue;
		}

		kprintf("Loaded font: %s\n", f);

		int ssfn_res = ssfn_load(&ssfn_ctx, ptr);
		kprintf("SSFN_RES = %d\n", ssfn_res);

		fil->close();
		delete fil;

		break;
	}

	dir->close();
	delete dir;

	ssfn_select(&ssfn_ctx, SSFN_FAMILY_ANY, nullptr, SSFN_STYLE_REGULAR, 16);
}