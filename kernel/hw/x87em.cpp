#include "hw/x87em.hpp"
#include "hw/cpu.hpp"

FPUState fpuState;

uint32_t fpuInternalTo32(Float80 flt)
{
	//double -> float

	uint32_t out = 0;
	if (flt >> 63) {
		out |= (1ULL << 31ULL);
	}

	uint64_t significand = flt & 0xFFFFFFFFFFFFFULL;
	int64_t expo = ((flt >> 52) & 0x7FF) - 1023 + 127;
	if (expo < 0 || expo > 255) {
		panic("HMMM...");
		//underflow / overflow
		return 0;
	}

	significand >>= 52ULL - 23ULL;
	out |= significand;
	out |= expo << 23ULL;
	return out;
}

uint64_t fpuInternalTo64(Float80 flt)
{
	// double -> double
	return flt;
}

Float80 fpu32ToInternal(uint32_t flt)
{
	// float -> double
	uint32_t out = 0;
	if (flt >> 31) {
		out |= (1ULL << 63ULL);
	}

	uint64_t significand = flt & 0x7FFFFF;
	uint64_t expo = ((flt >> 23) & 0xFF) - 127 + 1023;

	significand <<= 52ULL - 23ULL;
	out |= significand;
	out |= expo << 52ULL;
	return out;
}

Float80 fpu64ToInternal(uint64_t flt)
{
	// double -> double
	return flt;
}

int64_t fpuFloatToLong(Float80 flt)
{
	// double -> int

	int expo = ((flt >> 52) & 0x7FF) - 1023;
	if (expo < 0) {
		return 0;
	}

	int64_t significand = flt & 0xFFFFFFFFFFFFFULL;
	significand |= (1ULL << 52ULL);
	significand >>= 52 - expo;

	if (flt >> 63) {
		significand = -significand;
	}

	return significand;
}

Float80 fpuULongToFloat(uint64_t significand)
{
	// unsigned long -> double

	int shifts = 0;
	while ((significand & (1ULL << 52ULL)) == 0) {
		significand <<= 1;
		shifts++;
	}

	uint64_t exponent = 1023 + 52 - shifts;
	return (exponent << 52ULL) | (significand & 0xFFFFFFFFFFFFFULL);
}

Float80 fpuLongToFloat(int64_t signedSignificand)
{
	// long -> double

	int shifts = 0;
	bool neg = false;

	uint64_t significand;
	if (signedSignificand > 0) {
		significand = signedSignificand;
	} else {
		significand = -signedSignificand;
		neg = true;
	}

	while ((significand & (1ULL << 52ULL)) == 0) {
		significand <<= 1;
		shifts++;
	}

	uint64_t exponent = 1023 + 52 - shifts;
	uint64_t merged = (exponent << 52ULL) | (significand & 0xFFFFFFFFFFFFFULL);
	if (neg) {
		merged |= (1ULL << 63ULL);
	}
	return merged;
}

Float80 fpuGet0()
{
	return 0;
}

Float80 fpuGet1()
{
	return 1.0;
}

Float80 fpuGetPi()
{
	return 3.141592;
}

Float80 fpuGetLog2E()
{
	panic("AHA!");
	return 0xDEADBEEF;
}

Float80 fpuGetLogE2()
{
	panic("AHA!");
	return 0xDEADBEEF;
}

Float80 fpuGetLog210()
{
	panic("AHA!");
	return 0xDEADBEEF;
}

Float80 fpuGetLog102()
{
	panic("AHA!");
	return 0xDEADBEEF;
}

bool fpuIsSecondLarger(Float80 x, Float80 y)
{
	return y > x;
}

bool fpuAreEqual(Float80 x, Float80 y)
{
	return x == y;
}

void fpuUnorderedCompare(Float80 x, Float80 y)
{
	fpuState.c0 = !fpuAreEqual(x, y) && fpuIsSecondLarger(x, y);
	fpuState.c2 = 0;
	fpuState.c3 = fpuAreEqual(x, y);
}

Float80 fpuAdd(Float80 x, Float80 y)
{
	return x + y;
}

Float80 fpuAbs(Float80 x)
{
	if (x < 0.0) {
		x = -x;
	}
	return x;
}

Float80 fpuChs(Float80 x)
{
	return -x;
}

Float80 fpuSub(Float80 x, Float80 y)
{
	return fpuAdd(x, -y);
}

Float80 fpuMultiply(Float80 x, Float80 y)
{
	return x * y;
}

Float80 fpuDivide(Float80 x, Float80 y)
{
	return x / y;
}

Float80 fpuSquare(Float80 flt)
{
	return fpuMultiply(flt, flt);
}

Float80 fpuGetReg(int num)
{
	if (num < 0 || num > 7) {
		panic("em8087 bad reg get");
	}
	kprintf("REG(%d) = ST(%d)\n", num, (fpuState.stackTop + num) % 8);
	return fpuState.regs[(fpuState.stackTop + num) % 8];
}

void fpuSetReg(int num, Float80 flt)
{
	if (num < 0 || num > 7) {
		panic("em8087 bad reg set");
	}
	kprintf("REG(%d) = ST(%d)\n", num, (fpuState.stackTop + num) % 8);
	fpuState.regs[(fpuState.stackTop + num) % 8] = flt;
}

void fpuPush(Float80 flt)
{
	fpuState.stackTop = (fpuState.stackTop + 7) % 8;
	fpuState.regs[fpuState.stackTop] = flt;

	kprintf("pushing, REG(%d) set.\n\n", fpuState.stackTop);

	if (fpuState.valuesOnStack == 8) {
		fpuState.stackFault = 1;
	} else {
		fpuState.valuesOnStack++;
	}
}

