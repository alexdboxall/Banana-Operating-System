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

    union
    {
        struct
        {
            uint16_t maskInvalidOperation : 1;
            uint16_t maskDenormalisedOperand : 1;
            uint16_t maskZeroDivide : 1;
            uint16_t maskOverflow : 1;
            uint16_t maskUnderflow : 1;
            uint16_t maskPrecision : 1;
            uint16_t : 2;
            uint16_t precisionControl : 2;
            uint16_t roundingControl : 2;
            uint16_t infinityControl : 1;
            uint16_t : 3;
        };

        uint16_t control;
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

Float80 fpuULongToFloat(uint64_t significand)
{
    Float80 out;

    if (significand == 0) {
        out.sign = 0;
        out.exponent = 0;
        out.fraction = 0;
        return out;
    }

    out.sign = 0;

    int shifts = 0;
    int extraShifts = 0;
    while (significand >> 62) {
        extraShifts++;
        significand >>= 1;
    }

    while ((significand & (1ULL << (FRACTION_LENGTH - 1))) == 0) {
        significand <<= 1;
        shifts++;
    }

    out.fraction = significand;
    out.exponent = FRACTION_LENGTH - shifts + EXPONENT_BIAS + extraShifts;

    return out;
}

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
    int extraShifts = 0;
    while (significand >> 62) {
        extraShifts++;
        significand >>= 1;
    }

    while ((significand & (1ULL << (FRACTION_LENGTH - 1))) == 0) {
        significand <<= 1;
        shifts++;
    }

    out.fraction = significand;
    out.exponent = FRACTION_LENGTH - shifts + EXPONENT_BIAS + extraShifts;

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

Float80 fpuChs(Float80 x)
{
    x.sign ^= 1;
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
    if (num < 0 || num > 7) {
        panic("em8087 bad reg set");
    }
    return fpuState.regs[(fpuState.stackTop + num) % 8];
}

void fpuSetReg(int num, Float80 flt)
{
    if (num < 0 || num > 7) {
        panic("em8087 bad reg set");
    }
    fpuState.regs[(fpuState.stackTop + num) % 8] = flt;
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

Float80 fpu32ToInternal(uint32_t flt)
{
    Float80 out;
    out.sign = flt >> 31;
    out.fraction = flt & 0x7FFFFFULL;
    out.fraction <<= (FRACTION_LENGTH - 23) - 1;
    out.fraction |= (1ULL << (FRACTION_LENGTH - 1));
    out.exponent = ((flt >> 23) & 0xFF) - 126 + EXPONENT_BIAS;
    return out;
}

Float80 fpu64ToInternal(uint64_t flt)
{
    Float80 out;
    out.sign = flt >> 63;
    out.fraction = flt & 0xFFFFFFFFFFFFFULL;
    out.fraction <<= (FRACTION_LENGTH - 52) - 1;
    out.fraction |= (1ULL << (FRACTION_LENGTH - 1));
    out.exponent = ((flt >> 52) & 0x7FF) - 1022 + EXPONENT_BIAS;
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

void fpuUnorderedCompare(Float80 x, Float80 y)
{
    fpuState.c0 = !fpuAreEqual(x, y) && fpuIsSecondLarger(x, y);
    fpuState.c2 = 0;
    fpuState.c3 = fpuAreEqual(x, y);
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
        case 0xE0:
            fpuSetReg(0, fpuChs(fpuGetReg(0)));
            r->eip += 2;
            return true;
        case 0xE1:              //FABS
            fpuSetReg(0, fpuAbs(fpuGetReg(0)));
            r->eip += 2;
            return true;
        case 0xE8:              //FLD1
            fpuPush(fpuGet1());
            r->eip += 2;
            return true;
        case 0xE9:              //FLD1
            fpuPush(fpuGetLog210());
            r->eip += 2;
            return true;
        case 0xEA:              //FLD1
            fpuPush(fpuGetLog2E());
            r->eip += 2;
            return true;
        case 0xEB:              //FLD1
            fpuPush(fpuGetPi());
            r->eip += 2;
            return true;
        case 0xEC:              //FLD1
            fpuPush(fpuGetLog102());
            r->eip += 2;
            return true;
        case 0xED:              //FLD1
            fpuPush(fpuGetLogE2());
            r->eip += 2;
            return true;
        case 0xEE:              //FLD1
            fpuPush(fpuGet0());
            r->eip += 2;
            return true;
        default:
            break;
        }
    }

    if (eip[0] == 0xD9 && eip[1] >= 0xC0 && eip[1] < 0xC8) {            //FLD
        fpuPush(fpuGetReg(eip[1] - 0xC0));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADD
        fpuSetReg(0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDC && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADD
        fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADDP
        fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FSUB
        fpuSetReg(0, fpuSub(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUBR
        fpuSetReg(0, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDC && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUB
        fpuSetReg(eip[1] - 0xE8, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FSUBRP
        fpuSetReg(eip[1] - 0xE0, fpuSub(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0)));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUBP
        fpuSetReg(eip[1] - 0xE8, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
        fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDC && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
        fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMULP
        fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
        r->eip += 2;
        fpuPop();
        return true;


    } else if (eip[0] == 0xD8 && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVP
        fpuSetReg(0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
        r->eip += 2;
        fpuPop();
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xF8 && eip[1] <= 0xFF) {     //FDIVP
        fpuSetReg(eip[1] - 0xF8, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
        r->eip += 2;
        fpuPop();
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xF8 && eip[1] <= 0xFF) {     //FDIVRP
        fpuSetReg(0, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
        r->eip += 2;
        fpuPop();
        return true;

    } else if (eip[0] == 0xDE && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVRP
        fpuSetReg(eip[1] - 0xF0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
        r->eip += 2;
        fpuPop();
        return true;


    } else if (eip[0] == 0xD9 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FXCH
        Float80 st1 = fpuGetReg(eip[1] - 0xC8);
        fpuSetReg(eip[1] - 0xC8, fpuGetReg(0));
        fpuSetReg(0, st1);
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDD && eip[1] >= 0xD0 && eip[1] <= 0xD7) {     //FST
        fpuSetReg(eip[1] - 0xD0, fpuGetReg(0));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDD && eip[1] >= 0xD8 && eip[1] <= 0xDF) {     //FSTP
        fpuSetReg(eip[1] - 0xD8, fpuGetReg(0));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xD0 && eip[1] <= 0xD7) {     //FCOM
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xD0));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xD8 && eip[1] >= 0xD8 && eip[1] <= 0xDF) {     //FCOMP
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xD8));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDD && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FUCOM
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0));
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDD && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FUCOM
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xE8));
        fpuPop();
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDA && eip[1] == 0xE9) {                      //FUCOMPP
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(1));
        r->eip += 2;
        fpuPop();
        fpuPop();
        return true;

    } else if (eip[0] == 0xDE && eip[1] == 0xD9) {                      //FCOMPP
        fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xD8));
        r->eip += 2;
        fpuPop();
        fpuPop();
        return true;

    } else if (eip[0] == 0xDF && eip[1] == 0xE0) {                      //FNSTSW
        r->eax &= ~0xFFFF;
        r->eax |= fpuState.status;
        r->eip += 2;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 2) {                        //FCOM
        uint64_t* p = (uint64_t*) ptr;
        fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 3) {                        //FCOMP
        uint64_t* p = (uint64_t*) ptr;
        fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
        fpuPop();
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD9 && middleDigit == 7) {                      //FNSTCW
        uint16_t* p = (uint16_t*) ptr;
        *ptr = fpuState.control;
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD9 && middleDigit == 5) {                      //FLDCW
        uint16_t* p = (uint16_t*) ptr;
        fpuState.control = *ptr;
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDB && middleDigit == 2) {                      //FIST
        uint32_t* p = (uint32_t*) ptr;
        *ptr = fpuFloatToLong(fpuGetReg(0));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDB && middleDigit == 3) {                      //FISTP
        uint32_t* p = (uint32_t*) ptr;
        *ptr = fpuFloatToLong(fpuPop());
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDF && middleDigit == 7) {                      //FISTP
        uint64_t* p = (uint64_t*) ptr;
        *ptr = fpuFloatToLong(fpuPop());
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDD && middleDigit == 0) {                    //FLD
        uint64_t* p = (uint64_t*) ptr;
        fpuPush(fpu64ToInternal(*p));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD9 && middleDigit == 0) {                    //FLD
        uint32_t* p = (uint32_t*) ptr;
        fpuPush(fpu32ToInternal(*p));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDD && middleDigit == 2) {                    //FST
        uint64_t* p = (uint64_t*) ptr;
        *p = fpuInternalTo64(fpuGetReg(0));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDD && middleDigit == 3) {                    //FSTP
        uint64_t* p = (uint64_t*) ptr;
        *p = fpuInternalTo64(fpuPop());
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDF && middleDigit == 5) {                    //FILD
        uint64_t* p = (uint64_t*) ptr;
        fpuPush(fpuULongToFloat(*p));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDB && middleDigit == 0) {                    //FILD
        uint32_t* p = (uint32_t*) ptr;
        fpuPush(fpuULongToFloat(*p));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 0) {                    //FADD
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuAdd(fpuGetReg(0), fpu32ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 1) {                    //FMUL
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpu32ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 1) {                    //FMUL
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpu64ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 6) {                    //FDIV
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu32ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 6) {                    //FDIV
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu64ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 4) {                    //FSUB
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuSub(fpuGetReg(0), fpu32ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 4) {                    //FSUB
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuSub(fpuGetReg(0), fpu64ToInternal(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 5) {                    //FSUBR
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuSub(fpu32ToInternal(*p), fpuGetReg(0)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 5) {                    //FSUBR
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuSub(fpu64ToInternal(*p), fpuGetReg(0)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xD8 && middleDigit == 7) {                    //FDIVR
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuDivide(fpu32ToInternal(*p), fpuGetReg(0)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 7) {                    //FDIVR
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuDivide(fpu64ToInternal(*p), fpuGetReg(0)));
        r->eip += instrLen;
        return true;


    } else if (eip[0] == 0xDA && middleDigit == 1) {                    //FIMUL
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuLongToFloat(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDA && middleDigit == 4) {                    //FISUB
        uint32_t* p = (uint32_t*) ptr;
        fpuSetReg(0, fpuSub(fpuGetReg(0), fpuLongToFloat(*p)));
        r->eip += instrLen;
        return true;

    } else if (eip[0] == 0xDC && middleDigit == 0) {                    //FADD
        uint64_t* p = (uint64_t*) ptr;
        fpuSetReg(0, fpuAdd(fpuGetReg(0), fpu64ToInternal(*p)));
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

