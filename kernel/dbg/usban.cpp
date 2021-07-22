#include <krnl/panic.hpp>
#include <core/common.hpp>
#include <stdint.h>

struct source_location
{
	const char* file;
	uint32_t line;
	uint32_t column;
};

void KiUbsanPrintDetails(const char* str, void* ptr)
{
	kprintf("UBSAN DETECTED: %s\n", str);

	source_location* src = (source_location*) ptr;
	kprintf("file: %s\n", src->file);
	kprintf("line: %d\n", src->line);
	kprintf("clmn: %d\n", src->column);

	KePanic(str);
}

extern "C" void __ubsan_handle_type_mismatch_v1(void* ptr)
{
	KiUbsanPrintDetails("__ubsan_handle_type_mismatch_v1", ptr);
}

extern "C" void __ubsan_handle_pointer_overflow(void* ptr)
{
	KiUbsanPrintDetails("__ubsan_handle_pointer_overflow", ptr);
}

extern "C" void __ubsan_handle_out_of_bounds(void* ptr)
{
	KiUbsanPrintDetails("__ubsan_handle_out_of_bounds", ptr);
}

extern "C" void __ubsan_handle_add_overflow() {
	KePanic("__ubsan_handle_add_overflow");
}

extern "C" void __ubsan_handle_load_invalid_value()
{
	KePanic("__ubsan_handle_load_invalid_value");
}

extern "C" void __ubsan_handle_divrem_overflow()
{
	KePanic("__ubsan_handle_divrem_overflow");
}

extern "C" void __ubsan_handle_mul_overflow()
{
	KePanic("__ubsan_handle_mul_overflow");
}

extern "C" void __ubsan_handle_sub_overflow()
{
	KePanic("__ubsan_handle_sub_overflow");
}

extern "C" void __ubsan_handle_shift_out_of_bounds()
{
	KePanic("__ubsan_handle_shift_out_of_bounds");
}

extern "C" void __ubsan_handle_negate_overflow()
{
	KePanic("__ubsan_handle_negate_overflow");
}