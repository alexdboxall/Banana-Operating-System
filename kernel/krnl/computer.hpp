#pragma once

#ifndef _COMPUTER_HPP_
#define _COMPUTER_HPP_

#include "krnl/common.hpp"
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

	bool nmiEnabled();
	void enableNMI(bool enable = true);
	void disableNMI();

	uint8_t readCMOS(uint8_t reg);
	void writeCMOS(uint8_t reg, uint8_t val);

	void handleNMI();

	Clock* clock;
	CPU* cpu[1];
	FPU* fpu;

	ACPI* root;
};

namespace Krnl
{
	extern Computer* computer;
}

using Krnl::computer;

extern bool KeIsSchedulingOn;
extern bool KeIsPreemptionOn;

void KePrepareShutdown();
void KeShutdown();
void KeSleep();
void KeRestart();

#endif