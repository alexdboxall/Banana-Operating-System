#include <krnl/panic.hpp>
#include <core/common.hpp>
#include <stdint.h>

// Alignment must be a power of 2.
#define is_aligned(value, alignment) !(value & (alignment - 1))

struct type_mismatch_info
{
	struct source_location location;
	struct type_descriptor* type;
	uintptr_t alignment;
	uint8_t type_check_kind;
};

const char* Type_Check_Kinds[] = {
	"load of",
	"store to",
	"reference binding to",
	"member access within",
	"member call on",
	"constructor call on",
	"downcast of",
	"downcast of",
	"upcast of",
	"cast to virtual base of",
};

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
}

extern "C" void __ubsan_handle_type_mismatch_v1(struct type_mismatch_info* type_mismatch, uintptr_t pointer)
{
	kprintf("__ubsan_handle_type_mismatch_v1\n");
	
	struct source_location* location = &type_mismatch->location;

	if (pointer == nullptr) {
		kprintf("Null pointer access\n");

	} else if (type_mismatch->alignment != 0 &&
		is_aligned(pointer, type_mismatch->alignment)) {
		kprintf("ubsan: Unaligned memory access\n");

	} else {
		kprintf("ubsan: Insufficient size\n");
		kprintf("ubsan: %s address %p with insufficient space for object of type %s\n",
			Type_Check_Kinds[type_mismatch->type_check_kind], (void*) pointer,
			type_mismatch->type->name);
	}

	KiUbsanPrintDetails("__ubsan_handle_type_mismatch_v1", type_mismatch);
	KePanic("__ubsan_handle_type_mismatch_v1");
}

extern "C" void __ubsan_handle_pointer_overflow(void* ptr)
{
	KiUbsanPrintDetails("__ubsan_handle_pointer_overflow", ptr);
	KePanic("__ubsan_handle_pointer_overflow");
}

extern "C" void __ubsan_handle_out_of_bounds(void* ptr)
{
	KiUbsanPrintDetails("__ubsan_handle_out_of_bounds", ptr);
	KePanic("__ubsan_handle_out_of_bounds");
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