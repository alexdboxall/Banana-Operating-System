
#ifndef _IDE_HPP_
#define _IDE_HPP_

#ifndef JUMPER32

#include <stdint.h>
#include "hal/diskctrl.hpp"
#include "hw/bus/pci.hpp"

#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_STATUS	   0x07
#define ATA_REG_COMMAND    0x07

#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B

#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

#define ATA_REG_BUSMSTR_COMMAND		0x0E
#define ATA_REG_BUSMSTR_STATUS		0x10
#define ATA_REG_BUSMSTR_PRDT0		0x12
#define ATA_REG_BUSMSTR_PRDT1		0x13
#define ATA_REG_BUSMSTR_PRDT2		0x14
#define ATA_REG_BUSMSTR_PRDT3		0x15

#define ATA_PRIMARY        0x00
#define ATA_SECONDARY      0x01
#define ATA_READ           0x00
#define ATA_WRITE          0x01

#define IDE_ATA            0x00
#define IDE_ATAPI          0x01

#define ATA_MASTER         0x00
#define ATA_SLAVE          0x01

#define ATAPI_CMD_TEST_UNIT_READY	0x00
#define ATAPI_CMD_EJECT				0x1B
#define ATAPI_CMD_REQUEST_SENSE		0x03
#define ATAPI_CMD_READ				0xA8

#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define ATA_ER_BBK      0x80    // Bad sector
#define ATA_ER_UNC      0x40    // Uncorrectable data
#define ATA_ER_MC       0x20    // No media
#define ATA_ER_IDNF     0x10    // ID mark not found
#define ATA_ER_MCR      0x08    // No media
#define ATA_ER_ABRT     0x04    // Command aborted
#define ATA_ER_TK0NF    0x02    // Track 0 not found
#define ATA_ER_AMNF     0x01    // No address mark

#define ATA_SR_BSY      0x80    // Busy
#define ATA_SR_DRDY     0x40    // Drive ready
#define ATA_SR_DF       0x20    // Drive write fault
#define ATA_SR_DSC      0x10    // Drive seek complete
#define ATA_SR_DRQ      0x08    // Data request ready
#define ATA_SR_CORR     0x04    // Corrected data
#define ATA_SR_IDX      0x02    // Inlex
#define ATA_SR_ERR      0x01    // Error


class IDE: public HardDiskController
{
private:

protected:
	friend void ideChannel0IRQHandler(regs* r, void* context);
	friend void ideChannel1IRQHandler(regs* r, void* context);

	bool detectDone = false;

	struct IDEChannels
	{
		uint16_t base;
		uint16_t ctrl;
		uint16_t busMastering;
		uint8_t nIEN;

	} channels[2];

public:
	struct IDEDevice
	{
		unsigned char  reserved;    // 0 (Empty) or 1 (This Drive really exists).
		unsigned char  channel;     // 0 (Primary Channel) or 1 (Secondary Channel).
		unsigned char  drive;       // 0 (Master Drive) or 1 (Slave Drive).
		unsigned short type;        // 0: ATA, 1:ATAPI.
		unsigned short signature;   // Drive Signature
		unsigned short capabilities;// Features.
		unsigned int   commandSets; // Command Sets Supported.
		unsigned int   size;        // Size in Sectors.
		unsigned char  model[41];   // Model in string.

		bool hasLBA;
		bool hasLBA48;
		bool hasDMA;

	} devices[4];

	volatile bool irqInvoked[2];
	
	bool legacyIRQs;

	void enableIRQs(uint8_t channel, bool on);

	IDE();

	void selectDrive(uint8_t channel, uint8_t drive);

	void prepareInterrupt(uint8_t channel);
	bool waitInterrupt(uint8_t channel);

	uint16_t getBase(uint8_t channel);

	uint8_t read(uint8_t channel, uint8_t reg);
	void write(uint8_t channel, uint8_t reg, uint8_t data);
	void readBuffer(uint8_t channel, uint8_t reg, uint32_t buffer, uint32_t quads);
	uint8_t polling(uint8_t channel, uint32_t advanced_check);
	uint8_t printError(uint8_t channel, uint8_t drive, uint8_t err);

	int open(int, int, void*);
	int close(int, int, void*);

	void detect();
};

#endif

#endif