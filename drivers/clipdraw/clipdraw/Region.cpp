#include "Region.hpp"
#include "Mouse.hpp"

#include <stdint.h>
#include "krnl/main.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "krnl/kheap.hpp"
#include <hal/video.hpp>
extern "C" {
#include "libk/string.h"
}

#pragma GCC optimize ("O0")

extern "C" void* __not_memcpy(void* destination, const void* source, size_t n);

double sqrt(double s)
{
	return s / 3;
}

#define _min_(a, b) ((a < b ? a : b))
#define _max_(a, b) ((a > b ? a : b))

uint32_t readUnaligned32(uint8_t* ptr)
{
	return *((uint32_t*) ptr);
}

void writeUnaligned32(uint8_t* ptr, uint32_t data)
{
	*((uint32_t*) ptr) = data;
}

Region createTightCursorRegion(int x, int y, uint32_t* data)
{
	Region rgn(x, y, MOUSE_WIDTH, MOUSE_HEIGHT);
	rgn.dataSize = 4 * (MOUSE_HEIGHT * 17 + 1);
	rgn.data = (uint32_t*) malloc(rgn.dataSize);

	uint32_t* data32 = (uint32_t*) rgn.data;

	for (int y = 0; y < 32; y++) {
		uint32_t wte = *(((uint32_t*) data) + y + 0);
		uint32_t blk = *(((uint32_t*) data) + y + 32);

		int invs[16];
		int invCount = 0;

		bool in = false;

		for (int x = 0; x < 32; x++) {
			bool newIn = (blk & 1) || (wte & 1);
			if (in != newIn) {
				invs[invCount++] = x;
				in = newIn;
			}
			blk >>= 1;
			wte >>= 1;
		}
		if (in) {
			invs[invCount++] = 32;
		}

		*data32++ = invCount | (1 << 16);
		for (int i = 0; i < invCount; ++i) {
			*data32++ = invs[i];
		}

		blk >>= 1;
		wte >>= 1;
	}

	*data32++ = 0xFFFFFFFF;
	rgn.dataSize = ((size_t) data32) - ((size_t) rgn.data);
	return rgn;
}

Region createEllipseRegion(int x, int y, int w, int h)
{
	Region rgn(x, y, w, h);
	rgn.dataSize = h * 12 + 4;
	rgn.data = (uint32_t*) malloc(rgn.dataSize);

	if (rgn.data == nullptr) {
		KePanic("abort");
	}

	uint32_t* data32 = (uint32_t*) rgn.data;

	for (int i = 0; i < h; ++i) {
		double ey = 1.0 - (2.0 * (double) i / (double) (h - 1));
		double ex = sqrt(1.0 - ey * ey) * w;

		int startX = (int) ((w - ex) / 2);
		int endX = (int) (startX + ex);

		*data32++ = 0x00010002;
		*data32++ = startX;
		*data32++ = endX;
	}

	*data32++ = 0xFFFFFFFFU;

	return rgn;
}

Region createPolygonRegion(int* x, int* y, int num)
{
	int minX = x[0];
	int minY = y[0];
	int maxX = x[0];
	int maxY = y[0];

	for (int i = 0; i < num; ++i) {
		if (x[i] < minX) minX = x[i];
		if (y[i] < minY) minY = y[i];
		if (x[i] > maxX) maxX = x[i];
		if (y[i] > maxY) maxY = y[i];
	}

	int w = maxX - minX;
	int h = maxY - minY;

	Region rgn(minX, minY, w, h);

	//assert(false);

	// TODO: create lots of edge tables and sort them bottom up and other weirdness

	// TODO: work out how the hell to get the size of this thing...

	return rgn;
}

