/* This file auto-generated from insns.dat by insns.pl - don't edit it */

#include "nasm.h"
#include "insns.h"

static const struct itemplate instrux_DB[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DW[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DD[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DQ[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DT[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DO[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DY[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_DZ[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_RESB[] = {
    {I_RESB, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESW[] = {
    {I_RESW, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESD[] = {
    {I_RESD, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESQ[] = {
    {I_RESQ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_REST[] = {
    {I_REST, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESO[] = {
    {I_RESO, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESY[] = {
    {I_RESY, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_RESZ[] = {
    {I_RESZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45059, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_INCBIN[] = {
    ITEMPLATE_END
};

static const struct itemplate instrux_AAA[] = {
    {I_AAA, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45921, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_AAD[] = {
    {I_AAD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44921, 1},
    {I_AAD, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44925, 2},
    ITEMPLATE_END
};

static const struct itemplate instrux_AAM[] = {
    {I_AAM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44929, 1},
    {I_AAM, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44933, 2},
    ITEMPLATE_END
};

static const struct itemplate instrux_AAS[] = {
    {I_AAS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45924, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADC[] = {
    {I_ADC, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43121, 3},
    {I_ADC, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43122, 0},
    {I_ADC, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39341, 3},
    {I_ADC, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39342, 0},
    {I_ADC, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39347, 4},
    {I_ADC, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39348, 5},
    {I_ADC, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39353, 6},
    {I_ADC, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39354, 7},
    {I_ADC, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+33422, 8},
    {I_ADC, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+33422, 0},
    {I_ADC, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43126, 8},
    {I_ADC, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43126, 0},
    {I_ADC, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43131, 9},
    {I_ADC, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43131, 5},
    {I_ADC, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43136, 10},
    {I_ADC, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43136, 7},
    {I_ADC, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+29961, 11},
    {I_ADC, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+29968, 12},
    {I_ADC, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+29975, 13},
    {I_ADC, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44937, 8},
    {I_ADC, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29962, 8},
    {I_ADC, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43141, 8},
    {I_ADC, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29969, 9},
    {I_ADC, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43146, 9},
    {I_ADC, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29976, 10},
    {I_ADC, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43151, 10},
    {I_ADC, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39359, 3},
    {I_ADC, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29961, 3},
    {I_ADC, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+29982, 3},
    {I_ADC, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29968, 4},
    {I_ADC, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+29989, 4},
    {I_ADC, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+29975, 6},
    {I_ADC, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+29996, 6},
    {I_ADC, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39359, 3},
    {I_ADC, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+29961, 3},
    {I_ADC, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+29982, 3},
    {I_ADC, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+29968, 4},
    {I_ADC, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+29989, 4},
    {I_ADC, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39365, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADD[] = {
    {I_ADD, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43156, 3},
    {I_ADD, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43157, 0},
    {I_ADD, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39371, 3},
    {I_ADD, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39372, 0},
    {I_ADD, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39377, 4},
    {I_ADD, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39378, 5},
    {I_ADD, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39383, 6},
    {I_ADD, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39384, 7},
    {I_ADD, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+37195, 8},
    {I_ADD, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+37195, 0},
    {I_ADD, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43161, 8},
    {I_ADD, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43161, 0},
    {I_ADD, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43166, 9},
    {I_ADD, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43166, 5},
    {I_ADD, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43171, 10},
    {I_ADD, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43171, 7},
    {I_ADD, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30003, 11},
    {I_ADD, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30010, 12},
    {I_ADD, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30017, 13},
    {I_ADD, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44941, 8},
    {I_ADD, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30004, 8},
    {I_ADD, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43176, 8},
    {I_ADD, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30011, 9},
    {I_ADD, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43181, 9},
    {I_ADD, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30018, 10},
    {I_ADD, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43186, 10},
    {I_ADD, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39389, 3},
    {I_ADD, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30003, 3},
    {I_ADD, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30024, 3},
    {I_ADD, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30010, 4},
    {I_ADD, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30031, 4},
    {I_ADD, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30017, 6},
    {I_ADD, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30038, 6},
    {I_ADD, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39389, 3},
    {I_ADD, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30003, 3},
    {I_ADD, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30024, 3},
    {I_ADD, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30010, 4},
    {I_ADD, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30031, 4},
    {I_ADD, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39395, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_AND[] = {
    {I_AND, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43191, 3},
    {I_AND, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43192, 0},
    {I_AND, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39401, 3},
    {I_AND, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39402, 0},
    {I_AND, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39407, 4},
    {I_AND, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39408, 5},
    {I_AND, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39413, 6},
    {I_AND, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39414, 7},
    {I_AND, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+37475, 8},
    {I_AND, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+37475, 0},
    {I_AND, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43196, 8},
    {I_AND, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43196, 0},
    {I_AND, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43201, 9},
    {I_AND, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43201, 5},
    {I_AND, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43206, 10},
    {I_AND, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43206, 7},
    {I_AND, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30045, 11},
    {I_AND, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30052, 12},
    {I_AND, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30059, 13},
    {I_AND, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44945, 8},
    {I_AND, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30046, 8},
    {I_AND, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43211, 8},
    {I_AND, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30053, 9},
    {I_AND, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43216, 9},
    {I_AND, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30060, 10},
    {I_AND, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43221, 10},
    {I_AND, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39419, 3},
    {I_AND, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30045, 3},
    {I_AND, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30066, 3},
    {I_AND, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30052, 4},
    {I_AND, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30073, 4},
    {I_AND, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30059, 6},
    {I_AND, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30080, 6},
    {I_AND, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39419, 3},
    {I_AND, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30045, 3},
    {I_AND, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30066, 3},
    {I_AND, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30052, 4},
    {I_AND, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30073, 4},
    {I_AND, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39425, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_ARPL[] = {
    {I_ARPL, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+28973, 15},
    {I_ARPL, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+28973, 16},
    ITEMPLATE_END
};

static const struct itemplate instrux_BB0_RESET[] = {
    {I_BB0_RESET, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44949, 17},
    ITEMPLATE_END
};

static const struct itemplate instrux_BB1_RESET[] = {
    {I_BB1_RESET, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44953, 17},
    ITEMPLATE_END
};

static const struct itemplate instrux_BOUND[] = {
    {I_BOUND, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43226, 18},
    {I_BOUND, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43231, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_BSF[] = {
    {I_BSF, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30087, 9},
    {I_BSF, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30087, 5},
    {I_BSF, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30094, 9},
    {I_BSF, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30094, 5},
    {I_BSF, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30101, 10},
    {I_BSF, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30101, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_BSR[] = {
    {I_BSR, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30108, 9},
    {I_BSR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30108, 5},
    {I_BSR, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30115, 9},
    {I_BSR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30115, 5},
    {I_BSR, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30122, 10},
    {I_BSR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30122, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_BSWAP[] = {
    {I_BSWAP, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39431, 20},
    {I_BSWAP, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39437, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_BT[] = {
    {I_BT, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39443, 9},
    {I_BT, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39443, 5},
    {I_BT, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39449, 9},
    {I_BT, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39449, 5},
    {I_BT, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39455, 10},
    {I_BT, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39455, 7},
    {I_BT, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30129, 5},
    {I_BT, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30136, 5},
    {I_BT, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30143, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_BTC[] = {
    {I_BTC, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30150, 4},
    {I_BTC, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30151, 5},
    {I_BTC, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30157, 4},
    {I_BTC, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30158, 5},
    {I_BTC, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30164, 6},
    {I_BTC, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30165, 7},
    {I_BTC, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12025, 12},
    {I_BTC, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12033, 12},
    {I_BTC, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12041, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_BTR[] = {
    {I_BTR, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30171, 4},
    {I_BTR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30172, 5},
    {I_BTR, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30178, 4},
    {I_BTR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30179, 5},
    {I_BTR, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30185, 6},
    {I_BTR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30186, 7},
    {I_BTR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12049, 12},
    {I_BTR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12057, 12},
    {I_BTR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12065, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_BTS[] = {
    {I_BTS, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30192, 4},
    {I_BTS, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30193, 5},
    {I_BTS, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30199, 4},
    {I_BTS, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30200, 5},
    {I_BTS, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30206, 6},
    {I_BTS, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30207, 7},
    {I_BTS, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12073, 12},
    {I_BTS, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12081, 12},
    {I_BTS, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12089, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_CALL[] = {
    {I_CALL, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43236, 21},
    {I_CALL, 1, {IMMEDIATE|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43236, 21},
    {I_CALL, 1, {IMMEDIATE|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39461, 1},
    {I_CALL, 1, {IMMEDIATE|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43241, 22},
    {I_CALL, 1, {IMMEDIATE|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43241, 22},
    {I_CALL, 1, {IMMEDIATE|BITS16|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39467, 1},
    {I_CALL, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43246, 23},
    {I_CALL, 1, {IMMEDIATE|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43246, 23},
    {I_CALL, 1, {IMMEDIATE|BITS32|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39473, 19},
    {I_CALL, 1, {IMMEDIATE|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43251, 24},
    {I_CALL, 1, {IMMEDIATE|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43251, 24},
    {I_CALL, 2, {IMMEDIATE|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39479, 1},
    {I_CALL, 2, {IMMEDIATE|BITS16|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39485, 1},
    {I_CALL, 2, {IMMEDIATE|COLON,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39485, 1},
    {I_CALL, 2, {IMMEDIATE|BITS32|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39491, 19},
    {I_CALL, 2, {IMMEDIATE|COLON,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39491, 19},
    {I_CALL, 1, {MEMORY|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43256, 1},
    {I_CALL, 1, {MEMORY|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43261, 7},
    {I_CALL, 1, {MEMORY|BITS16|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43266, 0},
    {I_CALL, 1, {MEMORY|BITS32|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43271, 5},
    {I_CALL, 1, {MEMORY|BITS64|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43261, 7},
    {I_CALL, 1, {MEMORY|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43276, 21},
    {I_CALL, 1, {RM_GPR|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43281, 22},
    {I_CALL, 1, {RM_GPR|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43286, 23},
    {I_CALL, 1, {RM_GPR|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43291, 24},
    {I_CALL, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43276, 21},
    {I_CALL, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43281, 22},
    {I_CALL, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43286, 23},
    {I_CALL, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43291, 24},
    ITEMPLATE_END
};

static const struct itemplate instrux_CBW[] = {
    {I_CBW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44957, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CDQ[] = {
    {I_CDQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44961, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_CDQE[] = {
    {I_CDQE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44965, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLC[] = {
    {I_CLC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44693, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLD[] = {
    {I_CLD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41900, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLI[] = {
    {I_CLI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44008, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLTS[] = {
    {I_CLTS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44969, 25},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMC[] = {
    {I_CMC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45927, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMP[] = {
    {I_CMP, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44973, 8},
    {I_CMP, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44973, 0},
    {I_CMP, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43296, 8},
    {I_CMP, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43296, 0},
    {I_CMP, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43301, 9},
    {I_CMP, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43301, 5},
    {I_CMP, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43306, 10},
    {I_CMP, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43306, 7},
    {I_CMP, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+37433, 8},
    {I_CMP, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+37433, 0},
    {I_CMP, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43311, 8},
    {I_CMP, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+43311, 0},
    {I_CMP, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43316, 9},
    {I_CMP, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+43316, 5},
    {I_CMP, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43321, 10},
    {I_CMP, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+43321, 7},
    {I_CMP, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39497, 0},
    {I_CMP, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39503, 5},
    {I_CMP, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39509, 7},
    {I_CMP, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44977, 8},
    {I_CMP, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39497, 8},
    {I_CMP, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43326, 8},
    {I_CMP, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39503, 9},
    {I_CMP, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43331, 9},
    {I_CMP, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39509, 10},
    {I_CMP, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43336, 10},
    {I_CMP, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43341, 8},
    {I_CMP, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39497, 8},
    {I_CMP, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39515, 8},
    {I_CMP, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39503, 9},
    {I_CMP, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39521, 9},
    {I_CMP, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39509, 10},
    {I_CMP, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39527, 10},
    {I_CMP, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43341, 8},
    {I_CMP, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39497, 8},
    {I_CMP, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39515, 8},
    {I_CMP, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39503, 9},
    {I_CMP, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39521, 9},
    {I_CMP, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43346, 26},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPSB[] = {
    {I_CMPSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44981, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPSD[] = {
    {I_CMPSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43351, 5},
    {I_CMPSD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+31333, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPSQ[] = {
    {I_CMPSQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43356, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPSW[] = {
    {I_CMPSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43361, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPXCHG[] = {
    {I_CMPXCHG, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39533, 27},
    {I_CMPXCHG, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39534, 28},
    {I_CMPXCHG, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30213, 27},
    {I_CMPXCHG, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30214, 28},
    {I_CMPXCHG, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30220, 27},
    {I_CMPXCHG, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30221, 28},
    {I_CMPXCHG, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30227, 6},
    {I_CMPXCHG, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30228, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPXCHG486[] = {
    {I_CMPXCHG486, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43366, 29},
    {I_CMPXCHG486, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+43366, 30},
    {I_CMPXCHG486, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39539, 29},
    {I_CMPXCHG486, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39539, 30},
    {I_CMPXCHG486, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39545, 29},
    {I_CMPXCHG486, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39545, 30},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPXCHG8B[] = {
    {I_CMPXCHG8B, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30234, 31},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPXCHG16B[] = {
    {I_CMPXCHG16B, 1, {MEMORY|BITS128,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39551, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_CPUID[] = {
    {I_CPUID, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44985, 28},
    ITEMPLATE_END
};

static const struct itemplate instrux_CPU_READ[] = {
    {I_CPU_READ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44989, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_CPU_WRITE[] = {
    {I_CPU_WRITE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44993, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_CQO[] = {
    {I_CQO, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44997, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_CWD[] = {
    {I_CWD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45001, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_CWDE[] = {
    {I_CWDE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45005, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_DAA[] = {
    {I_DAA, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45930, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_DAS[] = {
    {I_DAS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45933, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_DEC[] = {
    {I_DEC, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45009, 1},
    {I_DEC, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45013, 19},
    {I_DEC, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43371, 11},
    {I_DEC, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39557, 11},
    {I_DEC, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39563, 12},
    {I_DEC, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39569, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_DIV[] = {
    {I_DIV, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45017, 0},
    {I_DIV, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43376, 0},
    {I_DIV, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43381, 5},
    {I_DIV, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43386, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_DMINT[] = {
    {I_DMINT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45021, 33},
    ITEMPLATE_END
};

static const struct itemplate instrux_EMMS[] = {
    {I_EMMS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45025, 34},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENTER[] = {
    {I_ENTER, 2, {IMMEDIATE,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43391, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_EQU[] = {
    {I_EQU, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45965, 0},
    {I_EQU, 2, {IMMEDIATE|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45965, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_F2XM1[] = {
    {I_F2XM1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45029, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FABS[] = {
    {I_FABS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45033, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FADD[] = {
    {I_FADD, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45037, 36},
    {I_FADD, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45041, 36},
    {I_FADD, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43396, 36},
    {I_FADD, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43401, 36},
    {I_FADD, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43396, 36},
    {I_FADD, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43406, 36},
    {I_FADD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45045, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FADDP[] = {
    {I_FADDP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43411, 36},
    {I_FADDP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43411, 36},
    {I_FADDP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45045, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FBLD[] = {
    {I_FBLD, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45049, 36},
    {I_FBLD, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45049, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FBSTP[] = {
    {I_FBSTP, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45053, 36},
    {I_FBSTP, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45053, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCHS[] = {
    {I_FCHS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45057, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCLEX[] = {
    {I_FCLEX, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43416, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVB[] = {
    {I_FCMOVB, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43421, 37},
    {I_FCMOVB, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43426, 37},
    {I_FCMOVB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45061, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVBE[] = {
    {I_FCMOVBE, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43431, 37},
    {I_FCMOVBE, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43436, 37},
    {I_FCMOVBE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45065, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVE[] = {
    {I_FCMOVE, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43441, 37},
    {I_FCMOVE, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43446, 37},
    {I_FCMOVE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45069, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVNB[] = {
    {I_FCMOVNB, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43451, 37},
    {I_FCMOVNB, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43456, 37},
    {I_FCMOVNB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45073, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVNBE[] = {
    {I_FCMOVNBE, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43461, 37},
    {I_FCMOVNBE, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43466, 37},
    {I_FCMOVNBE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45077, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVNE[] = {
    {I_FCMOVNE, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43471, 37},
    {I_FCMOVNE, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43476, 37},
    {I_FCMOVNE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45081, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVNU[] = {
    {I_FCMOVNU, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43481, 37},
    {I_FCMOVNU, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43486, 37},
    {I_FCMOVNU, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45085, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCMOVU[] = {
    {I_FCMOVU, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43491, 37},
    {I_FCMOVU, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43496, 37},
    {I_FCMOVU, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45089, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOM[] = {
    {I_FCOM, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45093, 36},
    {I_FCOM, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45097, 36},
    {I_FCOM, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43501, 36},
    {I_FCOM, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43506, 36},
    {I_FCOM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45101, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOMI[] = {
    {I_FCOMI, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43511, 37},
    {I_FCOMI, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43516, 37},
    {I_FCOMI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45105, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOMIP[] = {
    {I_FCOMIP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43521, 37},
    {I_FCOMIP, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43526, 37},
    {I_FCOMIP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45109, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOMP[] = {
    {I_FCOMP, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45113, 36},
    {I_FCOMP, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45117, 36},
    {I_FCOMP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43531, 36},
    {I_FCOMP, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43536, 36},
    {I_FCOMP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45121, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOMPP[] = {
    {I_FCOMPP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45125, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FCOS[] = {
    {I_FCOS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45129, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDECSTP[] = {
    {I_FDECSTP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45133, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDISI[] = {
    {I_FDISI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43541, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDIV[] = {
    {I_FDIV, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45137, 36},
    {I_FDIV, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45141, 36},
    {I_FDIV, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43546, 36},
    {I_FDIV, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43551, 36},
    {I_FDIV, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43546, 36},
    {I_FDIV, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43556, 36},
    {I_FDIV, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45145, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDIVP[] = {
    {I_FDIVP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43561, 36},
    {I_FDIVP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43561, 36},
    {I_FDIVP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45145, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDIVR[] = {
    {I_FDIVR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45149, 36},
    {I_FDIVR, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45153, 36},
    {I_FDIVR, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43566, 36},
    {I_FDIVR, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43566, 36},
    {I_FDIVR, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43571, 36},
    {I_FDIVR, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43576, 36},
    {I_FDIVR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45157, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FDIVRP[] = {
    {I_FDIVRP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43581, 36},
    {I_FDIVRP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43581, 36},
    {I_FDIVRP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45157, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FEMMS[] = {
    {I_FEMMS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45161, 39},
    ITEMPLATE_END
};

static const struct itemplate instrux_FENI[] = {
    {I_FENI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43586, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FFREE[] = {
    {I_FFREE, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43591, 36},
    {I_FFREE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45165, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FFREEP[] = {
    {I_FFREEP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43596, 40},
    {I_FFREEP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45169, 40},
    ITEMPLATE_END
};

static const struct itemplate instrux_FIADD[] = {
    {I_FIADD, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45173, 36},
    {I_FIADD, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45177, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FICOM[] = {
    {I_FICOM, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45181, 36},
    {I_FICOM, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45185, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FICOMP[] = {
    {I_FICOMP, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45189, 36},
    {I_FICOMP, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45193, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FIDIV[] = {
    {I_FIDIV, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45197, 36},
    {I_FIDIV, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45201, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FIDIVR[] = {
    {I_FIDIVR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45205, 36},
    {I_FIDIVR, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45209, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FILD[] = {
    {I_FILD, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45213, 36},
    {I_FILD, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45217, 36},
    {I_FILD, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45221, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FIMUL[] = {
    {I_FIMUL, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45225, 36},
    {I_FIMUL, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45229, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FINCSTP[] = {
    {I_FINCSTP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45233, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FINIT[] = {
    {I_FINIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43601, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FIST[] = {
    {I_FIST, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45237, 36},
    {I_FIST, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45241, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FISTP[] = {
    {I_FISTP, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45245, 36},
    {I_FISTP, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45249, 36},
    {I_FISTP, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45253, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FISTTP[] = {
    {I_FISTTP, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45257, 41},
    {I_FISTTP, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45261, 41},
    {I_FISTTP, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45265, 41},
    ITEMPLATE_END
};

static const struct itemplate instrux_FISUB[] = {
    {I_FISUB, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45269, 36},
    {I_FISUB, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45273, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FISUBR[] = {
    {I_FISUBR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45277, 36},
    {I_FISUBR, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45281, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLD[] = {
    {I_FLD, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45285, 36},
    {I_FLD, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45289, 36},
    {I_FLD, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45293, 36},
    {I_FLD, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43606, 36},
    {I_FLD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45297, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLD1[] = {
    {I_FLD1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45301, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDCW[] = {
    {I_FLDCW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45305, 42},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDENV[] = {
    {I_FLDENV, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45309, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDL2E[] = {
    {I_FLDL2E, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45313, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDL2T[] = {
    {I_FLDL2T, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45317, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDLG2[] = {
    {I_FLDLG2, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45321, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDLN2[] = {
    {I_FLDLN2, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45325, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDPI[] = {
    {I_FLDPI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45329, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FLDZ[] = {
    {I_FLDZ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45333, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FMUL[] = {
    {I_FMUL, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45337, 36},
    {I_FMUL, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45341, 36},
    {I_FMUL, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43611, 36},
    {I_FMUL, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43611, 36},
    {I_FMUL, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43616, 36},
    {I_FMUL, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43621, 36},
    {I_FMUL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45345, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FMULP[] = {
    {I_FMULP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43626, 36},
    {I_FMULP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43626, 36},
    {I_FMULP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45345, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNCLEX[] = {
    {I_FNCLEX, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43417, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNDISI[] = {
    {I_FNDISI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43542, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNENI[] = {
    {I_FNENI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43587, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNINIT[] = {
    {I_FNINIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43602, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNOP[] = {
    {I_FNOP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45349, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNSAVE[] = {
    {I_FNSAVE, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43632, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNSTCW[] = {
    {I_FNSTCW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43642, 42},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNSTENV[] = {
    {I_FNSTENV, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43647, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FNSTSW[] = {
    {I_FNSTSW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43657, 42},
    {I_FNSTSW, 1, {REG_AX,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43662, 43},
    ITEMPLATE_END
};

static const struct itemplate instrux_FPATAN[] = {
    {I_FPATAN, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45353, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FPREM[] = {
    {I_FPREM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45357, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FPREM1[] = {
    {I_FPREM1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45361, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FPTAN[] = {
    {I_FPTAN, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45365, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FRNDINT[] = {
    {I_FRNDINT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45369, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FRSTOR[] = {
    {I_FRSTOR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45373, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSAVE[] = {
    {I_FSAVE, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43631, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSCALE[] = {
    {I_FSCALE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45377, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSETPM[] = {
    {I_FSETPM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45381, 43},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSIN[] = {
    {I_FSIN, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45385, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSINCOS[] = {
    {I_FSINCOS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45389, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSQRT[] = {
    {I_FSQRT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45393, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FST[] = {
    {I_FST, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45397, 36},
    {I_FST, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45401, 36},
    {I_FST, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43636, 36},
    {I_FST, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45405, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSTCW[] = {
    {I_FSTCW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43641, 42},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSTENV[] = {
    {I_FSTENV, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43646, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSTP[] = {
    {I_FSTP, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45409, 36},
    {I_FSTP, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45413, 36},
    {I_FSTP, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45417, 36},
    {I_FSTP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43651, 36},
    {I_FSTP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45421, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSTSW[] = {
    {I_FSTSW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43656, 42},
    {I_FSTSW, 1, {REG_AX,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43661, 43},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSUB[] = {
    {I_FSUB, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45425, 36},
    {I_FSUB, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45429, 36},
    {I_FSUB, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43666, 36},
    {I_FSUB, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43666, 36},
    {I_FSUB, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43671, 36},
    {I_FSUB, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43676, 36},
    {I_FSUB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45433, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSUBP[] = {
    {I_FSUBP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43681, 36},
    {I_FSUBP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43681, 36},
    {I_FSUBP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45433, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSUBR[] = {
    {I_FSUBR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45437, 36},
    {I_FSUBR, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45441, 36},
    {I_FSUBR, 1, {FPUREG|TO,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43686, 36},
    {I_FSUBR, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43686, 36},
    {I_FSUBR, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43691, 36},
    {I_FSUBR, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43696, 36},
    {I_FSUBR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45445, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FSUBRP[] = {
    {I_FSUBRP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43701, 36},
    {I_FSUBRP, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43701, 36},
    {I_FSUBRP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45445, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FTST[] = {
    {I_FTST, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45449, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FUCOM[] = {
    {I_FUCOM, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43706, 38},
    {I_FUCOM, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43711, 38},
    {I_FUCOM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45453, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FUCOMI[] = {
    {I_FUCOMI, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43716, 37},
    {I_FUCOMI, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43721, 37},
    {I_FUCOMI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45457, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FUCOMIP[] = {
    {I_FUCOMIP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43726, 37},
    {I_FUCOMIP, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43731, 37},
    {I_FUCOMIP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45461, 37},
    ITEMPLATE_END
};

static const struct itemplate instrux_FUCOMP[] = {
    {I_FUCOMP, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43736, 38},
    {I_FUCOMP, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43741, 38},
    {I_FUCOMP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45465, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FUCOMPP[] = {
    {I_FUCOMPP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45469, 38},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXAM[] = {
    {I_FXAM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45473, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXCH[] = {
    {I_FXCH, 1, {FPUREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43746, 36},
    {I_FXCH, 2, {FPUREG,FPU0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43746, 36},
    {I_FXCH, 2, {FPU0,FPUREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+43751, 36},
    {I_FXCH, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45477, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXTRACT[] = {
    {I_FXTRACT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45481, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FYL2X[] = {
    {I_FYL2X, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45485, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_FYL2XP1[] = {
    {I_FYL2XP1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45489, 36},
    ITEMPLATE_END
};

static const struct itemplate instrux_HLT[] = {
    {I_HLT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45936, 44},
    ITEMPLATE_END
};

static const struct itemplate instrux_IBTS[] = {
    {I_IBTS, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39539, 45},
    {I_IBTS, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39539, 46},
    {I_IBTS, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39545, 47},
    {I_IBTS, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39545, 46},
    ITEMPLATE_END
};

static const struct itemplate instrux_ICEBP[] = {
    {I_ICEBP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45939, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_IDIV[] = {
    {I_IDIV, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45493, 0},
    {I_IDIV, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43756, 0},
    {I_IDIV, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43761, 5},
    {I_IDIV, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43766, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_IMUL[] = {
    {I_IMUL, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45497, 0},
    {I_IMUL, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43771, 0},
    {I_IMUL, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43776, 5},
    {I_IMUL, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43781, 7},
    {I_IMUL, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39575, 9},
    {I_IMUL, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39575, 5},
    {I_IMUL, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39581, 9},
    {I_IMUL, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39581, 5},
    {I_IMUL, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39587, 10},
    {I_IMUL, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39587, 7},
    {I_IMUL, 3, {REG_GPR|BITS16,MEMORY,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39593, 48},
    {I_IMUL, 3, {REG_GPR|BITS16,MEMORY,SBYTEWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39593, 49},
    {I_IMUL, 3, {REG_GPR|BITS16,MEMORY,IMMEDIATE|BITS16,0,0}, NO_DECORATOR, nasm_bytecodes+39599, 49},
    {I_IMUL, 3, {REG_GPR|BITS16,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39599, 49},
    {I_IMUL, 3, {REG_GPR|BITS16,REG_GPR|BITS16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39593, 35},
    {I_IMUL, 3, {REG_GPR|BITS16,REG_GPR|BITS16,SBYTEWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39593, 49},
    {I_IMUL, 3, {REG_GPR|BITS16,REG_GPR|BITS16,IMMEDIATE|BITS16,0,0}, NO_DECORATOR, nasm_bytecodes+39599, 35},
    {I_IMUL, 3, {REG_GPR|BITS16,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39599, 49},
    {I_IMUL, 3, {REG_GPR|BITS32,MEMORY,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39605, 50},
    {I_IMUL, 3, {REG_GPR|BITS32,MEMORY,SBYTEDWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39605, 9},
    {I_IMUL, 3, {REG_GPR|BITS32,MEMORY,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+39611, 9},
    {I_IMUL, 3, {REG_GPR|BITS32,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39611, 9},
    {I_IMUL, 3, {REG_GPR|BITS32,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39605, 5},
    {I_IMUL, 3, {REG_GPR|BITS32,REG_GPR|BITS32,SBYTEDWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39605, 9},
    {I_IMUL, 3, {REG_GPR|BITS32,REG_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+39611, 5},
    {I_IMUL, 3, {REG_GPR|BITS32,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39611, 9},
    {I_IMUL, 3, {REG_GPR|BITS64,MEMORY,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39617, 51},
    {I_IMUL, 3, {REG_GPR|BITS64,MEMORY,SBYTEDWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39617, 10},
    {I_IMUL, 3, {REG_GPR|BITS64,MEMORY,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+39623, 51},
    {I_IMUL, 3, {REG_GPR|BITS64,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39629, 10},
    {I_IMUL, 3, {REG_GPR|BITS64,REG_GPR|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39617, 7},
    {I_IMUL, 3, {REG_GPR|BITS64,REG_GPR|BITS64,SBYTEDWORD,0,0}, NO_DECORATOR, nasm_bytecodes+39617, 10},
    {I_IMUL, 3, {REG_GPR|BITS64,REG_GPR|BITS64,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+39623, 7},
    {I_IMUL, 3, {REG_GPR|BITS64,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+39629, 10},
    {I_IMUL, 2, {REG_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39635, 35},
    {I_IMUL, 2, {REG_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39635, 49},
    {I_IMUL, 2, {REG_GPR|BITS16,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39641, 35},
    {I_IMUL, 2, {REG_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39641, 49},
    {I_IMUL, 2, {REG_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39647, 5},
    {I_IMUL, 2, {REG_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39647, 9},
    {I_IMUL, 2, {REG_GPR|BITS32,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39653, 5},
    {I_IMUL, 2, {REG_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39653, 9},
    {I_IMUL, 2, {REG_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39659, 7},
    {I_IMUL, 2, {REG_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+39659, 10},
    {I_IMUL, 2, {REG_GPR|BITS64,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39665, 7},
    {I_IMUL, 2, {REG_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39665, 10},
    ITEMPLATE_END
};

static const struct itemplate instrux_IN[] = {
    {I_IN, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45501, 52},
    {I_IN, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43786, 52},
    {I_IN, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43791, 53},
    {I_IN, 2, {REG_AL,REG_DX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45942, 0},
    {I_IN, 2, {REG_AX,REG_DX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45505, 0},
    {I_IN, 2, {REG_EAX,REG_DX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45509, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_INC[] = {
    {I_INC, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45513, 1},
    {I_INC, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45517, 19},
    {I_INC, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43796, 11},
    {I_INC, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39671, 11},
    {I_INC, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39677, 12},
    {I_INC, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39683, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_INSB[] = {
    {I_INSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45945, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_INSD[] = {
    {I_INSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45521, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_INSW[] = {
    {I_INSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45525, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_INT[] = {
    {I_INT, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45529, 52},
    ITEMPLATE_END
};

static const struct itemplate instrux_INT01[] = {
    {I_INT01, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45939, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_INT1[] = {
    {I_INT1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45939, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_INT03[] = {
    {I_INT03, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45948, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_INT3[] = {
    {I_INT3, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45948, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_INTO[] = {
    {I_INTO, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45951, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVD[] = {
    {I_INVD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45533, 54},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVPCID[] = {
    {I_INVPCID, 2, {REG_GPR|BITS32,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+30241, 55},
    {I_INVPCID, 2, {REG_GPR|BITS64,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+30241, 56},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVLPG[] = {
    {I_INVLPG, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43801, 54},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVLPGA[] = {
    {I_INVLPGA, 2, {REG_AX,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+39689, 57},
    {I_INVLPGA, 2, {REG_EAX,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+39695, 58},
    {I_INVLPGA, 2, {REG_RAX,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30248, 59},
    {I_INVLPGA, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39696, 58},
    ITEMPLATE_END
};

static const struct itemplate instrux_IRET[] = {
    {I_IRET, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45537, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_IRETD[] = {
    {I_IRETD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45541, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_IRETQ[] = {
    {I_IRETQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45545, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_IRETW[] = {
    {I_IRETW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45549, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_JCXZ[] = {
    {I_JCXZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43806, 1},
    ITEMPLATE_END
};

static const struct itemplate instrux_JECXZ[] = {
    {I_JECXZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43811, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_JRCXZ[] = {
    {I_JRCXZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39701, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_JMP[] = {
    {I_JMP, 1, {IMMEDIATE|SHORT,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43817, 0},
    {I_JMP, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43816, 0},
    {I_JMP, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43821, 21},
    {I_JMP, 1, {IMMEDIATE|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43821, 21},
    {I_JMP, 1, {IMMEDIATE|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39707, 1},
    {I_JMP, 1, {IMMEDIATE|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43826, 22},
    {I_JMP, 1, {IMMEDIATE|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43826, 22},
    {I_JMP, 1, {IMMEDIATE|BITS16|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39713, 1},
    {I_JMP, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43831, 23},
    {I_JMP, 1, {IMMEDIATE|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43831, 23},
    {I_JMP, 1, {IMMEDIATE|BITS32|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39719, 19},
    {I_JMP, 1, {IMMEDIATE|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43836, 24},
    {I_JMP, 1, {IMMEDIATE|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43836, 24},
    {I_JMP, 2, {IMMEDIATE|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39725, 1},
    {I_JMP, 2, {IMMEDIATE|BITS16|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39731, 1},
    {I_JMP, 2, {IMMEDIATE|COLON,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39731, 1},
    {I_JMP, 2, {IMMEDIATE|BITS32|COLON,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39737, 19},
    {I_JMP, 2, {IMMEDIATE|COLON,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39737, 19},
    {I_JMP, 1, {MEMORY|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43841, 1},
    {I_JMP, 1, {MEMORY|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43846, 7},
    {I_JMP, 1, {MEMORY|BITS16|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43851, 0},
    {I_JMP, 1, {MEMORY|BITS32|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43856, 5},
    {I_JMP, 1, {MEMORY|BITS64|FAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43846, 7},
    {I_JMP, 1, {MEMORY|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43861, 21},
    {I_JMP, 1, {RM_GPR|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43866, 22},
    {I_JMP, 1, {RM_GPR|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43871, 23},
    {I_JMP, 1, {RM_GPR|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43876, 24},
    {I_JMP, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43861, 21},
    {I_JMP, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43866, 22},
    {I_JMP, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43871, 23},
    {I_JMP, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43876, 24},
    ITEMPLATE_END
};

static const struct itemplate instrux_JMPE[] = {
    {I_JMPE, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39743, 60},
    {I_JMPE, 1, {IMMEDIATE|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39749, 60},
    {I_JMPE, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39755, 60},
    {I_JMPE, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39761, 60},
    {I_JMPE, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39767, 60},
    ITEMPLATE_END
};

static const struct itemplate instrux_LAHF[] = {
    {I_LAHF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45954, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_LAR[] = {
    {I_LAR, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39773, 61},
    {I_LAR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39773, 62},
    {I_LAR, 2, {REG_GPR|BITS16,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39773, 63},
    {I_LAR, 2, {REG_GPR|BITS16,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30255, 64},
    {I_LAR, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39779, 65},
    {I_LAR, 2, {REG_GPR|BITS32,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39779, 63},
    {I_LAR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39779, 63},
    {I_LAR, 2, {REG_GPR|BITS32,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30262, 64},
    {I_LAR, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39785, 66},
    {I_LAR, 2, {REG_GPR|BITS64,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39785, 64},
    {I_LAR, 2, {REG_GPR|BITS64,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39785, 64},
    {I_LAR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39785, 64},
    ITEMPLATE_END
};

static const struct itemplate instrux_LDS[] = {
    {I_LDS, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43881, 1},
    {I_LDS, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43886, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_LEA[] = {
    {I_LEA, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43891, 67},
    {I_LEA, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43896, 68},
    {I_LEA, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43901, 69},
    {I_LEA, 2, {REG_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43891, 67},
    {I_LEA, 2, {REG_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43896, 68},
    {I_LEA, 2, {REG_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+43901, 69},
    ITEMPLATE_END
};

static const struct itemplate instrux_LEAVE[] = {
    {I_LEAVE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44153, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_LES[] = {
    {I_LES, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43906, 1},
    {I_LES, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+43911, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_LFENCE[] = {
    {I_LFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39791, 59},
    {I_LFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39791, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_LFS[] = {
    {I_LFS, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39797, 5},
    {I_LFS, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39803, 5},
    {I_LFS, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39809, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LGDT[] = {
    {I_LGDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43916, 25},
    ITEMPLATE_END
};

static const struct itemplate instrux_LGS[] = {
    {I_LGS, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39815, 5},
    {I_LGS, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39821, 5},
    {I_LGS, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39827, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LIDT[] = {
    {I_LIDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43921, 25},
    ITEMPLATE_END
};

static const struct itemplate instrux_LLDT[] = {
    {I_LLDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43926, 70},
    {I_LLDT, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43926, 70},
    {I_LLDT, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43926, 70},
    ITEMPLATE_END
};

static const struct itemplate instrux_LMSW[] = {
    {I_LMSW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43931, 25},
    {I_LMSW, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43931, 25},
    {I_LMSW, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43931, 25},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOADALL[] = {
    {I_LOADALL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45553, 46},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOADALL286[] = {
    {I_LOADALL286, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45557, 71},
    ITEMPLATE_END
};

static const struct itemplate instrux_LODSB[] = {
    {I_LODSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45957, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_LODSD[] = {
    {I_LODSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45561, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_LODSQ[] = {
    {I_LODSQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45565, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LODSW[] = {
    {I_LODSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45569, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOOP[] = {
    {I_LOOP, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43936, 0},
    {I_LOOP, 2, {IMMEDIATE,REG_CX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43941, 1},
    {I_LOOP, 2, {IMMEDIATE,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43946, 5},
    {I_LOOP, 2, {IMMEDIATE,REG_RCX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43951, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOOPE[] = {
    {I_LOOPE, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43956, 0},
    {I_LOOPE, 2, {IMMEDIATE,REG_CX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43961, 1},
    {I_LOOPE, 2, {IMMEDIATE,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43966, 5},
    {I_LOOPE, 2, {IMMEDIATE,REG_RCX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43971, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOOPNE[] = {
    {I_LOOPNE, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43976, 0},
    {I_LOOPNE, 2, {IMMEDIATE,REG_CX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43981, 1},
    {I_LOOPNE, 2, {IMMEDIATE,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43986, 5},
    {I_LOOPNE, 2, {IMMEDIATE,REG_RCX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43991, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOOPNZ[] = {
    {I_LOOPNZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43976, 0},
    {I_LOOPNZ, 2, {IMMEDIATE,REG_CX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43981, 1},
    {I_LOOPNZ, 2, {IMMEDIATE,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43986, 5},
    {I_LOOPNZ, 2, {IMMEDIATE,REG_RCX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43991, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LOOPZ[] = {
    {I_LOOPZ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43956, 0},
    {I_LOOPZ, 2, {IMMEDIATE,REG_CX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43961, 1},
    {I_LOOPZ, 2, {IMMEDIATE,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43966, 5},
    {I_LOOPZ, 2, {IMMEDIATE,REG_RCX,0,0,0}, NO_DECORATOR, nasm_bytecodes+43971, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LSL[] = {
    {I_LSL, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39833, 61},
    {I_LSL, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39833, 62},
    {I_LSL, 2, {REG_GPR|BITS16,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39833, 63},
    {I_LSL, 2, {REG_GPR|BITS16,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30269, 64},
    {I_LSL, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39839, 65},
    {I_LSL, 2, {REG_GPR|BITS32,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39839, 63},
    {I_LSL, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39839, 63},
    {I_LSL, 2, {REG_GPR|BITS32,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30276, 64},
    {I_LSL, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39845, 66},
    {I_LSL, 2, {REG_GPR|BITS64,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39845, 64},
    {I_LSL, 2, {REG_GPR|BITS64,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39845, 64},
    {I_LSL, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39845, 64},
    ITEMPLATE_END
};

static const struct itemplate instrux_LSS[] = {
    {I_LSS, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39851, 5},
    {I_LSS, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39857, 5},
    {I_LSS, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39863, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_LTR[] = {
    {I_LTR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43996, 70},
    {I_LTR, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43996, 70},
    {I_LTR, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43996, 70},
    ITEMPLATE_END
};

static const struct itemplate instrux_MFENCE[] = {
    {I_MFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39869, 59},
    {I_MFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39869, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MONITOR[] = {
    {I_MONITOR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44001, 72},
    {I_MONITOR, 3, {REG_EAX,REG_ECX,REG_EDX,0,0}, NO_DECORATOR, nasm_bytecodes+44001, 73},
    {I_MONITOR, 3, {REG_RAX,REG_ECX,REG_EDX,0,0}, NO_DECORATOR, nasm_bytecodes+44001, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MONITORX[] = {
    {I_MONITORX, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44006, 74},
    {I_MONITORX, 3, {REG_RAX,REG_ECX,REG_EDX,0,0}, NO_DECORATOR, nasm_bytecodes+44006, 59},
    {I_MONITORX, 3, {REG_EAX,REG_ECX,REG_EDX,0,0}, NO_DECORATOR, nasm_bytecodes+44006, 74},
    {I_MONITORX, 3, {REG_AX,REG_ECX,REG_EDX,0,0}, NO_DECORATOR, nasm_bytecodes+44006, 74},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOV[] = {
    {I_MOV, 2, {MEMORY,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44027, 75},
    {I_MOV, 2, {REG_GPR|BITS16,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44011, 0},
    {I_MOV, 2, {REG_GPR|BITS32,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44016, 5},
    {I_MOV, 2, {REG_GPR|BITS64,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44021, 76},
    {I_MOV, 2, {RM_GPR|BITS64,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44026, 7},
    {I_MOV, 2, {REG_SREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44047, 75},
    {I_MOV, 2, {REG_SREG,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44047, 77},
    {I_MOV, 2, {REG_SREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44047, 78},
    {I_MOV, 2, {REG_SREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44031, 76},
    {I_MOV, 2, {REG_SREG,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44036, 0},
    {I_MOV, 2, {REG_SREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44041, 5},
    {I_MOV, 2, {REG_SREG,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44046, 7},
    {I_MOV, 2, {REG_AL,MEM_OFFS,0,0,0}, NO_DECORATOR, nasm_bytecodes+45573, 8},
    {I_MOV, 2, {REG_AX,MEM_OFFS,0,0,0}, NO_DECORATOR, nasm_bytecodes+44051, 8},
    {I_MOV, 2, {REG_EAX,MEM_OFFS,0,0,0}, NO_DECORATOR, nasm_bytecodes+44056, 9},
    {I_MOV, 2, {REG_RAX,MEM_OFFS,0,0,0}, NO_DECORATOR, nasm_bytecodes+44061, 10},
    {I_MOV, 2, {MEM_OFFS,REG_AL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45577, 79},
    {I_MOV, 2, {MEM_OFFS,REG_AX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44066, 79},
    {I_MOV, 2, {MEM_OFFS,REG_EAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44071, 80},
    {I_MOV, 2, {MEM_OFFS,REG_RAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44076, 81},
    {I_MOV, 2, {REG_GPR|BITS32,REG_CREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39875, 82},
    {I_MOV, 2, {REG_GPR|BITS64,REG_CREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39881, 83},
    {I_MOV, 2, {REG_CREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39887, 82},
    {I_MOV, 2, {REG_CREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39893, 83},
    {I_MOV, 2, {REG_GPR|BITS32,REG_DREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39900, 82},
    {I_MOV, 2, {REG_GPR|BITS64,REG_DREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39899, 83},
    {I_MOV, 2, {REG_DREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39906, 82},
    {I_MOV, 2, {REG_DREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39905, 83},
    {I_MOV, 2, {REG_GPR|BITS32,REG_TREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+44081, 19},
    {I_MOV, 2, {REG_TREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44086, 19},
    {I_MOV, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44091, 8},
    {I_MOV, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44092, 0},
    {I_MOV, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39911, 8},
    {I_MOV, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39912, 0},
    {I_MOV, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39917, 9},
    {I_MOV, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39918, 5},
    {I_MOV, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39923, 10},
    {I_MOV, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39924, 7},
    {I_MOV, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45581, 8},
    {I_MOV, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+45581, 0},
    {I_MOV, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44096, 8},
    {I_MOV, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44096, 0},
    {I_MOV, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44101, 9},
    {I_MOV, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44101, 5},
    {I_MOV, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44106, 10},
    {I_MOV, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44106, 7},
    {I_MOV, 2, {REG_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45585, 8},
    {I_MOV, 2, {REG_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44111, 8},
    {I_MOV, 2, {REG_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44116, 9},
    {I_MOV, 2, {REG_GPR|BITS64,UDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+44121, 84},
    {I_MOV, 2, {REG_GPR|BITS64,SDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30298, 84},
    {I_MOV, 2, {REG_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44126, 10},
    {I_MOV, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+39929, 8},
    {I_MOV, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30283, 8},
    {I_MOV, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30290, 9},
    {I_MOV, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30297, 10},
    {I_MOV, 2, {RM_GPR|BITS64,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30297, 7},
    {I_MOV, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39929, 8},
    {I_MOV, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30283, 8},
    {I_MOV, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30290, 9},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVD[] = {
    {I_MOVD, 2, {MMXREG,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39935, 85},
    {I_MOVD, 2, {RM_GPR|BITS32,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39941, 85},
    {I_MOVD, 2, {MMXREG,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30304, 86},
    {I_MOVD, 2, {RM_GPR|BITS64,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+30311, 86},
    {I_MOVD, 2, {MEMORY,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31179, 146},
    {I_MOVD, 2, {XMM_L16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31186, 146},
    {I_MOVD, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31186, 142},
    {I_MOVD, 2, {RM_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31179, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVQ[] = {
    {I_MOVQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+39947, 87},
    {I_MOVQ, 2, {RM_MMX,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39953, 87},
    {I_MOVQ, 2, {MMXREG,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30304, 88},
    {I_MOVQ, 2, {RM_GPR|BITS64,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+30311, 88},
    {I_MOVQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40919, 142},
    {I_MOVQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40925, 142},
    {I_MOVQ, 2, {MEMORY,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40925, 147},
    {I_MOVQ, 2, {XMM_L16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40919, 147},
    {I_MOVQ, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31193, 148},
    {I_MOVQ, 2, {RM_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31200, 148},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSB[] = {
    {I_MOVSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+12158, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSD[] = {
    {I_MOVSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45589, 5},
    {I_MOVSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41477, 142},
    {I_MOVSD, 2, {RM_XMM_L16|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41483, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSQ[] = {
    {I_MOVSQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45593, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSW[] = {
    {I_MOVSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45597, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSX[] = {
    {I_MOVSX, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39959, 53},
    {I_MOVSX, 2, {REG_GPR|BITS16,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39959, 5},
    {I_MOVSX, 2, {REG_GPR|BITS32,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39965, 5},
    {I_MOVSX, 2, {REG_GPR|BITS32,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39971, 5},
    {I_MOVSX, 2, {REG_GPR|BITS64,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39977, 7},
    {I_MOVSX, 2, {REG_GPR|BITS64,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+39983, 7},
    {I_MOVSX, 2, {REG_GPR|BITS64,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44131, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSXD[] = {
    {I_MOVSXD, 2, {REG_GPR|BITS64,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44131, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVZX[] = {
    {I_MOVZX, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39989, 53},
    {I_MOVZX, 2, {REG_GPR|BITS16,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39989, 5},
    {I_MOVZX, 2, {REG_GPR|BITS32,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+39995, 5},
    {I_MOVZX, 2, {REG_GPR|BITS32,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40001, 5},
    {I_MOVZX, 2, {REG_GPR|BITS64,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40007, 7},
    {I_MOVZX, 2, {REG_GPR|BITS64,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40013, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MUL[] = {
    {I_MUL, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45601, 0},
    {I_MUL, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44136, 0},
    {I_MUL, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44141, 5},
    {I_MUL, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44146, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_MWAIT[] = {
    {I_MWAIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44151, 72},
    {I_MWAIT, 2, {REG_EAX,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44151, 72},
    ITEMPLATE_END
};

static const struct itemplate instrux_MWAITX[] = {
    {I_MWAITX, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44156, 74},
    {I_MWAITX, 2, {REG_EAX,REG_ECX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44156, 74},
    ITEMPLATE_END
};

static const struct itemplate instrux_NEG[] = {
    {I_NEG, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44161, 11},
    {I_NEG, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40019, 11},
    {I_NEG, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40025, 12},
    {I_NEG, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40031, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_NOP[] = {
    {I_NOP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44166, 0},
    {I_NOP, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40037, 89},
    {I_NOP, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40043, 89},
    {I_NOP, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40049, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_NOT[] = {
    {I_NOT, 1, {RM_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44171, 11},
    {I_NOT, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40055, 11},
    {I_NOT, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40061, 12},
    {I_NOT, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40067, 13},
    ITEMPLATE_END
};

static const struct itemplate instrux_OR[] = {
    {I_OR, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44176, 3},
    {I_OR, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44177, 0},
    {I_OR, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40073, 3},
    {I_OR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40074, 0},
    {I_OR, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40079, 4},
    {I_OR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40080, 5},
    {I_OR, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40085, 6},
    {I_OR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40086, 7},
    {I_OR, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+37720, 8},
    {I_OR, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+37720, 0},
    {I_OR, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44181, 8},
    {I_OR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44181, 0},
    {I_OR, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44186, 9},
    {I_OR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44186, 5},
    {I_OR, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44191, 10},
    {I_OR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44191, 7},
    {I_OR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30318, 11},
    {I_OR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30325, 12},
    {I_OR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30332, 13},
    {I_OR, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45605, 8},
    {I_OR, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30319, 8},
    {I_OR, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44196, 8},
    {I_OR, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30326, 9},
    {I_OR, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44201, 9},
    {I_OR, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30333, 10},
    {I_OR, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44206, 10},
    {I_OR, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40091, 3},
    {I_OR, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30318, 3},
    {I_OR, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30339, 3},
    {I_OR, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30325, 4},
    {I_OR, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30346, 4},
    {I_OR, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30332, 6},
    {I_OR, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30353, 6},
    {I_OR, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40091, 3},
    {I_OR, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30318, 3},
    {I_OR, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30339, 3},
    {I_OR, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30325, 4},
    {I_OR, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30346, 4},
    {I_OR, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40097, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_OUT[] = {
    {I_OUT, 2, {IMMEDIATE,REG_AL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45609, 52},
    {I_OUT, 2, {IMMEDIATE,REG_AX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44211, 52},
    {I_OUT, 2, {IMMEDIATE,REG_EAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+44216, 53},
    {I_OUT, 2, {REG_DX,REG_AL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44908, 0},
    {I_OUT, 2, {REG_DX,REG_AX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45613, 0},
    {I_OUT, 2, {REG_DX,REG_EAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45617, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_OUTSB[] = {
    {I_OUTSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45960, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_OUTSD[] = {
    {I_OUTSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45621, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_OUTSW[] = {
    {I_OUTSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45625, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_PACKSSDW[] = {
    {I_PACKSSDW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30360, 87},
    {I_PACKSSDW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40943, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PACKSSWB[] = {
    {I_PACKSSWB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30367, 87},
    {I_PACKSSWB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40937, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PACKUSWB[] = {
    {I_PACKUSWB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30374, 87},
    {I_PACKUSWB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40949, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDB[] = {
    {I_PADDB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30381, 87},
    {I_PADDB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40955, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDD[] = {
    {I_PADDD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30388, 87},
    {I_PADDD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40967, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDSB[] = {
    {I_PADDSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30395, 87},
    {I_PADDSB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40985, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDSIW[] = {
    {I_PADDSIW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40103, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDSW[] = {
    {I_PADDSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30402, 87},
    {I_PADDSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40991, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDUSB[] = {
    {I_PADDUSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30409, 87},
    {I_PADDUSB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40997, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDUSW[] = {
    {I_PADDUSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30416, 87},
    {I_PADDUSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41003, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDW[] = {
    {I_PADDW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30423, 87},
    {I_PADDW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40961, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAND[] = {
    {I_PAND, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30430, 87},
    {I_PAND, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41009, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PANDN[] = {
    {I_PANDN, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30437, 87},
    {I_PANDN, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41015, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAUSE[] = {
    {I_PAUSE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45629, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAVEB[] = {
    {I_PAVEB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40109, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAVGUSB[] = {
    {I_PAVGUSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12097, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPEQB[] = {
    {I_PCMPEQB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30444, 87},
    {I_PCMPEQB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41033, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPEQD[] = {
    {I_PCMPEQD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30451, 87},
    {I_PCMPEQD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41045, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPEQW[] = {
    {I_PCMPEQW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30458, 87},
    {I_PCMPEQW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41039, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPGTB[] = {
    {I_PCMPGTB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30465, 87},
    {I_PCMPGTB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41051, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPGTD[] = {
    {I_PCMPGTD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30472, 87},
    {I_PCMPGTD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41063, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPGTW[] = {
    {I_PCMPGTW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30479, 87},
    {I_PCMPGTW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41057, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PDISTIB[] = {
    {I_PDISTIB, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41310, 92},
    ITEMPLATE_END
};

static const struct itemplate instrux_PF2ID[] = {
    {I_PF2ID, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12105, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFACC[] = {
    {I_PFACC, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12113, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFADD[] = {
    {I_PFADD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12121, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFCMPEQ[] = {
    {I_PFCMPEQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12129, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFCMPGE[] = {
    {I_PFCMPGE, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12137, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFCMPGT[] = {
    {I_PFCMPGT, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12145, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFMAX[] = {
    {I_PFMAX, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12153, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFMIN[] = {
    {I_PFMIN, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12161, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFMUL[] = {
    {I_PFMUL, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12169, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRCP[] = {
    {I_PFRCP, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12177, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRCPIT1[] = {
    {I_PFRCPIT1, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12185, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRCPIT2[] = {
    {I_PFRCPIT2, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12193, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRSQIT1[] = {
    {I_PFRSQIT1, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12201, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRSQRT[] = {
    {I_PFRSQRT, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12209, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFSUB[] = {
    {I_PFSUB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12217, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFSUBR[] = {
    {I_PFSUBR, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12225, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PI2FD[] = {
    {I_PI2FD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12233, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMACHRIW[] = {
    {I_PMACHRIW, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41406, 92},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMADDWD[] = {
    {I_PMADDWD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30486, 87},
    {I_PMADDWD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41069, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAGW[] = {
    {I_PMAGW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40115, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHRIW[] = {
    {I_PMULHRIW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40121, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHRWA[] = {
    {I_PMULHRWA, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12241, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHRWC[] = {
    {I_PMULHRWC, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40127, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHW[] = {
    {I_PMULHW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30493, 87},
    {I_PMULHW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41111, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULLW[] = {
    {I_PMULLW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30500, 87},
    {I_PMULLW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41117, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMVGEZB[] = {
    {I_PMVGEZB, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41538, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMVLZB[] = {
    {I_PMVLZB, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41394, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMVNZB[] = {
    {I_PMVNZB, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41376, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMVZB[] = {
    {I_PMVZB, 2, {MMXREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41298, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_POP[] = {
    {I_POP, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45633, 0},
    {I_POP, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45637, 19},
    {I_POP, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45641, 7},
    {I_POP, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44221, 0},
    {I_POP, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44226, 19},
    {I_POP, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44231, 7},
    {I_POP, 1, {REG_ES,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+12534, 1},
    {I_POP, 1, {REG_CS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7495, 93},
    {I_POP, 1, {REG_SS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7621, 1},
    {I_POP, 1, {REG_DS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7765, 1},
    {I_POP, 1, {REG_FS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45645, 5},
    {I_POP, 1, {REG_GS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45649, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPA[] = {
    {I_POPA, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45653, 18},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPAD[] = {
    {I_POPAD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45657, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPAW[] = {
    {I_POPAW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45661, 18},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPF[] = {
    {I_POPF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45665, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPFD[] = {
    {I_POPFD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45669, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPFQ[] = {
    {I_POPFQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45669, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPFW[] = {
    {I_POPFW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45673, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_POR[] = {
    {I_POR, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30507, 87},
    {I_POR, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41129, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCH[] = {
    {I_PREFETCH, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44236, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHW[] = {
    {I_PREFETCHW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44241, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSLLD[] = {
    {I_PSLLD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30514, 87},
    {I_PSLLD, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30521, 34},
    {I_PSLLD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41147, 143},
    {I_PSLLD, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31263, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSLLQ[] = {
    {I_PSLLQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30528, 87},
    {I_PSLLQ, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30535, 34},
    {I_PSLLQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41153, 143},
    {I_PSLLQ, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31270, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSLLW[] = {
    {I_PSLLW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30542, 87},
    {I_PSLLW, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30549, 34},
    {I_PSLLW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41141, 143},
    {I_PSLLW, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31256, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRAD[] = {
    {I_PSRAD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30556, 87},
    {I_PSRAD, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30563, 34},
    {I_PSRAD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41165, 143},
    {I_PSRAD, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31284, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRAW[] = {
    {I_PSRAW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30570, 87},
    {I_PSRAW, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30577, 34},
    {I_PSRAW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41159, 143},
    {I_PSRAW, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31277, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRLD[] = {
    {I_PSRLD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30584, 87},
    {I_PSRLD, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30591, 34},
    {I_PSRLD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41177, 143},
    {I_PSRLD, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31305, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRLQ[] = {
    {I_PSRLQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30598, 87},
    {I_PSRLQ, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30605, 34},
    {I_PSRLQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41183, 143},
    {I_PSRLQ, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31312, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRLW[] = {
    {I_PSRLW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30612, 87},
    {I_PSRLW, 2, {MMXREG,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30619, 34},
    {I_PSRLW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41171, 143},
    {I_PSRLW, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31298, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBB[] = {
    {I_PSUBB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30626, 87},
    {I_PSUBB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41189, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBD[] = {
    {I_PSUBD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30633, 87},
    {I_PSUBD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41201, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBSB[] = {
    {I_PSUBSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30640, 87},
    {I_PSUBSB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41213, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBSIW[] = {
    {I_PSUBSIW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40133, 90},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBSW[] = {
    {I_PSUBSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30647, 87},
    {I_PSUBSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41219, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBUSB[] = {
    {I_PSUBUSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30654, 87},
    {I_PSUBUSB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41225, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBUSW[] = {
    {I_PSUBUSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30661, 87},
    {I_PSUBUSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41231, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBW[] = {
    {I_PSUBW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30668, 87},
    {I_PSUBW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41195, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKHBW[] = {
    {I_PUNPCKHBW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30675, 87},
    {I_PUNPCKHBW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41237, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKHDQ[] = {
    {I_PUNPCKHDQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30682, 87},
    {I_PUNPCKHDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41249, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKHWD[] = {
    {I_PUNPCKHWD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30689, 87},
    {I_PUNPCKHWD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41243, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKLBW[] = {
    {I_PUNPCKLBW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30696, 87},
    {I_PUNPCKLBW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41261, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKLDQ[] = {
    {I_PUNPCKLDQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30703, 87},
    {I_PUNPCKLDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41273, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKLWD[] = {
    {I_PUNPCKLWD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30710, 87},
    {I_PUNPCKLWD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41267, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSH[] = {
    {I_PUSH, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45677, 0},
    {I_PUSH, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45681, 19},
    {I_PUSH, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45685, 7},
    {I_PUSH, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44246, 0},
    {I_PUSH, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44251, 19},
    {I_PUSH, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44256, 7},
    {I_PUSH, 1, {REG_ES,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+12502, 1},
    {I_PUSH, 1, {REG_CS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7477, 1},
    {I_PUSH, 1, {REG_SS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7603, 1},
    {I_PUSH, 1, {REG_DS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+7747, 1},
    {I_PUSH, 1, {REG_FS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45689, 5},
    {I_PUSH, 1, {REG_GS,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45693, 5},
    {I_PUSH, 1, {IMMEDIATE|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44282, 35},
    {I_PUSH, 1, {SBYTEWORD|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44261, 94},
    {I_PUSH, 1, {IMMEDIATE|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44266, 94},
    {I_PUSH, 1, {SBYTEDWORD|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44271, 95},
    {I_PUSH, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44276, 95},
    {I_PUSH, 1, {SBYTEDWORD|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44271, 96},
    {I_PUSH, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44276, 96},
    {I_PUSH, 1, {SBYTEDWORD|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44281, 97},
    {I_PUSH, 1, {IMMEDIATE|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44286, 97},
    {I_PUSH, 1, {SBYTEDWORD|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44281, 97},
    {I_PUSH, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44286, 97},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHA[] = {
    {I_PUSHA, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45697, 18},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHAD[] = {
    {I_PUSHAD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45701, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHAW[] = {
    {I_PUSHAW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45705, 18},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHF[] = {
    {I_PUSHF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45709, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHFD[] = {
    {I_PUSHFD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45713, 19},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHFQ[] = {
    {I_PUSHFQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45713, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUSHFW[] = {
    {I_PUSHFW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45717, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_PXOR[] = {
    {I_PXOR, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+30717, 87},
    {I_PXOR, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41285, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_RCL[] = {
    {I_RCL, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45721, 0},
    {I_RCL, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45725, 0},
    {I_RCL, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44291, 35},
    {I_RCL, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44296, 0},
    {I_RCL, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44301, 0},
    {I_RCL, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40139, 35},
    {I_RCL, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44306, 5},
    {I_RCL, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44311, 5},
    {I_RCL, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40145, 5},
    {I_RCL, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44316, 7},
    {I_RCL, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44321, 7},
    {I_RCL, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40151, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_RCR[] = {
    {I_RCR, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45729, 0},
    {I_RCR, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45733, 0},
    {I_RCR, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44326, 35},
    {I_RCR, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44331, 0},
    {I_RCR, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44336, 0},
    {I_RCR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40157, 35},
    {I_RCR, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44341, 5},
    {I_RCR, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44346, 5},
    {I_RCR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40163, 5},
    {I_RCR, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44351, 7},
    {I_RCR, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44356, 7},
    {I_RCR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40169, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDSHR[] = {
    {I_RDSHR, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40175, 98},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDMSR[] = {
    {I_RDMSR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45737, 99},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDPMC[] = {
    {I_RDPMC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45741, 89},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDTSC[] = {
    {I_RDTSC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45745, 28},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDTSCP[] = {
    {I_RDTSCP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44361, 100},
    ITEMPLATE_END
};

static const struct itemplate instrux_RET[] = {
    {I_RET, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45766, 21},
    {I_RET, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44387, 101},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETF[] = {
    {I_RETF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45770, 0},
    {I_RETF, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44392, 75},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETN[] = {
    {I_RETN, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45766, 21},
    {I_RETN, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44387, 101},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETW[] = {
    {I_RETW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45749, 21},
    {I_RETW, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44387, 101},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETFW[] = {
    {I_RETFW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45753, 0},
    {I_RETFW, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44366, 75},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETNW[] = {
    {I_RETNW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45749, 21},
    {I_RETNW, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44371, 101},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETD[] = {
    {I_RETD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45757, 22},
    {I_RETD, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44376, 102},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETFD[] = {
    {I_RETFD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45761, 0},
    {I_RETFD, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44381, 75},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETND[] = {
    {I_RETND, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45757, 22},
    {I_RETND, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44376, 102},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETQ[] = {
    {I_RETQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45765, 24},
    {I_RETQ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44386, 103},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETFQ[] = {
    {I_RETFQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45769, 7},
    {I_RETFQ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44391, 104},
    ITEMPLATE_END
};

static const struct itemplate instrux_RETNQ[] = {
    {I_RETNQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45765, 24},
    {I_RETNQ, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44386, 103},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROL[] = {
    {I_ROL, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45773, 0},
    {I_ROL, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45777, 0},
    {I_ROL, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44396, 35},
    {I_ROL, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44401, 0},
    {I_ROL, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44406, 0},
    {I_ROL, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40181, 35},
    {I_ROL, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44411, 5},
    {I_ROL, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44416, 5},
    {I_ROL, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40187, 5},
    {I_ROL, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44421, 7},
    {I_ROL, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44426, 7},
    {I_ROL, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40193, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROR[] = {
    {I_ROR, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45781, 0},
    {I_ROR, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45785, 0},
    {I_ROR, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44431, 35},
    {I_ROR, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44436, 0},
    {I_ROR, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44441, 0},
    {I_ROR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40199, 35},
    {I_ROR, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44446, 5},
    {I_ROR, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44451, 5},
    {I_ROR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40205, 5},
    {I_ROR, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44456, 7},
    {I_ROR, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44461, 7},
    {I_ROR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40211, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDM[] = {
    {I_RDM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44949, 33},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSDC[] = {
    {I_RSDC, 2, {REG_SREG,MEMORY|BITS80,0,0,0}, NO_DECORATOR, nasm_bytecodes+41658, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSLDT[] = {
    {I_RSLDT, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44466, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSM[] = {
    {I_RSM, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45789, 106},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSTS[] = {
    {I_RSTS, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44471, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_SAHF[] = {
    {I_SAHF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+12126, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_SAL[] = {
    {I_SAL, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45793, 0},
    {I_SAL, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45797, 0},
    {I_SAL, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44476, 35},
    {I_SAL, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44481, 0},
    {I_SAL, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44486, 0},
    {I_SAL, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40217, 35},
    {I_SAL, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44491, 5},
    {I_SAL, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44496, 5},
    {I_SAL, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40223, 5},
    {I_SAL, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44501, 7},
    {I_SAL, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44506, 7},
    {I_SAL, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40229, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SALC[] = {
    {I_SALC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44898, 107},
    ITEMPLATE_END
};

static const struct itemplate instrux_SAR[] = {
    {I_SAR, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45801, 0},
    {I_SAR, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45805, 0},
    {I_SAR, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44511, 35},
    {I_SAR, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44516, 0},
    {I_SAR, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44521, 0},
    {I_SAR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40235, 35},
    {I_SAR, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44526, 5},
    {I_SAR, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44531, 5},
    {I_SAR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40241, 5},
    {I_SAR, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44536, 7},
    {I_SAR, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44541, 7},
    {I_SAR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40247, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SBB[] = {
    {I_SBB, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44546, 3},
    {I_SBB, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44547, 0},
    {I_SBB, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40253, 3},
    {I_SBB, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40254, 0},
    {I_SBB, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40259, 4},
    {I_SBB, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40260, 5},
    {I_SBB, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40265, 6},
    {I_SBB, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40266, 7},
    {I_SBB, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+32309, 8},
    {I_SBB, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+32309, 0},
    {I_SBB, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44551, 8},
    {I_SBB, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44551, 0},
    {I_SBB, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44556, 9},
    {I_SBB, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44556, 5},
    {I_SBB, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44561, 10},
    {I_SBB, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44561, 7},
    {I_SBB, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30724, 11},
    {I_SBB, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30731, 12},
    {I_SBB, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30738, 13},
    {I_SBB, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45809, 8},
    {I_SBB, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30725, 8},
    {I_SBB, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44566, 8},
    {I_SBB, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30732, 9},
    {I_SBB, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44571, 9},
    {I_SBB, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30739, 10},
    {I_SBB, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44576, 10},
    {I_SBB, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40271, 3},
    {I_SBB, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30724, 3},
    {I_SBB, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30745, 3},
    {I_SBB, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30731, 4},
    {I_SBB, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30752, 4},
    {I_SBB, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30738, 6},
    {I_SBB, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30759, 6},
    {I_SBB, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40271, 3},
    {I_SBB, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30724, 3},
    {I_SBB, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30745, 3},
    {I_SBB, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30731, 4},
    {I_SBB, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30752, 4},
    {I_SBB, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40277, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_SCASB[] = {
    {I_SCASB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45813, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_SCASD[] = {
    {I_SCASD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44581, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_SCASQ[] = {
    {I_SCASQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44586, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SCASW[] = {
    {I_SCASW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44591, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_SFENCE[] = {
    {I_SFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40283, 59},
    {I_SFENCE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40283, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_SGDT[] = {
    {I_SGDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44596, 108},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHL[] = {
    {I_SHL, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45793, 0},
    {I_SHL, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45797, 0},
    {I_SHL, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44476, 35},
    {I_SHL, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44481, 0},
    {I_SHL, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44486, 0},
    {I_SHL, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40217, 35},
    {I_SHL, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44491, 5},
    {I_SHL, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44496, 5},
    {I_SHL, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40223, 5},
    {I_SHL, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44501, 7},
    {I_SHL, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44506, 7},
    {I_SHL, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40229, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHLD[] = {
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30766, 109},
    {I_SHLD, 3, {REG_GPR|BITS16,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30766, 109},
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30773, 109},
    {I_SHLD, 3, {REG_GPR|BITS32,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30773, 109},
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30780, 110},
    {I_SHLD, 3, {REG_GPR|BITS64,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30780, 110},
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS16,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40289, 9},
    {I_SHLD, 3, {REG_GPR|BITS16,REG_GPR|BITS16,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40289, 5},
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS32,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40295, 9},
    {I_SHLD, 3, {REG_GPR|BITS32,REG_GPR|BITS32,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40295, 5},
    {I_SHLD, 3, {MEMORY,REG_GPR|BITS64,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40301, 10},
    {I_SHLD, 3, {REG_GPR|BITS64,REG_GPR|BITS64,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40301, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHR[] = {
    {I_SHR, 2, {RM_GPR|BITS8,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45817, 0},
    {I_SHR, 2, {RM_GPR|BITS8,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+45821, 0},
    {I_SHR, 2, {RM_GPR|BITS8,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44601, 35},
    {I_SHR, 2, {RM_GPR|BITS16,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44606, 0},
    {I_SHR, 2, {RM_GPR|BITS16,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44611, 0},
    {I_SHR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40307, 35},
    {I_SHR, 2, {RM_GPR|BITS32,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44616, 5},
    {I_SHR, 2, {RM_GPR|BITS32,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44621, 5},
    {I_SHR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40313, 5},
    {I_SHR, 2, {RM_GPR|BITS64,UNITY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44626, 7},
    {I_SHR, 2, {RM_GPR|BITS64,REG_CL,0,0,0}, NO_DECORATOR, nasm_bytecodes+44631, 7},
    {I_SHR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40319, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHRD[] = {
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30787, 109},
    {I_SHRD, 3, {REG_GPR|BITS16,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30787, 109},
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30794, 109},
    {I_SHRD, 3, {REG_GPR|BITS32,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30794, 109},
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30801, 110},
    {I_SHRD, 3, {REG_GPR|BITS64,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+30801, 110},
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS16,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40325, 9},
    {I_SHRD, 3, {REG_GPR|BITS16,REG_GPR|BITS16,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40325, 5},
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS32,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40331, 9},
    {I_SHRD, 3, {REG_GPR|BITS32,REG_GPR|BITS32,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40331, 5},
    {I_SHRD, 3, {MEMORY,REG_GPR|BITS64,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40337, 10},
    {I_SHRD, 3, {REG_GPR|BITS64,REG_GPR|BITS64,REG_CL,0,0}, NO_DECORATOR, nasm_bytecodes+40337, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SIDT[] = {
    {I_SIDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44636, 108},
    ITEMPLATE_END
};

static const struct itemplate instrux_SLDT[] = {
    {I_SLDT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40362, 108},
    {I_SLDT, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40362, 108},
    {I_SLDT, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40343, 108},
    {I_SLDT, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40349, 5},
    {I_SLDT, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40355, 7},
    {I_SLDT, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40361, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SKINIT[] = {
    {I_SKINIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44641, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SMI[] = {
    {I_SMI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45939, 111},
    ITEMPLATE_END
};

static const struct itemplate instrux_SMINT[] = {
    {I_SMINT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45825, 33},
    ITEMPLATE_END
};

static const struct itemplate instrux_SMINTOLD[] = {
    {I_SMINTOLD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45829, 112},
    ITEMPLATE_END
};

static const struct itemplate instrux_SMSW[] = {
    {I_SMSW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40380, 108},
    {I_SMSW, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40380, 108},
    {I_SMSW, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40367, 108},
    {I_SMSW, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40373, 5},
    {I_SMSW, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40379, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_STC[] = {
    {I_STC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44363, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_STD[] = {
    {I_STD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45963, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_STI[] = {
    {I_STI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44158, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_STOSB[] = {
    {I_STOSB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+12230, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_STOSD[] = {
    {I_STOSD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45833, 5},
    ITEMPLATE_END
};

static const struct itemplate instrux_STOSQ[] = {
    {I_STOSQ, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45837, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_STOSW[] = {
    {I_STOSW, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45841, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_STR[] = {
    {I_STR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40398, 62},
    {I_STR, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40398, 62},
    {I_STR, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40385, 62},
    {I_STR, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40391, 63},
    {I_STR, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40397, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SUB[] = {
    {I_SUB, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44646, 3},
    {I_SUB, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44647, 0},
    {I_SUB, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40403, 3},
    {I_SUB, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40404, 0},
    {I_SUB, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40409, 4},
    {I_SUB, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40410, 5},
    {I_SUB, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40415, 6},
    {I_SUB, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40416, 7},
    {I_SUB, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+38077, 8},
    {I_SUB, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38077, 0},
    {I_SUB, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44651, 8},
    {I_SUB, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44651, 0},
    {I_SUB, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44656, 9},
    {I_SUB, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44656, 5},
    {I_SUB, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44661, 10},
    {I_SUB, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44661, 7},
    {I_SUB, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30808, 11},
    {I_SUB, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30815, 12},
    {I_SUB, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30822, 13},
    {I_SUB, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45845, 8},
    {I_SUB, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30809, 8},
    {I_SUB, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44666, 8},
    {I_SUB, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30816, 9},
    {I_SUB, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44671, 9},
    {I_SUB, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30823, 10},
    {I_SUB, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44676, 10},
    {I_SUB, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40421, 3},
    {I_SUB, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30808, 3},
    {I_SUB, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30829, 3},
    {I_SUB, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30815, 4},
    {I_SUB, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30836, 4},
    {I_SUB, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30822, 6},
    {I_SUB, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30843, 6},
    {I_SUB, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40421, 3},
    {I_SUB, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30808, 3},
    {I_SUB, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30829, 3},
    {I_SUB, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30815, 4},
    {I_SUB, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30836, 4},
    {I_SUB, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40427, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_SVDC[] = {
    {I_SVDC, 2, {MEMORY|BITS80,REG_SREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+31398, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_SVLDT[] = {
    {I_SVLDT, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44681, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_SVTS[] = {
    {I_SVTS, 1, {MEMORY|BITS80,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44686, 105},
    ITEMPLATE_END
};

static const struct itemplate instrux_SWAPGS[] = {
    {I_SWAPGS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44691, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_SYSCALL[] = {
    {I_SYSCALL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45557, 113},
    ITEMPLATE_END
};

static const struct itemplate instrux_SYSENTER[] = {
    {I_SYSENTER, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45849, 89},
    ITEMPLATE_END
};

static const struct itemplate instrux_SYSEXIT[] = {
    {I_SYSEXIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45853, 114},
    ITEMPLATE_END
};

static const struct itemplate instrux_SYSRET[] = {
    {I_SYSRET, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45553, 115},
    ITEMPLATE_END
};

static const struct itemplate instrux_TEST[] = {
    {I_TEST, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+45857, 8},
    {I_TEST, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+45857, 0},
    {I_TEST, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44696, 8},
    {I_TEST, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44696, 0},
    {I_TEST, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44701, 9},
    {I_TEST, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44701, 5},
    {I_TEST, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44706, 10},
    {I_TEST, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44706, 7},
    {I_TEST, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+45861, 8},
    {I_TEST, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44711, 8},
    {I_TEST, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44716, 9},
    {I_TEST, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44721, 10},
    {I_TEST, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45865, 8},
    {I_TEST, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44726, 8},
    {I_TEST, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44731, 9},
    {I_TEST, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44736, 10},
    {I_TEST, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44741, 8},
    {I_TEST, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40433, 8},
    {I_TEST, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40439, 9},
    {I_TEST, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40445, 10},
    {I_TEST, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44741, 8},
    {I_TEST, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40433, 8},
    {I_TEST, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40439, 9},
    ITEMPLATE_END
};

static const struct itemplate instrux_UD0[] = {
    {I_UD0, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45869, 116},
    {I_UD0, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40451, 35},
    {I_UD0, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40457, 35},
    {I_UD0, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40463, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_UD1[] = {
    {I_UD1, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40469, 35},
    {I_UD1, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40475, 35},
    {I_UD1, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40481, 35},
    {I_UD1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45873, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_UD2B[] = {
    {I_UD2B, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45873, 35},
    {I_UD2B, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40469, 35},
    {I_UD2B, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40475, 35},
    {I_UD2B, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40481, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_UD2[] = {
    {I_UD2, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45877, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_UD2A[] = {
    {I_UD2A, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45877, 35},
    ITEMPLATE_END
};

static const struct itemplate instrux_UMOV[] = {
    {I_UMOV, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40487, 117},
    {I_UMOV, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40487, 111},
    {I_UMOV, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30850, 117},
    {I_UMOV, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30850, 111},
    {I_UMOV, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30857, 117},
    {I_UMOV, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30857, 111},
    {I_UMOV, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40493, 117},
    {I_UMOV, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40493, 111},
    {I_UMOV, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30864, 117},
    {I_UMOV, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30864, 111},
    {I_UMOV, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30871, 117},
    {I_UMOV, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30871, 111},
    ITEMPLATE_END
};

static const struct itemplate instrux_VERR[] = {
    {I_VERR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44746, 62},
    {I_VERR, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44746, 62},
    {I_VERR, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44746, 62},
    ITEMPLATE_END
};

static const struct itemplate instrux_VERW[] = {
    {I_VERW, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44751, 62},
    {I_VERW, 1, {MEMORY|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44751, 62},
    {I_VERW, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44751, 62},
    ITEMPLATE_END
};

static const struct itemplate instrux_FWAIT[] = {
    {I_FWAIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45455, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_WBINVD[] = {
    {I_WBINVD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44917, 54},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRSHR[] = {
    {I_WRSHR, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40499, 98},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRMSR[] = {
    {I_WRMSR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45881, 99},
    ITEMPLATE_END
};

static const struct itemplate instrux_XADD[] = {
    {I_XADD, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40505, 118},
    {I_XADD, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40506, 20},
    {I_XADD, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30878, 118},
    {I_XADD, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30879, 20},
    {I_XADD, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30885, 118},
    {I_XADD, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30886, 20},
    {I_XADD, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30892, 6},
    {I_XADD, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30893, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_XBTS[] = {
    {I_XBTS, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40511, 119},
    {I_XBTS, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40511, 111},
    {I_XBTS, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40517, 120},
    {I_XBTS, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40517, 111},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCHG[] = {
    {I_XCHG, 2, {REG_AX,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+45885, 0},
    {I_XCHG, 2, {REG_EAX,REG32NA,0,0,0}, NO_DECORATOR, nasm_bytecodes+45889, 5},
    {I_XCHG, 2, {REG_RAX,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+45893, 7},
    {I_XCHG, 2, {REG_GPR|BITS16,REG_AX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45897, 0},
    {I_XCHG, 2, {REG32NA,REG_EAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45901, 5},
    {I_XCHG, 2, {REG_GPR|BITS64,REG_RAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45905, 7},
    {I_XCHG, 2, {REG_EAX,REG_EAX,0,0,0}, NO_DECORATOR, nasm_bytecodes+45909, 19},
    {I_XCHG, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44756, 3},
    {I_XCHG, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44757, 0},
    {I_XCHG, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40523, 3},
    {I_XCHG, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40524, 0},
    {I_XCHG, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40529, 4},
    {I_XCHG, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40530, 5},
    {I_XCHG, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+40535, 6},
    {I_XCHG, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40536, 7},
    {I_XCHG, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44761, 3},
    {I_XCHG, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44762, 0},
    {I_XCHG, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40541, 3},
    {I_XCHG, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40542, 0},
    {I_XCHG, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40547, 4},
    {I_XCHG, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40548, 5},
    {I_XCHG, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40553, 6},
    {I_XCHG, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40554, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_XLATB[] = {
    {I_XLATB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41930, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_XLAT[] = {
    {I_XLAT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41930, 0},
    ITEMPLATE_END
};

static const struct itemplate instrux_XOR[] = {
    {I_XOR, 2, {MEMORY,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44766, 3},
    {I_XOR, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+44767, 0},
    {I_XOR, 2, {MEMORY,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40559, 3},
    {I_XOR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40560, 0},
    {I_XOR, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40565, 4},
    {I_XOR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40566, 5},
    {I_XOR, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40571, 6},
    {I_XOR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40572, 7},
    {I_XOR, 2, {REG_GPR|BITS8,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+37517, 8},
    {I_XOR, 2, {REG_GPR|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+37517, 0},
    {I_XOR, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44771, 8},
    {I_XOR, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+44771, 0},
    {I_XOR, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44776, 9},
    {I_XOR, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+44776, 5},
    {I_XOR, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+44781, 10},
    {I_XOR, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+44781, 7},
    {I_XOR, 2, {RM_GPR|BITS16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30899, 11},
    {I_XOR, 2, {RM_GPR|BITS32,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30906, 12},
    {I_XOR, 2, {RM_GPR|BITS64,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+30913, 13},
    {I_XOR, 2, {REG_AL,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+45913, 8},
    {I_XOR, 2, {REG_AX,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30900, 8},
    {I_XOR, 2, {REG_AX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44786, 8},
    {I_XOR, 2, {REG_EAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30907, 9},
    {I_XOR, 2, {REG_EAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44791, 9},
    {I_XOR, 2, {REG_RAX,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30914, 10},
    {I_XOR, 2, {REG_RAX,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+44796, 10},
    {I_XOR, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40577, 3},
    {I_XOR, 2, {RM_GPR|BITS16,SBYTEWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30899, 3},
    {I_XOR, 2, {RM_GPR|BITS16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30920, 3},
    {I_XOR, 2, {RM_GPR|BITS32,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30906, 4},
    {I_XOR, 2, {RM_GPR|BITS32,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30927, 4},
    {I_XOR, 2, {RM_GPR|BITS64,SBYTEDWORD,0,0,0}, NO_DECORATOR, nasm_bytecodes+30913, 6},
    {I_XOR, 2, {RM_GPR|BITS64,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+30934, 6},
    {I_XOR, 2, {MEMORY,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+40577, 3},
    {I_XOR, 2, {MEMORY,SBYTEWORD|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30899, 3},
    {I_XOR, 2, {MEMORY,IMMEDIATE|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30920, 3},
    {I_XOR, 2, {MEMORY,SBYTEDWORD|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30906, 4},
    {I_XOR, 2, {MEMORY,IMMEDIATE|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30927, 4},
    {I_XOR, 2, {RM_GPR|BITS8,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+40583, 14},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDPS[] = {
    {I_ADDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40595, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDSS[] = {
    {I_ADDSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40601, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_ANDNPS[] = {
    {I_ANDNPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40607, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_ANDPS[] = {
    {I_ANDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40613, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPEQPS[] = {
    {I_CMPEQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12249, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPEQSS[] = {
    {I_CMPEQSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12257, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLEPS[] = {
    {I_CMPLEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12265, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLESS[] = {
    {I_CMPLESS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12273, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLTPS[] = {
    {I_CMPLTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12281, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLTSS[] = {
    {I_CMPLTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12289, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNEQPS[] = {
    {I_CMPNEQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12297, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNEQSS[] = {
    {I_CMPNEQSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12305, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLEPS[] = {
    {I_CMPNLEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12313, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLESS[] = {
    {I_CMPNLESS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12321, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLTPS[] = {
    {I_CMPNLTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12329, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLTSS[] = {
    {I_CMPNLTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12337, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPORDPS[] = {
    {I_CMPORDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12345, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPORDSS[] = {
    {I_CMPORDSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12353, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPUNORDPS[] = {
    {I_CMPUNORDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12361, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPUNORDSS[] = {
    {I_CMPUNORDSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12369, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPPS[] = {
    {I_CMPPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+30997, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPSS[] = {
    {I_CMPSS, 3, {XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+31004, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_COMISS[] = {
    {I_COMISS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40619, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPI2PS[] = {
    {I_CVTPI2PS, 2, {XMM_L16,RM_MMX|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40625, 124},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPS2PI[] = {
    {I_CVTPS2PI, 2, {MMXREG,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40631, 124},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSI2SS[] = {
    {I_CVTSI2SS, 2, {XMM_L16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31012, 125},
    {I_CVTSI2SS, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31012, 125},
    {I_CVTSI2SS, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31011, 126},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSS2SI[] = {
    {I_CVTSS2SI, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31019, 125},
    {I_CVTSS2SI, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31019, 125},
    {I_CVTSS2SI, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31018, 127},
    {I_CVTSS2SI, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31018, 127},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTPS2PI[] = {
    {I_CVTTPS2PI, 2, {MMXREG,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40637, 128},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTSS2SI[] = {
    {I_CVTTSS2SI, 2, {REG_GPR|BITS32,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31026, 125},
    {I_CVTTSS2SI, 2, {REG_GPR|BITS64,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31025, 127},
    ITEMPLATE_END
};

static const struct itemplate instrux_DIVPS[] = {
    {I_DIVPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40643, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_DIVSS[] = {
    {I_DIVSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40649, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_LDMXCSR[] = {
    {I_LDMXCSR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40655, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MAXPS[] = {
    {I_MAXPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40661, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MAXSS[] = {
    {I_MAXSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40667, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MINPS[] = {
    {I_MINPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40673, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MINSS[] = {
    {I_MINSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40679, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVAPS[] = {
    {I_MOVAPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40685, 123},
    {I_MOVAPS, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40691, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVHPS[] = {
    {I_MOVHPS, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40697, 123},
    {I_MOVHPS, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40703, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVLHPS[] = {
    {I_MOVLHPS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40697, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVLPS[] = {
    {I_MOVLPS, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+40493, 123},
    {I_MOVLPS, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40709, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVHLPS[] = {
    {I_MOVHLPS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40493, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVMSKPS[] = {
    {I_MOVMSKPS, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40715, 123},
    {I_MOVMSKPS, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31032, 129},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTPS[] = {
    {I_MOVNTPS, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40721, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSS[] = {
    {I_MOVSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40727, 123},
    {I_MOVSS, 2, {RM_XMM_L16|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40733, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVUPS[] = {
    {I_MOVUPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40739, 123},
    {I_MOVUPS, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40745, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MULPS[] = {
    {I_MULPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40751, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_MULSS[] = {
    {I_MULSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40757, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_ORPS[] = {
    {I_ORPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40763, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_RCPPS[] = {
    {I_RCPPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40769, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_RCPSS[] = {
    {I_RCPSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40775, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSQRTPS[] = {
    {I_RSQRTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40781, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSQRTSS[] = {
    {I_RSQRTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40787, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHUFPS[] = {
    {I_SHUFPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+31039, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_SQRTPS[] = {
    {I_SQRTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40793, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_SQRTSS[] = {
    {I_SQRTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40799, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_STMXCSR[] = {
    {I_STMXCSR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40805, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_SUBPS[] = {
    {I_SUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40811, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_SUBSS[] = {
    {I_SUBSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40817, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_UCOMISS[] = {
    {I_UCOMISS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+40823, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_UNPCKHPS[] = {
    {I_UNPCKHPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40829, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_UNPCKLPS[] = {
    {I_UNPCKLPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40835, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_XORPS[] = {
    {I_XORPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40841, 123},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXRSTOR[] = {
    {I_FXRSTOR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31047, 130},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXRSTOR64[] = {
    {I_FXRSTOR64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31046, 131},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXSAVE[] = {
    {I_FXSAVE, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31054, 130},
    ITEMPLATE_END
};

static const struct itemplate instrux_FXSAVE64[] = {
    {I_FXSAVE64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31053, 131},
    ITEMPLATE_END
};

static const struct itemplate instrux_XGETBV[] = {
    {I_XGETBV, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44806, 132},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSETBV[] = {
    {I_XSETBV, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44811, 133},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVE[] = {
    {I_XSAVE, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31061, 132},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVE64[] = {
    {I_XSAVE64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31060, 134},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVEC[] = {
    {I_XSAVEC, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31068, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVEC64[] = {
    {I_XSAVEC64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31067, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVEOPT[] = {
    {I_XSAVEOPT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31075, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVEOPT64[] = {
    {I_XSAVEOPT64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31074, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVES[] = {
    {I_XSAVES, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31082, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSAVES64[] = {
    {I_XSAVES64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31081, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_XRSTOR[] = {
    {I_XRSTOR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31089, 132},
    ITEMPLATE_END
};

static const struct itemplate instrux_XRSTOR64[] = {
    {I_XRSTOR64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31088, 134},
    ITEMPLATE_END
};

static const struct itemplate instrux_XRSTORS[] = {
    {I_XRSTORS, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31096, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_XRSTORS64[] = {
    {I_XRSTORS64, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31095, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHNTA[] = {
    {I_PREFETCHNTA, 1, {MEMORY|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42000, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHT0[] = {
    {I_PREFETCHT0, 1, {MEMORY|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42018, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHT1[] = {
    {I_PREFETCHT1, 1, {MEMORY|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42036, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHT2[] = {
    {I_PREFETCHT2, 1, {MEMORY|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42054, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_MASKMOVQ[] = {
    {I_MASKMOVQ, 2, {MMXREG,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+40847, 138},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTQ[] = {
    {I_MOVNTQ, 2, {MEMORY,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+40853, 139},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAVGB[] = {
    {I_PAVGB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31102, 139},
    {I_PAVGB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41021, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PAVGW[] = {
    {I_PAVGW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31109, 139},
    {I_PAVGW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41027, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PEXTRW[] = {
    {I_PEXTRW, 3, {REG_GPR|BITS32,MMXREG,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31116, 140},
    {I_PEXTRW, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31207, 150},
    {I_PEXTRW, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31207, 151},
    {I_PEXTRW, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4277, 171},
    {I_PEXTRW, 3, {MEMORY|BITS16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4277, 171},
    {I_PEXTRW, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4276, 172},
    ITEMPLATE_END
};

static const struct itemplate instrux_PINSRW[] = {
    {I_PINSRW, 3, {MMXREG,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31123, 140},
    {I_PINSRW, 3, {MMXREG,RM_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31123, 140},
    {I_PINSRW, 3, {MMXREG,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31123, 140},
    {I_PINSRW, 3, {XMM_L16,REG_GPR|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31214, 150},
    {I_PINSRW, 3, {XMM_L16,REG_GPR|BITS32,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31214, 150},
    {I_PINSRW, 3, {XMM_L16,REG_GPR|BITS64,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31214, 151},
    {I_PINSRW, 3, {XMM_L16,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31214, 150},
    {I_PINSRW, 3, {XMM_L16,MEMORY|BITS16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31214, 150},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXSW[] = {
    {I_PMAXSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31130, 139},
    {I_PMAXSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41075, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXUB[] = {
    {I_PMAXUB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31137, 139},
    {I_PMAXUB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41081, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINSW[] = {
    {I_PMINSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31144, 139},
    {I_PMINSW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41087, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINUB[] = {
    {I_PMINUB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31151, 139},
    {I_PMINUB, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41093, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVMSKB[] = {
    {I_PMOVMSKB, 2, {REG_GPR|BITS32,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+40859, 138},
    {I_PMOVMSKB, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41099, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHUW[] = {
    {I_PMULHUW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31158, 139},
    {I_PMULHUW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41105, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSADBW[] = {
    {I_PSADBW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31165, 139},
    {I_PSADBW, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41135, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSHUFW[] = {
    {I_PSHUFW, 3, {MMXREG,RM_MMX,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+12377, 141},
    ITEMPLATE_END
};

static const struct itemplate instrux_PF2IW[] = {
    {I_PF2IW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12385, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFNACC[] = {
    {I_PFNACC, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12393, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFPNACC[] = {
    {I_PFPNACC, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12401, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PI2FW[] = {
    {I_PI2FW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12409, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSWAPD[] = {
    {I_PSWAPD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12417, 91},
    ITEMPLATE_END
};

static const struct itemplate instrux_MASKMOVDQU[] = {
    {I_MASKMOVDQU, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40865, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLFLUSH[] = {
    {I_CLFLUSH, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40871, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTDQ[] = {
    {I_MOVNTDQ, 2, {MEMORY,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40877, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTI[] = {
    {I_MOVNTI, 2, {MEMORY,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31173, 144},
    {I_MOVNTI, 2, {MEMORY,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31172, 145},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTPD[] = {
    {I_MOVNTPD, 2, {MEMORY,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40883, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDQA[] = {
    {I_MOVDQA, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40889, 143},
    {I_MOVDQA, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40895, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDQU[] = {
    {I_MOVDQU, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+40901, 143},
    {I_MOVDQU, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40907, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDQ2Q[] = {
    {I_MOVDQ2Q, 2, {MMXREG,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40913, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVQ2DQ[] = {
    {I_MOVQ2DQ, 2, {XMM_L16,MMXREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+40931, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_PADDQ[] = {
    {I_PADDQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+40973, 149},
    {I_PADDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+40979, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULUDQ[] = {
    {I_PMULUDQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31221, 143},
    {I_PMULUDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41123, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSHUFD[] = {
    {I_PSHUFD, 3, {XMM_L16,XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31228, 150},
    {I_PSHUFD, 3, {XMM_L16,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31228, 152},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSHUFHW[] = {
    {I_PSHUFHW, 3, {XMM_L16,XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31235, 150},
    {I_PSHUFHW, 3, {XMM_L16,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31235, 152},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSHUFLW[] = {
    {I_PSHUFLW, 3, {XMM_L16,XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31242, 150},
    {I_PSHUFLW, 3, {XMM_L16,MEMORY,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+31242, 152},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSLLDQ[] = {
    {I_PSLLDQ, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31249, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSRLDQ[] = {
    {I_PSRLDQ, 2, {XMM_L16,IMMEDIATE,0,0,0}, NO_DECORATOR, nasm_bytecodes+31291, 153},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSUBQ[] = {
    {I_PSUBQ, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31319, 143},
    {I_PSUBQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41207, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKHQDQ[] = {
    {I_PUNPCKHQDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41255, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_PUNPCKLQDQ[] = {
    {I_PUNPCKLQDQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41279, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDPD[] = {
    {I_ADDPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41291, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDSD[] = {
    {I_ADDSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41297, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_ANDNPD[] = {
    {I_ANDNPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41303, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_ANDPD[] = {
    {I_ANDPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41309, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPEQPD[] = {
    {I_CMPEQPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12425, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPEQSD[] = {
    {I_CMPEQSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12433, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLEPD[] = {
    {I_CMPLEPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12441, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLESD[] = {
    {I_CMPLESD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12449, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLTPD[] = {
    {I_CMPLTPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12457, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPLTSD[] = {
    {I_CMPLTSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12465, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNEQPD[] = {
    {I_CMPNEQPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12473, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNEQSD[] = {
    {I_CMPNEQSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12481, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLEPD[] = {
    {I_CMPNLEPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12489, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLESD[] = {
    {I_CMPNLESD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12497, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLTPD[] = {
    {I_CMPNLTPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12505, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPNLTSD[] = {
    {I_CMPNLTSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12513, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPORDPD[] = {
    {I_CMPORDPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12521, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPORDSD[] = {
    {I_CMPORDSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12529, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPUNORDPD[] = {
    {I_CMPUNORDPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12537, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPUNORDSD[] = {
    {I_CMPUNORDSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12545, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMPPD[] = {
    {I_CMPPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+31326, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_COMISD[] = {
    {I_COMISD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41315, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTDQ2PD[] = {
    {I_CVTDQ2PD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41321, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTDQ2PS[] = {
    {I_CVTDQ2PS, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41327, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPD2DQ[] = {
    {I_CVTPD2DQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41333, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPD2PI[] = {
    {I_CVTPD2PI, 2, {MMXREG,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41339, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPD2PS[] = {
    {I_CVTPD2PS, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41345, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPI2PD[] = {
    {I_CVTPI2PD, 2, {XMM_L16,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+41351, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPS2DQ[] = {
    {I_CVTPS2DQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41357, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTPS2PD[] = {
    {I_CVTPS2PD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41363, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSD2SI[] = {
    {I_CVTSD2SI, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31340, 154},
    {I_CVTSD2SI, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31340, 154},
    {I_CVTSD2SI, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31347, 155},
    {I_CVTSD2SI, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31347, 155},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSD2SS[] = {
    {I_CVTSD2SS, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41369, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSI2SD[] = {
    {I_CVTSI2SD, 2, {XMM_L16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31362, 156},
    {I_CVTSI2SD, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31354, 156},
    {I_CVTSI2SD, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31361, 155},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTSS2SD[] = {
    {I_CVTSS2SD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41375, 146},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTPD2PI[] = {
    {I_CVTTPD2PI, 2, {MMXREG,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41381, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTPD2DQ[] = {
    {I_CVTTPD2DQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41387, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTPS2DQ[] = {
    {I_CVTTPS2DQ, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41393, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_CVTTSD2SI[] = {
    {I_CVTTSD2SI, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31368, 154},
    {I_CVTTSD2SI, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31368, 154},
    {I_CVTTSD2SI, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31375, 155},
    {I_CVTTSD2SI, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+31375, 155},
    ITEMPLATE_END
};

static const struct itemplate instrux_DIVPD[] = {
    {I_DIVPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41399, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_DIVSD[] = {
    {I_DIVSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41405, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_MAXPD[] = {
    {I_MAXPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41411, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MAXSD[] = {
    {I_MAXSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41417, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_MINPD[] = {
    {I_MINPD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41423, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MINSD[] = {
    {I_MINSD, 2, {XMM_L16,RM_XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41429, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVAPD[] = {
    {I_MOVAPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41435, 142},
    {I_MOVAPD, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41441, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVHPD[] = {
    {I_MOVHPD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41447, 142},
    {I_MOVHPD, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41453, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVLPD[] = {
    {I_MOVLPD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41459, 142},
    {I_MOVLPD, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41465, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVMSKPD[] = {
    {I_MOVMSKPD, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41471, 142},
    {I_MOVMSKPD, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31382, 148},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVUPD[] = {
    {I_MOVUPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41489, 142},
    {I_MOVUPD, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41495, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_MULPD[] = {
    {I_MULPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41501, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_MULSD[] = {
    {I_MULSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41507, 147},
    ITEMPLATE_END
};

static const struct itemplate instrux_ORPD[] = {
    {I_ORPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41513, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHUFPD[] = {
    {I_SHUFPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+31389, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_SQRTPD[] = {
    {I_SQRTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41519, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_SQRTSD[] = {
    {I_SQRTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41525, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_SUBPD[] = {
    {I_SUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41531, 143},
    ITEMPLATE_END
};

static const struct itemplate instrux_SUBSD[] = {
    {I_SUBSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41537, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_UCOMISD[] = {
    {I_UCOMISD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41543, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_UNPCKHPD[] = {
    {I_UNPCKHPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41549, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_UNPCKLPD[] = {
    {I_UNPCKLPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41555, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_XORPD[] = {
    {I_XORPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41561, 142},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDSUBPD[] = {
    {I_ADDSUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41567, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADDSUBPS[] = {
    {I_ADDSUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41573, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_HADDPD[] = {
    {I_HADDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41579, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_HADDPS[] = {
    {I_HADDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41585, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_HSUBPD[] = {
    {I_HSUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41591, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_HSUBPS[] = {
    {I_HSUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41597, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_LDDQU[] = {
    {I_LDDQU, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41603, 157},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDDUP[] = {
    {I_MOVDDUP, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+41609, 158},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSHDUP[] = {
    {I_MOVSHDUP, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41615, 159},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVSLDUP[] = {
    {I_MOVSLDUP, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41621, 159},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLGI[] = {
    {I_CLGI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44816, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_STGI[] = {
    {I_STGI, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44821, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMCALL[] = {
    {I_VMCALL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44826, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMCLEAR[] = {
    {I_VMCLEAR, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41627, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMFUNC[] = {
    {I_VMFUNC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44831, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMLAUNCH[] = {
    {I_VMLAUNCH, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44836, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMLOAD[] = {
    {I_VMLOAD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44841, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMMCALL[] = {
    {I_VMMCALL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44846, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMPTRLD[] = {
    {I_VMPTRLD, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41633, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMPTRST[] = {
    {I_VMPTRST, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41639, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMREAD[] = {
    {I_VMREAD, 2, {RM_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31397, 162},
    {I_VMREAD, 2, {RM_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31396, 163},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMRESUME[] = {
    {I_VMRESUME, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44851, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMRUN[] = {
    {I_VMRUN, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44856, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMSAVE[] = {
    {I_VMSAVE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44861, 160},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMWRITE[] = {
    {I_VMWRITE, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31404, 162},
    {I_VMWRITE, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31403, 163},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMXOFF[] = {
    {I_VMXOFF, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44866, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMXON[] = {
    {I_VMXON, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41645, 161},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVEPT[] = {
    {I_INVEPT, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+12554, 164},
    {I_INVEPT, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+12553, 165},
    ITEMPLATE_END
};

static const struct itemplate instrux_INVVPID[] = {
    {I_INVVPID, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+12562, 164},
    {I_INVVPID, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+12561, 165},
    ITEMPLATE_END
};

static const struct itemplate instrux_PABSB[] = {
    {I_PABSB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31410, 166},
    {I_PABSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31417, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PABSW[] = {
    {I_PABSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31424, 166},
    {I_PABSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31431, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PABSD[] = {
    {I_PABSD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31438, 166},
    {I_PABSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31445, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PALIGNR[] = {
    {I_PALIGNR, 3, {MMXREG,RM_MMX,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+12569, 166},
    {I_PALIGNR, 3, {XMM_L16,RM_XMM_L16,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+12577, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHADDW[] = {
    {I_PHADDW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31452, 166},
    {I_PHADDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31459, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHADDD[] = {
    {I_PHADDD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31466, 166},
    {I_PHADDD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31473, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHADDSW[] = {
    {I_PHADDSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31480, 166},
    {I_PHADDSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31487, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHSUBW[] = {
    {I_PHSUBW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31494, 166},
    {I_PHSUBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31501, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHSUBD[] = {
    {I_PHSUBD, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31508, 166},
    {I_PHSUBD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31515, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHSUBSW[] = {
    {I_PHSUBSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31522, 166},
    {I_PHSUBSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31529, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMADDUBSW[] = {
    {I_PMADDUBSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31536, 166},
    {I_PMADDUBSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31543, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULHRSW[] = {
    {I_PMULHRSW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31550, 166},
    {I_PMULHRSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31557, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSHUFB[] = {
    {I_PSHUFB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31564, 166},
    {I_PSHUFB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31571, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSIGNB[] = {
    {I_PSIGNB, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31578, 166},
    {I_PSIGNB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31585, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSIGNW[] = {
    {I_PSIGNW, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31592, 166},
    {I_PSIGNW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31599, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_PSIGND[] = {
    {I_PSIGND, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+31606, 166},
    {I_PSIGND, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31613, 167},
    ITEMPLATE_END
};

static const struct itemplate instrux_EXTRQ[] = {
    {I_EXTRQ, 3, {XMM_L16,IMMEDIATE,IMMEDIATE,0,0}, NO_DECORATOR, nasm_bytecodes+12585, 168},
    {I_EXTRQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41651, 168},
    ITEMPLATE_END
};

static const struct itemplate instrux_INSERTQ[] = {
    {I_INSERTQ, 4, {XMM_L16,XMM_L16,IMMEDIATE,IMMEDIATE,0}, NO_DECORATOR, nasm_bytecodes+12593, 168},
    {I_INSERTQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41657, 168},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTSD[] = {
    {I_MOVNTSD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41663, 169},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTSS[] = {
    {I_MOVNTSS, 2, {MEMORY|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+41669, 170},
    ITEMPLATE_END
};

static const struct itemplate instrux_LZCNT[] = {
    {I_LZCNT, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31620, 113},
    {I_LZCNT, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31627, 113},
    {I_LZCNT, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31634, 59},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLENDPD[] = {
    {I_BLENDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12601, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLENDPS[] = {
    {I_BLENDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12609, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLENDVPD[] = {
    {I_BLENDVPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM0,0,0}, NO_DECORATOR, nasm_bytecodes+31641, 171},
    {I_BLENDVPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31641, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLENDVPS[] = {
    {I_BLENDVPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM0,0,0}, NO_DECORATOR, nasm_bytecodes+31648, 171},
    {I_BLENDVPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31648, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_DPPD[] = {
    {I_DPPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12617, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_DPPS[] = {
    {I_DPPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12625, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_EXTRACTPS[] = {
    {I_EXTRACTPS, 3, {RM_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4241, 171},
    {I_EXTRACTPS, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4240, 172},
    ITEMPLATE_END
};

static const struct itemplate instrux_INSERTPS[] = {
    {I_INSERTPS, 3, {XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12633, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVNTDQA[] = {
    {I_MOVNTDQA, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31655, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_MPSADBW[] = {
    {I_MPSADBW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12641, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PACKUSDW[] = {
    {I_PACKUSDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31662, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PBLENDVB[] = {
    {I_PBLENDVB, 3, {XMM_L16,RM_XMM_L16,XMM0,0,0}, NO_DECORATOR, nasm_bytecodes+31669, 171},
    {I_PBLENDVB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31669, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PBLENDW[] = {
    {I_PBLENDW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12649, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPEQQ[] = {
    {I_PCMPEQQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31676, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PEXTRB[] = {
    {I_PEXTRB, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4250, 171},
    {I_PEXTRB, 3, {MEMORY|BITS8,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4250, 171},
    {I_PEXTRB, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4249, 172},
    ITEMPLATE_END
};

static const struct itemplate instrux_PEXTRD[] = {
    {I_PEXTRD, 3, {RM_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4258, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PEXTRQ[] = {
    {I_PEXTRQ, 3, {RM_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4267, 172},
    ITEMPLATE_END
};

static const struct itemplate instrux_PHMINPOSUW[] = {
    {I_PHMINPOSUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31683, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PINSRB[] = {
    {I_PINSRB, 3, {XMM_L16,MEMORY,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4286, 173},
    {I_PINSRB, 3, {XMM_L16,RM_GPR|BITS8,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4285, 173},
    {I_PINSRB, 3, {XMM_L16,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4286, 173},
    ITEMPLATE_END
};

static const struct itemplate instrux_PINSRD[] = {
    {I_PINSRD, 3, {XMM_L16,RM_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4294, 173},
    ITEMPLATE_END
};

static const struct itemplate instrux_PINSRQ[] = {
    {I_PINSRQ, 3, {XMM_L16,RM_GPR|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+4303, 174},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXSB[] = {
    {I_PMAXSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31690, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXSD[] = {
    {I_PMAXSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31697, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXUD[] = {
    {I_PMAXUD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31704, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMAXUW[] = {
    {I_PMAXUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31711, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINSB[] = {
    {I_PMINSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31718, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINSD[] = {
    {I_PMINSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31725, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINUD[] = {
    {I_PMINUD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31732, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMINUW[] = {
    {I_PMINUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31739, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXBW[] = {
    {I_PMOVSXBW, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31746, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXBD[] = {
    {I_PMOVSXBD, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31753, 176},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXBQ[] = {
    {I_PMOVSXBQ, 2, {XMM_L16,RM_XMM_L16|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31760, 177},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXWD[] = {
    {I_PMOVSXWD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31767, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXWQ[] = {
    {I_PMOVSXWQ, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31774, 176},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVSXDQ[] = {
    {I_PMOVSXDQ, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31781, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXBW[] = {
    {I_PMOVZXBW, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31788, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXBD[] = {
    {I_PMOVZXBD, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31795, 176},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXBQ[] = {
    {I_PMOVZXBQ, 2, {XMM_L16,RM_XMM_L16|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31802, 177},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXWD[] = {
    {I_PMOVZXWD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31809, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXWQ[] = {
    {I_PMOVZXWQ, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31816, 176},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMOVZXDQ[] = {
    {I_PMOVZXDQ, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31823, 175},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULDQ[] = {
    {I_PMULDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31830, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PMULLD[] = {
    {I_PMULLD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31837, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_PTEST[] = {
    {I_PTEST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31844, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROUNDPD[] = {
    {I_ROUNDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12657, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROUNDPS[] = {
    {I_ROUNDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12665, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROUNDSD[] = {
    {I_ROUNDSD, 3, {XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12673, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_ROUNDSS[] = {
    {I_ROUNDSS, 3, {XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12681, 171},
    ITEMPLATE_END
};

static const struct itemplate instrux_CRC32[] = {
    {I_CRC32, 2, {REG_GPR|BITS32,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12706, 178},
    {I_CRC32, 2, {REG_GPR|BITS32,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12689, 178},
    {I_CRC32, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12697, 178},
    {I_CRC32, 2, {REG_GPR|BITS64,RM_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+12705, 179},
    {I_CRC32, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+12713, 179},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPESTRI[] = {
    {I_PCMPESTRI, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12721, 178},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPESTRM[] = {
    {I_PCMPESTRM, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12729, 178},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPISTRI[] = {
    {I_PCMPISTRI, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12737, 178},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPISTRM[] = {
    {I_PCMPISTRM, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12745, 178},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCMPGTQ[] = {
    {I_PCMPGTQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31851, 178},
    ITEMPLATE_END
};

static const struct itemplate instrux_POPCNT[] = {
    {I_POPCNT, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+31858, 180},
    {I_POPCNT, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+31865, 181},
    {I_POPCNT, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+31872, 182},
    ITEMPLATE_END
};

static const struct itemplate instrux_GETSEC[] = {
    {I_GETSEC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+45917, 137},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRCPV[] = {
    {I_PFRCPV, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12753, 183},
    ITEMPLATE_END
};

static const struct itemplate instrux_PFRSQRTV[] = {
    {I_PFRSQRTV, 2, {MMXREG,RM_MMX,0,0,0}, NO_DECORATOR, nasm_bytecodes+12761, 183},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVBE[] = {
    {I_MOVBE, 2, {REG_GPR|BITS16,MEMORY|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12769, 184},
    {I_MOVBE, 2, {REG_GPR|BITS32,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12777, 184},
    {I_MOVBE, 2, {REG_GPR|BITS64,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+12785, 184},
    {I_MOVBE, 2, {MEMORY|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+12793, 184},
    {I_MOVBE, 2, {MEMORY|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+12801, 184},
    {I_MOVBE, 2, {MEMORY|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+12809, 184},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESENC[] = {
    {I_AESENC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31879, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESENCLAST[] = {
    {I_AESENCLAST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31886, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESDEC[] = {
    {I_AESDEC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31893, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESDECLAST[] = {
    {I_AESDECLAST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31900, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESIMC[] = {
    {I_AESIMC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31907, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_AESKEYGENASSIST[] = {
    {I_AESKEYGENASSIST, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12817, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESENC[] = {
    {I_VAESENC, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+31914, 186},
    {I_VAESENC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31921, 186},
    {I_VAESENC, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+31977, 187},
    {I_VAESENC, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+31984, 187},
    {I_VAESENC, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+12833, 188},
    {I_VAESENC, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12841, 188},
    {I_VAESENC, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+12849, 188},
    {I_VAESENC, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+12857, 188},
    {I_VAESENC, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+12961, 189},
    {I_VAESENC, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+12969, 189},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESENCLAST[] = {
    {I_VAESENCLAST, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+31928, 186},
    {I_VAESENCLAST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31935, 186},
    {I_VAESENCLAST, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+31991, 187},
    {I_VAESENCLAST, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+31998, 187},
    {I_VAESENCLAST, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+12865, 188},
    {I_VAESENCLAST, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12873, 188},
    {I_VAESENCLAST, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+12881, 188},
    {I_VAESENCLAST, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+12889, 188},
    {I_VAESENCLAST, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+12977, 189},
    {I_VAESENCLAST, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+12985, 189},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESDEC[] = {
    {I_VAESDEC, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+31942, 186},
    {I_VAESDEC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31949, 186},
    {I_VAESDEC, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32005, 187},
    {I_VAESDEC, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32012, 187},
    {I_VAESDEC, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+12897, 188},
    {I_VAESDEC, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12905, 188},
    {I_VAESDEC, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+12913, 188},
    {I_VAESDEC, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+12921, 188},
    {I_VAESDEC, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+12993, 189},
    {I_VAESDEC, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+13001, 189},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESDECLAST[] = {
    {I_VAESDECLAST, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+31956, 186},
    {I_VAESDECLAST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31963, 186},
    {I_VAESDECLAST, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32019, 187},
    {I_VAESDECLAST, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32026, 187},
    {I_VAESDECLAST, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+12929, 188},
    {I_VAESDECLAST, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+12937, 188},
    {I_VAESDECLAST, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+12945, 188},
    {I_VAESDECLAST, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+12953, 188},
    {I_VAESDECLAST, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+13009, 189},
    {I_VAESDECLAST, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+13017, 189},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESIMC[] = {
    {I_VAESIMC, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+31970, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VAESKEYGENASSIST[] = {
    {I_VAESKEYGENASSIST, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+12825, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDPD[] = {
    {I_VADDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32033, 186},
    {I_VADDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32040, 186},
    {I_VADDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32047, 186},
    {I_VADDPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32054, 186},
    {I_VADDPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16097, 231},
    {I_VADDPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16105, 231},
    {I_VADDPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16113, 231},
    {I_VADDPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16121, 231},
    {I_VADDPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+16129, 232},
    {I_VADDPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16137, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDPS[] = {
    {I_VADDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32061, 186},
    {I_VADDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32068, 186},
    {I_VADDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32075, 186},
    {I_VADDPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32082, 186},
    {I_VADDPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16145, 231},
    {I_VADDPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16153, 231},
    {I_VADDPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16161, 231},
    {I_VADDPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16169, 231},
    {I_VADDPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+16177, 232},
    {I_VADDPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+16185, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDSD[] = {
    {I_VADDSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32089, 186},
    {I_VADDSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32096, 186},
    {I_VADDSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+16193, 232},
    {I_VADDSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+16201, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDSS[] = {
    {I_VADDSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32103, 186},
    {I_VADDSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32110, 186},
    {I_VADDSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+16209, 232},
    {I_VADDSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+16217, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDSUBPD[] = {
    {I_VADDSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32117, 186},
    {I_VADDSUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32124, 186},
    {I_VADDSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32131, 186},
    {I_VADDSUBPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32138, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VADDSUBPS[] = {
    {I_VADDSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32145, 186},
    {I_VADDSUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32152, 186},
    {I_VADDSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32159, 186},
    {I_VADDSUBPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32166, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VANDPD[] = {
    {I_VANDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32173, 186},
    {I_VANDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32180, 186},
    {I_VANDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32187, 186},
    {I_VANDPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32194, 186},
    {I_VANDPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16321, 233},
    {I_VANDPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16329, 233},
    {I_VANDPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16337, 233},
    {I_VANDPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16345, 233},
    {I_VANDPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16353, 234},
    {I_VANDPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16361, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VANDPS[] = {
    {I_VANDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32201, 186},
    {I_VANDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32208, 186},
    {I_VANDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32215, 186},
    {I_VANDPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32222, 186},
    {I_VANDPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16369, 233},
    {I_VANDPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16377, 233},
    {I_VANDPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16385, 233},
    {I_VANDPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16393, 233},
    {I_VANDPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16401, 234},
    {I_VANDPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16409, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VANDNPD[] = {
    {I_VANDNPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32229, 186},
    {I_VANDNPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32236, 186},
    {I_VANDNPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32243, 186},
    {I_VANDNPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32250, 186},
    {I_VANDNPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16225, 233},
    {I_VANDNPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16233, 233},
    {I_VANDNPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16241, 233},
    {I_VANDNPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16249, 233},
    {I_VANDNPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16257, 234},
    {I_VANDNPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16265, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VANDNPS[] = {
    {I_VANDNPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32257, 186},
    {I_VANDNPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32264, 186},
    {I_VANDNPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32271, 186},
    {I_VANDNPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32278, 186},
    {I_VANDNPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16273, 233},
    {I_VANDNPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16281, 233},
    {I_VANDNPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16289, 233},
    {I_VANDNPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16297, 233},
    {I_VANDNPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16305, 234},
    {I_VANDNPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16313, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDPD[] = {
    {I_VBLENDPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13025, 186},
    {I_VBLENDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13033, 186},
    {I_VBLENDPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13041, 186},
    {I_VBLENDPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13049, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDPS[] = {
    {I_VBLENDPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13057, 186},
    {I_VBLENDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13065, 186},
    {I_VBLENDPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13073, 186},
    {I_VBLENDPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13081, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDVPD[] = {
    {I_VBLENDVPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+13089, 186},
    {I_VBLENDVPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+13097, 186},
    {I_VBLENDVPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+13105, 186},
    {I_VBLENDVPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+13113, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDVPS[] = {
    {I_VBLENDVPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+13121, 186},
    {I_VBLENDVPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+13129, 186},
    {I_VBLENDVPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+13137, 186},
    {I_VBLENDVPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+13145, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTSS[] = {
    {I_VBROADCASTSS, 2, {XMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32285, 186},
    {I_VBROADCASTSS, 2, {YMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32292, 186},
    {I_VBROADCASTSS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32285, 205},
    {I_VBROADCASTSS, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32292, 205},
    {I_VBROADCASTSS, 2, {XMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16633, 231},
    {I_VBROADCASTSS, 2, {YMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16641, 231},
    {I_VBROADCASTSS, 2, {ZMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16649, 232},
    {I_VBROADCASTSS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16657, 231},
    {I_VBROADCASTSS, 2, {YMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16665, 231},
    {I_VBROADCASTSS, 2, {ZMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16673, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTSD[] = {
    {I_VBROADCASTSD, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32299, 186},
    {I_VBROADCASTSD, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32299, 205},
    {I_VBROADCASTSD, 2, {YMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16601, 231},
    {I_VBROADCASTSD, 2, {ZMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16609, 232},
    {I_VBROADCASTSD, 2, {YMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16617, 231},
    {I_VBROADCASTSD, 2, {ZMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF128[] = {
    {I_VBROADCASTF128, 2, {YMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32306, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OSPD[] = {
    {I_VCMPEQ_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4312, 186},
    {I_VCMPEQ_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4321, 186},
    {I_VCMPEQ_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4330, 186},
    {I_VCMPEQ_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4339, 186},
    {I_VCMPEQ_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4312, 186},
    {I_VCMPEQ_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4321, 186},
    {I_VCMPEQ_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4330, 186},
    {I_VCMPEQ_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4339, 186},
    {I_VCMPEQ_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1520, 231},
    {I_VCMPEQ_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1530, 231},
    {I_VCMPEQ_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1540, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQPD[] = {
    {I_VCMPEQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4348, 186},
    {I_VCMPEQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4357, 186},
    {I_VCMPEQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4366, 186},
    {I_VCMPEQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4375, 186},
    {I_VCMPEQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+240, 231},
    {I_VCMPEQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+250, 231},
    {I_VCMPEQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+260, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OSPD[] = {
    {I_VCMPLT_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4384, 186},
    {I_VCMPLT_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4393, 186},
    {I_VCMPLT_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4402, 186},
    {I_VCMPLT_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4411, 186},
    {I_VCMPLT_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+320, 231},
    {I_VCMPLT_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+330, 231},
    {I_VCMPLT_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+340, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLTPD[] = {
    {I_VCMPLTPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4384, 186},
    {I_VCMPLTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4393, 186},
    {I_VCMPLTPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4402, 186},
    {I_VCMPLTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4411, 186},
    {I_VCMPLTPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+320, 231},
    {I_VCMPLTPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+330, 231},
    {I_VCMPLTPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+340, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OSPD[] = {
    {I_VCMPLE_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4420, 186},
    {I_VCMPLE_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4429, 186},
    {I_VCMPLE_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4438, 186},
    {I_VCMPLE_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4447, 186},
    {I_VCMPLE_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+400, 231},
    {I_VCMPLE_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+410, 231},
    {I_VCMPLE_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLEPD[] = {
    {I_VCMPLEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4420, 186},
    {I_VCMPLEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4429, 186},
    {I_VCMPLEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4438, 186},
    {I_VCMPLEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4447, 186},
    {I_VCMPLEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+400, 231},
    {I_VCMPLEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+410, 231},
    {I_VCMPLEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_QPD[] = {
    {I_VCMPUNORD_QPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4456, 186},
    {I_VCMPUNORD_QPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4465, 186},
    {I_VCMPUNORD_QPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4474, 186},
    {I_VCMPUNORD_QPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4483, 186},
    {I_VCMPUNORD_QPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+480, 231},
    {I_VCMPUNORD_QPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+490, 231},
    {I_VCMPUNORD_QPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+500, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORDPD[] = {
    {I_VCMPUNORDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4456, 186},
    {I_VCMPUNORDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4465, 186},
    {I_VCMPUNORDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4474, 186},
    {I_VCMPUNORDPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4483, 186},
    {I_VCMPUNORDPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+480, 231},
    {I_VCMPUNORDPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+490, 231},
    {I_VCMPUNORDPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+500, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_UQPD[] = {
    {I_VCMPNEQ_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4492, 186},
    {I_VCMPNEQ_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4501, 186},
    {I_VCMPNEQ_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4510, 186},
    {I_VCMPNEQ_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4519, 186},
    {I_VCMPNEQ_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+560, 231},
    {I_VCMPNEQ_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+570, 231},
    {I_VCMPNEQ_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+580, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQPD[] = {
    {I_VCMPNEQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4492, 186},
    {I_VCMPNEQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4501, 186},
    {I_VCMPNEQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4510, 186},
    {I_VCMPNEQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4519, 186},
    {I_VCMPNEQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+560, 231},
    {I_VCMPNEQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+570, 231},
    {I_VCMPNEQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+580, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_USPD[] = {
    {I_VCMPNLT_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4528, 186},
    {I_VCMPNLT_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4537, 186},
    {I_VCMPNLT_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4546, 186},
    {I_VCMPNLT_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4555, 186},
    {I_VCMPNLT_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+640, 231},
    {I_VCMPNLT_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+650, 231},
    {I_VCMPNLT_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLTPD[] = {
    {I_VCMPNLTPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4528, 186},
    {I_VCMPNLTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4537, 186},
    {I_VCMPNLTPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4546, 186},
    {I_VCMPNLTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4555, 186},
    {I_VCMPNLTPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+640, 231},
    {I_VCMPNLTPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+650, 231},
    {I_VCMPNLTPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_USPD[] = {
    {I_VCMPNLE_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4564, 186},
    {I_VCMPNLE_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4573, 186},
    {I_VCMPNLE_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4582, 186},
    {I_VCMPNLE_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4591, 186},
    {I_VCMPNLE_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+720, 231},
    {I_VCMPNLE_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+730, 231},
    {I_VCMPNLE_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+740, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLEPD[] = {
    {I_VCMPNLEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4564, 186},
    {I_VCMPNLEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4573, 186},
    {I_VCMPNLEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4582, 186},
    {I_VCMPNLEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4591, 186},
    {I_VCMPNLEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+720, 231},
    {I_VCMPNLEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+730, 231},
    {I_VCMPNLEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+740, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_QPD[] = {
    {I_VCMPORD_QPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4600, 186},
    {I_VCMPORD_QPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4609, 186},
    {I_VCMPORD_QPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4618, 186},
    {I_VCMPORD_QPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4627, 186},
    {I_VCMPORD_QPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+800, 231},
    {I_VCMPORD_QPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+810, 231},
    {I_VCMPORD_QPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+820, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORDPD[] = {
    {I_VCMPORDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4600, 186},
    {I_VCMPORDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4609, 186},
    {I_VCMPORDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4618, 186},
    {I_VCMPORDPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4627, 186},
    {I_VCMPORDPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+800, 231},
    {I_VCMPORDPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+810, 231},
    {I_VCMPORDPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+820, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_UQPD[] = {
    {I_VCMPEQ_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4636, 186},
    {I_VCMPEQ_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4645, 186},
    {I_VCMPEQ_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4654, 186},
    {I_VCMPEQ_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4663, 186},
    {I_VCMPEQ_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+880, 231},
    {I_VCMPEQ_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+890, 231},
    {I_VCMPEQ_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+900, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_USPD[] = {
    {I_VCMPNGE_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4672, 186},
    {I_VCMPNGE_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4681, 186},
    {I_VCMPNGE_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4690, 186},
    {I_VCMPNGE_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4699, 186},
    {I_VCMPNGE_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+960, 231},
    {I_VCMPNGE_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+970, 231},
    {I_VCMPNGE_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+980, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGEPD[] = {
    {I_VCMPNGEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4672, 186},
    {I_VCMPNGEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4681, 186},
    {I_VCMPNGEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4690, 186},
    {I_VCMPNGEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4699, 186},
    {I_VCMPNGEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+960, 231},
    {I_VCMPNGEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+970, 231},
    {I_VCMPNGEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+980, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_USPD[] = {
    {I_VCMPNGT_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4708, 186},
    {I_VCMPNGT_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4717, 186},
    {I_VCMPNGT_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4726, 186},
    {I_VCMPNGT_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4735, 186},
    {I_VCMPNGT_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1040, 231},
    {I_VCMPNGT_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1050, 231},
    {I_VCMPNGT_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1060, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGTPD[] = {
    {I_VCMPNGTPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4708, 186},
    {I_VCMPNGTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4717, 186},
    {I_VCMPNGTPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4726, 186},
    {I_VCMPNGTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4735, 186},
    {I_VCMPNGTPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1040, 231},
    {I_VCMPNGTPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1050, 231},
    {I_VCMPNGTPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1060, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OQPD[] = {
    {I_VCMPFALSE_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4744, 186},
    {I_VCMPFALSE_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4753, 186},
    {I_VCMPFALSE_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4762, 186},
    {I_VCMPFALSE_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4771, 186},
    {I_VCMPFALSE_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1120, 231},
    {I_VCMPFALSE_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1130, 231},
    {I_VCMPFALSE_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1140, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSEPD[] = {
    {I_VCMPFALSEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4744, 186},
    {I_VCMPFALSEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4753, 186},
    {I_VCMPFALSEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4762, 186},
    {I_VCMPFALSEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4771, 186},
    {I_VCMPFALSEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1120, 231},
    {I_VCMPFALSEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1130, 231},
    {I_VCMPFALSEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1140, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OQPD[] = {
    {I_VCMPNEQ_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4780, 186},
    {I_VCMPNEQ_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4789, 186},
    {I_VCMPNEQ_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4798, 186},
    {I_VCMPNEQ_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4807, 186},
    {I_VCMPNEQ_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1200, 231},
    {I_VCMPNEQ_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1210, 231},
    {I_VCMPNEQ_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1220, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OSPD[] = {
    {I_VCMPGE_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4816, 186},
    {I_VCMPGE_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4825, 186},
    {I_VCMPGE_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4834, 186},
    {I_VCMPGE_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4843, 186},
    {I_VCMPGE_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1280, 231},
    {I_VCMPGE_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1290, 231},
    {I_VCMPGE_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1300, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGEPD[] = {
    {I_VCMPGEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4816, 186},
    {I_VCMPGEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4825, 186},
    {I_VCMPGEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4834, 186},
    {I_VCMPGEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4843, 186},
    {I_VCMPGEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1280, 231},
    {I_VCMPGEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1290, 231},
    {I_VCMPGEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1300, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OSPD[] = {
    {I_VCMPGT_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4852, 186},
    {I_VCMPGT_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4861, 186},
    {I_VCMPGT_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4870, 186},
    {I_VCMPGT_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4879, 186},
    {I_VCMPGT_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1360, 231},
    {I_VCMPGT_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1370, 231},
    {I_VCMPGT_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1380, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGTPD[] = {
    {I_VCMPGTPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4852, 186},
    {I_VCMPGTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4861, 186},
    {I_VCMPGTPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4870, 186},
    {I_VCMPGTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4879, 186},
    {I_VCMPGTPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1360, 231},
    {I_VCMPGTPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1370, 231},
    {I_VCMPGTPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1380, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_UQPD[] = {
    {I_VCMPTRUE_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4888, 186},
    {I_VCMPTRUE_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4897, 186},
    {I_VCMPTRUE_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4906, 186},
    {I_VCMPTRUE_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4915, 186},
    {I_VCMPTRUE_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1440, 231},
    {I_VCMPTRUE_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1450, 231},
    {I_VCMPTRUE_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1460, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUEPD[] = {
    {I_VCMPTRUEPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4888, 186},
    {I_VCMPTRUEPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4897, 186},
    {I_VCMPTRUEPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4906, 186},
    {I_VCMPTRUEPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4915, 186},
    {I_VCMPTRUEPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1440, 231},
    {I_VCMPTRUEPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1450, 231},
    {I_VCMPTRUEPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1460, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OQPD[] = {
    {I_VCMPLT_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4924, 186},
    {I_VCMPLT_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4933, 186},
    {I_VCMPLT_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4942, 186},
    {I_VCMPLT_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4951, 186},
    {I_VCMPLT_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1600, 231},
    {I_VCMPLT_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1610, 231},
    {I_VCMPLT_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1620, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OQPD[] = {
    {I_VCMPLE_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4960, 186},
    {I_VCMPLE_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+4969, 186},
    {I_VCMPLE_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+4978, 186},
    {I_VCMPLE_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+4987, 186},
    {I_VCMPLE_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1680, 231},
    {I_VCMPLE_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1690, 231},
    {I_VCMPLE_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1700, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_SPD[] = {
    {I_VCMPUNORD_SPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+4996, 186},
    {I_VCMPUNORD_SPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5005, 186},
    {I_VCMPUNORD_SPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5014, 186},
    {I_VCMPUNORD_SPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5023, 186},
    {I_VCMPUNORD_SPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1760, 231},
    {I_VCMPUNORD_SPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1770, 231},
    {I_VCMPUNORD_SPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1780, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_USPD[] = {
    {I_VCMPNEQ_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5032, 186},
    {I_VCMPNEQ_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5041, 186},
    {I_VCMPNEQ_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5050, 186},
    {I_VCMPNEQ_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5059, 186},
    {I_VCMPNEQ_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1840, 231},
    {I_VCMPNEQ_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1850, 231},
    {I_VCMPNEQ_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1860, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_UQPD[] = {
    {I_VCMPNLT_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5068, 186},
    {I_VCMPNLT_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5077, 186},
    {I_VCMPNLT_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5086, 186},
    {I_VCMPNLT_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5095, 186},
    {I_VCMPNLT_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1920, 231},
    {I_VCMPNLT_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+1930, 231},
    {I_VCMPNLT_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+1940, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_UQPD[] = {
    {I_VCMPNLE_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5104, 186},
    {I_VCMPNLE_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5113, 186},
    {I_VCMPNLE_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5122, 186},
    {I_VCMPNLE_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5131, 186},
    {I_VCMPNLE_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2000, 231},
    {I_VCMPNLE_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2010, 231},
    {I_VCMPNLE_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2020, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_SPD[] = {
    {I_VCMPORD_SPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5140, 186},
    {I_VCMPORD_SPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5149, 186},
    {I_VCMPORD_SPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5158, 186},
    {I_VCMPORD_SPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5167, 186},
    {I_VCMPORD_SPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2080, 231},
    {I_VCMPORD_SPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2090, 231},
    {I_VCMPORD_SPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2100, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_USPD[] = {
    {I_VCMPEQ_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5176, 186},
    {I_VCMPEQ_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5185, 186},
    {I_VCMPEQ_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5194, 186},
    {I_VCMPEQ_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5203, 186},
    {I_VCMPEQ_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2160, 231},
    {I_VCMPEQ_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2170, 231},
    {I_VCMPEQ_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2180, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_UQPD[] = {
    {I_VCMPNGE_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5212, 186},
    {I_VCMPNGE_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5221, 186},
    {I_VCMPNGE_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5230, 186},
    {I_VCMPNGE_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5239, 186},
    {I_VCMPNGE_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2240, 231},
    {I_VCMPNGE_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2250, 231},
    {I_VCMPNGE_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2260, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_UQPD[] = {
    {I_VCMPNGT_UQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5248, 186},
    {I_VCMPNGT_UQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5257, 186},
    {I_VCMPNGT_UQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5266, 186},
    {I_VCMPNGT_UQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5275, 186},
    {I_VCMPNGT_UQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2320, 231},
    {I_VCMPNGT_UQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2330, 231},
    {I_VCMPNGT_UQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2340, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OSPD[] = {
    {I_VCMPFALSE_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5284, 186},
    {I_VCMPFALSE_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5293, 186},
    {I_VCMPFALSE_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5302, 186},
    {I_VCMPFALSE_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5311, 186},
    {I_VCMPFALSE_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2400, 231},
    {I_VCMPFALSE_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2410, 231},
    {I_VCMPFALSE_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OSPD[] = {
    {I_VCMPNEQ_OSPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5320, 186},
    {I_VCMPNEQ_OSPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5329, 186},
    {I_VCMPNEQ_OSPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5338, 186},
    {I_VCMPNEQ_OSPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5347, 186},
    {I_VCMPNEQ_OSPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2480, 231},
    {I_VCMPNEQ_OSPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2490, 231},
    {I_VCMPNEQ_OSPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2500, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OQPD[] = {
    {I_VCMPGE_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5356, 186},
    {I_VCMPGE_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5365, 186},
    {I_VCMPGE_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5374, 186},
    {I_VCMPGE_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5383, 186},
    {I_VCMPGE_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2560, 231},
    {I_VCMPGE_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2570, 231},
    {I_VCMPGE_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2580, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OQPD[] = {
    {I_VCMPGT_OQPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5392, 186},
    {I_VCMPGT_OQPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5401, 186},
    {I_VCMPGT_OQPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5410, 186},
    {I_VCMPGT_OQPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5419, 186},
    {I_VCMPGT_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2640, 231},
    {I_VCMPGT_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2650, 231},
    {I_VCMPGT_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_USPD[] = {
    {I_VCMPTRUE_USPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5428, 186},
    {I_VCMPTRUE_USPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5437, 186},
    {I_VCMPTRUE_USPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5446, 186},
    {I_VCMPTRUE_USPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5455, 186},
    {I_VCMPTRUE_USPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2720, 231},
    {I_VCMPTRUE_USPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2730, 231},
    {I_VCMPTRUE_USPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+2740, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPPD[] = {
    {I_VCMPPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13153, 186},
    {I_VCMPPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13161, 186},
    {I_VCMPPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13169, 186},
    {I_VCMPPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13177, 186},
    {I_VCMPPD, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+8110, 231},
    {I_VCMPPD, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+8119, 231},
    {I_VCMPPD, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+8128, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OSPS[] = {
    {I_VCMPEQ_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5464, 186},
    {I_VCMPEQ_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5473, 186},
    {I_VCMPEQ_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5482, 186},
    {I_VCMPEQ_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5491, 186},
    {I_VCMPEQ_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5464, 186},
    {I_VCMPEQ_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5473, 186},
    {I_VCMPEQ_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5482, 186},
    {I_VCMPEQ_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5491, 186},
    {I_VCMPEQ_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1550, 231},
    {I_VCMPEQ_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1560, 231},
    {I_VCMPEQ_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1570, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQPS[] = {
    {I_VCMPEQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5500, 186},
    {I_VCMPEQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5509, 186},
    {I_VCMPEQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5518, 186},
    {I_VCMPEQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5527, 186},
    {I_VCMPEQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+270, 231},
    {I_VCMPEQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+280, 231},
    {I_VCMPEQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+290, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OSPS[] = {
    {I_VCMPLT_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5536, 186},
    {I_VCMPLT_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5545, 186},
    {I_VCMPLT_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5554, 186},
    {I_VCMPLT_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5563, 186},
    {I_VCMPLT_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+350, 231},
    {I_VCMPLT_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+360, 231},
    {I_VCMPLT_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+370, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLTPS[] = {
    {I_VCMPLTPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5536, 186},
    {I_VCMPLTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5545, 186},
    {I_VCMPLTPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5554, 186},
    {I_VCMPLTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5563, 186},
    {I_VCMPLTPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+350, 231},
    {I_VCMPLTPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+360, 231},
    {I_VCMPLTPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+370, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OSPS[] = {
    {I_VCMPLE_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5572, 186},
    {I_VCMPLE_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5581, 186},
    {I_VCMPLE_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5590, 186},
    {I_VCMPLE_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5599, 186},
    {I_VCMPLE_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+430, 231},
    {I_VCMPLE_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+440, 231},
    {I_VCMPLE_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+450, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLEPS[] = {
    {I_VCMPLEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5572, 186},
    {I_VCMPLEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5581, 186},
    {I_VCMPLEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5590, 186},
    {I_VCMPLEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5599, 186},
    {I_VCMPLEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+430, 231},
    {I_VCMPLEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+440, 231},
    {I_VCMPLEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+450, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_QPS[] = {
    {I_VCMPUNORD_QPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5608, 186},
    {I_VCMPUNORD_QPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5617, 186},
    {I_VCMPUNORD_QPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5626, 186},
    {I_VCMPUNORD_QPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5635, 186},
    {I_VCMPUNORD_QPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+510, 231},
    {I_VCMPUNORD_QPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+520, 231},
    {I_VCMPUNORD_QPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+530, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORDPS[] = {
    {I_VCMPUNORDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5608, 186},
    {I_VCMPUNORDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5617, 186},
    {I_VCMPUNORDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5626, 186},
    {I_VCMPUNORDPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5635, 186},
    {I_VCMPUNORDPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+510, 231},
    {I_VCMPUNORDPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+520, 231},
    {I_VCMPUNORDPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+530, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_UQPS[] = {
    {I_VCMPNEQ_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5644, 186},
    {I_VCMPNEQ_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5653, 186},
    {I_VCMPNEQ_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5662, 186},
    {I_VCMPNEQ_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5671, 186},
    {I_VCMPNEQ_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+590, 231},
    {I_VCMPNEQ_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+600, 231},
    {I_VCMPNEQ_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+610, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQPS[] = {
    {I_VCMPNEQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5644, 186},
    {I_VCMPNEQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5653, 186},
    {I_VCMPNEQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5662, 186},
    {I_VCMPNEQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5671, 186},
    {I_VCMPNEQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+590, 231},
    {I_VCMPNEQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+600, 231},
    {I_VCMPNEQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+610, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_USPS[] = {
    {I_VCMPNLT_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5680, 186},
    {I_VCMPNLT_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5689, 186},
    {I_VCMPNLT_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5698, 186},
    {I_VCMPNLT_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5707, 186},
    {I_VCMPNLT_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+670, 231},
    {I_VCMPNLT_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+680, 231},
    {I_VCMPNLT_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+690, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLTPS[] = {
    {I_VCMPNLTPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5680, 186},
    {I_VCMPNLTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5689, 186},
    {I_VCMPNLTPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5698, 186},
    {I_VCMPNLTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5707, 186},
    {I_VCMPNLTPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+670, 231},
    {I_VCMPNLTPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+680, 231},
    {I_VCMPNLTPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+690, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_USPS[] = {
    {I_VCMPNLE_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5716, 186},
    {I_VCMPNLE_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5725, 186},
    {I_VCMPNLE_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5734, 186},
    {I_VCMPNLE_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5743, 186},
    {I_VCMPNLE_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+750, 231},
    {I_VCMPNLE_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+760, 231},
    {I_VCMPNLE_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+770, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLEPS[] = {
    {I_VCMPNLEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5716, 186},
    {I_VCMPNLEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5725, 186},
    {I_VCMPNLEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5734, 186},
    {I_VCMPNLEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5743, 186},
    {I_VCMPNLEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+750, 231},
    {I_VCMPNLEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+760, 231},
    {I_VCMPNLEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+770, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_QPS[] = {
    {I_VCMPORD_QPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5752, 186},
    {I_VCMPORD_QPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5761, 186},
    {I_VCMPORD_QPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5770, 186},
    {I_VCMPORD_QPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5779, 186},
    {I_VCMPORD_QPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+830, 231},
    {I_VCMPORD_QPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+840, 231},
    {I_VCMPORD_QPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+850, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORDPS[] = {
    {I_VCMPORDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5752, 186},
    {I_VCMPORDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5761, 186},
    {I_VCMPORDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5770, 186},
    {I_VCMPORDPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5779, 186},
    {I_VCMPORDPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+830, 231},
    {I_VCMPORDPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+840, 231},
    {I_VCMPORDPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+850, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_UQPS[] = {
    {I_VCMPEQ_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5788, 186},
    {I_VCMPEQ_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5797, 186},
    {I_VCMPEQ_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5806, 186},
    {I_VCMPEQ_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5815, 186},
    {I_VCMPEQ_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+910, 231},
    {I_VCMPEQ_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+920, 231},
    {I_VCMPEQ_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+930, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_USPS[] = {
    {I_VCMPNGE_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5824, 186},
    {I_VCMPNGE_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5833, 186},
    {I_VCMPNGE_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5842, 186},
    {I_VCMPNGE_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5851, 186},
    {I_VCMPNGE_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+990, 231},
    {I_VCMPNGE_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1000, 231},
    {I_VCMPNGE_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1010, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGEPS[] = {
    {I_VCMPNGEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5824, 186},
    {I_VCMPNGEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5833, 186},
    {I_VCMPNGEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5842, 186},
    {I_VCMPNGEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5851, 186},
    {I_VCMPNGEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+990, 231},
    {I_VCMPNGEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1000, 231},
    {I_VCMPNGEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1010, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_USPS[] = {
    {I_VCMPNGT_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5860, 186},
    {I_VCMPNGT_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5869, 186},
    {I_VCMPNGT_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5878, 186},
    {I_VCMPNGT_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5887, 186},
    {I_VCMPNGT_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1070, 231},
    {I_VCMPNGT_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1080, 231},
    {I_VCMPNGT_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1090, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGTPS[] = {
    {I_VCMPNGTPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5860, 186},
    {I_VCMPNGTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5869, 186},
    {I_VCMPNGTPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5878, 186},
    {I_VCMPNGTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5887, 186},
    {I_VCMPNGTPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1070, 231},
    {I_VCMPNGTPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1080, 231},
    {I_VCMPNGTPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1090, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OQPS[] = {
    {I_VCMPFALSE_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5896, 186},
    {I_VCMPFALSE_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5905, 186},
    {I_VCMPFALSE_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5914, 186},
    {I_VCMPFALSE_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5923, 186},
    {I_VCMPFALSE_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1150, 231},
    {I_VCMPFALSE_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1160, 231},
    {I_VCMPFALSE_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1170, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSEPS[] = {
    {I_VCMPFALSEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5896, 186},
    {I_VCMPFALSEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5905, 186},
    {I_VCMPFALSEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5914, 186},
    {I_VCMPFALSEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5923, 186},
    {I_VCMPFALSEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1150, 231},
    {I_VCMPFALSEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1160, 231},
    {I_VCMPFALSEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1170, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OQPS[] = {
    {I_VCMPNEQ_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5932, 186},
    {I_VCMPNEQ_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5941, 186},
    {I_VCMPNEQ_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5950, 186},
    {I_VCMPNEQ_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5959, 186},
    {I_VCMPNEQ_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1230, 231},
    {I_VCMPNEQ_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1240, 231},
    {I_VCMPNEQ_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1250, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OSPS[] = {
    {I_VCMPGE_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5968, 186},
    {I_VCMPGE_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5977, 186},
    {I_VCMPGE_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5986, 186},
    {I_VCMPGE_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5995, 186},
    {I_VCMPGE_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1310, 231},
    {I_VCMPGE_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1320, 231},
    {I_VCMPGE_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1330, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGEPS[] = {
    {I_VCMPGEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+5968, 186},
    {I_VCMPGEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+5977, 186},
    {I_VCMPGEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+5986, 186},
    {I_VCMPGEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+5995, 186},
    {I_VCMPGEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1310, 231},
    {I_VCMPGEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1320, 231},
    {I_VCMPGEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1330, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OSPS[] = {
    {I_VCMPGT_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6004, 186},
    {I_VCMPGT_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6013, 186},
    {I_VCMPGT_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6022, 186},
    {I_VCMPGT_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6031, 186},
    {I_VCMPGT_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1390, 231},
    {I_VCMPGT_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1400, 231},
    {I_VCMPGT_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1410, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGTPS[] = {
    {I_VCMPGTPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6004, 186},
    {I_VCMPGTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6013, 186},
    {I_VCMPGTPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6022, 186},
    {I_VCMPGTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6031, 186},
    {I_VCMPGTPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1390, 231},
    {I_VCMPGTPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1400, 231},
    {I_VCMPGTPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1410, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_UQPS[] = {
    {I_VCMPTRUE_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6040, 186},
    {I_VCMPTRUE_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6049, 186},
    {I_VCMPTRUE_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6058, 186},
    {I_VCMPTRUE_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6067, 186},
    {I_VCMPTRUE_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1470, 231},
    {I_VCMPTRUE_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1480, 231},
    {I_VCMPTRUE_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1490, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUEPS[] = {
    {I_VCMPTRUEPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6040, 186},
    {I_VCMPTRUEPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6049, 186},
    {I_VCMPTRUEPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6058, 186},
    {I_VCMPTRUEPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6067, 186},
    {I_VCMPTRUEPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1470, 231},
    {I_VCMPTRUEPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1480, 231},
    {I_VCMPTRUEPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1490, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OQPS[] = {
    {I_VCMPLT_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6076, 186},
    {I_VCMPLT_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6085, 186},
    {I_VCMPLT_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6094, 186},
    {I_VCMPLT_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6103, 186},
    {I_VCMPLT_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1630, 231},
    {I_VCMPLT_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1640, 231},
    {I_VCMPLT_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1650, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OQPS[] = {
    {I_VCMPLE_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6112, 186},
    {I_VCMPLE_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6121, 186},
    {I_VCMPLE_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6130, 186},
    {I_VCMPLE_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6139, 186},
    {I_VCMPLE_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1710, 231},
    {I_VCMPLE_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1720, 231},
    {I_VCMPLE_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1730, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_SPS[] = {
    {I_VCMPUNORD_SPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6148, 186},
    {I_VCMPUNORD_SPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6157, 186},
    {I_VCMPUNORD_SPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6166, 186},
    {I_VCMPUNORD_SPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6175, 186},
    {I_VCMPUNORD_SPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1790, 231},
    {I_VCMPUNORD_SPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1800, 231},
    {I_VCMPUNORD_SPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1810, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_USPS[] = {
    {I_VCMPNEQ_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6184, 186},
    {I_VCMPNEQ_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6193, 186},
    {I_VCMPNEQ_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6202, 186},
    {I_VCMPNEQ_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6211, 186},
    {I_VCMPNEQ_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1870, 231},
    {I_VCMPNEQ_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1880, 231},
    {I_VCMPNEQ_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1890, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_UQPS[] = {
    {I_VCMPNLT_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6220, 186},
    {I_VCMPNLT_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6229, 186},
    {I_VCMPNLT_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6238, 186},
    {I_VCMPNLT_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6247, 186},
    {I_VCMPNLT_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1950, 231},
    {I_VCMPNLT_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+1960, 231},
    {I_VCMPNLT_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+1970, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_UQPS[] = {
    {I_VCMPNLE_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6256, 186},
    {I_VCMPNLE_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6265, 186},
    {I_VCMPNLE_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6274, 186},
    {I_VCMPNLE_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6283, 186},
    {I_VCMPNLE_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2030, 231},
    {I_VCMPNLE_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2040, 231},
    {I_VCMPNLE_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2050, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_SPS[] = {
    {I_VCMPORD_SPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6292, 186},
    {I_VCMPORD_SPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6301, 186},
    {I_VCMPORD_SPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6310, 186},
    {I_VCMPORD_SPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6319, 186},
    {I_VCMPORD_SPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2110, 231},
    {I_VCMPORD_SPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2120, 231},
    {I_VCMPORD_SPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2130, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_USPS[] = {
    {I_VCMPEQ_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6328, 186},
    {I_VCMPEQ_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6337, 186},
    {I_VCMPEQ_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6346, 186},
    {I_VCMPEQ_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6355, 186},
    {I_VCMPEQ_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2190, 231},
    {I_VCMPEQ_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2200, 231},
    {I_VCMPEQ_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2210, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_UQPS[] = {
    {I_VCMPNGE_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6364, 186},
    {I_VCMPNGE_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6373, 186},
    {I_VCMPNGE_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6382, 186},
    {I_VCMPNGE_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6391, 186},
    {I_VCMPNGE_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2270, 231},
    {I_VCMPNGE_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2280, 231},
    {I_VCMPNGE_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2290, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_UQPS[] = {
    {I_VCMPNGT_UQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6400, 186},
    {I_VCMPNGT_UQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6409, 186},
    {I_VCMPNGT_UQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6418, 186},
    {I_VCMPNGT_UQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6427, 186},
    {I_VCMPNGT_UQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2350, 231},
    {I_VCMPNGT_UQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2360, 231},
    {I_VCMPNGT_UQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2370, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OSPS[] = {
    {I_VCMPFALSE_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6436, 186},
    {I_VCMPFALSE_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6445, 186},
    {I_VCMPFALSE_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6454, 186},
    {I_VCMPFALSE_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6463, 186},
    {I_VCMPFALSE_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2430, 231},
    {I_VCMPFALSE_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2440, 231},
    {I_VCMPFALSE_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2450, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OSPS[] = {
    {I_VCMPNEQ_OSPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6472, 186},
    {I_VCMPNEQ_OSPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6481, 186},
    {I_VCMPNEQ_OSPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6490, 186},
    {I_VCMPNEQ_OSPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6499, 186},
    {I_VCMPNEQ_OSPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2510, 231},
    {I_VCMPNEQ_OSPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2520, 231},
    {I_VCMPNEQ_OSPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2530, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OQPS[] = {
    {I_VCMPGE_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6508, 186},
    {I_VCMPGE_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6517, 186},
    {I_VCMPGE_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6526, 186},
    {I_VCMPGE_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6535, 186},
    {I_VCMPGE_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2590, 231},
    {I_VCMPGE_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2600, 231},
    {I_VCMPGE_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2610, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OQPS[] = {
    {I_VCMPGT_OQPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6544, 186},
    {I_VCMPGT_OQPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6553, 186},
    {I_VCMPGT_OQPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6562, 186},
    {I_VCMPGT_OQPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6571, 186},
    {I_VCMPGT_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2670, 231},
    {I_VCMPGT_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2680, 231},
    {I_VCMPGT_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2690, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_USPS[] = {
    {I_VCMPTRUE_USPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+6580, 186},
    {I_VCMPTRUE_USPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+6589, 186},
    {I_VCMPTRUE_USPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+6598, 186},
    {I_VCMPTRUE_USPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+6607, 186},
    {I_VCMPTRUE_USPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2750, 231},
    {I_VCMPTRUE_USPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2760, 231},
    {I_VCMPTRUE_USPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+2770, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPPS[] = {
    {I_VCMPPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13185, 186},
    {I_VCMPPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13193, 186},
    {I_VCMPPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13201, 186},
    {I_VCMPPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13209, 186},
    {I_VCMPPS, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+8137, 231},
    {I_VCMPPS, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+8146, 231},
    {I_VCMPPS, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+8155, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OSSD[] = {
    {I_VCMPEQ_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6616, 186},
    {I_VCMPEQ_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6625, 186},
    {I_VCMPEQ_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6616, 186},
    {I_VCMPEQ_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6625, 186},
    {I_VCMPEQ_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1580, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQSD[] = {
    {I_VCMPEQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6634, 186},
    {I_VCMPEQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6643, 186},
    {I_VCMPEQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+300, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OSSD[] = {
    {I_VCMPLT_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6652, 186},
    {I_VCMPLT_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6661, 186},
    {I_VCMPLT_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+380, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLTSD[] = {
    {I_VCMPLTSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6652, 186},
    {I_VCMPLTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6661, 186},
    {I_VCMPLTSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+380, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OSSD[] = {
    {I_VCMPLE_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6670, 186},
    {I_VCMPLE_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6679, 186},
    {I_VCMPLE_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+460, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLESD[] = {
    {I_VCMPLESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6670, 186},
    {I_VCMPLESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6679, 186},
    {I_VCMPLESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+460, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_QSD[] = {
    {I_VCMPUNORD_QSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6688, 186},
    {I_VCMPUNORD_QSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6697, 186},
    {I_VCMPUNORD_QSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+540, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORDSD[] = {
    {I_VCMPUNORDSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6688, 186},
    {I_VCMPUNORDSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6697, 186},
    {I_VCMPUNORDSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+540, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_UQSD[] = {
    {I_VCMPNEQ_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6706, 186},
    {I_VCMPNEQ_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6715, 186},
    {I_VCMPNEQ_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+620, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQSD[] = {
    {I_VCMPNEQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6706, 186},
    {I_VCMPNEQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6715, 186},
    {I_VCMPNEQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+620, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_USSD[] = {
    {I_VCMPNLT_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6724, 186},
    {I_VCMPNLT_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6733, 186},
    {I_VCMPNLT_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+700, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLTSD[] = {
    {I_VCMPNLTSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6724, 186},
    {I_VCMPNLTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6733, 186},
    {I_VCMPNLTSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+700, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_USSD[] = {
    {I_VCMPNLE_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6742, 186},
    {I_VCMPNLE_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6751, 186},
    {I_VCMPNLE_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+780, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLESD[] = {
    {I_VCMPNLESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6742, 186},
    {I_VCMPNLESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6751, 186},
    {I_VCMPNLESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+780, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_QSD[] = {
    {I_VCMPORD_QSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6760, 186},
    {I_VCMPORD_QSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6769, 186},
    {I_VCMPORD_QSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+860, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORDSD[] = {
    {I_VCMPORDSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6760, 186},
    {I_VCMPORDSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6769, 186},
    {I_VCMPORDSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+860, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_UQSD[] = {
    {I_VCMPEQ_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6778, 186},
    {I_VCMPEQ_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6787, 186},
    {I_VCMPEQ_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+940, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_USSD[] = {
    {I_VCMPNGE_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6796, 186},
    {I_VCMPNGE_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6805, 186},
    {I_VCMPNGE_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1020, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGESD[] = {
    {I_VCMPNGESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6796, 186},
    {I_VCMPNGESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6805, 186},
    {I_VCMPNGESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1020, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_USSD[] = {
    {I_VCMPNGT_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6814, 186},
    {I_VCMPNGT_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6823, 186},
    {I_VCMPNGT_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1100, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGTSD[] = {
    {I_VCMPNGTSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6814, 186},
    {I_VCMPNGTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6823, 186},
    {I_VCMPNGTSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1100, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OQSD[] = {
    {I_VCMPFALSE_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6832, 186},
    {I_VCMPFALSE_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6841, 186},
    {I_VCMPFALSE_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1180, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSESD[] = {
    {I_VCMPFALSESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6832, 186},
    {I_VCMPFALSESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6841, 186},
    {I_VCMPFALSESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1180, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OQSD[] = {
    {I_VCMPNEQ_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6850, 186},
    {I_VCMPNEQ_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6859, 186},
    {I_VCMPNEQ_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1260, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OSSD[] = {
    {I_VCMPGE_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6868, 186},
    {I_VCMPGE_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6877, 186},
    {I_VCMPGE_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1340, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGESD[] = {
    {I_VCMPGESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6868, 186},
    {I_VCMPGESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6877, 186},
    {I_VCMPGESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1340, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OSSD[] = {
    {I_VCMPGT_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6886, 186},
    {I_VCMPGT_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6895, 186},
    {I_VCMPGT_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGTSD[] = {
    {I_VCMPGTSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6886, 186},
    {I_VCMPGTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6895, 186},
    {I_VCMPGTSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_UQSD[] = {
    {I_VCMPTRUE_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6904, 186},
    {I_VCMPTRUE_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6913, 186},
    {I_VCMPTRUE_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1500, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUESD[] = {
    {I_VCMPTRUESD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6904, 186},
    {I_VCMPTRUESD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6913, 186},
    {I_VCMPTRUESD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1500, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OQSD[] = {
    {I_VCMPLT_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6922, 186},
    {I_VCMPLT_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6931, 186},
    {I_VCMPLT_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OQSD[] = {
    {I_VCMPLE_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6940, 186},
    {I_VCMPLE_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6949, 186},
    {I_VCMPLE_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1740, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_SSD[] = {
    {I_VCMPUNORD_SSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6958, 186},
    {I_VCMPUNORD_SSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6967, 186},
    {I_VCMPUNORD_SSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1820, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_USSD[] = {
    {I_VCMPNEQ_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6976, 186},
    {I_VCMPNEQ_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+6985, 186},
    {I_VCMPNEQ_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1900, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_UQSD[] = {
    {I_VCMPNLT_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+6994, 186},
    {I_VCMPNLT_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7003, 186},
    {I_VCMPNLT_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1980, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_UQSD[] = {
    {I_VCMPNLE_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7012, 186},
    {I_VCMPNLE_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7021, 186},
    {I_VCMPNLE_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2060, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_SSD[] = {
    {I_VCMPORD_SSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7030, 186},
    {I_VCMPORD_SSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7039, 186},
    {I_VCMPORD_SSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2140, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_USSD[] = {
    {I_VCMPEQ_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7048, 186},
    {I_VCMPEQ_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7057, 186},
    {I_VCMPEQ_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2220, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_UQSD[] = {
    {I_VCMPNGE_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7066, 186},
    {I_VCMPNGE_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7075, 186},
    {I_VCMPNGE_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2300, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_UQSD[] = {
    {I_VCMPNGT_UQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7084, 186},
    {I_VCMPNGT_UQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7093, 186},
    {I_VCMPNGT_UQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2380, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OSSD[] = {
    {I_VCMPFALSE_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7102, 186},
    {I_VCMPFALSE_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7111, 186},
    {I_VCMPFALSE_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2460, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OSSD[] = {
    {I_VCMPNEQ_OSSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7120, 186},
    {I_VCMPNEQ_OSSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7129, 186},
    {I_VCMPNEQ_OSSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2540, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OQSD[] = {
    {I_VCMPGE_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7138, 186},
    {I_VCMPGE_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7147, 186},
    {I_VCMPGE_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2620, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OQSD[] = {
    {I_VCMPGT_OQSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7156, 186},
    {I_VCMPGT_OQSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7165, 186},
    {I_VCMPGT_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2700, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_USSD[] = {
    {I_VCMPTRUE_USSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7174, 186},
    {I_VCMPTRUE_USSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7183, 186},
    {I_VCMPTRUE_USSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2780, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPSD[] = {
    {I_VCMPSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13217, 186},
    {I_VCMPSD, 3, {XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13225, 186},
    {I_VCMPSD, 4, {KREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+8164, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OSSS[] = {
    {I_VCMPEQ_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7192, 186},
    {I_VCMPEQ_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7201, 186},
    {I_VCMPEQ_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7192, 186},
    {I_VCMPEQ_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7201, 186},
    {I_VCMPEQ_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1590, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQSS[] = {
    {I_VCMPEQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7210, 186},
    {I_VCMPEQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7219, 186},
    {I_VCMPEQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+310, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OSSS[] = {
    {I_VCMPLT_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7228, 186},
    {I_VCMPLT_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7237, 186},
    {I_VCMPLT_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+390, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLTSS[] = {
    {I_VCMPLTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7228, 186},
    {I_VCMPLTSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7237, 186},
    {I_VCMPLTSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+390, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OSSS[] = {
    {I_VCMPLE_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7246, 186},
    {I_VCMPLE_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7255, 186},
    {I_VCMPLE_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+470, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLESS[] = {
    {I_VCMPLESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7246, 186},
    {I_VCMPLESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7255, 186},
    {I_VCMPLESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+470, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_QSS[] = {
    {I_VCMPUNORD_QSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7264, 186},
    {I_VCMPUNORD_QSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7273, 186},
    {I_VCMPUNORD_QSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+550, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORDSS[] = {
    {I_VCMPUNORDSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7264, 186},
    {I_VCMPUNORDSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7273, 186},
    {I_VCMPUNORDSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+550, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_UQSS[] = {
    {I_VCMPNEQ_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7282, 186},
    {I_VCMPNEQ_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7291, 186},
    {I_VCMPNEQ_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+630, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQSS[] = {
    {I_VCMPNEQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7282, 186},
    {I_VCMPNEQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7291, 186},
    {I_VCMPNEQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+630, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_USSS[] = {
    {I_VCMPNLT_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7300, 186},
    {I_VCMPNLT_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7309, 186},
    {I_VCMPNLT_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+710, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLTSS[] = {
    {I_VCMPNLTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7300, 186},
    {I_VCMPNLTSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7309, 186},
    {I_VCMPNLTSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+710, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_USSS[] = {
    {I_VCMPNLE_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7318, 186},
    {I_VCMPNLE_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7327, 186},
    {I_VCMPNLE_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+790, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLESS[] = {
    {I_VCMPNLESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7318, 186},
    {I_VCMPNLESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7327, 186},
    {I_VCMPNLESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+790, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_QSS[] = {
    {I_VCMPORD_QSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7336, 186},
    {I_VCMPORD_QSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7345, 186},
    {I_VCMPORD_QSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+870, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORDSS[] = {
    {I_VCMPORDSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7336, 186},
    {I_VCMPORDSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7345, 186},
    {I_VCMPORDSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+870, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_UQSS[] = {
    {I_VCMPEQ_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7354, 186},
    {I_VCMPEQ_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7363, 186},
    {I_VCMPEQ_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+950, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_USSS[] = {
    {I_VCMPNGE_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7372, 186},
    {I_VCMPNGE_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7381, 186},
    {I_VCMPNGE_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1030, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGESS[] = {
    {I_VCMPNGESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7372, 186},
    {I_VCMPNGESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7381, 186},
    {I_VCMPNGESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1030, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_USSS[] = {
    {I_VCMPNGT_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7390, 186},
    {I_VCMPNGT_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7399, 186},
    {I_VCMPNGT_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1110, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGTSS[] = {
    {I_VCMPNGTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7390, 186},
    {I_VCMPNGTSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7399, 186},
    {I_VCMPNGTSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1110, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OQSS[] = {
    {I_VCMPFALSE_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7408, 186},
    {I_VCMPFALSE_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7417, 186},
    {I_VCMPFALSE_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1190, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSESS[] = {
    {I_VCMPFALSESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7408, 186},
    {I_VCMPFALSESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7417, 186},
    {I_VCMPFALSESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1190, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OQSS[] = {
    {I_VCMPNEQ_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7426, 186},
    {I_VCMPNEQ_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7435, 186},
    {I_VCMPNEQ_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1270, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OSSS[] = {
    {I_VCMPGE_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7444, 186},
    {I_VCMPGE_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7453, 186},
    {I_VCMPGE_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1350, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGESS[] = {
    {I_VCMPGESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7444, 186},
    {I_VCMPGESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7453, 186},
    {I_VCMPGESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1350, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OSSS[] = {
    {I_VCMPGT_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7462, 186},
    {I_VCMPGT_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7471, 186},
    {I_VCMPGT_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1430, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGTSS[] = {
    {I_VCMPGTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7462, 186},
    {I_VCMPGTSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7471, 186},
    {I_VCMPGTSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1430, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_UQSS[] = {
    {I_VCMPTRUE_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7480, 186},
    {I_VCMPTRUE_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7489, 186},
    {I_VCMPTRUE_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1510, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUESS[] = {
    {I_VCMPTRUESS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7480, 186},
    {I_VCMPTRUESS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7489, 186},
    {I_VCMPTRUESS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1510, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLT_OQSS[] = {
    {I_VCMPLT_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7498, 186},
    {I_VCMPLT_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7507, 186},
    {I_VCMPLT_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1670, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPLE_OQSS[] = {
    {I_VCMPLE_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7516, 186},
    {I_VCMPLE_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7525, 186},
    {I_VCMPLE_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1750, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPUNORD_SSS[] = {
    {I_VCMPUNORD_SSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7534, 186},
    {I_VCMPUNORD_SSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7543, 186},
    {I_VCMPUNORD_SSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1830, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_USSS[] = {
    {I_VCMPNEQ_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7552, 186},
    {I_VCMPNEQ_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7561, 186},
    {I_VCMPNEQ_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1910, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLT_UQSS[] = {
    {I_VCMPNLT_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7570, 186},
    {I_VCMPNLT_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7579, 186},
    {I_VCMPNLT_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+1990, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNLE_UQSS[] = {
    {I_VCMPNLE_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7588, 186},
    {I_VCMPNLE_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7597, 186},
    {I_VCMPNLE_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2070, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPORD_SSS[] = {
    {I_VCMPORD_SSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7606, 186},
    {I_VCMPORD_SSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7615, 186},
    {I_VCMPORD_SSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2150, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_USSS[] = {
    {I_VCMPEQ_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7624, 186},
    {I_VCMPEQ_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7633, 186},
    {I_VCMPEQ_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2230, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGE_UQSS[] = {
    {I_VCMPNGE_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7642, 186},
    {I_VCMPNGE_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7651, 186},
    {I_VCMPNGE_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2310, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNGT_UQSS[] = {
    {I_VCMPNGT_UQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7660, 186},
    {I_VCMPNGT_UQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7669, 186},
    {I_VCMPNGT_UQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2390, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPFALSE_OSSS[] = {
    {I_VCMPFALSE_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7678, 186},
    {I_VCMPFALSE_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7687, 186},
    {I_VCMPFALSE_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2470, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPNEQ_OSSS[] = {
    {I_VCMPNEQ_OSSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7696, 186},
    {I_VCMPNEQ_OSSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7705, 186},
    {I_VCMPNEQ_OSSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2550, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGE_OQSS[] = {
    {I_VCMPGE_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7714, 186},
    {I_VCMPGE_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7723, 186},
    {I_VCMPGE_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2630, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPGT_OQSS[] = {
    {I_VCMPGT_OQSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7732, 186},
    {I_VCMPGT_OQSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7741, 186},
    {I_VCMPGT_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2710, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPTRUE_USSS[] = {
    {I_VCMPTRUE_USSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+7750, 186},
    {I_VCMPTRUE_USSS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+7759, 186},
    {I_VCMPTRUE_USSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+2790, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPSS[] = {
    {I_VCMPSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13233, 186},
    {I_VCMPSS, 3, {XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13241, 186},
    {I_VCMPSS, 4, {KREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+8173, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCOMISD[] = {
    {I_VCOMISD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32313, 186},
    {I_VCOMISD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+16681, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCOMISS[] = {
    {I_VCOMISS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32320, 186},
    {I_VCOMISS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+16689, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTDQ2PD[] = {
    {I_VCVTDQ2PD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32327, 186},
    {I_VCVTDQ2PD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32334, 186},
    {I_VCVTDQ2PD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16793, 231},
    {I_VCVTDQ2PD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16801, 231},
    {I_VCVTDQ2PD, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+16809, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTDQ2PS[] = {
    {I_VCVTDQ2PS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32341, 186},
    {I_VCVTDQ2PS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32348, 186},
    {I_VCVTDQ2PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16817, 231},
    {I_VCVTDQ2PS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16825, 231},
    {I_VCVTDQ2PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+16833, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPD2DQ[] = {
    {I_VCVTPD2DQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32355, 186},
    {I_VCVTPD2DQ, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32355, 190},
    {I_VCVTPD2DQ, 2, {XMM_L16,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32362, 186},
    {I_VCVTPD2DQ, 2, {XMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32362, 191},
    {I_VCVTPD2DQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16841, 231},
    {I_VCVTPD2DQ, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16849, 231},
    {I_VCVTPD2DQ, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16857, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPD2PS[] = {
    {I_VCVTPD2PS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32369, 186},
    {I_VCVTPD2PS, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32369, 190},
    {I_VCVTPD2PS, 2, {XMM_L16,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32376, 186},
    {I_VCVTPD2PS, 2, {XMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32376, 191},
    {I_VCVTPD2PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16865, 231},
    {I_VCVTPD2PS, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16873, 231},
    {I_VCVTPD2PS, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16881, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2DQ[] = {
    {I_VCVTPS2DQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32383, 186},
    {I_VCVTPS2DQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32390, 186},
    {I_VCVTPS2DQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16985, 231},
    {I_VCVTPS2DQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+16993, 231},
    {I_VCVTPS2DQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17001, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2PD[] = {
    {I_VCVTPS2PD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32397, 186},
    {I_VCVTPS2PD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32404, 186},
    {I_VCVTPS2PD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17009, 231},
    {I_VCVTPS2PD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17017, 231},
    {I_VCVTPS2PD, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17025, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSD2SI[] = {
    {I_VCVTSD2SI, 2, {REG_GPR|BITS32,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32411, 186},
    {I_VCVTSD2SI, 2, {REG_GPR|BITS64,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32418, 192},
    {I_VCVTSD2SI, 2, {REG_GPR|BITS32,RM_XMM|BITS64,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17153, 232},
    {I_VCVTSD2SI, 2, {REG_GPR|BITS64,RM_XMM|BITS64,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17161, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSD2SS[] = {
    {I_VCVTSD2SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32425, 186},
    {I_VCVTSD2SS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32432, 186},
    {I_VCVTSD2SS, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17169, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSI2SD[] = {
    {I_VCVTSI2SD, 3, {XMM_L16,XMM_L16,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32439, 193},
    {I_VCVTSI2SD, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32446, 193},
    {I_VCVTSI2SD, 3, {XMM_L16,XMM_L16,MEMORY|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32439, 193},
    {I_VCVTSI2SD, 2, {XMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32446, 193},
    {I_VCVTSI2SD, 3, {XMM_L16,XMM_L16,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32453, 194},
    {I_VCVTSI2SD, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32460, 194},
    {I_VCVTSI2SD, 3, {XMMREG,XMMREG,RM_GPR|BITS32,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17193, 232},
    {I_VCVTSI2SD, 3, {XMMREG,XMMREG,RM_GPR|BITS64,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17201, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSI2SS[] = {
    {I_VCVTSI2SS, 3, {XMM_L16,XMM_L16,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32467, 193},
    {I_VCVTSI2SS, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32474, 193},
    {I_VCVTSI2SS, 3, {XMM_L16,XMM_L16,MEMORY|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32467, 193},
    {I_VCVTSI2SS, 2, {XMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32474, 193},
    {I_VCVTSI2SS, 3, {XMM_L16,XMM_L16,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32481, 194},
    {I_VCVTSI2SS, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32488, 194},
    {I_VCVTSI2SS, 3, {XMMREG,XMMREG,RM_GPR|BITS32,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17209, 232},
    {I_VCVTSI2SS, 3, {XMMREG,XMMREG,RM_GPR|BITS64,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17217, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSS2SD[] = {
    {I_VCVTSS2SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32495, 186},
    {I_VCVTSS2SD, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32502, 186},
    {I_VCVTSS2SD, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+17225, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSS2SI[] = {
    {I_VCVTSS2SI, 2, {REG_GPR|BITS32,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32509, 186},
    {I_VCVTSS2SI, 2, {REG_GPR|BITS64,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32516, 192},
    {I_VCVTSS2SI, 2, {REG_GPR|BITS32,RM_XMM|BITS32,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17233, 232},
    {I_VCVTSS2SI, 2, {REG_GPR|BITS64,RM_XMM|BITS32,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17241, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPD2DQ[] = {
    {I_VCVTTPD2DQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32523, 186},
    {I_VCVTTPD2DQ, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32523, 190},
    {I_VCVTTPD2DQ, 2, {XMM_L16,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32530, 186},
    {I_VCVTTPD2DQ, 2, {XMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32530, 191},
    {I_VCVTTPD2DQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17265, 231},
    {I_VCVTTPD2DQ, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17273, 231},
    {I_VCVTTPD2DQ, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+17281, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPS2DQ[] = {
    {I_VCVTTPS2DQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32537, 186},
    {I_VCVTTPS2DQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32544, 186},
    {I_VCVTTPS2DQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17361, 231},
    {I_VCVTTPS2DQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17369, 231},
    {I_VCVTTPS2DQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17377, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTSD2SI[] = {
    {I_VCVTTSD2SI, 2, {REG_GPR|BITS32,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32551, 186},
    {I_VCVTTSD2SI, 2, {REG_GPR|BITS64,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32558, 192},
    {I_VCVTTSD2SI, 2, {REG_GPR|BITS32,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17457, 232},
    {I_VCVTTSD2SI, 2, {REG_GPR|BITS64,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17465, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTSS2SI[] = {
    {I_VCVTTSS2SI, 2, {REG_GPR|BITS32,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32565, 186},
    {I_VCVTTSS2SI, 2, {REG_GPR|BITS64,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32572, 192},
    {I_VCVTTSS2SI, 2, {REG_GPR|BITS32,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17489, 232},
    {I_VCVTTSS2SI, 2, {REG_GPR|BITS64,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17497, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDIVPD[] = {
    {I_VDIVPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32579, 186},
    {I_VDIVPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32586, 186},
    {I_VDIVPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32593, 186},
    {I_VDIVPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32600, 186},
    {I_VDIVPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17649, 231},
    {I_VDIVPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17657, 231},
    {I_VDIVPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17665, 231},
    {I_VDIVPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17673, 231},
    {I_VDIVPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+17681, 232},
    {I_VDIVPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+17689, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDIVPS[] = {
    {I_VDIVPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32607, 186},
    {I_VDIVPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32614, 186},
    {I_VDIVPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32621, 186},
    {I_VDIVPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32628, 186},
    {I_VDIVPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17697, 231},
    {I_VDIVPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17705, 231},
    {I_VDIVPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17713, 231},
    {I_VDIVPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17721, 231},
    {I_VDIVPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+17729, 232},
    {I_VDIVPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17737, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDIVSD[] = {
    {I_VDIVSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32635, 186},
    {I_VDIVSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32642, 186},
    {I_VDIVSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17745, 232},
    {I_VDIVSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+17753, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDIVSS[] = {
    {I_VDIVSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32649, 186},
    {I_VDIVSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32656, 186},
    {I_VDIVSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17761, 232},
    {I_VDIVSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+17769, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDPPD[] = {
    {I_VDPPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13249, 186},
    {I_VDPPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13257, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDPPS[] = {
    {I_VDPPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13265, 186},
    {I_VDPPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13273, 186},
    {I_VDPPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13281, 186},
    {I_VDPPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13289, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTF128[] = {
    {I_VEXTRACTF128, 3, {RM_XMM_L16|BITS128,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13297, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTPS[] = {
    {I_VEXTRACTPS, 3, {RM_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13305, 186},
    {I_VEXTRACTPS, 3, {REG_GPR|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+8479, 232},
    {I_VEXTRACTPS, 3, {REG_GPR|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+8479, 232},
    {I_VEXTRACTPS, 3, {MEMORY|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+8479, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VHADDPD[] = {
    {I_VHADDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32663, 186},
    {I_VHADDPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32670, 186},
    {I_VHADDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32677, 186},
    {I_VHADDPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32684, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VHADDPS[] = {
    {I_VHADDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32691, 186},
    {I_VHADDPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32698, 186},
    {I_VHADDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32705, 186},
    {I_VHADDPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32712, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VHSUBPD[] = {
    {I_VHSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32719, 186},
    {I_VHSUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32726, 186},
    {I_VHSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32733, 186},
    {I_VHSUBPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32740, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VHSUBPS[] = {
    {I_VHSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32747, 186},
    {I_VHSUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32754, 186},
    {I_VHSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32761, 186},
    {I_VHSUBPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32768, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTF128[] = {
    {I_VINSERTF128, 4, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13313, 186},
    {I_VINSERTF128, 3, {YMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13321, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTPS[] = {
    {I_VINSERTPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13329, 186},
    {I_VINSERTPS, 3, {XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13337, 186},
    {I_VINSERTPS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9172, 232},
    {I_VINSERTPS, 3, {XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9181, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VLDDQU[] = {
    {I_VLDDQU, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32775, 186},
    {I_VLDDQU, 2, {YMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32782, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VLDQQU[] = {
    {I_VLDQQU, 2, {YMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32782, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VLDMXCSR[] = {
    {I_VLDMXCSR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+32789, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMASKMOVDQU[] = {
    {I_VMASKMOVDQU, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+32796, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMASKMOVPS[] = {
    {I_VMASKMOVPS, 3, {XMM_L16,XMM_L16,MEMORY|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32803, 186},
    {I_VMASKMOVPS, 3, {YMM_L16,YMM_L16,MEMORY|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32810, 186},
    {I_VMASKMOVPS, 3, {MEMORY|BITS128,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+32817, 190},
    {I_VMASKMOVPS, 3, {MEMORY|BITS256,YMM_L16,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+32824, 191},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMASKMOVPD[] = {
    {I_VMASKMOVPD, 3, {XMM_L16,XMM_L16,MEMORY|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32831, 186},
    {I_VMASKMOVPD, 3, {YMM_L16,YMM_L16,MEMORY|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32838, 186},
    {I_VMASKMOVPD, 3, {MEMORY|BITS128,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+32845, 186},
    {I_VMASKMOVPD, 3, {MEMORY|BITS256,YMM_L16,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+32852, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMAXPD[] = {
    {I_VMAXPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32859, 186},
    {I_VMAXPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32866, 186},
    {I_VMAXPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32873, 186},
    {I_VMAXPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32880, 186},
    {I_VMAXPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18961, 231},
    {I_VMAXPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+18969, 231},
    {I_VMAXPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18977, 231},
    {I_VMAXPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+18985, 231},
    {I_VMAXPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|SAE,0,0}, nasm_bytecodes+18993, 232},
    {I_VMAXPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+19001, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMAXPS[] = {
    {I_VMAXPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32887, 186},
    {I_VMAXPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32894, 186},
    {I_VMAXPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32901, 186},
    {I_VMAXPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32908, 186},
    {I_VMAXPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+19009, 231},
    {I_VMAXPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+19017, 231},
    {I_VMAXPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+19025, 231},
    {I_VMAXPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+19033, 231},
    {I_VMAXPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|SAE,0,0}, nasm_bytecodes+19041, 232},
    {I_VMAXPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+19049, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMAXSD[] = {
    {I_VMAXSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32915, 186},
    {I_VMAXSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+32922, 186},
    {I_VMAXSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+19057, 232},
    {I_VMAXSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+19065, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMAXSS[] = {
    {I_VMAXSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+32929, 186},
    {I_VMAXSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+32936, 186},
    {I_VMAXSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+19073, 232},
    {I_VMAXSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+19081, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMINPD[] = {
    {I_VMINPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32943, 186},
    {I_VMINPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32950, 186},
    {I_VMINPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32957, 186},
    {I_VMINPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32964, 186},
    {I_VMINPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+19089, 231},
    {I_VMINPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+19097, 231},
    {I_VMINPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+19105, 231},
    {I_VMINPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+19113, 231},
    {I_VMINPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|SAE,0,0}, nasm_bytecodes+19121, 232},
    {I_VMINPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+19129, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMINPS[] = {
    {I_VMINPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+32971, 186},
    {I_VMINPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+32978, 186},
    {I_VMINPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+32985, 186},
    {I_VMINPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+32992, 186},
    {I_VMINPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+19137, 231},
    {I_VMINPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+19145, 231},
    {I_VMINPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+19153, 231},
    {I_VMINPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+19161, 231},
    {I_VMINPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|SAE,0,0}, nasm_bytecodes+19169, 232},
    {I_VMINPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+19177, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMINSD[] = {
    {I_VMINSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+32999, 186},
    {I_VMINSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33006, 186},
    {I_VMINSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+19185, 232},
    {I_VMINSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+19193, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMINSS[] = {
    {I_VMINSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+33013, 186},
    {I_VMINSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+33020, 186},
    {I_VMINSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+19201, 232},
    {I_VMINSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+19209, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVAPD[] = {
    {I_VMOVAPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33027, 186},
    {I_VMOVAPD, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33034, 186},
    {I_VMOVAPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33041, 186},
    {I_VMOVAPD, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33048, 186},
    {I_VMOVAPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19217, 231},
    {I_VMOVAPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19225, 231},
    {I_VMOVAPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19233, 232},
    {I_VMOVAPD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19241, 231},
    {I_VMOVAPD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19249, 231},
    {I_VMOVAPD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19257, 232},
    {I_VMOVAPD, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19265, 231},
    {I_VMOVAPD, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19273, 231},
    {I_VMOVAPD, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19281, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVAPS[] = {
    {I_VMOVAPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33055, 186},
    {I_VMOVAPS, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33062, 186},
    {I_VMOVAPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33069, 186},
    {I_VMOVAPS, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33076, 186},
    {I_VMOVAPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19289, 231},
    {I_VMOVAPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19297, 231},
    {I_VMOVAPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19305, 232},
    {I_VMOVAPS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19313, 231},
    {I_VMOVAPS, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19321, 231},
    {I_VMOVAPS, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19329, 232},
    {I_VMOVAPS, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19337, 231},
    {I_VMOVAPS, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19345, 231},
    {I_VMOVAPS, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19353, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVD[] = {
    {I_VMOVD, 2, {XMM_L16,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+33083, 186},
    {I_VMOVD, 2, {RM_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33090, 186},
    {I_VMOVD, 2, {XMMREG,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+19361, 232},
    {I_VMOVD, 2, {RM_GPR|BITS32,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19369, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVQ[] = {
    {I_VMOVQ, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33097, 195},
    {I_VMOVQ, 2, {RM_XMM_L16|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33104, 195},
    {I_VMOVQ, 2, {XMM_L16,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33111, 194},
    {I_VMOVQ, 2, {RM_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33118, 194},
    {I_VMOVQ, 2, {XMMREG,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19913, 232},
    {I_VMOVQ, 2, {RM_GPR|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19921, 232},
    {I_VMOVQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19929, 232},
    {I_VMOVQ, 2, {RM_XMM|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19937, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDDUP[] = {
    {I_VMOVDDUP, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33125, 186},
    {I_VMOVDDUP, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33132, 186},
    {I_VMOVDDUP, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19377, 231},
    {I_VMOVDDUP, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19385, 231},
    {I_VMOVDDUP, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19393, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQA[] = {
    {I_VMOVDQA, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33139, 186},
    {I_VMOVDQA, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33146, 186},
    {I_VMOVDQA, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33153, 186},
    {I_VMOVDQA, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33160, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVQQA[] = {
    {I_VMOVQQA, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33153, 186},
    {I_VMOVQQA, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33160, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQU[] = {
    {I_VMOVDQU, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33167, 186},
    {I_VMOVDQU, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33174, 186},
    {I_VMOVDQU, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33181, 186},
    {I_VMOVDQU, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33188, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVQQU[] = {
    {I_VMOVQQU, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33181, 186},
    {I_VMOVQQU, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33188, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVHLPS[] = {
    {I_VMOVHLPS, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33195, 186},
    {I_VMOVHLPS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33202, 186},
    {I_VMOVHLPS, 3, {XMMREG,XMMREG,XMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+19689, 232},
    {I_VMOVHLPS, 2, {XMMREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19697, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVHPD[] = {
    {I_VMOVHPD, 3, {XMM_L16,XMM_L16,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+33209, 186},
    {I_VMOVHPD, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33216, 186},
    {I_VMOVHPD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33223, 186},
    {I_VMOVHPD, 3, {XMMREG,XMMREG,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+19705, 232},
    {I_VMOVHPD, 2, {XMMREG,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19713, 232},
    {I_VMOVHPD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19721, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVHPS[] = {
    {I_VMOVHPS, 3, {XMM_L16,XMM_L16,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+33230, 186},
    {I_VMOVHPS, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33237, 186},
    {I_VMOVHPS, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33244, 186},
    {I_VMOVHPS, 3, {XMMREG,XMMREG,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+19729, 232},
    {I_VMOVHPS, 2, {XMMREG,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19737, 232},
    {I_VMOVHPS, 2, {MEMORY|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19745, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVLHPS[] = {
    {I_VMOVLHPS, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33230, 186},
    {I_VMOVLHPS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33237, 186},
    {I_VMOVLHPS, 3, {XMMREG,XMMREG,XMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+19753, 232},
    {I_VMOVLHPS, 2, {XMMREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19761, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVLPD[] = {
    {I_VMOVLPD, 3, {XMM_L16,XMM_L16,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+33251, 186},
    {I_VMOVLPD, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33258, 186},
    {I_VMOVLPD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33265, 186},
    {I_VMOVLPD, 3, {XMMREG,XMMREG,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+19769, 232},
    {I_VMOVLPD, 2, {XMMREG,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19777, 232},
    {I_VMOVLPD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19785, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVLPS[] = {
    {I_VMOVLPS, 3, {XMM_L16,XMM_L16,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+33195, 186},
    {I_VMOVLPS, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33202, 186},
    {I_VMOVLPS, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33272, 186},
    {I_VMOVLPS, 3, {XMMREG,XMMREG,MEMORY|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+19793, 232},
    {I_VMOVLPS, 2, {XMMREG,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+19801, 232},
    {I_VMOVLPS, 2, {MEMORY|BITS64,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19809, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVMSKPD[] = {
    {I_VMOVMSKPD, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33279, 192},
    {I_VMOVMSKPD, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33279, 186},
    {I_VMOVMSKPD, 2, {REG_GPR|BITS64,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33286, 192},
    {I_VMOVMSKPD, 2, {REG_GPR|BITS32,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33286, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVMSKPS[] = {
    {I_VMOVMSKPS, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33293, 192},
    {I_VMOVMSKPS, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33293, 186},
    {I_VMOVMSKPS, 2, {REG_GPR|BITS64,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33300, 192},
    {I_VMOVMSKPS, 2, {REG_GPR|BITS32,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33300, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVNTDQ[] = {
    {I_VMOVNTDQ, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33307, 186},
    {I_VMOVNTDQ, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33314, 186},
    {I_VMOVNTDQ, 2, {MEMORY|BITS128,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19817, 231},
    {I_VMOVNTDQ, 2, {MEMORY|BITS256,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19825, 231},
    {I_VMOVNTDQ, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19833, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVNTQQ[] = {
    {I_VMOVNTQQ, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33314, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVNTDQA[] = {
    {I_VMOVNTDQA, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33321, 186},
    {I_VMOVNTDQA, 2, {YMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38074, 205},
    {I_VMOVNTDQA, 2, {XMMREG,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+19841, 231},
    {I_VMOVNTDQA, 2, {YMMREG,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+19849, 231},
    {I_VMOVNTDQA, 2, {ZMMREG,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+19857, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVNTPD[] = {
    {I_VMOVNTPD, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33328, 186},
    {I_VMOVNTPD, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33335, 186},
    {I_VMOVNTPD, 2, {MEMORY|BITS128,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19865, 231},
    {I_VMOVNTPD, 2, {MEMORY|BITS256,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19873, 231},
    {I_VMOVNTPD, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19881, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVNTPS[] = {
    {I_VMOVNTPS, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33342, 186},
    {I_VMOVNTPS, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33349, 186},
    {I_VMOVNTPS, 2, {MEMORY|BITS128,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19889, 231},
    {I_VMOVNTPS, 2, {MEMORY|BITS256,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19897, 231},
    {I_VMOVNTPS, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+19905, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVSD[] = {
    {I_VMOVSD, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33356, 186},
    {I_VMOVSD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33363, 186},
    {I_VMOVSD, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33370, 186},
    {I_VMOVSD, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33377, 186},
    {I_VMOVSD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33384, 186},
    {I_VMOVSD, 2, {MEMORY|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33391, 186},
    {I_VMOVSD, 2, {XMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19945, 232},
    {I_VMOVSD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+19953, 232},
    {I_VMOVSD, 3, {XMMREG,XMMREG,XMMREG,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19961, 232},
    {I_VMOVSD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19969, 232},
    {I_VMOVSD, 3, {XMMREG,XMMREG,XMMREG,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19977, 232},
    {I_VMOVSD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19985, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVSHDUP[] = {
    {I_VMOVSHDUP, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33398, 186},
    {I_VMOVSHDUP, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33405, 186},
    {I_VMOVSHDUP, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19993, 231},
    {I_VMOVSHDUP, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20001, 231},
    {I_VMOVSHDUP, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20009, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVSLDUP[] = {
    {I_VMOVSLDUP, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33412, 186},
    {I_VMOVSLDUP, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33419, 186},
    {I_VMOVSLDUP, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20017, 231},
    {I_VMOVSLDUP, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20025, 231},
    {I_VMOVSLDUP, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20033, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVSS[] = {
    {I_VMOVSS, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33426, 186},
    {I_VMOVSS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33433, 186},
    {I_VMOVSS, 2, {XMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+33440, 186},
    {I_VMOVSS, 3, {XMM_L16,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+33447, 186},
    {I_VMOVSS, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33454, 186},
    {I_VMOVSS, 2, {MEMORY|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33461, 186},
    {I_VMOVSS, 2, {XMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20041, 232},
    {I_VMOVSS, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20049, 232},
    {I_VMOVSS, 3, {XMMREG,XMMREG,XMMREG,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20057, 232},
    {I_VMOVSS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20065, 232},
    {I_VMOVSS, 3, {XMMREG,XMMREG,XMMREG,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20073, 232},
    {I_VMOVSS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20081, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVUPD[] = {
    {I_VMOVUPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33468, 186},
    {I_VMOVUPD, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33475, 186},
    {I_VMOVUPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33482, 186},
    {I_VMOVUPD, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33489, 186},
    {I_VMOVUPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20089, 231},
    {I_VMOVUPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20097, 231},
    {I_VMOVUPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20105, 232},
    {I_VMOVUPD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20113, 231},
    {I_VMOVUPD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20121, 231},
    {I_VMOVUPD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20129, 232},
    {I_VMOVUPD, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20137, 231},
    {I_VMOVUPD, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20145, 231},
    {I_VMOVUPD, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20153, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVUPS[] = {
    {I_VMOVUPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33496, 186},
    {I_VMOVUPS, 2, {RM_XMM_L16|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33503, 186},
    {I_VMOVUPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33510, 186},
    {I_VMOVUPS, 2, {RM_YMM_L16|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+33517, 186},
    {I_VMOVUPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20161, 231},
    {I_VMOVUPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20169, 231},
    {I_VMOVUPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20177, 232},
    {I_VMOVUPS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20185, 231},
    {I_VMOVUPS, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20193, 231},
    {I_VMOVUPS, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20201, 232},
    {I_VMOVUPS, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20209, 231},
    {I_VMOVUPS, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20217, 231},
    {I_VMOVUPS, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+20225, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMPSADBW[] = {
    {I_VMPSADBW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13345, 186},
    {I_VMPSADBW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13353, 186},
    {I_VMPSADBW, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15529, 205},
    {I_VMPSADBW, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15537, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMULPD[] = {
    {I_VMULPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33524, 186},
    {I_VMULPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33531, 186},
    {I_VMULPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+33538, 186},
    {I_VMULPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33545, 186},
    {I_VMULPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20233, 231},
    {I_VMULPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20241, 231},
    {I_VMULPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20249, 231},
    {I_VMULPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20257, 231},
    {I_VMULPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+20265, 232},
    {I_VMULPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+20273, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMULPS[] = {
    {I_VMULPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33552, 186},
    {I_VMULPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33559, 186},
    {I_VMULPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+33566, 186},
    {I_VMULPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33573, 186},
    {I_VMULPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20281, 231},
    {I_VMULPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20289, 231},
    {I_VMULPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20297, 231},
    {I_VMULPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20305, 231},
    {I_VMULPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+20313, 232},
    {I_VMULPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+20321, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMULSD[] = {
    {I_VMULSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+33580, 186},
    {I_VMULSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+33587, 186},
    {I_VMULSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+20329, 232},
    {I_VMULSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+20337, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMULSS[] = {
    {I_VMULSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+33594, 186},
    {I_VMULSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+33601, 186},
    {I_VMULSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+20345, 232},
    {I_VMULSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+20353, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VORPD[] = {
    {I_VORPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33608, 186},
    {I_VORPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33615, 186},
    {I_VORPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+33622, 186},
    {I_VORPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33629, 186},
    {I_VORPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20361, 233},
    {I_VORPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20369, 233},
    {I_VORPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20377, 233},
    {I_VORPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20385, 233},
    {I_VORPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20393, 234},
    {I_VORPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20401, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VORPS[] = {
    {I_VORPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33636, 186},
    {I_VORPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33643, 186},
    {I_VORPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+33650, 186},
    {I_VORPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+33657, 186},
    {I_VORPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20409, 233},
    {I_VORPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20417, 233},
    {I_VORPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20425, 233},
    {I_VORPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20433, 233},
    {I_VORPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20441, 234},
    {I_VORPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20449, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPABSB[] = {
    {I_VPABSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33664, 186},
    {I_VPABSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36814, 205},
    {I_VPABSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20457, 235},
    {I_VPABSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20465, 235},
    {I_VPABSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20473, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPABSW[] = {
    {I_VPABSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33671, 186},
    {I_VPABSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36821, 205},
    {I_VPABSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20529, 235},
    {I_VPABSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20537, 235},
    {I_VPABSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20545, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPABSD[] = {
    {I_VPABSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33678, 186},
    {I_VPABSD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36828, 205},
    {I_VPABSD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20481, 231},
    {I_VPABSD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20489, 231},
    {I_VPABSD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20497, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPACKSSWB[] = {
    {I_VPACKSSWB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33685, 186},
    {I_VPACKSSWB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33692, 186},
    {I_VPACKSSWB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36835, 205},
    {I_VPACKSSWB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36842, 205},
    {I_VPACKSSWB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20601, 235},
    {I_VPACKSSWB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20609, 235},
    {I_VPACKSSWB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20617, 235},
    {I_VPACKSSWB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20625, 235},
    {I_VPACKSSWB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20633, 236},
    {I_VPACKSSWB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20641, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPACKSSDW[] = {
    {I_VPACKSSDW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33699, 186},
    {I_VPACKSSDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33706, 186},
    {I_VPACKSSDW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36849, 205},
    {I_VPACKSSDW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36856, 205},
    {I_VPACKSSDW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20553, 235},
    {I_VPACKSSDW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20561, 235},
    {I_VPACKSSDW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20569, 235},
    {I_VPACKSSDW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20577, 235},
    {I_VPACKSSDW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20585, 236},
    {I_VPACKSSDW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20593, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPACKUSWB[] = {
    {I_VPACKUSWB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33713, 186},
    {I_VPACKUSWB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33720, 186},
    {I_VPACKUSWB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36877, 205},
    {I_VPACKUSWB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36884, 205},
    {I_VPACKUSWB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20697, 235},
    {I_VPACKUSWB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20705, 235},
    {I_VPACKUSWB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20713, 235},
    {I_VPACKUSWB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20721, 235},
    {I_VPACKUSWB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20729, 236},
    {I_VPACKUSWB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20737, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPACKUSDW[] = {
    {I_VPACKUSDW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33727, 186},
    {I_VPACKUSDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33734, 186},
    {I_VPACKUSDW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36863, 205},
    {I_VPACKUSDW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36870, 205},
    {I_VPACKUSDW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20649, 235},
    {I_VPACKUSDW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20657, 235},
    {I_VPACKUSDW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20665, 235},
    {I_VPACKUSDW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20673, 235},
    {I_VPACKUSDW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20681, 236},
    {I_VPACKUSDW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20689, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDB[] = {
    {I_VPADDB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33741, 186},
    {I_VPADDB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33748, 186},
    {I_VPADDB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36891, 205},
    {I_VPADDB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36898, 205},
    {I_VPADDB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20745, 235},
    {I_VPADDB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20753, 235},
    {I_VPADDB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20761, 235},
    {I_VPADDB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20769, 235},
    {I_VPADDB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20777, 236},
    {I_VPADDB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20785, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDW[] = {
    {I_VPADDW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33755, 186},
    {I_VPADDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33762, 186},
    {I_VPADDW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36905, 205},
    {I_VPADDW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36912, 205},
    {I_VPADDW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21081, 235},
    {I_VPADDW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21089, 235},
    {I_VPADDW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21097, 235},
    {I_VPADDW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21105, 235},
    {I_VPADDW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21113, 236},
    {I_VPADDW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21121, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDD[] = {
    {I_VPADDD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33769, 186},
    {I_VPADDD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33776, 186},
    {I_VPADDD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36919, 205},
    {I_VPADDD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36926, 205},
    {I_VPADDD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20793, 231},
    {I_VPADDD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20801, 231},
    {I_VPADDD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20809, 231},
    {I_VPADDD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20817, 231},
    {I_VPADDD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+20825, 232},
    {I_VPADDD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+20833, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDQ[] = {
    {I_VPADDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33783, 186},
    {I_VPADDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33790, 186},
    {I_VPADDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36933, 205},
    {I_VPADDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36940, 205},
    {I_VPADDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20841, 231},
    {I_VPADDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20849, 231},
    {I_VPADDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20857, 231},
    {I_VPADDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20865, 231},
    {I_VPADDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+20873, 232},
    {I_VPADDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20881, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDSB[] = {
    {I_VPADDSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33797, 186},
    {I_VPADDSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33804, 186},
    {I_VPADDSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36947, 205},
    {I_VPADDSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36954, 205},
    {I_VPADDSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20889, 235},
    {I_VPADDSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20897, 235},
    {I_VPADDSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20905, 235},
    {I_VPADDSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20913, 235},
    {I_VPADDSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20921, 236},
    {I_VPADDSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20929, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDSW[] = {
    {I_VPADDSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33811, 186},
    {I_VPADDSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33818, 186},
    {I_VPADDSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36961, 205},
    {I_VPADDSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36968, 205},
    {I_VPADDSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20937, 235},
    {I_VPADDSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20945, 235},
    {I_VPADDSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20953, 235},
    {I_VPADDSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20961, 235},
    {I_VPADDSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20969, 236},
    {I_VPADDSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20977, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDUSB[] = {
    {I_VPADDUSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33825, 186},
    {I_VPADDUSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33832, 186},
    {I_VPADDUSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36975, 205},
    {I_VPADDUSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36982, 205},
    {I_VPADDUSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20985, 235},
    {I_VPADDUSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+20993, 235},
    {I_VPADDUSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21001, 235},
    {I_VPADDUSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21009, 235},
    {I_VPADDUSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21017, 236},
    {I_VPADDUSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21025, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPADDUSW[] = {
    {I_VPADDUSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33839, 186},
    {I_VPADDUSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33846, 186},
    {I_VPADDUSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+36989, 205},
    {I_VPADDUSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36996, 205},
    {I_VPADDUSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21033, 235},
    {I_VPADDUSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21041, 235},
    {I_VPADDUSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21049, 235},
    {I_VPADDUSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21057, 235},
    {I_VPADDUSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21065, 236},
    {I_VPADDUSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21073, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPALIGNR[] = {
    {I_VPALIGNR, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13361, 186},
    {I_VPALIGNR, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13369, 186},
    {I_VPALIGNR, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15545, 205},
    {I_VPALIGNR, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15553, 205},
    {I_VPALIGNR, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9190, 235},
    {I_VPALIGNR, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9199, 235},
    {I_VPALIGNR, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9208, 235},
    {I_VPALIGNR, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9217, 235},
    {I_VPALIGNR, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9226, 236},
    {I_VPALIGNR, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9235, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPAND[] = {
    {I_VPAND, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33853, 186},
    {I_VPAND, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33860, 186},
    {I_VPAND, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37003, 205},
    {I_VPAND, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37010, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPANDN[] = {
    {I_VPANDN, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33867, 186},
    {I_VPANDN, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33874, 186},
    {I_VPANDN, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37017, 205},
    {I_VPANDN, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37024, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPAVGB[] = {
    {I_VPAVGB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33881, 186},
    {I_VPAVGB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33888, 186},
    {I_VPAVGB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37031, 205},
    {I_VPAVGB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37038, 205},
    {I_VPAVGB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21321, 235},
    {I_VPAVGB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21329, 235},
    {I_VPAVGB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21337, 235},
    {I_VPAVGB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21345, 235},
    {I_VPAVGB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21353, 236},
    {I_VPAVGB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21361, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPAVGW[] = {
    {I_VPAVGW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33895, 186},
    {I_VPAVGW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33902, 186},
    {I_VPAVGW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37045, 205},
    {I_VPAVGW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37052, 205},
    {I_VPAVGW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21369, 235},
    {I_VPAVGW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21377, 235},
    {I_VPAVGW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21385, 235},
    {I_VPAVGW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21393, 235},
    {I_VPAVGW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21401, 236},
    {I_VPAVGW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21409, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDVB[] = {
    {I_VPBLENDVB, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+13377, 186},
    {I_VPBLENDVB, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+13385, 186},
    {I_VPBLENDVB, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15561, 205},
    {I_VPBLENDVB, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15569, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDW[] = {
    {I_VPBLENDW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13393, 186},
    {I_VPBLENDW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13401, 186},
    {I_VPBLENDW, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15577, 205},
    {I_VPBLENDW, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15585, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPESTRI[] = {
    {I_VPCMPESTRI, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13409, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPESTRM[] = {
    {I_VPCMPESTRM, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13417, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPISTRI[] = {
    {I_VPCMPISTRI, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13425, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPISTRM[] = {
    {I_VPCMPISTRM, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13433, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQB[] = {
    {I_VPCMPEQB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33909, 186},
    {I_VPCMPEQB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33916, 186},
    {I_VPCMPEQB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37059, 205},
    {I_VPCMPEQB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37066, 205},
    {I_VPCMPEQB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21801, 235},
    {I_VPCMPEQB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21809, 235},
    {I_VPCMPEQB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21817, 236},
    {I_VPCMPEQB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2800, 235},
    {I_VPCMPEQB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2810, 235},
    {I_VPCMPEQB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2820, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQW[] = {
    {I_VPCMPEQW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33923, 186},
    {I_VPCMPEQW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33930, 186},
    {I_VPCMPEQW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37073, 205},
    {I_VPCMPEQW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37080, 205},
    {I_VPCMPEQW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21873, 235},
    {I_VPCMPEQW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21881, 235},
    {I_VPCMPEQW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21889, 236},
    {I_VPCMPEQW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3010, 235},
    {I_VPCMPEQW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3020, 235},
    {I_VPCMPEQW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3030, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQD[] = {
    {I_VPCMPEQD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33937, 186},
    {I_VPCMPEQD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33944, 186},
    {I_VPCMPEQD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37087, 205},
    {I_VPCMPEQD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37094, 205},
    {I_VPCMPEQD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21825, 231},
    {I_VPCMPEQD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21833, 231},
    {I_VPCMPEQD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21841, 232},
    {I_VPCMPEQD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2830, 231},
    {I_VPCMPEQD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2840, 231},
    {I_VPCMPEQD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2850, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQQ[] = {
    {I_VPCMPEQQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33951, 186},
    {I_VPCMPEQQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33958, 186},
    {I_VPCMPEQQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37101, 205},
    {I_VPCMPEQQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37108, 205},
    {I_VPCMPEQQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21849, 231},
    {I_VPCMPEQQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21857, 231},
    {I_VPCMPEQQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21865, 232},
    {I_VPCMPEQQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2860, 231},
    {I_VPCMPEQQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2870, 231},
    {I_VPCMPEQQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2880, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTB[] = {
    {I_VPCMPGTB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33965, 186},
    {I_VPCMPGTB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33972, 186},
    {I_VPCMPGTB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37115, 205},
    {I_VPCMPGTB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37122, 205},
    {I_VPCMPGTB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21897, 235},
    {I_VPCMPGTB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21905, 235},
    {I_VPCMPGTB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21913, 236},
    {I_VPCMPGTB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3280, 235},
    {I_VPCMPGTB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3290, 235},
    {I_VPCMPGTB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3300, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTW[] = {
    {I_VPCMPGTW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33979, 186},
    {I_VPCMPGTW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+33986, 186},
    {I_VPCMPGTW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37129, 205},
    {I_VPCMPGTW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37136, 205},
    {I_VPCMPGTW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21969, 235},
    {I_VPCMPGTW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21977, 235},
    {I_VPCMPGTW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21985, 236},
    {I_VPCMPGTW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3490, 235},
    {I_VPCMPGTW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3500, 235},
    {I_VPCMPGTW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3510, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTD[] = {
    {I_VPCMPGTD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+33993, 186},
    {I_VPCMPGTD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34000, 186},
    {I_VPCMPGTD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37143, 205},
    {I_VPCMPGTD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37150, 205},
    {I_VPCMPGTD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21921, 231},
    {I_VPCMPGTD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21929, 231},
    {I_VPCMPGTD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+21937, 232},
    {I_VPCMPGTD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3310, 231},
    {I_VPCMPGTD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3320, 231},
    {I_VPCMPGTD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3330, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTQ[] = {
    {I_VPCMPGTQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34007, 186},
    {I_VPCMPGTQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34014, 186},
    {I_VPCMPGTQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37157, 205},
    {I_VPCMPGTQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37164, 205},
    {I_VPCMPGTQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21945, 231},
    {I_VPCMPGTQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21953, 231},
    {I_VPCMPGTQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+21961, 232},
    {I_VPCMPGTQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3340, 231},
    {I_VPCMPGTQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3350, 231},
    {I_VPCMPGTQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3360, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMILPD[] = {
    {I_VPERMILPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34021, 186},
    {I_VPERMILPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34028, 186},
    {I_VPERMILPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+34035, 186},
    {I_VPERMILPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+34042, 186},
    {I_VPERMILPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13441, 186},
    {I_VPERMILPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13449, 186},
    {I_VPERMILPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9460, 231},
    {I_VPERMILPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9469, 231},
    {I_VPERMILPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9478, 232},
    {I_VPERMILPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22361, 231},
    {I_VPERMILPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22369, 231},
    {I_VPERMILPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22377, 231},
    {I_VPERMILPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22385, 231},
    {I_VPERMILPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22393, 232},
    {I_VPERMILPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22401, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMILPS[] = {
    {I_VPERMILPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34049, 186},
    {I_VPERMILPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34056, 186},
    {I_VPERMILPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+34063, 186},
    {I_VPERMILPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+34070, 186},
    {I_VPERMILPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13457, 186},
    {I_VPERMILPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13465, 186},
    {I_VPERMILPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9487, 231},
    {I_VPERMILPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9496, 231},
    {I_VPERMILPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9505, 232},
    {I_VPERMILPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22409, 231},
    {I_VPERMILPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22417, 231},
    {I_VPERMILPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22425, 231},
    {I_VPERMILPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22433, 231},
    {I_VPERMILPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22441, 232},
    {I_VPERMILPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22449, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERM2F128[] = {
    {I_VPERM2F128, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13473, 186},
    {I_VPERM2F128, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13481, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXTRB[] = {
    {I_VPEXTRB, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13489, 192},
    {I_VPEXTRB, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13489, 186},
    {I_VPEXTRB, 3, {MEMORY|BITS8,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13489, 186},
    {I_VPEXTRB, 3, {REG_GPR|BITS8,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9550, 236},
    {I_VPEXTRB, 3, {REG_GPR|BITS16,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9550, 236},
    {I_VPEXTRB, 3, {REG_GPR|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9550, 236},
    {I_VPEXTRB, 3, {REG_GPR|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9550, 236},
    {I_VPEXTRB, 3, {MEMORY|BITS8,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9550, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXTRW[] = {
    {I_VPEXTRW, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13497, 192},
    {I_VPEXTRW, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13497, 186},
    {I_VPEXTRW, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13505, 192},
    {I_VPEXTRW, 3, {REG_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13505, 186},
    {I_VPEXTRW, 3, {MEMORY|BITS16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13505, 186},
    {I_VPEXTRW, 3, {REG_GPR|BITS16,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9577, 236},
    {I_VPEXTRW, 3, {REG_GPR|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9577, 236},
    {I_VPEXTRW, 3, {REG_GPR|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9577, 236},
    {I_VPEXTRW, 3, {MEMORY|BITS16,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9577, 236},
    {I_VPEXTRW, 3, {REG_GPR|BITS16,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9586, 236},
    {I_VPEXTRW, 3, {REG_GPR|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9586, 236},
    {I_VPEXTRW, 3, {REG_GPR|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9586, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXTRD[] = {
    {I_VPEXTRD, 3, {REG_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13513, 192},
    {I_VPEXTRD, 3, {RM_GPR|BITS32,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13513, 186},
    {I_VPEXTRD, 3, {RM_GPR|BITS32,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9559, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXTRQ[] = {
    {I_VPEXTRQ, 3, {RM_GPR|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13521, 192},
    {I_VPEXTRQ, 3, {RM_GPR|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9568, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDW[] = {
    {I_VPHADDW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34077, 186},
    {I_VPHADDW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34084, 186},
    {I_VPHADDW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37171, 205},
    {I_VPHADDW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37178, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDD[] = {
    {I_VPHADDD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34091, 186},
    {I_VPHADDD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34098, 186},
    {I_VPHADDD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37185, 205},
    {I_VPHADDD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37192, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDSW[] = {
    {I_VPHADDSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34105, 186},
    {I_VPHADDSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34112, 186},
    {I_VPHADDSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37199, 205},
    {I_VPHADDSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37206, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHMINPOSUW[] = {
    {I_VPHMINPOSUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34119, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBW[] = {
    {I_VPHSUBW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34126, 186},
    {I_VPHSUBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34133, 186},
    {I_VPHSUBW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37213, 205},
    {I_VPHSUBW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37220, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBD[] = {
    {I_VPHSUBD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34140, 186},
    {I_VPHSUBD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34147, 186},
    {I_VPHSUBD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37227, 205},
    {I_VPHSUBD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37234, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBSW[] = {
    {I_VPHSUBSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34154, 186},
    {I_VPHSUBSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34161, 186},
    {I_VPHSUBSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37241, 205},
    {I_VPHSUBSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37248, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPINSRB[] = {
    {I_VPINSRB, 4, {XMM_L16,XMM_L16,MEMORY|BITS8,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13529, 186},
    {I_VPINSRB, 3, {XMM_L16,MEMORY|BITS8,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13537, 186},
    {I_VPINSRB, 4, {XMM_L16,XMM_L16,RM_GPR|BITS8,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13529, 186},
    {I_VPINSRB, 3, {XMM_L16,RM_GPR|BITS8,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13537, 186},
    {I_VPINSRB, 4, {XMM_L16,XMM_L16,REG_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13529, 186},
    {I_VPINSRB, 3, {XMM_L16,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13537, 186},
    {I_VPINSRB, 4, {XMMREG,XMMREG,REG_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9703, 236},
    {I_VPINSRB, 3, {XMMREG,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9712, 236},
    {I_VPINSRB, 4, {XMMREG,XMMREG,MEMORY|BITS8,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9703, 236},
    {I_VPINSRB, 3, {XMMREG,MEMORY|BITS8,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9712, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPINSRW[] = {
    {I_VPINSRW, 4, {XMM_L16,XMM_L16,MEMORY|BITS16,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13545, 186},
    {I_VPINSRW, 3, {XMM_L16,MEMORY|BITS16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13553, 186},
    {I_VPINSRW, 4, {XMM_L16,XMM_L16,RM_GPR|BITS16,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13545, 186},
    {I_VPINSRW, 3, {XMM_L16,RM_GPR|BITS16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13553, 186},
    {I_VPINSRW, 4, {XMM_L16,XMM_L16,REG_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13545, 186},
    {I_VPINSRW, 3, {XMM_L16,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13553, 186},
    {I_VPINSRW, 4, {XMMREG,XMMREG,REG_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9757, 236},
    {I_VPINSRW, 3, {XMMREG,REG_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9766, 236},
    {I_VPINSRW, 4, {XMMREG,XMMREG,MEMORY|BITS16,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9757, 236},
    {I_VPINSRW, 3, {XMMREG,MEMORY|BITS16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9766, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPINSRD[] = {
    {I_VPINSRD, 4, {XMM_L16,XMM_L16,MEMORY|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13561, 186},
    {I_VPINSRD, 3, {XMM_L16,MEMORY|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13569, 186},
    {I_VPINSRD, 4, {XMM_L16,XMM_L16,RM_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13561, 186},
    {I_VPINSRD, 3, {XMM_L16,RM_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13569, 186},
    {I_VPINSRD, 4, {XMMREG,XMMREG,RM_GPR|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9721, 234},
    {I_VPINSRD, 3, {XMMREG,RM_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9730, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPINSRQ[] = {
    {I_VPINSRQ, 4, {XMM_L16,XMM_L16,MEMORY|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13577, 192},
    {I_VPINSRQ, 3, {XMM_L16,MEMORY|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13585, 192},
    {I_VPINSRQ, 4, {XMM_L16,XMM_L16,RM_GPR|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13577, 192},
    {I_VPINSRQ, 3, {XMM_L16,RM_GPR|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13585, 192},
    {I_VPINSRQ, 4, {XMMREG,XMMREG,RM_GPR|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+9739, 234},
    {I_VPINSRQ, 3, {XMMREG,RM_GPR|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+9748, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADDWD[] = {
    {I_VPMADDWD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34168, 186},
    {I_VPMADDWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34175, 186},
    {I_VPMADDWD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37269, 205},
    {I_VPMADDWD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37276, 205},
    {I_VPMADDWD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22937, 235},
    {I_VPMADDWD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22945, 235},
    {I_VPMADDWD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22953, 235},
    {I_VPMADDWD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22961, 235},
    {I_VPMADDWD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22969, 236},
    {I_VPMADDWD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22977, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADDUBSW[] = {
    {I_VPMADDUBSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34182, 186},
    {I_VPMADDUBSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34189, 186},
    {I_VPMADDUBSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37255, 205},
    {I_VPMADDUBSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37262, 205},
    {I_VPMADDUBSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22889, 235},
    {I_VPMADDUBSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22897, 235},
    {I_VPMADDUBSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22905, 235},
    {I_VPMADDUBSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22913, 235},
    {I_VPMADDUBSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22921, 236},
    {I_VPMADDUBSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22929, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXSB[] = {
    {I_VPMAXSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34196, 186},
    {I_VPMAXSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34203, 186},
    {I_VPMAXSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37283, 205},
    {I_VPMAXSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37290, 205},
    {I_VPMAXSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22985, 235},
    {I_VPMAXSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22993, 235},
    {I_VPMAXSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23001, 235},
    {I_VPMAXSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23009, 235},
    {I_VPMAXSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23017, 236},
    {I_VPMAXSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23025, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXSW[] = {
    {I_VPMAXSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34210, 186},
    {I_VPMAXSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34217, 186},
    {I_VPMAXSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37297, 205},
    {I_VPMAXSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37304, 205},
    {I_VPMAXSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23129, 235},
    {I_VPMAXSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23137, 235},
    {I_VPMAXSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23145, 235},
    {I_VPMAXSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23153, 235},
    {I_VPMAXSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23161, 236},
    {I_VPMAXSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23169, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXSD[] = {
    {I_VPMAXSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34224, 186},
    {I_VPMAXSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34231, 186},
    {I_VPMAXSD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37311, 205},
    {I_VPMAXSD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37318, 205},
    {I_VPMAXSD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23033, 231},
    {I_VPMAXSD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23041, 231},
    {I_VPMAXSD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23049, 231},
    {I_VPMAXSD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23057, 231},
    {I_VPMAXSD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23065, 232},
    {I_VPMAXSD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23073, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXUB[] = {
    {I_VPMAXUB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34238, 186},
    {I_VPMAXUB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34245, 186},
    {I_VPMAXUB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37325, 205},
    {I_VPMAXUB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37332, 205},
    {I_VPMAXUB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23177, 235},
    {I_VPMAXUB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23185, 235},
    {I_VPMAXUB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23193, 235},
    {I_VPMAXUB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23201, 235},
    {I_VPMAXUB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23209, 236},
    {I_VPMAXUB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23217, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXUW[] = {
    {I_VPMAXUW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34252, 186},
    {I_VPMAXUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34259, 186},
    {I_VPMAXUW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37339, 205},
    {I_VPMAXUW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37346, 205},
    {I_VPMAXUW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23321, 235},
    {I_VPMAXUW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23329, 235},
    {I_VPMAXUW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23337, 235},
    {I_VPMAXUW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23345, 235},
    {I_VPMAXUW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23353, 236},
    {I_VPMAXUW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23361, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXUD[] = {
    {I_VPMAXUD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34266, 186},
    {I_VPMAXUD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34273, 186},
    {I_VPMAXUD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37353, 205},
    {I_VPMAXUD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37360, 205},
    {I_VPMAXUD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23225, 231},
    {I_VPMAXUD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23233, 231},
    {I_VPMAXUD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23241, 231},
    {I_VPMAXUD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23249, 231},
    {I_VPMAXUD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23257, 232},
    {I_VPMAXUD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23265, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINSB[] = {
    {I_VPMINSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34280, 186},
    {I_VPMINSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34287, 186},
    {I_VPMINSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37367, 205},
    {I_VPMINSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37374, 205},
    {I_VPMINSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23369, 235},
    {I_VPMINSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23377, 235},
    {I_VPMINSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23385, 235},
    {I_VPMINSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23393, 235},
    {I_VPMINSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23401, 236},
    {I_VPMINSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23409, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINSW[] = {
    {I_VPMINSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34294, 186},
    {I_VPMINSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34301, 186},
    {I_VPMINSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37381, 205},
    {I_VPMINSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37388, 205},
    {I_VPMINSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23513, 235},
    {I_VPMINSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23521, 235},
    {I_VPMINSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23529, 235},
    {I_VPMINSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23537, 235},
    {I_VPMINSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23545, 236},
    {I_VPMINSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23553, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINSD[] = {
    {I_VPMINSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34308, 186},
    {I_VPMINSD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34315, 186},
    {I_VPMINSD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37395, 205},
    {I_VPMINSD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37402, 205},
    {I_VPMINSD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23417, 231},
    {I_VPMINSD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23425, 231},
    {I_VPMINSD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23433, 231},
    {I_VPMINSD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23441, 231},
    {I_VPMINSD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23449, 232},
    {I_VPMINSD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23457, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINUB[] = {
    {I_VPMINUB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34322, 186},
    {I_VPMINUB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34329, 186},
    {I_VPMINUB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37409, 205},
    {I_VPMINUB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37416, 205},
    {I_VPMINUB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23561, 235},
    {I_VPMINUB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23569, 235},
    {I_VPMINUB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23577, 235},
    {I_VPMINUB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23585, 235},
    {I_VPMINUB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23593, 236},
    {I_VPMINUB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23601, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINUW[] = {
    {I_VPMINUW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34336, 186},
    {I_VPMINUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34343, 186},
    {I_VPMINUW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37423, 205},
    {I_VPMINUW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37430, 205},
    {I_VPMINUW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23705, 235},
    {I_VPMINUW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23713, 235},
    {I_VPMINUW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23721, 235},
    {I_VPMINUW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23729, 235},
    {I_VPMINUW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23737, 236},
    {I_VPMINUW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23745, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINUD[] = {
    {I_VPMINUD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34350, 186},
    {I_VPMINUD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34357, 186},
    {I_VPMINUD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37437, 205},
    {I_VPMINUD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37444, 205},
    {I_VPMINUD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23609, 231},
    {I_VPMINUD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23617, 231},
    {I_VPMINUD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23625, 231},
    {I_VPMINUD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23633, 231},
    {I_VPMINUD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+23641, 232},
    {I_VPMINUD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+23649, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVMSKB[] = {
    {I_VPMOVMSKB, 2, {REG_GPR|BITS64,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+34364, 192},
    {I_VPMOVMSKB, 2, {REG_GPR|BITS32,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+34364, 186},
    {I_VPMOVMSKB, 2, {REG_GPR|BITS32,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37451, 205},
    {I_VPMOVMSKB, 2, {REG_GPR|BITS64,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37451, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXBW[] = {
    {I_VPMOVSXBW, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34371, 186},
    {I_VPMOVSXBW, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37458, 205},
    {I_VPMOVSXBW, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24497, 235},
    {I_VPMOVSXBW, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24505, 235},
    {I_VPMOVSXBW, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24513, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXBD[] = {
    {I_VPMOVSXBD, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+34378, 186},
    {I_VPMOVSXBD, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+37465, 205},
    {I_VPMOVSXBD, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37465, 205},
    {I_VPMOVSXBD, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24449, 231},
    {I_VPMOVSXBD, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24457, 231},
    {I_VPMOVSXBD, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24465, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXBQ[] = {
    {I_VPMOVSXBQ, 2, {XMM_L16,RM_XMM_L16|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+34385, 186},
    {I_VPMOVSXBQ, 2, {YMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+37472, 205},
    {I_VPMOVSXBQ, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37472, 205},
    {I_VPMOVSXBQ, 2, {XMMREG,RM_XMM|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24473, 231},
    {I_VPMOVSXBQ, 2, {YMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24481, 231},
    {I_VPMOVSXBQ, 2, {ZMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24489, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXWD[] = {
    {I_VPMOVSXWD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34392, 186},
    {I_VPMOVSXWD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37479, 205},
    {I_VPMOVSXWD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24545, 231},
    {I_VPMOVSXWD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24553, 231},
    {I_VPMOVSXWD, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24561, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXWQ[] = {
    {I_VPMOVSXWQ, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+34399, 186},
    {I_VPMOVSXWQ, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+37486, 205},
    {I_VPMOVSXWQ, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37486, 205},
    {I_VPMOVSXWQ, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24569, 231},
    {I_VPMOVSXWQ, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24577, 231},
    {I_VPMOVSXWQ, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24585, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSXDQ[] = {
    {I_VPMOVSXDQ, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34406, 186},
    {I_VPMOVSXDQ, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37493, 205},
    {I_VPMOVSXDQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24521, 231},
    {I_VPMOVSXDQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24529, 231},
    {I_VPMOVSXDQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24537, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXBW[] = {
    {I_VPMOVZXBW, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34413, 186},
    {I_VPMOVZXBW, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37500, 205},
    {I_VPMOVZXBW, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25001, 235},
    {I_VPMOVZXBW, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25009, 235},
    {I_VPMOVZXBW, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25017, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXBD[] = {
    {I_VPMOVZXBD, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+34420, 186},
    {I_VPMOVZXBD, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+37507, 205},
    {I_VPMOVZXBD, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37507, 205},
    {I_VPMOVZXBD, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24953, 231},
    {I_VPMOVZXBD, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24961, 231},
    {I_VPMOVZXBD, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24969, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXBQ[] = {
    {I_VPMOVZXBQ, 2, {XMM_L16,RM_XMM_L16|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+34427, 186},
    {I_VPMOVZXBQ, 2, {YMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+37514, 205},
    {I_VPMOVZXBQ, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37514, 205},
    {I_VPMOVZXBQ, 2, {XMMREG,RM_XMM|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24977, 231},
    {I_VPMOVZXBQ, 2, {YMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24985, 231},
    {I_VPMOVZXBQ, 2, {ZMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24993, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXWD[] = {
    {I_VPMOVZXWD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34434, 186},
    {I_VPMOVZXWD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37521, 205},
    {I_VPMOVZXWD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25049, 231},
    {I_VPMOVZXWD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25057, 231},
    {I_VPMOVZXWD, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25065, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXWQ[] = {
    {I_VPMOVZXWQ, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+34441, 186},
    {I_VPMOVZXWQ, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+37528, 205},
    {I_VPMOVZXWQ, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+37528, 205},
    {I_VPMOVZXWQ, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25073, 231},
    {I_VPMOVZXWQ, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25081, 231},
    {I_VPMOVZXWQ, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25089, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVZXDQ[] = {
    {I_VPMOVZXDQ, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+34448, 186},
    {I_VPMOVZXDQ, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37535, 205},
    {I_VPMOVZXDQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25025, 231},
    {I_VPMOVZXDQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25033, 231},
    {I_VPMOVZXDQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25041, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULHUW[] = {
    {I_VPMULHUW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34455, 186},
    {I_VPMULHUW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34462, 186},
    {I_VPMULHUW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37570, 205},
    {I_VPMULHUW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37577, 205},
    {I_VPMULHUW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25193, 235},
    {I_VPMULHUW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25201, 235},
    {I_VPMULHUW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25209, 235},
    {I_VPMULHUW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25217, 235},
    {I_VPMULHUW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25225, 236},
    {I_VPMULHUW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25233, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULHRSW[] = {
    {I_VPMULHRSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34469, 186},
    {I_VPMULHRSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34476, 186},
    {I_VPMULHRSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37556, 205},
    {I_VPMULHRSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37563, 205},
    {I_VPMULHRSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25145, 235},
    {I_VPMULHRSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25153, 235},
    {I_VPMULHRSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25161, 235},
    {I_VPMULHRSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25169, 235},
    {I_VPMULHRSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25177, 236},
    {I_VPMULHRSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25185, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULHW[] = {
    {I_VPMULHW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34483, 186},
    {I_VPMULHW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34490, 186},
    {I_VPMULHW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37584, 205},
    {I_VPMULHW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37591, 205},
    {I_VPMULHW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25241, 235},
    {I_VPMULHW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25249, 235},
    {I_VPMULHW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25257, 235},
    {I_VPMULHW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25265, 235},
    {I_VPMULHW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25273, 236},
    {I_VPMULHW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25281, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULLW[] = {
    {I_VPMULLW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34497, 186},
    {I_VPMULLW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34504, 186},
    {I_VPMULLW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37598, 205},
    {I_VPMULLW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37605, 205},
    {I_VPMULLW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25385, 235},
    {I_VPMULLW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25393, 235},
    {I_VPMULLW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25401, 235},
    {I_VPMULLW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25409, 235},
    {I_VPMULLW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25417, 236},
    {I_VPMULLW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25425, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULLD[] = {
    {I_VPMULLD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34511, 186},
    {I_VPMULLD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34518, 186},
    {I_VPMULLD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37612, 205},
    {I_VPMULLD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37619, 205},
    {I_VPMULLD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25289, 231},
    {I_VPMULLD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25297, 231},
    {I_VPMULLD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25305, 231},
    {I_VPMULLD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25313, 231},
    {I_VPMULLD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25321, 232},
    {I_VPMULLD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25329, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULUDQ[] = {
    {I_VPMULUDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34525, 186},
    {I_VPMULUDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34532, 186},
    {I_VPMULUDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37626, 205},
    {I_VPMULUDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37633, 205},
    {I_VPMULUDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25481, 231},
    {I_VPMULUDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25489, 231},
    {I_VPMULUDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25497, 231},
    {I_VPMULUDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25505, 231},
    {I_VPMULUDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25513, 232},
    {I_VPMULUDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25521, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULDQ[] = {
    {I_VPMULDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34539, 186},
    {I_VPMULDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34546, 186},
    {I_VPMULDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37542, 205},
    {I_VPMULDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37549, 205},
    {I_VPMULDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25097, 231},
    {I_VPMULDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25105, 231},
    {I_VPMULDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25113, 231},
    {I_VPMULDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25121, 231},
    {I_VPMULDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25129, 232},
    {I_VPMULDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25137, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPOR[] = {
    {I_VPOR, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34553, 186},
    {I_VPOR, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34560, 186},
    {I_VPOR, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37640, 205},
    {I_VPOR, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37647, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSADBW[] = {
    {I_VPSADBW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34567, 186},
    {I_VPSADBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34574, 186},
    {I_VPSADBW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37654, 205},
    {I_VPSADBW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37661, 205},
    {I_VPSADBW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+25817, 235},
    {I_VPSADBW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+25825, 235},
    {I_VPSADBW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+25833, 235},
    {I_VPSADBW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+25841, 235},
    {I_VPSADBW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+25849, 236},
    {I_VPSADBW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+25857, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHUFB[] = {
    {I_VPSHUFB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34581, 186},
    {I_VPSHUFB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34588, 186},
    {I_VPSHUFB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37668, 205},
    {I_VPSHUFB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37675, 205},
    {I_VPSHUFB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25865, 235},
    {I_VPSHUFB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25873, 235},
    {I_VPSHUFB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25881, 235},
    {I_VPSHUFB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25889, 235},
    {I_VPSHUFB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25897, 236},
    {I_VPSHUFB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25905, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHUFD[] = {
    {I_VPSHUFD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13593, 186},
    {I_VPSHUFD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15593, 205},
    {I_VPSHUFD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10099, 231},
    {I_VPSHUFD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10108, 231},
    {I_VPSHUFD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10117, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHUFHW[] = {
    {I_VPSHUFHW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13601, 186},
    {I_VPSHUFHW, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15601, 205},
    {I_VPSHUFHW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10126, 235},
    {I_VPSHUFHW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10135, 235},
    {I_VPSHUFHW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10144, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHUFLW[] = {
    {I_VPSHUFLW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13609, 186},
    {I_VPSHUFLW, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15609, 205},
    {I_VPSHUFLW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10153, 235},
    {I_VPSHUFLW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10162, 235},
    {I_VPSHUFLW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10171, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSIGNB[] = {
    {I_VPSIGNB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34595, 186},
    {I_VPSIGNB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34602, 186},
    {I_VPSIGNB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37682, 205},
    {I_VPSIGNB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37689, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSIGNW[] = {
    {I_VPSIGNW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34609, 186},
    {I_VPSIGNW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34616, 186},
    {I_VPSIGNW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37696, 205},
    {I_VPSIGNW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37703, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSIGND[] = {
    {I_VPSIGND, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34623, 186},
    {I_VPSIGND, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34630, 186},
    {I_VPSIGND, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37710, 205},
    {I_VPSIGND, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37717, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLDQ[] = {
    {I_VPSLLDQ, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13617, 186},
    {I_VPSLLDQ, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13625, 186},
    {I_VPSLLDQ, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15617, 205},
    {I_VPSLLDQ, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15625, 205},
    {I_VPSLLDQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10234, 235},
    {I_VPSLLDQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10243, 235},
    {I_VPSLLDQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10252, 235},
    {I_VPSLLDQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10261, 235},
    {I_VPSLLDQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10270, 236},
    {I_VPSLLDQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10279, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLDQ[] = {
    {I_VPSRLDQ, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13633, 186},
    {I_VPSRLDQ, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13641, 186},
    {I_VPSRLDQ, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15713, 205},
    {I_VPSRLDQ, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15721, 205},
    {I_VPSRLDQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10612, 235},
    {I_VPSRLDQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10621, 235},
    {I_VPSRLDQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10630, 235},
    {I_VPSRLDQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10639, 235},
    {I_VPSRLDQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+10648, 236},
    {I_VPSRLDQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+10657, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLW[] = {
    {I_VPSLLW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34637, 186},
    {I_VPSLLW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34644, 186},
    {I_VPSLLW, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13649, 186},
    {I_VPSLLW, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13657, 186},
    {I_VPSLLW, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37724, 205},
    {I_VPSLLW, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37731, 205},
    {I_VPSLLW, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15633, 205},
    {I_VPSLLW, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15641, 205},
    {I_VPSLLW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26153, 235},
    {I_VPSLLW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26161, 235},
    {I_VPSLLW, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26169, 235},
    {I_VPSLLW, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26177, 235},
    {I_VPSLLW, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26185, 236},
    {I_VPSLLW, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26193, 236},
    {I_VPSLLW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10342, 235},
    {I_VPSLLW, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10351, 235},
    {I_VPSLLW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10360, 235},
    {I_VPSLLW, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10369, 235},
    {I_VPSLLW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10378, 236},
    {I_VPSLLW, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10387, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLD[] = {
    {I_VPSLLD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34651, 186},
    {I_VPSLLD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34658, 186},
    {I_VPSLLD, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13665, 186},
    {I_VPSLLD, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13673, 186},
    {I_VPSLLD, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37738, 205},
    {I_VPSLLD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37745, 205},
    {I_VPSLLD, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15649, 205},
    {I_VPSLLD, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15657, 205},
    {I_VPSLLD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25913, 231},
    {I_VPSLLD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25921, 231},
    {I_VPSLLD, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25929, 231},
    {I_VPSLLD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25937, 231},
    {I_VPSLLD, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25945, 232},
    {I_VPSLLD, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25953, 232},
    {I_VPSLLD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10180, 231},
    {I_VPSLLD, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10189, 231},
    {I_VPSLLD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10198, 231},
    {I_VPSLLD, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10207, 231},
    {I_VPSLLD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10216, 232},
    {I_VPSLLD, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10225, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLQ[] = {
    {I_VPSLLQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34665, 186},
    {I_VPSLLQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34672, 186},
    {I_VPSLLQ, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13681, 186},
    {I_VPSLLQ, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13689, 186},
    {I_VPSLLQ, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37752, 205},
    {I_VPSLLQ, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37759, 205},
    {I_VPSLLQ, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15665, 205},
    {I_VPSLLQ, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15673, 205},
    {I_VPSLLQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25961, 231},
    {I_VPSLLQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25969, 231},
    {I_VPSLLQ, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25977, 231},
    {I_VPSLLQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25985, 231},
    {I_VPSLLQ, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+25993, 232},
    {I_VPSLLQ, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26001, 232},
    {I_VPSLLQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10288, 231},
    {I_VPSLLQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10297, 231},
    {I_VPSLLQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10306, 231},
    {I_VPSLLQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10315, 231},
    {I_VPSLLQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10324, 232},
    {I_VPSLLQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10333, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAW[] = {
    {I_VPSRAW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34679, 186},
    {I_VPSRAW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34686, 186},
    {I_VPSRAW, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13697, 186},
    {I_VPSRAW, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13705, 186},
    {I_VPSRAW, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37766, 205},
    {I_VPSRAW, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37773, 205},
    {I_VPSRAW, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15681, 205},
    {I_VPSRAW, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15689, 205},
    {I_VPSRAW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26441, 235},
    {I_VPSRAW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26449, 235},
    {I_VPSRAW, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26457, 235},
    {I_VPSRAW, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26465, 235},
    {I_VPSRAW, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26473, 236},
    {I_VPSRAW, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26481, 236},
    {I_VPSRAW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10504, 235},
    {I_VPSRAW, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10513, 235},
    {I_VPSRAW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10522, 235},
    {I_VPSRAW, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10531, 235},
    {I_VPSRAW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10540, 236},
    {I_VPSRAW, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10549, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAD[] = {
    {I_VPSRAD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34693, 186},
    {I_VPSRAD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34700, 186},
    {I_VPSRAD, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13713, 186},
    {I_VPSRAD, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13721, 186},
    {I_VPSRAD, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37780, 205},
    {I_VPSRAD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37787, 205},
    {I_VPSRAD, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15697, 205},
    {I_VPSRAD, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15705, 205},
    {I_VPSRAD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26201, 231},
    {I_VPSRAD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26209, 231},
    {I_VPSRAD, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26217, 231},
    {I_VPSRAD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26225, 231},
    {I_VPSRAD, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26233, 232},
    {I_VPSRAD, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26241, 232},
    {I_VPSRAD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10396, 231},
    {I_VPSRAD, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10405, 231},
    {I_VPSRAD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10414, 231},
    {I_VPSRAD, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10423, 231},
    {I_VPSRAD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10432, 232},
    {I_VPSRAD, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10441, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLW[] = {
    {I_VPSRLW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34707, 186},
    {I_VPSRLW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34714, 186},
    {I_VPSRLW, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13729, 186},
    {I_VPSRLW, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13737, 186},
    {I_VPSRLW, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37794, 205},
    {I_VPSRLW, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37801, 205},
    {I_VPSRLW, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15729, 205},
    {I_VPSRLW, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15737, 205},
    {I_VPSRLW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26729, 235},
    {I_VPSRLW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26737, 235},
    {I_VPSRLW, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26745, 235},
    {I_VPSRLW, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26753, 235},
    {I_VPSRLW, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26761, 236},
    {I_VPSRLW, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26769, 236},
    {I_VPSRLW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10720, 235},
    {I_VPSRLW, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10729, 235},
    {I_VPSRLW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10738, 235},
    {I_VPSRLW, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10747, 235},
    {I_VPSRLW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10756, 236},
    {I_VPSRLW, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10765, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLD[] = {
    {I_VPSRLD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34721, 186},
    {I_VPSRLD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34728, 186},
    {I_VPSRLD, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13745, 186},
    {I_VPSRLD, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13753, 186},
    {I_VPSRLD, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37808, 205},
    {I_VPSRLD, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37815, 205},
    {I_VPSRLD, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15745, 205},
    {I_VPSRLD, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15753, 205},
    {I_VPSRLD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26489, 231},
    {I_VPSRLD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26497, 231},
    {I_VPSRLD, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26505, 231},
    {I_VPSRLD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26513, 231},
    {I_VPSRLD, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26521, 232},
    {I_VPSRLD, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26529, 232},
    {I_VPSRLD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10558, 231},
    {I_VPSRLD, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10567, 231},
    {I_VPSRLD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10576, 231},
    {I_VPSRLD, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10585, 231},
    {I_VPSRLD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10594, 232},
    {I_VPSRLD, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10603, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLQ[] = {
    {I_VPSRLQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34735, 186},
    {I_VPSRLQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34742, 186},
    {I_VPSRLQ, 3, {XMM_L16,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13761, 186},
    {I_VPSRLQ, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+13769, 186},
    {I_VPSRLQ, 3, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+37822, 205},
    {I_VPSRLQ, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+37829, 205},
    {I_VPSRLQ, 3, {YMM_L16,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15761, 205},
    {I_VPSRLQ, 2, {YMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15769, 205},
    {I_VPSRLQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26537, 231},
    {I_VPSRLQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26545, 231},
    {I_VPSRLQ, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26553, 231},
    {I_VPSRLQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26561, 231},
    {I_VPSRLQ, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26569, 232},
    {I_VPSRLQ, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26577, 232},
    {I_VPSRLQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10666, 231},
    {I_VPSRLQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10675, 231},
    {I_VPSRLQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10684, 231},
    {I_VPSRLQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10693, 231},
    {I_VPSRLQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10702, 232},
    {I_VPSRLQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10711, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTEST[] = {
    {I_VPTEST, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34749, 186},
    {I_VPTEST, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+34756, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBB[] = {
    {I_VPSUBB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34763, 186},
    {I_VPSUBB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34770, 186},
    {I_VPSUBB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37836, 205},
    {I_VPSUBB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37843, 205},
    {I_VPSUBB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26777, 235},
    {I_VPSUBB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26785, 235},
    {I_VPSUBB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26793, 235},
    {I_VPSUBB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26801, 235},
    {I_VPSUBB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26809, 236},
    {I_VPSUBB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26817, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBW[] = {
    {I_VPSUBW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34777, 186},
    {I_VPSUBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34784, 186},
    {I_VPSUBW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37850, 205},
    {I_VPSUBW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37857, 205},
    {I_VPSUBW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27113, 235},
    {I_VPSUBW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27121, 235},
    {I_VPSUBW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27129, 235},
    {I_VPSUBW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27137, 235},
    {I_VPSUBW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27145, 236},
    {I_VPSUBW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27153, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBD[] = {
    {I_VPSUBD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34791, 186},
    {I_VPSUBD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34798, 186},
    {I_VPSUBD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37864, 205},
    {I_VPSUBD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37871, 205},
    {I_VPSUBD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26825, 231},
    {I_VPSUBD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26833, 231},
    {I_VPSUBD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26841, 231},
    {I_VPSUBD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26849, 231},
    {I_VPSUBD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26857, 232},
    {I_VPSUBD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26865, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBQ[] = {
    {I_VPSUBQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34805, 186},
    {I_VPSUBQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34812, 186},
    {I_VPSUBQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37878, 205},
    {I_VPSUBQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37885, 205},
    {I_VPSUBQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26873, 231},
    {I_VPSUBQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26881, 231},
    {I_VPSUBQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26889, 231},
    {I_VPSUBQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26897, 231},
    {I_VPSUBQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26905, 232},
    {I_VPSUBQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26913, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBSB[] = {
    {I_VPSUBSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34819, 186},
    {I_VPSUBSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34826, 186},
    {I_VPSUBSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37892, 205},
    {I_VPSUBSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37899, 205},
    {I_VPSUBSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26921, 235},
    {I_VPSUBSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26929, 235},
    {I_VPSUBSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26937, 235},
    {I_VPSUBSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26945, 235},
    {I_VPSUBSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26953, 236},
    {I_VPSUBSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26961, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBSW[] = {
    {I_VPSUBSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34833, 186},
    {I_VPSUBSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34840, 186},
    {I_VPSUBSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37906, 205},
    {I_VPSUBSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37913, 205},
    {I_VPSUBSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26969, 235},
    {I_VPSUBSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26977, 235},
    {I_VPSUBSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26985, 235},
    {I_VPSUBSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26993, 235},
    {I_VPSUBSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27001, 236},
    {I_VPSUBSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27009, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBUSB[] = {
    {I_VPSUBUSB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34847, 186},
    {I_VPSUBUSB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34854, 186},
    {I_VPSUBUSB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37920, 205},
    {I_VPSUBUSB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37927, 205},
    {I_VPSUBUSB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27017, 235},
    {I_VPSUBUSB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27025, 235},
    {I_VPSUBUSB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27033, 235},
    {I_VPSUBUSB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27041, 235},
    {I_VPSUBUSB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27049, 236},
    {I_VPSUBUSB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27057, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSUBUSW[] = {
    {I_VPSUBUSW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34861, 186},
    {I_VPSUBUSW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34868, 186},
    {I_VPSUBUSW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37934, 205},
    {I_VPSUBUSW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37941, 205},
    {I_VPSUBUSW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27065, 235},
    {I_VPSUBUSW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27073, 235},
    {I_VPSUBUSW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27081, 235},
    {I_VPSUBUSW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27089, 235},
    {I_VPSUBUSW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27097, 236},
    {I_VPSUBUSW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27105, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKHBW[] = {
    {I_VPUNPCKHBW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34875, 186},
    {I_VPUNPCKHBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34882, 186},
    {I_VPUNPCKHBW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37948, 205},
    {I_VPUNPCKHBW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37955, 205},
    {I_VPUNPCKHBW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27353, 235},
    {I_VPUNPCKHBW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27361, 235},
    {I_VPUNPCKHBW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27369, 235},
    {I_VPUNPCKHBW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27377, 235},
    {I_VPUNPCKHBW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27385, 236},
    {I_VPUNPCKHBW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27393, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKHWD[] = {
    {I_VPUNPCKHWD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34889, 186},
    {I_VPUNPCKHWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34896, 186},
    {I_VPUNPCKHWD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37962, 205},
    {I_VPUNPCKHWD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37969, 205},
    {I_VPUNPCKHWD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27497, 235},
    {I_VPUNPCKHWD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27505, 235},
    {I_VPUNPCKHWD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27513, 235},
    {I_VPUNPCKHWD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27521, 235},
    {I_VPUNPCKHWD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27529, 236},
    {I_VPUNPCKHWD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27537, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKHDQ[] = {
    {I_VPUNPCKHDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34903, 186},
    {I_VPUNPCKHDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34910, 186},
    {I_VPUNPCKHDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37976, 205},
    {I_VPUNPCKHDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37983, 205},
    {I_VPUNPCKHDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27401, 231},
    {I_VPUNPCKHDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27409, 231},
    {I_VPUNPCKHDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27417, 231},
    {I_VPUNPCKHDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27425, 231},
    {I_VPUNPCKHDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27433, 232},
    {I_VPUNPCKHDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27441, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKHQDQ[] = {
    {I_VPUNPCKHQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34917, 186},
    {I_VPUNPCKHQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34924, 186},
    {I_VPUNPCKHQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+37990, 205},
    {I_VPUNPCKHQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+37997, 205},
    {I_VPUNPCKHQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27449, 231},
    {I_VPUNPCKHQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27457, 231},
    {I_VPUNPCKHQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27465, 231},
    {I_VPUNPCKHQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27473, 231},
    {I_VPUNPCKHQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27481, 232},
    {I_VPUNPCKHQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27489, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKLBW[] = {
    {I_VPUNPCKLBW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34931, 186},
    {I_VPUNPCKLBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34938, 186},
    {I_VPUNPCKLBW, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38004, 205},
    {I_VPUNPCKLBW, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38011, 205},
    {I_VPUNPCKLBW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27545, 235},
    {I_VPUNPCKLBW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27553, 235},
    {I_VPUNPCKLBW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27561, 235},
    {I_VPUNPCKLBW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27569, 235},
    {I_VPUNPCKLBW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27577, 236},
    {I_VPUNPCKLBW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27585, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKLWD[] = {
    {I_VPUNPCKLWD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34945, 186},
    {I_VPUNPCKLWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34952, 186},
    {I_VPUNPCKLWD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38018, 205},
    {I_VPUNPCKLWD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38025, 205},
    {I_VPUNPCKLWD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27689, 235},
    {I_VPUNPCKLWD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27697, 235},
    {I_VPUNPCKLWD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27705, 235},
    {I_VPUNPCKLWD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27713, 235},
    {I_VPUNPCKLWD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27721, 236},
    {I_VPUNPCKLWD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27729, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKLDQ[] = {
    {I_VPUNPCKLDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34959, 186},
    {I_VPUNPCKLDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34966, 186},
    {I_VPUNPCKLDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38032, 205},
    {I_VPUNPCKLDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38039, 205},
    {I_VPUNPCKLDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27593, 231},
    {I_VPUNPCKLDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27601, 231},
    {I_VPUNPCKLDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27609, 231},
    {I_VPUNPCKLDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27617, 231},
    {I_VPUNPCKLDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27625, 232},
    {I_VPUNPCKLDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27633, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPUNPCKLQDQ[] = {
    {I_VPUNPCKLQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34973, 186},
    {I_VPUNPCKLQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34980, 186},
    {I_VPUNPCKLQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38046, 205},
    {I_VPUNPCKLQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38053, 205},
    {I_VPUNPCKLQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27641, 231},
    {I_VPUNPCKLQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27649, 231},
    {I_VPUNPCKLQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27657, 231},
    {I_VPUNPCKLQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27665, 231},
    {I_VPUNPCKLQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27673, 232},
    {I_VPUNPCKLQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27681, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPXOR[] = {
    {I_VPXOR, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+34987, 186},
    {I_VPXOR, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+34994, 186},
    {I_VPXOR, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38060, 205},
    {I_VPXOR, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38067, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCPPS[] = {
    {I_VRCPPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35001, 186},
    {I_VRCPPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35008, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCPSS[] = {
    {I_VRCPSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35015, 186},
    {I_VRCPSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+35022, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRTPS[] = {
    {I_VRSQRTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35029, 186},
    {I_VRSQRTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35036, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRTSS[] = {
    {I_VRSQRTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35043, 186},
    {I_VRSQRTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+35050, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VROUNDPD[] = {
    {I_VROUNDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13777, 186},
    {I_VROUNDPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13785, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VROUNDPS[] = {
    {I_VROUNDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13793, 186},
    {I_VROUNDPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13801, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VROUNDSD[] = {
    {I_VROUNDSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13809, 186},
    {I_VROUNDSD, 3, {XMM_L16,RM_XMM_L16|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13817, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VROUNDSS[] = {
    {I_VROUNDSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13825, 186},
    {I_VROUNDSS, 3, {XMM_L16,RM_XMM_L16|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13833, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFPD[] = {
    {I_VSHUFPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13841, 186},
    {I_VSHUFPD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13849, 186},
    {I_VSHUFPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13857, 186},
    {I_VSHUFPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13865, 186},
    {I_VSHUFPD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11476, 231},
    {I_VSHUFPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11485, 231},
    {I_VSHUFPD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11494, 231},
    {I_VSHUFPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11503, 231},
    {I_VSHUFPD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11512, 232},
    {I_VSHUFPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11521, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFPS[] = {
    {I_VSHUFPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13873, 186},
    {I_VSHUFPS, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13881, 186},
    {I_VSHUFPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13889, 186},
    {I_VSHUFPS, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13897, 186},
    {I_VSHUFPS, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11530, 231},
    {I_VSHUFPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11539, 231},
    {I_VSHUFPS, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11548, 231},
    {I_VSHUFPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11557, 231},
    {I_VSHUFPS, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11566, 232},
    {I_VSHUFPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11575, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSQRTPD[] = {
    {I_VSQRTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35057, 186},
    {I_VSQRTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35064, 186},
    {I_VSQRTPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28217, 231},
    {I_VSQRTPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28225, 231},
    {I_VSQRTPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+28233, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSQRTPS[] = {
    {I_VSQRTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35071, 186},
    {I_VSQRTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35078, 186},
    {I_VSQRTPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28241, 231},
    {I_VSQRTPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28249, 231},
    {I_VSQRTPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+28257, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSQRTSD[] = {
    {I_VSQRTSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35085, 186},
    {I_VSQRTSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+35092, 186},
    {I_VSQRTSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28265, 232},
    {I_VSQRTSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28273, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSQRTSS[] = {
    {I_VSQRTSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35099, 186},
    {I_VSQRTSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+35106, 186},
    {I_VSQRTSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28281, 232},
    {I_VSQRTSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28289, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSTMXCSR[] = {
    {I_VSTMXCSR, 1, {MEMORY|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+35113, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSUBPD[] = {
    {I_VSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35120, 186},
    {I_VSUBPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35127, 186},
    {I_VSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35134, 186},
    {I_VSUBPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35141, 186},
    {I_VSUBPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28297, 231},
    {I_VSUBPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28305, 231},
    {I_VSUBPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28313, 231},
    {I_VSUBPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28321, 231},
    {I_VSUBPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+28329, 232},
    {I_VSUBPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+28337, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSUBPS[] = {
    {I_VSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35148, 186},
    {I_VSUBPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35155, 186},
    {I_VSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35162, 186},
    {I_VSUBPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35169, 186},
    {I_VSUBPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28345, 231},
    {I_VSUBPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28353, 231},
    {I_VSUBPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28361, 231},
    {I_VSUBPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28369, 231},
    {I_VSUBPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+28377, 232},
    {I_VSUBPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+28385, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSUBSD[] = {
    {I_VSUBSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35176, 186},
    {I_VSUBSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+35183, 186},
    {I_VSUBSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28393, 232},
    {I_VSUBSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28401, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSUBSS[] = {
    {I_VSUBSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35190, 186},
    {I_VSUBSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+35197, 186},
    {I_VSUBSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28409, 232},
    {I_VSUBSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28417, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VTESTPS[] = {
    {I_VTESTPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35204, 186},
    {I_VTESTPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35211, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VTESTPD[] = {
    {I_VTESTPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35218, 186},
    {I_VTESTPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35225, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUCOMISD[] = {
    {I_VUCOMISD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+35232, 186},
    {I_VUCOMISD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+28425, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUCOMISS[] = {
    {I_VUCOMISS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+35239, 186},
    {I_VUCOMISS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+28433, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUNPCKHPD[] = {
    {I_VUNPCKHPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35246, 186},
    {I_VUNPCKHPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35253, 186},
    {I_VUNPCKHPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35260, 186},
    {I_VUNPCKHPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35267, 186},
    {I_VUNPCKHPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28441, 231},
    {I_VUNPCKHPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28449, 231},
    {I_VUNPCKHPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28457, 231},
    {I_VUNPCKHPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28465, 231},
    {I_VUNPCKHPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28473, 232},
    {I_VUNPCKHPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28481, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUNPCKHPS[] = {
    {I_VUNPCKHPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35274, 186},
    {I_VUNPCKHPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35281, 186},
    {I_VUNPCKHPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35288, 186},
    {I_VUNPCKHPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35295, 186},
    {I_VUNPCKHPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28489, 231},
    {I_VUNPCKHPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28497, 231},
    {I_VUNPCKHPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28505, 231},
    {I_VUNPCKHPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28513, 231},
    {I_VUNPCKHPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28521, 232},
    {I_VUNPCKHPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28529, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUNPCKLPD[] = {
    {I_VUNPCKLPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35302, 186},
    {I_VUNPCKLPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35309, 186},
    {I_VUNPCKLPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35316, 186},
    {I_VUNPCKLPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35323, 186},
    {I_VUNPCKLPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28537, 231},
    {I_VUNPCKLPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28545, 231},
    {I_VUNPCKLPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28553, 231},
    {I_VUNPCKLPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28561, 231},
    {I_VUNPCKLPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28569, 232},
    {I_VUNPCKLPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28577, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VUNPCKLPS[] = {
    {I_VUNPCKLPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35330, 186},
    {I_VUNPCKLPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35337, 186},
    {I_VUNPCKLPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35344, 186},
    {I_VUNPCKLPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35351, 186},
    {I_VUNPCKLPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28585, 231},
    {I_VUNPCKLPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28593, 231},
    {I_VUNPCKLPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28601, 231},
    {I_VUNPCKLPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28609, 231},
    {I_VUNPCKLPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28617, 232},
    {I_VUNPCKLPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VXORPD[] = {
    {I_VXORPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35358, 186},
    {I_VXORPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35365, 186},
    {I_VXORPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35372, 186},
    {I_VXORPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35379, 186},
    {I_VXORPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28633, 233},
    {I_VXORPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28641, 233},
    {I_VXORPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28649, 233},
    {I_VXORPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28657, 233},
    {I_VXORPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28665, 234},
    {I_VXORPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28673, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VXORPS[] = {
    {I_VXORPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35386, 186},
    {I_VXORPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+35393, 186},
    {I_VXORPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35400, 186},
    {I_VXORPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+35407, 186},
    {I_VXORPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28681, 233},
    {I_VXORPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28689, 233},
    {I_VXORPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28697, 233},
    {I_VXORPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28705, 233},
    {I_VXORPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28713, 234},
    {I_VXORPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28721, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VZEROALL[] = {
    {I_VZEROALL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41675, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_VZEROUPPER[] = {
    {I_VZEROUPPER, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41681, 186},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCLMULLQLQDQ[] = {
    {I_PCLMULLQLQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7768, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCLMULHQLQDQ[] = {
    {I_PCLMULHQLQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7777, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCLMULLQHQDQ[] = {
    {I_PCLMULLQHQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7786, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCLMULHQHQDQ[] = {
    {I_PCLMULHQHQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7795, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCLMULQDQ[] = {
    {I_PCLMULQDQ, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13905, 185},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCLMULLQLQDQ[] = {
    {I_VPCLMULLQLQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+7804, 186},
    {I_VPCLMULLQLQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7813, 186},
    {I_VPCLMULLQLQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+7876, 196},
    {I_VPCLMULLQLQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+7885, 196},
    {I_VPCLMULLQLQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+0, 197},
    {I_VPCLMULLQLQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+10, 197},
    {I_VPCLMULLQLQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+80, 197},
    {I_VPCLMULLQLQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+90, 197},
    {I_VPCLMULLQLQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+160, 198},
    {I_VPCLMULLQLQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+170, 198},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCLMULHQLQDQ[] = {
    {I_VPCLMULHQLQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+7822, 186},
    {I_VPCLMULHQLQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7831, 186},
    {I_VPCLMULHQLQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+7894, 196},
    {I_VPCLMULHQLQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+7903, 196},
    {I_VPCLMULHQLQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+20, 197},
    {I_VPCLMULHQLQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+30, 197},
    {I_VPCLMULHQLQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+100, 197},
    {I_VPCLMULHQLQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+110, 197},
    {I_VPCLMULHQLQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+180, 198},
    {I_VPCLMULHQLQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+190, 198},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCLMULLQHQDQ[] = {
    {I_VPCLMULLQHQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+7840, 186},
    {I_VPCLMULLQHQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7849, 186},
    {I_VPCLMULLQHQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+7912, 196},
    {I_VPCLMULLQHQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+7921, 196},
    {I_VPCLMULLQHQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+40, 197},
    {I_VPCLMULLQHQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+50, 197},
    {I_VPCLMULLQHQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+120, 197},
    {I_VPCLMULLQHQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+130, 197},
    {I_VPCLMULLQHQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+200, 198},
    {I_VPCLMULLQHQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+210, 198},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCLMULHQHQDQ[] = {
    {I_VPCLMULHQHQDQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+7858, 186},
    {I_VPCLMULHQHQDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+7867, 186},
    {I_VPCLMULHQHQDQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+7930, 196},
    {I_VPCLMULHQHQDQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+7939, 196},
    {I_VPCLMULHQHQDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+60, 197},
    {I_VPCLMULHQHQDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+70, 197},
    {I_VPCLMULHQHQDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+140, 197},
    {I_VPCLMULHQHQDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+150, 197},
    {I_VPCLMULHQHQDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, NO_DECORATOR, nasm_bytecodes+220, 198},
    {I_VPCLMULHQHQDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+230, 198},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCLMULQDQ[] = {
    {I_VPCLMULQDQ, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13913, 186},
    {I_VPCLMULQDQ, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13921, 186},
    {I_VPCLMULQDQ, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+13929, 196},
    {I_VPCLMULQDQ, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13937, 196},
    {I_VPCLMULQDQ, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+7948, 197},
    {I_VPCLMULQDQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+7957, 197},
    {I_VPCLMULQDQ, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+7966, 197},
    {I_VPCLMULQDQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+7975, 197},
    {I_VPCLMULQDQ, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+7984, 198},
    {I_VPCLMULQDQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+7993, 198},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD132PS[] = {
    {I_VFMADD132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35414, 199},
    {I_VFMADD132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35421, 199},
    {I_VFMADD132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17865, 231},
    {I_VFMADD132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17873, 231},
    {I_VFMADD132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+17881, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD132PD[] = {
    {I_VFMADD132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35428, 199},
    {I_VFMADD132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35435, 199},
    {I_VFMADD132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17841, 231},
    {I_VFMADD132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17849, 231},
    {I_VFMADD132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+17857, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD312PS[] = {
    {I_VFMADD312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35414, 199},
    {I_VFMADD312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35421, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD312PD[] = {
    {I_VFMADD312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35428, 199},
    {I_VFMADD312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35435, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD213PS[] = {
    {I_VFMADD213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35442, 199},
    {I_VFMADD213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35449, 199},
    {I_VFMADD213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17929, 231},
    {I_VFMADD213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17937, 231},
    {I_VFMADD213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+17945, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD213PD[] = {
    {I_VFMADD213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35456, 199},
    {I_VFMADD213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35463, 199},
    {I_VFMADD213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17905, 231},
    {I_VFMADD213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17913, 231},
    {I_VFMADD213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+17921, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD123PS[] = {
    {I_VFMADD123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35442, 199},
    {I_VFMADD123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35449, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD123PD[] = {
    {I_VFMADD123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35456, 199},
    {I_VFMADD123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35463, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD231PS[] = {
    {I_VFMADD231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35470, 199},
    {I_VFMADD231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35477, 199},
    {I_VFMADD231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+17993, 231},
    {I_VFMADD231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18001, 231},
    {I_VFMADD231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18009, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD231PD[] = {
    {I_VFMADD231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35484, 199},
    {I_VFMADD231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35491, 199},
    {I_VFMADD231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17969, 231},
    {I_VFMADD231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+17977, 231},
    {I_VFMADD231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+17985, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD321PS[] = {
    {I_VFMADD321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35470, 199},
    {I_VFMADD321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35477, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD321PD[] = {
    {I_VFMADD321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35484, 199},
    {I_VFMADD321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35491, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB132PS[] = {
    {I_VFMADDSUB132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35498, 199},
    {I_VFMADDSUB132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35505, 199},
    {I_VFMADDSUB132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18057, 231},
    {I_VFMADDSUB132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18065, 231},
    {I_VFMADDSUB132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18073, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB132PD[] = {
    {I_VFMADDSUB132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35512, 199},
    {I_VFMADDSUB132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35519, 199},
    {I_VFMADDSUB132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18033, 231},
    {I_VFMADDSUB132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18041, 231},
    {I_VFMADDSUB132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18049, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB312PS[] = {
    {I_VFMADDSUB312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35498, 199},
    {I_VFMADDSUB312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35505, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB312PD[] = {
    {I_VFMADDSUB312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35512, 199},
    {I_VFMADDSUB312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35519, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB213PS[] = {
    {I_VFMADDSUB213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35526, 199},
    {I_VFMADDSUB213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35533, 199},
    {I_VFMADDSUB213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18105, 231},
    {I_VFMADDSUB213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18113, 231},
    {I_VFMADDSUB213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18121, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB213PD[] = {
    {I_VFMADDSUB213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35540, 199},
    {I_VFMADDSUB213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35547, 199},
    {I_VFMADDSUB213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18081, 231},
    {I_VFMADDSUB213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18089, 231},
    {I_VFMADDSUB213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18097, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB123PS[] = {
    {I_VFMADDSUB123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35526, 199},
    {I_VFMADDSUB123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35533, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB123PD[] = {
    {I_VFMADDSUB123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35540, 199},
    {I_VFMADDSUB123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35547, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB231PS[] = {
    {I_VFMADDSUB231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35554, 199},
    {I_VFMADDSUB231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35561, 199},
    {I_VFMADDSUB231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18153, 231},
    {I_VFMADDSUB231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18161, 231},
    {I_VFMADDSUB231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18169, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB231PD[] = {
    {I_VFMADDSUB231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35568, 199},
    {I_VFMADDSUB231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35575, 199},
    {I_VFMADDSUB231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18129, 231},
    {I_VFMADDSUB231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18137, 231},
    {I_VFMADDSUB231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18145, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB321PS[] = {
    {I_VFMADDSUB321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35554, 199},
    {I_VFMADDSUB321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35561, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUB321PD[] = {
    {I_VFMADDSUB321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35568, 199},
    {I_VFMADDSUB321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35575, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB132PS[] = {
    {I_VFMSUB132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35582, 199},
    {I_VFMSUB132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35589, 199},
    {I_VFMSUB132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18201, 231},
    {I_VFMSUB132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18209, 231},
    {I_VFMSUB132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18217, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB132PD[] = {
    {I_VFMSUB132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35596, 199},
    {I_VFMSUB132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35603, 199},
    {I_VFMSUB132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18177, 231},
    {I_VFMSUB132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18185, 231},
    {I_VFMSUB132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18193, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB312PS[] = {
    {I_VFMSUB312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35582, 199},
    {I_VFMSUB312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35589, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB312PD[] = {
    {I_VFMSUB312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35596, 199},
    {I_VFMSUB312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35603, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB213PS[] = {
    {I_VFMSUB213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35610, 199},
    {I_VFMSUB213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35617, 199},
    {I_VFMSUB213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18265, 231},
    {I_VFMSUB213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18273, 231},
    {I_VFMSUB213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18281, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB213PD[] = {
    {I_VFMSUB213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35624, 199},
    {I_VFMSUB213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35631, 199},
    {I_VFMSUB213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18241, 231},
    {I_VFMSUB213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18249, 231},
    {I_VFMSUB213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18257, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB123PS[] = {
    {I_VFMSUB123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35610, 199},
    {I_VFMSUB123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35617, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB123PD[] = {
    {I_VFMSUB123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35624, 199},
    {I_VFMSUB123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35631, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB231PS[] = {
    {I_VFMSUB231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35638, 199},
    {I_VFMSUB231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35645, 199},
    {I_VFMSUB231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18329, 231},
    {I_VFMSUB231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18337, 231},
    {I_VFMSUB231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18345, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB231PD[] = {
    {I_VFMSUB231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35652, 199},
    {I_VFMSUB231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35659, 199},
    {I_VFMSUB231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18305, 231},
    {I_VFMSUB231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18313, 231},
    {I_VFMSUB231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18321, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB321PS[] = {
    {I_VFMSUB321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35638, 199},
    {I_VFMSUB321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35645, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB321PD[] = {
    {I_VFMSUB321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35652, 199},
    {I_VFMSUB321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35659, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD132PS[] = {
    {I_VFMSUBADD132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35666, 199},
    {I_VFMSUBADD132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35673, 199},
    {I_VFMSUBADD132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18393, 231},
    {I_VFMSUBADD132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18401, 231},
    {I_VFMSUBADD132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18409, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD132PD[] = {
    {I_VFMSUBADD132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35680, 199},
    {I_VFMSUBADD132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35687, 199},
    {I_VFMSUBADD132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18369, 231},
    {I_VFMSUBADD132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18377, 231},
    {I_VFMSUBADD132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18385, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD312PS[] = {
    {I_VFMSUBADD312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35666, 199},
    {I_VFMSUBADD312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35673, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD312PD[] = {
    {I_VFMSUBADD312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35680, 199},
    {I_VFMSUBADD312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35687, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD213PS[] = {
    {I_VFMSUBADD213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35694, 199},
    {I_VFMSUBADD213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35701, 199},
    {I_VFMSUBADD213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18441, 231},
    {I_VFMSUBADD213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18449, 231},
    {I_VFMSUBADD213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18457, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD213PD[] = {
    {I_VFMSUBADD213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35708, 199},
    {I_VFMSUBADD213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35715, 199},
    {I_VFMSUBADD213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18417, 231},
    {I_VFMSUBADD213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18425, 231},
    {I_VFMSUBADD213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18433, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD123PS[] = {
    {I_VFMSUBADD123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35694, 199},
    {I_VFMSUBADD123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35701, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD123PD[] = {
    {I_VFMSUBADD123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35708, 199},
    {I_VFMSUBADD123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35715, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD231PS[] = {
    {I_VFMSUBADD231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35722, 199},
    {I_VFMSUBADD231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35729, 199},
    {I_VFMSUBADD231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18489, 231},
    {I_VFMSUBADD231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18497, 231},
    {I_VFMSUBADD231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18505, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD231PD[] = {
    {I_VFMSUBADD231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35736, 199},
    {I_VFMSUBADD231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35743, 199},
    {I_VFMSUBADD231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18465, 231},
    {I_VFMSUBADD231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18473, 231},
    {I_VFMSUBADD231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18481, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD321PS[] = {
    {I_VFMSUBADD321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35722, 199},
    {I_VFMSUBADD321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35729, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADD321PD[] = {
    {I_VFMSUBADD321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35736, 199},
    {I_VFMSUBADD321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35743, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD132PS[] = {
    {I_VFNMADD132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35750, 199},
    {I_VFNMADD132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35757, 199},
    {I_VFNMADD132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18537, 231},
    {I_VFNMADD132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18545, 231},
    {I_VFNMADD132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18553, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD132PD[] = {
    {I_VFNMADD132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35764, 199},
    {I_VFNMADD132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35771, 199},
    {I_VFNMADD132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18513, 231},
    {I_VFNMADD132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18521, 231},
    {I_VFNMADD132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18529, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD312PS[] = {
    {I_VFNMADD312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35750, 199},
    {I_VFNMADD312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35757, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD312PD[] = {
    {I_VFNMADD312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35764, 199},
    {I_VFNMADD312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35771, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD213PS[] = {
    {I_VFNMADD213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35778, 199},
    {I_VFNMADD213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35785, 199},
    {I_VFNMADD213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18601, 231},
    {I_VFNMADD213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18609, 231},
    {I_VFNMADD213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18617, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD213PD[] = {
    {I_VFNMADD213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35792, 199},
    {I_VFNMADD213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35799, 199},
    {I_VFNMADD213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18577, 231},
    {I_VFNMADD213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18585, 231},
    {I_VFNMADD213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18593, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD123PS[] = {
    {I_VFNMADD123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35778, 199},
    {I_VFNMADD123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35785, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD123PD[] = {
    {I_VFNMADD123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35792, 199},
    {I_VFNMADD123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35799, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD231PS[] = {
    {I_VFNMADD231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35806, 199},
    {I_VFNMADD231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35813, 199},
    {I_VFNMADD231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18665, 231},
    {I_VFNMADD231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18673, 231},
    {I_VFNMADD231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18681, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD231PD[] = {
    {I_VFNMADD231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35820, 199},
    {I_VFNMADD231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35827, 199},
    {I_VFNMADD231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18641, 231},
    {I_VFNMADD231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18649, 231},
    {I_VFNMADD231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18657, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD321PS[] = {
    {I_VFNMADD321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35806, 199},
    {I_VFNMADD321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35813, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD321PD[] = {
    {I_VFNMADD321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35820, 199},
    {I_VFNMADD321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35827, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB132PS[] = {
    {I_VFNMSUB132PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35834, 199},
    {I_VFNMSUB132PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35841, 199},
    {I_VFNMSUB132PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18729, 231},
    {I_VFNMSUB132PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18737, 231},
    {I_VFNMSUB132PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18745, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB132PD[] = {
    {I_VFNMSUB132PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35848, 199},
    {I_VFNMSUB132PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35855, 199},
    {I_VFNMSUB132PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18705, 231},
    {I_VFNMSUB132PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18713, 231},
    {I_VFNMSUB132PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18721, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB312PS[] = {
    {I_VFNMSUB312PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35834, 199},
    {I_VFNMSUB312PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35841, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB312PD[] = {
    {I_VFNMSUB312PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35848, 199},
    {I_VFNMSUB312PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35855, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB213PS[] = {
    {I_VFNMSUB213PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35862, 199},
    {I_VFNMSUB213PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35869, 199},
    {I_VFNMSUB213PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18793, 231},
    {I_VFNMSUB213PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18801, 231},
    {I_VFNMSUB213PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18809, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB213PD[] = {
    {I_VFNMSUB213PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35876, 199},
    {I_VFNMSUB213PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35883, 199},
    {I_VFNMSUB213PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18769, 231},
    {I_VFNMSUB213PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18777, 231},
    {I_VFNMSUB213PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18785, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB123PS[] = {
    {I_VFNMSUB123PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35862, 199},
    {I_VFNMSUB123PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35869, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB123PD[] = {
    {I_VFNMSUB123PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35876, 199},
    {I_VFNMSUB123PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35883, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB231PS[] = {
    {I_VFNMSUB231PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35890, 199},
    {I_VFNMSUB231PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35897, 199},
    {I_VFNMSUB231PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18857, 231},
    {I_VFNMSUB231PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+18865, 231},
    {I_VFNMSUB231PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+18873, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB231PD[] = {
    {I_VFNMSUB231PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35904, 199},
    {I_VFNMSUB231PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35911, 199},
    {I_VFNMSUB231PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18833, 231},
    {I_VFNMSUB231PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+18841, 231},
    {I_VFNMSUB231PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+18849, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB321PS[] = {
    {I_VFNMSUB321PS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35890, 199},
    {I_VFNMSUB321PS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35897, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB321PD[] = {
    {I_VFNMSUB321PD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+35904, 199},
    {I_VFNMSUB321PD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+35911, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD132SS[] = {
    {I_VFMADD132SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35918, 199},
    {I_VFMADD132SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17897, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD132SD[] = {
    {I_VFMADD132SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35925, 199},
    {I_VFMADD132SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17889, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD312SS[] = {
    {I_VFMADD312SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35918, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD312SD[] = {
    {I_VFMADD312SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35925, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD213SS[] = {
    {I_VFMADD213SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35932, 199},
    {I_VFMADD213SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17961, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD213SD[] = {
    {I_VFMADD213SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35939, 199},
    {I_VFMADD213SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+17953, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD123SS[] = {
    {I_VFMADD123SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35932, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD123SD[] = {
    {I_VFMADD123SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35939, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD231SS[] = {
    {I_VFMADD231SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35946, 199},
    {I_VFMADD231SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18025, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD231SD[] = {
    {I_VFMADD231SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35953, 199},
    {I_VFMADD231SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18017, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD321SS[] = {
    {I_VFMADD321SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35946, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADD321SD[] = {
    {I_VFMADD321SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35953, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB132SS[] = {
    {I_VFMSUB132SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35960, 199},
    {I_VFMSUB132SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18233, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB132SD[] = {
    {I_VFMSUB132SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35967, 199},
    {I_VFMSUB132SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18225, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB312SS[] = {
    {I_VFMSUB312SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35960, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB312SD[] = {
    {I_VFMSUB312SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35967, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB213SS[] = {
    {I_VFMSUB213SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35974, 199},
    {I_VFMSUB213SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18297, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB213SD[] = {
    {I_VFMSUB213SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35981, 199},
    {I_VFMSUB213SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18289, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB123SS[] = {
    {I_VFMSUB123SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35974, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB123SD[] = {
    {I_VFMSUB123SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35981, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB231SS[] = {
    {I_VFMSUB231SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35988, 199},
    {I_VFMSUB231SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18361, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB231SD[] = {
    {I_VFMSUB231SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35995, 199},
    {I_VFMSUB231SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18353, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB321SS[] = {
    {I_VFMSUB321SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+35988, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUB321SD[] = {
    {I_VFMSUB321SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+35995, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD132SS[] = {
    {I_VFNMADD132SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36002, 199},
    {I_VFNMADD132SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18569, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD132SD[] = {
    {I_VFNMADD132SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36009, 199},
    {I_VFNMADD132SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18561, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD312SS[] = {
    {I_VFNMADD312SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36002, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD312SD[] = {
    {I_VFNMADD312SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36009, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD213SS[] = {
    {I_VFNMADD213SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36016, 199},
    {I_VFNMADD213SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18633, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD213SD[] = {
    {I_VFNMADD213SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36023, 199},
    {I_VFNMADD213SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD123SS[] = {
    {I_VFNMADD123SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36016, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD123SD[] = {
    {I_VFNMADD123SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36023, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD231SS[] = {
    {I_VFNMADD231SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36030, 199},
    {I_VFNMADD231SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18697, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD231SD[] = {
    {I_VFNMADD231SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36037, 199},
    {I_VFNMADD231SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18689, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD321SS[] = {
    {I_VFNMADD321SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36030, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADD321SD[] = {
    {I_VFNMADD321SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36037, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB132SS[] = {
    {I_VFNMSUB132SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36044, 199},
    {I_VFNMSUB132SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18761, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB132SD[] = {
    {I_VFNMSUB132SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36051, 199},
    {I_VFNMSUB132SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18753, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB312SS[] = {
    {I_VFNMSUB312SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36044, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB312SD[] = {
    {I_VFNMSUB312SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36051, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB213SS[] = {
    {I_VFNMSUB213SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36058, 199},
    {I_VFNMSUB213SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18825, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB213SD[] = {
    {I_VFNMSUB213SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36065, 199},
    {I_VFNMSUB213SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18817, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB123SS[] = {
    {I_VFNMSUB123SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36058, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB123SD[] = {
    {I_VFNMSUB123SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36065, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB231SS[] = {
    {I_VFNMSUB231SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36072, 199},
    {I_VFNMSUB231SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18889, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB231SD[] = {
    {I_VFNMSUB231SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36079, 199},
    {I_VFNMSUB231SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+18881, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB321SS[] = {
    {I_VFNMSUB321SS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+36072, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUB321SD[] = {
    {I_VFNMSUB321SD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+36079, 199},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDFSBASE[] = {
    {I_RDFSBASE, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36086, 136},
    {I_RDFSBASE, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36093, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDGSBASE[] = {
    {I_RDGSBASE, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36100, 136},
    {I_RDGSBASE, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36107, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDRAND[] = {
    {I_RDRAND, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41687, 135},
    {I_RDRAND, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41693, 135},
    {I_RDRAND, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41699, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRFSBASE[] = {
    {I_WRFSBASE, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36114, 136},
    {I_WRFSBASE, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36121, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRGSBASE[] = {
    {I_WRGSBASE, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36128, 136},
    {I_WRGSBASE, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36135, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPH2PS[] = {
    {I_VCVTPH2PS, 2, {YMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36142, 200},
    {I_VCVTPH2PS, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+36149, 200},
    {I_VCVTPH2PS, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16961, 231},
    {I_VCVTPH2PS, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16969, 231},
    {I_VCVTPH2PS, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+16977, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2PH[] = {
    {I_VCVTPS2PH, 3, {RM_XMM_L16|BITS128,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13945, 200},
    {I_VCVTPS2PH, 3, {RM_XMM_L16|BITS64,XMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+13953, 200},
    {I_VCVTPS2PH, 3, {XMMREG,XMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8182, 231},
    {I_VCVTPS2PH, 3, {XMMREG,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8191, 231},
    {I_VCVTPS2PH, 3, {YMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+8200, 232},
    {I_VCVTPS2PH, 3, {MEMORY|BITS64,XMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8182, 231},
    {I_VCVTPS2PH, 3, {MEMORY|BITS128,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8191, 231},
    {I_VCVTPS2PH, 3, {MEMORY|BITS256,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,SAE,0,0,0}, nasm_bytecodes+8200, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADCX[] = {
    {I_ADCX, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+13961, 135},
    {I_ADCX, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+13969, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_ADOX[] = {
    {I_ADOX, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+13977, 135},
    {I_ADOX, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+13985, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDSEED[] = {
    {I_RDSEED, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41705, 135},
    {I_RDSEED, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41711, 135},
    {I_RDSEED, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41717, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLAC[] = {
    {I_CLAC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44871, 201},
    ITEMPLATE_END
};

static const struct itemplate instrux_STAC[] = {
    {I_STAC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44876, 201},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSTORE[] = {
    {I_XSTORE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44881, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCRYPTECB[] = {
    {I_XCRYPTECB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41723, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCRYPTCBC[] = {
    {I_XCRYPTCBC, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41729, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCRYPTCTR[] = {
    {I_XCRYPTCTR, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41735, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCRYPTCFB[] = {
    {I_XCRYPTCFB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41741, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XCRYPTOFB[] = {
    {I_XCRYPTOFB, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41747, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_MONTMUL[] = {
    {I_MONTMUL, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41753, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSHA1[] = {
    {I_XSHA1, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41759, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSHA256[] = {
    {I_XSHA256, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41765, 32},
    ITEMPLATE_END
};

static const struct itemplate instrux_LLWPCB[] = {
    {I_LLWPCB, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36156, 202},
    {I_LLWPCB, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36163, 203},
    ITEMPLATE_END
};

static const struct itemplate instrux_SLWPCB[] = {
    {I_SLWPCB, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36170, 202},
    {I_SLWPCB, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36177, 203},
    ITEMPLATE_END
};

static const struct itemplate instrux_LWPVAL[] = {
    {I_LWPVAL, 3, {REG_GPR|BITS32,RM_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+13993, 202},
    {I_LWPVAL, 3, {REG_GPR|BITS64,RM_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14001, 203},
    ITEMPLATE_END
};

static const struct itemplate instrux_LWPINS[] = {
    {I_LWPINS, 3, {REG_GPR|BITS32,RM_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14009, 202},
    {I_LWPINS, 3, {REG_GPR|BITS64,RM_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14017, 203},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDPD[] = {
    {I_VFMADDPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14025, 204},
    {I_VFMADDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14033, 204},
    {I_VFMADDPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14041, 204},
    {I_VFMADDPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14049, 204},
    {I_VFMADDPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14057, 204},
    {I_VFMADDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14065, 204},
    {I_VFMADDPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14073, 204},
    {I_VFMADDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14081, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDPS[] = {
    {I_VFMADDPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14089, 204},
    {I_VFMADDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14097, 204},
    {I_VFMADDPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14105, 204},
    {I_VFMADDPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14113, 204},
    {I_VFMADDPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14121, 204},
    {I_VFMADDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14129, 204},
    {I_VFMADDPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14137, 204},
    {I_VFMADDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14145, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSD[] = {
    {I_VFMADDSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14153, 204},
    {I_VFMADDSD, 3, {XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14161, 204},
    {I_VFMADDSD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0}, NO_DECORATOR, nasm_bytecodes+14169, 204},
    {I_VFMADDSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+14177, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSS[] = {
    {I_VFMADDSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14185, 204},
    {I_VFMADDSS, 3, {XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14193, 204},
    {I_VFMADDSS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0}, NO_DECORATOR, nasm_bytecodes+14201, 204},
    {I_VFMADDSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14209, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUBPD[] = {
    {I_VFMADDSUBPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14217, 204},
    {I_VFMADDSUBPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14225, 204},
    {I_VFMADDSUBPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14233, 204},
    {I_VFMADDSUBPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14241, 204},
    {I_VFMADDSUBPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14249, 204},
    {I_VFMADDSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14257, 204},
    {I_VFMADDSUBPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14265, 204},
    {I_VFMADDSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14273, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMADDSUBPS[] = {
    {I_VFMADDSUBPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14281, 204},
    {I_VFMADDSUBPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14289, 204},
    {I_VFMADDSUBPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14297, 204},
    {I_VFMADDSUBPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14305, 204},
    {I_VFMADDSUBPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14313, 204},
    {I_VFMADDSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14321, 204},
    {I_VFMADDSUBPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14329, 204},
    {I_VFMADDSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14337, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADDPD[] = {
    {I_VFMSUBADDPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14345, 204},
    {I_VFMSUBADDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14353, 204},
    {I_VFMSUBADDPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14361, 204},
    {I_VFMSUBADDPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14369, 204},
    {I_VFMSUBADDPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14377, 204},
    {I_VFMSUBADDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14385, 204},
    {I_VFMSUBADDPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14393, 204},
    {I_VFMSUBADDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14401, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBADDPS[] = {
    {I_VFMSUBADDPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14409, 204},
    {I_VFMSUBADDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14417, 204},
    {I_VFMSUBADDPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14425, 204},
    {I_VFMSUBADDPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14433, 204},
    {I_VFMSUBADDPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14441, 204},
    {I_VFMSUBADDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14449, 204},
    {I_VFMSUBADDPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14457, 204},
    {I_VFMSUBADDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14465, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBPD[] = {
    {I_VFMSUBPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14473, 204},
    {I_VFMSUBPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14481, 204},
    {I_VFMSUBPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14489, 204},
    {I_VFMSUBPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14497, 204},
    {I_VFMSUBPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14505, 204},
    {I_VFMSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14513, 204},
    {I_VFMSUBPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14521, 204},
    {I_VFMSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14529, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBPS[] = {
    {I_VFMSUBPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14537, 204},
    {I_VFMSUBPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14545, 204},
    {I_VFMSUBPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14553, 204},
    {I_VFMSUBPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14561, 204},
    {I_VFMSUBPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14569, 204},
    {I_VFMSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14577, 204},
    {I_VFMSUBPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14585, 204},
    {I_VFMSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14593, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBSD[] = {
    {I_VFMSUBSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14601, 204},
    {I_VFMSUBSD, 3, {XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14609, 204},
    {I_VFMSUBSD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0}, NO_DECORATOR, nasm_bytecodes+14617, 204},
    {I_VFMSUBSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+14625, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFMSUBSS[] = {
    {I_VFMSUBSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14633, 204},
    {I_VFMSUBSS, 3, {XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14641, 204},
    {I_VFMSUBSS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0}, NO_DECORATOR, nasm_bytecodes+14649, 204},
    {I_VFMSUBSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14657, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADDPD[] = {
    {I_VFNMADDPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14665, 204},
    {I_VFNMADDPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14673, 204},
    {I_VFNMADDPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14681, 204},
    {I_VFNMADDPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14689, 204},
    {I_VFNMADDPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14697, 204},
    {I_VFNMADDPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14705, 204},
    {I_VFNMADDPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14713, 204},
    {I_VFNMADDPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14721, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADDPS[] = {
    {I_VFNMADDPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14729, 204},
    {I_VFNMADDPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14737, 204},
    {I_VFNMADDPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14745, 204},
    {I_VFNMADDPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14753, 204},
    {I_VFNMADDPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14761, 204},
    {I_VFNMADDPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14769, 204},
    {I_VFNMADDPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14777, 204},
    {I_VFNMADDPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14785, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADDSD[] = {
    {I_VFNMADDSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14793, 204},
    {I_VFNMADDSD, 3, {XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14801, 204},
    {I_VFNMADDSD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0}, NO_DECORATOR, nasm_bytecodes+14809, 204},
    {I_VFNMADDSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+14817, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMADDSS[] = {
    {I_VFNMADDSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14825, 204},
    {I_VFNMADDSS, 3, {XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14833, 204},
    {I_VFNMADDSS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0}, NO_DECORATOR, nasm_bytecodes+14841, 204},
    {I_VFNMADDSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+14849, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUBPD[] = {
    {I_VFNMSUBPD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14857, 204},
    {I_VFNMSUBPD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14865, 204},
    {I_VFNMSUBPD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14873, 204},
    {I_VFNMSUBPD, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14881, 204},
    {I_VFNMSUBPD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14889, 204},
    {I_VFNMSUBPD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14897, 204},
    {I_VFNMSUBPD, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14905, 204},
    {I_VFNMSUBPD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14913, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUBPS[] = {
    {I_VFNMSUBPS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14921, 204},
    {I_VFNMSUBPS, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14929, 204},
    {I_VFNMSUBPS, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14937, 204},
    {I_VFNMSUBPS, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14945, 204},
    {I_VFNMSUBPS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+14953, 204},
    {I_VFNMSUBPS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+14961, 204},
    {I_VFNMSUBPS, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+14969, 204},
    {I_VFNMSUBPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+14977, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUBSD[] = {
    {I_VFNMSUBSD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+14985, 204},
    {I_VFNMSUBSD, 3, {XMM_L16,RM_XMM_L16|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+14993, 204},
    {I_VFNMSUBSD, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0}, NO_DECORATOR, nasm_bytecodes+15001, 204},
    {I_VFNMSUBSD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+15009, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFNMSUBSS[] = {
    {I_VFNMSUBSS, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15017, 204},
    {I_VFNMSUBSS, 3, {XMM_L16,RM_XMM_L16|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15025, 204},
    {I_VFNMSUBSS, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0}, NO_DECORATOR, nasm_bytecodes+15033, 204},
    {I_VFNMSUBSS, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+15041, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFRCZPD[] = {
    {I_VFRCZPD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36184, 204},
    {I_VFRCZPD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36191, 204},
    {I_VFRCZPD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36198, 204},
    {I_VFRCZPD, 1, {YMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36205, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFRCZPS[] = {
    {I_VFRCZPS, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36212, 204},
    {I_VFRCZPS, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36219, 204},
    {I_VFRCZPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+36226, 204},
    {I_VFRCZPS, 1, {YMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36233, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFRCZSD[] = {
    {I_VFRCZSD, 2, {XMM_L16,RM_XMM_L16|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+36240, 204},
    {I_VFRCZSD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36247, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFRCZSS[] = {
    {I_VFRCZSS, 2, {XMM_L16,RM_XMM_L16|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+36254, 204},
    {I_VFRCZSS, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36261, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMOV[] = {
    {I_VPCMOV, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15049, 204},
    {I_VPCMOV, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15057, 204},
    {I_VPCMOV, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15065, 204},
    {I_VPCMOV, 3, {YMM_L16,RM_YMM_L16|BITS256,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15073, 204},
    {I_VPCMOV, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+15081, 204},
    {I_VPCMOV, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+15089, 204},
    {I_VPCMOV, 4, {YMM_L16,YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0}, NO_DECORATOR, nasm_bytecodes+15097, 204},
    {I_VPCMOV, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+15105, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMB[] = {
    {I_VPCOMB, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15113, 204},
    {I_VPCOMB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15121, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMD[] = {
    {I_VPCOMD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15129, 204},
    {I_VPCOMD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15137, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMQ[] = {
    {I_VPCOMQ, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15145, 204},
    {I_VPCOMQ, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15153, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMUB[] = {
    {I_VPCOMUB, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15161, 204},
    {I_VPCOMUB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15169, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMUD[] = {
    {I_VPCOMUD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15177, 204},
    {I_VPCOMUD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15185, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMUQ[] = {
    {I_VPCOMUQ, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15193, 204},
    {I_VPCOMUQ, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15201, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMUW[] = {
    {I_VPCOMUW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15209, 204},
    {I_VPCOMUW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15217, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMW[] = {
    {I_VPCOMW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15225, 204},
    {I_VPCOMW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15233, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDBD[] = {
    {I_VPHADDBD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36268, 204},
    {I_VPHADDBD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36275, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDBQ[] = {
    {I_VPHADDBQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36282, 204},
    {I_VPHADDBQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36289, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDBW[] = {
    {I_VPHADDBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36296, 204},
    {I_VPHADDBW, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36303, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDDQ[] = {
    {I_VPHADDDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36310, 204},
    {I_VPHADDDQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36317, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUBD[] = {
    {I_VPHADDUBD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36324, 204},
    {I_VPHADDUBD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36331, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUBQ[] = {
    {I_VPHADDUBQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36338, 204},
    {I_VPHADDUBQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36345, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUBW[] = {
    {I_VPHADDUBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36352, 204},
    {I_VPHADDUBW, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36359, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUDQ[] = {
    {I_VPHADDUDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36366, 204},
    {I_VPHADDUDQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36373, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUWD[] = {
    {I_VPHADDUWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36380, 204},
    {I_VPHADDUWD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36387, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDUWQ[] = {
    {I_VPHADDUWQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36394, 204},
    {I_VPHADDUWQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36401, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDWD[] = {
    {I_VPHADDWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36408, 204},
    {I_VPHADDWD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36415, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHADDWQ[] = {
    {I_VPHADDWQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36422, 204},
    {I_VPHADDWQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36429, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBBW[] = {
    {I_VPHSUBBW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36436, 204},
    {I_VPHSUBBW, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36443, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBDQ[] = {
    {I_VPHSUBDQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36450, 204},
    {I_VPHSUBDQ, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36457, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPHSUBWD[] = {
    {I_VPHSUBWD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36464, 204},
    {I_VPHSUBWD, 1, {XMM_L16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+36471, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSDD[] = {
    {I_VPMACSDD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15241, 204},
    {I_VPMACSDD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15249, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSDQH[] = {
    {I_VPMACSDQH, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15257, 204},
    {I_VPMACSDQH, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15265, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSDQL[] = {
    {I_VPMACSDQL, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15273, 204},
    {I_VPMACSDQL, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15281, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSSDD[] = {
    {I_VPMACSSDD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15289, 204},
    {I_VPMACSSDD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15297, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSSDQH[] = {
    {I_VPMACSSDQH, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15305, 204},
    {I_VPMACSSDQH, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15313, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSSDQL[] = {
    {I_VPMACSSDQL, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15321, 204},
    {I_VPMACSSDQL, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15329, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSSWD[] = {
    {I_VPMACSSWD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15337, 204},
    {I_VPMACSSWD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15345, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSSWW[] = {
    {I_VPMACSSWW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15353, 204},
    {I_VPMACSSWW, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15361, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSWD[] = {
    {I_VPMACSWD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15369, 204},
    {I_VPMACSWD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15377, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMACSWW[] = {
    {I_VPMACSWW, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15385, 204},
    {I_VPMACSWW, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15393, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADCSSWD[] = {
    {I_VPMADCSSWD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15401, 204},
    {I_VPMADCSSWD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15409, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADCSWD[] = {
    {I_VPMADCSWD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15417, 204},
    {I_VPMADCSWD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15425, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPPERM[] = {
    {I_VPPERM, 4, {XMM_L16,XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0}, NO_DECORATOR, nasm_bytecodes+15433, 204},
    {I_VPPERM, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+15441, 204},
    {I_VPPERM, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0}, NO_DECORATOR, nasm_bytecodes+15449, 204},
    {I_VPPERM, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15457, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROTB[] = {
    {I_VPROTB, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36478, 204},
    {I_VPROTB, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36485, 204},
    {I_VPROTB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36492, 204},
    {I_VPROTB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36499, 204},
    {I_VPROTB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15465, 204},
    {I_VPROTB, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15473, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROTD[] = {
    {I_VPROTD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36506, 204},
    {I_VPROTD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36513, 204},
    {I_VPROTD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36520, 204},
    {I_VPROTD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36527, 204},
    {I_VPROTD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15481, 204},
    {I_VPROTD, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15489, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROTQ[] = {
    {I_VPROTQ, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36534, 204},
    {I_VPROTQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36541, 204},
    {I_VPROTQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36548, 204},
    {I_VPROTQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36555, 204},
    {I_VPROTQ, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15497, 204},
    {I_VPROTQ, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15505, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROTW[] = {
    {I_VPROTW, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36562, 204},
    {I_VPROTW, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36569, 204},
    {I_VPROTW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36576, 204},
    {I_VPROTW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36583, 204},
    {I_VPROTW, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15513, 204},
    {I_VPROTW, 2, {XMM_L16,IMMEDIATE|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+15521, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHAB[] = {
    {I_VPSHAB, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36590, 204},
    {I_VPSHAB, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36597, 204},
    {I_VPSHAB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36604, 204},
    {I_VPSHAB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36611, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHAD[] = {
    {I_VPSHAD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36618, 204},
    {I_VPSHAD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36625, 204},
    {I_VPSHAD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36632, 204},
    {I_VPSHAD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36639, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHAQ[] = {
    {I_VPSHAQ, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36646, 204},
    {I_VPSHAQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36653, 204},
    {I_VPSHAQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36660, 204},
    {I_VPSHAQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36667, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHAW[] = {
    {I_VPSHAW, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36674, 204},
    {I_VPSHAW, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36681, 204},
    {I_VPSHAW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36688, 204},
    {I_VPSHAW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36695, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLB[] = {
    {I_VPSHLB, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36702, 204},
    {I_VPSHLB, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36709, 204},
    {I_VPSHLB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36716, 204},
    {I_VPSHLB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36723, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLD[] = {
    {I_VPSHLD, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36730, 204},
    {I_VPSHLD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36737, 204},
    {I_VPSHLD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36744, 204},
    {I_VPSHLD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36751, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLQ[] = {
    {I_VPSHLQ, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36758, 204},
    {I_VPSHLQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36765, 204},
    {I_VPSHLQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36772, 204},
    {I_VPSHLQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36779, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLW[] = {
    {I_VPSHLW, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+36786, 204},
    {I_VPSHLW, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+36793, 204},
    {I_VPSHLW, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+36800, 204},
    {I_VPSHLW, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+36807, 204},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI128[] = {
    {I_VBROADCASTI128, 2, {YMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38081, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDD[] = {
    {I_VPBLENDD, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15777, 205},
    {I_VPBLENDD, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15785, 205},
    {I_VPBLENDD, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15793, 205},
    {I_VPBLENDD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15801, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTB[] = {
    {I_VPBROADCASTB, 2, {XMM_L16,MEMORY|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38088, 205},
    {I_VPBROADCASTB, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38088, 205},
    {I_VPBROADCASTB, 2, {YMM_L16,MEMORY|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38095, 205},
    {I_VPBROADCASTB, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38095, 205},
    {I_VPBROADCASTB, 2, {XMMREG,RM_XMM|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21513, 235},
    {I_VPBROADCASTB, 2, {YMMREG,RM_XMM|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21521, 235},
    {I_VPBROADCASTB, 2, {ZMMREG,RM_XMM|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21529, 236},
    {I_VPBROADCASTB, 2, {XMMREG,REG_GPR|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21537, 235},
    {I_VPBROADCASTB, 2, {XMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21537, 235},
    {I_VPBROADCASTB, 2, {XMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21537, 235},
    {I_VPBROADCASTB, 2, {XMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21537, 235},
    {I_VPBROADCASTB, 2, {YMMREG,REG_GPR|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21545, 235},
    {I_VPBROADCASTB, 2, {YMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21545, 235},
    {I_VPBROADCASTB, 2, {YMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21545, 235},
    {I_VPBROADCASTB, 2, {YMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21545, 235},
    {I_VPBROADCASTB, 2, {ZMMREG,REG_GPR|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21553, 236},
    {I_VPBROADCASTB, 2, {ZMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21553, 236},
    {I_VPBROADCASTB, 2, {ZMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21553, 236},
    {I_VPBROADCASTB, 2, {ZMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21553, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTW[] = {
    {I_VPBROADCASTW, 2, {XMM_L16,MEMORY|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38102, 205},
    {I_VPBROADCASTW, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38102, 205},
    {I_VPBROADCASTW, 2, {YMM_L16,MEMORY|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38109, 205},
    {I_VPBROADCASTW, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38109, 205},
    {I_VPBROADCASTW, 2, {XMMREG,RM_XMM|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21753, 235},
    {I_VPBROADCASTW, 2, {YMMREG,RM_XMM|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21761, 235},
    {I_VPBROADCASTW, 2, {ZMMREG,RM_XMM|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21769, 236},
    {I_VPBROADCASTW, 2, {XMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21777, 235},
    {I_VPBROADCASTW, 2, {XMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21777, 235},
    {I_VPBROADCASTW, 2, {XMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21777, 235},
    {I_VPBROADCASTW, 2, {YMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21785, 235},
    {I_VPBROADCASTW, 2, {YMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21785, 235},
    {I_VPBROADCASTW, 2, {YMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21785, 235},
    {I_VPBROADCASTW, 2, {ZMMREG,REG_GPR|BITS16,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21793, 236},
    {I_VPBROADCASTW, 2, {ZMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21793, 236},
    {I_VPBROADCASTW, 2, {ZMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21793, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTD[] = {
    {I_VPBROADCASTD, 2, {XMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38116, 205},
    {I_VPBROADCASTD, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38116, 205},
    {I_VPBROADCASTD, 2, {YMM_L16,MEMORY|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38123, 205},
    {I_VPBROADCASTD, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38123, 205},
    {I_VPBROADCASTD, 2, {XMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21561, 231},
    {I_VPBROADCASTD, 2, {YMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21569, 231},
    {I_VPBROADCASTD, 2, {ZMMREG,MEMORY|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21577, 232},
    {I_VPBROADCASTD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21585, 231},
    {I_VPBROADCASTD, 2, {YMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21593, 231},
    {I_VPBROADCASTD, 2, {ZMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21601, 232},
    {I_VPBROADCASTD, 2, {XMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21609, 231},
    {I_VPBROADCASTD, 2, {YMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21617, 231},
    {I_VPBROADCASTD, 2, {ZMMREG,REG_GPR|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTQ[] = {
    {I_VPBROADCASTQ, 2, {XMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38130, 205},
    {I_VPBROADCASTQ, 2, {XMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38130, 205},
    {I_VPBROADCASTQ, 2, {YMM_L16,MEMORY|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38137, 205},
    {I_VPBROADCASTQ, 2, {YMM_L16,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38137, 205},
    {I_VPBROADCASTQ, 2, {XMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21681, 231},
    {I_VPBROADCASTQ, 2, {YMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21689, 231},
    {I_VPBROADCASTQ, 2, {ZMMREG,MEMORY|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21697, 232},
    {I_VPBROADCASTQ, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21705, 231},
    {I_VPBROADCASTQ, 2, {YMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21713, 231},
    {I_VPBROADCASTQ, 2, {ZMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21721, 232},
    {I_VPBROADCASTQ, 2, {XMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21729, 231},
    {I_VPBROADCASTQ, 2, {YMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21737, 231},
    {I_VPBROADCASTQ, 2, {ZMMREG,REG_GPR|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21745, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMD[] = {
    {I_VPERMD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38144, 205},
    {I_VPERMD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38151, 205},
    {I_VPERMD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22185, 231},
    {I_VPERMD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22193, 231},
    {I_VPERMD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22201, 232},
    {I_VPERMD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22209, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMPD[] = {
    {I_VPERMPD, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15809, 205},
    {I_VPERMPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9514, 231},
    {I_VPERMPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9523, 232},
    {I_VPERMPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22457, 231},
    {I_VPERMPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22465, 231},
    {I_VPERMPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22473, 232},
    {I_VPERMPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22481, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMPS[] = {
    {I_VPERMPS, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38158, 205},
    {I_VPERMPS, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38165, 205},
    {I_VPERMPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22489, 231},
    {I_VPERMPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22497, 231},
    {I_VPERMPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22505, 232},
    {I_VPERMPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22513, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMQ[] = {
    {I_VPERMQ, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15817, 205},
    {I_VPERMQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9532, 231},
    {I_VPERMQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9541, 232},
    {I_VPERMQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22521, 231},
    {I_VPERMQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22529, 231},
    {I_VPERMQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22537, 232},
    {I_VPERMQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22545, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERM2I128[] = {
    {I_VPERM2I128, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15825, 205},
    {I_VPERM2I128, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15833, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTI128[] = {
    {I_VEXTRACTI128, 3, {RM_XMM_L16|BITS128,YMM_L16,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15841, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTI128[] = {
    {I_VINSERTI128, 4, {YMM_L16,YMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+15849, 205},
    {I_VINSERTI128, 3, {YMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+15857, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMASKMOVD[] = {
    {I_VPMASKMOVD, 3, {XMM_L16,XMM_L16,MEMORY|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38172, 205},
    {I_VPMASKMOVD, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38179, 205},
    {I_VPMASKMOVD, 3, {YMM_L16,YMM_L16,MEMORY|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38186, 205},
    {I_VPMASKMOVD, 2, {YMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38193, 205},
    {I_VPMASKMOVD, 3, {MEMORY|BITS128,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+38228, 205},
    {I_VPMASKMOVD, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38235, 205},
    {I_VPMASKMOVD, 3, {MEMORY|BITS256,YMM_L16,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+38242, 205},
    {I_VPMASKMOVD, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38249, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMASKMOVQ[] = {
    {I_VPMASKMOVQ, 3, {XMM_L16,XMM_L16,MEMORY|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38200, 205},
    {I_VPMASKMOVQ, 2, {XMM_L16,MEMORY|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38207, 205},
    {I_VPMASKMOVQ, 3, {YMM_L16,YMM_L16,MEMORY|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38214, 205},
    {I_VPMASKMOVQ, 2, {YMM_L16,MEMORY|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38221, 205},
    {I_VPMASKMOVQ, 3, {MEMORY|BITS128,XMM_L16,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+38256, 205},
    {I_VPMASKMOVQ, 2, {MEMORY|BITS128,XMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38263, 205},
    {I_VPMASKMOVQ, 3, {MEMORY|BITS256,YMM_L16,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+38270, 205},
    {I_VPMASKMOVQ, 2, {MEMORY|BITS256,YMM_L16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38277, 205},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLVD[] = {
    {I_VPSLLVD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38284, 205},
    {I_VPSLLVD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38291, 205},
    {I_VPSLLVD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38312, 205},
    {I_VPSLLVD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38319, 205},
    {I_VPSLLVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26009, 231},
    {I_VPSLLVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26017, 231},
    {I_VPSLLVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26025, 231},
    {I_VPSLLVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26033, 231},
    {I_VPSLLVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26041, 232},
    {I_VPSLLVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26049, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLVQ[] = {
    {I_VPSLLVQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38298, 205},
    {I_VPSLLVQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38305, 205},
    {I_VPSLLVQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38326, 205},
    {I_VPSLLVQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38333, 205},
    {I_VPSLLVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26057, 231},
    {I_VPSLLVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26065, 231},
    {I_VPSLLVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26073, 231},
    {I_VPSLLVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26081, 231},
    {I_VPSLLVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26089, 232},
    {I_VPSLLVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26097, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAVD[] = {
    {I_VPSRAVD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38340, 205},
    {I_VPSRAVD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38347, 205},
    {I_VPSRAVD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38354, 205},
    {I_VPSRAVD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38361, 205},
    {I_VPSRAVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26297, 231},
    {I_VPSRAVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26305, 231},
    {I_VPSRAVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26313, 231},
    {I_VPSRAVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26321, 231},
    {I_VPSRAVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26329, 232},
    {I_VPSRAVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26337, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLVD[] = {
    {I_VPSRLVD, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38368, 205},
    {I_VPSRLVD, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38375, 205},
    {I_VPSRLVD, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38396, 205},
    {I_VPSRLVD, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38403, 205},
    {I_VPSRLVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26585, 231},
    {I_VPSRLVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26593, 231},
    {I_VPSRLVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26601, 231},
    {I_VPSRLVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26609, 231},
    {I_VPSRLVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+26617, 232},
    {I_VPSRLVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+26625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLVQ[] = {
    {I_VPSRLVQ, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+38382, 205},
    {I_VPSRLVQ, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+38389, 205},
    {I_VPSRLVQ, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+38410, 205},
    {I_VPSRLVQ, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+38417, 205},
    {I_VPSRLVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26633, 231},
    {I_VPSRLVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26641, 231},
    {I_VPSRLVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26649, 231},
    {I_VPSRLVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26657, 231},
    {I_VPSRLVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26665, 232},
    {I_VPSRLVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26673, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERDPD[] = {
    {I_VGATHERDPD, 3, {XMM_L16,XMEM|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15865, 205},
    {I_VGATHERDPD, 3, {YMM_L16,XMEM|BITS64,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15881, 205},
    {I_VGATHERDPD, 2, {XMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8704, 231},
    {I_VGATHERDPD, 2, {YMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8713, 231},
    {I_VGATHERDPD, 2, {ZMMREG,YMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8722, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERQPD[] = {
    {I_VGATHERQPD, 3, {XMM_L16,XMEM|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15873, 205},
    {I_VGATHERQPD, 3, {YMM_L16,YMEM|BITS64,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15889, 205},
    {I_VGATHERQPD, 2, {XMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8830, 231},
    {I_VGATHERQPD, 2, {YMMREG,YMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8839, 231},
    {I_VGATHERQPD, 2, {ZMMREG,ZMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8848, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERDPS[] = {
    {I_VGATHERDPS, 3, {XMM_L16,XMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15897, 205},
    {I_VGATHERDPS, 3, {YMM_L16,YMEM|BITS32,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15913, 205},
    {I_VGATHERDPS, 2, {XMMREG,XMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8731, 231},
    {I_VGATHERDPS, 2, {YMMREG,YMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8740, 231},
    {I_VGATHERDPS, 2, {ZMMREG,ZMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8749, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERQPS[] = {
    {I_VGATHERQPS, 3, {XMM_L16,XMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15905, 205},
    {I_VGATHERQPS, 3, {XMM_L16,YMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15921, 205},
    {I_VGATHERQPS, 2, {XMMREG,XMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8857, 231},
    {I_VGATHERQPS, 2, {XMMREG,YMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8866, 231},
    {I_VGATHERQPS, 2, {YMMREG,ZMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8875, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPGATHERDD[] = {
    {I_VPGATHERDD, 3, {XMM_L16,XMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15929, 205},
    {I_VPGATHERDD, 3, {YMM_L16,YMEM|BITS32,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15945, 205},
    {I_VPGATHERDD, 2, {XMMREG,XMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9595, 231},
    {I_VPGATHERDD, 2, {YMMREG,YMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9604, 231},
    {I_VPGATHERDD, 2, {ZMMREG,ZMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9613, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPGATHERQD[] = {
    {I_VPGATHERQD, 3, {XMM_L16,XMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15937, 205},
    {I_VPGATHERQD, 3, {XMM_L16,YMEM|BITS32,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15953, 205},
    {I_VPGATHERQD, 2, {XMMREG,XMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9649, 231},
    {I_VPGATHERQD, 2, {XMMREG,YMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9658, 231},
    {I_VPGATHERQD, 2, {YMMREG,ZMEM|BITS32,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9667, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPGATHERDQ[] = {
    {I_VPGATHERDQ, 3, {XMM_L16,XMEM|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15961, 205},
    {I_VPGATHERDQ, 3, {YMM_L16,XMEM|BITS64,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15977, 205},
    {I_VPGATHERDQ, 2, {XMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9622, 231},
    {I_VPGATHERDQ, 2, {YMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9631, 231},
    {I_VPGATHERDQ, 2, {ZMMREG,YMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9640, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPGATHERQQ[] = {
    {I_VPGATHERQQ, 3, {XMM_L16,XMEM|BITS64,XMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15969, 205},
    {I_VPGATHERQQ, 3, {YMM_L16,YMEM|BITS64,YMM_L16,0,0}, NO_DECORATOR, nasm_bytecodes+15985, 205},
    {I_VPGATHERQQ, 2, {XMMREG,XMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9676, 231},
    {I_VPGATHERQQ, 2, {YMMREG,YMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9685, 231},
    {I_VPGATHERQQ, 2, {ZMMREG,ZMEM|BITS64,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9694, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_XABORT[] = {
    {I_XABORT, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44886, 206},
    {I_XABORT, 1, {IMMEDIATE|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44886, 206},
    ITEMPLATE_END
};

static const struct itemplate instrux_XBEGIN[] = {
    {I_XBEGIN, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41771, 206},
    {I_XBEGIN, 1, {IMMEDIATE|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41771, 206},
    {I_XBEGIN, 1, {IMMEDIATE|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41777, 207},
    {I_XBEGIN, 1, {IMMEDIATE|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41777, 207},
    {I_XBEGIN, 1, {IMMEDIATE|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41783, 207},
    {I_XBEGIN, 1, {IMMEDIATE|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41783, 207},
    {I_XBEGIN, 1, {IMMEDIATE|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41789, 208},
    {I_XBEGIN, 1, {IMMEDIATE|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41789, 208},
    ITEMPLATE_END
};

static const struct itemplate instrux_XEND[] = {
    {I_XEND, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44891, 206},
    ITEMPLATE_END
};

static const struct itemplate instrux_XTEST[] = {
    {I_XTEST, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44896, 209},
    ITEMPLATE_END
};

static const struct itemplate instrux_ANDN[] = {
    {I_ANDN, 3, {REG_GPR|BITS32,REG_GPR|BITS32,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38424, 210},
    {I_ANDN, 3, {REG_GPR|BITS64,REG_GPR|BITS64,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38431, 211},
    ITEMPLATE_END
};

static const struct itemplate instrux_BEXTR[] = {
    {I_BEXTR, 3, {REG_GPR|BITS32,RM_GPR|BITS32,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38438, 210},
    {I_BEXTR, 3, {REG_GPR|BITS64,RM_GPR|BITS64,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38445, 211},
    {I_BEXTR, 3, {REG_GPR|BITS32,RM_GPR|BITS32,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+15993, 212},
    {I_BEXTR, 3, {REG_GPR|BITS64,RM_GPR|BITS64,IMMEDIATE|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+16001, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLCI[] = {
    {I_BLCI, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38452, 212},
    {I_BLCI, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38459, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLCIC[] = {
    {I_BLCIC, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38466, 212},
    {I_BLCIC, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38473, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLSI[] = {
    {I_BLSI, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38480, 210},
    {I_BLSI, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38487, 211},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLSIC[] = {
    {I_BLSIC, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38494, 212},
    {I_BLSIC, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38501, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLCFILL[] = {
    {I_BLCFILL, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38508, 212},
    {I_BLCFILL, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38515, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLSFILL[] = {
    {I_BLSFILL, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38522, 212},
    {I_BLSFILL, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38529, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLCMSK[] = {
    {I_BLCMSK, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38536, 212},
    {I_BLCMSK, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38543, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLSMSK[] = {
    {I_BLSMSK, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38550, 210},
    {I_BLSMSK, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38557, 211},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLSR[] = {
    {I_BLSR, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38564, 210},
    {I_BLSR, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38571, 211},
    ITEMPLATE_END
};

static const struct itemplate instrux_BLCS[] = {
    {I_BLCS, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38578, 212},
    {I_BLCS, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38585, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_BZHI[] = {
    {I_BZHI, 3, {REG_GPR|BITS32,RM_GPR|BITS32,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38592, 214},
    {I_BZHI, 3, {REG_GPR|BITS64,RM_GPR|BITS64,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38599, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_MULX[] = {
    {I_MULX, 3, {REG_GPR|BITS32,REG_GPR|BITS32,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38606, 214},
    {I_MULX, 3, {REG_GPR|BITS64,REG_GPR|BITS64,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38613, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_PDEP[] = {
    {I_PDEP, 3, {REG_GPR|BITS32,REG_GPR|BITS32,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38620, 214},
    {I_PDEP, 3, {REG_GPR|BITS64,REG_GPR|BITS64,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38627, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_PEXT[] = {
    {I_PEXT, 3, {REG_GPR|BITS32,REG_GPR|BITS32,RM_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38634, 214},
    {I_PEXT, 3, {REG_GPR|BITS64,REG_GPR|BITS64,RM_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38641, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_RORX[] = {
    {I_RORX, 3, {REG_GPR|BITS32,RM_GPR|BITS32,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16009, 214},
    {I_RORX, 3, {REG_GPR|BITS64,RM_GPR|BITS64,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16017, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_SARX[] = {
    {I_SARX, 3, {REG_GPR|BITS32,RM_GPR|BITS32,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38648, 214},
    {I_SARX, 3, {REG_GPR|BITS64,RM_GPR|BITS64,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38655, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHLX[] = {
    {I_SHLX, 3, {REG_GPR|BITS32,RM_GPR|BITS32,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38662, 214},
    {I_SHLX, 3, {REG_GPR|BITS64,RM_GPR|BITS64,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38669, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHRX[] = {
    {I_SHRX, 3, {REG_GPR|BITS32,RM_GPR|BITS32,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+38676, 214},
    {I_SHRX, 3, {REG_GPR|BITS64,RM_GPR|BITS64,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+38683, 215},
    ITEMPLATE_END
};

static const struct itemplate instrux_TZCNT[] = {
    {I_TZCNT, 2, {REG_GPR|BITS16,RM_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38690, 216},
    {I_TZCNT, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38697, 216},
    {I_TZCNT, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38704, 217},
    ITEMPLATE_END
};

static const struct itemplate instrux_TZMSK[] = {
    {I_TZMSK, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38711, 212},
    {I_TZMSK, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38718, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_T1MSKC[] = {
    {I_T1MSKC, 2, {REG_GPR|BITS32,RM_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38725, 212},
    {I_T1MSKC, 2, {REG_GPR|BITS64,RM_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38732, 213},
    ITEMPLATE_END
};

static const struct itemplate instrux_PREFETCHWT1[] = {
    {I_PREFETCHWT1, 1, {MEMORY|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44901, 218},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDMK[] = {
    {I_BNDMK, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41795, 219},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDCL[] = {
    {I_BNDCL, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+38740, 220},
    {I_BNDCL, 2, {BNDREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38740, 221},
    {I_BNDCL, 2, {BNDREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38739, 222},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDCU[] = {
    {I_BNDCU, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+38747, 220},
    {I_BNDCU, 2, {BNDREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38747, 221},
    {I_BNDCU, 2, {BNDREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38746, 222},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDCN[] = {
    {I_BNDCN, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+38754, 220},
    {I_BNDCN, 2, {BNDREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38754, 221},
    {I_BNDCN, 2, {BNDREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38753, 222},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDMOV[] = {
    {I_BNDMOV, 2, {BNDREG,BNDREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+41801, 220},
    {I_BNDMOV, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41801, 220},
    {I_BNDMOV, 2, {BNDREG,BNDREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+41807, 220},
    {I_BNDMOV, 2, {MEMORY,BNDREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+41807, 220},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDLDX[] = {
    {I_BNDLDX, 2, {BNDREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+41802, 219},
    {I_BNDLDX, 3, {BNDREG,MEMORY,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+41813, 223},
    {I_BNDLDX, 3, {BNDREG,MEMORY,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+41813, 224},
    ITEMPLATE_END
};

static const struct itemplate instrux_BNDSTX[] = {
    {I_BNDSTX, 2, {MEMORY,BNDREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+41808, 219},
    {I_BNDSTX, 3, {MEMORY,REG_GPR|BITS32,BNDREG,0,0}, NO_DECORATOR, nasm_bytecodes+41819, 223},
    {I_BNDSTX, 3, {MEMORY,REG_GPR|BITS64,BNDREG,0,0}, NO_DECORATOR, nasm_bytecodes+41819, 224},
    {I_BNDSTX, 3, {MEMORY,BNDREG,REG_GPR|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+41825, 223},
    {I_BNDSTX, 3, {MEMORY,BNDREG,REG_GPR|BITS64,0,0}, NO_DECORATOR, nasm_bytecodes+41825, 224},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA1MSG1[] = {
    {I_SHA1MSG1, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41831, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA1MSG2[] = {
    {I_SHA1MSG2, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41837, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA1NEXTE[] = {
    {I_SHA1NEXTE, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41843, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA1RNDS4[] = {
    {I_SHA1RNDS4, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+38760, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA256MSG1[] = {
    {I_SHA256MSG1, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41849, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA256MSG2[] = {
    {I_SHA256MSG2, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41855, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_SHA256RNDS2[] = {
    {I_SHA256RNDS2, 3, {XMM_L16,RM_XMM_L16|BITS128,XMM0,0,0}, NO_DECORATOR, nasm_bytecodes+41861, 225},
    {I_SHA256RNDS2, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+41861, 225},
    ITEMPLATE_END
};

static const struct itemplate instrux_KADDB[] = {
    {I_KADDB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38767, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KADDD[] = {
    {I_KADDD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38774, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KADDQ[] = {
    {I_KADDQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38781, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KADDW[] = {
    {I_KADDW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38788, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDB[] = {
    {I_KANDB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38795, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDD[] = {
    {I_KANDD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38802, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDNB[] = {
    {I_KANDNB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38809, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDND[] = {
    {I_KANDND, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38816, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDNQ[] = {
    {I_KANDNQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38823, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDNW[] = {
    {I_KANDNW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38830, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDQ[] = {
    {I_KANDQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38837, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDW[] = {
    {I_KANDW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38844, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KMOVB[] = {
    {I_KMOVB, 2, {KREG,RM_K|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38851, 226},
    {I_KMOVB, 2, {MEMORY|BITS8,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38858, 226},
    {I_KMOVB, 2, {KREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38865, 226},
    {I_KMOVB, 2, {KREG,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+16025, 226},
    {I_KMOVB, 2, {REG_GPR|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38872, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KMOVD[] = {
    {I_KMOVD, 2, {KREG,RM_K|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38879, 226},
    {I_KMOVD, 2, {MEMORY|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38886, 226},
    {I_KMOVD, 2, {KREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38893, 226},
    {I_KMOVD, 2, {REG_GPR|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38900, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KMOVQ[] = {
    {I_KMOVQ, 2, {KREG,RM_K|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38907, 226},
    {I_KMOVQ, 2, {MEMORY|BITS64,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38914, 226},
    {I_KMOVQ, 2, {KREG,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38921, 226},
    {I_KMOVQ, 2, {REG_GPR|BITS64,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38928, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KMOVW[] = {
    {I_KMOVW, 2, {KREG,RM_K|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38935, 226},
    {I_KMOVW, 2, {MEMORY|BITS16,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38942, 226},
    {I_KMOVW, 2, {KREG,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38949, 226},
    {I_KMOVW, 2, {KREG,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38949, 226},
    {I_KMOVW, 2, {REG_GPR|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38956, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KNOTB[] = {
    {I_KNOTB, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38963, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KNOTD[] = {
    {I_KNOTD, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38970, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KNOTQ[] = {
    {I_KNOTQ, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38977, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KNOTW[] = {
    {I_KNOTW, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+38984, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORB[] = {
    {I_KORB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38991, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORD[] = {
    {I_KORD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38998, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORQ[] = {
    {I_KORQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39005, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORW[] = {
    {I_KORW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39012, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORTESTB[] = {
    {I_KORTESTB, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39019, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORTESTD[] = {
    {I_KORTESTD, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39026, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORTESTQ[] = {
    {I_KORTESTQ, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39033, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORTESTW[] = {
    {I_KORTESTW, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39040, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTLB[] = {
    {I_KSHIFTLB, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16033, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTLD[] = {
    {I_KSHIFTLD, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16041, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTLQ[] = {
    {I_KSHIFTLQ, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16049, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTLW[] = {
    {I_KSHIFTLW, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16057, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTRB[] = {
    {I_KSHIFTRB, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16065, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTRD[] = {
    {I_KSHIFTRD, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16073, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTRQ[] = {
    {I_KSHIFTRQ, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16081, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTRW[] = {
    {I_KSHIFTRW, 3, {KREG,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16089, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KTESTB[] = {
    {I_KTESTB, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39047, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KTESTD[] = {
    {I_KTESTD, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39054, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KTESTQ[] = {
    {I_KTESTQ, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39061, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KTESTW[] = {
    {I_KTESTW, 2, {KREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39068, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KUNPCKBW[] = {
    {I_KUNPCKBW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39075, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KUNPCKDQ[] = {
    {I_KUNPCKDQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39082, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KUNPCKWD[] = {
    {I_KUNPCKWD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39089, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXNORB[] = {
    {I_KXNORB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39096, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXNORD[] = {
    {I_KXNORD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39103, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXNORQ[] = {
    {I_KXNORQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39110, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXNORW[] = {
    {I_KXNORW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39117, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXORB[] = {
    {I_KXORB, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39124, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXORD[] = {
    {I_KXORD, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39131, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXORQ[] = {
    {I_KXORQ, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39138, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXORW[] = {
    {I_KXORW, 3, {KREG,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39145, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KADD[] = {
    {I_KADD, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38767, 227},
    {I_KADD, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38774, 227},
    {I_KADD, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38781, 227},
    {I_KADD, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38788, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KAND[] = {
    {I_KAND, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38795, 227},
    {I_KAND, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38802, 227},
    {I_KAND, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38837, 227},
    {I_KAND, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38844, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KANDN[] = {
    {I_KANDN, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38809, 227},
    {I_KANDN, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38816, 227},
    {I_KANDN, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38823, 227},
    {I_KANDN, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38830, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KMOV[] = {
    {I_KMOV, 2, {KREG|BITS8,RM_K|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38851, 227},
    {I_KMOV, 2, {MEMORY|BITS8,KREG|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38858, 228},
    {I_KMOV, 2, {KREG|BITS8,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38865, 229},
    {I_KMOV, 2, {KREG|BITS8,REG_GPR|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38865, 227},
    {I_KMOV, 2, {REG_GPR|BITS32,KREG|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38872, 229},
    {I_KMOV, 2, {KREG|BITS32,RM_K|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38879, 227},
    {I_KMOV, 2, {MEMORY|BITS32,KREG|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38886, 227},
    {I_KMOV, 2, {KREG|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38893, 227},
    {I_KMOV, 2, {REG_GPR|BITS32,KREG|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38900, 227},
    {I_KMOV, 2, {KREG|BITS64,RM_K|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38907, 227},
    {I_KMOV, 2, {MEMORY|BITS64,KREG|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38914, 227},
    {I_KMOV, 2, {KREG|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38921, 227},
    {I_KMOV, 2, {REG_GPR|BITS64,KREG|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38928, 227},
    {I_KMOV, 2, {KREG|BITS16,RM_K|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38935, 227},
    {I_KMOV, 2, {MEMORY|BITS16,KREG|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38942, 227},
    {I_KMOV, 2, {KREG|BITS16,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38949, 229},
    {I_KMOV, 2, {REG_GPR|BITS32,KREG|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38956, 229},
    {I_KMOV, 2, {KREG|BITS16,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38949, 229},
    {I_KMOV, 2, {KREG|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38949, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KNOT[] = {
    {I_KNOT, 2, {KREG|BITS8,KREG|BITS8,0,0,0}, NO_DECORATOR, nasm_bytecodes+38963, 227},
    {I_KNOT, 2, {KREG|BITS32,KREG|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+38970, 227},
    {I_KNOT, 2, {KREG|BITS64,KREG|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+38977, 227},
    {I_KNOT, 2, {KREG|BITS16,KREG|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+38984, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KOR[] = {
    {I_KOR, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38991, 227},
    {I_KOR, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+38998, 227},
    {I_KOR, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39005, 227},
    {I_KOR, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39012, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KORTEST[] = {
    {I_KORTEST, 2, {KREG|BITS8,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39019, 227},
    {I_KORTEST, 2, {KREG|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39026, 227},
    {I_KORTEST, 2, {KREG|BITS64,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39033, 227},
    {I_KORTEST, 2, {KREG|BITS16,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39040, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTL[] = {
    {I_KSHIFTL, 3, {KREG|BITS8,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16033, 230},
    {I_KSHIFTL, 3, {KREG|BITS32,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16041, 230},
    {I_KSHIFTL, 3, {KREG|BITS64,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16049, 230},
    {I_KSHIFTL, 3, {KREG|BITS16,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16057, 230},
    ITEMPLATE_END
};

static const struct itemplate instrux_KSHIFTR[] = {
    {I_KSHIFTR, 3, {KREG|BITS8,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16065, 230},
    {I_KSHIFTR, 3, {KREG|BITS32,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16073, 230},
    {I_KSHIFTR, 3, {KREG|BITS64,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16081, 230},
    {I_KSHIFTR, 3, {KREG|BITS16,KREG,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+16089, 230},
    ITEMPLATE_END
};

static const struct itemplate instrux_KTEST[] = {
    {I_KTEST, 2, {KREG|BITS8,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39047, 227},
    {I_KTEST, 2, {KREG|BITS32,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39054, 227},
    {I_KTEST, 2, {KREG|BITS64,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39061, 227},
    {I_KTEST, 2, {KREG|BITS16,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39068, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KUNPCK[] = {
    {I_KUNPCK, 3, {KREG|BITS16,KREG|BITS8,KREG|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+39075, 226},
    {I_KUNPCK, 3, {KREG|BITS64,KREG|BITS32,KREG|BITS32,0,0}, NO_DECORATOR, nasm_bytecodes+39082, 226},
    {I_KUNPCK, 3, {KREG|BITS32,KREG|BITS16,KREG|BITS16,0,0}, NO_DECORATOR, nasm_bytecodes+39089, 226},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXNOR[] = {
    {I_KXNOR, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39096, 227},
    {I_KXNOR, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39103, 227},
    {I_KXNOR, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39110, 227},
    {I_KXNOR, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39117, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_KXOR[] = {
    {I_KXOR, 3, {KREG|BITS8,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39124, 227},
    {I_KXOR, 3, {KREG|BITS32,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39131, 227},
    {I_KXOR, 3, {KREG|BITS64,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39138, 227},
    {I_KXOR, 3, {KREG|BITS16,KREG,KREG,0,0}, NO_DECORATOR, nasm_bytecodes+39145, 227},
    ITEMPLATE_END
};

static const struct itemplate instrux_VALIGND[] = {
    {I_VALIGND, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+8002, 231},
    {I_VALIGND, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8011, 231},
    {I_VALIGND, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+8020, 231},
    {I_VALIGND, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8029, 231},
    {I_VALIGND, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+8038, 232},
    {I_VALIGND, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8047, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VALIGNQ[] = {
    {I_VALIGNQ, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+8056, 231},
    {I_VALIGNQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8065, 231},
    {I_VALIGNQ, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+8074, 231},
    {I_VALIGNQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8083, 231},
    {I_VALIGNQ, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+8092, 232},
    {I_VALIGNQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8101, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDMPD[] = {
    {I_VBLENDMPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16417, 231},
    {I_VBLENDMPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16425, 231},
    {I_VBLENDMPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+16433, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBLENDMPS[] = {
    {I_VBLENDMPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16441, 231},
    {I_VBLENDMPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16449, 231},
    {I_VBLENDMPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+16457, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF32X2[] = {
    {I_VBROADCASTF32X2, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16465, 233},
    {I_VBROADCASTF32X2, 2, {ZMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16473, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF32X4[] = {
    {I_VBROADCASTF32X4, 2, {YMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16481, 231},
    {I_VBROADCASTF32X4, 2, {ZMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16489, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF32X8[] = {
    {I_VBROADCASTF32X8, 2, {ZMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16497, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF64X2[] = {
    {I_VBROADCASTF64X2, 2, {YMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16505, 233},
    {I_VBROADCASTF64X2, 2, {ZMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16513, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTF64X4[] = {
    {I_VBROADCASTF64X4, 2, {ZMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16521, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI32X2[] = {
    {I_VBROADCASTI32X2, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16529, 233},
    {I_VBROADCASTI32X2, 2, {YMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16537, 233},
    {I_VBROADCASTI32X2, 2, {ZMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16545, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI32X4[] = {
    {I_VBROADCASTI32X4, 2, {YMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16553, 231},
    {I_VBROADCASTI32X4, 2, {ZMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16561, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI32X8[] = {
    {I_VBROADCASTI32X8, 2, {ZMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16569, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI64X2[] = {
    {I_VBROADCASTI64X2, 2, {YMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16577, 233},
    {I_VBROADCASTI64X2, 2, {ZMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16585, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VBROADCASTI64X4[] = {
    {I_VBROADCASTI64X4, 2, {ZMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16593, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OQPD[] = {
    {I_VCMPEQ_OQPD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+240, 231},
    {I_VCMPEQ_OQPD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+250, 231},
    {I_VCMPEQ_OQPD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64|SAE,0,0}, nasm_bytecodes+260, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OQPS[] = {
    {I_VCMPEQ_OQPS, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+270, 231},
    {I_VCMPEQ_OQPS, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+280, 231},
    {I_VCMPEQ_OQPS, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32|SAE,0,0}, nasm_bytecodes+290, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OQSD[] = {
    {I_VCMPEQ_OQSD, 3, {KREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+300, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCMPEQ_OQSS[] = {
    {I_VCMPEQ_OQSS, 3, {KREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK,0,SAE,0,0}, nasm_bytecodes+310, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCOMPRESSPD[] = {
    {I_VCOMPRESSPD, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16697, 231},
    {I_VCOMPRESSPD, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16705, 231},
    {I_VCOMPRESSPD, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16713, 232},
    {I_VCOMPRESSPD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16721, 231},
    {I_VCOMPRESSPD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16729, 231},
    {I_VCOMPRESSPD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16737, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCOMPRESSPS[] = {
    {I_VCOMPRESSPS, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16745, 231},
    {I_VCOMPRESSPS, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16753, 231},
    {I_VCOMPRESSPS, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+16761, 232},
    {I_VCOMPRESSPS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16769, 231},
    {I_VCOMPRESSPS, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16777, 231},
    {I_VCOMPRESSPS, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+16785, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPD2QQ[] = {
    {I_VCVTPD2QQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16889, 233},
    {I_VCVTPD2QQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16897, 233},
    {I_VCVTPD2QQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16905, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPD2UDQ[] = {
    {I_VCVTPD2UDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16913, 231},
    {I_VCVTPD2UDQ, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16921, 231},
    {I_VCVTPD2UDQ, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16929, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPD2UQQ[] = {
    {I_VCVTPD2UQQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16937, 233},
    {I_VCVTPD2UQQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+16945, 233},
    {I_VCVTPD2UQQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+16953, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2QQ[] = {
    {I_VCVTPS2QQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17033, 233},
    {I_VCVTPS2QQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17041, 233},
    {I_VCVTPS2QQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17049, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2UDQ[] = {
    {I_VCVTPS2UDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17057, 231},
    {I_VCVTPS2UDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17065, 231},
    {I_VCVTPS2UDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17073, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTPS2UQQ[] = {
    {I_VCVTPS2UQQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17081, 233},
    {I_VCVTPS2UQQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17089, 233},
    {I_VCVTPS2UQQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17097, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTQQ2PD[] = {
    {I_VCVTQQ2PD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17105, 233},
    {I_VCVTQQ2PD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17113, 233},
    {I_VCVTQQ2PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+17121, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTQQ2PS[] = {
    {I_VCVTQQ2PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17129, 233},
    {I_VCVTQQ2PS, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17137, 233},
    {I_VCVTQQ2PS, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+17145, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSD2USI[] = {
    {I_VCVTSD2USI, 2, {REG_GPR|BITS32,RM_XMM|BITS64,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17177, 232},
    {I_VCVTSD2USI, 2, {REG_GPR|BITS64,RM_XMM|BITS64,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17185, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTSS2USI[] = {
    {I_VCVTSS2USI, 2, {REG_GPR|BITS32,RM_XMM|BITS32,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17249, 232},
    {I_VCVTSS2USI, 2, {REG_GPR|BITS64,RM_XMM|BITS32,0,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17257, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPD2QQ[] = {
    {I_VCVTTPD2QQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17289, 233},
    {I_VCVTTPD2QQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17297, 233},
    {I_VCVTTPD2QQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+17305, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPD2UDQ[] = {
    {I_VCVTTPD2UDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17313, 231},
    {I_VCVTTPD2UDQ, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17321, 231},
    {I_VCVTTPD2UDQ, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+17329, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPD2UQQ[] = {
    {I_VCVTTPD2UQQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17337, 233},
    {I_VCVTTPD2UQQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17345, 233},
    {I_VCVTTPD2UQQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+17353, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPS2QQ[] = {
    {I_VCVTTPS2QQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17385, 233},
    {I_VCVTTPS2QQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17393, 233},
    {I_VCVTTPS2QQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17401, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPS2UDQ[] = {
    {I_VCVTTPS2UDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17409, 231},
    {I_VCVTTPS2UDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17417, 231},
    {I_VCVTTPS2UDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17425, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTPS2UQQ[] = {
    {I_VCVTTPS2UQQ, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17433, 233},
    {I_VCVTTPS2UQQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17441, 233},
    {I_VCVTTPS2UQQ, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17449, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTSD2USI[] = {
    {I_VCVTTSD2USI, 2, {REG_GPR|BITS32,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17473, 232},
    {I_VCVTTSD2USI, 2, {REG_GPR|BITS64,RM_XMM|BITS64,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17481, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTTSS2USI[] = {
    {I_VCVTTSS2USI, 2, {REG_GPR|BITS32,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17505, 232},
    {I_VCVTTSS2USI, 2, {REG_GPR|BITS64,RM_XMM|BITS32,0,0,0}, {0,SAE,0,0,0}, nasm_bytecodes+17513, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUDQ2PD[] = {
    {I_VCVTUDQ2PD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17521, 231},
    {I_VCVTUDQ2PD, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17529, 231},
    {I_VCVTUDQ2PD, 2, {ZMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17537, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUDQ2PS[] = {
    {I_VCVTUDQ2PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17545, 231},
    {I_VCVTUDQ2PS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+17553, 231},
    {I_VCVTUDQ2PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+17561, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUQQ2PD[] = {
    {I_VCVTUQQ2PD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17569, 233},
    {I_VCVTUQQ2PD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17577, 233},
    {I_VCVTUQQ2PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+17585, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUQQ2PS[] = {
    {I_VCVTUQQ2PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17593, 233},
    {I_VCVTUQQ2PS, 2, {XMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+17601, 233},
    {I_VCVTUQQ2PS, 2, {YMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+17609, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUSI2SD[] = {
    {I_VCVTUSI2SD, 3, {XMMREG,XMMREG,RM_GPR|BITS32,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17617, 232},
    {I_VCVTUSI2SD, 3, {XMMREG,XMMREG,RM_GPR|BITS64,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17625, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTUSI2SS[] = {
    {I_VCVTUSI2SS, 3, {XMMREG,XMMREG,RM_GPR|BITS32,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17633, 232},
    {I_VCVTUSI2SS, 3, {XMMREG,XMMREG,RM_GPR|BITS64,0,0}, {0,ER,0,0,0}, nasm_bytecodes+17641, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDBPSADBW[] = {
    {I_VDBPSADBW, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8209, 235},
    {I_VDBPSADBW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8218, 235},
    {I_VDBPSADBW, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8227, 235},
    {I_VDBPSADBW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8236, 235},
    {I_VDBPSADBW, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8245, 236},
    {I_VDBPSADBW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8254, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXP2PD[] = {
    {I_VEXP2PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+17777, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXP2PS[] = {
    {I_VEXP2PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+17785, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXPANDPD[] = {
    {I_VEXPANDPD, 2, {XMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17793, 231},
    {I_VEXPANDPD, 2, {YMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17801, 231},
    {I_VEXPANDPD, 2, {ZMMREG,MEMORY|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17809, 232},
    {I_VEXPANDPD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17793, 231},
    {I_VEXPANDPD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17801, 231},
    {I_VEXPANDPD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17809, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXPANDPS[] = {
    {I_VEXPANDPS, 2, {XMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17817, 231},
    {I_VEXPANDPS, 2, {YMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17825, 231},
    {I_VEXPANDPS, 2, {ZMMREG,MEMORY|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17833, 232},
    {I_VEXPANDPS, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17817, 231},
    {I_VEXPANDPS, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17825, 231},
    {I_VEXPANDPS, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+17833, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTF32X4[] = {
    {I_VEXTRACTF32X4, 3, {XMMREG,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8263, 231},
    {I_VEXTRACTF32X4, 3, {XMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8272, 232},
    {I_VEXTRACTF32X4, 3, {MEMORY|BITS128,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8281, 231},
    {I_VEXTRACTF32X4, 3, {MEMORY|BITS128,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8290, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTF32X8[] = {
    {I_VEXTRACTF32X8, 3, {YMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8299, 234},
    {I_VEXTRACTF32X8, 3, {MEMORY|BITS256,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8308, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTF64X2[] = {
    {I_VEXTRACTF64X2, 3, {XMMREG,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8317, 233},
    {I_VEXTRACTF64X2, 3, {XMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8326, 234},
    {I_VEXTRACTF64X2, 3, {MEMORY|BITS128,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8335, 233},
    {I_VEXTRACTF64X2, 3, {MEMORY|BITS128,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8344, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTF64X4[] = {
    {I_VEXTRACTF64X4, 3, {YMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8353, 232},
    {I_VEXTRACTF64X4, 3, {MEMORY|BITS256,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8362, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTI32X4[] = {
    {I_VEXTRACTI32X4, 3, {XMMREG,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8371, 231},
    {I_VEXTRACTI32X4, 3, {XMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8380, 232},
    {I_VEXTRACTI32X4, 3, {MEMORY|BITS128,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8389, 231},
    {I_VEXTRACTI32X4, 3, {MEMORY|BITS128,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8398, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTI32X8[] = {
    {I_VEXTRACTI32X8, 3, {YMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8407, 234},
    {I_VEXTRACTI32X8, 3, {MEMORY|BITS256,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8416, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTI64X2[] = {
    {I_VEXTRACTI64X2, 3, {XMMREG,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8425, 233},
    {I_VEXTRACTI64X2, 3, {XMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8434, 234},
    {I_VEXTRACTI64X2, 3, {MEMORY|BITS128,YMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8443, 233},
    {I_VEXTRACTI64X2, 3, {MEMORY|BITS128,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8452, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VEXTRACTI64X4[] = {
    {I_VEXTRACTI64X4, 3, {YMMREG,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8461, 232},
    {I_VEXTRACTI64X4, 3, {MEMORY|BITS256,ZMMREG,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8470, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFIXUPIMMPD[] = {
    {I_VFIXUPIMMPD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+8488, 231},
    {I_VFIXUPIMMPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8497, 231},
    {I_VFIXUPIMMPD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+8506, 231},
    {I_VFIXUPIMMPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8515, 231},
    {I_VFIXUPIMMPD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64|SAE,0,0}, nasm_bytecodes+8524, 232},
    {I_VFIXUPIMMPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+8533, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFIXUPIMMPS[] = {
    {I_VFIXUPIMMPS, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+8542, 231},
    {I_VFIXUPIMMPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8551, 231},
    {I_VFIXUPIMMPS, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+8560, 231},
    {I_VFIXUPIMMPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8569, 231},
    {I_VFIXUPIMMPS, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32|SAE,0,0}, nasm_bytecodes+8578, 232},
    {I_VFIXUPIMMPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+8587, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFIXUPIMMSD[] = {
    {I_VFIXUPIMMSD, 4, {XMMREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+8596, 232},
    {I_VFIXUPIMMSD, 3, {XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+8605, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFIXUPIMMSS[] = {
    {I_VFIXUPIMMSS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+8614, 232},
    {I_VFIXUPIMMSS, 3, {XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+8623, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFPCLASSPD[] = {
    {I_VFPCLASSPD, 3, {KREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK,B64,0,0,0}, nasm_bytecodes+8632, 233},
    {I_VFPCLASSPD, 3, {KREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK,B64,0,0,0}, nasm_bytecodes+8641, 233},
    {I_VFPCLASSPD, 3, {KREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK,B64,0,0,0}, nasm_bytecodes+8650, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFPCLASSPS[] = {
    {I_VFPCLASSPS, 3, {KREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK,B32,0,0,0}, nasm_bytecodes+8659, 233},
    {I_VFPCLASSPS, 3, {KREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK,B32,0,0,0}, nasm_bytecodes+8668, 233},
    {I_VFPCLASSPS, 3, {KREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK,B32,0,0,0}, nasm_bytecodes+8677, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFPCLASSSD[] = {
    {I_VFPCLASSSD, 3, {KREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8686, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VFPCLASSSS[] = {
    {I_VFPCLASSSS, 3, {KREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8695, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF0DPD[] = {
    {I_VGATHERPF0DPD, 1, {YMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8758, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF0DPS[] = {
    {I_VGATHERPF0DPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8767, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF0QPD[] = {
    {I_VGATHERPF0QPD, 1, {ZMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8776, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF0QPS[] = {
    {I_VGATHERPF0QPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8785, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF1DPD[] = {
    {I_VGATHERPF1DPD, 1, {YMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8794, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF1DPS[] = {
    {I_VGATHERPF1DPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8803, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF1QPD[] = {
    {I_VGATHERPF1QPD, 1, {ZMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8812, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGATHERPF1QPS[] = {
    {I_VGATHERPF1QPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+8821, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETEXPPD[] = {
    {I_VGETEXPPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+18897, 231},
    {I_VGETEXPPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+18905, 231},
    {I_VGETEXPPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+18913, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETEXPPS[] = {
    {I_VGETEXPPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+18921, 231},
    {I_VGETEXPPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+18929, 231},
    {I_VGETEXPPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+18937, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETEXPSD[] = {
    {I_VGETEXPSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+18945, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETEXPSS[] = {
    {I_VGETEXPSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+18953, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETMANTPD[] = {
    {I_VGETMANTPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8884, 231},
    {I_VGETMANTPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+8893, 231},
    {I_VGETMANTPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+8902, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETMANTPS[] = {
    {I_VGETMANTPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8911, 231},
    {I_VGETMANTPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+8920, 231},
    {I_VGETMANTPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+8929, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETMANTSD[] = {
    {I_VGETMANTSD, 4, {XMMREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+8938, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGETMANTSS[] = {
    {I_VGETMANTSS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+8947, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTF32X4[] = {
    {I_VINSERTF32X4, 4, {YMMREG,YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8956, 231},
    {I_VINSERTF32X4, 3, {YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8965, 231},
    {I_VINSERTF32X4, 4, {ZMMREG,ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8974, 232},
    {I_VINSERTF32X4, 3, {ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8983, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTF32X8[] = {
    {I_VINSERTF32X8, 4, {ZMMREG,ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+8992, 234},
    {I_VINSERTF32X8, 3, {ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9001, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTF64X2[] = {
    {I_VINSERTF64X2, 4, {YMMREG,YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9010, 233},
    {I_VINSERTF64X2, 3, {YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9019, 233},
    {I_VINSERTF64X2, 4, {ZMMREG,ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9028, 234},
    {I_VINSERTF64X2, 3, {ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9037, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTF64X4[] = {
    {I_VINSERTF64X4, 4, {ZMMREG,ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9046, 232},
    {I_VINSERTF64X4, 3, {ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9055, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTI32X4[] = {
    {I_VINSERTI32X4, 4, {YMMREG,YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9064, 231},
    {I_VINSERTI32X4, 3, {YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9073, 231},
    {I_VINSERTI32X4, 4, {ZMMREG,ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9082, 232},
    {I_VINSERTI32X4, 3, {ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9091, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTI32X8[] = {
    {I_VINSERTI32X8, 4, {ZMMREG,ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9100, 234},
    {I_VINSERTI32X8, 3, {ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9109, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTI64X2[] = {
    {I_VINSERTI64X2, 4, {YMMREG,YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9118, 233},
    {I_VINSERTI64X2, 3, {YMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9127, 233},
    {I_VINSERTI64X2, 4, {ZMMREG,ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9136, 234},
    {I_VINSERTI64X2, 3, {ZMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9145, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VINSERTI64X4[] = {
    {I_VINSERTI64X4, 4, {ZMMREG,ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9154, 232},
    {I_VINSERTI64X4, 3, {ZMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9163, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQA32[] = {
    {I_VMOVDQA32, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19401, 231},
    {I_VMOVDQA32, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19409, 231},
    {I_VMOVDQA32, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19417, 232},
    {I_VMOVDQA32, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19425, 231},
    {I_VMOVDQA32, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19433, 231},
    {I_VMOVDQA32, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19441, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQA64[] = {
    {I_VMOVDQA64, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19449, 231},
    {I_VMOVDQA64, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19457, 231},
    {I_VMOVDQA64, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19465, 232},
    {I_VMOVDQA64, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19473, 231},
    {I_VMOVDQA64, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19481, 231},
    {I_VMOVDQA64, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19489, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQU16[] = {
    {I_VMOVDQU16, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19497, 235},
    {I_VMOVDQU16, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19505, 235},
    {I_VMOVDQU16, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19513, 236},
    {I_VMOVDQU16, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19521, 235},
    {I_VMOVDQU16, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19529, 235},
    {I_VMOVDQU16, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19537, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQU32[] = {
    {I_VMOVDQU32, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19545, 231},
    {I_VMOVDQU32, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19553, 231},
    {I_VMOVDQU32, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19561, 232},
    {I_VMOVDQU32, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19569, 231},
    {I_VMOVDQU32, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19577, 231},
    {I_VMOVDQU32, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19585, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQU64[] = {
    {I_VMOVDQU64, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19593, 231},
    {I_VMOVDQU64, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19601, 231},
    {I_VMOVDQU64, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19609, 232},
    {I_VMOVDQU64, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19617, 231},
    {I_VMOVDQU64, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19625, 231},
    {I_VMOVDQU64, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19633, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VMOVDQU8[] = {
    {I_VMOVDQU8, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19641, 235},
    {I_VMOVDQU8, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19649, 235},
    {I_VMOVDQU8, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19657, 236},
    {I_VMOVDQU8, 2, {RM_XMM|BITS128,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19665, 235},
    {I_VMOVDQU8, 2, {RM_YMM|BITS256,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19673, 235},
    {I_VMOVDQU8, 2, {RM_ZMM|BITS512,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+19681, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPABSQ[] = {
    {I_VPABSQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20505, 231},
    {I_VPABSQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20513, 231},
    {I_VPABSQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+20521, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPANDD[] = {
    {I_VPANDD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21129, 231},
    {I_VPANDD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21137, 231},
    {I_VPANDD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21145, 231},
    {I_VPANDD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21153, 231},
    {I_VPANDD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21161, 232},
    {I_VPANDD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21169, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPANDND[] = {
    {I_VPANDND, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21177, 231},
    {I_VPANDND, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21185, 231},
    {I_VPANDND, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21193, 231},
    {I_VPANDND, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21201, 231},
    {I_VPANDND, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21209, 232},
    {I_VPANDND, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+21217, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPANDNQ[] = {
    {I_VPANDNQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21225, 231},
    {I_VPANDNQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21233, 231},
    {I_VPANDNQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21241, 231},
    {I_VPANDNQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21249, 231},
    {I_VPANDNQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21257, 232},
    {I_VPANDNQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21265, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPANDQ[] = {
    {I_VPANDQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21273, 231},
    {I_VPANDQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21281, 231},
    {I_VPANDQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21289, 231},
    {I_VPANDQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21297, 231},
    {I_VPANDQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21305, 232},
    {I_VPANDQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+21313, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDMB[] = {
    {I_VPBLENDMB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21417, 235},
    {I_VPBLENDMB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21425, 235},
    {I_VPBLENDMB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21433, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDMD[] = {
    {I_VPBLENDMD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21441, 231},
    {I_VPBLENDMD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21449, 231},
    {I_VPBLENDMD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+21457, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDMQ[] = {
    {I_VPBLENDMQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21465, 231},
    {I_VPBLENDMQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21473, 231},
    {I_VPBLENDMQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+21481, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBLENDMW[] = {
    {I_VPBLENDMW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21489, 235},
    {I_VPBLENDMW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21497, 235},
    {I_VPBLENDMW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+21505, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTMB2Q[] = {
    {I_VPBROADCASTMB2Q, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21633, 239},
    {I_VPBROADCASTMB2Q, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21641, 239},
    {I_VPBROADCASTMB2Q, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21649, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPBROADCASTMW2D[] = {
    {I_VPBROADCASTMW2D, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21657, 239},
    {I_VPBROADCASTMW2D, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21665, 239},
    {I_VPBROADCASTMW2D, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+21673, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQUB[] = {
    {I_VPCMPEQUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2890, 235},
    {I_VPCMPEQUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2900, 235},
    {I_VPCMPEQUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2910, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQUD[] = {
    {I_VPCMPEQUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2920, 231},
    {I_VPCMPEQUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2930, 231},
    {I_VPCMPEQUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+2940, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQUQ[] = {
    {I_VPCMPEQUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2950, 231},
    {I_VPCMPEQUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2960, 231},
    {I_VPCMPEQUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+2970, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPEQUW[] = {
    {I_VPCMPEQUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2980, 235},
    {I_VPCMPEQUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+2990, 235},
    {I_VPCMPEQUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3000, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEB[] = {
    {I_VPCMPGEB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3040, 235},
    {I_VPCMPGEB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3050, 235},
    {I_VPCMPGEB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3060, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGED[] = {
    {I_VPCMPGED, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3070, 231},
    {I_VPCMPGED, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3080, 231},
    {I_VPCMPGED, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3090, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEQ[] = {
    {I_VPCMPGEQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3100, 231},
    {I_VPCMPGEQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3110, 231},
    {I_VPCMPGEQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3120, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEUB[] = {
    {I_VPCMPGEUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3130, 235},
    {I_VPCMPGEUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3140, 235},
    {I_VPCMPGEUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3150, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEUD[] = {
    {I_VPCMPGEUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3160, 231},
    {I_VPCMPGEUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3170, 231},
    {I_VPCMPGEUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3180, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEUQ[] = {
    {I_VPCMPGEUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3190, 231},
    {I_VPCMPGEUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3200, 231},
    {I_VPCMPGEUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3210, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEUW[] = {
    {I_VPCMPGEUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3220, 235},
    {I_VPCMPGEUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3230, 235},
    {I_VPCMPGEUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3240, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGEW[] = {
    {I_VPCMPGEW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3250, 235},
    {I_VPCMPGEW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3260, 235},
    {I_VPCMPGEW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3270, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTUB[] = {
    {I_VPCMPGTUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3370, 235},
    {I_VPCMPGTUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3380, 235},
    {I_VPCMPGTUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3390, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTUD[] = {
    {I_VPCMPGTUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3400, 231},
    {I_VPCMPGTUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3410, 231},
    {I_VPCMPGTUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTUQ[] = {
    {I_VPCMPGTUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3430, 231},
    {I_VPCMPGTUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3440, 231},
    {I_VPCMPGTUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3450, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPGTUW[] = {
    {I_VPCMPGTUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3460, 235},
    {I_VPCMPGTUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3470, 235},
    {I_VPCMPGTUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3480, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEB[] = {
    {I_VPCMPLEB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3520, 235},
    {I_VPCMPLEB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3530, 235},
    {I_VPCMPLEB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3540, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLED[] = {
    {I_VPCMPLED, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3550, 231},
    {I_VPCMPLED, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3560, 231},
    {I_VPCMPLED, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3570, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEQ[] = {
    {I_VPCMPLEQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3580, 231},
    {I_VPCMPLEQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3590, 231},
    {I_VPCMPLEQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3600, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEUB[] = {
    {I_VPCMPLEUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3610, 235},
    {I_VPCMPLEUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3620, 235},
    {I_VPCMPLEUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3630, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEUD[] = {
    {I_VPCMPLEUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3640, 231},
    {I_VPCMPLEUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3650, 231},
    {I_VPCMPLEUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEUQ[] = {
    {I_VPCMPLEUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3670, 231},
    {I_VPCMPLEUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3680, 231},
    {I_VPCMPLEUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3690, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEUW[] = {
    {I_VPCMPLEUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3700, 235},
    {I_VPCMPLEUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3710, 235},
    {I_VPCMPLEUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3720, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLEW[] = {
    {I_VPCMPLEW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3730, 235},
    {I_VPCMPLEW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3740, 235},
    {I_VPCMPLEW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3750, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTB[] = {
    {I_VPCMPLTB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3760, 235},
    {I_VPCMPLTB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3770, 235},
    {I_VPCMPLTB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3780, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTD[] = {
    {I_VPCMPLTD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3790, 231},
    {I_VPCMPLTD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3800, 231},
    {I_VPCMPLTD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3810, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTQ[] = {
    {I_VPCMPLTQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3820, 231},
    {I_VPCMPLTQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3830, 231},
    {I_VPCMPLTQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3840, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTUB[] = {
    {I_VPCMPLTUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3850, 235},
    {I_VPCMPLTUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3860, 235},
    {I_VPCMPLTUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3870, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTUD[] = {
    {I_VPCMPLTUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3880, 231},
    {I_VPCMPLTUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3890, 231},
    {I_VPCMPLTUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3900, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTUQ[] = {
    {I_VPCMPLTUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3910, 231},
    {I_VPCMPLTUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3920, 231},
    {I_VPCMPLTUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3930, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTUW[] = {
    {I_VPCMPLTUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3940, 235},
    {I_VPCMPLTUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3950, 235},
    {I_VPCMPLTUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3960, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPLTW[] = {
    {I_VPCMPLTW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3970, 235},
    {I_VPCMPLTW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3980, 235},
    {I_VPCMPLTW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3990, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQB[] = {
    {I_VPCMPNEQB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4000, 235},
    {I_VPCMPNEQB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4010, 235},
    {I_VPCMPNEQB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4020, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQD[] = {
    {I_VPCMPNEQD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4030, 231},
    {I_VPCMPNEQD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4040, 231},
    {I_VPCMPNEQD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4050, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQQ[] = {
    {I_VPCMPNEQQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4060, 231},
    {I_VPCMPNEQQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4070, 231},
    {I_VPCMPNEQQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4080, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQUB[] = {
    {I_VPCMPNEQUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4090, 235},
    {I_VPCMPNEQUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4100, 235},
    {I_VPCMPNEQUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4110, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQUD[] = {
    {I_VPCMPNEQUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4120, 231},
    {I_VPCMPNEQUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4130, 231},
    {I_VPCMPNEQUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+4140, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQUQ[] = {
    {I_VPCMPNEQUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4150, 231},
    {I_VPCMPNEQUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4160, 231},
    {I_VPCMPNEQUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+4170, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQUW[] = {
    {I_VPCMPNEQUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4180, 235},
    {I_VPCMPNEQUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4190, 235},
    {I_VPCMPNEQUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4200, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNEQW[] = {
    {I_VPCMPNEQW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4210, 235},
    {I_VPCMPNEQW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4220, 235},
    {I_VPCMPNEQW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+4230, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTB[] = {
    {I_VPCMPNGTB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3520, 235},
    {I_VPCMPNGTB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3530, 235},
    {I_VPCMPNGTB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3540, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTD[] = {
    {I_VPCMPNGTD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3550, 231},
    {I_VPCMPNGTD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3560, 231},
    {I_VPCMPNGTD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3570, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTQ[] = {
    {I_VPCMPNGTQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3580, 231},
    {I_VPCMPNGTQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3590, 231},
    {I_VPCMPNGTQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3600, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTUB[] = {
    {I_VPCMPNGTUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3610, 235},
    {I_VPCMPNGTUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3620, 235},
    {I_VPCMPNGTUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3630, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTUD[] = {
    {I_VPCMPNGTUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3640, 231},
    {I_VPCMPNGTUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3650, 231},
    {I_VPCMPNGTUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3660, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTUQ[] = {
    {I_VPCMPNGTUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3670, 231},
    {I_VPCMPNGTUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3680, 231},
    {I_VPCMPNGTUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3690, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTUW[] = {
    {I_VPCMPNGTUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3700, 235},
    {I_VPCMPNGTUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3710, 235},
    {I_VPCMPNGTUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3720, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNGTW[] = {
    {I_VPCMPNGTW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3730, 235},
    {I_VPCMPNGTW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3740, 235},
    {I_VPCMPNGTW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3750, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEB[] = {
    {I_VPCMPNLEB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3280, 235},
    {I_VPCMPNLEB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3290, 235},
    {I_VPCMPNLEB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3300, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLED[] = {
    {I_VPCMPNLED, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3310, 231},
    {I_VPCMPNLED, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3320, 231},
    {I_VPCMPNLED, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3330, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEQ[] = {
    {I_VPCMPNLEQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3340, 231},
    {I_VPCMPNLEQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3350, 231},
    {I_VPCMPNLEQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3360, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEUB[] = {
    {I_VPCMPNLEUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3370, 235},
    {I_VPCMPNLEUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3380, 235},
    {I_VPCMPNLEUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3390, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEUD[] = {
    {I_VPCMPNLEUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3400, 231},
    {I_VPCMPNLEUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3410, 231},
    {I_VPCMPNLEUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3420, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEUQ[] = {
    {I_VPCMPNLEUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3430, 231},
    {I_VPCMPNLEUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3440, 231},
    {I_VPCMPNLEUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3450, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEUW[] = {
    {I_VPCMPNLEUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3460, 235},
    {I_VPCMPNLEUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3470, 235},
    {I_VPCMPNLEUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3480, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLEW[] = {
    {I_VPCMPNLEW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3490, 235},
    {I_VPCMPNLEW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3500, 235},
    {I_VPCMPNLEW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3510, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTB[] = {
    {I_VPCMPNLTB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3040, 235},
    {I_VPCMPNLTB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3050, 235},
    {I_VPCMPNLTB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3060, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTD[] = {
    {I_VPCMPNLTD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3070, 231},
    {I_VPCMPNLTD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3080, 231},
    {I_VPCMPNLTD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3090, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTQ[] = {
    {I_VPCMPNLTQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3100, 231},
    {I_VPCMPNLTQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3110, 231},
    {I_VPCMPNLTQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3120, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTUB[] = {
    {I_VPCMPNLTUB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3130, 235},
    {I_VPCMPNLTUB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3140, 235},
    {I_VPCMPNLTUB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3150, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTUD[] = {
    {I_VPCMPNLTUD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3160, 231},
    {I_VPCMPNLTUD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3170, 231},
    {I_VPCMPNLTUD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+3180, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTUQ[] = {
    {I_VPCMPNLTUQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3190, 231},
    {I_VPCMPNLTUQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3200, 231},
    {I_VPCMPNLTUQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+3210, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTUW[] = {
    {I_VPCMPNLTUW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3220, 235},
    {I_VPCMPNLTUW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3230, 235},
    {I_VPCMPNLTUW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3240, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPNLTW[] = {
    {I_VPCMPNLTW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3250, 235},
    {I_VPCMPNLTW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3260, 235},
    {I_VPCMPNLTW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+3270, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPB[] = {
    {I_VPCMPB, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9244, 235},
    {I_VPCMPB, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9253, 235},
    {I_VPCMPB, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9262, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPD[] = {
    {I_VPCMPD, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9271, 231},
    {I_VPCMPD, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9280, 231},
    {I_VPCMPD, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9289, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPQ[] = {
    {I_VPCMPQ, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9298, 231},
    {I_VPCMPQ, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9307, 231},
    {I_VPCMPQ, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9316, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPUB[] = {
    {I_VPCMPUB, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9325, 235},
    {I_VPCMPUB, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9334, 235},
    {I_VPCMPUB, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9343, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPUD[] = {
    {I_VPCMPUD, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9352, 231},
    {I_VPCMPUD, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9361, 231},
    {I_VPCMPUD, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B32,0,0}, nasm_bytecodes+9370, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPUQ[] = {
    {I_VPCMPUQ, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9379, 231},
    {I_VPCMPUQ, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9388, 231},
    {I_VPCMPUQ, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,B64,0,0}, nasm_bytecodes+9397, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPUW[] = {
    {I_VPCMPUW, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9406, 235},
    {I_VPCMPUW, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9415, 235},
    {I_VPCMPUW, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9424, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCMPW[] = {
    {I_VPCMPW, 4, {KREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9433, 235},
    {I_VPCMPW, 4, {KREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9442, 235},
    {I_VPCMPW, 4, {KREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK,0,0,0,0}, nasm_bytecodes+9451, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMPRESSD[] = {
    {I_VPCOMPRESSD, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+21993, 231},
    {I_VPCOMPRESSD, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+22001, 231},
    {I_VPCOMPRESSD, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+22009, 232},
    {I_VPCOMPRESSD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22017, 231},
    {I_VPCOMPRESSD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22025, 231},
    {I_VPCOMPRESSD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22033, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMPRESSQ[] = {
    {I_VPCOMPRESSQ, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+22041, 231},
    {I_VPCOMPRESSQ, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+22049, 231},
    {I_VPCOMPRESSQ, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+22057, 232},
    {I_VPCOMPRESSQ, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22065, 231},
    {I_VPCOMPRESSQ, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22073, 231},
    {I_VPCOMPRESSQ, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22081, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCONFLICTD[] = {
    {I_VPCONFLICTD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22089, 239},
    {I_VPCONFLICTD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22097, 239},
    {I_VPCONFLICTD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22105, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCONFLICTQ[] = {
    {I_VPCONFLICTQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22113, 239},
    {I_VPCONFLICTQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22121, 239},
    {I_VPCONFLICTQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22129, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMB[] = {
    {I_VPERMB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22137, 241},
    {I_VPERMB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22145, 241},
    {I_VPERMB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22153, 241},
    {I_VPERMB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22161, 241},
    {I_VPERMB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22169, 242},
    {I_VPERMB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22177, 242},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2B[] = {
    {I_VPERMI2B, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22217, 241},
    {I_VPERMI2B, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22225, 241},
    {I_VPERMI2B, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22233, 242},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2D[] = {
    {I_VPERMI2D, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22241, 231},
    {I_VPERMI2D, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22249, 231},
    {I_VPERMI2D, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22257, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2PD[] = {
    {I_VPERMI2PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22265, 231},
    {I_VPERMI2PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22273, 231},
    {I_VPERMI2PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22281, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2PS[] = {
    {I_VPERMI2PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22289, 231},
    {I_VPERMI2PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22297, 231},
    {I_VPERMI2PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22305, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2Q[] = {
    {I_VPERMI2Q, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22313, 231},
    {I_VPERMI2Q, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22321, 231},
    {I_VPERMI2Q, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22329, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMI2W[] = {
    {I_VPERMI2W, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22337, 235},
    {I_VPERMI2W, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22345, 235},
    {I_VPERMI2W, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22353, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2B[] = {
    {I_VPERMT2B, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22553, 241},
    {I_VPERMT2B, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22561, 241},
    {I_VPERMT2B, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22569, 242},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2D[] = {
    {I_VPERMT2D, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22577, 231},
    {I_VPERMT2D, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22585, 231},
    {I_VPERMT2D, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22593, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2PD[] = {
    {I_VPERMT2PD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22601, 231},
    {I_VPERMT2PD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22609, 231},
    {I_VPERMT2PD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22617, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2PS[] = {
    {I_VPERMT2PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22625, 231},
    {I_VPERMT2PS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22633, 231},
    {I_VPERMT2PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+22641, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2Q[] = {
    {I_VPERMT2Q, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22649, 231},
    {I_VPERMT2Q, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22657, 231},
    {I_VPERMT2Q, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22665, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMT2W[] = {
    {I_VPERMT2W, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22673, 235},
    {I_VPERMT2W, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22681, 235},
    {I_VPERMT2W, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22689, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPERMW[] = {
    {I_VPERMW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22697, 235},
    {I_VPERMW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22705, 235},
    {I_VPERMW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22713, 235},
    {I_VPERMW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22721, 235},
    {I_VPERMW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22729, 236},
    {I_VPERMW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22737, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXPANDD[] = {
    {I_VPEXPANDD, 2, {XMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22745, 231},
    {I_VPEXPANDD, 2, {YMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22753, 231},
    {I_VPEXPANDD, 2, {ZMMREG,MEMORY|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22761, 232},
    {I_VPEXPANDD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22745, 231},
    {I_VPEXPANDD, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22753, 231},
    {I_VPEXPANDD, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22761, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXPANDQ[] = {
    {I_VPEXPANDQ, 2, {XMMREG,MEMORY|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22769, 231},
    {I_VPEXPANDQ, 2, {YMMREG,MEMORY|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22777, 231},
    {I_VPEXPANDQ, 2, {ZMMREG,MEMORY|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22785, 232},
    {I_VPEXPANDQ, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22769, 231},
    {I_VPEXPANDQ, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22777, 231},
    {I_VPEXPANDQ, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+22785, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPLZCNTD[] = {
    {I_VPLZCNTD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22793, 239},
    {I_VPLZCNTD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22801, 239},
    {I_VPLZCNTD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+22809, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPLZCNTQ[] = {
    {I_VPLZCNTQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22817, 239},
    {I_VPLZCNTQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22825, 239},
    {I_VPLZCNTQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+22833, 240},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADD52HUQ[] = {
    {I_VPMADD52HUQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22841, 243},
    {I_VPMADD52HUQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22849, 243},
    {I_VPMADD52HUQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22857, 244},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMADD52LUQ[] = {
    {I_VPMADD52LUQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22865, 243},
    {I_VPMADD52LUQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22873, 243},
    {I_VPMADD52LUQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+22881, 244},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXSQ[] = {
    {I_VPMAXSQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23081, 231},
    {I_VPMAXSQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23089, 231},
    {I_VPMAXSQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23097, 231},
    {I_VPMAXSQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23105, 231},
    {I_VPMAXSQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23113, 232},
    {I_VPMAXSQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23121, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMAXUQ[] = {
    {I_VPMAXUQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23273, 231},
    {I_VPMAXUQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23281, 231},
    {I_VPMAXUQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23289, 231},
    {I_VPMAXUQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23297, 231},
    {I_VPMAXUQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23305, 232},
    {I_VPMAXUQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23313, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINSQ[] = {
    {I_VPMINSQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23465, 231},
    {I_VPMINSQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23473, 231},
    {I_VPMINSQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23481, 231},
    {I_VPMINSQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23489, 231},
    {I_VPMINSQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23497, 232},
    {I_VPMINSQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23505, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMINUQ[] = {
    {I_VPMINUQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23657, 231},
    {I_VPMINUQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23665, 231},
    {I_VPMINUQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23673, 231},
    {I_VPMINUQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23681, 231},
    {I_VPMINUQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+23689, 232},
    {I_VPMINUQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+23697, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVB2M[] = {
    {I_VPMOVB2M, 2, {KREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23753, 235},
    {I_VPMOVB2M, 2, {KREG,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23761, 235},
    {I_VPMOVB2M, 2, {KREG,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23769, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVD2M[] = {
    {I_VPMOVD2M, 2, {KREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23777, 233},
    {I_VPMOVD2M, 2, {KREG,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23785, 233},
    {I_VPMOVD2M, 2, {KREG,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23793, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVDB[] = {
    {I_VPMOVDB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23801, 231},
    {I_VPMOVDB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23809, 231},
    {I_VPMOVDB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23817, 232},
    {I_VPMOVDB, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23825, 231},
    {I_VPMOVDB, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23833, 231},
    {I_VPMOVDB, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23841, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVDW[] = {
    {I_VPMOVDW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23849, 231},
    {I_VPMOVDW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23857, 231},
    {I_VPMOVDW, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+23865, 232},
    {I_VPMOVDW, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23873, 231},
    {I_VPMOVDW, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23881, 231},
    {I_VPMOVDW, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+23889, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVM2B[] = {
    {I_VPMOVM2B, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23897, 235},
    {I_VPMOVM2B, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23905, 235},
    {I_VPMOVM2B, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23913, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVM2D[] = {
    {I_VPMOVM2D, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23921, 233},
    {I_VPMOVM2D, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23929, 233},
    {I_VPMOVM2D, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23937, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVM2Q[] = {
    {I_VPMOVM2Q, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23945, 233},
    {I_VPMOVM2Q, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23953, 233},
    {I_VPMOVM2Q, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23961, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVM2W[] = {
    {I_VPMOVM2W, 2, {XMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23969, 235},
    {I_VPMOVM2W, 2, {YMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23977, 235},
    {I_VPMOVM2W, 2, {ZMMREG,KREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23985, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVQ2M[] = {
    {I_VPMOVQ2M, 2, {KREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+23993, 233},
    {I_VPMOVQ2M, 2, {KREG,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+24001, 233},
    {I_VPMOVQ2M, 2, {KREG,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+24009, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVQB[] = {
    {I_VPMOVQB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24017, 231},
    {I_VPMOVQB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24025, 231},
    {I_VPMOVQB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24033, 232},
    {I_VPMOVQB, 2, {MEMORY|BITS16,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24041, 231},
    {I_VPMOVQB, 2, {MEMORY|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24049, 231},
    {I_VPMOVQB, 2, {MEMORY|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24057, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVQD[] = {
    {I_VPMOVQD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24065, 231},
    {I_VPMOVQD, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24073, 231},
    {I_VPMOVQD, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24081, 232},
    {I_VPMOVQD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24089, 231},
    {I_VPMOVQD, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24097, 231},
    {I_VPMOVQD, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24105, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVQW[] = {
    {I_VPMOVQW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24113, 231},
    {I_VPMOVQW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24121, 231},
    {I_VPMOVQW, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24129, 232},
    {I_VPMOVQW, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24137, 231},
    {I_VPMOVQW, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24145, 231},
    {I_VPMOVQW, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24153, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSDB[] = {
    {I_VPMOVSDB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24161, 231},
    {I_VPMOVSDB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24169, 231},
    {I_VPMOVSDB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24177, 232},
    {I_VPMOVSDB, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24185, 231},
    {I_VPMOVSDB, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24193, 231},
    {I_VPMOVSDB, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24201, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSDW[] = {
    {I_VPMOVSDW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24209, 231},
    {I_VPMOVSDW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24217, 231},
    {I_VPMOVSDW, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24225, 232},
    {I_VPMOVSDW, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24233, 231},
    {I_VPMOVSDW, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24241, 231},
    {I_VPMOVSDW, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24249, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSQB[] = {
    {I_VPMOVSQB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24257, 231},
    {I_VPMOVSQB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24265, 231},
    {I_VPMOVSQB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24273, 232},
    {I_VPMOVSQB, 2, {MEMORY|BITS16,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24281, 231},
    {I_VPMOVSQB, 2, {MEMORY|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24289, 231},
    {I_VPMOVSQB, 2, {MEMORY|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24297, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSQD[] = {
    {I_VPMOVSQD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24305, 231},
    {I_VPMOVSQD, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24313, 231},
    {I_VPMOVSQD, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24321, 232},
    {I_VPMOVSQD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24329, 231},
    {I_VPMOVSQD, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24337, 231},
    {I_VPMOVSQD, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24345, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSQW[] = {
    {I_VPMOVSQW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24353, 231},
    {I_VPMOVSQW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24361, 231},
    {I_VPMOVSQW, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24369, 232},
    {I_VPMOVSQW, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24377, 231},
    {I_VPMOVSQW, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24385, 231},
    {I_VPMOVSQW, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24393, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVSWB[] = {
    {I_VPMOVSWB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24401, 235},
    {I_VPMOVSWB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24409, 235},
    {I_VPMOVSWB, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24417, 236},
    {I_VPMOVSWB, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24425, 235},
    {I_VPMOVSWB, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24433, 235},
    {I_VPMOVSWB, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24441, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSDB[] = {
    {I_VPMOVUSDB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24593, 231},
    {I_VPMOVUSDB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24601, 231},
    {I_VPMOVUSDB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24609, 232},
    {I_VPMOVUSDB, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24617, 231},
    {I_VPMOVUSDB, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24625, 231},
    {I_VPMOVUSDB, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24633, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSDW[] = {
    {I_VPMOVUSDW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24641, 231},
    {I_VPMOVUSDW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24649, 231},
    {I_VPMOVUSDW, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24657, 232},
    {I_VPMOVUSDW, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24665, 231},
    {I_VPMOVUSDW, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24673, 231},
    {I_VPMOVUSDW, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24681, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSQB[] = {
    {I_VPMOVUSQB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24689, 231},
    {I_VPMOVUSQB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24697, 231},
    {I_VPMOVUSQB, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24705, 232},
    {I_VPMOVUSQB, 2, {MEMORY|BITS16,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24713, 231},
    {I_VPMOVUSQB, 2, {MEMORY|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24721, 231},
    {I_VPMOVUSQB, 2, {MEMORY|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24729, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSQD[] = {
    {I_VPMOVUSQD, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24737, 231},
    {I_VPMOVUSQD, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24745, 231},
    {I_VPMOVUSQD, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24753, 232},
    {I_VPMOVUSQD, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24761, 231},
    {I_VPMOVUSQD, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24769, 231},
    {I_VPMOVUSQD, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24777, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSQW[] = {
    {I_VPMOVUSQW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24785, 231},
    {I_VPMOVUSQW, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24793, 231},
    {I_VPMOVUSQW, 2, {XMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24801, 232},
    {I_VPMOVUSQW, 2, {MEMORY|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24809, 231},
    {I_VPMOVUSQW, 2, {MEMORY|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24817, 231},
    {I_VPMOVUSQW, 2, {MEMORY|BITS128,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24825, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVUSWB[] = {
    {I_VPMOVUSWB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24833, 235},
    {I_VPMOVUSWB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24841, 235},
    {I_VPMOVUSWB, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24849, 236},
    {I_VPMOVUSWB, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24857, 235},
    {I_VPMOVUSWB, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24865, 235},
    {I_VPMOVUSWB, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24873, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVW2M[] = {
    {I_VPMOVW2M, 2, {KREG,XMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+24881, 235},
    {I_VPMOVW2M, 2, {KREG,YMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+24889, 235},
    {I_VPMOVW2M, 2, {KREG,ZMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+24897, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMOVWB[] = {
    {I_VPMOVWB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24905, 235},
    {I_VPMOVWB, 2, {XMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24913, 235},
    {I_VPMOVWB, 2, {YMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+24921, 236},
    {I_VPMOVWB, 2, {MEMORY|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24929, 235},
    {I_VPMOVWB, 2, {MEMORY|BITS128,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24937, 235},
    {I_VPMOVWB, 2, {MEMORY|BITS256,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+24945, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULLQ[] = {
    {I_VPMULLQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25337, 233},
    {I_VPMULLQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25345, 233},
    {I_VPMULLQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25353, 233},
    {I_VPMULLQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25361, 233},
    {I_VPMULLQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25369, 234},
    {I_VPMULLQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25377, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPMULTISHIFTQB[] = {
    {I_VPMULTISHIFTQB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25433, 241},
    {I_VPMULTISHIFTQB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25441, 241},
    {I_VPMULTISHIFTQB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25449, 241},
    {I_VPMULTISHIFTQB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25457, 241},
    {I_VPMULTISHIFTQB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25465, 242},
    {I_VPMULTISHIFTQB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25473, 242},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPORD[] = {
    {I_VPORD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25529, 231},
    {I_VPORD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25537, 231},
    {I_VPORD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25545, 231},
    {I_VPORD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25553, 231},
    {I_VPORD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25561, 232},
    {I_VPORD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25569, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPORQ[] = {
    {I_VPORQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25577, 231},
    {I_VPORQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25585, 231},
    {I_VPORQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25593, 231},
    {I_VPORQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25601, 231},
    {I_VPORQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25609, 232},
    {I_VPORQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25617, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROLD[] = {
    {I_VPROLD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9775, 231},
    {I_VPROLD, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9784, 231},
    {I_VPROLD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9793, 231},
    {I_VPROLD, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9802, 231},
    {I_VPROLD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9811, 232},
    {I_VPROLD, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9820, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROLQ[] = {
    {I_VPROLQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9829, 231},
    {I_VPROLQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9838, 231},
    {I_VPROLQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9847, 231},
    {I_VPROLQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9856, 231},
    {I_VPROLQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9865, 232},
    {I_VPROLQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9874, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROLVD[] = {
    {I_VPROLVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25625, 231},
    {I_VPROLVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25633, 231},
    {I_VPROLVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25641, 231},
    {I_VPROLVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25649, 231},
    {I_VPROLVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25657, 232},
    {I_VPROLVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25665, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPROLVQ[] = {
    {I_VPROLVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25673, 231},
    {I_VPROLVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25681, 231},
    {I_VPROLVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25689, 231},
    {I_VPROLVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25697, 231},
    {I_VPROLVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25705, 232},
    {I_VPROLVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25713, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPRORD[] = {
    {I_VPRORD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9883, 231},
    {I_VPRORD, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9892, 231},
    {I_VPRORD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9901, 231},
    {I_VPRORD, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9910, 231},
    {I_VPRORD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+9919, 232},
    {I_VPRORD, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9928, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPRORQ[] = {
    {I_VPRORQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9937, 231},
    {I_VPRORQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9946, 231},
    {I_VPRORQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9955, 231},
    {I_VPRORQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9964, 231},
    {I_VPRORQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+9973, 232},
    {I_VPRORQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+9982, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPRORVD[] = {
    {I_VPRORVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25721, 231},
    {I_VPRORVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25729, 231},
    {I_VPRORVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25737, 231},
    {I_VPRORVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25745, 231},
    {I_VPRORVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+25753, 232},
    {I_VPRORVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+25761, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPRORVQ[] = {
    {I_VPRORVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25769, 231},
    {I_VPRORVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25777, 231},
    {I_VPRORVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25785, 231},
    {I_VPRORVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25793, 231},
    {I_VPRORVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+25801, 232},
    {I_VPRORVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+25809, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSCATTERDD[] = {
    {I_VPSCATTERDD, 2, {XMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+9991, 231},
    {I_VPSCATTERDD, 2, {YMEM|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10000, 231},
    {I_VPSCATTERDD, 2, {ZMEM|BITS32,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10009, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSCATTERDQ[] = {
    {I_VPSCATTERDQ, 2, {XMEM|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10018, 231},
    {I_VPSCATTERDQ, 2, {XMEM|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10027, 231},
    {I_VPSCATTERDQ, 2, {YMEM|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10036, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSCATTERQD[] = {
    {I_VPSCATTERQD, 2, {XMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10045, 231},
    {I_VPSCATTERQD, 2, {YMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10054, 231},
    {I_VPSCATTERQD, 2, {ZMEM|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10063, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSCATTERQQ[] = {
    {I_VPSCATTERQQ, 2, {XMEM|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10072, 231},
    {I_VPSCATTERQQ, 2, {YMEM|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10081, 231},
    {I_VPSCATTERQQ, 2, {ZMEM|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+10090, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSLLVW[] = {
    {I_VPSLLVW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26105, 235},
    {I_VPSLLVW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26113, 235},
    {I_VPSLLVW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26121, 235},
    {I_VPSLLVW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26129, 235},
    {I_VPSLLVW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26137, 236},
    {I_VPSLLVW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26145, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAQ[] = {
    {I_VPSRAQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26249, 231},
    {I_VPSRAQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26257, 231},
    {I_VPSRAQ, 3, {YMMREG,YMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26265, 231},
    {I_VPSRAQ, 2, {YMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26273, 231},
    {I_VPSRAQ, 3, {ZMMREG,ZMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26281, 232},
    {I_VPSRAQ, 2, {ZMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26289, 232},
    {I_VPSRAQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10450, 231},
    {I_VPSRAQ, 2, {XMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10459, 231},
    {I_VPSRAQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10468, 231},
    {I_VPSRAQ, 2, {YMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10477, 231},
    {I_VPSRAQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10486, 232},
    {I_VPSRAQ, 2, {ZMMREG,IMMEDIATE|BITS8,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+10495, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAVQ[] = {
    {I_VPSRAVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26345, 231},
    {I_VPSRAVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26353, 231},
    {I_VPSRAVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26361, 231},
    {I_VPSRAVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26369, 231},
    {I_VPSRAVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+26377, 232},
    {I_VPSRAVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+26385, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRAVW[] = {
    {I_VPSRAVW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26393, 235},
    {I_VPSRAVW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26401, 235},
    {I_VPSRAVW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26409, 235},
    {I_VPSRAVW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26417, 235},
    {I_VPSRAVW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26425, 236},
    {I_VPSRAVW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26433, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSRLVW[] = {
    {I_VPSRLVW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26681, 235},
    {I_VPSRLVW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26689, 235},
    {I_VPSRLVW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26697, 235},
    {I_VPSRLVW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26705, 235},
    {I_VPSRLVW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26713, 236},
    {I_VPSRLVW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+26721, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTERNLOGD[] = {
    {I_VPTERNLOGD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+10774, 231},
    {I_VPTERNLOGD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+10783, 231},
    {I_VPTERNLOGD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+10792, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTERNLOGQ[] = {
    {I_VPTERNLOGQ, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+10801, 231},
    {I_VPTERNLOGQ, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+10810, 231},
    {I_VPTERNLOGQ, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+10819, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTMB[] = {
    {I_VPTESTMB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27161, 235},
    {I_VPTESTMB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27169, 235},
    {I_VPTESTMB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27177, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTMD[] = {
    {I_VPTESTMD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27185, 231},
    {I_VPTESTMD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27193, 231},
    {I_VPTESTMD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27201, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTMQ[] = {
    {I_VPTESTMQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27209, 231},
    {I_VPTESTMQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27217, 231},
    {I_VPTESTMQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27225, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTMW[] = {
    {I_VPTESTMW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27233, 235},
    {I_VPTESTMW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27241, 235},
    {I_VPTESTMW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27249, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTNMB[] = {
    {I_VPTESTNMB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27257, 235},
    {I_VPTESTNMB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27265, 235},
    {I_VPTESTNMB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27273, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTNMD[] = {
    {I_VPTESTNMD, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27281, 231},
    {I_VPTESTNMD, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27289, 231},
    {I_VPTESTNMD, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B32,0,0}, nasm_bytecodes+27297, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTNMQ[] = {
    {I_VPTESTNMQ, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27305, 231},
    {I_VPTESTNMQ, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27313, 231},
    {I_VPTESTNMQ, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,B64,0,0}, nasm_bytecodes+27321, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPTESTNMW[] = {
    {I_VPTESTNMW, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27329, 235},
    {I_VPTESTNMW, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27337, 235},
    {I_VPTESTNMW, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+27345, 236},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPXORD[] = {
    {I_VPXORD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27737, 231},
    {I_VPXORD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27745, 231},
    {I_VPXORD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27753, 231},
    {I_VPXORD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27761, 231},
    {I_VPXORD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+27769, 232},
    {I_VPXORD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27777, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPXORQ[] = {
    {I_VPXORQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27785, 231},
    {I_VPXORQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27793, 231},
    {I_VPXORQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27801, 231},
    {I_VPXORQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27809, 231},
    {I_VPXORQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+27817, 232},
    {I_VPXORQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27825, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRANGEPD[] = {
    {I_VRANGEPD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+10828, 233},
    {I_VRANGEPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10837, 233},
    {I_VRANGEPD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+10846, 233},
    {I_VRANGEPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10855, 233},
    {I_VRANGEPD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64|SAE,0,0}, nasm_bytecodes+10864, 234},
    {I_VRANGEPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+10873, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRANGEPS[] = {
    {I_VRANGEPS, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+10882, 233},
    {I_VRANGEPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10891, 233},
    {I_VRANGEPS, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+10900, 233},
    {I_VRANGEPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10909, 233},
    {I_VRANGEPS, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32|SAE,0,0}, nasm_bytecodes+10918, 234},
    {I_VRANGEPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+10927, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRANGESD[] = {
    {I_VRANGESD, 4, {XMMREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+10936, 234},
    {I_VRANGESD, 3, {XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+10945, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRANGESS[] = {
    {I_VRANGESS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+10954, 234},
    {I_VRANGESS, 3, {XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+10963, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP14PD[] = {
    {I_VRCP14PD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27833, 231},
    {I_VRCP14PD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27841, 231},
    {I_VRCP14PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27849, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP14PS[] = {
    {I_VRCP14PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27857, 231},
    {I_VRCP14PS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27865, 231},
    {I_VRCP14PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27873, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP14SD[] = {
    {I_VRCP14SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27881, 232},
    {I_VRCP14SD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27889, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP14SS[] = {
    {I_VRCP14SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27897, 232},
    {I_VRCP14SS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+27905, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP28PD[] = {
    {I_VRCP28PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+27913, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP28PS[] = {
    {I_VRCP28PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+27921, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP28SD[] = {
    {I_VRCP28SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+27929, 237},
    {I_VRCP28SD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+27937, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRCP28SS[] = {
    {I_VRCP28SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+27945, 237},
    {I_VRCP28SS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+27953, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VREDUCEPD[] = {
    {I_VREDUCEPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10972, 233},
    {I_VREDUCEPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+10981, 233},
    {I_VREDUCEPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+10990, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VREDUCEPS[] = {
    {I_VREDUCEPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+10999, 233},
    {I_VREDUCEPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11008, 233},
    {I_VREDUCEPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+11017, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VREDUCESD[] = {
    {I_VREDUCESD, 4, {XMMREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+11026, 234},
    {I_VREDUCESD, 3, {XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+11035, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VREDUCESS[] = {
    {I_VREDUCESS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+11044, 234},
    {I_VREDUCESS, 3, {XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+11053, 234},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRNDSCALEPD[] = {
    {I_VRNDSCALEPD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11062, 231},
    {I_VRNDSCALEPD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11071, 231},
    {I_VRNDSCALEPD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+11080, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRNDSCALEPS[] = {
    {I_VRNDSCALEPS, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11089, 231},
    {I_VRNDSCALEPS, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11098, 231},
    {I_VRNDSCALEPS, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+11107, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRNDSCALESD[] = {
    {I_VRNDSCALESD, 4, {XMMREG,XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+11116, 232},
    {I_VRNDSCALESD, 3, {XMMREG,RM_XMM|BITS64,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+11125, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRNDSCALESS[] = {
    {I_VRNDSCALESS, 4, {XMMREG,XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+11134, 232},
    {I_VRNDSCALESS, 3, {XMMREG,RM_XMM|BITS32,IMMEDIATE|BITS8,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+11143, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT14PD[] = {
    {I_VRSQRT14PD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27961, 231},
    {I_VRSQRT14PD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27969, 231},
    {I_VRSQRT14PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+27977, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT14PS[] = {
    {I_VRSQRT14PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27985, 231},
    {I_VRSQRT14PS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+27993, 231},
    {I_VRSQRT14PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28001, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT14SD[] = {
    {I_VRSQRT14SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28009, 232},
    {I_VRSQRT14SD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28017, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT14SS[] = {
    {I_VRSQRT14SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28025, 232},
    {I_VRSQRT14SS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28033, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT28PD[] = {
    {I_VRSQRT28PD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|SAE,0,0,0}, nasm_bytecodes+28041, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT28PS[] = {
    {I_VRSQRT28PS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|SAE,0,0,0}, nasm_bytecodes+28049, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT28SD[] = {
    {I_VRSQRT28SD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+28057, 237},
    {I_VRSQRT28SD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+28065, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VRSQRT28SS[] = {
    {I_VRSQRT28SS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,SAE,0,0}, nasm_bytecodes+28073, 237},
    {I_VRSQRT28SS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,SAE,0,0,0}, nasm_bytecodes+28081, 237},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCALEFPD[] = {
    {I_VSCALEFPD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28089, 231},
    {I_VSCALEFPD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28097, 231},
    {I_VSCALEFPD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+28105, 231},
    {I_VSCALEFPD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+28113, 231},
    {I_VSCALEFPD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64|ER,0,0}, nasm_bytecodes+28121, 232},
    {I_VSCALEFPD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64|ER,0,0,0}, nasm_bytecodes+28129, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCALEFPS[] = {
    {I_VSCALEFPS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28137, 231},
    {I_VSCALEFPS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28145, 231},
    {I_VSCALEFPS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+28153, 231},
    {I_VSCALEFPS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+28161, 231},
    {I_VSCALEFPS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32|ER,0,0}, nasm_bytecodes+28169, 232},
    {I_VSCALEFPS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32|ER,0,0,0}, nasm_bytecodes+28177, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCALEFSD[] = {
    {I_VSCALEFSD, 3, {XMMREG,XMMREG,RM_XMM|BITS64,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28185, 232},
    {I_VSCALEFSD, 2, {XMMREG,RM_XMM|BITS64,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28193, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCALEFSS[] = {
    {I_VSCALEFSS, 3, {XMMREG,XMMREG,RM_XMM|BITS32,0,0}, {MASK|Z,0,ER,0,0}, nasm_bytecodes+28201, 232},
    {I_VSCALEFSS, 2, {XMMREG,RM_XMM|BITS32,0,0,0}, {MASK|Z,ER,0,0,0}, nasm_bytecodes+28209, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERDPD[] = {
    {I_VSCATTERDPD, 2, {XMEM|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11152, 231},
    {I_VSCATTERDPD, 2, {XMEM|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11161, 231},
    {I_VSCATTERDPD, 2, {YMEM|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11170, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERDPS[] = {
    {I_VSCATTERDPS, 2, {XMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11179, 231},
    {I_VSCATTERDPS, 2, {YMEM|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11188, 231},
    {I_VSCATTERDPS, 2, {ZMEM|BITS32,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11197, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF0DPD[] = {
    {I_VSCATTERPF0DPD, 1, {YMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11206, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF0DPS[] = {
    {I_VSCATTERPF0DPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11215, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF0QPD[] = {
    {I_VSCATTERPF0QPD, 1, {ZMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11224, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF0QPS[] = {
    {I_VSCATTERPF0QPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11233, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF1DPD[] = {
    {I_VSCATTERPF1DPD, 1, {YMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11242, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF1DPS[] = {
    {I_VSCATTERPF1DPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11251, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF1QPD[] = {
    {I_VSCATTERPF1QPD, 1, {ZMEM|BITS64,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11260, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERPF1QPS[] = {
    {I_VSCATTERPF1QPS, 1, {ZMEM|BITS32,0,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11269, 238},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERQPD[] = {
    {I_VSCATTERQPD, 2, {XMEM|BITS64,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11278, 231},
    {I_VSCATTERQPD, 2, {YMEM|BITS64,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11287, 231},
    {I_VSCATTERQPD, 2, {ZMEM|BITS64,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11296, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSCATTERQPS[] = {
    {I_VSCATTERQPS, 2, {XMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11305, 231},
    {I_VSCATTERQPS, 2, {YMEM|BITS32,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11314, 231},
    {I_VSCATTERQPS, 2, {ZMEM|BITS32,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+11323, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFF32X4[] = {
    {I_VSHUFF32X4, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11332, 231},
    {I_VSHUFF32X4, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11341, 231},
    {I_VSHUFF32X4, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11350, 232},
    {I_VSHUFF32X4, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11359, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFF64X2[] = {
    {I_VSHUFF64X2, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11368, 231},
    {I_VSHUFF64X2, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11377, 231},
    {I_VSHUFF64X2, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11386, 232},
    {I_VSHUFF64X2, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11395, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFI32X4[] = {
    {I_VSHUFI32X4, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11404, 231},
    {I_VSHUFI32X4, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11413, 231},
    {I_VSHUFI32X4, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11422, 232},
    {I_VSHUFI32X4, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11431, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_VSHUFI64X2[] = {
    {I_VSHUFI64X2, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11440, 231},
    {I_VSHUFI64X2, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11449, 231},
    {I_VSHUFI64X2, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11458, 232},
    {I_VSHUFI64X2, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11467, 232},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDPKRU[] = {
    {I_RDPKRU, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44906, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRPKRU[] = {
    {I_WRPKRU, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44911, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDPID[] = {
    {I_RDPID, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39153, 245},
    {I_RDPID, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39152, 136},
    {I_RDPID, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39153, 246},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLFLUSHOPT[] = {
    {I_CLFLUSHOPT, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41867, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLWB[] = {
    {I_CLWB, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41873, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCOMMIT[] = {
    {I_PCOMMIT, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41879, 247},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLZERO[] = {
    {I_CLZERO, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41898, 248},
    {I_CLZERO, 1, {REG_AX,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41885, 249},
    {I_CLZERO, 1, {REG_EAX,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41891, 248},
    {I_CLZERO, 1, {REG_RAX,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41897, 250},
    ITEMPLATE_END
};

static const struct itemplate instrux_PTWRITE[] = {
    {I_PTWRITE, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31061, 135},
    {I_PTWRITE, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+31060, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLDEMOTE[] = {
    {I_CLDEMOTE, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41903, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDIRI[] = {
    {I_MOVDIRI, 2, {MEMORY|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39159, 251},
    {I_MOVDIRI, 2, {MEMORY|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39166, 252},
    ITEMPLATE_END
};

static const struct itemplate instrux_MOVDIR64B[] = {
    {I_MOVDIR64B, 2, {REG_GPR|BITS16,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+28729, 245},
    {I_MOVDIR64B, 2, {REG_GPR|BITS32,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+28737, 135},
    {I_MOVDIR64B, 2, {REG_GPR|BITS64,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+11584, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_PCONFIG[] = {
    {I_PCONFIG, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41909, 135},
    {I_PCONFIG, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41909, 274},
    ITEMPLATE_END
};

static const struct itemplate instrux_TPAUSE[] = {
    {I_TPAUSE, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41873, 135},
    {I_TPAUSE, 3, {REG_GPR|BITS32,REG_EDX,REG_EAX,0,0}, NO_DECORATOR, nasm_bytecodes+41873, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_UMONITOR[] = {
    {I_UMONITOR, 1, {REG_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39173, 245},
    {I_UMONITOR, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39180, 135},
    {I_UMONITOR, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+28745, 136},
    ITEMPLATE_END
};

static const struct itemplate instrux_UMWAIT[] = {
    {I_UMWAIT, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41915, 135},
    {I_UMWAIT, 3, {REG_GPR|BITS32,REG_EDX,REG_EAX,0,0}, NO_DECORATOR, nasm_bytecodes+41915, 135},
    ITEMPLATE_END
};

static const struct itemplate instrux_WBNOINVD[] = {
    {I_WBNOINVD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44916, 135},
    {I_WBNOINVD, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44916, 276},
    ITEMPLATE_END
};

static const struct itemplate instrux_GF2P8AFFINEINVQB[] = {
    {I_GF2P8AFFINEINVQB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28753, 253},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGF2P8AFFINEINVQB[] = {
    {I_VGF2P8AFFINEINVQB, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+28761, 254},
    {I_VGF2P8AFFINEINVQB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28769, 254},
    {I_VGF2P8AFFINEINVQB, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+28777, 254},
    {I_VGF2P8AFFINEINVQB, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28785, 254},
    {I_VGF2P8AFFINEINVQB, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11593, 255},
    {I_VGF2P8AFFINEINVQB, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11602, 255},
    {I_VGF2P8AFFINEINVQB, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11611, 255},
    {I_VGF2P8AFFINEINVQB, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11620, 255},
    {I_VGF2P8AFFINEINVQB, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11629, 256},
    {I_VGF2P8AFFINEINVQB, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11638, 256},
    ITEMPLATE_END
};

static const struct itemplate instrux_GF2P8AFFINEQB[] = {
    {I_GF2P8AFFINEQB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28793, 253},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGF2P8AFFINEQB[] = {
    {I_VGF2P8AFFINEQB, 4, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+28801, 254},
    {I_VGF2P8AFFINEQB, 3, {XMM_L16,RM_XMM_L16|BITS128,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28809, 254},
    {I_VGF2P8AFFINEQB, 4, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0}, NO_DECORATOR, nasm_bytecodes+28817, 254},
    {I_VGF2P8AFFINEQB, 3, {YMM_L16,RM_YMM_L16|BITS256,IMMEDIATE|BITS8,0,0}, NO_DECORATOR, nasm_bytecodes+28825, 254},
    {I_VGF2P8AFFINEQB, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11647, 255},
    {I_VGF2P8AFFINEQB, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11656, 255},
    {I_VGF2P8AFFINEQB, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11665, 255},
    {I_VGF2P8AFFINEQB, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11674, 255},
    {I_VGF2P8AFFINEQB, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11683, 256},
    {I_VGF2P8AFFINEQB, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11692, 256},
    ITEMPLATE_END
};

static const struct itemplate instrux_GF2P8MULB[] = {
    {I_GF2P8MULB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+39187, 253},
    ITEMPLATE_END
};

static const struct itemplate instrux_VGF2P8MULB[] = {
    {I_VGF2P8MULB, 3, {XMM_L16,XMM_L16,RM_XMM_L16|BITS128,0,0}, NO_DECORATOR, nasm_bytecodes+39194, 254},
    {I_VGF2P8MULB, 2, {XMM_L16,RM_XMM_L16|BITS128,0,0,0}, NO_DECORATOR, nasm_bytecodes+39201, 254},
    {I_VGF2P8MULB, 3, {YMM_L16,YMM_L16,RM_YMM_L16|BITS256,0,0}, NO_DECORATOR, nasm_bytecodes+39208, 254},
    {I_VGF2P8MULB, 2, {YMM_L16,RM_YMM_L16|BITS256,0,0,0}, NO_DECORATOR, nasm_bytecodes+39215, 254},
    {I_VGF2P8MULB, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28833, 255},
    {I_VGF2P8MULB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28841, 255},
    {I_VGF2P8MULB, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28849, 255},
    {I_VGF2P8MULB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28857, 255},
    {I_VGF2P8MULB, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28865, 256},
    {I_VGF2P8MULB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28873, 256},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMPRESSB[] = {
    {I_VPCOMPRESSB, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28881, 257},
    {I_VPCOMPRESSB, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28889, 257},
    {I_VPCOMPRESSB, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28897, 258},
    {I_VPCOMPRESSB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28905, 257},
    {I_VPCOMPRESSB, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28913, 257},
    {I_VPCOMPRESSB, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28921, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPCOMPRESSW[] = {
    {I_VPCOMPRESSW, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28929, 257},
    {I_VPCOMPRESSW, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28937, 257},
    {I_VPCOMPRESSW, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28945, 258},
    {I_VPCOMPRESSW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28953, 257},
    {I_VPCOMPRESSW, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28961, 257},
    {I_VPCOMPRESSW, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+28969, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXPANDB[] = {
    {I_VPEXPANDB, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28977, 257},
    {I_VPEXPANDB, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28985, 257},
    {I_VPEXPANDB, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+28993, 258},
    {I_VPEXPANDB, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29001, 257},
    {I_VPEXPANDB, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29009, 257},
    {I_VPEXPANDB, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29017, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPEXPANDW[] = {
    {I_VPEXPANDW, 2, {MEMORY|BITS128,XMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29025, 257},
    {I_VPEXPANDW, 2, {MEMORY|BITS256,YMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29033, 257},
    {I_VPEXPANDW, 2, {MEMORY|BITS512,ZMMREG,0,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29041, 258},
    {I_VPEXPANDW, 2, {XMMREG,XMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29049, 257},
    {I_VPEXPANDW, 2, {YMMREG,YMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29057, 257},
    {I_VPEXPANDW, 2, {ZMMREG,ZMMREG,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29065, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDW[] = {
    {I_VPSHLDW, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11701, 257},
    {I_VPSHLDW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11710, 257},
    {I_VPSHLDW, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11719, 257},
    {I_VPSHLDW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11728, 257},
    {I_VPSHLDW, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11737, 258},
    {I_VPSHLDW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11746, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDD[] = {
    {I_VPSHLDD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11755, 257},
    {I_VPSHLDD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11764, 257},
    {I_VPSHLDD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11773, 257},
    {I_VPSHLDD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11782, 257},
    {I_VPSHLDD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11791, 258},
    {I_VPSHLDD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11800, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDQ[] = {
    {I_VPSHLDQ, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11809, 257},
    {I_VPSHLDQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11818, 257},
    {I_VPSHLDQ, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11827, 257},
    {I_VPSHLDQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11836, 257},
    {I_VPSHLDQ, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11845, 258},
    {I_VPSHLDQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11854, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDVW[] = {
    {I_VPSHLDVW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29073, 257},
    {I_VPSHLDVW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29081, 257},
    {I_VPSHLDVW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29089, 257},
    {I_VPSHLDVW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29097, 257},
    {I_VPSHLDVW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29105, 258},
    {I_VPSHLDVW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29113, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDVD[] = {
    {I_VPSHLDVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29121, 257},
    {I_VPSHLDVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29129, 257},
    {I_VPSHLDVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29137, 257},
    {I_VPSHLDVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29145, 257},
    {I_VPSHLDVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29153, 258},
    {I_VPSHLDVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29161, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHLDVQ[] = {
    {I_VPSHLDVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29169, 257},
    {I_VPSHLDVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29177, 257},
    {I_VPSHLDVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29185, 257},
    {I_VPSHLDVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29193, 257},
    {I_VPSHLDVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29201, 258},
    {I_VPSHLDVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29209, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDW[] = {
    {I_VPSHRDW, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11863, 257},
    {I_VPSHRDW, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11872, 257},
    {I_VPSHRDW, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11881, 257},
    {I_VPSHRDW, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11890, 257},
    {I_VPSHRDW, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11899, 258},
    {I_VPSHRDW, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+11908, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDD[] = {
    {I_VPSHRDD, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11917, 257},
    {I_VPSHRDD, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11926, 257},
    {I_VPSHRDD, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11935, 257},
    {I_VPSHRDD, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11944, 257},
    {I_VPSHRDD, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+11953, 258},
    {I_VPSHRDD, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+11962, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDQ[] = {
    {I_VPSHRDQ, 4, {XMMREG,XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11971, 257},
    {I_VPSHRDQ, 3, {XMMREG,RM_XMM|BITS128,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11980, 257},
    {I_VPSHRDQ, 4, {YMMREG,YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+11989, 257},
    {I_VPSHRDQ, 3, {YMMREG,RM_YMM|BITS256,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+11998, 257},
    {I_VPSHRDQ, 4, {ZMMREG,ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+12007, 258},
    {I_VPSHRDQ, 3, {ZMMREG,RM_ZMM|BITS512,IMMEDIATE|BITS8,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+12016, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDVW[] = {
    {I_VPSHRDVW, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29217, 257},
    {I_VPSHRDVW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29225, 257},
    {I_VPSHRDVW, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29233, 257},
    {I_VPSHRDVW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29241, 257},
    {I_VPSHRDVW, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29249, 258},
    {I_VPSHRDVW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29257, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDVD[] = {
    {I_VPSHRDVD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29265, 257},
    {I_VPSHRDVD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29273, 257},
    {I_VPSHRDVD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29281, 257},
    {I_VPSHRDVD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29289, 257},
    {I_VPSHRDVD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29297, 258},
    {I_VPSHRDVD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29305, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHRDVQ[] = {
    {I_VPSHRDVQ, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29313, 257},
    {I_VPSHRDVQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29321, 257},
    {I_VPSHRDVQ, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29329, 257},
    {I_VPSHRDVQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29337, 257},
    {I_VPSHRDVQ, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B64,0,0}, nasm_bytecodes+29345, 258},
    {I_VPSHRDVQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B64,0,0,0}, nasm_bytecodes+29353, 258},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPDPBUSD[] = {
    {I_VPDPBUSD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29361, 259},
    {I_VPDPBUSD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29369, 259},
    {I_VPDPBUSD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29377, 259},
    {I_VPDPBUSD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29385, 259},
    {I_VPDPBUSD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29393, 260},
    {I_VPDPBUSD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29401, 260},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPDPBUSDS[] = {
    {I_VPDPBUSDS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29409, 259},
    {I_VPDPBUSDS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29417, 259},
    {I_VPDPBUSDS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29425, 259},
    {I_VPDPBUSDS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29433, 259},
    {I_VPDPBUSDS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29441, 260},
    {I_VPDPBUSDS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29449, 260},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPDPWSSD[] = {
    {I_VPDPWSSD, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29457, 259},
    {I_VPDPWSSD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29465, 259},
    {I_VPDPWSSD, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29473, 259},
    {I_VPDPWSSD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29481, 259},
    {I_VPDPWSSD, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29489, 260},
    {I_VPDPWSSD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29497, 260},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPDPWSSDS[] = {
    {I_VPDPWSSDS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29505, 259},
    {I_VPDPWSSDS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29513, 259},
    {I_VPDPWSSDS, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29521, 259},
    {I_VPDPWSSDS, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29529, 259},
    {I_VPDPWSSDS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29537, 260},
    {I_VPDPWSSDS, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29545, 260},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPOPCNTB[] = {
    {I_VPOPCNTB, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29553, 261},
    {I_VPOPCNTB, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29561, 261},
    {I_VPOPCNTB, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29569, 262},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPOPCNTW[] = {
    {I_VPOPCNTW, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29577, 261},
    {I_VPOPCNTW, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29585, 261},
    {I_VPOPCNTW, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29593, 262},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPOPCNTD[] = {
    {I_VPOPCNTD, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29601, 263},
    {I_VPOPCNTD, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29609, 263},
    {I_VPOPCNTD, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29617, 264},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPOPCNTQ[] = {
    {I_VPOPCNTQ, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29625, 263},
    {I_VPOPCNTQ, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29633, 263},
    {I_VPOPCNTQ, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29641, 264},
    ITEMPLATE_END
};

static const struct itemplate instrux_VPSHUFBITQMB[] = {
    {I_VPSHUFBITQMB, 3, {KREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29649, 261},
    {I_VPSHUFBITQMB, 3, {KREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29657, 261},
    {I_VPSHUFBITQMB, 3, {KREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK,0,0,0,0}, nasm_bytecodes+29665, 262},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4FMADDPS[] = {
    {I_V4FMADDPS, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29673, 265},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4FNMADDPS[] = {
    {I_V4FNMADDPS, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29681, 265},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4FMADDSS[] = {
    {I_V4FMADDSS, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29689, 265},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4FNMADDSS[] = {
    {I_V4FNMADDSS, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29697, 265},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4DPWSSDS[] = {
    {I_V4DPWSSDS, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29705, 266},
    ITEMPLATE_END
};

static const struct itemplate instrux_V4DPWSSD[] = {
    {I_V4DPWSSD, 3, {ZMM_L16,ZMM_L16|RS4,MEMORY,0,0}, {MASK|Z,0,0,0,0}, nasm_bytecodes+29713, 266},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENCLS[] = {
    {I_ENCLS, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41921, 267},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENCLU[] = {
    {I_ENCLU, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41927, 267},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENCLV[] = {
    {I_ENCLV, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41933, 267},
    ITEMPLATE_END
};

static const struct itemplate instrux_CLRSSBSY[] = {
    {I_CLRSSBSY, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39181, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENDBR32[] = {
    {I_ENDBR32, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41939, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENDBR64[] = {
    {I_ENDBR64, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41945, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_INCSSPD[] = {
    {I_INCSSPD, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39222, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_INCSSPQ[] = {
    {I_INCSSPQ, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39229, 269},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDSSPD[] = {
    {I_RDSSPD, 1, {REG_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39236, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_RDSSPQ[] = {
    {I_RDSSPQ, 1, {REG_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39243, 269},
    ITEMPLATE_END
};

static const struct itemplate instrux_RSTORSSP[] = {
    {I_RSTORSSP, 1, {MEMORY|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41951, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_SAVEPREVSSP[] = {
    {I_SAVEPREVSSP, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41957, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_SETSSBSY[] = {
    {I_SETSSBSY, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41963, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRUSSD[] = {
    {I_WRUSSD, 2, {MEMORY|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+29721, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRUSSQ[] = {
    {I_WRUSSQ, 2, {MEMORY|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+29729, 269},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRSSD[] = {
    {I_WRSSD, 2, {MEMORY|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+39250, 268},
    ITEMPLATE_END
};

static const struct itemplate instrux_WRSSQ[] = {
    {I_WRSSQ, 2, {MEMORY|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+39257, 269},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENQCMD[] = {
    {I_ENQCMD, 2, {REG_GPR|BITS16,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29737, 270},
    {I_ENQCMD, 2, {REG_GPR|BITS32,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29737, 270},
    {I_ENQCMD, 2, {REG_GPR|BITS32,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29745, 270},
    {I_ENQCMD, 2, {REG_GPR|BITS64,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29753, 271},
    ITEMPLATE_END
};

static const struct itemplate instrux_ENQCMDS[] = {
    {I_ENQCMDS, 2, {REG_GPR|BITS16,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29761, 272},
    {I_ENQCMDS, 2, {REG_GPR|BITS32,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29761, 272},
    {I_ENQCMDS, 2, {REG_GPR|BITS32,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29769, 272},
    {I_ENQCMDS, 2, {REG_GPR|BITS64,MEMORY|BITS512,0,0,0}, NO_DECORATOR, nasm_bytecodes+29777, 273},
    ITEMPLATE_END
};

static const struct itemplate instrux_SERIALIZE[] = {
    {I_SERIALIZE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41969, 275},
    ITEMPLATE_END
};

static const struct itemplate instrux_XRESLDTRK[] = {
    {I_XRESLDTRK, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41975, 277},
    ITEMPLATE_END
};

static const struct itemplate instrux_XSUSLDTRK[] = {
    {I_XSUSLDTRK, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41981, 277},
    ITEMPLATE_END
};

static const struct itemplate instrux_VCVTNE2PS2BF16[] = {
    {I_VCVTNE2PS2BF16, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29785, 278},
    {I_VCVTNE2PS2BF16, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29793, 278},
    {I_VCVTNE2PS2BF16, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29801, 278},
    {I_VCVTNE2PS2BF16, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29809, 278},
    {I_VCVTNE2PS2BF16, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29817, 278},
    {I_VCVTNE2PS2BF16, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29825, 278},
    {I_VCVTNE2PS2BF16, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29833, 278},
    {I_VCVTNE2PS2BF16, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29841, 278},
    {I_VCVTNE2PS2BF16, 3, {YMMREG,YMMREG,RM_YMM|BITS256,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29849, 278},
    {I_VCVTNE2PS2BF16, 2, {YMMREG,RM_YMM|BITS256,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29857, 278},
    {I_VCVTNE2PS2BF16, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS512,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29865, 278},
    {I_VCVTNE2PS2BF16, 2, {ZMMREG,RM_ZMM|BITS512,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29873, 278},
    ITEMPLATE_END
};

static const struct itemplate instrux_VDPBF16PS[] = {
    {I_VDPBF16PS, 3, {XMMREG,XMMREG,RM_XMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29881, 278},
    {I_VDPBF16PS, 2, {XMMREG,RM_XMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29889, 278},
    {I_VDPBF16PS, 3, {YMMREG,YMMREG,RM_YMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29897, 278},
    {I_VDPBF16PS, 2, {YMMREG,RM_YMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29905, 278},
    {I_VDPBF16PS, 3, {ZMMREG,ZMMREG,RM_ZMM|BITS128,0,0}, {MASK|Z,0,B32,0,0}, nasm_bytecodes+29913, 278},
    {I_VDPBF16PS, 2, {ZMMREG,RM_ZMM|BITS128,0,0,0}, {MASK|Z,B32,0,0,0}, nasm_bytecodes+29921, 278},
    ITEMPLATE_END
};

static const struct itemplate instrux_VP2INTERSECTD[] = {
    {I_VP2INTERSECTD, 3, {KREG|RS2,XMMREG,RM_XMM|BITS128,0,0}, {0,0,B32,0,0}, nasm_bytecodes+29929, 278},
    {I_VP2INTERSECTD, 3, {KREG|RS2,YMMREG,RM_YMM|BITS128,0,0}, {0,0,B32,0,0}, nasm_bytecodes+29937, 278},
    {I_VP2INTERSECTD, 3, {KREG|RS2,ZMMREG,RM_ZMM|BITS128,0,0}, {0,0,B32,0,0}, nasm_bytecodes+29945, 278},
    ITEMPLATE_END
};

static const struct itemplate instrux_LDTILECFG[] = {
    {I_LDTILECFG, 1, {MEMORY|BITS512,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39264, 279},
    ITEMPLATE_END
};

static const struct itemplate instrux_STTILECFG[] = {
    {I_STTILECFG, 1, {MEMORY|BITS512,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39271, 279},
    ITEMPLATE_END
};

static const struct itemplate instrux_TDPBF16PS[] = {
    {I_TDPBF16PS, 3, {TMMREG,TMMREG,TMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+39278, 280},
    ITEMPLATE_END
};

static const struct itemplate instrux_TDPBSSD[] = {
    {I_TDPBSSD, 3, {TMMREG,TMMREG,TMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+39285, 281},
    ITEMPLATE_END
};

static const struct itemplate instrux_TDPBSUD[] = {
    {I_TDPBSUD, 3, {TMMREG,TMMREG,TMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+39292, 281},
    ITEMPLATE_END
};

static const struct itemplate instrux_TDPBUSD[] = {
    {I_TDPBUSD, 3, {TMMREG,TMMREG,TMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+39299, 281},
    ITEMPLATE_END
};

static const struct itemplate instrux_TDPBUUD[] = {
    {I_TDPBUUD, 3, {TMMREG,TMMREG,TMMREG,0,0}, NO_DECORATOR, nasm_bytecodes+39306, 281},
    ITEMPLATE_END
};

static const struct itemplate instrux_TILELOADD[] = {
    {I_TILELOADD, 2, {TMMREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39313, 282},
    ITEMPLATE_END
};

static const struct itemplate instrux_TILELOADDT1[] = {
    {I_TILELOADDT1, 2, {TMMREG,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+39320, 282},
    ITEMPLATE_END
};

static const struct itemplate instrux_TILERELEASE[] = {
    {I_TILERELEASE, 0, {0,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+39327, 283},
    ITEMPLATE_END
};

static const struct itemplate instrux_TILESTORED[] = {
    {I_TILESTORED, 2, {MEMORY,TMMREG,0,0,0}, NO_DECORATOR, nasm_bytecodes+39334, 282},
    ITEMPLATE_END
};

static const struct itemplate instrux_TILEZERO[] = {
    {I_TILEZERO, 1, {TMMREG,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+29953, 283},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP0[] = {
    {I_HINT_NOP0, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41987, 284},
    {I_HINT_NOP0, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41993, 284},
    {I_HINT_NOP0, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+41999, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP1[] = {
    {I_HINT_NOP1, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42005, 284},
    {I_HINT_NOP1, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42011, 284},
    {I_HINT_NOP1, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42017, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP2[] = {
    {I_HINT_NOP2, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42023, 284},
    {I_HINT_NOP2, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42029, 284},
    {I_HINT_NOP2, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42035, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP3[] = {
    {I_HINT_NOP3, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42041, 284},
    {I_HINT_NOP3, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42047, 284},
    {I_HINT_NOP3, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42053, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP4[] = {
    {I_HINT_NOP4, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42059, 284},
    {I_HINT_NOP4, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42065, 284},
    {I_HINT_NOP4, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42071, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP5[] = {
    {I_HINT_NOP5, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42077, 284},
    {I_HINT_NOP5, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42083, 284},
    {I_HINT_NOP5, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42089, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP6[] = {
    {I_HINT_NOP6, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42095, 284},
    {I_HINT_NOP6, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42101, 284},
    {I_HINT_NOP6, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42107, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP7[] = {
    {I_HINT_NOP7, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42113, 284},
    {I_HINT_NOP7, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42119, 284},
    {I_HINT_NOP7, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42125, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP8[] = {
    {I_HINT_NOP8, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42131, 284},
    {I_HINT_NOP8, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42137, 284},
    {I_HINT_NOP8, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42143, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP9[] = {
    {I_HINT_NOP9, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42149, 284},
    {I_HINT_NOP9, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42155, 284},
    {I_HINT_NOP9, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42161, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP10[] = {
    {I_HINT_NOP10, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42167, 284},
    {I_HINT_NOP10, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42173, 284},
    {I_HINT_NOP10, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42179, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP11[] = {
    {I_HINT_NOP11, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42185, 284},
    {I_HINT_NOP11, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42191, 284},
    {I_HINT_NOP11, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42197, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP12[] = {
    {I_HINT_NOP12, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42203, 284},
    {I_HINT_NOP12, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42209, 284},
    {I_HINT_NOP12, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42215, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP13[] = {
    {I_HINT_NOP13, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42221, 284},
    {I_HINT_NOP13, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42227, 284},
    {I_HINT_NOP13, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42233, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP14[] = {
    {I_HINT_NOP14, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42239, 284},
    {I_HINT_NOP14, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42245, 284},
    {I_HINT_NOP14, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42251, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP15[] = {
    {I_HINT_NOP15, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42257, 284},
    {I_HINT_NOP15, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42263, 284},
    {I_HINT_NOP15, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42269, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP16[] = {
    {I_HINT_NOP16, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42275, 284},
    {I_HINT_NOP16, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42281, 284},
    {I_HINT_NOP16, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42287, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP17[] = {
    {I_HINT_NOP17, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42293, 284},
    {I_HINT_NOP17, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42299, 284},
    {I_HINT_NOP17, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42305, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP18[] = {
    {I_HINT_NOP18, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42311, 284},
    {I_HINT_NOP18, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42317, 284},
    {I_HINT_NOP18, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42323, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP19[] = {
    {I_HINT_NOP19, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42329, 284},
    {I_HINT_NOP19, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42335, 284},
    {I_HINT_NOP19, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42341, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP20[] = {
    {I_HINT_NOP20, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42347, 284},
    {I_HINT_NOP20, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42353, 284},
    {I_HINT_NOP20, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42359, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP21[] = {
    {I_HINT_NOP21, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42365, 284},
    {I_HINT_NOP21, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42371, 284},
    {I_HINT_NOP21, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42377, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP22[] = {
    {I_HINT_NOP22, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42383, 284},
    {I_HINT_NOP22, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42389, 284},
    {I_HINT_NOP22, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42395, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP23[] = {
    {I_HINT_NOP23, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42401, 284},
    {I_HINT_NOP23, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42407, 284},
    {I_HINT_NOP23, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42413, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP24[] = {
    {I_HINT_NOP24, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42419, 284},
    {I_HINT_NOP24, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42425, 284},
    {I_HINT_NOP24, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42431, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP25[] = {
    {I_HINT_NOP25, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42437, 284},
    {I_HINT_NOP25, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42443, 284},
    {I_HINT_NOP25, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42449, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP26[] = {
    {I_HINT_NOP26, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42455, 284},
    {I_HINT_NOP26, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42461, 284},
    {I_HINT_NOP26, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42467, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP27[] = {
    {I_HINT_NOP27, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42473, 284},
    {I_HINT_NOP27, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42479, 284},
    {I_HINT_NOP27, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42485, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP28[] = {
    {I_HINT_NOP28, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42491, 284},
    {I_HINT_NOP28, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42497, 284},
    {I_HINT_NOP28, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42503, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP29[] = {
    {I_HINT_NOP29, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42509, 284},
    {I_HINT_NOP29, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42515, 284},
    {I_HINT_NOP29, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42521, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP30[] = {
    {I_HINT_NOP30, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42527, 284},
    {I_HINT_NOP30, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42533, 284},
    {I_HINT_NOP30, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42539, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP31[] = {
    {I_HINT_NOP31, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42545, 284},
    {I_HINT_NOP31, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42551, 284},
    {I_HINT_NOP31, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42557, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP32[] = {
    {I_HINT_NOP32, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42563, 284},
    {I_HINT_NOP32, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42569, 284},
    {I_HINT_NOP32, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42575, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP33[] = {
    {I_HINT_NOP33, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42581, 284},
    {I_HINT_NOP33, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42587, 284},
    {I_HINT_NOP33, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42593, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP34[] = {
    {I_HINT_NOP34, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42599, 284},
    {I_HINT_NOP34, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42605, 284},
    {I_HINT_NOP34, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42611, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP35[] = {
    {I_HINT_NOP35, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42617, 284},
    {I_HINT_NOP35, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42623, 284},
    {I_HINT_NOP35, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42629, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP36[] = {
    {I_HINT_NOP36, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42635, 284},
    {I_HINT_NOP36, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42641, 284},
    {I_HINT_NOP36, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42647, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP37[] = {
    {I_HINT_NOP37, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42653, 284},
    {I_HINT_NOP37, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42659, 284},
    {I_HINT_NOP37, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42665, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP38[] = {
    {I_HINT_NOP38, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42671, 284},
    {I_HINT_NOP38, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42677, 284},
    {I_HINT_NOP38, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42683, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP39[] = {
    {I_HINT_NOP39, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42689, 284},
    {I_HINT_NOP39, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42695, 284},
    {I_HINT_NOP39, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42701, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP40[] = {
    {I_HINT_NOP40, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42707, 284},
    {I_HINT_NOP40, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42713, 284},
    {I_HINT_NOP40, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42719, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP41[] = {
    {I_HINT_NOP41, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42725, 284},
    {I_HINT_NOP41, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42731, 284},
    {I_HINT_NOP41, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42737, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP42[] = {
    {I_HINT_NOP42, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42743, 284},
    {I_HINT_NOP42, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42749, 284},
    {I_HINT_NOP42, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42755, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP43[] = {
    {I_HINT_NOP43, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42761, 284},
    {I_HINT_NOP43, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42767, 284},
    {I_HINT_NOP43, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42773, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP44[] = {
    {I_HINT_NOP44, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42779, 284},
    {I_HINT_NOP44, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42785, 284},
    {I_HINT_NOP44, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42791, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP45[] = {
    {I_HINT_NOP45, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42797, 284},
    {I_HINT_NOP45, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42803, 284},
    {I_HINT_NOP45, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42809, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP46[] = {
    {I_HINT_NOP46, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42815, 284},
    {I_HINT_NOP46, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42821, 284},
    {I_HINT_NOP46, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42827, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP47[] = {
    {I_HINT_NOP47, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42833, 284},
    {I_HINT_NOP47, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42839, 284},
    {I_HINT_NOP47, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42845, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP48[] = {
    {I_HINT_NOP48, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42851, 284},
    {I_HINT_NOP48, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42857, 284},
    {I_HINT_NOP48, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42863, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP49[] = {
    {I_HINT_NOP49, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42869, 284},
    {I_HINT_NOP49, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42875, 284},
    {I_HINT_NOP49, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42881, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP50[] = {
    {I_HINT_NOP50, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42887, 284},
    {I_HINT_NOP50, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42893, 284},
    {I_HINT_NOP50, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42899, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP51[] = {
    {I_HINT_NOP51, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42905, 284},
    {I_HINT_NOP51, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42911, 284},
    {I_HINT_NOP51, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42917, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP52[] = {
    {I_HINT_NOP52, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42923, 284},
    {I_HINT_NOP52, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42929, 284},
    {I_HINT_NOP52, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42935, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP53[] = {
    {I_HINT_NOP53, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42941, 284},
    {I_HINT_NOP53, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42947, 284},
    {I_HINT_NOP53, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42953, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP54[] = {
    {I_HINT_NOP54, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42959, 284},
    {I_HINT_NOP54, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42965, 284},
    {I_HINT_NOP54, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42971, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP55[] = {
    {I_HINT_NOP55, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42977, 284},
    {I_HINT_NOP55, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42983, 284},
    {I_HINT_NOP55, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42989, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP56[] = {
    {I_HINT_NOP56, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40037, 284},
    {I_HINT_NOP56, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40043, 284},
    {I_HINT_NOP56, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40049, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP57[] = {
    {I_HINT_NOP57, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+42995, 284},
    {I_HINT_NOP57, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43001, 284},
    {I_HINT_NOP57, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43007, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP58[] = {
    {I_HINT_NOP58, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43013, 284},
    {I_HINT_NOP58, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43019, 284},
    {I_HINT_NOP58, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43025, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP59[] = {
    {I_HINT_NOP59, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43031, 284},
    {I_HINT_NOP59, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43037, 284},
    {I_HINT_NOP59, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43043, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP60[] = {
    {I_HINT_NOP60, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43049, 284},
    {I_HINT_NOP60, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43055, 284},
    {I_HINT_NOP60, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43061, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP61[] = {
    {I_HINT_NOP61, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43067, 284},
    {I_HINT_NOP61, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43073, 284},
    {I_HINT_NOP61, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43079, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP62[] = {
    {I_HINT_NOP62, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43085, 284},
    {I_HINT_NOP62, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43091, 284},
    {I_HINT_NOP62, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43097, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_HINT_NOP63[] = {
    {I_HINT_NOP63, 1, {RM_GPR|BITS16,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43103, 284},
    {I_HINT_NOP63, 1, {RM_GPR|BITS32,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43109, 284},
    {I_HINT_NOP63, 1, {RM_GPR|BITS64,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+43115, 285},
    ITEMPLATE_END
};

static const struct itemplate instrux_CMOVcc[] = {
    {I_CMOVcc, 2, {REG_GPR|BITS16,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30941, 121},
    {I_CMOVcc, 2, {REG_GPR|BITS16,REG_GPR|BITS16,0,0,0}, NO_DECORATOR, nasm_bytecodes+30941, 89},
    {I_CMOVcc, 2, {REG_GPR|BITS32,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30948, 121},
    {I_CMOVcc, 2, {REG_GPR|BITS32,REG_GPR|BITS32,0,0,0}, NO_DECORATOR, nasm_bytecodes+30948, 89},
    {I_CMOVcc, 2, {REG_GPR|BITS64,MEMORY,0,0,0}, NO_DECORATOR, nasm_bytecodes+30955, 10},
    {I_CMOVcc, 2, {REG_GPR|BITS64,REG_GPR|BITS64,0,0,0}, NO_DECORATOR, nasm_bytecodes+30955, 7},
    ITEMPLATE_END
};

static const struct itemplate instrux_Jcc[] = {
    {I_Jcc, 1, {IMMEDIATE|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30962, 122},
    {I_Jcc, 1, {IMMEDIATE|BITS16|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30969, 23},
    {I_Jcc, 1, {IMMEDIATE|BITS32|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30976, 23},
    {I_Jcc, 1, {IMMEDIATE|BITS64|NEAR,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30983, 24},
    {I_Jcc, 1, {IMMEDIATE|SHORT,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44802, 21},
    {I_Jcc, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44801, 21},
    {I_Jcc, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30984, 122},
    {I_Jcc, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+30990, 21},
    {I_Jcc, 1, {IMMEDIATE,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+44802, 21},
    ITEMPLATE_END
};

static const struct itemplate instrux_SETcc[] = {
    {I_SETcc, 1, {MEMORY,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40589, 53},
    {I_SETcc, 1, {REG_GPR|BITS8,0,0,0,0}, NO_DECORATOR, nasm_bytecodes+40589, 5},
    ITEMPLATE_END
};

const struct itemplate * const nasm_instructions[] = {
    instrux_DB,
    instrux_DW,
    instrux_DD,
    instrux_DQ,
    instrux_DT,
    instrux_DO,
    instrux_DY,
    instrux_DZ,
    instrux_RESB,
    instrux_RESW,
    instrux_RESD,
    instrux_RESQ,
    instrux_REST,
    instrux_RESO,
    instrux_RESY,
    instrux_RESZ,
    instrux_INCBIN,
    instrux_AAA,
    instrux_AAD,
    instrux_AAM,
    instrux_AAS,
    instrux_ADC,
    instrux_ADD,
    instrux_AND,
    instrux_ARPL,
    instrux_BB0_RESET,
    instrux_BB1_RESET,
    instrux_BOUND,
    instrux_BSF,
    instrux_BSR,
    instrux_BSWAP,
    instrux_BT,
    instrux_BTC,
    instrux_BTR,
    instrux_BTS,
    instrux_CALL,
    instrux_CBW,
    instrux_CDQ,
    instrux_CDQE,
    instrux_CLC,
    instrux_CLD,
    instrux_CLI,
    instrux_CLTS,
    instrux_CMC,
    instrux_CMP,
    instrux_CMPSB,
    instrux_CMPSD,
    instrux_CMPSQ,
    instrux_CMPSW,
    instrux_CMPXCHG,
    instrux_CMPXCHG486,
    instrux_CMPXCHG8B,
    instrux_CMPXCHG16B,
    instrux_CPUID,
    instrux_CPU_READ,
    instrux_CPU_WRITE,
    instrux_CQO,
    instrux_CWD,
    instrux_CWDE,
    instrux_DAA,
    instrux_DAS,
    instrux_DEC,
    instrux_DIV,
    instrux_DMINT,
    instrux_EMMS,
    instrux_ENTER,
    instrux_EQU,
    instrux_F2XM1,
    instrux_FABS,
    instrux_FADD,
    instrux_FADDP,
    instrux_FBLD,
    instrux_FBSTP,
    instrux_FCHS,
    instrux_FCLEX,
    instrux_FCMOVB,
    instrux_FCMOVBE,
    instrux_FCMOVE,
    instrux_FCMOVNB,
    instrux_FCMOVNBE,
    instrux_FCMOVNE,
    instrux_FCMOVNU,
    instrux_FCMOVU,
    instrux_FCOM,
    instrux_FCOMI,
    instrux_FCOMIP,
    instrux_FCOMP,
    instrux_FCOMPP,
    instrux_FCOS,
    instrux_FDECSTP,
    instrux_FDISI,
    instrux_FDIV,
    instrux_FDIVP,
    instrux_FDIVR,
    instrux_FDIVRP,
    instrux_FEMMS,
    instrux_FENI,
    instrux_FFREE,
    instrux_FFREEP,
    instrux_FIADD,
    instrux_FICOM,
    instrux_FICOMP,
    instrux_FIDIV,
    instrux_FIDIVR,
    instrux_FILD,
    instrux_FIMUL,
    instrux_FINCSTP,
    instrux_FINIT,
    instrux_FIST,
    instrux_FISTP,
    instrux_FISTTP,
    instrux_FISUB,
    instrux_FISUBR,
    instrux_FLD,
    instrux_FLD1,
    instrux_FLDCW,
    instrux_FLDENV,
    instrux_FLDL2E,
    instrux_FLDL2T,
    instrux_FLDLG2,
    instrux_FLDLN2,
    instrux_FLDPI,
    instrux_FLDZ,
    instrux_FMUL,
    instrux_FMULP,
    instrux_FNCLEX,
    instrux_FNDISI,
    instrux_FNENI,
    instrux_FNINIT,
    instrux_FNOP,
    instrux_FNSAVE,
    instrux_FNSTCW,
    instrux_FNSTENV,
    instrux_FNSTSW,
    instrux_FPATAN,
    instrux_FPREM,
    instrux_FPREM1,
    instrux_FPTAN,
    instrux_FRNDINT,
    instrux_FRSTOR,
    instrux_FSAVE,
    instrux_FSCALE,
    instrux_FSETPM,
    instrux_FSIN,
    instrux_FSINCOS,
    instrux_FSQRT,
    instrux_FST,
    instrux_FSTCW,
    instrux_FSTENV,
    instrux_FSTP,
    instrux_FSTSW,
    instrux_FSUB,
    instrux_FSUBP,
    instrux_FSUBR,
    instrux_FSUBRP,
    instrux_FTST,
    instrux_FUCOM,
    instrux_FUCOMI,
    instrux_FUCOMIP,
    instrux_FUCOMP,
    instrux_FUCOMPP,
    instrux_FXAM,
    instrux_FXCH,
    instrux_FXTRACT,
    instrux_FYL2X,
    instrux_FYL2XP1,
    instrux_HLT,
    instrux_IBTS,
    instrux_ICEBP,
    instrux_IDIV,
    instrux_IMUL,
    instrux_IN,
    instrux_INC,
    instrux_INSB,
    instrux_INSD,
    instrux_INSW,
    instrux_INT,
    instrux_INT01,
    instrux_INT1,
    instrux_INT03,
    instrux_INT3,
    instrux_INTO,
    instrux_INVD,
    instrux_INVPCID,
    instrux_INVLPG,
    instrux_INVLPGA,
    instrux_IRET,
    instrux_IRETD,
    instrux_IRETQ,
    instrux_IRETW,
    instrux_JCXZ,
    instrux_JECXZ,
    instrux_JRCXZ,
    instrux_JMP,
    instrux_JMPE,
    instrux_LAHF,
    instrux_LAR,
    instrux_LDS,
    instrux_LEA,
    instrux_LEAVE,
    instrux_LES,
    instrux_LFENCE,
    instrux_LFS,
    instrux_LGDT,
    instrux_LGS,
    instrux_LIDT,
    instrux_LLDT,
    instrux_LMSW,
    instrux_LOADALL,
    instrux_LOADALL286,
    instrux_LODSB,
    instrux_LODSD,
    instrux_LODSQ,
    instrux_LODSW,
    instrux_LOOP,
    instrux_LOOPE,
    instrux_LOOPNE,
    instrux_LOOPNZ,
    instrux_LOOPZ,
    instrux_LSL,
    instrux_LSS,
    instrux_LTR,
    instrux_MFENCE,
    instrux_MONITOR,
    instrux_MONITORX,
    instrux_MOV,
    instrux_MOVD,
    instrux_MOVQ,
    instrux_MOVSB,
    instrux_MOVSD,
    instrux_MOVSQ,
    instrux_MOVSW,
    instrux_MOVSX,
    instrux_MOVSXD,
    instrux_MOVZX,
    instrux_MUL,
    instrux_MWAIT,
    instrux_MWAITX,
    instrux_NEG,
    instrux_NOP,
    instrux_NOT,
    instrux_OR,
    instrux_OUT,
    instrux_OUTSB,
    instrux_OUTSD,
    instrux_OUTSW,
    instrux_PACKSSDW,
    instrux_PACKSSWB,
    instrux_PACKUSWB,
    instrux_PADDB,
    instrux_PADDD,
    instrux_PADDSB,
    instrux_PADDSIW,
    instrux_PADDSW,
    instrux_PADDUSB,
    instrux_PADDUSW,
    instrux_PADDW,
    instrux_PAND,
    instrux_PANDN,
    instrux_PAUSE,
    instrux_PAVEB,
    instrux_PAVGUSB,
    instrux_PCMPEQB,
    instrux_PCMPEQD,
    instrux_PCMPEQW,
    instrux_PCMPGTB,
    instrux_PCMPGTD,
    instrux_PCMPGTW,
    instrux_PDISTIB,
    instrux_PF2ID,
    instrux_PFACC,
    instrux_PFADD,
    instrux_PFCMPEQ,
    instrux_PFCMPGE,
    instrux_PFCMPGT,
    instrux_PFMAX,
    instrux_PFMIN,
    instrux_PFMUL,
    instrux_PFRCP,
    instrux_PFRCPIT1,
    instrux_PFRCPIT2,
    instrux_PFRSQIT1,
    instrux_PFRSQRT,
    instrux_PFSUB,
    instrux_PFSUBR,
    instrux_PI2FD,
    instrux_PMACHRIW,
    instrux_PMADDWD,
    instrux_PMAGW,
    instrux_PMULHRIW,
    instrux_PMULHRWA,
    instrux_PMULHRWC,
    instrux_PMULHW,
    instrux_PMULLW,
    instrux_PMVGEZB,
    instrux_PMVLZB,
    instrux_PMVNZB,
    instrux_PMVZB,
    instrux_POP,
    instrux_POPA,
    instrux_POPAD,
    instrux_POPAW,
    instrux_POPF,
    instrux_POPFD,
    instrux_POPFQ,
    instrux_POPFW,
    instrux_POR,
    instrux_PREFETCH,
    instrux_PREFETCHW,
    instrux_PSLLD,
    instrux_PSLLQ,
    instrux_PSLLW,
    instrux_PSRAD,
    instrux_PSRAW,
    instrux_PSRLD,
    instrux_PSRLQ,
    instrux_PSRLW,
    instrux_PSUBB,
    instrux_PSUBD,
    instrux_PSUBSB,
    instrux_PSUBSIW,
    instrux_PSUBSW,
    instrux_PSUBUSB,
    instrux_PSUBUSW,
    instrux_PSUBW,
    instrux_PUNPCKHBW,
    instrux_PUNPCKHDQ,
    instrux_PUNPCKHWD,
    instrux_PUNPCKLBW,
    instrux_PUNPCKLDQ,
    instrux_PUNPCKLWD,
    instrux_PUSH,
    instrux_PUSHA,
    instrux_PUSHAD,
    instrux_PUSHAW,
    instrux_PUSHF,
    instrux_PUSHFD,
    instrux_PUSHFQ,
    instrux_PUSHFW,
    instrux_PXOR,
    instrux_RCL,
    instrux_RCR,
    instrux_RDSHR,
    instrux_RDMSR,
    instrux_RDPMC,
    instrux_RDTSC,
    instrux_RDTSCP,
    instrux_RET,
    instrux_RETF,
    instrux_RETN,
    instrux_RETW,
    instrux_RETFW,
    instrux_RETNW,
    instrux_RETD,
    instrux_RETFD,
    instrux_RETND,
    instrux_RETQ,
    instrux_RETFQ,
    instrux_RETNQ,
    instrux_ROL,
    instrux_ROR,
    instrux_RDM,
    instrux_RSDC,
    instrux_RSLDT,
    instrux_RSM,
    instrux_RSTS,
    instrux_SAHF,
    instrux_SAL,
    instrux_SALC,
    instrux_SAR,
    instrux_SBB,
    instrux_SCASB,
    instrux_SCASD,
    instrux_SCASQ,
    instrux_SCASW,
    instrux_SFENCE,
    instrux_SGDT,
    instrux_SHL,
    instrux_SHLD,
    instrux_SHR,
    instrux_SHRD,
    instrux_SIDT,
    instrux_SLDT,
    instrux_SKINIT,
    instrux_SMI,
    instrux_SMINT,
    instrux_SMINTOLD,
    instrux_SMSW,
    instrux_STC,
    instrux_STD,
    instrux_STI,
    instrux_STOSB,
    instrux_STOSD,
    instrux_STOSQ,
    instrux_STOSW,
    instrux_STR,
    instrux_SUB,
    instrux_SVDC,
    instrux_SVLDT,
    instrux_SVTS,
    instrux_SWAPGS,
    instrux_SYSCALL,
    instrux_SYSENTER,
    instrux_SYSEXIT,
    instrux_SYSRET,
    instrux_TEST,
    instrux_UD0,
    instrux_UD1,
    instrux_UD2B,
    instrux_UD2,
    instrux_UD2A,
    instrux_UMOV,
    instrux_VERR,
    instrux_VERW,
    instrux_FWAIT,
    instrux_WBINVD,
    instrux_WRSHR,
    instrux_WRMSR,
    instrux_XADD,
    instrux_XBTS,
    instrux_XCHG,
    instrux_XLATB,
    instrux_XLAT,
    instrux_XOR,
    instrux_ADDPS,
    instrux_ADDSS,
    instrux_ANDNPS,
    instrux_ANDPS,
    instrux_CMPEQPS,
    instrux_CMPEQSS,
    instrux_CMPLEPS,
    instrux_CMPLESS,
    instrux_CMPLTPS,
    instrux_CMPLTSS,
    instrux_CMPNEQPS,
    instrux_CMPNEQSS,
    instrux_CMPNLEPS,
    instrux_CMPNLESS,
    instrux_CMPNLTPS,
    instrux_CMPNLTSS,
    instrux_CMPORDPS,
    instrux_CMPORDSS,
    instrux_CMPUNORDPS,
    instrux_CMPUNORDSS,
    instrux_CMPPS,
    instrux_CMPSS,
    instrux_COMISS,
    instrux_CVTPI2PS,
    instrux_CVTPS2PI,
    instrux_CVTSI2SS,
    instrux_CVTSS2SI,
    instrux_CVTTPS2PI,
    instrux_CVTTSS2SI,
    instrux_DIVPS,
    instrux_DIVSS,
    instrux_LDMXCSR,
    instrux_MAXPS,
    instrux_MAXSS,
    instrux_MINPS,
    instrux_MINSS,
    instrux_MOVAPS,
    instrux_MOVHPS,
    instrux_MOVLHPS,
    instrux_MOVLPS,
    instrux_MOVHLPS,
    instrux_MOVMSKPS,
    instrux_MOVNTPS,
    instrux_MOVSS,
    instrux_MOVUPS,
    instrux_MULPS,
    instrux_MULSS,
    instrux_ORPS,
    instrux_RCPPS,
    instrux_RCPSS,
    instrux_RSQRTPS,
    instrux_RSQRTSS,
    instrux_SHUFPS,
    instrux_SQRTPS,
    instrux_SQRTSS,
    instrux_STMXCSR,
    instrux_SUBPS,
    instrux_SUBSS,
    instrux_UCOMISS,
    instrux_UNPCKHPS,
    instrux_UNPCKLPS,
    instrux_XORPS,
    instrux_FXRSTOR,
    instrux_FXRSTOR64,
    instrux_FXSAVE,
    instrux_FXSAVE64,
    instrux_XGETBV,
    instrux_XSETBV,
    instrux_XSAVE,
    instrux_XSAVE64,
    instrux_XSAVEC,
    instrux_XSAVEC64,
    instrux_XSAVEOPT,
    instrux_XSAVEOPT64,
    instrux_XSAVES,
    instrux_XSAVES64,
    instrux_XRSTOR,
    instrux_XRSTOR64,
    instrux_XRSTORS,
    instrux_XRSTORS64,
    instrux_PREFETCHNTA,
    instrux_PREFETCHT0,
    instrux_PREFETCHT1,
    instrux_PREFETCHT2,
    instrux_MASKMOVQ,
    instrux_MOVNTQ,
    instrux_PAVGB,
    instrux_PAVGW,
    instrux_PEXTRW,
    instrux_PINSRW,
    instrux_PMAXSW,
    instrux_PMAXUB,
    instrux_PMINSW,
    instrux_PMINUB,
    instrux_PMOVMSKB,
    instrux_PMULHUW,
    instrux_PSADBW,
    instrux_PSHUFW,
    instrux_PF2IW,
    instrux_PFNACC,
    instrux_PFPNACC,
    instrux_PI2FW,
    instrux_PSWAPD,
    instrux_MASKMOVDQU,
    instrux_CLFLUSH,
    instrux_MOVNTDQ,
    instrux_MOVNTI,
    instrux_MOVNTPD,
    instrux_MOVDQA,
    instrux_MOVDQU,
    instrux_MOVDQ2Q,
    instrux_MOVQ2DQ,
    instrux_PADDQ,
    instrux_PMULUDQ,
    instrux_PSHUFD,
    instrux_PSHUFHW,
    instrux_PSHUFLW,
    instrux_PSLLDQ,
    instrux_PSRLDQ,
    instrux_PSUBQ,
    instrux_PUNPCKHQDQ,
    instrux_PUNPCKLQDQ,
    instrux_ADDPD,
    instrux_ADDSD,
    instrux_ANDNPD,
    instrux_ANDPD,
    instrux_CMPEQPD,
    instrux_CMPEQSD,
    instrux_CMPLEPD,
    instrux_CMPLESD,
    instrux_CMPLTPD,
    instrux_CMPLTSD,
    instrux_CMPNEQPD,
    instrux_CMPNEQSD,
    instrux_CMPNLEPD,
    instrux_CMPNLESD,
    instrux_CMPNLTPD,
    instrux_CMPNLTSD,
    instrux_CMPORDPD,
    instrux_CMPORDSD,
    instrux_CMPUNORDPD,
    instrux_CMPUNORDSD,
    instrux_CMPPD,
    instrux_COMISD,
    instrux_CVTDQ2PD,
    instrux_CVTDQ2PS,
    instrux_CVTPD2DQ,
    instrux_CVTPD2PI,
    instrux_CVTPD2PS,
    instrux_CVTPI2PD,
    instrux_CVTPS2DQ,
    instrux_CVTPS2PD,
    instrux_CVTSD2SI,
    instrux_CVTSD2SS,
    instrux_CVTSI2SD,
    instrux_CVTSS2SD,
    instrux_CVTTPD2PI,
    instrux_CVTTPD2DQ,
    instrux_CVTTPS2DQ,
    instrux_CVTTSD2SI,
    instrux_DIVPD,
    instrux_DIVSD,
    instrux_MAXPD,
    instrux_MAXSD,
    instrux_MINPD,
    instrux_MINSD,
    instrux_MOVAPD,
    instrux_MOVHPD,
    instrux_MOVLPD,
    instrux_MOVMSKPD,
    instrux_MOVUPD,
    instrux_MULPD,
    instrux_MULSD,
    instrux_ORPD,
    instrux_SHUFPD,
    instrux_SQRTPD,
    instrux_SQRTSD,
    instrux_SUBPD,
    instrux_SUBSD,
    instrux_UCOMISD,
    instrux_UNPCKHPD,
    instrux_UNPCKLPD,
    instrux_XORPD,
    instrux_ADDSUBPD,
    instrux_ADDSUBPS,
    instrux_HADDPD,
    instrux_HADDPS,
    instrux_HSUBPD,
    instrux_HSUBPS,
    instrux_LDDQU,
    instrux_MOVDDUP,
    instrux_MOVSHDUP,
    instrux_MOVSLDUP,
    instrux_CLGI,
    instrux_STGI,
    instrux_VMCALL,
    instrux_VMCLEAR,
    instrux_VMFUNC,
    instrux_VMLAUNCH,
    instrux_VMLOAD,
    instrux_VMMCALL,
    instrux_VMPTRLD,
    instrux_VMPTRST,
    instrux_VMREAD,
    instrux_VMRESUME,
    instrux_VMRUN,
    instrux_VMSAVE,
    instrux_VMWRITE,
    instrux_VMXOFF,
    instrux_VMXON,
    instrux_INVEPT,
    instrux_INVVPID,
    instrux_PABSB,
    instrux_PABSW,
    instrux_PABSD,
    instrux_PALIGNR,
    instrux_PHADDW,
    instrux_PHADDD,
    instrux_PHADDSW,
    instrux_PHSUBW,
    instrux_PHSUBD,
    instrux_PHSUBSW,
    instrux_PMADDUBSW,
    instrux_PMULHRSW,
    instrux_PSHUFB,
    instrux_PSIGNB,
    instrux_PSIGNW,
    instrux_PSIGND,
    instrux_EXTRQ,
    instrux_INSERTQ,
    instrux_MOVNTSD,
    instrux_MOVNTSS,
    instrux_LZCNT,
    instrux_BLENDPD,
    instrux_BLENDPS,
    instrux_BLENDVPD,
    instrux_BLENDVPS,
    instrux_DPPD,
    instrux_DPPS,
    instrux_EXTRACTPS,
    instrux_INSERTPS,
    instrux_MOVNTDQA,
    instrux_MPSADBW,
    instrux_PACKUSDW,
    instrux_PBLENDVB,
    instrux_PBLENDW,
    instrux_PCMPEQQ,
    instrux_PEXTRB,
    instrux_PEXTRD,
    instrux_PEXTRQ,
    instrux_PHMINPOSUW,
    instrux_PINSRB,
    instrux_PINSRD,
    instrux_PINSRQ,
    instrux_PMAXSB,
    instrux_PMAXSD,
    instrux_PMAXUD,
    instrux_PMAXUW,
    instrux_PMINSB,
    instrux_PMINSD,
    instrux_PMINUD,
    instrux_PMINUW,
    instrux_PMOVSXBW,
    instrux_PMOVSXBD,
    instrux_PMOVSXBQ,
    instrux_PMOVSXWD,
    instrux_PMOVSXWQ,
    instrux_PMOVSXDQ,
    instrux_PMOVZXBW,
    instrux_PMOVZXBD,
    instrux_PMOVZXBQ,
    instrux_PMOVZXWD,
    instrux_PMOVZXWQ,
    instrux_PMOVZXDQ,
    instrux_PMULDQ,
    instrux_PMULLD,
    instrux_PTEST,
    instrux_ROUNDPD,
    instrux_ROUNDPS,
    instrux_ROUNDSD,
    instrux_ROUNDSS,
    instrux_CRC32,
    instrux_PCMPESTRI,
    instrux_PCMPESTRM,
    instrux_PCMPISTRI,
    instrux_PCMPISTRM,
    instrux_PCMPGTQ,
    instrux_POPCNT,
    instrux_GETSEC,
    instrux_PFRCPV,
    instrux_PFRSQRTV,
    instrux_MOVBE,
    instrux_AESENC,
    instrux_AESENCLAST,
    instrux_AESDEC,
    instrux_AESDECLAST,
    instrux_AESIMC,
    instrux_AESKEYGENASSIST,
    instrux_VAESENC,
    instrux_VAESENCLAST,
    instrux_VAESDEC,
    instrux_VAESDECLAST,
    instrux_VAESIMC,
    instrux_VAESKEYGENASSIST,
    instrux_VADDPD,
    instrux_VADDPS,
    instrux_VADDSD,
    instrux_VADDSS,
    instrux_VADDSUBPD,
    instrux_VADDSUBPS,
    instrux_VANDPD,
    instrux_VANDPS,
    instrux_VANDNPD,
    instrux_VANDNPS,
    instrux_VBLENDPD,
    instrux_VBLENDPS,
    instrux_VBLENDVPD,
    instrux_VBLENDVPS,
    instrux_VBROADCASTSS,
    instrux_VBROADCASTSD,
    instrux_VBROADCASTF128,
    instrux_VCMPEQ_OSPD,
    instrux_VCMPEQPD,
    instrux_VCMPLT_OSPD,
    instrux_VCMPLTPD,
    instrux_VCMPLE_OSPD,
    instrux_VCMPLEPD,
    instrux_VCMPUNORD_QPD,
    instrux_VCMPUNORDPD,
    instrux_VCMPNEQ_UQPD,
    instrux_VCMPNEQPD,
    instrux_VCMPNLT_USPD,
    instrux_VCMPNLTPD,
    instrux_VCMPNLE_USPD,
    instrux_VCMPNLEPD,
    instrux_VCMPORD_QPD,
    instrux_VCMPORDPD,
    instrux_VCMPEQ_UQPD,
    instrux_VCMPNGE_USPD,
    instrux_VCMPNGEPD,
    instrux_VCMPNGT_USPD,
    instrux_VCMPNGTPD,
    instrux_VCMPFALSE_OQPD,
    instrux_VCMPFALSEPD,
    instrux_VCMPNEQ_OQPD,
    instrux_VCMPGE_OSPD,
    instrux_VCMPGEPD,
    instrux_VCMPGT_OSPD,
    instrux_VCMPGTPD,
    instrux_VCMPTRUE_UQPD,
    instrux_VCMPTRUEPD,
    instrux_VCMPLT_OQPD,
    instrux_VCMPLE_OQPD,
    instrux_VCMPUNORD_SPD,
    instrux_VCMPNEQ_USPD,
    instrux_VCMPNLT_UQPD,
    instrux_VCMPNLE_UQPD,
    instrux_VCMPORD_SPD,
    instrux_VCMPEQ_USPD,
    instrux_VCMPNGE_UQPD,
    instrux_VCMPNGT_UQPD,
    instrux_VCMPFALSE_OSPD,
    instrux_VCMPNEQ_OSPD,
    instrux_VCMPGE_OQPD,
    instrux_VCMPGT_OQPD,
    instrux_VCMPTRUE_USPD,
    instrux_VCMPPD,
    instrux_VCMPEQ_OSPS,
    instrux_VCMPEQPS,
    instrux_VCMPLT_OSPS,
    instrux_VCMPLTPS,
    instrux_VCMPLE_OSPS,
    instrux_VCMPLEPS,
    instrux_VCMPUNORD_QPS,
    instrux_VCMPUNORDPS,
    instrux_VCMPNEQ_UQPS,
    instrux_VCMPNEQPS,
    instrux_VCMPNLT_USPS,
    instrux_VCMPNLTPS,
    instrux_VCMPNLE_USPS,
    instrux_VCMPNLEPS,
    instrux_VCMPORD_QPS,
    instrux_VCMPORDPS,
    instrux_VCMPEQ_UQPS,
    instrux_VCMPNGE_USPS,
    instrux_VCMPNGEPS,
    instrux_VCMPNGT_USPS,
    instrux_VCMPNGTPS,
    instrux_VCMPFALSE_OQPS,
    instrux_VCMPFALSEPS,
    instrux_VCMPNEQ_OQPS,
    instrux_VCMPGE_OSPS,
    instrux_VCMPGEPS,
    instrux_VCMPGT_OSPS,
    instrux_VCMPGTPS,
    instrux_VCMPTRUE_UQPS,
    instrux_VCMPTRUEPS,
    instrux_VCMPLT_OQPS,
    instrux_VCMPLE_OQPS,
    instrux_VCMPUNORD_SPS,
    instrux_VCMPNEQ_USPS,
    instrux_VCMPNLT_UQPS,
    instrux_VCMPNLE_UQPS,
    instrux_VCMPORD_SPS,
    instrux_VCMPEQ_USPS,
    instrux_VCMPNGE_UQPS,
    instrux_VCMPNGT_UQPS,
    instrux_VCMPFALSE_OSPS,
    instrux_VCMPNEQ_OSPS,
    instrux_VCMPGE_OQPS,
    instrux_VCMPGT_OQPS,
    instrux_VCMPTRUE_USPS,
    instrux_VCMPPS,
    instrux_VCMPEQ_OSSD,
    instrux_VCMPEQSD,
    instrux_VCMPLT_OSSD,
    instrux_VCMPLTSD,
    instrux_VCMPLE_OSSD,
    instrux_VCMPLESD,
    instrux_VCMPUNORD_QSD,
    instrux_VCMPUNORDSD,
    instrux_VCMPNEQ_UQSD,
    instrux_VCMPNEQSD,
    instrux_VCMPNLT_USSD,
    instrux_VCMPNLTSD,
    instrux_VCMPNLE_USSD,
    instrux_VCMPNLESD,
    instrux_VCMPORD_QSD,
    instrux_VCMPORDSD,
    instrux_VCMPEQ_UQSD,
    instrux_VCMPNGE_USSD,
    instrux_VCMPNGESD,
    instrux_VCMPNGT_USSD,
    instrux_VCMPNGTSD,
    instrux_VCMPFALSE_OQSD,
    instrux_VCMPFALSESD,
    instrux_VCMPNEQ_OQSD,
    instrux_VCMPGE_OSSD,
    instrux_VCMPGESD,
    instrux_VCMPGT_OSSD,
    instrux_VCMPGTSD,
    instrux_VCMPTRUE_UQSD,
    instrux_VCMPTRUESD,
    instrux_VCMPLT_OQSD,
    instrux_VCMPLE_OQSD,
    instrux_VCMPUNORD_SSD,
    instrux_VCMPNEQ_USSD,
    instrux_VCMPNLT_UQSD,
    instrux_VCMPNLE_UQSD,
    instrux_VCMPORD_SSD,
    instrux_VCMPEQ_USSD,
    instrux_VCMPNGE_UQSD,
    instrux_VCMPNGT_UQSD,
    instrux_VCMPFALSE_OSSD,
    instrux_VCMPNEQ_OSSD,
    instrux_VCMPGE_OQSD,
    instrux_VCMPGT_OQSD,
    instrux_VCMPTRUE_USSD,
    instrux_VCMPSD,
    instrux_VCMPEQ_OSSS,
    instrux_VCMPEQSS,
    instrux_VCMPLT_OSSS,
    instrux_VCMPLTSS,
    instrux_VCMPLE_OSSS,
    instrux_VCMPLESS,
    instrux_VCMPUNORD_QSS,
    instrux_VCMPUNORDSS,
    instrux_VCMPNEQ_UQSS,
    instrux_VCMPNEQSS,
    instrux_VCMPNLT_USSS,
    instrux_VCMPNLTSS,
    instrux_VCMPNLE_USSS,
    instrux_VCMPNLESS,
    instrux_VCMPORD_QSS,
    instrux_VCMPORDSS,
    instrux_VCMPEQ_UQSS,
    instrux_VCMPNGE_USSS,
    instrux_VCMPNGESS,
    instrux_VCMPNGT_USSS,
    instrux_VCMPNGTSS,
    instrux_VCMPFALSE_OQSS,
    instrux_VCMPFALSESS,
    instrux_VCMPNEQ_OQSS,
    instrux_VCMPGE_OSSS,
    instrux_VCMPGESS,
    instrux_VCMPGT_OSSS,
    instrux_VCMPGTSS,
    instrux_VCMPTRUE_UQSS,
    instrux_VCMPTRUESS,
    instrux_VCMPLT_OQSS,
    instrux_VCMPLE_OQSS,
    instrux_VCMPUNORD_SSS,
    instrux_VCMPNEQ_USSS,
    instrux_VCMPNLT_UQSS,
    instrux_VCMPNLE_UQSS,
    instrux_VCMPORD_SSS,
    instrux_VCMPEQ_USSS,
    instrux_VCMPNGE_UQSS,
    instrux_VCMPNGT_UQSS,
    instrux_VCMPFALSE_OSSS,
    instrux_VCMPNEQ_OSSS,
    instrux_VCMPGE_OQSS,
    instrux_VCMPGT_OQSS,
    instrux_VCMPTRUE_USSS,
    instrux_VCMPSS,
    instrux_VCOMISD,
    instrux_VCOMISS,
    instrux_VCVTDQ2PD,
    instrux_VCVTDQ2PS,
    instrux_VCVTPD2DQ,
    instrux_VCVTPD2PS,
    instrux_VCVTPS2DQ,
    instrux_VCVTPS2PD,
    instrux_VCVTSD2SI,
    instrux_VCVTSD2SS,
    instrux_VCVTSI2SD,
    instrux_VCVTSI2SS,
    instrux_VCVTSS2SD,
    instrux_VCVTSS2SI,
    instrux_VCVTTPD2DQ,
    instrux_VCVTTPS2DQ,
    instrux_VCVTTSD2SI,
    instrux_VCVTTSS2SI,
    instrux_VDIVPD,
    instrux_VDIVPS,
    instrux_VDIVSD,
    instrux_VDIVSS,
    instrux_VDPPD,
    instrux_VDPPS,
    instrux_VEXTRACTF128,
    instrux_VEXTRACTPS,
    instrux_VHADDPD,
    instrux_VHADDPS,
    instrux_VHSUBPD,
    instrux_VHSUBPS,
    instrux_VINSERTF128,
    instrux_VINSERTPS,
    instrux_VLDDQU,
    instrux_VLDQQU,
    instrux_VLDMXCSR,
    instrux_VMASKMOVDQU,
    instrux_VMASKMOVPS,
    instrux_VMASKMOVPD,
    instrux_VMAXPD,
    instrux_VMAXPS,
    instrux_VMAXSD,
    instrux_VMAXSS,
    instrux_VMINPD,
    instrux_VMINPS,
    instrux_VMINSD,
    instrux_VMINSS,
    instrux_VMOVAPD,
    instrux_VMOVAPS,
    instrux_VMOVD,
    instrux_VMOVQ,
    instrux_VMOVDDUP,
    instrux_VMOVDQA,
    instrux_VMOVQQA,
    instrux_VMOVDQU,
    instrux_VMOVQQU,
    instrux_VMOVHLPS,
    instrux_VMOVHPD,
    instrux_VMOVHPS,
    instrux_VMOVLHPS,
    instrux_VMOVLPD,
    instrux_VMOVLPS,
    instrux_VMOVMSKPD,
    instrux_VMOVMSKPS,
    instrux_VMOVNTDQ,
    instrux_VMOVNTQQ,
    instrux_VMOVNTDQA,
    instrux_VMOVNTPD,
    instrux_VMOVNTPS,
    instrux_VMOVSD,
    instrux_VMOVSHDUP,
    instrux_VMOVSLDUP,
    instrux_VMOVSS,
    instrux_VMOVUPD,
    instrux_VMOVUPS,
    instrux_VMPSADBW,
    instrux_VMULPD,
    instrux_VMULPS,
    instrux_VMULSD,
    instrux_VMULSS,
    instrux_VORPD,
    instrux_VORPS,
    instrux_VPABSB,
    instrux_VPABSW,
    instrux_VPABSD,
    instrux_VPACKSSWB,
    instrux_VPACKSSDW,
    instrux_VPACKUSWB,
    instrux_VPACKUSDW,
    instrux_VPADDB,
    instrux_VPADDW,
    instrux_VPADDD,
    instrux_VPADDQ,
    instrux_VPADDSB,
    instrux_VPADDSW,
    instrux_VPADDUSB,
    instrux_VPADDUSW,
    instrux_VPALIGNR,
    instrux_VPAND,
    instrux_VPANDN,
    instrux_VPAVGB,
    instrux_VPAVGW,
    instrux_VPBLENDVB,
    instrux_VPBLENDW,
    instrux_VPCMPESTRI,
    instrux_VPCMPESTRM,
    instrux_VPCMPISTRI,
    instrux_VPCMPISTRM,
    instrux_VPCMPEQB,
    instrux_VPCMPEQW,
    instrux_VPCMPEQD,
    instrux_VPCMPEQQ,
    instrux_VPCMPGTB,
    instrux_VPCMPGTW,
    instrux_VPCMPGTD,
    instrux_VPCMPGTQ,
    instrux_VPERMILPD,
    instrux_VPERMILPS,
    instrux_VPERM2F128,
    instrux_VPEXTRB,
    instrux_VPEXTRW,
    instrux_VPEXTRD,
    instrux_VPEXTRQ,
    instrux_VPHADDW,
    instrux_VPHADDD,
    instrux_VPHADDSW,
    instrux_VPHMINPOSUW,
    instrux_VPHSUBW,
    instrux_VPHSUBD,
    instrux_VPHSUBSW,
    instrux_VPINSRB,
    instrux_VPINSRW,
    instrux_VPINSRD,
    instrux_VPINSRQ,
    instrux_VPMADDWD,
    instrux_VPMADDUBSW,
    instrux_VPMAXSB,
    instrux_VPMAXSW,
    instrux_VPMAXSD,
    instrux_VPMAXUB,
    instrux_VPMAXUW,
    instrux_VPMAXUD,
    instrux_VPMINSB,
    instrux_VPMINSW,
    instrux_VPMINSD,
    instrux_VPMINUB,
    instrux_VPMINUW,
    instrux_VPMINUD,
    instrux_VPMOVMSKB,
    instrux_VPMOVSXBW,
    instrux_VPMOVSXBD,
    instrux_VPMOVSXBQ,
    instrux_VPMOVSXWD,
    instrux_VPMOVSXWQ,
    instrux_VPMOVSXDQ,
    instrux_VPMOVZXBW,
    instrux_VPMOVZXBD,
    instrux_VPMOVZXBQ,
    instrux_VPMOVZXWD,
    instrux_VPMOVZXWQ,
    instrux_VPMOVZXDQ,
    instrux_VPMULHUW,
    instrux_VPMULHRSW,
    instrux_VPMULHW,
    instrux_VPMULLW,
    instrux_VPMULLD,
    instrux_VPMULUDQ,
    instrux_VPMULDQ,
    instrux_VPOR,
    instrux_VPSADBW,
    instrux_VPSHUFB,
    instrux_VPSHUFD,
    instrux_VPSHUFHW,
    instrux_VPSHUFLW,
    instrux_VPSIGNB,
    instrux_VPSIGNW,
    instrux_VPSIGND,
    instrux_VPSLLDQ,
    instrux_VPSRLDQ,
    instrux_VPSLLW,
    instrux_VPSLLD,
    instrux_VPSLLQ,
    instrux_VPSRAW,
    instrux_VPSRAD,
    instrux_VPSRLW,
    instrux_VPSRLD,
    instrux_VPSRLQ,
    instrux_VPTEST,
    instrux_VPSUBB,
    instrux_VPSUBW,
    instrux_VPSUBD,
    instrux_VPSUBQ,
    instrux_VPSUBSB,
    instrux_VPSUBSW,
    instrux_VPSUBUSB,
    instrux_VPSUBUSW,
    instrux_VPUNPCKHBW,
    instrux_VPUNPCKHWD,
    instrux_VPUNPCKHDQ,
    instrux_VPUNPCKHQDQ,
    instrux_VPUNPCKLBW,
    instrux_VPUNPCKLWD,
    instrux_VPUNPCKLDQ,
    instrux_VPUNPCKLQDQ,
    instrux_VPXOR,
    instrux_VRCPPS,
    instrux_VRCPSS,
    instrux_VRSQRTPS,
    instrux_VRSQRTSS,
    instrux_VROUNDPD,
    instrux_VROUNDPS,
    instrux_VROUNDSD,
    instrux_VROUNDSS,
    instrux_VSHUFPD,
    instrux_VSHUFPS,
    instrux_VSQRTPD,
    instrux_VSQRTPS,
    instrux_VSQRTSD,
    instrux_VSQRTSS,
    instrux_VSTMXCSR,
    instrux_VSUBPD,
    instrux_VSUBPS,
    instrux_VSUBSD,
    instrux_VSUBSS,
    instrux_VTESTPS,
    instrux_VTESTPD,
    instrux_VUCOMISD,
    instrux_VUCOMISS,
    instrux_VUNPCKHPD,
    instrux_VUNPCKHPS,
    instrux_VUNPCKLPD,
    instrux_VUNPCKLPS,
    instrux_VXORPD,
    instrux_VXORPS,
    instrux_VZEROALL,
    instrux_VZEROUPPER,
    instrux_PCLMULLQLQDQ,
    instrux_PCLMULHQLQDQ,
    instrux_PCLMULLQHQDQ,
    instrux_PCLMULHQHQDQ,
    instrux_PCLMULQDQ,
    instrux_VPCLMULLQLQDQ,
    instrux_VPCLMULHQLQDQ,
    instrux_VPCLMULLQHQDQ,
    instrux_VPCLMULHQHQDQ,
    instrux_VPCLMULQDQ,
    instrux_VFMADD132PS,
    instrux_VFMADD132PD,
    instrux_VFMADD312PS,
    instrux_VFMADD312PD,
    instrux_VFMADD213PS,
    instrux_VFMADD213PD,
    instrux_VFMADD123PS,
    instrux_VFMADD123PD,
    instrux_VFMADD231PS,
    instrux_VFMADD231PD,
    instrux_VFMADD321PS,
    instrux_VFMADD321PD,
    instrux_VFMADDSUB132PS,
    instrux_VFMADDSUB132PD,
    instrux_VFMADDSUB312PS,
    instrux_VFMADDSUB312PD,
    instrux_VFMADDSUB213PS,
    instrux_VFMADDSUB213PD,
    instrux_VFMADDSUB123PS,
    instrux_VFMADDSUB123PD,
    instrux_VFMADDSUB231PS,
    instrux_VFMADDSUB231PD,
    instrux_VFMADDSUB321PS,
    instrux_VFMADDSUB321PD,
    instrux_VFMSUB132PS,
    instrux_VFMSUB132PD,
    instrux_VFMSUB312PS,
    instrux_VFMSUB312PD,
    instrux_VFMSUB213PS,
    instrux_VFMSUB213PD,
    instrux_VFMSUB123PS,
    instrux_VFMSUB123PD,
    instrux_VFMSUB231PS,
    instrux_VFMSUB231PD,
    instrux_VFMSUB321PS,
    instrux_VFMSUB321PD,
    instrux_VFMSUBADD132PS,
    instrux_VFMSUBADD132PD,
    instrux_VFMSUBADD312PS,
    instrux_VFMSUBADD312PD,
    instrux_VFMSUBADD213PS,
    instrux_VFMSUBADD213PD,
    instrux_VFMSUBADD123PS,
    instrux_VFMSUBADD123PD,
    instrux_VFMSUBADD231PS,
    instrux_VFMSUBADD231PD,
    instrux_VFMSUBADD321PS,
    instrux_VFMSUBADD321PD,
    instrux_VFNMADD132PS,
    instrux_VFNMADD132PD,
    instrux_VFNMADD312PS,
    instrux_VFNMADD312PD,
    instrux_VFNMADD213PS,
    instrux_VFNMADD213PD,
    instrux_VFNMADD123PS,
    instrux_VFNMADD123PD,
    instrux_VFNMADD231PS,
    instrux_VFNMADD231PD,
    instrux_VFNMADD321PS,
    instrux_VFNMADD321PD,
    instrux_VFNMSUB132PS,
    instrux_VFNMSUB132PD,
    instrux_VFNMSUB312PS,
    instrux_VFNMSUB312PD,
    instrux_VFNMSUB213PS,
    instrux_VFNMSUB213PD,
    instrux_VFNMSUB123PS,
    instrux_VFNMSUB123PD,
    instrux_VFNMSUB231PS,
    instrux_VFNMSUB231PD,
    instrux_VFNMSUB321PS,
    instrux_VFNMSUB321PD,
    instrux_VFMADD132SS,
    instrux_VFMADD132SD,
    instrux_VFMADD312SS,
    instrux_VFMADD312SD,
    instrux_VFMADD213SS,
    instrux_VFMADD213SD,
    instrux_VFMADD123SS,
    instrux_VFMADD123SD,
    instrux_VFMADD231SS,
    instrux_VFMADD231SD,
    instrux_VFMADD321SS,
    instrux_VFMADD321SD,
    instrux_VFMSUB132SS,
    instrux_VFMSUB132SD,
    instrux_VFMSUB312SS,
    instrux_VFMSUB312SD,
    instrux_VFMSUB213SS,
    instrux_VFMSUB213SD,
    instrux_VFMSUB123SS,
    instrux_VFMSUB123SD,
    instrux_VFMSUB231SS,
    instrux_VFMSUB231SD,
    instrux_VFMSUB321SS,
    instrux_VFMSUB321SD,
    instrux_VFNMADD132SS,
    instrux_VFNMADD132SD,
    instrux_VFNMADD312SS,
    instrux_VFNMADD312SD,
    instrux_VFNMADD213SS,
    instrux_VFNMADD213SD,
    instrux_VFNMADD123SS,
    instrux_VFNMADD123SD,
    instrux_VFNMADD231SS,
    instrux_VFNMADD231SD,
    instrux_VFNMADD321SS,
    instrux_VFNMADD321SD,
    instrux_VFNMSUB132SS,
    instrux_VFNMSUB132SD,
    instrux_VFNMSUB312SS,
    instrux_VFNMSUB312SD,
    instrux_VFNMSUB213SS,
    instrux_VFNMSUB213SD,
    instrux_VFNMSUB123SS,
    instrux_VFNMSUB123SD,
    instrux_VFNMSUB231SS,
    instrux_VFNMSUB231SD,
    instrux_VFNMSUB321SS,
    instrux_VFNMSUB321SD,
    instrux_RDFSBASE,
    instrux_RDGSBASE,
    instrux_RDRAND,
    instrux_WRFSBASE,
    instrux_WRGSBASE,
    instrux_VCVTPH2PS,
    instrux_VCVTPS2PH,
    instrux_ADCX,
    instrux_ADOX,
    instrux_RDSEED,
    instrux_CLAC,
    instrux_STAC,
    instrux_XSTORE,
    instrux_XCRYPTECB,
    instrux_XCRYPTCBC,
    instrux_XCRYPTCTR,
    instrux_XCRYPTCFB,
    instrux_XCRYPTOFB,
    instrux_MONTMUL,
    instrux_XSHA1,
    instrux_XSHA256,
    instrux_LLWPCB,
    instrux_SLWPCB,
    instrux_LWPVAL,
    instrux_LWPINS,
    instrux_VFMADDPD,
    instrux_VFMADDPS,
    instrux_VFMADDSD,
    instrux_VFMADDSS,
    instrux_VFMADDSUBPD,
    instrux_VFMADDSUBPS,
    instrux_VFMSUBADDPD,
    instrux_VFMSUBADDPS,
    instrux_VFMSUBPD,
    instrux_VFMSUBPS,
    instrux_VFMSUBSD,
    instrux_VFMSUBSS,
    instrux_VFNMADDPD,
    instrux_VFNMADDPS,
    instrux_VFNMADDSD,
    instrux_VFNMADDSS,
    instrux_VFNMSUBPD,
    instrux_VFNMSUBPS,
    instrux_VFNMSUBSD,
    instrux_VFNMSUBSS,
    instrux_VFRCZPD,
    instrux_VFRCZPS,
    instrux_VFRCZSD,
    instrux_VFRCZSS,
    instrux_VPCMOV,
    instrux_VPCOMB,
    instrux_VPCOMD,
    instrux_VPCOMQ,
    instrux_VPCOMUB,
    instrux_VPCOMUD,
    instrux_VPCOMUQ,
    instrux_VPCOMUW,
    instrux_VPCOMW,
    instrux_VPHADDBD,
    instrux_VPHADDBQ,
    instrux_VPHADDBW,
    instrux_VPHADDDQ,
    instrux_VPHADDUBD,
    instrux_VPHADDUBQ,
    instrux_VPHADDUBW,
    instrux_VPHADDUDQ,
    instrux_VPHADDUWD,
    instrux_VPHADDUWQ,
    instrux_VPHADDWD,
    instrux_VPHADDWQ,
    instrux_VPHSUBBW,
    instrux_VPHSUBDQ,
    instrux_VPHSUBWD,
    instrux_VPMACSDD,
    instrux_VPMACSDQH,
    instrux_VPMACSDQL,
    instrux_VPMACSSDD,
    instrux_VPMACSSDQH,
    instrux_VPMACSSDQL,
    instrux_VPMACSSWD,
    instrux_VPMACSSWW,
    instrux_VPMACSWD,
    instrux_VPMACSWW,
    instrux_VPMADCSSWD,
    instrux_VPMADCSWD,
    instrux_VPPERM,
    instrux_VPROTB,
    instrux_VPROTD,
    instrux_VPROTQ,
    instrux_VPROTW,
    instrux_VPSHAB,
    instrux_VPSHAD,
    instrux_VPSHAQ,
    instrux_VPSHAW,
    instrux_VPSHLB,
    instrux_VPSHLD,
    instrux_VPSHLQ,
    instrux_VPSHLW,
    instrux_VBROADCASTI128,
    instrux_VPBLENDD,
    instrux_VPBROADCASTB,
    instrux_VPBROADCASTW,
    instrux_VPBROADCASTD,
    instrux_VPBROADCASTQ,
    instrux_VPERMD,
    instrux_VPERMPD,
    instrux_VPERMPS,
    instrux_VPERMQ,
    instrux_VPERM2I128,
    instrux_VEXTRACTI128,
    instrux_VINSERTI128,
    instrux_VPMASKMOVD,
    instrux_VPMASKMOVQ,
    instrux_VPSLLVD,
    instrux_VPSLLVQ,
    instrux_VPSRAVD,
    instrux_VPSRLVD,
    instrux_VPSRLVQ,
    instrux_VGATHERDPD,
    instrux_VGATHERQPD,
    instrux_VGATHERDPS,
    instrux_VGATHERQPS,
    instrux_VPGATHERDD,
    instrux_VPGATHERQD,
    instrux_VPGATHERDQ,
    instrux_VPGATHERQQ,
    instrux_XABORT,
    instrux_XBEGIN,
    instrux_XEND,
    instrux_XTEST,
    instrux_ANDN,
    instrux_BEXTR,
    instrux_BLCI,
    instrux_BLCIC,
    instrux_BLSI,
    instrux_BLSIC,
    instrux_BLCFILL,
    instrux_BLSFILL,
    instrux_BLCMSK,
    instrux_BLSMSK,
    instrux_BLSR,
    instrux_BLCS,
    instrux_BZHI,
    instrux_MULX,
    instrux_PDEP,
    instrux_PEXT,
    instrux_RORX,
    instrux_SARX,
    instrux_SHLX,
    instrux_SHRX,
    instrux_TZCNT,
    instrux_TZMSK,
    instrux_T1MSKC,
    instrux_PREFETCHWT1,
    instrux_BNDMK,
    instrux_BNDCL,
    instrux_BNDCU,
    instrux_BNDCN,
    instrux_BNDMOV,
    instrux_BNDLDX,
    instrux_BNDSTX,
    instrux_SHA1MSG1,
    instrux_SHA1MSG2,
    instrux_SHA1NEXTE,
    instrux_SHA1RNDS4,
    instrux_SHA256MSG1,
    instrux_SHA256MSG2,
    instrux_SHA256RNDS2,
    instrux_KADDB,
    instrux_KADDD,
    instrux_KADDQ,
    instrux_KADDW,
    instrux_KANDB,
    instrux_KANDD,
    instrux_KANDNB,
    instrux_KANDND,
    instrux_KANDNQ,
    instrux_KANDNW,
    instrux_KANDQ,
    instrux_KANDW,
    instrux_KMOVB,
    instrux_KMOVD,
    instrux_KMOVQ,
    instrux_KMOVW,
    instrux_KNOTB,
    instrux_KNOTD,
    instrux_KNOTQ,
    instrux_KNOTW,
    instrux_KORB,
    instrux_KORD,
    instrux_KORQ,
    instrux_KORW,
    instrux_KORTESTB,
    instrux_KORTESTD,
    instrux_KORTESTQ,
    instrux_KORTESTW,
    instrux_KSHIFTLB,
    instrux_KSHIFTLD,
    instrux_KSHIFTLQ,
    instrux_KSHIFTLW,
    instrux_KSHIFTRB,
    instrux_KSHIFTRD,
    instrux_KSHIFTRQ,
    instrux_KSHIFTRW,
    instrux_KTESTB,
    instrux_KTESTD,
    instrux_KTESTQ,
    instrux_KTESTW,
    instrux_KUNPCKBW,
    instrux_KUNPCKDQ,
    instrux_KUNPCKWD,
    instrux_KXNORB,
    instrux_KXNORD,
    instrux_KXNORQ,
    instrux_KXNORW,
    instrux_KXORB,
    instrux_KXORD,
    instrux_KXORQ,
    instrux_KXORW,
    instrux_KADD,
    instrux_KAND,
    instrux_KANDN,
    instrux_KMOV,
    instrux_KNOT,
    instrux_KOR,
    instrux_KORTEST,
    instrux_KSHIFTL,
    instrux_KSHIFTR,
    instrux_KTEST,
    instrux_KUNPCK,
    instrux_KXNOR,
    instrux_KXOR,
    instrux_VALIGND,
    instrux_VALIGNQ,
    instrux_VBLENDMPD,
    instrux_VBLENDMPS,
    instrux_VBROADCASTF32X2,
    instrux_VBROADCASTF32X4,
    instrux_VBROADCASTF32X8,
    instrux_VBROADCASTF64X2,
    instrux_VBROADCASTF64X4,
    instrux_VBROADCASTI32X2,
    instrux_VBROADCASTI32X4,
    instrux_VBROADCASTI32X8,
    instrux_VBROADCASTI64X2,
    instrux_VBROADCASTI64X4,
    instrux_VCMPEQ_OQPD,
    instrux_VCMPEQ_OQPS,
    instrux_VCMPEQ_OQSD,
    instrux_VCMPEQ_OQSS,
    instrux_VCOMPRESSPD,
    instrux_VCOMPRESSPS,
    instrux_VCVTPD2QQ,
    instrux_VCVTPD2UDQ,
    instrux_VCVTPD2UQQ,
    instrux_VCVTPS2QQ,
    instrux_VCVTPS2UDQ,
    instrux_VCVTPS2UQQ,
    instrux_VCVTQQ2PD,
    instrux_VCVTQQ2PS,
    instrux_VCVTSD2USI,
    instrux_VCVTSS2USI,
    instrux_VCVTTPD2QQ,
    instrux_VCVTTPD2UDQ,
    instrux_VCVTTPD2UQQ,
    instrux_VCVTTPS2QQ,
    instrux_VCVTTPS2UDQ,
    instrux_VCVTTPS2UQQ,
    instrux_VCVTTSD2USI,
    instrux_VCVTTSS2USI,
    instrux_VCVTUDQ2PD,
    instrux_VCVTUDQ2PS,
    instrux_VCVTUQQ2PD,
    instrux_VCVTUQQ2PS,
    instrux_VCVTUSI2SD,
    instrux_VCVTUSI2SS,
    instrux_VDBPSADBW,
    instrux_VEXP2PD,
    instrux_VEXP2PS,
    instrux_VEXPANDPD,
    instrux_VEXPANDPS,
    instrux_VEXTRACTF32X4,
    instrux_VEXTRACTF32X8,
    instrux_VEXTRACTF64X2,
    instrux_VEXTRACTF64X4,
    instrux_VEXTRACTI32X4,
    instrux_VEXTRACTI32X8,
    instrux_VEXTRACTI64X2,
    instrux_VEXTRACTI64X4,
    instrux_VFIXUPIMMPD,
    instrux_VFIXUPIMMPS,
    instrux_VFIXUPIMMSD,
    instrux_VFIXUPIMMSS,
    instrux_VFPCLASSPD,
    instrux_VFPCLASSPS,
    instrux_VFPCLASSSD,
    instrux_VFPCLASSSS,
    instrux_VGATHERPF0DPD,
    instrux_VGATHERPF0DPS,
    instrux_VGATHERPF0QPD,
    instrux_VGATHERPF0QPS,
    instrux_VGATHERPF1DPD,
    instrux_VGATHERPF1DPS,
    instrux_VGATHERPF1QPD,
    instrux_VGATHERPF1QPS,
    instrux_VGETEXPPD,
    instrux_VGETEXPPS,
    instrux_VGETEXPSD,
    instrux_VGETEXPSS,
    instrux_VGETMANTPD,
    instrux_VGETMANTPS,
    instrux_VGETMANTSD,
    instrux_VGETMANTSS,
    instrux_VINSERTF32X4,
    instrux_VINSERTF32X8,
    instrux_VINSERTF64X2,
    instrux_VINSERTF64X4,
    instrux_VINSERTI32X4,
    instrux_VINSERTI32X8,
    instrux_VINSERTI64X2,
    instrux_VINSERTI64X4,
    instrux_VMOVDQA32,
    instrux_VMOVDQA64,
    instrux_VMOVDQU16,
    instrux_VMOVDQU32,
    instrux_VMOVDQU64,
    instrux_VMOVDQU8,
    instrux_VPABSQ,
    instrux_VPANDD,
    instrux_VPANDND,
    instrux_VPANDNQ,
    instrux_VPANDQ,
    instrux_VPBLENDMB,
    instrux_VPBLENDMD,
    instrux_VPBLENDMQ,
    instrux_VPBLENDMW,
    instrux_VPBROADCASTMB2Q,
    instrux_VPBROADCASTMW2D,
    instrux_VPCMPEQUB,
    instrux_VPCMPEQUD,
    instrux_VPCMPEQUQ,
    instrux_VPCMPEQUW,
    instrux_VPCMPGEB,
    instrux_VPCMPGED,
    instrux_VPCMPGEQ,
    instrux_VPCMPGEUB,
    instrux_VPCMPGEUD,
    instrux_VPCMPGEUQ,
    instrux_VPCMPGEUW,
    instrux_VPCMPGEW,
    instrux_VPCMPGTUB,
    instrux_VPCMPGTUD,
    instrux_VPCMPGTUQ,
    instrux_VPCMPGTUW,
    instrux_VPCMPLEB,
    instrux_VPCMPLED,
    instrux_VPCMPLEQ,
    instrux_VPCMPLEUB,
    instrux_VPCMPLEUD,
    instrux_VPCMPLEUQ,
    instrux_VPCMPLEUW,
    instrux_VPCMPLEW,
    instrux_VPCMPLTB,
    instrux_VPCMPLTD,
    instrux_VPCMPLTQ,
    instrux_VPCMPLTUB,
    instrux_VPCMPLTUD,
    instrux_VPCMPLTUQ,
    instrux_VPCMPLTUW,
    instrux_VPCMPLTW,
    instrux_VPCMPNEQB,
    instrux_VPCMPNEQD,
    instrux_VPCMPNEQQ,
    instrux_VPCMPNEQUB,
    instrux_VPCMPNEQUD,
    instrux_VPCMPNEQUQ,
    instrux_VPCMPNEQUW,
    instrux_VPCMPNEQW,
    instrux_VPCMPNGTB,
    instrux_VPCMPNGTD,
    instrux_VPCMPNGTQ,
    instrux_VPCMPNGTUB,
    instrux_VPCMPNGTUD,
    instrux_VPCMPNGTUQ,
    instrux_VPCMPNGTUW,
    instrux_VPCMPNGTW,
    instrux_VPCMPNLEB,
    instrux_VPCMPNLED,
    instrux_VPCMPNLEQ,
    instrux_VPCMPNLEUB,
    instrux_VPCMPNLEUD,
    instrux_VPCMPNLEUQ,
    instrux_VPCMPNLEUW,
    instrux_VPCMPNLEW,
    instrux_VPCMPNLTB,
    instrux_VPCMPNLTD,
    instrux_VPCMPNLTQ,
    instrux_VPCMPNLTUB,
    instrux_VPCMPNLTUD,
    instrux_VPCMPNLTUQ,
    instrux_VPCMPNLTUW,
    instrux_VPCMPNLTW,
    instrux_VPCMPB,
    instrux_VPCMPD,
    instrux_VPCMPQ,
    instrux_VPCMPUB,
    instrux_VPCMPUD,
    instrux_VPCMPUQ,
    instrux_VPCMPUW,
    instrux_VPCMPW,
    instrux_VPCOMPRESSD,
    instrux_VPCOMPRESSQ,
    instrux_VPCONFLICTD,
    instrux_VPCONFLICTQ,
    instrux_VPERMB,
    instrux_VPERMI2B,
    instrux_VPERMI2D,
    instrux_VPERMI2PD,
    instrux_VPERMI2PS,
    instrux_VPERMI2Q,
    instrux_VPERMI2W,
    instrux_VPERMT2B,
    instrux_VPERMT2D,
    instrux_VPERMT2PD,
    instrux_VPERMT2PS,
    instrux_VPERMT2Q,
    instrux_VPERMT2W,
    instrux_VPERMW,
    instrux_VPEXPANDD,
    instrux_VPEXPANDQ,
    instrux_VPLZCNTD,
    instrux_VPLZCNTQ,
    instrux_VPMADD52HUQ,
    instrux_VPMADD52LUQ,
    instrux_VPMAXSQ,
    instrux_VPMAXUQ,
    instrux_VPMINSQ,
    instrux_VPMINUQ,
    instrux_VPMOVB2M,
    instrux_VPMOVD2M,
    instrux_VPMOVDB,
    instrux_VPMOVDW,
    instrux_VPMOVM2B,
    instrux_VPMOVM2D,
    instrux_VPMOVM2Q,
    instrux_VPMOVM2W,
    instrux_VPMOVQ2M,
    instrux_VPMOVQB,
    instrux_VPMOVQD,
    instrux_VPMOVQW,
    instrux_VPMOVSDB,
    instrux_VPMOVSDW,
    instrux_VPMOVSQB,
    instrux_VPMOVSQD,
    instrux_VPMOVSQW,
    instrux_VPMOVSWB,
    instrux_VPMOVUSDB,
    instrux_VPMOVUSDW,
    instrux_VPMOVUSQB,
    instrux_VPMOVUSQD,
    instrux_VPMOVUSQW,
    instrux_VPMOVUSWB,
    instrux_VPMOVW2M,
    instrux_VPMOVWB,
    instrux_VPMULLQ,
    instrux_VPMULTISHIFTQB,
    instrux_VPORD,
    instrux_VPORQ,
    instrux_VPROLD,
    instrux_VPROLQ,
    instrux_VPROLVD,
    instrux_VPROLVQ,
    instrux_VPRORD,
    instrux_VPRORQ,
    instrux_VPRORVD,
    instrux_VPRORVQ,
    instrux_VPSCATTERDD,
    instrux_VPSCATTERDQ,
    instrux_VPSCATTERQD,
    instrux_VPSCATTERQQ,
    instrux_VPSLLVW,
    instrux_VPSRAQ,
    instrux_VPSRAVQ,
    instrux_VPSRAVW,
    instrux_VPSRLVW,
    instrux_VPTERNLOGD,
    instrux_VPTERNLOGQ,
    instrux_VPTESTMB,
    instrux_VPTESTMD,
    instrux_VPTESTMQ,
    instrux_VPTESTMW,
    instrux_VPTESTNMB,
    instrux_VPTESTNMD,
    instrux_VPTESTNMQ,
    instrux_VPTESTNMW,
    instrux_VPXORD,
    instrux_VPXORQ,
    instrux_VRANGEPD,
    instrux_VRANGEPS,
    instrux_VRANGESD,
    instrux_VRANGESS,
    instrux_VRCP14PD,
    instrux_VRCP14PS,
    instrux_VRCP14SD,
    instrux_VRCP14SS,
    instrux_VRCP28PD,
    instrux_VRCP28PS,
    instrux_VRCP28SD,
    instrux_VRCP28SS,
    instrux_VREDUCEPD,
    instrux_VREDUCEPS,
    instrux_VREDUCESD,
    instrux_VREDUCESS,
    instrux_VRNDSCALEPD,
    instrux_VRNDSCALEPS,
    instrux_VRNDSCALESD,
    instrux_VRNDSCALESS,
    instrux_VRSQRT14PD,
    instrux_VRSQRT14PS,
    instrux_VRSQRT14SD,
    instrux_VRSQRT14SS,
    instrux_VRSQRT28PD,
    instrux_VRSQRT28PS,
    instrux_VRSQRT28SD,
    instrux_VRSQRT28SS,
    instrux_VSCALEFPD,
    instrux_VSCALEFPS,
    instrux_VSCALEFSD,
    instrux_VSCALEFSS,
    instrux_VSCATTERDPD,
    instrux_VSCATTERDPS,
    instrux_VSCATTERPF0DPD,
    instrux_VSCATTERPF0DPS,
    instrux_VSCATTERPF0QPD,
    instrux_VSCATTERPF0QPS,
    instrux_VSCATTERPF1DPD,
    instrux_VSCATTERPF1DPS,
    instrux_VSCATTERPF1QPD,
    instrux_VSCATTERPF1QPS,
    instrux_VSCATTERQPD,
    instrux_VSCATTERQPS,
    instrux_VSHUFF32X4,
    instrux_VSHUFF64X2,
    instrux_VSHUFI32X4,
    instrux_VSHUFI64X2,
    instrux_RDPKRU,
    instrux_WRPKRU,
    instrux_RDPID,
    instrux_CLFLUSHOPT,
    instrux_CLWB,
    instrux_PCOMMIT,
    instrux_CLZERO,
    instrux_PTWRITE,
    instrux_CLDEMOTE,
    instrux_MOVDIRI,
    instrux_MOVDIR64B,
    instrux_PCONFIG,
    instrux_TPAUSE,
    instrux_UMONITOR,
    instrux_UMWAIT,
    instrux_WBNOINVD,
    instrux_GF2P8AFFINEINVQB,
    instrux_VGF2P8AFFINEINVQB,
    instrux_GF2P8AFFINEQB,
    instrux_VGF2P8AFFINEQB,
    instrux_GF2P8MULB,
    instrux_VGF2P8MULB,
    instrux_VPCOMPRESSB,
    instrux_VPCOMPRESSW,
    instrux_VPEXPANDB,
    instrux_VPEXPANDW,
    instrux_VPSHLDW,
    instrux_VPSHLDD,
    instrux_VPSHLDQ,
    instrux_VPSHLDVW,
    instrux_VPSHLDVD,
    instrux_VPSHLDVQ,
    instrux_VPSHRDW,
    instrux_VPSHRDD,
    instrux_VPSHRDQ,
    instrux_VPSHRDVW,
    instrux_VPSHRDVD,
    instrux_VPSHRDVQ,
    instrux_VPDPBUSD,
    instrux_VPDPBUSDS,
    instrux_VPDPWSSD,
    instrux_VPDPWSSDS,
    instrux_VPOPCNTB,
    instrux_VPOPCNTW,
    instrux_VPOPCNTD,
    instrux_VPOPCNTQ,
    instrux_VPSHUFBITQMB,
    instrux_V4FMADDPS,
    instrux_V4FNMADDPS,
    instrux_V4FMADDSS,
    instrux_V4FNMADDSS,
    instrux_V4DPWSSDS,
    instrux_V4DPWSSD,
    instrux_ENCLS,
    instrux_ENCLU,
    instrux_ENCLV,
    instrux_CLRSSBSY,
    instrux_ENDBR32,
    instrux_ENDBR64,
    instrux_INCSSPD,
    instrux_INCSSPQ,
    instrux_RDSSPD,
    instrux_RDSSPQ,
    instrux_RSTORSSP,
    instrux_SAVEPREVSSP,
    instrux_SETSSBSY,
    instrux_WRUSSD,
    instrux_WRUSSQ,
    instrux_WRSSD,
    instrux_WRSSQ,
    instrux_ENQCMD,
    instrux_ENQCMDS,
    instrux_SERIALIZE,
    instrux_XRESLDTRK,
    instrux_XSUSLDTRK,
    instrux_VCVTNE2PS2BF16,
    instrux_VDPBF16PS,
    instrux_VP2INTERSECTD,
    instrux_LDTILECFG,
    instrux_STTILECFG,
    instrux_TDPBF16PS,
    instrux_TDPBSSD,
    instrux_TDPBSUD,
    instrux_TDPBUSD,
    instrux_TDPBUUD,
    instrux_TILELOADD,
    instrux_TILELOADDT1,
    instrux_TILERELEASE,
    instrux_TILESTORED,
    instrux_TILEZERO,
    instrux_HINT_NOP0,
    instrux_HINT_NOP1,
    instrux_HINT_NOP2,
    instrux_HINT_NOP3,
    instrux_HINT_NOP4,
    instrux_HINT_NOP5,
    instrux_HINT_NOP6,
    instrux_HINT_NOP7,
    instrux_HINT_NOP8,
    instrux_HINT_NOP9,
    instrux_HINT_NOP10,
    instrux_HINT_NOP11,
    instrux_HINT_NOP12,
    instrux_HINT_NOP13,
    instrux_HINT_NOP14,
    instrux_HINT_NOP15,
    instrux_HINT_NOP16,
    instrux_HINT_NOP17,
    instrux_HINT_NOP18,
    instrux_HINT_NOP19,
    instrux_HINT_NOP20,
    instrux_HINT_NOP21,
    instrux_HINT_NOP22,
    instrux_HINT_NOP23,
    instrux_HINT_NOP24,
    instrux_HINT_NOP25,
    instrux_HINT_NOP26,
    instrux_HINT_NOP27,
    instrux_HINT_NOP28,
    instrux_HINT_NOP29,
    instrux_HINT_NOP30,
    instrux_HINT_NOP31,
    instrux_HINT_NOP32,
    instrux_HINT_NOP33,
    instrux_HINT_NOP34,
    instrux_HINT_NOP35,
    instrux_HINT_NOP36,
    instrux_HINT_NOP37,
    instrux_HINT_NOP38,
    instrux_HINT_NOP39,
    instrux_HINT_NOP40,
    instrux_HINT_NOP41,
    instrux_HINT_NOP42,
    instrux_HINT_NOP43,
    instrux_HINT_NOP44,
    instrux_HINT_NOP45,
    instrux_HINT_NOP46,
    instrux_HINT_NOP47,
    instrux_HINT_NOP48,
    instrux_HINT_NOP49,
    instrux_HINT_NOP50,
    instrux_HINT_NOP51,
    instrux_HINT_NOP52,
    instrux_HINT_NOP53,
    instrux_HINT_NOP54,
    instrux_HINT_NOP55,
    instrux_HINT_NOP56,
    instrux_HINT_NOP57,
    instrux_HINT_NOP58,
    instrux_HINT_NOP59,
    instrux_HINT_NOP60,
    instrux_HINT_NOP61,
    instrux_HINT_NOP62,
    instrux_HINT_NOP63,
    instrux_CMOVcc,
    instrux_Jcc,
    instrux_SETcc,
};
