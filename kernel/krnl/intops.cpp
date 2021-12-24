#include <krnl/intops.hpp>

void KeBasedUnsignedIntegerToString(uint64_t i, char b[], int base)
{
	char const digit[] = "0123456789ABCDEF";

	char* p = b;
	uint64_t shifter = i;
	do { //Move to where representation ends
		++p;
		shifter = shifter / base;
	} while (shifter);
	*p = '\0';
	do { //Move back, inserting digits as u go
		*--p = digit[i % base];
		i = i / base;
	} while (i);
}

void KeBasedSignedIntegerToString(int64_t i, char b[], int base)
{
	char const digit[] = "0123456789ABCDEF";

	char* p = b;
	if (i < 0) {
		i = -i;
		*p++ = '-';
	}

	uint64_t shifter = i;
	do { //Move to where representation ends
		++p;
		shifter = shifter / base;
	} while (shifter);
	*p = '\0';
	do { //Move back, inserting digits as u go
		*--p = digit[i % base];
		i = i / base;
	} while (i);
}

int KeGetDigitsInNumber(long long int n)
{
	int digits = 0;
	while (n) {
		n /= 10;
		++digits;
	}
	return digits;
}

void KeItoa(unsigned long long int i, char* bf)
{
	KeBasedUnsignedIntegerToString(i, bf, 10);
}

void KeItoa(long long int i, char* bf)
{
	KeBasedSignedIntegerToString(i, bf, 10);
}

void KeXtoa(uint64_t i, char* bf)
{
	KeBasedUnsignedIntegerToString(i, bf, 16);
}