Region createSlowRoundedRectangleRegion(int x, int y, int w, int h, int r)
{
	Region rect = createRectangleRegion(x, y, w, h);
	Region cornerSubtract = createRectangleRegion(x, y, r, r);
	Region cornerAdd = createEllipseRegion(x, y, r * 2, r * 2);

	Region withoutTopLeft = getRegionDifference(rect, cornerSubtract);
	cornerSubtract.relX += w - r;

	Region withoutTop = getRegionDifference(withoutTopLeft, cornerSubtract);
	cornerSubtract.relY += h - r;

	Region withoutTopAndBottomRight = getRegionDifference(withoutTop, cornerSubtract);
	cornerSubtract.relX -= w - r;

	Region withoutCorners = getRegionDifference(withoutTopAndBottomRight, cornerSubtract);

	Region circleInTL = getRegionUnion(withoutCorners, cornerAdd);
	cornerAdd.relX += w - 2 * r;

	Region circleInTLTR = getRegionUnion(circleInTL, cornerAdd);	
	cornerAdd.relY += h - 2 * r;

	Region circleInTLTRBR = getRegionUnion(circleInTLTR, cornerAdd);
	cornerAdd.relX -= w - 2 * r;

	Region result = getRegionUnion(circleInTLTRBR, cornerAdd);

	free(rect.data);
	free(cornerSubtract.data);
	free(cornerAdd.data);
	free(withoutTopLeft.data);
	free(withoutTop.data);
	free(withoutTopAndBottomRight.data);
	free(withoutCorners.data);
	free(circleInTL.data);
	free(circleInTLTR.data);
	free(circleInTLTRBR.data);

	return result;
}

Region createRectangleRegion(int x, int y, int w, int h)
{
	//assert(h > 0);
	//assert(h <= 0x1FFFFF);

	Region rgn(x, y, w, h);

	rgn.dataSize = 16;
	rgn.data = (uint32_t*) malloc(rgn.dataSize);

	rgn.data[0] = 0x2 | (h << 16);
	rgn.data[1] = 0;
	rgn.data[2] = w;
	rgn.data[3] = 0xFFFFFFFFU;

	return rgn;
}

Region createBorderRegion(int x, int y, int w, int h, int r)
{
	Region rgn(x, y, w, h);

	rgn.dataSize = 4 * 12;
	rgn.data = (uint32_t*) malloc(rgn.dataSize);
	//assert(rgn.data != nullptr);

	uint32_t* data32 = rgn.data;
	*data32++ = 2 | (r << 16);
	*data32++ = 0;
	*data32++ = w;

	*data32++ = 4 | ((h - 2 * r) << 16);
	*data32++ = 0;
	*data32++ = r;
	*data32++ = w - r;
	*data32++ = w;

	*data32++ = 2 | (r << 16);
	*data32++ = 0;
	*data32++ = w;

	*data32++ = 0xFFFFFFFF;

	return rgn;
}

Region createAntRegion(int x, int y, int w, int h, int r)
{
	Region rgn = createBorderRegion(x, y, w, h, r);
	rgn.dotted = true;
	return rgn;
}

int compressScanlineAndAddToRegion(Region* rgn, int bytesUsed, uint32_t* inversionPoints, uint32_t numInversionPoints, uint32_t count)
{
	//assert(bytesUsed >= 0);
	//assert(numInversionPoints >= 0);
	//assert(count >= 0);

	rgn->data[bytesUsed / 4] = numInversionPoints | (count << 16);
	memcpy(rgn->data + (bytesUsed / 4) + 1, inversionPoints, numInversionPoints * 4);
	bytesUsed += 4 + numInversionPoints * 4;

	return bytesUsed;
}

