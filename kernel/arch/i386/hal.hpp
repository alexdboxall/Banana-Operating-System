#include <stdint.h>
#include <krnl/panic.hpp>

#define INLINE inline __attribute__((always_inline)) 

namespace Hal
{
	void initialise();

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