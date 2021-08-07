#include "arch/sys_arch.h"
#include "arch/cc.h"
#include "lwip/err.h"

err_t sys_sem_new(sys_sem_t* sem, u8_t count)
{
	return 0;
}

void sys_sem_free(sys_sem_t* sem)
{

}

void sys_sem_signal(sys_sem_t* sem)
{

}

u32_t sys_arch_sem_wait(sys_sem_t* sem, u32_t timeout)
{
	return 0;
}

err_t sys_mbox_new(mbox_t* mbox, int size)
{
	return 0;
}

void sys_mbox_free(sys_mbox_t* mbox)
{

}

void sys_mbox_post(sys_mbox_t* mbox, void* msg)
{

}

u32_t sys_arch_mbox_fetch(sys_mbox_t* mbox, void** msg, u32_t timeout)
{
	return 0;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t* mbox, void** msg)
{
	return 0;
}

err_t sys_mbox_trypost(sys_mbox_t* mbox, void* msg)
{

}

sys_thread_t sys_thread_new(char* name, void (*thread)(void* arg), void* arg, int stacksize, int prio)
{
	return 0;
}

void sys_init(void)
{

}