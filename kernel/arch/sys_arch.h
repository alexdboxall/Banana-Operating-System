#pragma once

#include <stdint.h>
#include <stddef.h>

typedef size_t sys_sem_t;
typedef size_t sys_mbox_t;
typedef size_t sys_thread_t;
typedef size_t sys_mutex_t;

#define SYS_MBOX_NULL 0
#define SYS_SEM_NULL 0

#define sys_sem_valid(x)		1
#define sys_mbox_valid(x)		1
#define sys_sem_set_invalid(x)	
#define sys_mbox_set_invalid(x) 