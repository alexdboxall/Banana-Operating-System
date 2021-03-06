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

//must be even, and cannot be >= 64
#define FRACTION_LENGTH 62ULL
#define EXPONENT_BIAS   16383

typedef struct _Float80
{
    uint64_t fraction;
    uint16_t exponent;
    bool sign;

} Float80;


typedef struct _FPUState
{
    union
    {
        struct
        {
            uint16_t invalidOperation : 1;
            uint16_t denormalisedOperand : 1;
            uint16_t zeroDivide : 1;
            uint16_t overflow : 1;
            uint16_t underflow : 1;
            uint16_t precision : 1;
            uint16_t stackFault : 1;
            uint16_t errSummaryStatus : 1;
            uint16_t c0 : 1;
            uint16_t c1 : 1;
            uint16_t c2 : 1;
            uint16_t stackTop : 3;
            uint16_t c3 : 1;
            uint16_t fpuBusy : 1;
        };

        uint16_t status;
    };

    Float80 regs[8];
    int valuesOnStack = 0;

} FPUState;

FPUState fpuState;

int64_t fpuFloatToLong(Float80 flt)
{
    int exponent = flt.exponent - EXPONENT_BIAS;
    if (exponent > FRACTION_LENGTH + 1) {
        //overflow
        return 0;
    }
    if (exponent < 0) {
        //round to zero
        return 0;
    }
    if (exponent > FRACTION_LENGTH) {
        return 0;
    }
    int64_t res = flt.fraction >> (FRACTION_LENGTH - exponent);
    if (flt.sign) {
        res = -res;
    }
    return res;
}

Float80 fpuReciprocal(Float80 x);

Float80 fpuLongToFloat(int64_t signedSignificand)
{
    Float80 out;

    if (signedSignificand == 0) {
        out.sign = 0;
        out.exponent = 0;
        out.fraction = 0;
        return out;
    }

    if (signedSignificand < 0) {
        out.sign = 1;
        signedSignificand = -signedSignificand;
    } else {
        out.sign = 0;
    }

    uint64_t significand = signedSignificand;

    int shifts = 0;

    while ((significand & (1ULL << (FRACTION_LENGTH - 1))) == 0) {
        significand <<= 1;
        shifts++;
    }

    out.fraction = significand;
    out.exponent = FRACTION_LENGTH - shifts + EXPONENT_BIAS;

    return out;
}

Float80 fpuGet0()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0;
    out.exponent = 16383;
    return out;
}

Float80 fpuGet1()
{
    Float80 out;
    out.sign = 0;
    out.fraction = (1ULL << (FRACTION_LENGTH - 1));
    out.exponent = 16383;
    return out;
}

Float80 fpuGetPi()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0x3243F6A8885A308CULL;
    out.exponent = 16385;
    return out;
}

Float80 fpuGetLog2E()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0x2E2A8ECA5705FC1CULL;
    out.exponent = 16384;
    return out;
}

Float80 fpuGetLogE2()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0x2C5C85FDF473DE68ULL;
    out.exponent = 16383;
    return out;
}

Float80 fpuGetLog210()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0x35269E12F346E2BEULL;
    out.exponent = 16385;
    return out;
}

Float80 fpuGetLog102()
{
    Float80 out;
    out.sign = 0;
    out.fraction = 0x268826A13EF3FDE6ULL;
    out.exponent = 16382;
    return out;
}

bool fpuIsSecondLarger(Float80 x, Float80 y)
{
    if (y.exponent > x.exponent) return true;
    else if (y.exponent < x.exponent) return false;
    else {
        return y.fraction > x.fraction;
    }
}

bool fpuAreEqual(Float80 x, Float80 y)
{
    return (x.exponent == y.exponent && x.sign == y.sign && x.fraction == y.fraction);
}

