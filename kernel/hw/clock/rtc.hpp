#ifndef _RTC_HPP_
#define _RTC_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/clock.hpp"

void rtcIRQHandler(regs* regs, void* context);

class RTC: public Clock
{
private:

protected:
	friend void rtcIRQHandler(regs* regs, void* context);

	time_t rtcTime;
	bool get_update_in_progress_flag();

public:
	int open(int, int, void*);
	int close(int, int, void*);

	void completeRTCRefresh();

	time_t timeInSecondsUTC();
	datetime_t timeInDatetimeUTC();

	bool setTimeInSecondsUTC(time_t t);
	bool setTimeInDatetimeUTC(datetime_t d);

	RTC();
	virtual ~RTC();
};


#endif