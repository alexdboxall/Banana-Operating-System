#ifndef __x87EMULATOR__
#define __x87EMULATOR__

#include <stdint.h>
#include <stdbool.h>

#include "hal/intctrl.hpp"

typedef uint64_t Float80;

typedef struct _FPUState
{
	union
	{
		struct
		{
			uint16_t invalidOperation : 1;
			uint16_t denormalisedOperand : 1;
			uint16_t zeroDivide : 1;
			uint16_t overflow : 1;
			uint16_t underflow : 1;
			uint16_t precision : 1;
			uint16_t stackFault : 1;
			uint16_t errSummaryStatus : 1;
			uint16_t c0 : 1;
			uint16_t c1 : 1;
			uint16_t c2 : 1;
			uint16_t stackTop : 3;
			uint16_t c3 : 1;
			uint16_t fpuBusy : 1;
		};

		uint16_t status;
	};

	union
	{
		struct
		{
			uint16_t maskInvalidOperation : 1;
			uint16_t maskDenormalisedOperand : 1;
			uint16_t maskZeroDivide : 1;
			uint16_t maskOverflow : 1;
			uint16_t maskUnderflow : 1;
			uint16_t maskPrecision : 1;
			uint16_t : 2;
			uint16_t precisionControl : 2;
			uint16_t roundingControl : 2;
			uint16_t infinityControl : 1;
			uint16_t : 3;
		};

		uint16_t control;
	};

	Float80 regs[8];
	int valuesOnStack = 0;

} FPUState;

bool x87Handler(regs* r);

#endif
