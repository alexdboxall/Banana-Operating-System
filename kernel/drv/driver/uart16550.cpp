#pragma once

#include <drv/driver/uart16550.hpp>
#include <krnl/panic.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

int UART16550::nextCOMNumber = 1;

const char comNames[9][48] = {
	"UART16550 Compatible Serial Port",
	"UART16550 Compatible Serial Port (COM1)",
	"UART16550 Compatible Serial Port (COM2)",
	"UART16550 Compatible Serial Port (COM3)",
	"UART16550 Compatible Serial Port (COM4)",
	"UART16550 Compatible Serial Port (COM5)",
	"UART16550 Compatible Serial Port (COM6)",
	"UART16550 Compatible Serial Port (COM7)",
	"UART16550 Compatible Serial Port (COM8)",
};

void UART16550::initialise()
{
	if (hw->connectionType == DeviceRootConnectionType::ISAManual) {
		base = hw->isamanual.probeBase[0];

	} else {
		KePanic("UART16550 is for ISA ports only");
	}

	hw->registerPortRange(base, 8, 1);

	comNumber = nextCOMNumber++;
}

void UART16550::detect()
{

}

void UART16550::deinitialise()
{

}

void UART16550::setPowerState(DevicePowerState state)
{

}

const char* UART16550::getHumanReadableName()
{
	if (comNumber >= 1 && comNumber <= 8) {
		return comNames[comNumber];
	} else {
		return comNames[0];
	}
}

bool UART16550::areInterruptsSupported()
{
	return true;
}

bool UART16550::areInterruptsEnabled()
{
	return irqsOn;
}

void UART16550::enableInterrupts(bool state)
{
	irqsOn = state;

	KePanic("TODO: set IRQ mode");
}

void UART16550::setBaud(int _baud)
{
	baud = getClosestSupportedBaud(_baud);

	KePanic("TODO: set baud");
}

int UART16550::getBaudDivisor(int baud)
{
	if (baud >= 115200) return 1;
	if (baud <= 0) return 65535;

	return 115200 / baud;
}

int UART16550::getClosestSupportedBaud(int baud)
{
	return 115200 / getBaudDivisor(baud);
}

int UART16550::getBaud()
{
	return baud;
}

void UART16550::write(uint8_t data)
{
	KePanic("UART16550::writeByte");
}

uint8_t UART16550::read()
{
	KePanic("UART16550::read");
}

int UART16550::getHardwareBufferSize()
{
	return 1;
}

int UART16550::getNumberBytesInIRQBuffer()
{
	return 0;
}

int UART16550::getMaximumBytesInIRQBuffer()
{
	return 0;
}

void UART16550::emptyBuffer()
{

}

void UART16550::waitForData()
{
	while (!isDataReady()) {
		;
	}
}

bool UART16550::isDataReady()
{
	KePanic("UART16550::isDataReady");
	return false;
}

void UART16550::setParityMode(SerialParityMode mode)
{
	if (!isParityModeSupported(mode)) return;

	parity = mode;
	KePanic("UART16550::setParityMode");
}

bool UART16550::isParityModeSupported(SerialParityMode mode)
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

SerialParityMode UART16550::getPartityMode()
{
	return parity;
}

void UART16550::setTransmissionSize(int size)
{
	if (!isTransmissionSizeValid(size)) return;
	transferSize = size;
	KePanic("UART16550::setTransmissionSize");
}

bool UART16550::isTransmissionSizeValid(int size)
{
	return size >= 5 && size <= 8;
}

int UART16550::getTransmissionSize()
{
	return transferSize;
}

void UART16550::setNumberOfStopBits(int size)
{
	if (!isNumberOfStopBitsValid(size)) return;
	numStopBits = size;

	KePanic("UART16550::setNumberOfStopBits");
}

bool UART16550::isNumberOfStopBitsValid(int size)
{
	return size == 1 || size == 2;
}

int UART16550::getNumberOfStopBits()
{
	return numStopBits;
}

bool UART16550::supportsHardwareStopBits()
{
	return true;
}

bool UART16550::supportsHardwareParity()
{
	return true;
}

bool UART16550::didAnyErrorsOccur()
{
	KePanic("UART16550::didAnyErrorsOccur");
	return false;
}

void UART16550::clearAllErrors()
{
	KePanic("UART16550::clearAllErrors");
}

void UART16550::clearFirstError()
{
	KePanic("UART16550::clearFirstError");
}

SerialErrorType UART16550::getFirstError()
{
	KePanic("UART16550::getFirstError");
	return SerialErrorType::UnknownError;
}