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

public:
	int close(int a, int b, void* c);

	Clock* clock;
	CPU* cpu[1];
	FPU* fpu;

	ACPI* root;
};

extern Computer* computer;

extern bool KeIsSchedulingOn;
extern bool KeIsPreemptionOn;

#endif