#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/diskctrl.hpp"
//#pragma GCC optimize ("Os")

HardDiskController::HardDiskController(const char* name) : Device(name)
{
	deviceType = DeviceType::HardDiskController;
}

HardDiskController::~HardDiskController()
{

}