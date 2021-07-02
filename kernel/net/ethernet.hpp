#pragma once

#include <stdint.h>
#include <stddef.h>

struct EthernetUnwrappedFrame
{
	uint8_t macSource[6];
	uint8_t macDest[6];

	uint16_t typeOrLength;
	uint8_t* data;

};



void EthernetSendPacket();				
void EthernetReceivedPacket(uint8_t* data, uint16_t length);		//drivers call this