
extern "C" {
#include <libk/string.h>
}
#include <thr/alarm.hpp>
#include <hal/timer.hpp>

uint64_t KeAlarm(ThreadControlBlock* thr, uint64_t millitenth)
{
	kprintf("set alarm here: %d\n", (int) millitenth);
	uint64_t ret = thr->alarm ? thr->alarm - milliTenthsSinceBoot : 0;
	thr->alarm = millitenth ? millitenth + milliTenthsSinceBoot : 0;
	kprintf("total = %d\n", (int) thr->alarm);
	return ret;
}

void KeCheckAlarm(ThreadControlBlock* thr)
{
	kprintf("Checking alarm. (%d vs %d)\n", (int) thr->alarm, (int) milliTenthsSinceBoot);
	if (thr->alarm && thr->alarm <= milliTenthsSinceBoot) {
		thr->alarm = 0;
		kprintf("raising SIGALRM\n");
		KeRaiseSignal(thr->processRelatedTo->signals, SIGALRM);
	}
}
