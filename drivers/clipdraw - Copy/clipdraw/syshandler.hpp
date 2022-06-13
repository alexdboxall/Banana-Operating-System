#pragma once

#include <stdint.h>

#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"

uint64_t NiSystemCallHandler(regs* r);
void NiInstallSysHooks();