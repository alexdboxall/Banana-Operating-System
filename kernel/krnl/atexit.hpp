#pragma once

#include <stdint.h>

/// <summary>
/// Registers a handler to be called on system shutdown or restart.
/// <param name="handler">A handler to run with the given context.</param>
/// <param name="context">An argument to be passed to the handler.</param>
/// </summary>
void KeRegisterAtexit(void (*handler)(void*), void* context);


/// <summary>
/// Runs the atexit handlers. Should only be called on system shutdown or restart.
/// </summary>
void KeExecuteAtexit();


/// <summary>
/// Initialises atexit. Must only be called once by an early part of the kernel.
/// </summary>
void KeInitialiseAtexit();