
#ifndef _PS2_HPP_
#define _PS2_HPP_

#include <stdint.h>
#include "hal/bus.hpp"

#define PS2_DATA	0x60
#define PS2_STATUS	0x64
#define PS2_COMMAND	0x64

#define PS2_STATUS_BIT_OUT_FULL		1
#define PS2_STATUS_BIT_IN_FULL		2
#define PS2_STATUS_BIT_SYSFLAG		4
#define PS2_STATUS_BIT_CONTROLLER	8
#define PS2_STATUS_BIT_TIMEOUT		64
#define PS2_STATUS_BIT_PARITY		128

#define PS2_CMD_READ_RAM						0x20
#define PS2_CMD_WRITE_RAM						0x60
#define PS2_CMD_DISABLE_PORT_2					0xA7
#define PS2_CMD_ENABLE_PORT_2					0xA8
#define PS2_CMD_TEST_PORT_2						0xA9
#define PS2_CMD_TEST_CONTROLLER					0xAA
#define PS2_CMD_TEST_PORT_1						0xAB
#define PS2_CMD_DISABLE_PORT_1					0xAD
#define PS2_CMD_ENABLE_PORT_1					0xAE
#define PS2_CMD_READ_CONTROLLER_OUTPUT_PORT		0xD0
#define PS2_CMD_WRITE_CONTROLLER_OUTPUT_PORT	0xD1
#define PS2_CMD_WRITE_NEXT_TO_PORT_2_INPUT		0xD4

#define PS2_CONFIG_BIT_PORT_1_IRQ_ENABLE	1
#define PS2_CONFIG_BIT_PORT_2_IRQ_ENABLE	2
#define PS2_CONFIG_BIT_SYSFLAG				4
#define PS2_CONFIG_BIT_PORT_1_CLOCK_DISABLE	16
#define PS2_CONFIG_BIT_PORT_2_CLOCK_DISABLE	32
#define PS2_CONFIG_TRANSLATION_ENABLE		64

#define PS2_OUTPORT_BIT_RESET						1
#define PS2_OUTPORT_BIT_A20							2
#define PS2_OUTPORT_BIT_PORT_2_CLOCK				4
#define PS2_OUTPORT_BIT_PORT_2_DATA					8
#define PS2_OUTPORT_BIT_BUFFER_FULL_FROM_PORT_1		16
#define PS2_OUTPORT_BIT_BUFFER_FULL_FROM_PORT_2		32
#define PS2_OUTPORT_BIT_PORT_1_CLOCK				64
#define PS2_OUTPORT_BIT_PORT_1_DATA					128

#define PS2_DEV_CMD_IDENTIFY			0xF2
#define PS2_DEV_CMD_ENABLE_SCANNING		0xF4
#define PS2_DEV_CMD_DISABLE_SCANNING	0xF5
#define PS2_DEV_CMD_RESET				0xFF
#define PS2_DEV_CMD_RESEND				0xFE

#define PS2_PORT1	0
#define PS2_PORT2	1

class PS2Port;

class PS2: public Bus
{
private:

protected:

public:
	PS2();

	PS2Port* devicePorts[2];

	int open(int, int, void*);
	int close(int, int, void*);

	void detect();

	bool controllerWrite(uint8_t command);
	bool controllerWrite(uint8_t command, uint8_t argument);
	uint8_t controllerRead();
};

#endif