Region performRegionOperation(Region a, Region b, RegionOperation op)
{
	int x = _min_(a.relX, b.relX);
	int y = _min_(a.relY, b.relY);
	int w = _max_(a.relX + a.width, b.relX + b.width) - x;
	int h = _max_(a.relY + a.height, b.relY + b.height) - y;

	////assert(x >= 0);
	////assert(y >= 0);
	//assert(w >= 0);
	//assert(h > 0);
	
	//assert(a.height > 0);
	//assert(b.height > 0);

	int ayOffset = a.relY < b.relY ? 0 : a.relY - b.relY;
	int byOffset = b.relY < a.relY ? 0 : b.relY - a.relY;

	int axOffset = a.relX < b.relX ? 0 : a.relX - b.relX;
	int bxOffset = b.relX < a.relX ? 0 : b.relX - a.relX;

	Region rgn(x, y, w, h);
	rgn.dataSize = (a.dataSize + b.dataSize) * 4;			// we will resize DOWN later, but we never resize up
	rgn.data = (uint32_t*) calloc(rgn.dataSize, 1);

	//assert(rgn.data != nullptr);

	int bytesUsed = 0;

	uint32_t* ptr[2] = { a.data, b.data };
	uint32_t* maxPtr[2] = { a.data + a.dataSize, b.data + b.dataSize };			// only used for //assertions

	const int MAX_INV_POINTS = 512;

	uint32_t inversionPoints[2][MAX_INV_POINTS];
	int numInversionPoints[2];
	int inversionLifetime[2] = {0, 0};
	uint32_t outputInversionPoints[MAX_INV_POINTS];
	uint32_t lastTimeInversionPoints[MAX_INV_POINTS];
	lastTimeInversionPoints[0] = -1;				//to ensure the first time isn't 'the same as last time'

	int inARow = 0;
	int lastTimeNumOutputInversionPoints = -1;

	for (int i = 0; i < h; ++i) {
		// check if any are out of range
		bool inBounds[2];
		int ay = i - ayOffset;
		int by = i - byOffset;
		inBounds[0] = ay >= 0 && ay < a.height;
		inBounds[1] = by >= 0 && by < b.height;

		// decode regions
		for (int r = 0; r < 2; ++r) {
			if (!inBounds[r]) {
				inversionLifetime[r] = 0;
			}
			if (inBounds[r] && inversionLifetime[r] == 0) {
				//assert(ptr[r] < maxPtr[r]);
				
				uint32_t data = *(ptr[r]);
				if (data == 0xFFFFFFFF) {
					inBounds[r] = false;
					continue;
				}
				numInversionPoints[r] = data & 0xFFFF;
				inversionLifetime[r] = data >> 16;
				ptr[r]++;
				
				for (int j = 0; j < numInversionPoints[r]; ++j) {
					//assert(j < MAX_INV_POINTS);
					inversionPoints[r][j] = *(ptr[r]);
					//assert(ptr[r] < maxPtr[r]);
					ptr[r]++;
					//assert(ptr[r] <= maxPtr[r]);
				}
			}
		}
	
		int numOutputInversionPoints = 0;
		int aCurr = 0;
		int bCurr = 0;

		bool aIn = false;
		bool bIn = false;
		bool cIn = false;

		bool sameAsLastTime = true;

		while ((inversionLifetime[0] && aCurr < numInversionPoints[0]) || (inversionLifetime[1] && bCurr < numInversionPoints[1])) {
			//assert(aCurr < MAX_INV_POINTS);
			//assert(bCurr < MAX_INV_POINTS);
			
			int aInv = aCurr < numInversionPoints[0] && inversionLifetime[0] ? inversionPoints[0][aCurr] + axOffset : -1;
			int bInv = bCurr < numInversionPoints[1] && inversionLifetime[1] ? inversionPoints[1][bCurr] + bxOffset : -1;

			if (aInv == -1) aIn = false;
			if (bInv == -1) bIn = false;

			int location = aInv;

			if (aInv != -1 && (aInv <= bInv || bInv == -1)) {		//		<= is crucial
				aIn ^= true;
				++aCurr;
			}
			if (bInv != -1 && (bInv <= aInv || aInv == -1)) {		//		<= is crucial
				bIn ^= true;
				++bCurr;
				location = bInv;
			}

			bool newCIn = aIn;
			switch (op) {
			case RegionOperation::Difference:
				newCIn &= !bIn;
				break;
			case RegionOperation::Intersection:
				newCIn &= bIn;
				break;
			case RegionOperation::Union:
				newCIn |= bIn;
				break;
			case RegionOperation::XOR:
				newCIn ^= bIn;
				break;
			}

			if (newCIn != cIn) {
				cIn = newCIn;
				//assert(numOutputInversionPoints < MAX_INV_POINTS);
				if (lastTimeInversionPoints[numOutputInversionPoints] != location) {
					sameAsLastTime = false;
				}
				outputInversionPoints[numOutputInversionPoints++] = location;
				//assert(numOutputInversionPoints < MAX_INV_POINTS);
			}
		}

		if (sameAsLastTime && numOutputInversionPoints == lastTimeNumOutputInversionPoints) {
			inARow++;
		} else {
			if (inARow != 0) {
				bytesUsed = compressScanlineAndAddToRegion(&rgn, bytesUsed, lastTimeInversionPoints, lastTimeNumOutputInversionPoints, inARow);
			}
			lastTimeNumOutputInversionPoints = numOutputInversionPoints;
			//assert(lastTimeNumOutputInversionPoints < MAX_INV_POINTS);
			memcpy(lastTimeInversionPoints, outputInversionPoints, lastTimeNumOutputInversionPoints * 4);
			inARow = 1;
		}

		if (inversionLifetime[0]) --inversionLifetime[0];
		if (inversionLifetime[1]) --inversionLifetime[1];
	}

	if (inARow != 0) {
		//assert(lastTimeNumOutputInversionPoints < MAX_INV_POINTS);
		bytesUsed = compressScanlineAndAddToRegion(&rgn, bytesUsed, lastTimeInversionPoints, lastTimeNumOutputInversionPoints, inARow);
	}

	rgn.dataSize = bytesUsed;
	rgn.data[rgn.dataSize / 4] = 0xFFFFFFFF;
	rgn.dataSize += 4;
	uint32_t* res = (uint32_t*) realloc(rgn.data, rgn.dataSize);
	if (res == nullptr) {
		KePanic("abort");
	}
	rgn.data = res;

	return rgn;
}

