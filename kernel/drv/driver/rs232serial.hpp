#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/serial.hpp>

#include <stdint.h>

class RS232Serial : public SerialDriver
{
private:
	uint16_t base;
	SerialParityMode parity;
	int transferSize;
	int numStopBits;
	int baud;
	bool irqsOn;

	int getBaudDivisor(int baud);

public:
	RS232Serial()
	{

	}

	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();

	bool areInterruptsSupported();
	bool areInterruptsEnabled();
	void enableInterrupts(bool state = true);
	void setBaud(int baud);
	int getClosestSupportedBaud(int baud);
	int getBaud();
	void write(uint8_t data);
	uint8_t read();
	int getHardwareBufferSize();
	int getNumberBytesInIRQBuffer();
	int getMaximumBytesInIRQBuffer();
	void emptyBuffer();
	void waitForData();
	bool isDataReady();
	void setParityMode(SerialParityMode mode);
	bool isParityModeSupported(SerialParityMode mode);
	SerialParityMode getPartityMode();
	void setTransmissionSize(int size);
	bool isTransmissionSizeValid(int size);
	int getTransmissionSize();
	void setNumberOfStopBits(int size);
	bool isNumberOfStopBitsValid(int size);
	int getNumberOfStopBits();
	bool supportsHardwareStopBits();
	bool supportsHardwareParity();

	bool didAnyErrorsOccur();
	void clearAllErrors();
	void clearFirstError();
	SerialErrorType getFirstError();
};
