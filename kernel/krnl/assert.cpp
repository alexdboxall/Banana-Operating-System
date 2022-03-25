
#include <krnl/panic.hpp>
#include <krnl/intops.hpp>
#include <krnl/assert.hpp>
#include <libk/string.h>

/// <summary>
/// Called when an assertion fails, causing a system panic with the relevant details.
/// Not to be directly called.
/// </summary>
/// <param name="condition">The expression (in code) which failed the assertion.</param>
/// <param name="file">The file where the assertion failed.</param>
/// <param name="func">The function where the assertion failed.</param>
/// <param name="line">The line where the assertion failed.</param>
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