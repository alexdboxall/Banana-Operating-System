#pragma once

#include <stdint.h>
#include <stddef.h>

#define INLINEX inline __attribute__((always_inline)) 

/// <summary>
/// Initialises the HAL. Should only be called once, and is internal to the kernel.
/// </summary>
void HalInitialise();

/// <summary>
/// Initialies the floating point coprocessor if it exists. Should only be called once, and is internal to the kernel.
/// </summary>
void HalInitialiseCoprocessor();

/// <summary>
/// Called when the system receives an NMI.
/// </summary>
void HalReceivedNMI();


void HalHandleOpcodeFault(void* regs, void* ctxt);
void HalDisplayDebugInfo(void* r);

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
/// Returns a 32-bit random value using a hardware RNG generator if available, else it should return zero.
/// </summary>
/// <returns>A 32-bit random value, or zero if hardware RNG is not supported.</returns>
uint32_t HalGetRand();

/// <summary>
/// Sends an acknowledgement message to the interrupt controller that the interrupt has been handled. Needs to be called 
/// after every interrupt.
/// </summary>
/// <param name="irq">The interrupt number to acknowledge.</param>
void HalEndOfInterrupt(int irq);

/// <summary>
/// Reboots the system immediately.
/// </summary>
void HalRestart();

/// <summary>
/// Performs a system shutdown immediately if supported, otherwise displays a message to the user telling them it is okay to turn off their computer.
/// </summary>
void HalShutdown();

/// <summary>
/// Puts the system to sleep immediately if supported, otherwise does nothing.
/// </summary>
void HalSleep();

/// <summary>
/// Scrolls the console by one row, discarding the topmost row's contents. The bottommost row is set to the colours specified as blank characters.
/// </summary>
/// <param name="fg">The foreground colour for the bottommost row (from 0-15, CGA palette).</param>
/// <param name="bg">The background colour for the bottommost row (from 0-15, CGA palette).</param>
void HalConsoleScroll(int fg, int bg);

/// <summary>
/// Writes a charcater to the console.
/// </summary>
/// <param name="c">The character.</param>
/// <param name="fg">The foreground colour (from 0-15, CGA palette).</param>
/// <param name="bg">The backgronud colour (from 0-15, CGA palette).</param>
/// <param name="x">The X position to write the character (from 0-79).</param>
/// <param name="y">The Y position to write the character (from 0-24).</param>
void HalConsoleWriteCharacter(char c, int fg, int bg, int x, int y);

/// <summary>
/// Sets the position of the cursor on the console.
/// </summary>
/// <param name="x">The X position (from 0-79).</param>
/// <param name="y">The Y position (from 0-24).</param>
void HalConsoleCursorUpdate(int x, int y);

/// <summary>
/// Called when the system is idle (not running any tasks). It may put the system into a low-power mode until the next interrupt, perform background caching / cleaning work, etc.
/// </summary>
void HalSystemIdle();

/// <summary>
/// Allocates a buffer which stores the coprocessor state. This buffer is passed into HalSaveCoprocessor and HalLoadCoprocessor.
/// </summary>
/// <returns></returns>
INLINEX void* HalAllocateCoprocessorState()
{
	return nullptr;
}

/// <summary>
/// Saves the coprocessor state to a buffer previously allocated with HalAllocateCoprocessorState.
/// </summary>
/// <param name="buffer">The buffer to save the data to.</param>
INLINEX void HalSaveCoprocessor(void* buffer)
{

}


INLINEX void HalFlushTLB()
{
	size_t cr3;
	asm volatile ("mov %%cr3, %0" : "=r"(cr3));
	asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

/// <summary>
/// Restores the coprocessor state from a buffer previously allocated with HalAllocateCoprocessorState.
/// </summary>
/// <param name="buffer">The buffer to load the data from.</param>
INLINEX void HalLoadCoprocessor(void* buffer)
{
	size_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r"(cr0));
	cr0 |= 8;
	asm volatile ("mov %0, %%cr0" :: "r"(cr0));
}

/// <summary>
/// Enables hardware interrupts.
/// </summary>
INLINEX void HalEnableInterrupts()
{
	asm volatile ("sti");
}

/// <summary>
/// Disables hardware interrupts.
/// </summary>
INLINEX void HalDisableInterrupts()
{
	asm volatile ("cli");
}

/// <summary>
/// Waits until the next interrupt.
/// </summary>
INLINEX void HalStallProcessor()
{
	asm volatile ("hlt");
}

/// <summary>
/// Reads from an 8 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <returns>The data received.</returns>
INLINEX uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

/// <summary>
/// Reads from a 16 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <returns>The data received.</returns>
INLINEX uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("inw %1, %w0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

/// <summary>
/// Reads from a 32 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <returns>The data received.</returns>
INLINEX uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile ("inl %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

/// <summary>
/// Reads from an 8 bit I/O port multiple times, storing the data in a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 8 bit values to read from the port.</param>
INLINEX void insb(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insb" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

/// <summary>
/// Reads from a 16 bit I/O port multiple times, storing the data in a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 16 bit values to read from the port.</param>
INLINEX void insw(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insw" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

/// <summary>
/// Reads from a 32 bit I/O port multiple times, storing the data in a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 32 bit values to read from the port.</param>
INLINEX void insl(uint16_t port, void* addr, size_t cnt)
{
	asm volatile ("rep insl" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}

/// <summary>
/// Writes data to an 8 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="val">The value to write.</param>
INLINEX void outb(uint16_t port, uint8_t  val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

/// <summary>
/// Writes data to a 16 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="val">The value to write.</param>
INLINEX void outw(uint16_t port, uint16_t val)
{
	asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

/// <summary>
/// Writes data to a 32 bit I/O port.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="val">The value to write.</param>
INLINEX void outl(uint16_t port, uint32_t val)
{
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port));
}

/// <summary>
/// Writes from an 8 bit I/O port multiple times, using data from a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 8 bit values to write to the port.</param>
INLINEX void outsb(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsb" : "+S" (addr), "+c" (cnt) : "d" (port));
}

/// <summary>
/// Writes from a 16 bit I/O port multiple times, using data from a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 16 bit values to write to the port.</param>
INLINEX void outsw(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsw" : "+S" (addr), "+c" (cnt) : "d" (port));
}

/// <summary>
/// Writes from a 32 bit I/O port multiple times, using data from a buffer.
/// </summary>
/// <param name="port">The port number.</param>
/// <param name="addr">The buffer address.</param>
/// <param name="cnt">The number of 32 bit values to write to the port.</param>
INLINEX void outsl(uint16_t port, const void* addr, size_t cnt)
{
	asm volatile ("rep outsl" : "+S" (addr), "+c" (cnt) : "d" (port));
}