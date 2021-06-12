#include <krnl/signal.hpp>
#include <krnl/panic.hpp>
#include <core/common.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void KiDefaultSignalHandlerAbort(int sig)
{
	KePanic("KiDefaultSignalHandlerAbort");
}

void KiDefaultSignalHandlerTerminate(int sig)
{
	KePanic("KiDefaultSignalHandlerTerminate");
}

void KiDefaultSignalHandlerIgnore(int sig)
{

}

void KiDefaultSignalHandlerPause(int sig)
{
	KePanic("KiDefaultSignalHandlerPause");
}

void KiDefaultSignalHandlerResume(int sig)
{
	KePanic("KiDefaultSignalHandlerResume");
}

void KiSigKill(int sig)
{
	KePanic("KiSigKill");
}

#define	SIGHUP	1		/* hangup */
#define	SIGINT	2		/* interrupt */
#define	SIGQUIT	3		/* quit */
#define	SIGILL	4		/* illegal instruction (not reset when caught) */
#define	SIGTRAP	5		/* trace trap (not reset when caught) */
#define	SIGIOT	6		/* IOT instruction */
#define	SIGABRT 6		/* used by abort, replace SIGIOT in the future */
#define	SIGEMT	7		/* EMT instruction */
#define	SIGFPE	8		/* floating point exception */
#define	SIGKILL	9		/* kill (cannot be caught or ignored) */
#define	SIGBUS	10		/* bus error */
#define	SIGSEGV	11		/* segmentation violation */
#define	SIGSYS	12		/* bad argument to system call */
#define	SIGPIPE	13		/* write on a pipe with no one to read it */
#define	SIGALRM	14		/* alarm clock */
#define	SIGTERM	15		/* software termination signal from kill */

sig_handler_bna_t KiDefaultSignalHandlers[] = {
	KiDefaultSignalHandlerAbort,			//NULL
	KiDefaultSignalHandlerTerminate,		//SIGHUP
	KiDefaultSignalHandlerTerminate,		//SIGINT
	KiDefaultSignalHandlerAbort,			//SIGQUIT
	KiDefaultSignalHandlerAbort,			//SIGILL
	KiDefaultSignalHandlerAbort,			//SIGTRAP
	KiDefaultSignalHandlerAbort,			//SIGIOT
	KiDefaultSignalHandlerAbort,			//SIGABRT
	KiDefaultSignalHandlerAbort,			//SIGEMT
	KiDefaultSignalHandlerAbort,			//SIGFPE
	KiSigKill,								//SIGKILL
	KiDefaultSignalHandlerAbort,			//SIGBUS
	KiDefaultSignalHandlerAbort,			//SIGSEGV
	KiDefaultSignalHandlerAbort,			//SIGSYS
	KiDefaultSignalHandlerTerminate,		//SIGPIPE
	KiDefaultSignalHandlerTerminate,		//SIGALRM
	KiDefaultSignalHandlerTerminate,		//SIGTERM
	KiDefaultSignalHandlerAbort,			//NULL
	KiDefaultSignalHandlerAbort,			//NULL
};

SigHandlerBlock KeInitSignals()
{
	kprintf("KeInitSignals A\n");
	SigHandlerBlock ret;
	ret.pendingBase = 0;
	ret.current = 0;

	memset(ret.pending, 0, sizeof(ret.pending));
	memset(ret.handler, 0, sizeof(ret.handler));
	kprintf("KeInitSignals B\n");

	return ret;
}

int KeRegisterSignalHandler(SigHandlerBlock* shb, int sig, sig_handler_bna_t handler, uint32_t mask, int flags)
{
	kprintf("KeRegisterSignalHandler A\n");

	if (sig >= __MAX_SIGNALS__) {
		return 1;
	}

	kprintf("A 0x%X\n", &shb->handler[sig]);
	kprintf("A 0x%X\n", &shb->masks[sig]);
	kprintf("A 0x%X\n", &shb->flags[sig]);
	/*shb->handler[sig] = handler;
	* 
	shb->masks[sig] = mask | (1 << sig);
	shb->flags[sig] = 0;*/
	kprintf("KeRegisterSignalHandler C\n");

	return 0;
}

int KeRaiseSignal(SigHandlerBlock* shb, int sig)
{
	return 1;
	kprintf("KeRaiseSignal A\n");

	shb->checkSignals = true;
	int base = shb->pendingBase;

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[(i + base) % MAX_PENDING_SIGNALS] == 0) {
			shb->pending[(i + base) % MAX_PENDING_SIGNALS] = sig;
			kprintf("KeRaiseSignal B\n");
			return 0;
		}
	}
	kprintf("KeRaiseSignal C\n");

	return 1;
}

size_t KeCheckSignal(SigHandlerBlock* shb)
{
	return 0;
	kprintf("KeCheckSignal A\n");

	if (!shb->checkSignals) {
		return 0;
	}
	kprintf("KeCheckSignal B\n");

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[(shb->pendingBase + i) % MAX_PENDING_SIGNALS]) {
			int sig = shb->pending[(shb->pendingBase + i) % MAX_PENDING_SIGNALS];
			kprintf("KeCheckSignal C\n");

			for (int j = 0; j < __MAX_SIGNALS__; ++j) {
				if ((shb->current & (1 << j)) && (shb->masks[j] & (1 << sig))) {
					//blocked for now
					kprintf("KeCheckSignal D\n");
					return 0;
				}
			}
			kprintf("KeCheckSignal E\n");

			//only increase base if can actually be handled
			shb->pending[shb->pendingBase++] = 0;
			shb->current |= 1 << sig;

			shb->checkSignals = false;

			for (int j = 0; j < MAX_PENDING_SIGNALS; ++j) {
				if (shb->pending[j]) {
					shb->checkSignals = true;
					break;
				}
			}
			kprintf("KeCheckSignal F\n");

			size_t handler = (size_t) shb->handler[sig];

			if (sig == SIGKILL) {
				kprintf("KeCheckSignal G\n");

				return (size_t) KiSigKill;

			} else if (handler == SIG_IGN) {
				kprintf("KeCheckSignal H\n");
				return 0;

			} else if (handler == SIG_DFL) {
				kprintf("KeCheckSignal I\n");
				return (size_t) KiDefaultSignalHandlers[sig];
			}

			kprintf("KeCheckSignal J\n");
			return handler;
		}
		++shb->pendingBase;
	}
	kprintf("KeCheckSignal K\n");

	return 0;
}

void KeCompleteSignal(SigHandlerBlock* shb, int sig)
{
	if (sig >= __MAX_SIGNALS__ || !(shb->current & (1 << sig))) {
		KePanic("KeCompleteSignal");
	}
	shb->current &= ~(1 << sig);
}