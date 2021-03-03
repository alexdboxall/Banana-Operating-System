#include "core/common.hpp"
#include "hal/device.hpp"
#include "hal/cpu.hpp"
#include "hal/fpu.hpp"

#include "hw/fpu/x87.hpp"
#include "hw/fpu/sse.hpp"
#include "hw/fpu/avx.hpp"
#include "hw/fpu/mmx.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

FPU::FPU(const char* name) : Device(name)
{
    deviceType = DeviceType::FPU;
}

FPU::~FPU()
{

}

FPU* setupFPU() {

	if (computer->features.hasAVX) {
		return (FPU*) new AVX();
	}

	if (computer->features.hasSSE) {
		return (FPU*) new SSE();
	}

	if (computer->features.hasMMX) {
		return (FPU*) new MMX();
	}

	if (computer->features.hasx87) {
		return (FPU*) new x87();
	}

	kprintf("NO FPU!\n");

	//turn on x87 emulation
	thisCPU()->writeCR0(thisCPU()->readCR0() | 4);
    
	return nullptr;
}
