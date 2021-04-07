#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/diskphys.hpp"
#include "hal/vcache.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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

int eject()
{
	printf("Eject called on non-removable medium.\n");
	return 1;
}