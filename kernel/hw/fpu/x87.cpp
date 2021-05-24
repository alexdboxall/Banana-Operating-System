#include "core/main.hpp"
#include "hw/cpu.hpp"
#include "hw/acpi.hpp"
#include "hw/fpu/x87.hpp"
#include <stdint.h>

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-omit-frame-pointer")

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

extern "C" size_t x87Detect();
extern "C" void x87Init();
extern "C" void x87Save(size_t ptr);
extern "C" void x87Load(size_t ptr);
extern "C" void x87Close();

x87::x87() : FPU("x87 FPU")
{

}

int x87::open(int num, int a, void* v)
{
    x87Init();
    return 0;
}

int x87::close(int a, int b, void* c)
{
    x87Close();
    return 0;
}

bool x87::available() {
    return x87Detect();
}

void x87::save(void* ptr) {
    x87Save((size_t) ptr);
}

void x87::load(void* ptr) {
    x87Load((size_t) ptr);
}

#pragma GCC diagnostic pop
