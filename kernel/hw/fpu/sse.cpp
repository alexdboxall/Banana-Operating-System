#include "core/main.hpp"
#include "hw/acpi.hpp"
#include "hw/fpu/SSE.hpp"
#include <stdint.h>

extern "C" size_t sseDetect();
extern "C" void sseInit();
extern "C" void sseSave(size_t ptr);
extern "C" void sseLoad(size_t ptr);
extern "C" void sseClose();

SSE::SSE() : FPU("SSE FPU")
{

}

int SSE::open(int num, int a, void* v)
{
    sseInit();
    return 0;
}

int SSE::close(int a, int b, void* c)
{
    sseClose();

    return 0;
}

bool SSE::available() {
	bool b = sseDetect();
    return b;
}

void SSE::save(void* ptr) {
    sseSave((size_t) ptr);
}

void SSE::load(void* ptr) {
    sseLoad((size_t) ptr);
}
