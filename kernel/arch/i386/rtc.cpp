#include "arch/i386/rtc.hpp"
#include "krnl/computer.hpp"
#include "thr/prcssthr.hpp"
#include "krnl/common.hpp"

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
	//clear minutes and seconds so we know no imporant updates will take place
	computer->writeCMOS(0x00, 0);
	computer->writeCMOS(0x02, 0);

	uint8_t second = d.second;
	uint8_t minute = d.minute;
	uint8_t hour = d.hour;
	uint8_t day = d.day;
	uint8_t month = d.month;
	uint8_t year = d.year % 100;

	uint8_t registerB = computer->readCMOS(0x0B);

	//convert binary to BCD
	if (!(registerB & 0x04)) {
		second = (second % 10) | ((second / 10) * 16);
		minute = (minute % 10) | ((minute / 10) * 16);
		hour = (hour % 10)	| ((hour / 10) * 16);
		day = (day % 10) | ((day / 10) * 16);
		month = (month % 10) | ((month / 10) * 16);
		year = (year % 10) | ((year / 10) * 16);
	}

	//12 hour mode
	if (!(registerB & 0x02)) {
		if (hour >= 12) {
			//12-23 to 1-12
			hour -= 12;
			//0-11 to 1-12
			if (hour == 0) hour = 12;
			hour |= 0x80;
		} else {
			//0-11 to 1-12
			if (hour == 0) hour = 12;
		}
	}

	computer->writeCMOS(0x00, second);
	computer->writeCMOS(0x02, minute);
	computer->writeCMOS(0x04, hour);
	computer->writeCMOS(0x07, day);
	computer->writeCMOS(0x08, month);
	computer->writeCMOS(0x09, year);

	completeRTCRefresh();
	return true;
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

	extern uint32_t milliTenthsSinceBoot;

	uint32_t startTime = milliTenthsSinceBoot;
	while (get_update_in_progress_flag()) {
		//wait until it becomes set
		if (milliTenthsSinceBoot > startTime + 20000) {
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

		startTime = milliTenthsSinceBoot;
		while (get_update_in_progress_flag()) {
			//wait until it becomes set
			if (milliTenthsSinceBoot > startTime + 20000) {
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