Region getRegionUnion(Region a, Region b)
{
	return performRegionOperation(a, b, RegionOperation::Union);
}

Region getRegionDifference(Region a, Region b)
{
	return performRegionOperation(a, b, RegionOperation::Difference);
}

Region getRegionIntersection(Region a, Region b)
{
	return performRegionOperation(a, b, RegionOperation::Intersection);
}

Region getRegionXOR(Region a, Region b)
{
	return performRegionOperation(a, b, RegionOperation::XOR);
}

bool isPointInRegion(Region rgn, int wantX, int wantY)
{
	int scanline = 0;
	int i = 0;

	while (scanline < rgn.height) {
		uint32_t dword = rgn.data[i++];
		if (dword == 0xFFFFFFFF) {
			return false;
		}
		int numInversions = dword & 0xFFFF;
		int times = dword >> 16;

		uint32_t* data = (uint32_t*) (rgn.data + i);
		i += numInversions;

		bool in = false;
		int x = 0;
		while (x < rgn.width) {
			if (*data == x) {
				++data;
				in ^= true;
				--numInversions;
			}

			if (in) {

				if (scanline + rgn.relY <= wantY && wantY < scanline + rgn.relY + times) {
					if (rgn.relX + x <= wantX && wantX < rgn.relX + x + (*data) - x) {
						return true;
					}
				}
			}

			if (numInversions) {
				x = *data;

			} else if (!in) {		// no more inversions, and we're not in
				break;

			} else {
				++x;
			}
		}

		if (scanline + rgn.relY == wantY) {
			return false;
		}

		scanline += times;
	}

	return false;
}