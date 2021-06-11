#include <krnl/signal.hpp>
#include <krnl/panic.hpp>
#include <core/common.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

SigHandlerBlock KeInitSignals()
{
	SigHandlerBlock ret;
	ret.pendingBase = 0;
	ret.current = 0;

	memset(ret.pending, 0, sizeof(ret.pending));

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
	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[shb->pendingBase]) {
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
		++shb->pendingBase;
	}
	return 0;
}