#ifndef _DEBUG_HPP__
#define _DEBUG_HPP__

#include "core/common.hpp"
#include "hal/intctrl.hpp"

namespace Debug
{
	extern bool exceptionInDebugger = false;

	void displayFunctionCallers(int levels = 2);
	void handleFault(regs* r);

}

#endif