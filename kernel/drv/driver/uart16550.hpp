#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/serial.hpp>

#include <stdint.h>

class UART16550 : public SerialDriver
{
private:
	uint16_t base;
	SerialParityMode parity;
	int transferSize;
	int numStopBits;
	int baud;
	bool irqsOn;
	bool breakConditionOn = false;
	
	uint8_t modemControlRegData;
	
	int getBaudDivisor(int baud);
	void recomputeLineControlRegister();
	void recomputeModemControlRegister();
	
	static int nextCOMNumber;
	int comNumber;
	
	uint8_t irqBuffer[256];
	uint8_t irqBufferPosition = 0;
	int irqBufferBytesUsed = 0;

	void fillIRQBuffer();
	
public:
	UART16550()
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
	bool write(uint8_t data);
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

	void enableBreak(bool on = true);
	bool isBreakOn();
	void enableLookback(bool on = true);
	bool isLoopbackOn();
	void setDataTerminalRead(bool state);
	void setRequestToSend(bool state);
	void setAux1(bool state);
	void setAux2(bool state);
};
