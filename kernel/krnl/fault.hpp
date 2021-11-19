
#pragma once

struct regs;

extern void (*keInterruptHandlers[256][4])(regs* r, void* context);
extern void* keInterruptContexts[256][4];

extern bool (*gpFaultIntercept)(void* r);

void KeSetupInterrupts();

void KeDisplayProgramFault(const char* text);

void KeGeneralProtectionFault(void* r, void* context);
void KePageFault(void* r, void* context);
void KeNonMaskableInterrupt(void* r, void* context);
void KeOtherFault(void* r, void* context);
void KeOpcodeFault(void* r, void* context);
void KeDoubleFault(void* r, void* context);