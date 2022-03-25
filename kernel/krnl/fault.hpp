
#pragma once

#define RETURN_CODE_ON_OPCODE_FAULT					124
#define RETURN_CODE_ON_OTHER_FAULT					125
#define RETURN_CODE_ON_GENERAL_PROTECTION_FAULT		126
#define RETURN_CODE_ON_PAGE_FAULT					127

struct regs;

extern bool (*gpFaultIntercept)(void* r);

void KePageFault(void* r, void* context);
void KeOtherFault(void* r, void* context);
void KeOpcodeFault(void* r, void* context);
void KeDoubleFault(void* r, void* context);
void KeNonMaskableInterrupt(void* r, void* context); 
void KeGeneralProtectionFault(void* r, void* context);
