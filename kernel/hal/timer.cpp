#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "hw/cpu.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hw/timer/pit.hpp"
#include "hw/intctrl/apic.hpp"
#include "hw/timer/apictimer.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint32_t milliTenthsSinceBoot = 0;

Timer::Timer(const char* name) : Device(name)
{
	deviceType = DeviceType::Timer;

}

Timer::~Timer()
{

}

int Timer::read()
{
	return frequency;
}

Timer* setupTimer(int hz)
{
	/*if (CPU::getNumber() != 0) {
		APICTimer* t = new APICTimer();
		t->open(hz, 0, nullptr);
		computer->addChild(t);
		return t;
	}

	if (computer->features.hasAPIC) {
		PIT* timer = new PIT();
		computer->addChild(timer);
		timer->open(hz, 0, nullptr);

		APICTimer* timer2 = new APICTimer();
		timer2->open(hz, 0, nullptr);

		timer->close(0, 0, nullptr);

		computer->addChild(timer2);

		return timer;

	} else {*/
		PIT* timer = new PIT();
		computer->addChild(timer);
		timer->open(hz, 0, nullptr);
		return timer;
	/*}*/

	return nullptr;
}

void timerHandler(uint32_t milliTenths)
{
	milliTenthsSinceBoot += milliTenths;

	if (!KeIsSchedulingOn) return;

	ThreadControlBlock* next_task;
	ThreadControlBlock* this_task = nullptr;

	lockStuff();

	if (!sleepingTaskList.isEmpty()) {
		ThreadControlBlock* first = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
		do {
			ThreadControlBlock* curr = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
			sleepingTaskList.removeFirst();

			if (curr->sleepExpiry <= milliTenthsSinceBoot) {

				unblockTask(curr);
				if (curr == first) {
					first = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
				}

			} else {
				sleepingTaskList.addElement(curr);
			}

		} while (!sleepingTaskList.isEmpty() && (ThreadControlBlock*) sleepingTaskList.getFirstElement() != first);
	}

	//do preemption
	if (currentTaskTCB->timeSliceRemaining != 0 && KeIsPreemptionOn) {
		lockScheduler();		
		currentTaskTCB->timeSliceRemaining -= milliTenthsSinceBoot;
		if (currentTaskTCB->timeSliceRemaining <= milliTenthsSinceBoot) {
			schedule();
		}
		unlockScheduler();
	}

	// Done, unlock the scheduler (and do any postponed task switches!)

	unlockStuff();
}