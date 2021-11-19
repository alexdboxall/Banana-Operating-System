#pragma once

#include <stdint.h>
#include <stddef.h>

extern size_t HalPageGlobalFlag;
extern size_t HalPageWriteCombiningFlag;

void HalInitialise();
void HalInitialiseCoprocessor();
void HalReceivedNMI();
void HalEnableNMI();
void HalDisableNMI();
bool HalGetNMIState();
void HalDetectFeatures();
uint8_t* HalFindRSDP();
bool HalHandleOpcodeFault(void* regs, void* ctxt);
bool HalHandleGeneralProtectionFault(void* regs, void* ctxt);
bool HalHandlePageFault(void* regs, void* ctxt);
void HalDisplayDebugInfo(void* r);
void HalPanic(const char* message);
uint64_t HalQueryPerformanceCounter();
void HalMakeBeep(int hertz);
uint32_t HalGetRand();
void HalEndOfInterrupt(int irq);
void HalRestart();
void HalShutdown();
void HalSleep();
void HalConsoleScroll(int fg, int bg);
void HalConsoleWriteCharacter(char c, int fg, int bg, int x, int y);
void HalConsoleCursorUpdate(int x, int y);
void HalSystemIdle();
void* HalAllocateCoprocessorState();
void HalSaveCoprocessor(void* buffer);
void HalFlushTLB();
void HalLoadCoprocessor(void* buffer);
void HalEnableInterrupts();
void HalDisableInterrupts();
void HalStallProcessor();

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);
void insb(uint16_t port, void* addr, size_t cnt);
void insw(uint16_t port, void* addr, size_t cnt);
void insl(uint16_t port, void* addr, size_t cnt);
void outb(uint16_t port, uint8_t  val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, uint32_t val);
void outsb(uint16_t port, const void* addr, size_t cnt);
void outsw(uint16_t port, const void* addr, size_t cnt);
void outsl(uint16_t port, const void* addr, size_t cnt);