#include <net/ethernet.hpp>
#include <stdint.h>

#define CRC_POLY    0xEDB88320

uint16_t KeSwitchEndian16(uint16_t nb)
{
	return (nb >> 8) | (nb << 8);
}

uint32_t KeSwitchEndian32(uint32_t nb)
{
	return ((nb >> 24) & 0xff) |
		((nb << 8) & 0xff0000) |
		((nb >> 8) & 0xff00) |
		((nb << 24) & 0xff000000);
}


//https://stackoverflow.com/questions/60684565/c-crc32-checksum-does-not-match-wireshark-on-ethernet-frame-check-sequence
uint32_t EthernetCRC32(uint8_t* data, int len)
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

#define ETHERNET_PACKET_TYPE_ARP	0x806
#define ETHERNET_PACKET_TYPE_IP		0x800

void EthernetReceivedPacket(EthernetUnwrappedFrame* data, uint16_t length)
{
	EthernetUnwrappedFrame* frame = (EthernetUnwrappedFrame*) data;

	if (frame->typeOrLength == ETHERNET_PACKET_TYPE_ARP) {
		kprintf("Recieved ARP packet.\n");

	} else if (frame->typeOrLength == ETHERNET_PACKET_TYPE_IP) {
		kprintf("Recieved IP packet.\n");
	}
}