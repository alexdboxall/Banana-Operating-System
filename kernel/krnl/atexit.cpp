#include <core/common.hpp>
#include <core/main.hpp>
#include <core/computer.hpp>
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

#define MAX_ATEXIT_HANDLERS 64

void (*KiAtexitHandlers[MAX_ATEXIT_HANDLERS])(void*);
void* KiAtexitContexts[MAX_ATEXIT_HANDLERS];
int KiNextAtexitHandler = 0;

void KeInitialiseAtexit()
{
	KiNextAtexitHandler = 0;
	memset(KiAtexitHandlers, 0, sizeof(KiAtexitHandlers));
}

void KeRegisterAtexit(void (*handler)(void*), void* context)
{
	KiAtexitHandlers[KiNextAtexitHandler] = handler;
	KiAtexitContexts[KiNextAtexitHandler] = context;

	++KiNextAtexitHandler;

	if (KiNextAtexitHandler >= MAX_ATEXIT_HANDLERS) {
		KePanic("TOO MANY ATEXIT HANDLERS");
	}
}

void KeExecuteAtexit()
{
	for (int i = 0; i < KiNextAtexitHandler; ++i) {
		if (KiAtexitHandlers[i]) {
			KiAtexitHandlers[i](KiAtexitContexts[i]);
			KiAtexitHandlers[i] = nullptr;
		}
	}
}