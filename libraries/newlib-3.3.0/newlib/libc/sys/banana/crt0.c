#include <fcntl.h>

#pragma GCC push_options
#pragma GCC optimize ("O0")

extern void exit(int code);
extern int main ();
void _init_signal();
extern void _environ_setup();

#include <stdint.h>
#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"

extern uint64_t SystemCall(size_t a, size_t b, size_t c, size_t d);

void _start() {    
    _init_signal();
    _environ_setup();

	int rtid = SystemCall(PthreadGetTID, 0, 0, 0);
	if (rtid == 0) {
		int argc = SystemCall(GetArgc, 0, 0, 0);
		char** argv = malloc((argc + 2) * sizeof(char*));

		for (int i = 0; i < argc; ++i) {
			argv[i] = calloc(512, 1);
			int r = SystemCall(GetArgv, i, 0, (size_t) argv[i]);
			if (r != 0) break;
		}

		int ex = main(argc, argv);
		exit(ex);

	} else {
		void (*start)(void*) = (void(*)(void*))SystemCall(InternalPthreadGetStartLocation, 0, 0, 0);
		void* ctxt = (void*) SystemCall(InternalPthreadGetContext, 0, 0, 0);

		start(ctxt);

	}
}

#include <signal.h>
void _init_signal()
{
	for (int i = 0; i < __MAX_SIGNALS__; ++i) {
		signal(i, SIG_DFL);
	}
}

#pragma GCC pop_options