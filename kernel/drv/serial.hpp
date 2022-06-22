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
	TransmitterEmpty,
	BufferEmpty,
	HardwareFailure,
};

class SerialDriver : public Driver
{
public:
	SerialDriver()  {

	}

	SerialConfiguration getConfiguration()
	{
		SerialConfiguration config;
		config.baud = getBaud();
		config.parity = getPartityMode();
		config.stopBits = getNumberOfStopBits();
		config.transmissionSize = getTransmissionSize();
		config.interruptsEnabled = areInterruptsEnabled();
		config.expectsInterruptSupport = areInterruptsSupported();
		return config;
	}

	bool setConfiguration(SerialConfiguration config)
	{
		// check for invalid baud (configuration data should be precise)
		if (config.baud != getClosestSupportedBaud(config.baud)) {
			return false;
		}

		if (config.expectsInterruptSupport && !areInterruptsSupported()) {
			return false;
		}

		if (!isParityModeSupported(config.parity)) {
			return false;
		}

		if (!isTransmissionSizeValid(config.transmissionSize)) {
			return false;
		}

		if (!isNumberOfStopBitsValid(config.stopBits)) {
			return false;
		}

		setBaud(config.baud);
		setNumberOfStopBits(config.stopBits);
		setParityMode(config.parity);
		setTransmissionSize(config.transmissionSize);
		if (config.expectsInterruptSupport) {
			enableInterrupts(config.interruptsEnabled);
		}

		return true;
	}

	virtual bool areInterruptsSupported() = 0;
	virtual bool areInterruptsEnabled() = 0;
	virtual void enableInterrupts(bool state = true) = 0;
	virtual void setBaud(int baud) = 0;
	virtual int getClosestSupportedBaud(int baud) = 0;
	virtual int getBaud() = 0;
	virtual void write(uint8_t data) = 0;
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
		return HardwareType::Bus;
	}
	
public:
	SerialDriver* driver;

	SerialHardware() : Hardware()
	{
		driver = nullptr;
	}

	SerialHardware(SerialDriver* _driver) : Hardware()
	{
		driver = _driver;
		driver->hw = this;
		driver->initialise();
	}
};
