#include "NLoadedBitmap.hpp"

#include <stdlib.h>
#include <stdio.h>

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


NLoadedBitmap::~NLoadedBitmap()
{
	if (data2) {
		free(data2);
	}
}

NLoadedBitmap::NLoadedBitmap(uint8_t* d, int length)
{
	data2 = nullptr;

	int tgaWidth;
	int tgaHeight;
	long tgaLen = length;
	uint8_t* tgaData = d;
	uint32_t* parsed = tgaParse(tgaData, tgaLen, &tgaWidth, &tgaHeight);

	data = parsed;
	data2 = parsed;
	width = tgaWidth;
	height = tgaHeight;
}

NLoadedBitmap::NLoadedBitmap(const char* file)
{
	data2 = nullptr;

	int tgaWidth;
	int tgaHeight;
	FILE* f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	long tgaLen = ftell(f);
	rewind(f);
	uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
	fread(tgaData, tgaLen, 1, f);
	uint32_t* parsed = tgaParse(tgaData, tgaLen, &tgaWidth, &tgaHeight);
	fclose(f);
	free(tgaData);

	data = parsed;
	data2 = parsed;
	width = tgaWidth;
	height = tgaHeight;
}