#include "core/main.hpp"
#include "hw/acpi.hpp"
#include "hw/fpu/mmx.hpp"
#include "core/computer.hpp"
#include <stdint.h>

extern "C" size_t x87Detect();
extern "C" void x87Init();
extern "C" void x87Save(size_t ptr);
extern "C" void x87Load(size_t ptr);
extern "C" void x87Close();

MMX::MMX() : FPU("MMX FPU")
{

}

int MMX::open(int num, int a, void* v)
{
    x87Init();
    return 0;
}

int MMX::close(int a, int b, void* c)
{
    x87Close();
    return 0;
}

bool MMX::available() {
	return computer->features.hasMMX;
}

void MMX::save(void* ptr) {
    x87Save((size_t) ptr);
}

void MMX::load(void* ptr) {
    x87Load((size_t) ptr);
}