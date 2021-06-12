#include <krnl/signal.hpp>
#include <krnl/panic.hpp>
#include <core/common.hpp>
#include <thr/prcssthr.hpp>
#include <sys/syscalls.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")


//THESE RUN IN USER MODE!!!

void __attribute__((__section__(".userkernel"))) KiDefaultSignalHandlerAbort(int sig)
{
	char s[] = "KiDefaultSignalHandlerAbort";
	KeSystemCallFromUsermode((size_t) SystemCallNumber::Panic, 0, 0, (size_t) s);
}

void __attribute__((__section__(".userkernel"))) KiDefaultSignalHandlerTerminate(int sig)
{
	char s[] = "KiDefaultSignalHandlerTerminate";
	KeSystemCallFromUsermode((size_t) SystemCallNumber::Panic, 0, 0, (size_t) s);
}

void KiDefaultSignalHandlerIgnore(int sig)
{

}

void KiDefaultSignalHandlerPause(int sig)
{
	char s[] = "KiDefaultSignalHandlerPause";
	KeSystemCallFromUsermode((size_t) SystemCallNumber::Panic, 0, 0, (size_t) s);
}

void KiDefaultSignalHandlerResume(int sig)
{
	char s[] = "KiDefaultSignalHandlerResume";
	KeSystemCallFromUsermode((size_t) SystemCallNumber::Panic, 0, 0, (size_t) s);
}

void KiSigKill(int sig)
{
	char s[] = "KiSigKill";
	KeSystemCallFromUsermode((size_t) SystemCallNumber::Panic, 0, 0, (size_t) s);
}

//END OF USER MODE!!!



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

void KeDeinitSignals(SigHandlerBlock* block)
{
	free(block);
}

extern size_t START_USER_KERNEL;
extern size_t END_USER_KERNEL;

SigHandlerBlock* KeInitSignals()
{
	kprintf("START 0x%X\n", START_USER_KERNEL);
	kprintf("END   0x%X\n", END_USER_KERNEL);

	SigHandlerBlock* obj = (SigHandlerBlock*) malloc(sizeof(SigHandlerBlock));
	obj->pendingBase = 0;
	obj->current = 0;

	memset(obj->pending, 0, sizeof(obj->pending));
	memset(obj->handler, 0, sizeof(obj->handler));

	return obj;
}

int KeRegisterSignalHandler(SigHandlerBlock* shb, int sig, sig_handler_bna_t handler, uint32_t mask, int flags)
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
	kprintf("KeRaiseSignal A\n");

	shb->checkSignals = true;
	int base = shb->pendingBase;

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[(i + base) % MAX_PENDING_SIGNALS] == 0) {
			shb->pending[(i + base) % MAX_PENDING_SIGNALS] = sig;
			kprintf("KeRaiseSignal B went to slot %d\n", (i + base) % MAX_PENDING_SIGNALS);
			return 0;
		}
	}
	kprintf("KeRaiseSignal C\n");

	return 1;
}

extern "C" size_t KiCheckSignalZ()
{
	return KeCheckSignal(currentTaskTCB->processRelatedTo->signals);
}

size_t KeCheckSignal(SigHandlerBlock* shb)
{
	if (!shb->checkSignals) {
		return 0;
	}

	for (int i = 0; i < MAX_PENDING_SIGNALS; ++i) {
		if (shb->pending[(shb->pendingBase + i) % MAX_PENDING_SIGNALS]) {
			int sig = shb->pending[(shb->pendingBase + i) % MAX_PENDING_SIGNALS];

			for (int j = 0; j < __MAX_SIGNALS__; ++j) {
				if ((shb->current & (1 << j)) && (shb->masks[j] & (1 << sig))) {
					//blocked for now
					return 0;
				}
			}

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

			size_t handler = (size_t) shb->handler[sig];

			if (sig == SIGKILL) {
				return (size_t) KiSigKill;

			} else if (handler == SIG_IGN) {
				return 0;

			} else if (handler == SIG_DFL) {
				return (size_t) KiDefaultSignalHandlers[sig];
			}

			return handler;
		}
		++shb->pendingBase;
	}

	return 0;
}

void KeCompleteSignal(SigHandlerBlock* shb, int sig)
{
	if (sig >= __MAX_SIGNALS__ || !(shb->current & (1 << sig))) {
		KePanic("KeCompleteSignal");
	}
	shb->current &= ~(1 << sig);
}