#include "dbg/kconsole.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")
#include "core/terminal.hpp"

bool KeKernelInPanic = false;

void KePanic(const char* message)
{
	KeKernelInPanic = true;
	HalPanic(message);
}