#include "fs/vfs.hpp"
#include "hal/clock.hpp"
#include "reg/cm.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace User
{
	int timezoneHourOffset = 0;
	bool timezoneHalfHourOffset = false;
	bool dstOn = false;

	void loadClockSettings()
	{
		char tzstring[600];
		tzstring[0] = 0;

		Reghive* reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
		int loc = CmFindObjectFromPath(reg, "BANANA/TIME/TIMEZONE");
		kprintf("REGISTRY: %d\n", loc);
		if (loc > 0) {
			CmGetString(reg, loc, tzstring);
		}		
		CmClose(reg);
		kprintf("tzstring = '%s', 0x%X\n", tzstring, tzstring[0]);

		if (tzstring[0] == '+' || tzstring[0] == '-') {
			User::dstOn = false;
			User::timezoneHalfHourOffset = \
				(tzstring[2] == '.' && tzstring[3] == '5') ||
				(tzstring[3] == '.' && tzstring[4] == '5');

			User::timezoneHourOffset = tzstring[1] - '0';
			if (tzstring[3] == '.') {
				User::timezoneHourOffset *= 10;
				User::timezoneHourOffset += tzstring[2] - '0';
			}		
			if (tzstring[0] == '-') {
				User::timezoneHourOffset = -User::timezoneHourOffset;
			}

		} else {
			User::dstOn = false;
			User::timezoneHalfHourOffset = 0;
			User::timezoneHourOffset = 0;
		}

		kprintf("Timezone: %d.%d\n", User::timezoneHourOffset, (int) User::timezoneHalfHourOffset * 5);
	}
}

Clock::Clock(const char* name): Device(name)
{
	deviceType = DeviceType::Clock;

}

Clock::~Clock()
{

}

time_t Clock::timeInSecondsLocal()
{
	using namespace User;
	return timeInSecondsUTC() + (timezoneHourOffset + dstOn) * 3600 + (timezoneHalfHourOffset ? 1800 : 0);
}

datetime_t Clock::timeInDatetimeLocal()
{
	return secondsToDatetime(timeInSecondsLocal());
}

bool Clock::setTimeInSecondsLocal(time_t t)
{
	using namespace User;
	return setTimeInSecondsUTC(t - (timezoneHourOffset + dstOn) * 3600 - (timezoneHalfHourOffset ? 1800 : 0));
}

bool Clock::setTimeInDatetimeLocal(datetime_t d)
{
	using namespace User;
	return setTimeInSecondsUTC(datetimeToSeconds(d) - (timezoneHourOffset + dstOn) * 3600 - (timezoneHalfHourOffset ? 1800 : 0));
}


/*
 * mktime.c
 * Original Author:	G. Haley
 *
 * Converts the broken-down time, expressed as local time, in the structure
 * pointed to by tim_p into a calendar time value. The original values of the
 * tm_wday and tm_yday fields of the structure are ignored, and the original
 * values of the other fields have no restrictions. On successful completion
 * the fields of the structure are set to represent the specified calendar
 * time. Returns the specified calendar time. If the calendar time can not be
 * represented, returns the value (time_t) -1.
 *
 * Modifications:	Fixed tm_isdst usage - 27 August 2008 Craig Howland.
 * Modifications:	Changed to use different data structures and arguments - 6 October 2020 Alex Boxall.
 */

/*
 * gmtime_r.c
 * Original Author: Adapted from tzcode maintained by Arthur David Olson.
 * Modifications:
 * - Changed to mktm_r and added __tzcalc_limits - 04/10/02, Jeff Johnston
 * - Fixed bug in mday computations - 08/12/04, Alex Mogilnikov <alx@intellectronika.ru>
 * - Fixed bug in __tzcalc_limits - 08/12/04, Alex Mogilnikov <alx@intellectronika.ru>
 * - Move code from _mktm_r() to gmtime_r() - 05/09/14, Freddie Chopin <freddie_chopin@op.pl>
 * - Fixed bug in calculations for dates after year 2069 or before year 1901. Ideas for
 *   solution taken from musl's __secs_to_tm() - 07/12/2014, Freddie Chopin
 *   <freddie_chopin@op.pl>
 * - Use faster algorithm from civil_from_days() by Howard Hinnant - 12/06/2014,
 * Freddie Chopin <freddie_chopin@op.pl>
 * - Changed to use different data structures and arguments - 6 October 2020 Alex Boxall.
 *  
 *
 *
 * Converts the calendar time pointed to by tim_p into a broken-down time
 * expressed as local time. Returns a pointer to a structure containing the
 * broken-down time.
 */

