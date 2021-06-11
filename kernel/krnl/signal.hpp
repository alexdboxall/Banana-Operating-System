#pragma once

extern "C" {
#include <krnl/signaldef.h>
}

#include <stdint.h>

#define MAX_PENDING_SIGNALS		8

struct SigHandlerBlock
{
	sig_handler_bna_t* handler[__MAX_SIGNALS__];
	uint32_t masks[__MAX_SIGNALS__];
	uint8_t flags[__MAX_SIGNALS__];

	int pending[MAX_PENDING_SIGNALS];
	int pendingBase;
	int current;
	bool checkSignals;
};

SigHandlerBlock KeInitSignals();
int KeRegisterSignalHandler(SigHandlerBlock* shb, int sig, sig_handler_bna_t* handler, uint32_t mask, int flags);
int KeRaiseSignal(SigHandlerBlock* shb, int sig);
size_t KeCheckSignal(SigHandlerBlock* shb);