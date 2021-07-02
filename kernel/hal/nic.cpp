#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/nic.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

NIC::NIC(const char* name) : Device(name)
{
	deviceType = DeviceType::NIC;
}

NIC::~NIC()
{

}

//RETURNS IN BIG-ENDIAN
uint64_t NIC::getMAC()
{
	return 0;
}

int NIC::write(int len, uint8_t* data, int* br)
{
	return NS_UNIMPLEMENTED;
}