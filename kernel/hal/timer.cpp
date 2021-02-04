#include "core/common.hpp"
#include "core/prcssthr.hpp"
#include "hw/cpu.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hw/timer/pit.hpp"
#include "hw/intctrl/apic.hpp"
#include "hw/timer/apictimer.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

uint64_t nanoSinceBoot = 0;

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
	if (getCPUNumber() != 0) {
		APICTimer* t = new APICTimer();
		t->open(hz, 0, nullptr);
		thisCPU()->intCtrl->addChild(t);
		return t;
	}

	if (thisCPU()->intCtrl->getName()[0] == 'A' && computer->features.hasAPIC) {
		PIT* timer = new PIT();
		computer->addChild(timer);
		timer->open(hz, 0, nullptr);

		APICTimer* timer2 = new APICTimer();
		timer2->open(hz, 0, nullptr);

		timer->close(0, 0, nullptr);

		thisCPU()->intCtrl->addChild(timer2);

		return timer;

	} else {
		PIT* timer = new PIT();
		computer->addChild(timer);
		timer->open(hz, 0, nullptr);
		return timer;
	}

	return nullptr;
}

void timerHandler(uint64_t nanosecs)
{
	nanoSinceBoot += nanosecs;

	if (!schedulingOn) return;

	ThreadControlBlock* next_task;
	ThreadControlBlock* this_task = nullptr;

	lockStuff();

	// For each task, wake it up or put it back on the sleeping task list

	ThreadControlBlock* first = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
	if (!sleepingTaskList.isEmpty()) {
		do {
			ThreadControlBlock* curr = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
			sleepingTaskList.removeFirst();

			if (curr->sleepExpiry <= nanoSinceBoot) {

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
	if (currentTaskTCB->timeSliceRemaining != 0 && preemptionOn) {
		if (currentTaskTCB->timeSliceRemaining <= nanosecs) {
			lockScheduler();
			currentTaskTCB->timeSliceRemaining -= nanosecs;
			schedule();
			unlockScheduler();
		} else {
			currentTaskTCB->timeSliceRemaining -= nanosecs;
		}
	}

	// Done, unlock the scheduler (and do any postponed task switches!)

	unlockStuff();
}