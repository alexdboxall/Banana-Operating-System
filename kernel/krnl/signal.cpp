#include <krnl/signal.hpp>
#include <krnl/panic.hpp>
#include <core/common.hpp>

SigHandlerBlock KeInitSignals()
{
	SigHandlerBlock ret;
	ret.pendingBase = 0;

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		ret.pending[i] = 0;
	}

	ret.current = 0;

	return ret;
}

int KeRegisterSignalHandler(SigHandlerBlock* shb, int sig, sig_handler_bna_t* handler, uint32_t mask, int flags)
{
	if (sig >= __MAX_SIGNALS__) {
		return 1;
	}

	shb->handler[sig] = handler;
	shb->masks[sig] = mask | (1 << sig);
	shb->flags[sig] = 0;

	return 0;
}

int KeRaiseSignal(SigHandlerBlock* shb, int sig)
{
	int base = shb->pendingBase;

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[(i + base) % MAX_PENDING_SIGNALS] == 0) {
			shb->pending[(i + base) % MAX_PENDING_SIGNALS] = sig;
			return 0;
		}
	}

	return 1;
}

int KeCheckSignal(SigHandlerBlock* shb)
{
	bool found = false;
	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[shb->pendingBase]) {
			found = true;
			break;
		}
		++shb->pendingBase;
	}
	if (!found) {
		return 0;
	}

	int sig = shb->pending[shb->pendingBase];

	if (shb->masks[shb->current] & (1 << sig)) {
		//blocked for now
		return 0;
	}
	
	//only increase base if can actually be handled
	shb->pending[shb->pendingBase++] = 0;
	shb->current = sig;
	return sig;
}