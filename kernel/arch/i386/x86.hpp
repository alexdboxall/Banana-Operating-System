#pragma once

#include <stdint.h>

typedef struct x86Features
{
	uint32_t hasAPIC : 1;
	uint32_t hasCPUID : 1;
	uint32_t hasACPI : 1;
	uint32_t hasMSR : 1;
	uint32_t hasx87 : 1;
	uint32_t hasMMX : 1;
	uint32_t has3DNow : 1;
	uint32_t hasSSE : 1;
	uint32_t hasSSE2 : 1;
	uint32_t hasSSE3 : 1;
	uint32_t hasSSE41 : 1;
	uint32_t hasSSE42 : 1;
	uint32_t hasSSSE3 : 1;
	uint32_t hasAVX : 1;
	uint32_t hasAVX512 : 1;
	uint32_t hasMCE : 1;
	uint32_t hasNXBit : 1;
	uint32_t hasLongMode : 1;

};

extern x86Features features;

uint8_t x86ReadCMOS(uint8_t reg);
void x86WriteCMOS(uint8_t reg, uint8_t val);