Float80 fpuPop()
{
	kprintf("popping from REG(%d).\n", fpuState.stackTop);

	Float80 v = fpuState.regs[fpuState.stackTop];
	fpuState.stackTop = (fpuState.stackTop + 1) % 8;
	if (fpuState.valuesOnStack) {
		--fpuState.valuesOnStack;
	} else {
		fpuState.stackFault = 1;
	}

	return v;
}

/*
c0026a07:	dd 04 24             	fld    QWORD PTR [esp]
c0026a10:	dd 44 24 04          	fld    QWORD PTR [esp+0x4]
c0026a17:	db 1c 24             	fistp  DWORD PTR [esp]
*/

bool x87Handler(regs* r)
{
	uint8_t* eip = (uint8_t*) r->eip;

	uint8_t* ptr = 0;
	bool registerOnly = false;
	int instrLen = 2;
	uint8_t middleDigit;

	ptr = CPU::decodeAddress(r, &instrLen, &registerOnly, &middleDigit);

	kprintf("x87 0x%X\n", eip);

	kprintf("r->esp = 0x%X, r->useresp = 0x%X\n", r->esp, r->useresp);
	//kprintf("x87: %X %X %X %X\n", *eip, *(eip + 1), *(eip + 2), *(eip + 3));
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

	if (eip[0] == 0xD8 && eip[1] >= 0xC0 && eip[1] <= 0xC7) {           //FADD
		fpuSetReg(0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
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

	} else if (eip[0] == 0xD8 && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FSUB
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUBR
		fpuSetReg(0, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVP
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xF8 /*&& eip[1] <= 0xFF*/) {     //FDIVRP
		fpuSetReg(0, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xD9 && eip[1] >= 0xC0 && eip[1] <= 0xC7) {      //FLD
		fpuPush(fpuGetReg(eip[1] - 0xC0));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD9 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FXCH
		Float80 st1 = fpuGetReg(eip[1] - 0xC8);
		fpuSetReg(eip[1] - 0xC8, fpuGetReg(0));
		fpuSetReg(0, st1);
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADD
		fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
		fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUB
		fpuSetReg(eip[1] - 0xE8, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADDP
		fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		fpuPop();
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

	} else if (eip[0] == 0xDE && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMULP
		fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xF8 /*&& eip[1] <= 0xFF*/) {     //FDIVP
		fpuSetReg(eip[1] - 0xF8, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVRP
		fpuSetReg(eip[1] - 0xF0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
		r->eip += 2;
		fpuPop();
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
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(1));
		r->eip += 2;
		fpuPop();
		fpuPop();
		return true;

	} else if (eip[0] == 0xDF && eip[1] == 0xE0) {                      //FNSTSW
		r->eax &= ~0xFFFF;
		r->eax |= fpuState.status;
		r->eip += 2;
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

	} else if (eip[0] == 0xD8 && middleDigit == 4) {                    //FSUB
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 5) {                    //FSUBR
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuSub(fpu32ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 6) {                    //FDIV
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 7) {                    //FDIVR
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpu32ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 0) {                    //FLD
		uint32_t* p = (uint32_t*) ptr;
		fpuPush(fpu32ToInternal(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 3) {                    //FSTP
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuInternalTo32(fpuPop());
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 5) {                      //FLDCW
		uint16_t* p = (uint16_t*) ptr;
		fpuState.control = *p;
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 7) {                      //FNSTCW
		uint16_t* p = (uint16_t*) ptr;
		*p = fpuState.control;
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

	} else if (eip[0] == 0xDA && middleDigit == 7) {                    //FISUB
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuLongToFloat(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDB && middleDigit == 0) {                    //FILD
		uint32_t* p = (uint32_t*) ptr;
		fpuPush(fpuULongToFloat(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDB && middleDigit == 2) {                      //FIST
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuFloatToLong(fpuGetReg(0));
		r->eip += instrLen;
		return true;

		/*
c0026a07:	dd 04 24             	fld    QWORD PTR [esp]
c0026a10:	dd 44 24 04          	fld    QWORD PTR [esp+0x4]
c0026a17:	db 1c 24             	fistp  DWORD PTR [esp]
*/

	} else if (eip[0] == 0xDB && middleDigit == 3) {                      //FISTP
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuFloatToLong(fpuPop());
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 0) {                    //FADD
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuAdd(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 1) {                    //FMUL
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 2) {                    //FCOM
		uint64_t* p = (uint64_t*) ptr;
		fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 3) {                     //FCOMP
		uint64_t* p = (uint64_t*) ptr;
		fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
		fpuPop();
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 4) {                    //FSUB
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 5) {                    //FSUBR
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuSub(fpu64ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 6) {                    //FDIV
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 7) {                    //FDIVR
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuDivide(fpu64ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	/*
	c0026a07:	dd 04 24             	fld    QWORD PTR [esp]
	c0026a10:	dd 44 24 04          	fld    QWORD PTR [esp+0x4]
	c0026a17:	db 1c 24             	fistp  DWORD PTR [esp]
	*/

	} else if (eip[0] == 0xDD && middleDigit == 0) {                    //FLD
		uint64_t* p = (uint64_t*) ptr;
		fpuPush(fpu64ToInternal(*p));
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

	} else if (eip[0] == 0xDE && middleDigit == 1) {                    //FIMUL 16
		uint16_t* p = (uint16_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuLongToFloat(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDF && middleDigit == 5) {                    //FILD
		uint64_t* p = (uint64_t*) ptr;
		fpuPush(fpuULongToFloat(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDF && middleDigit == 7) {                    //FISTP
		uint64_t* p = (uint64_t*) ptr;
		*p = fpuFloatToLong(fpuPop());
		r->eip += instrLen;
		return true;
	}

	return false;
}
