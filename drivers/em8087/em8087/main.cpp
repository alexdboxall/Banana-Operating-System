#include <stdint.h>

void begin();
void start()
{
	begin();
}

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

typedef struct Float80
{
	uint64_t fraction;
	uint16_t exponent : 15;
    uint16_t  : 1;
    bool sign;

} Float80;

int64_t floatToLong(Float80 flt)
{
    return 0LL;
}

Float80 longToFloat(int64_t significand)
{
    Float80 out;

    // Only support 0
    if (significand == 0LL) {
        out.sign = 0;
        out.exponent = 0;
        out.fraction = 0;
        return out;
    }

    if (significand < 0) {
        out.sign = 1;
        significand = -significand;
    } else {
        out.sign = 0;
    }

    int shifts = 0;

    while ((significand & (1LL << 63LL)) == 0) {
        significand <<= 1;
        shifts++;
    }

    out.fraction = significand;
    out.exponent = 16383 + 63 - shifts;

    return out;
}

Float80 get0()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0;
    out.exponent = 0;
    return out;
}

Float80 get1()
{
    return longToFloat(0);
}

Float80 fpuStack[8];
int fpuSP = 0;

void fpuPush(Float80 flt)
{
    fpuStack[fpuSP++] = flt;
    if (fpuSP == 8) {
        panic("FPU OVERFLOW.");
    }
}

Float80 fpuPop()
{
    if (fpuSP == 0) {
        panic("FPU UNDERFLOW.");
    }
    return fpuStack[--fpuSP];
}

bool x87Handler(regs* r)
{
	uint8_t* eip = (uint8_t*) r->eip;
	kprintf("x87: %X %X %X\n", *eip, *(eip + 1), *(eip + 2));

    if (eip[0] == 0xD9) {
        switch (eip[1]) { 
        case 0xE8:  //D9 E8     FLD1
            fpuPush(get1());
            return true;
        case 0xE9:  //D9 E9     FLDL2T
            return false;
        case 0xEA:  //D9 EA     FLDL2E
            return false;
        case 0xEB:  //D9 EB     FLDPI
            return false;
        case 0xEC:  //D9 EC     FLDLG2
            return false;
        case 0xED:  //D9 ED     FLDLN2
            return false;
        case 0xEE:  //D9 EE     FLD0
            fpuPush(get0());
            return true;
        default:
            break;
        }
    }

	return false;
}

void begin()
{
	extern bool (*x87FaultIntercept)(regs * r);
	x87FaultIntercept = x87Handler;


}

