#include <krnl/panic.hpp>
#include <stdint.h>

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