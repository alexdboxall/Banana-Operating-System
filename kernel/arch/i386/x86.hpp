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


	uint32_t hasRDRAND : 1;
	uint32_t hasTSC : 1;
	uint32_t hasPAE : 1;
	uint32_t hasPSE : 1;
	uint32_t hasGlobalPages : 1;
	uint32_t hasPAT : 1;
	uint32_t hasSMEP : 1;
	uint32_t hasRDSEED : 1;
	uint32_t hasINVLPG : 1;
	uint32_t hasINVD : 1;
	uint32_t hasWBINVD : 1;
	uint32_t hasUMIP : 1;
	uint32_t hasSMAP : 1;
	uint32_t hasCR8 : 1;
	uint32_t hasSysenter : 1;
	uint32_t hasSyscall : 1;
	uint32_t hasMTRR : 1;
	uint32_t onboardFPU : 1;
	uint32_t hasTPAUSE : 1;

};

extern x86Features features;

uint8_t x86ReadCMOS(uint8_t reg);
void x86WriteCMOS(uint8_t reg, uint8_t val);
uint64_t x86rdmsr(uint32_t msr_id);
void x86wrmsr(uint32_t msr_id, uint64_t msr_value);