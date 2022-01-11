
extern "C" {
#include <libk/string.h>
}
#include <thr/alarm.hpp>
#include <hal/timer.hpp>

uint64_t KeAlarm(ThreadControlBlock* thr, uint64_t millitenth)
{
	uint64_t ret = thr->alarm ? thr->alarm - milliTenthsSinceBoot : 0;
	thr->alarm = millitenth ? millitenth + milliTenthsSinceBoot : 0;
	return ret;
}

void KeCheckAlarm(ThreadControlBlock* thr)
{
	if (thr->alarm && thr->alarm <= milliTenthsSinceBoot) {
		thr->alarm = 0;
		kprintf("raising SIGALRM\n");
		KeRaiseSignal(thr->processRelatedTo->signals, SIGALRM);
	}
}
