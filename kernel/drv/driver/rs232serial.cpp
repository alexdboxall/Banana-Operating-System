#pragma once

#include <drv/driver/rs232serial.hpp>
#include <krnl/panic.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void RS232Serial::initialise()
{
	if (hw->connectionType == DeviceRootConnectionType::ISAManual) {
		base = hw->isamanual.probeBase[0];

	} else {
		KePanic("RS232Serial is for ISA ports only");
	}
}

void RS232Serial::detect()
{

}

void RS232Serial::deinitialise()
{

}

void RS232Serial::setPowerState(DevicePowerState state)
{

}

const char* RS232Serial::getHumanReadableName()
{
	return "RS-232 Compatible Serial Port";
}

bool RS232Serial::areInterruptsSupported()
{
	return true;
}

bool RS232Serial::areInterruptsEnabled()
{
	return irqsOn;
}

void RS232Serial::enableInterrupts(bool state)
{
	irqsOn = state;

	KePanic("TODO: set IRQ mode");
}

void RS232Serial::setBaud(int _baud)
{
	baud = getClosestSupportedBaud(_baud);

	KePanic("TODO: set baud");
}

int RS232Serial::getBaudDivisor(int baud)
{
	if (baud >= 115200) return 1;
	if (baud <= 0) return 65535;

	return 115200 / baud;
}

int RS232Serial::getClosestSupportedBaud(int baud)
{
	return 115200 / getBaudDivisor(baud);
}

int RS232Serial::getBaud()
{
	return baud;
}

void RS232Serial::write(uint8_t data)
{
	KePanic("RS232Serial::writeByte");
}

uint8_t RS232Serial::read()
{
	KePanic("RS232Serial::read");
}

int RS232Serial::getHardwareBufferSize()
{
	return 1;
}

int RS232Serial::getNumberBytesInIRQBuffer()
{
	return 0;
}

int RS232Serial::getMaximumBytesInIRQBuffer()
{
	return 0;
}

void RS232Serial::emptyBuffer()
{

}

void RS232Serial::waitForData()
{
	while (!isDataReady()) {
		;
	}
}

bool RS232Serial::isDataReady()
{
	KePanic("RS232Serial::isDataReady");
	return false;
}

void RS232Serial::setParityMode(SerialParityMode mode)
{
	if (!isParityModeSupported(mode)) return;

	parity = mode;
	KePanic("RS232Serial::setParityMode");
}

bool RS232Serial::isParityModeSupported(SerialParityMode mode)
{
	switch (mode) {
	case SerialParityMode::None:
	case SerialParityMode::Zero:
	case SerialParityMode::One:
	case SerialParityMode::Odd:
	case SerialParityMode::Even:
		return true;
	default:
		// may in the future, new parity modes will be added to the list
		return false;
	}
}

SerialParityMode RS232Serial::getPartityMode()
{
	return parity;
}

void RS232Serial::setTransmissionSize(int size)
{
	if (!isTransmissionSizeValid(size)) return;
	transferSize = size;
	KePanic("RS232Serial::setTransmissionSize");
}

bool RS232Serial::isTransmissionSizeValid(int size)
{
	return size >= 5 && size <= 8;
}

int RS232Serial::getTransmissionSize()
{
	return transferSize;
}

void RS232Serial::setNumberOfStopBits(int size)
{
	if (!isNumberOfStopBitsValid(size)) return;
	numStopBits = size;

	KePanic("RS232Serial::setNumberOfStopBits");
}

bool RS232Serial::isNumberOfStopBitsValid(int size)
{
	return size == 1 || size == 2;
}

int RS232Serial::getNumberOfStopBits()
{
	return numStopBits;
}

bool RS232Serial::supportsHardwareStopBits()
{
	return true;
}

bool RS232Serial::supportsHardwareParity()
{
	return true;
}

bool RS232Serial::didAnyErrorsOccur()
{
	KePanic("RS232Serial::didAnyErrorsOccur");
	return false;
}

void RS232Serial::clearAllErrors()
{
	KePanic("RS232Serial::clearAllErrors");
}

void RS232Serial::clearFirstError()
{
	KePanic("RS232Serial::clearFirstError");
}

SerialErrorType RS232Serial::getFirstError()
{
	KePanic("RS232Serial::getFirstError");
	return SerialErrorType::UnknownError;
}