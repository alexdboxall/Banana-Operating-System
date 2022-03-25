#include <krnl/common.hpp>
#include <krnl/main.hpp>
#include <krnl/computer.hpp>
#include <krnl/hal.hpp>
#include <krnl/panic.hpp>
#include <krnl/random.hpp>
#include <krnl/atexit.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define MAX_ATEXIT_HANDLERS 32

void (*kiAtexitHandlers[MAX_ATEXIT_HANDLERS])(void*);
void* kiAtexitContexts[MAX_ATEXIT_HANDLERS];
int kiNextAtexitHandler = 0;

/// <summary>
/// Initialises the table which stores handlers to run on system shutdown and restart.
/// Must only be called once by an early part of the kernel.
/// </summary>
void KeInitialiseAtexit()
{
	kiNextAtexitHandler = 0;
	memset(kiAtexitHandlers, 0, sizeof(kiAtexitHandlers));
}

/// <summary>
/// Registers a handler to be called on system shutdown or restart. It will fail and panic if
/// there are too many handlers (MAX_ATEXIT_HANDLERS) already registered.
/// <param name="handler">A handler to run. It will be passed 'context' as an argument.</param>
/// <param name="context">An argument to be passed to the handler.</param>
/// </summary>
void KeRegisterAtexit(void (*handler)(void*), void* context)
{
	kiAtexitHandlers[kiNextAtexitHandler] = handler;
	kiAtexitContexts[kiNextAtexitHandler] = context;

	++kiNextAtexitHandler;

	if (kiNextAtexitHandler >= MAX_ATEXIT_HANDLERS) {
		KePanic("TOO MANY ATEXIT HANDLERS");
	}
}

/// <summary>
/// Runs the registered atexit handlers.
/// Should only be called on system shutdown or restart.
/// </summary>
void KeExecuteAtexit()
{
	for (int i = 0; i < kiNextAtexitHandler; ++i) {
		if (kiAtexitHandlers[i]) {
			kiAtexitHandlers[i](kiAtexitContexts[i]);
			kiAtexitHandlers[i] = nullptr;
		}
	}
}