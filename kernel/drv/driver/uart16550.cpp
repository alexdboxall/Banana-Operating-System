#pragma once

#include <drv/driver/uart16550.hpp>
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define DATA_REGISTER						0x00	// with DLAB set to 0
#define INTERRUPT_ENABLE_REGISTER			0x01	// with DLAB set to 0
#define DIVISOR_LOW_REGISTER				0x00	// with DLAB set to 1
#define DIVISOR_HIGH_REGISTER				0x01	// with DLAB set to 1
#define FIFO_CONTROL_REGISTER				0x02
#define INTERRUPT_IDENTIFICATION_REGISTER	0x02
#define LINE_CONTROL_REGISTER				0x03
#define MODEM_CONTROL_REGISTER				0x04
#define LINE_STATUS_REGISTER				0x05
#define MODEM_STATUS_REGISTER				0x06
#define SCRATCH_REGISTER					0x07

#define MCR_DTR			0x01
#define MCR_RTS			0x02
#define MCR_AUX_1		0x04
#define MCR_AUX_2		0x08
#define MCR_LOOPBACK	0x10

#define LSR_DATA_READY		0x01
#define LSR_OVERRUN_ERROR	0x02
#define LSR_PARITY_ERROR	0x04
#define LSR_FRAMING_ERROR	0x08
#define LSR_BREAK_INTERRUPT	0x10
#define LSR_CAN_TRANSMIT	0x20

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

	// enable FIFO (14 byte buffer)
	outb(base + FIFO_CONTROL_REGISTER, 0xC7);

	// OUT#1 and OUT#2 enabled, RTS/DSR set
	modemControlRegData = 0x0F;
	outb(base + MODEM_CONTROL_REGISTER, modemControlRegData);

	disableInterrupts();
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

	if (irqsOn) {
		// enable all IRQs
		outb(base + INTERRUPT_ENABLE_REGISTER, 0xF);

	
	} else {
		// disable all IRQs
		outb(base + INTERRUPT_ENABLE_REGISTER, 0x0);
	}
}

void UART16550::recomputeLineControlRegister()
{
	uint8_t data = 0;

	if (breakConditionOn) {
		data |= 0x40;
	}

	switch (parity) {
	case SerialParityMode::None:
		break;
	case SerialParityMode::Odd:
		data |= 0b001 << 3;
		break;
	case SerialParityMode::Even:
		data |= 0b011 << 3;
		break;
	case SerialParityMode::One:
		data |= 0b101 << 3;
		break;
	case SerialParityMode::Zero:
		data |= 0b111 << 3;
		break;
	default:
		KePanic("INVALID UART PARITY MODE DETECTED IN INTERNAL FUNCTION");
	}

	if (numStopBits == 2) {
		data |= 0b100;
	}

	switch (transferSize) {
	case 5:
		break;
	case 6:
		data |= 1;
		break;
	case 7:
		data |= 2;
		break;
	case 8:
		data |= 3;
		break;
	default:
		KePanic("INVALID UART WORD LENGTH DETECTED IN INTERNAL FUNCTION");
	}

	outb(base + LINE_CONTROL_REGISTER, data);
}

void UART16550::setBaud(int _baud)
{
	uint16_t divisor = getBaudDivisor(baud);
	
	outb(base + LINE_CONTROL_REGISTER, 0x80);	// set DLAB
	outb(base + DIVISOR_LOW_REGISTER, divisor & 0xFF);
	outb(base + DIVISOR_HIGH_REGISTER, divisor >> 8);

	recomputeLineControlRegister();
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

bool UART16550::write(uint8_t data)
{
	if (inb(base + LINE_STATUS_REGISTER) & LSR_CAN_TRANSMIT) {
		outb(base + DATA_REGISTER, data);
		return true;

	} else {
		return false;
	}
}

void UART16550::fillIRQBuffer()
{
	while (inb(base + LINE_STATUS_REGISTER) & LSR_DATA_READY) {
		irqBuffer[irqBufferPosition + irqBufferBytesUsed++] = inb(base + DATA_REGISTER);
		
		if (irqBufferBytesUsed >= 256) {
			KePanic("TODO: UART16550 error handling");
			break;
		}
	}
}

uint8_t UART16550::read()
{
	while (irqBufferBytesUsed == 0) {
		lockScheduler();
		fillIRQBuffer();
		schedule();
		unlockScheduler();

	}

	uint8_t value = irqBuffer[irqBufferPosition++];
	irqBufferBytesUsed--;
	return value;
}

int UART16550::getHardwareBufferSize()
{
	return 14;
}

int UART16550::getNumberBytesInIRQBuffer()
{
	return irqBufferBytesUsed;
}

int UART16550::getMaximumBytesInIRQBuffer()
{
	return 256;
}

void UART16550::emptyBuffer()
{
	irqBufferBytesUsed = 0;

	// TODO: clear the FIFO buffer
}

void UART16550::waitForData()
{
	while (!isDataReady()) {
		lockScheduler();
		schedule();
		unlockScheduler();
	}
}

bool UART16550::isDataReady()
{
	if (irqBufferBytesUsed != 0) {
		return true;
	}

	return inb(base + LINE_STATUS_REGISTER) & LSR_DATA_READY;
}

void UART16550::setParityMode(SerialParityMode mode)
{
	if (!isParityModeSupported(mode)) return;

	parity = mode;
	recomputeLineControlRegister();
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
	recomputeLineControlRegister();
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
	recomputeLineControlRegister();
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

void UART16550::recomputeModemControlRegister()
{
	outb(base + MODEM_CONTROL_REGISTER, modemControlRegData);
}

void UART16550::enableBreak(bool on)
{
	breakConditionOn = on;
	recomputeLineControlRegister();
}

bool UART16550::isBreakOn()
{
	return breakConditionOn;
}

void UART16550::enableLookback(bool on)
{
	if (on) {
		modemControlRegData |= MCR_LOOPBACK;
	} else {
		modemControlRegData &= ~MCR_LOOPBACK;
	}
}

bool UART16550::isLoopbackOn()
{
	return modemControlRegData & MCR_LOOPBACK;
}

void UART16550::setDataTerminalRead(bool state)
{
	if (state) {
		modemControlRegData |= MCR_DTR;
	} else {
		modemControlRegData &= ~MCR_DTR;
	}
}

void UART16550::setRequestToSend(bool state)
{
	if (state) {
		modemControlRegData |= MCR_RTS;
	} else {
		modemControlRegData &= ~MCR_RTS;
	}
}

void UART16550::setAux1(bool state)
{
	if (state) {
		modemControlRegData |= MCR_AUX_1;
	} else {
		modemControlRegData &= ~MCR_AUX_1;
	}
}

void UART16550::setAux2(bool state)
{
	if (state) {
		modemControlRegData |= MCR_AUX_2;
	} else {
		modemControlRegData &= ~MCR_AUX_2;
	}
}