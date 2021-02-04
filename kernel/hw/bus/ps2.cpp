#include "core/common.hpp"
#include "core/elf.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hw/bus/ps2.hpp"
#include "registry/registry.hpp"
#include "hw/bus/ps2port.hpp"

//#pragma GCC optimize ("Os")

PS2::PS2() : Bus("PS/2 Controller")
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
	int numPorts = PS2_UNKNOWN_PORTS;

	//disable devices to start
	//controllerWrite(PS2_CMD_DISABLE_PORT_1);
	//controllerWrite(PS2_CMD_DISABLE_PORT_2);

	//flush the output buffer
	inb(PS2_DATA);

	//perform self test
	controllerWrite(PS2_CMD_TEST_CONTROLLER);

	//check for bad response byte
	if (controllerRead() != 0x55) {
		return 1;
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

	//re-enable devices
	//controllerWrite(PS2_CMD_ENABLE_PORT_1);
	//controllerWrite(PS2_CMD_ENABLE_PORT_1);

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
	//write the command to the controller
	outb(PS2_COMMAND, command);

	return true;
}

bool PS2::controllerWrite(uint8_t command, uint8_t argument)
{
	//write the command to the controller
	outb(PS2_COMMAND, command);

	int timeout = 0;
	while (1) {
		//read the status
		uint8_t status = inb(PS2_STATUS);

		//check for any errors
		if ((status & PS2_STATUS_BIT_TIMEOUT) || (status & PS2_STATUS_BIT_PARITY)) {
			return false;
		}

		//check if it is ready
		if (!(status & PS2_STATUS_BIT_IN_FULL)) {
			break;
		}

		//return failure on a timeout
		if (timeout++ == 800) {
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
		if (timeout++ == 800) {
			return false;
		}
	}

	return inb(PS2_DATA);
}