#define _SEC_IN_MINUTE 60L
#define _SEC_IN_HOUR 3600L
#define _SEC_IN_DAY 86400L

static const int DAYS_IN_MONTH[12] =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#define _DAYS_IN_MONTH(x) ((x == 1) ? days_in_feb : DAYS_IN_MONTH[x])

static const int _DAYS_BEFORE_MONTH[12] =
{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

#define _ISLEAP(y) (((y) % 4) == 0 && (((y) % 100) != 0 || (((y)+1900) % 400) == 0))
#define _DAYS_IN_YEAR(year) (_ISLEAP(year) ? 366 : 365)

#define EPOCH_ADJUSTMENT_DAYS	719468L
#define ADJUSTED_EPOCH_YEAR	0
#define ADJUSTED_EPOCH_WDAY	3
#define DAYS_PER_ERA		146097L
#define DAYS_PER_CENTURY	36524L
#define DAYS_PER_4_YEARS	(3 * 365 + 366)
#define DAYS_PER_YEAR		365
#define DAYS_IN_JANUARY		31
#define DAYS_IN_FEBRUARY	28
#define YEARS_PER_ERA		400
#define SECSPERMIN 60
#define SECSPERHOUR 3600
#define SECSPERDAY (3600 * 24)
#define YEAR_BASE 1900

time_t datetimeToSeconds(datetime_t dt)
{
	dt.year -= YEAR_BASE;
	dt.month--;

	time_t tim = 0;
	long days = 0;
	int year, isdst = 0;

	/* compute hours, minutes, seconds */
	tim += dt.second + (dt.minute * _SEC_IN_MINUTE) +
		(dt.hour * _SEC_IN_HOUR);

	/* compute days in year */
	days += dt.day - 1;
	days += _DAYS_BEFORE_MONTH[dt.month];
	if (dt.month > 1 && _DAYS_IN_YEAR(dt.year) == 366)
		days++;

	if ((year = dt.year) > 70) {
		for (year = 70; year < dt.year; year++) {
			days += _DAYS_IN_YEAR(year);
		}
	} else if (year < 70) {
		for (year = 69; year > dt.year; year--) {
			days -= _DAYS_IN_YEAR(year);
		}
		days -= _DAYS_IN_YEAR(year);
	}

	tim += (time_t) days * _SEC_IN_DAY;
	return tim;
}

datetime_t secondsToDatetime(time_t lcltime)
{
	datetime_t res;

	long days, rem;
	int era, weekday, year;
	unsigned erayear, yearday, month, day;
	unsigned long eraday;

	days = lcltime / SECSPERDAY + EPOCH_ADJUSTMENT_DAYS;
	rem = lcltime % SECSPERDAY;
	if (rem < 0) {
		rem += SECSPERDAY;
		--days;
	}

	/* compute hour, min, and sec */
	res.hour = (int) (rem / SECSPERHOUR);
	rem %= SECSPERHOUR;
	res.minute = (int) (rem / SECSPERMIN);
	res.second = (int) (rem % SECSPERMIN);

	/* compute year, month, day & day of year */
	/* for description of this algorithm see
	 * http://howardhinnant.github.io/date_algorithms.html#civil_from_days */
	era = (days >= 0 ? days : days - (DAYS_PER_ERA - 1)) / DAYS_PER_ERA;
	eraday = days - era * DAYS_PER_ERA;	/* [0, 146096] */
	erayear = (eraday - eraday / (DAYS_PER_4_YEARS - 1) + eraday / DAYS_PER_CENTURY -
			   eraday / (DAYS_PER_ERA - 1)) / 365;	/* [0, 399] */
	yearday = eraday - (DAYS_PER_YEAR * erayear + erayear / 4 - erayear / 100);	/* [0, 365] */
	month = (5 * yearday + 2) / 153;	/* [0, 11] */
	day = yearday - (153 * month + 2) / 5 + 1;	/* [1, 31] */
	month += month < 10 ? 2 : -10;
	year = ADJUSTED_EPOCH_YEAR + erayear + era * YEARS_PER_ERA + (month <= 1);

	res.year = year;
	res.month = month + 1;
	res.day = day;

	return res;
}