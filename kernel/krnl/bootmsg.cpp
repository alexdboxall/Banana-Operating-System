#include <krnl/common.hpp>
#include <krnl/bootmsg.hpp>
#include <krnl/hal.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Loads the boot splash screen and displays it.
/// </summary>
void KeDisplaySplashScreen()
{
	for (int i = 0; "Starting Banana..."[i]; ++i) {
		HalConsoleWriteCharacter("Starting Banana..."[i], 0xF, 0x0, 2 + i, 1);
	}
}

/// <summary>
/// Sets the message on the bottom of the boot splash screen.
/// </summary>
/// <param name="msg"></param>
void KeSetBootMessage(const char* msg)
{
	for (int i = 0; i < 80; ++i) {
		HalConsoleWriteCharacter(' ', 0, 0, i, 20);
	}

	int startingXPosition = (80 - strlen(msg)) / 2;
	for (int i = 0; msg[i]; ++i) {
		HalConsoleWriteCharacter(msg[i], 0x7, 0x0, startingXPosition + i, 20);
	}
}