#pragma once

#include <stdint.h>
#include <stddef.h>

typedef uint8_t		u8_t;
typedef uint16_t	u16_t;
typedef uint32_t	u32_t;

typedef int8_t		s8_t;
typedef int16_t		s16_t;
typedef int32_t		s32_t;

typedef size_t	mem_ptr_t;

#define U16_F "d"
#define S16_F "d"
#define X16_F "X"
#define U32_F "d"
#define S32_F "d"
#define X32_F "X"
#define SZT_F "X"

#define BYTE_ORDER LITTLE_ENDIAN

#define LWIP_PLATFORM_BYTESWAP 1
#define LWIP_PLATFORM_HTONS(x) ( (((u16_t)(x))>>8) | (((x)&0xFF)<<8) )
#define LWIP_PLATFORM_HTONL(x) ( (((u32_t)(x))>>24) | (((x)&0xFF0000)>>8) \
| (((x) & 0xFF00) << 8) | (((x) & 0xFF) << 24))

#define LWIP_CHKSUM_ALGORITHM 2

#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_FIELD(...) __VA_ARGS__

extern void CLockScheduler();
extern void CUnlockScheduler();
extern void CPrintf(const char* msg, ...);

#define LWIP_PLATFORM_DIAG(x, ...) CPrintf("LWIP MSG: %s", x);
#define LWIP_PLATFORM_ASSERT(x, ...) CPrintf("LWIP ERR: %s", x);


#define SYS_ARCH_PROTECT(x) CLockScheduler();
#define SYS_ARCH_UNPROTECT(x) CUnlockScheduler();
#define SYS_ARCH_DECL_PROTECT(x) 