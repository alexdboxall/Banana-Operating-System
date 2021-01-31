#ifndef _WAIT_INTERNAL_H
#define _WAIT_INTERNAL_H

#include <stdint.h>
#include <sys/types.h>

pid_t wait (int* stat_loc);
pid_t waitpid (pid_t pid, int* stat_loc, int options);

#endif //_WAIT_INTERNAL_H

