
extern "C" {
#include <libk/string.h>
}
#include <krnl/panic.hpp>
#include <krnl/intops.hpp>
#include <krnl/assert.hpp>

void KeAssertionFailed(char* condition, const char* file, const char* func, int line)
{
	char msg[512];
	char intbf[32];
	KeItoa(line, intbf);
	strcpy(msg, "ASSERT FAIL: ");
	strcat(msg, condition);
	strcat(msg, ", ");
	strcat(msg, file);
	strcat(msg, ":");
	strcat(msg, func);
	strcat(msg, ":");
	strcat(msg, intbf);
	KePanic(msg);
}