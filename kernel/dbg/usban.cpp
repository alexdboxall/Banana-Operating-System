#include <krnl/panic.hpp>
#include <stdint.h>

struct source_location
{
    const char* file;
    uint32_t line;
    uint32_t column;
};

struct type_descriptor
{
    uint16_t kind;
    uint16_t info;
    char name[];
};

struct type_mismatch_info
{
    struct source_location location;
    struct type_descriptor* type;
    uintptr_t alignment;
    uint8_t type_check_kind;
};

struct out_of_bounds_info
{
    struct source_location location;
    struct type_descriptor left_type;
    struct type_descriptor right_type;
};

extern "C" void __ubsan_handle_type_mismatch_v1()
{
	KePanic("__ubsan_handle_type_mismatch_v1");
}

extern "C" void __ubsan_handle_pointer_overflow()
{
	KePanic("__ubsan_handle_pointer_overflow");
}

extern "C" void __ubsan_handle_add_overflow() {
	KePanic("__ubsan_handle_add_overflow");
}

extern "C" void __ubsan_handle_out_of_bounds()
{
	KePanic("__ubsan_handle_out_of_bounds");
}

extern "C" void __ubsan_handle_load_invalid_value()
{
	KePanic("__ubsan_handle_load_invalid_value");
}