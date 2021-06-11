#ifdef __cplusplus
extern "C" {
#endif

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

#define __MAX_SIGNALS__ 17

	typedef void (*sig_handler_bna_t)(int sig, void* hwctxt);

#ifdef __cplusplus
}
#endif
