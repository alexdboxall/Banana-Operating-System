#include "context.hpp"


#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

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
	ssfn_buf.x = 0;
	ssfn_buf.y = 0;
	ssfn_buf.fg = 0xFF000000ULL | col;

	if (!chars) {
		KePanic("NIContext::drvRenderTTF4");
	}

	*chars = ssfn_render(&ssfn_ctx, &ssfn_buf, str);

	int k = 0;
	for (int j = 0; j < 144; ++j) {
		for (int i = 0; i < 144; ++i, ++k) {
			if (glyphRenderBuffer[k] >> 24 == 0xFF) {
				screen->putpixel(x + i, y + j, glyphRenderBuffer[k] & 0xFFFFFF);
			}
		}
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
	glyphRenderBuffer = (uint32_t*) malloc(144 * 144 * 4);
	ssfn_buf.ptr = (uint8_t*) glyphRenderBuffer;
	ssfn_buf.w = 144;
	ssfn_buf.h = 144;
	ssfn_buf.p = 144 * 4;

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
		if (status != FileStatus::Success || br != siz) {
			fil->close();
			free(ptr);
			delete fil;
			continue;
		}

		int ssfn_res = ssfn_load(&ssfn_ctx, ptr);

		fil->close();
		delete fil;

		kprintf("Loaded font: %s\n", f);
	}

	dir->close();
	delete dir;
}