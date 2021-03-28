#ifndef _ETHERNET_HPP_
#define _ETHERNET_HPP_

#include <stdint.h>
#include <stddef.h>

typedef struct UnwrappedEthernetFrame
{
	uint8_t* data;
	uint32_t dataLength;

	uint8_t macSource[6];
	uint8_t macDest[6];

	uint16_t etherTypeOrLength;
	bool crcCorrect;


} UnwrappedEthernetFrame;

uint16_t switchEndian16(uint16_t nb);
uint32_t switchEndian32(uint32_t nb);

int wrapEthernetFrame (UnwrappedEthernetFrame input, uint8_t* outbuffer);				//returns PAYLOAD length
UnwrappedEthernetFrame unwrapEthernetFrame (uint8_t* input, int payloadLength = -1);	//takes in PAYLOAD length

#endif