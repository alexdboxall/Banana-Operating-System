#pragma once

#ifndef _VM8086_HPP_
#define _VM8086_HPP_

#include <stdint.h>
#include <stddef.h>

#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"

namespace Vm
{
	void initialise8086();
	bool start8086(const char* filename, uint16_t ip, uint16_t cs, uint16_t sp, uint16_t ss);
	uint32_t finish8086();

	bool faultHandler(regs* r);
}


#endif