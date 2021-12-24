#pragma once

#include <stdint.h>

typedef struct klocale_t
{
	uint32_t currencySign;
	char dateFormatOrder[4];
	uint32_t dateSeparator;
	uint32_t decimalPoint;
	uint32_t digitSeparator;
	uint8_t centsDigits;
	uint8_t digitGroupingAmount;
	uint32_t negativeSign;
	bool negativeSignIsTrailing;
	bool negativeSignSeparateWithSpace;
	bool negativeSignWrapWithBracketsInstead;
	bool currencySignIsTrailing;
	bool useLeadingZerosForDays;
	bool useLeadingZerosForMonths;
	bool currencySignSeparateWithSpace;

} klocale_t;

extern klocale_t keLocale;

void KeInitialiseLocale();
void KeSetLocale(klocale_t l);
void KeFormatLongDate(char* output, int bufferSize, int day, int month, int year);
void KeFormatShortDate(char* output, int bufferSize, int day, int month, int year);
void KeFormatCurrency(char* output, int bufferSize, long long int dollars, long long int decimals = 0);
void KeFormatCurrency(char* output, int bufferSize, double dollars);
void KeFormatNumber(char* output, long long int number, long long decimals = 0);
void KeFormatNumber(char* output, double number);