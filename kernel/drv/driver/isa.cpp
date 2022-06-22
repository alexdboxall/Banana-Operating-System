#pragma once

#include <drv/driver/isa.hpp>

void ISADriver::initialise()
{

}

void ISADriver::detect()
{

}

void ISADriver::deinitialise()
{

}

void ISADriver::setPowerState(DevicePowerState state)
{

}

const char* ISADriver::getHumanReadableName()
{
	return ISA_DRIVER_NAME;
}