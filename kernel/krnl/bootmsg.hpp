#pragma once

/// <summary>
/// Loads the boot splash screen.
/// </summary>
void KeDisplaySplashScreen();

/// <summary>
/// Sets the message on the bottom of the boot splash screen.
/// </summary>
/// <param name="msg"></param>
void KeSetBootMessage(const char* msg);