
#ifndef _SMP_HPP_
#define _SMP_HPP_

#include <stdint.h>
#include "core/common.hpp"
#include "hw/cpu.hpp"
#include "hw/acpi.hpp"
#include "hw/intctrl/apic.hpp"

namespace Krnl
{
	void startCPU (int num);
}

#endif