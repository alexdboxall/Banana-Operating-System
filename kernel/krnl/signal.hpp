#pragma once

extern "C" {
#include <krnl/signaldef.h>
}

#include <stdint.h>
#include <stddef.h>

//a power of 2 is very helpful here
#define MAX_PENDING_SIGNALS		8

struct SigHandlerBlock
{
	sig_handler_bna_t handler[__MAX_SIGNALS__];
	uint32_t masks[__MAX_SIGNALS__];
	uint8_t flags[__MAX_SIGNALS__];

	int pending[MAX_PENDING_SIGNALS];
	int pendingBase;
	uint32_t current;
	bool checkSignals;
};

SigHandlerBlock* KeInitSignals();
void KeDeinitSignals(SigHandlerBlock* block);
int KeRegisterSignalHandler(SigHandlerBlock* shb, int sig, sig_handler_bna_t handler, uint32_t mask, int flags);
int KeRaiseSignal(SigHandlerBlock* shb, int sig);
size_t KeCheckSignal(SigHandlerBlock* shb, int* num);
void KeCompleteSignal(SigHandlerBlock* shb, int sig);