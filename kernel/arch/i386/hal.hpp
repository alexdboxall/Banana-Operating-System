#include <stdint.h>
#include <krnl/panic.hpp>

#define INLINE inline __attribute__((always_inline)) 

namespace Hal
{
	void initialise();

	void initialiseCoprocessor();
	void* allocateCoprocessorState();
	void saveCoprocessor(void*);
	void loadCoprocessor(void*);

	INLINE void panic(const char* message)
	{
		Krnl::panic(message);
	}

	INLINE void enableIRQs()
	{
		asm volatile ("sti");
	}

	INLINE void disableIRQs()
	{
		asm volatile ("cli");
	}

	INLINE void pushIRQs(int* ptr)
	{
		panic("[i386] pushIRQs not implemented");
	}

	INLINE void popIRQs(int* ptr)
	{
		panic("[i386] popIRQs not implemented");
	}

	INLINE bool areIRQsOn()
	{
		unsigned long flags;
		asm volatile ("pushf\n\t"
					  "pop %0"
					  : "=g"(flags));
		return flags & (1 << 9);
	}

	INLINE uint64_t readTimestampCounter()
	{
		extern uint64_t(*_i386_HAL_tscFunction)();
		return _i386_HAL_tscFunction();
	}

	void makeBeep(int hertz);

	INLINE void stopBeep()
	{
		makeBeep(0);
	}

	uint32_t getRand();

	void endOfInterrupt();

	void restart();
	void shutdown();
	void sleep();

	INLINE void stallProcessor()
	{
		asm volatile ("hlt");
	}

	INLINE void systemIdle()
	{
		Hal::stallProcessor();
	}
};

INLINE uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

INLINE uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("inw %1, %w0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

INLINE uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile ("inl %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

INLINE void insb(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insb" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

INLINE void insw(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insw" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

INLINE void insl(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insl" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

INLINE void outb(uint16_t port, uint8_t  val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

INLINE void outw(uint16_t port, uint16_t val)
{
	asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

INLINE void outl(uint16_t port, uint32_t val)
{
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port));
}

INLINE void outsb(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsb" : "+S" (addr), "+c" (cnt) : "d" (port));
}

INLINE void outsw(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsw" : "+S" (addr), "+c" (cnt) : "d" (port));
}

INLINE void outsl(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsl" : "+S" (addr), "+c" (cnt) : "d" (port));
}