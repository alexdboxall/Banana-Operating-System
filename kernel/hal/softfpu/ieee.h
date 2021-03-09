#include <stdint.h>

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#define INTEGER_TYPE uint32_t
#define INTEGER_STYPE int32_t

#define INTEGER_DTYPE uint64_t
#define INTEGER_BTYPE uint64_t

#define INTEGER_TYPE_BITS 32

#define COMPUTE_TYPE uint32_t
#define COMPUTE_STYPE int32_t
#define COMPUTE_TYPE_BITS 32
#define MANTISSA_NWORDS 1
#define MANTISSA_BITS 24
#define EXP_BITS 8
#define FLOATING_TYPE float
#define SFmode
#define MSB_IMPLICIT true

#define S_MANTISSA_NWORDS 1
#define S_MANTISSA_BITS 24
#define S_EXP_BITS 8
#define S_FLOATING_TYPE float

#define B_MANTISSA_NWORDS 2
#define B_MANTISSA_BITS 53
#define B_EXP_BITS 11
#define B_FLOATING_TYPE double