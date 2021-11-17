
void KeDisplayProgramFault(const char* text);
extern bool (*gpFaultIntercept)(void* r);

void KeGeneralProtectionFault(void* r, void* context);
void KePageFault(void* r, void* context);
void KeNonMaskableInterrupt(void* r, void* context);
void KeOtherFault(void* r, void* context);
void KeOpcodeFault(void* r, void* context);
void KeDoubleFault(void* r, void* context);