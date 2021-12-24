#pragma once

#include <stdint.h>

void KeBasedUnsignedIntegerToString(uint64_t i, char b[], int base);
void KeBasedSignedIntegerToString(int64_t i, char b[], int base);
void KeItoa(long long int i, char* bf);
void KeXtoa(uint64_t i, char* bf);
int KeGetDigitsInNumber(long long int n);