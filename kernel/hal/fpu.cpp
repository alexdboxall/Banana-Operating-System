#include "core/common.hpp"
#include "hal/device.hpp"
#include "hal/fpu.hpp"

#include "hw/fpu/x87.hpp"
#include "hw/fpu/sse.hpp"
#include "hw/fpu/avx.hpp"
#include "hw/fpu/mmx.hpp"
//#pragma GCC optimize ("Os")

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
	
#ifdef JUMPER32
	return (FPU*) new x87();
#endif
    
    panic("NO FPU!");
	return nullptr;
}