Float80 fpuNormalise(Float80 flt)
{
    //ensure the top bit of the fraction is set
    while (!(flt.fraction & (1ULL << (FRACTION_LENGTH - 1)))) {
        //check for zero
        if (flt.fraction == 0) {
            flt.exponent = 0;
            return flt;
        }

        flt.fraction <<= 1;
        flt.exponent -= 1;
    }

    return flt;
}

Float80 fpuAdd(Float80 x, Float80 y)
{
    if (fpuIsSecondLarger(x, y)) {
        Float80 z = x;
        x = y;
        y = z;
    }

    Float80 sum;

    int expoDifference = x.exponent - y.exponent;

    y.fraction >>= expoDifference;
    y.exponent += expoDifference;

    sum.exponent = x.exponent;

    if (x.sign == y.sign) {
        sum.sign = x.sign;
        sum.fraction = x.fraction + y.fraction;

    } else if (y.sign) {
        if (y.fraction > x.fraction) {
            sum.fraction = y.fraction - x.fraction;
            sum.sign = 1;
        } else {
            sum.fraction = x.fraction - y.fraction;
            sum.sign = 0;
        }

    } else if (x.sign) {
        if (x.fraction > y.fraction) {
            sum.fraction = x.fraction - y.fraction;
            sum.sign = 1;
        } else {
            sum.fraction = y.fraction - x.fraction;
            sum.sign = 0;
        }
    }

    return fpuNormalise(sum);
}

Float80 fpuAbs(Float80 x)
{
    x.sign = 0;
    return x;
}

Float80 fpuSub(Float80 x, Float80 y)
{
    y.sign ^= 1;
    return fpuAdd(x, y);
}

Float80 fpuReverseSub(Float80 x, Float80 y)
{
    y.sign ^= 1;
    return fpuAdd(y, x);
}

Float80 fpuMultiply(Float80 x, Float80 y)
{
    Float80 product;

    x.fraction >>= FRACTION_LENGTH / 2;
    y.fraction >>= FRACTION_LENGTH / 2;

    product.sign = x.sign ^ y.sign;
    product.exponent = x.exponent + y.exponent - EXPONENT_BIAS;
    product.fraction = (x.fraction * y.fraction);

    return fpuNormalise(product);
}

uint64_t fpuMantissaDivision(uint64_t dividend, uint64_t divisor)
{
    uint64_t quotient = 0;
    uint64_t remainder = 0;

    int outputBits = -1;

    for (int i = FRACTION_LENGTH - 1; outputBits; --i) {
        remainder <<= 1;
        if (outputBits == -1) {
            remainder |= (dividend >> i) & 1;
        }
        if (remainder >= divisor) {
            remainder -= divisor;
            if (outputBits == -1) {
                quotient |= 1ULL << (FRACTION_LENGTH - 1ULL);
                outputBits = FRACTION_LENGTH - 1;
            } else {
                quotient |= 1ULL << outputBits;
            }
        }

        if (outputBits >= 0) {
            outputBits--;
        }
    }

    return quotient;
}

Float80 fpuDivide(Float80 x, Float80 y)
{
    Float80 product;

    product.sign = x.sign ^ y.sign;
    product.fraction = fpuMantissaDivision(x.fraction, y.fraction);

    if (y.fraction > x.fraction) {
        product.exponent = x.exponent - y.exponent + EXPONENT_BIAS + (x.fraction >= y.fraction) + 1;

    } else {
        product.exponent = x.exponent - y.exponent + EXPONENT_BIAS + (x.fraction >= y.fraction);
    }

    return fpuNormalise(product);
}

Float80 fpuReciprocal(Float80 x)
{
    return fpuDivide(fpuGet1(), x);
}

Float80 fpuSquare(Float80 flt)
{
    return fpuMultiply(flt, flt);
}

