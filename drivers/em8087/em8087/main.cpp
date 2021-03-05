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

Float80 fpuStack[8];
int fpuSP = 0;

void fpuPush(Float80 flt)
{
    
}

Float80 fpuPop()
{
    return fpuStack[0];
}

bool x87Handler(regs* r)
{
	uint8_t* eip = (uint8_t*) r->eip;
    kprintf("x87 handler called with faulting EIP of 0x%X\n", eip);
	kprintf("x87: %X %X %X\n", *eip, *(eip + 1), *(eip + 2));

    if (eip[0] == 0xD9) {
        switch (eip[1]) { 
        case 0xE8:  //D9 E8     FLD1
            fpuPush(fpuGet1());
            return true;
        case 0xE9:  //D9 E9     FLDL2T
            fpuPush(fpuGetLog210());
            return true;
        case 0xEA:  //D9 EA     FLDL2E
            fpuPush(fpuGetLog2E());
            return true;
        case 0xEB:  //D9 EB     FLDPI
            fpuPush(fpuGetPi());
            return true;
        case 0xEC:  //D9 EC     FLDLG2
            fpuPush(fpuGetLog102());
            return true;
        case 0xED:  //D9 ED     FLDLN2
            fpuPush(fpuGetLogE2());
            return true;
        case 0xEE:  //D9 EE     FLD0
            fpuPush(fpuGet0());
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

