#include <krnl/common.hpp>
#include <krnl/main.hpp>
#include <krnl/computer.hpp>
#include <krnl/hal.hpp>
#include <krnl/panic.hpp>
#include <krnl/intlformat.hpp>
#include <krnl/atexit.hpp>
#include <fs/vfs.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

klocale_t keLocale;

int KeGetDigitsInNumber(long long int n)
{
	int digits = 0;
	while (n) {
		n /= 10;
		++digits;
	}
	return digits;
}

void KeInitialiseLocale()
{
	klocale_t aus;
	aus.currencySign = '$';
	aus.dateSeparator = '/';
	aus.decimalPoint = '.';
	aus.digitSeparator = ',';
	aus.centsDigits = 2;
	aus.digitGroupingAmount = 3;
	aus.negativeSign = '-';
	aus.negativeSignIsTrailing = false;
	aus.negativeSignSeparateWithSpace = false;
	aus.negativeSignWrapWithBracketsInstead = false;
	aus.currencySignIsTrailing = false;
	aus.useLeadingZerosForMonths = false;
	aus.useLeadingZerosForDays = false;
	strcpy(aus.dateFormatOrder, "DMY");

	/*File* f = new File("C:/aus.locale", kernelProcess);
	f->open(FILE_OPEN_WRITE_NORMAL);
	char name[48];
	int br;
	memset(name, 0, 48);
	strcpy(name, "Australia");
	f->write(48, name, &br);
	f->write(sizeof(aus), &aus, &br);
	f->close();*/

	KeSetLocale(aus);
}

void KeFormatDate(char* output, int bufferSize, int day, int month, int year, bool longYear)
{
	char internalBuffer[128];
	char charBuffer[5];
	internalBuffer[0] = 0;

	for (int i = 0; i < 3; ++i) {
		bool usingDay = keLocale.dateFormatOrder[i] == 'D';
		bool usingMonth = keLocale.dateFormatOrder[i] == 'M';
		bool usingYear = keLocale.dateFormatOrder[i] == 'Y';

		int value = usingYear ? year :
					usingMonth ? month : day;

		if (usingYear) {
			if (longYear) {
				charBuffer[0] = (value / 1000) % 10 + '0';
				charBuffer[1] = (value / 100) % 10 + '0';
				charBuffer[2] = (value / 10) % 10 + '0';
				charBuffer[3] = (value / 1) % 10 + '0';
				charBuffer[4] = 0;
			} else {
				charBuffer[0] = (value / 10) % 10 + '0';
				charBuffer[1] = (value / 1) % 10 + '0';
				charBuffer[2] = 0;
			}
			
			strcat(internalBuffer, charBuffer);

		} else {
			bool oneDigit = KeGetDigitsInNumber(value) == 1;
			bool needLeadingZero = oneDigit && ((usingDay && keLocale.useLeadingZerosForDays) || (usingMonth && keLocale.useLeadingZerosForMonths));

			if (!oneDigit || needLeadingZero) {
				charBuffer[0] = (value / 10) % 10 + '0';
				charBuffer[1] = (value / 1) % 10 + '0';
				charBuffer[2] = 0;
			} else {
				charBuffer[0] = value % 10 + '0';
				charBuffer[1] = 0;
			}
			strcat(internalBuffer, charBuffer);
		}
		
		if (i == 0 || i == 1) {
			charBuffer[0] = keLocale.dateSeparator;
			charBuffer[1] = 0;
			strcat(internalBuffer, charBuffer);
		}
	}

	memset(output, 0, bufferSize);
	if (strlen(internalBuffer) + 1 <= bufferSize) {
		strcpy(output, internalBuffer);
	} else {
		memcpy(output, internalBuffer, bufferSize - 1);
	}
}

void KeFormatShortDate(char* output, int bufferSize, int day, int month, int year)
{
	KeFormatDate(output, bufferSize, day, month, year, false);
}

void KeFormatLongDate(char* output, int bufferSize, int day, int month, int year)
{
	KeFormatDate(output, bufferSize, day, month, year, true);
}

void KeSetLocale(klocale_t l)
{
	keLocale = l;
}

void KeFormatCurrency(char* output, int bufferSize, long long int dollars, int cents)
{
	
}

void KeFormatCurrency(char* output, int bufferSize, double dollars)
{

}

void KeFormatNumber(char* output, long long int number, long long decimals)
{

}

void KeFormatNumber(char* output, double number)
{

}