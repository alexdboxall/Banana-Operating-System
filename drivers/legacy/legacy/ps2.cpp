#include "core/common.hpp"
#include "thr/elf.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "reg/registry.hpp"

#include "ps2port.hpp"
#include "ps2.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

char ps2ctrlname[] = "PS/2 Controller";
PS2::PS2() : Bus(ps2ctrlname)
{
	//claim the ports
	ports[noPorts].rangeStart = PS2_DATA;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = PS2_STATUS;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
}

#define PS2_UNKNOWN_PORTS	0
#define PS2_ONE_PORT		1
#define PS2_TWO_PORTS		2

int PS2::open(int a, int b, void* c)
{
	lockScheduler();

	int numPorts = PS2_UNKNOWN_PORTS;

	//disable devices to start
	controllerWrite(PS2_CMD_DISABLE_PORT_1);
	controllerWrite(PS2_CMD_DISABLE_PORT_2);

	//flush the output buffer
	inb(PS2_DATA);
	inb(PS2_DATA);
	inb(PS2_DATA);
	inb(PS2_DATA);

	//perform self test
	controllerWrite(PS2_CMD_TEST_CONTROLLER);

	//check for bad response byte
	uint8_t respByte = controllerRead();
	if (respByte != 0x55) {
		respByte = controllerRead();
		if (respByte != 0x55) {
			controllerWrite(PS2_CMD_TEST_CONTROLLER);
			controllerWrite(PS2_CMD_TEST_CONTROLLER);
			respByte = controllerRead();
			if (respByte != 0x55) {
				respByte = controllerRead();
			}
		}
		//panic("PS/2 NOT 0x55");
		//return 1;
	}

	//disable devices again, as the self test may have reset it
	//controllerWrite(PS2_CMD_DISABLE_PORT_1);
	//controllerWrite(PS2_CMD_DISABLE_PORT_2);

	//TODO: determine how many ports we have
	numPorts = PS2_TWO_PORTS;

	//get the config byte
	controllerWrite(PS2_CMD_READ_RAM);
	uint8_t cfg = controllerRead();

	//enable IRQs
	cfg |= PS2_CONFIG_BIT_PORT_1_IRQ_ENABLE;
	cfg |= PS2_CONFIG_BIT_PORT_2_IRQ_ENABLE;

	//write back the configuration byte
	controllerWrite(PS2_CMD_WRITE_RAM, cfg);

	//re-enable devices
	controllerWrite(PS2_CMD_ENABLE_PORT_1);
	controllerWrite(PS2_CMD_ENABLE_PORT_2);

	unlockScheduler();

	//add the first port
	devicePorts[PS2_PORT1] = new PS2Port();
	addChild(devicePorts[PS2_PORT1]);
	devicePorts[PS2_PORT1]->open(0, 0, nullptr);

	//add the second port if it exists
	if (numPorts == PS2_TWO_PORTS) {
		devicePorts[PS2_PORT2] = new PS2Port();
		addChild(devicePorts[PS2_PORT2]);
		devicePorts[PS2_PORT2]->open(PS2_PORT2, 0, nullptr);
	}

	return 0;
}

int PS2::close(int a, int b, void* c)
{
	return 0;
}

void PS2::detect()
{
	
}

bool PS2::controllerWrite(uint8_t command)
{
	//wait for input full to clear
	int timeout = 0;
	while (1) {
		//read the status
		uint8_t status = inb(PS2_STATUS);

		//check for any errors
		if ((status & PS2_STATUS_BIT_TIMEOUT) || (status & PS2_STATUS_BIT_PARITY)) {
			break;
		}

		//check if it is ready
		if (!(status & PS2_STATUS_BIT_IN_FULL)) {
			break;
		}

		//return failure on a timeout
		if (timeout++ == 800) {
			break;
		}
	}

	//write the command to the controller
	outb(PS2_COMMAND, command);

	return true;
}

bool PS2::controllerWrite(uint8_t command, uint8_t argument)
{
	controllerWrite(command);

	int timeout = 0;
	while (1) {
		//read the status
		uint8_t status = inb(PS2_STATUS);

		//check for any errors
		if ((status & PS2_STATUS_BIT_TIMEOUT) || (status & PS2_STATUS_BIT_PARITY)) {
			outb(PS2_DATA, argument);
			return false;
		}

		//check if it is ready
		if (!(status & PS2_STATUS_BIT_IN_FULL)) {
			break;
		}

		//return failure on a timeout
		if (timeout++ == 800) {
			outb(PS2_DATA, argument);
			return false;
		}
	}

	//now send the argument
	outb(PS2_DATA, argument);

	return true;
}

uint8_t PS2::controllerRead()
{
	uint32_t timeout = 0;

	while (1) {
		//read the status
		uint8_t status = inb(PS2_STATUS);

		//check for any errors
		if ((status & PS2_STATUS_BIT_TIMEOUT) || (status & PS2_STATUS_BIT_PARITY)) {
			return false;
		}

		//check if it is ready
		if (status & PS2_STATUS_BIT_OUT_FULL) {
			break;
		}
		
		//return failure on a timeout
		if (timeout++ == 1600) {
			return inb(PS2_DATA);
		}
	}

	return inb(PS2_DATA);
}

