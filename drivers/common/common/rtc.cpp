#include "rtc.hpp"
#include "core/computer.hpp"
#include "thr/prcssthr.hpp"
#include "core/common.hpp"

#define CURRENT_YEAR 2020
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

int RTC::open(int, int, void*)
{
	return 0;
}

int RTC::close(int, int, void*)
{
	return 0;
}

time_t RTC::timeInSecondsUTC()
{
	return rtcTime;
}

datetime_t RTC::timeInDatetimeUTC()
{
	return secondsToDatetime(timeInSecondsUTC());
}

bool RTC::setTimeInSecondsUTC(time_t t)
{
	return setTimeInDatetimeUTC(secondsToDatetime(t));
}

bool RTC::get_update_in_progress_flag()
{
	return computer->readCMOS(0xA) & 0x80;
}

bool RTC::setTimeInDatetimeUTC(datetime_t d)
{

	return false;
}

void RTC::completeRTCRefresh()
{
	unsigned char last_second;
	unsigned char last_minute;
	unsigned char last_hour;
	unsigned char last_day;
	unsigned char last_month;
	unsigned char last_year;
	unsigned char registerB;

	extern uint64_t nanoSinceBoot;

	uint64_t startTime = nanoSinceBoot;
	while (get_update_in_progress_flag()) {
		//wait until it becomes set
		if (nanoSinceBoot > startTime + (uint64_t) (2000 * 1000 * 1000)) {
			//if the system is broken enough that this fails, we
			//may as well just read it
			break;
		}
	}
	uint8_t second = computer->readCMOS(0x00);
	uint8_t minute = computer->readCMOS(0x02);
	uint8_t hour = computer->readCMOS(0x04);
	uint8_t day = computer->readCMOS(0x07);
	uint8_t month = computer->readCMOS(0x08);
	uint32_t year = computer->readCMOS(0x09);

	do {
		last_second = second;
		last_minute = minute;
		last_hour = hour;
		last_day = day;
		last_month = month;
		last_year = year;

		startTime = nanoSinceBoot;
		while (get_update_in_progress_flag()) {
			//wait until it becomes set
			if (nanoSinceBoot > startTime + (uint64_t) (2000 * 1000 * 1000)) {
				//if the system is broken enough that this fails, we
				//may as well just read it
				break;
			}
		}

		second = computer->readCMOS(0x00);
		minute = computer->readCMOS(0x02);
		hour = computer->readCMOS(0x04);
		day = computer->readCMOS(0x07);
		month = computer->readCMOS(0x08);
		year = computer->readCMOS(0x09);

	} while ((last_second != second) || (last_minute != minute) || (last_hour != hour) ||
		(last_day != day) || (last_month != month) || (last_year != year));

	registerB = computer->readCMOS(0x0B);

	//convert BCD to binary
	if (!(registerB & 0x04)) {
		second = (second & 0x0F) + ((second / 16) * 10);
		minute = (minute & 0x0F) + ((minute / 16) * 10);
		hour = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80);
		day = (day & 0x0F) + ((day / 16) * 10);
		month = (month & 0x0F) + ((month / 16) * 10);
		year = (year & 0x0F) + ((year / 16) * 10);
	}

	if (!(registerB & 0x02) && (hour & 0x80)) {
		hour = ((hour & 0x7F) + 12) % 24;
	}

	year += (CURRENT_YEAR / 100) * 100;
	if (year < CURRENT_YEAR) {
		year += 100;
	}

	datetime_t d;
	d.second = second;
	d.minute = minute;
	d.hour = hour;
	d.day = day;
	d.month = month;
	d.year = year;

	kprintf("RTC ACTUAL HOUR = %d\n", hour);

	rtcTime = datetimeToSeconds(d);
}

void rtcIRQHandler(regs* regs, void* context)
{
	static uint16_t count = 0;

	//must read status so the next IRQ will come
	uint8_t val = computer->readCMOS(0x0C);
	
	//we only want update IRQs (all others are disabled anyway though)
	if (val & 0x80) {
		RTC* rtc = (RTC*) context;
		rtc->rtcTime++;

		//get the actual values every 65536 seconds to account for drift caused by missed IRQs (18 hours)
		++count;
		if (count == 0) {
			rtc->completeRTCRefresh();
		}
	}
}

RTC::RTC() : Clock("CMOS Real Time Clock")
{
	interrupt = addIRQHandler(8, rtcIRQHandler, true, (void*) this);

	disableIRQs();
	
	//enable RTC update IRQs
	uint8_t prev = computer->readCMOS(0x0B);
	computer->writeCMOS(0x0B, prev | 0x10);

	completeRTCRefresh();
	enableIRQs();
}

RTC::~RTC()
{

}