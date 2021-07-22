#include <krnl/panic.hpp>

void __ubsan_handle_type_mismatch_v1()
{
	KePanic("__ubsan_handle_type_mismatch_v1");
}

void __ubsan_handle_pointer_overflow()
{
	KePanic("__ubsan_handle_pointer_overflow");
}

void __ubsan_handle_add_overflow() {
	KePanic("__ubsan_handle_add_overflow");
}

void __ubsan_handle_out_of_bounds()
{
	KePanic("__ubsan_handle_out_of_bounds");
}

void __ubsan_handle_load_invalid_value()
{
	KePanic("__ubsan_handle_load_invalid_value");
}