Float80 fpuInverseSqrt(Float80 flt)
{
    Float80 threeHalves = fpuLongToFloat(3);
    threeHalves.exponent--;

    Float80 guess = flt;
    guess.exponent = -((guess.exponent - EXPONENT_BIAS) >> 1) + EXPONENT_BIAS;
    flt.exponent--;

    for (int i = 0; i < 7; ++i) {
        guess = fpuMultiply(guess, fpuSub(threeHalves, fpuMultiply(fpuSquare(guess), flt)));
    }

    return guess;
}

Float80 fpuSqrt(Float80 flt)
{
    return fpuDivide(fpuGet1(), fpuInverseSqrt(flt));
}

Float80 fpuGetReg(int num)
{
    return fpuState.regs[(fpuState.stackTop + num) % 8];
}


uint32_t fpuInternalTo32(Float80 flt)
{
    if (flt.exponent - EXPONENT_BIAS > 127) {
        flt.exponent = 127;
        fpuState.overflow = 1;
    }
    uint32_t out = 0;
    if (flt.sign) {
        out |= (1ULL << 31ULL);
    }
    out |= (flt.fraction & ~(1ULL << (FRACTION_LENGTH - 1))) >> (FRACTION_LENGTH - 24);
    out |= ((uint32_t) ((flt.exponent - EXPONENT_BIAS + 126))) << 23ULL;
    return out;
}

uint64_t fpuInternalTo64(Float80 flt)
{
    if (flt.exponent - EXPONENT_BIAS > 1023) {
        flt.exponent = 1023;
        fpuState.overflow = 1;
    }
    uint64_t out = 0;
    if (flt.sign) {
        out |= (1ULL << 63ULL);
    }
    out |= (flt.fraction & ~(1ULL << (FRACTION_LENGTH - 1))) >> (FRACTION_LENGTH - 53);
    out |= ((uint64_t)((flt.exponent - EXPONENT_BIAS + 1022))) << 52ULL;
    return out;
}

void fpuPush(Float80 flt)
{
    fpuState.stackTop = (fpuState.stackTop + 7) % 8;
    fpuState.regs[fpuState.stackTop] = flt;
    if (fpuState.valuesOnStack == 8) {
        fpuState.stackFault = 1;
    } else {
        fpuState.valuesOnStack++;
    }
}

Float80 fpuPop()
{
    Float80 v = fpuState.regs[fpuState.stackTop];
    fpuState.stackTop = (fpuState.stackTop + 1) % 8;
    if (fpuState.valuesOnStack) {
        --fpuState.valuesOnStack;
    } else {
        fpuState.stackFault = 1;
    }
    return v;
}

