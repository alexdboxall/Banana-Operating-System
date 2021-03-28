#include "net/ethernet.hpp"
#include "core/common.hpp"
extern "C" {
	#include "libk/string.h"
}

namespace Net
{
	uint16_t switchEndian16(uint16_t nb)
	{
		return (nb >> 8) | (nb << 8);
	}

	uint32_t switchEndian32(uint32_t nb)
	{
		return ((nb >> 24) & 0xff) |
			((nb << 8) & 0xff0000) |
			((nb >> 8) & 0xff00) |
			((nb << 24) & 0xff000000);
	}

#define CRC_POLY    0xEDB88320

	//https://stackoverflow.com/questions/60684565/c-crc32-checksum-does-not-match-wireshark-on-ethernet-frame-check-sequence
	uint32_t crc32Calc(uint8_t* data, int len)
	{
		int i, j;
		uint32_t crc;

		if (!data)
			return 0;

		if (len < 1)
			return 0;

		crc = 0xFFFFFFFF;

		for (j = 0; j < len; j++) {
			crc ^= data[j];

			for (i = 0; i < 8; i++) {
				crc = (crc & 1) ? ((crc >> 1) ^ CRC_POLY) : (crc >> 1);
			}
		}

		return (crc ^ 0xFFFFFFFF);
	}

	int wrapEthernetFrame(UnwrappedEthernetFrame input, uint8_t* outbuffer)
	{
		uint8_t* originalBuffer = outbuffer;

		//send the preamble
		for (int i = 0; i < 7; ++i) {
			*outbuffer++ = 0b10101010;
		}

		//frame delimiter (has two 1s on the end)
		*outbuffer++ = 0b10101011;

		//dest MAC
		memcpy(outbuffer, input.macDest, 6);
		outbuffer += 6;

		//source MAC
		memcpy(outbuffer, input.macSource, 6);
		outbuffer += 6;

		*outbuffer++ = input.etherTypeOrLength >> 8;		//MSB comes first over Ethernet
		*outbuffer++ = input.etherTypeOrLength & 0xFF;		//LSB comes last over Ethernet

		memcpy(outbuffer, input.data, input.dataLength);
		outbuffer += input.dataLength;

		uint32_t crc = crc32Calc(originalBuffer, outbuffer - originalBuffer);

		//again MSB comes first
		*outbuffer++ = (crc >> 24) & 0xFF;
		*outbuffer++ = (crc >> 16) & 0xFF;
		*outbuffer++ = (crc >> 8) & 0xFF;
		*outbuffer++ = (crc >> 0) & 0xFF;

		return input.dataLength;
	}

	UnwrappedEthernetFrame unwrapEthernetFrame(uint8_t* input, int payloadLength)
	{
		UnwrappedEthernetFrame unwrapped;
		uint8_t* originalInput = input;

		input += 8;
		memcpy(unwrapped.macDest, input, 6);
		input += 6;
		memcpy(unwrapped.macSource, input, 6);
		input += 6;

		uint16_t high = *input++;
		uint16_t low = *input++;

		unwrapped.etherTypeOrLength = (high << 8) | low;

		if (payloadLength == -1) {
			if (unwrapped.etherTypeOrLength <= 1500) {
				payloadLength = unwrapped.etherTypeOrLength;
			} else {
				kprintf("WORK OUT WHAT TO DO WITH PACKET WITH ETHERTYPE > 1500 AND NO GIVEN LENGTH!\n");
				unwrapped.crcCorrect = false;
				return unwrapped;
			}
		}

		memcpy(unwrapped.data, input, payloadLength);
		input += payloadLength;

		uint32_t b1 = *input++;
		uint32_t b2 = *input++;
		uint32_t b3 = *input++;
		uint32_t b4 = *input++;
		uint32_t crc = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;

		unwrapped.crcCorrect = crc32Calc(originalInput, input - originalInput - 4) == crc;

		return unwrapped;
	}
}