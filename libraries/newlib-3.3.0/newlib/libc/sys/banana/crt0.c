#include <fcntl.h>

#pragma GCC push_options
#pragma GCC optimize ("O0")

extern void exit(int code);
extern int main ();
extern void _init_signal();
extern void _environ_setup();

#include <stdint.h>
#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"

extern uint64_t SystemCall(size_t a, size_t b, size_t c, size_t d);

void _start() {    
    _init_signal();
    _environ_setup();

	int argc = SystemCall(GetArgc, 0, 0, 0);
	char** argv = malloc((argc + 2) * sizeof(char*));

	for (int i = 0; i < argc; ++i) {
		argv[i] = calloc(512, 1);
		int r = SystemCall(GetArgv, i, 0, (size_t) argv[i]);
		if (r != 0) break;
	}

    int ex = main(argc, argv);
    exit(ex);
}

#pragma GCC pop_options