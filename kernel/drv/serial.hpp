#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <stdint.h>

enum class SerialParityMode : int
{
	None,
	Zero,
	One,
	Odd,
	Even
};

struct SerialConfiguration
{
	int baud;
	SerialParityMode parity;

	uint8_t transmissionSize;
	uint8_t stopBits;
	bool interruptsEnabled;
	bool expectsInterruptSupport;
};

enum class SerialErrorType
{
	NoError,
	UnknownError,
	UnknownSenderError,
	UnknownReceiverError,
	DataLost,
	ParityError,
	StopBitError,
	HardwareFailure,
};

class SerialDriver : public Driver
{
public:
	SerialDriver()  {

	}

	virtual bool areInterruptsSupported() = 0;
	virtual bool areInterruptsEnabled() = 0;
	virtual void enableInterrupts(bool state = true) = 0;
	virtual void setBaud(int baud) = 0;
	virtual int getClosestSupportedBaud(int baud) = 0;
	virtual int getBaud() = 0;
	virtual bool write(uint8_t data) = 0;
	virtual uint8_t read() = 0;
	virtual int getHardwareBufferSize() = 0;
	virtual int getNumberBytesInIRQBuffer() = 0;
	virtual int getMaximumBytesInIRQBuffer() = 0;
	virtual void emptyBuffer() = 0;
	virtual void waitForData() = 0;
	virtual bool isDataReady() = 0;
	virtual void setParityMode(SerialParityMode mode) = 0;
	virtual bool isParityModeSupported(SerialParityMode mode) = 0;
	virtual SerialParityMode getPartityMode() = 0;
	virtual void setTransmissionSize(int size) = 0;
	virtual bool isTransmissionSizeValid(int size) = 0;
	virtual int getTransmissionSize() = 0;
	virtual void setNumberOfStopBits(int size) = 0;
	virtual bool isNumberOfStopBitsValid(int size) = 0;
	virtual int getNumberOfStopBits() = 0;
	virtual bool supportsHardwareStopBits() = 0;
	virtual bool supportsHardwareParity() = 0;

	virtual bool didAnyErrorsOccur() = 0;
	virtual void clearAllErrors() = 0;
	virtual void clearFirstError() = 0;
	virtual SerialErrorType getFirstError() = 0;


	virtual void enableBreak(bool on = true) = 0;
	virtual bool isBreakOn() = 0;
	virtual void enableLookback(bool on = true) = 0;
	virtual bool isLoopbackOn() = 0;
	virtual void setDataTerminalRead(bool state) = 0;
	virtual void setRequestToSend(bool state) = 0;
	virtual void setAux1(bool state) = 0;
	virtual void setAux2(bool state) = 0;

	void disableLoopback()
	{
		enableLookback(false);
	}

	void disableBreak()
	{
		enableBreak(false);
	}
	
	void disableInterrupts()
	{
		enableInterrupts(false);
	}
};

class SerialHardware : public Hardware
{
protected:
	virtual Driver* _getDriver() override
	{
		return (Driver*) driver;
	}

	HardwareType getType()
	{
		return HardwareType::SerialPort;
	}
	
public:
	SerialDriver* driver;

	SerialHardware() : Hardware()
	{
		driver = nullptr;
	}

	void setDriver(SerialDriver* _driver)
	{
		driver = _driver;
		driver->hw = this;
		driver->initialise();
	}
};
