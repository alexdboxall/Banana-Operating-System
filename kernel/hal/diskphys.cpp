#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/diskphys.hpp"
#include "hal/vcache.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

PhysicalDisk::PhysicalDisk(const char* name, int _sectorSize) : Device(name)
{
	deviceType = DeviceType::PhysicalDisk;
	sectorSize = _sectorSize;
	cache = nullptr;
}

void PhysicalDisk::startCache()
{
	cache = new VCache(this);
}

PhysicalDisk::~PhysicalDisk()
{

}
