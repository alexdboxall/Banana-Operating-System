#pragma once

#ifndef _VM8086_HPP_
#define _VM8086_HPP_

#include <stdint.h>
#include <stddef.h>

#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"

namespace Vm
{
	bool loadFileAsThread(Process* p, const char* filename, uint16_t ip, uint16_t cs, uint16_t sp, uint16_t ss);
	bool faultHandler(regs* r);
}


#endif