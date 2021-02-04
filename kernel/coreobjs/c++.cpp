#include "core/common.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;


//__cxa_atexit is called on all global object's destructors
//if we don't care about global object destructors (it's a kernel, we don't need to free memory when we shutdown)
//we can just ignore the calls

//__cxa_finalize calls the destructors stored by __cxa_atexit

//void* __dso_handle;

extern "C" int __cxa_atexit(void (*destructor) (void*), void* arg, void* dso)
{
	//This function should save all three parameters and if successful return zero, on failure non-zero. 
	//When your kernel exits you should call __cxa_finalize(0). According to the ABI specification, calling 
	//this with 0 as the parameter instead of the address of a function (to be called and removed from the list)
	//causes all destructors in the list to be called and removed from the list. 

	return 0;
}

extern "C" void __cxa_finalize(void* f)
{

}


extern "C" void __stack_chk_fail(void)
{

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

	kprintf("'0x%X'\n", __builtin_return_address(0));
	kprintf("'0x%X'\n", __builtin_return_address(1));
	kprintf("'0x%X'\n", __builtin_return_address(2));
	kprintf("'0x%X'\n", __builtin_return_address(3));

	panic("Stack smashing detected");

#pragma GCC diagnostic pop

}

extern "C" void __cxa_pure_virtual()
{
	panic("__cxa_pure_virtual");
}

void* operator new(size_t size)
{
	return malloc(size);
}

void* operator new[](size_t size)
{
	return malloc(size);
}

void operator delete(void* p)
{
	rfree(p);
}

void operator delete(void* p, long unsigned int)
{
	rfree(p);
}

void operator delete[](void* p)
{
	rfree(p);
}

void operator delete[](void* p, long unsigned int)
{
	rfree(p);
}

inline void* operator new(size_t, void* p)     throw() { return p; }
inline void* operator new[](size_t, void* p)   throw() { return p; }
inline void  operator delete  (void*, void*) throw() {};
inline void  operator delete[](void*, void*) throw() {};