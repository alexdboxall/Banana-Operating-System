#pragma once

#include <stdint.h>
#include <stddef.h>

#define INLINE inline __attribute__((always_inline)) 

/// <summary>
/// Initialises the HAL. Should only be called once, and is internal to the kernel.
/// </summary>
void HalInitialise();

/// <summary>
/// Initialies the floating point coprocessor if it exists. Should only be called once, and is internal to the kernel.
/// </summary>
void HalInitialiseCoprocessor();

/// <summary>
/// Causes a stop error, for when the system detects an unrecoverable situation which requires a complete lockup of the system.
/// </summary>
/// <param name="message">The error message to display to the user.</param>
void HalPanic(const char* message);

/// <summary>
/// Returns the value of performance counter (e.g. the timestamp counter) if the system has one. If the system has one,
/// all values are expected to be larger than the previously returned value. If the system does not have one, the function
/// shall either return zero or provide a estimate (in which case all values should be larger than the previously returned value).
/// </summary>
/// <returns>The current value of the performance counter.</returns>
uint64_t HalQueryPerformanceCounter();

/// <summary>
/// Causes the speaker to produce a tone at the requested frequency, until this function is called with a frequency of zero.
/// </summary>
/// <param name="hertz">The frequency to produce, or zero to stop.</param>
void HalMakeBeep(int hertz);

/// <summary>
/// Returns a 32-bit pseudo-random value. The seed is calculated using a hardware RNG generator if available.
/// </summary>
/// <returns>A 32-bit pseudo-random value.</returns>
uint32_t HalGetRand();
void HalEndOfInterrupt(int);
void HalRestart();
void HalShutdown();
void HalSleep();
void HalConsoleScroll(int fg, int bg);
void HalConsoleWriteCharacter(char c, int fg, int bg, int x, int y);
void HalConsoleCursorUpdate(int x, int y);
void HalSystemIdle();

INLINE void* HalAllocateCoprocessorState()
{
	return nullptr;
}

INLINE void HalSaveCoprocessor(void*)
{

}

INLINE void HalLoadCoprocessor(void*)
{
	size_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r"(cr0));
	cr0 |= 8;
	asm volatile ("mov %0, %%cr0" :: "r"(cr0));
}

INLINE void HalEnableInterrupts()
{
	asm volatile ("sti");
}

INLINE void HalDisableInterrupts()
{
	asm volatile ("cli");
}

INLINE void HalStallProcessor()
{
	asm volatile ("hlt");
}

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