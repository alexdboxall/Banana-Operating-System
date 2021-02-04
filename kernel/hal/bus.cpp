#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/bus.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

Bus::Bus(const char* name) : Device(name)
{
	deviceType = DeviceType::Bus;
}

Bus::~Bus()
{

}