bool x87Handler(regs* r)
{
	uint8_t* eip = (uint8_t*) r->eip;
    uint8_t middleDigit = (eip[1] >> 3) & 7;
    uint8_t mod = (eip[1] >> 6) & 3;
    uint8_t rm = (eip[1] >> 0) & 7;

    //mod 1      01
    //mid 3     011
    //r/m 4     100
    uint8_t* ptr = 0;
    bool registerOnly = false;
    bool ptrIllegal = false;

    int instrLen = 2;

    if (mod != 3 && rm != 4 && !(mod == 0 && rm == 5)) {
        //[reg]
        //[reg + disp8]
        //[reg + disp32]
        if (rm == 0) ptr = (uint8_t*) r->eax;
        if (rm == 1) ptr = (uint8_t*) r->ecx;
        if (rm == 2) ptr = (uint8_t*) r->edx;
        if (rm == 3) ptr = (uint8_t*) r->ebx;
        if (rm == 5) ptr = (uint8_t*) r->ebp;
        if (rm == 6) ptr = (uint8_t*) r->esi;
        if (rm == 7) ptr = (uint8_t*) r->edi;

        if (mod == 1) {
            ptr += *((int8_t*) (eip + 2));
            instrLen += 1;

        } else if (mod == 2) {
            ptr += *((int32_t*) (eip + 2));
            instrLen += 4;
        }

    } else if (mod == 0 && rm == 5) {
        //32 bit displacement
        ptr = (uint8_t*) (*((uint32_t*) (eip + 2)));
        instrLen += 4;

    } else if (mod == 3) {
        //register only mode
        registerOnly = true;

    } else if (rm == 4) {
        //SIB mode
        uint8_t sib = eip[2];
        uint8_t scale = (sib >> 6) & 3;
        uint8_t index = (sib >> 3) & 7;
        uint8_t base = (sib >> 0) & 7;
        instrLen += 1;

        kprintf("SIB. mod = %d, rm = %d, scale = %d, index = %d, base = %d\n", mod, rm, scale, index, base);

        uint32_t actBase;
        uint32_t actIndex;
        
        if (base == 0) actBase = r->eax;
        else if (base == 1) actBase = r->ecx;
        else if (base == 2) actBase = r->edx;
        else if (base == 3) actBase = r->ebx;
        else if (base == 4) actBase = r->useresp;
        else if (base == 5) actBase = r->ebp;
        else if (base == 6) actBase = r->esi;
        else if (base == 7) actBase = r->edi;

        if (index == 0) actIndex = r->eax;
        else if (index == 1) actIndex = r->ecx;
        else if (index == 2) actIndex = r->edx;
        else if (index == 3) actIndex = r->ebx;
        else if (index == 4) actIndex = 0;
        else if (index == 5) actIndex = r->ebp;
        else if (index == 6) actIndex = r->esi;
        else if (index == 7) actIndex = r->edi;

        if (mod == 0 && base == 5) {
            //displacement only
            ptr = (uint8_t*) (actIndex << scale);
            ptr += *((int32_t*) (eip + 3));
            instrLen += 4;

        } else if (mod == 0) {
            //SIB
            ptr = (uint8_t*) (actBase + actIndex << scale);

        } else if (mod == 1) {
            //SIB + disp8
            ptr = (uint8_t*) (actBase + actIndex << scale);
            ptr += *((int8_t*) (eip + 3));
            instrLen += 1;

        } else if (mod == 2) {
            //SIB + disp32
            ptr = (uint8_t*) (actBase + actIndex << scale);
            ptr += *((int32_t*) (eip + 3));
            instrLen += 4;
        }
    }

    kprintf("x87 handler called with faulting EIP of 0x%X\n", eip);
	kprintf("x87: %X %X %X %X\n", *eip, *(eip + 1), *(eip + 2), *(eip + 3));

    kprintf("decoded address = 0x%X\n", ptr);

    if (eip[0] == 0xD9) {
        switch (eip[1]) { 
        case 0xE8:  //D9 E8     FLD1
            fpuPush(fpuGet1());
            r->eip += 2;
            return true;
        case 0xE9:  //D9 E9     FLDL2T
            fpuPush(fpuGetLog210());
            r->eip += 2;
            return true;
        case 0xEA:  //D9 EA     FLDL2E
            fpuPush(fpuGetLog2E());
            r->eip += 2;
            return true;
        case 0xEB:  //D9 EB     FLDPI
            fpuPush(fpuGetPi());
            r->eip += 2;
            return true;
        case 0xEC:  //D9 EC     FLDLG2
            fpuPush(fpuGetLog102());
            r->eip += 2;
            return true;
        case 0xED:  //D9 ED     FLDLN2
            fpuPush(fpuGetLogE2());
            r->eip += 2;
            return true;
        case 0xEE:  //D9 EE     FLD0
            fpuPush(fpuGet0());
            r->eip += 2;
            return true;
        default:
            break;
        }

    } else if (eip[0] == 0xDD && middleDigit == 3) {
        if (registerOnly) panic("em8087 not implemented (1)");

        uint64_t* p = (uint64_t*) ptr;
        kprintf("about to write.\n");
        *p = fpuInternalTo64(fpuGetReg(0));
        kprintf("written.\n");
        r->eip += instrLen;
        return true;
    }

	return false;
}

void begin()
{
	extern bool (*x87FaultIntercept)(regs * r);
	x87FaultIntercept = x87Handler;


}

