#include "core/main.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "hw/fpu/AVX.hpp"
#include <stdint.h>

extern "C" size_t avxDetect();
extern "C" void avxInit();
extern "C" void avxSave(size_t ptr);
extern "C" void avxLoad(size_t ptr);
extern "C" void avxClose();

AVX::AVX() : FPU("AVX FPU")
{

}


int AVX::open(int num, int a, void* v)
{
    avxInit();
    return 0;
}

int AVX::close(int a, int b, void* c)
{
    avxClose();
    return 0;
}

bool AVX::available() {
    return avxDetect();
}

void AVX::save(void* ptr) {
    avxSave((size_t) ptr);
}

void AVX::load(void* ptr) {
    avxLoad((size_t) ptr);
}