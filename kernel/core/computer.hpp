#pragma once

#ifndef _COMPUTER_HPP_
#define _COMPUTER_HPP_

#include "core/common.hpp"
#include "hal/device.hpp"

class ACPI;
class CPU;
class FPU;
class Clock;

extern "C" void KeEntryPoint();
extern void KeFirstTask();

class Computer : public Device
{
private:
	friend void KeEntryPoint();
	Computer();
	int open(int a, int b, void* c);

protected:
	bool nmi;
	void detectFeatures();

public:
	int close(int a, int b, void* c);

	void shutdown();
	void restart();
	void sleep();

	void setBootMessage(const char* message);

	bool nmiEnabled();
	void enableNMI(bool enable = true);
	void disableNMI();

	void displayFeatures();

	uint8_t readCMOS(uint8_t reg);
	void writeCMOS(uint8_t reg, uint8_t val);

	void handleNMI();

	Clock* clock;
	CPU* cpu[1];
	FPU* fpu;

	ACPI* root;

	struct ComputerFeatures
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

	} features;

	void wrmsr(uint32_t msr_id, uint64_t msr_value);
	uint64_t rdmsr(uint32_t msr_id);
};

namespace Krnl
{
	extern Computer* computer;
	
	void firstTask();
}

using Krnl::computer;

extern bool KeIsSchedulingOn;
extern bool KeIsPreemptionOn;

#endif