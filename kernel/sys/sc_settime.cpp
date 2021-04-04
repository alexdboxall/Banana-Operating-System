#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hal/timer.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Sys
{
	/// <summary>
	/// Sets the system time.
	/// </summary>
	/// <param name="ebx">The number of seconds since midnight of the current day.</param>
	/// <param name="ecx">This is equal to DAY_OF_MONTH + MONTH * 32, where both a zero based.</param>
	/// <param name="edx">The year is stored in the low word. The high word is reserved.</param>
	/// <returns>Returns zero, even when it fails.</returns>
	/// 
	uint64_t setTime(regs* r)
	{
		//zero based
		int seconds = r->ebx % 60;
		int minutes = (r->ebx / 60) % 60;
		int hours = (r->ebx / 3600) % 24;

		//one based
		int day = ((r->ecx) % 32) + 1;
		int month = ((r->ecx / 32) % 12) + 1;

		int year = r->edx & 0xFFFF;

		return 0;
	}
}


