#include "arch/sys_arch.h"
#include "arch/cc.h"
#include "lwip/err.h"

#include <net/netosl.hpp>

void lwip_socket_init()
{
	KeCPrintf("Sockets not compiled. When they are, remove this function.\n");
}

void tcpip_callback_with_block()
{
	// TYPE SIGNATURE UNKNOWN!!
	KeCPanic("tcpip_callback_with_block");
}

err_t sys_sem_new(sys_sem_t* sem, u8_t count)
{
	KeNetCreateSemaphore((size_t*) sem, count);
	return ERR_OK;
}

void sys_sem_free(sys_sem_t* sem)
{
	KeNetFreeSemaphore((size_t*) sem);
}

void sys_sem_signal(sys_sem_t* sem)
{
	KeNetSignalSemaphore((size_t*) sem);
}

u32_t sys_arch_sem_wait(sys_sem_t* sem, u32_t timeout)
{
	return KeNetWaitSemaphore((size_t*) sem, timeout);
}

err_t sys_mbox_new(sys_mbox_t* mbox, int size)
{
	KeCPanic("sys_mbox_new");
	return 0;
}

void sys_mbox_free(sys_mbox_t* mbox)
{
	KeCPanic("sys_mbox_free");
}

void sys_mbox_post(sys_mbox_t* mbox, void* msg)
{
	KeCPanic("sys_mbox_post");
}

u32_t sys_arch_mbox_fetch(sys_mbox_t* mbox, void** msg, u32_t timeout)
{
	KeCPanic("sys_arch_mbox_fetch");
	return 0;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t* mbox, void** msg)
{
	KeCPanic("sys_arch_mbox_tryfetch");
	return 0;
}

err_t sys_mbox_trypost(sys_mbox_t* mbox, void* msg)
{
	KeCPanic("sys_mbox_trypost");
}

sys_thread_t sys_thread_new(char* name, void (*thread)(void*), void* arg, int stacksize, int prio)
{
	KeNetCreateThread(thread, arg);
	return 0;
}

void sys_init(void)
{

}
