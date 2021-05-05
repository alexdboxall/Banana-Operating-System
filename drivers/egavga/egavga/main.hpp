#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <stdint.h>

#include "hal/device.hpp"
#include "hal/video.hpp"

#define REG_SEQ_ADDR		0x3C4
#define REG_SEQ_DATA		0x3C5

#define REG_CRTC_ADDR_0		0x3B4
#define REG_CRTC_DATA_0		0x3B5
#define REG_CRTC_ADDR_1		0x3D4
#define REG_CRTC_DATA_1		0x3D5

#define REG_GFX_ADDR		0x3CE
#define REG_GFX_DATA		0x3CF

#define REG_ATTRIB_ADDR_READ	0x3C0
#define REG_ATTRIB_ADDR_WRITE	0x3C0
#define REG_ATTRIB_DATA_READ	0x3C1
#define REG_ATTRIB_DATA_WRITE	0x3C0

#define REG_EXT_INPUT_STATUS_1_MONO		0x3BA
#define REG_EXT_INPUT_STATUS_1_COLOUR	0x3DA

enum class GfxReg: int
{
	SetReset = 0x00,
	EnableSetReset = 0x01,
	ColourCompare = 0x02,
	DataRotate = 0x03,
	ReadMapSelect = 0x04,
	GraphicsMode = 0x05,
	MiscGraphics = 0x06,
	ColourDontCare = 0x07,
	BitMask = 0x08
};

enum class SeqReg : int
{
	Reset = 0x00,
	ClockingMode = 0x01,
	MapMask = 0x02,
	CharacterMapSelect = 0x03,
	SequencerMemoryMode = 0x04,
};

enum class AttribReg: int
{
	Palette0 = 0x00,
	Palette1 = 0x01,
	Palette2 = 0x02,
	Palette3 = 0x03,
	Palette4 = 0x04,
	Palette5 = 0x05,
	Palette6 = 0x06,
	Palette7 = 0x07,
	Palette8 = 0x08,
	Palette9 = 0x09,
	PaletteA = 0x0A,
	PaletteB = 0x0B,
	PaletteC = 0x0C,
	PaletteD = 0x0D,
	PaletteE = 0x0E,
	PaletteF = 0x0F,
	AttributeModeControl = 0x10,
	OverscanColour = 0x11,
	ColourPlaneEnable = 0x12,
	HorizPixelPanning = 0x13,
	ColourSelect = 0x14,
};

enum class CRTCReg: int
{
	HorizTotal = 0x00,
	EndHorizDisplay = 0x01,
	StartHorizBlanking = 0x02,
	EndHorizBlanking = 0x03,
	StartHorizRetrace = 0x04,
	EndHorizRetrace = 0x05,
	VerticalTotal = 0x06,
	Overflow = 0x07,
	PresetRowScan = 0x08,
	MaximumScanline = 0x09,
	CursorStart = 0x0A,
	CursorEnd = 0x0B,
	StartAddrHigh = 0x0C,
	StartAddrLow = 0x0D,
	CursorLocationHigh = 0x0E,
	CursorLocationLow = 0x0F,
	VerticalRetraceStart = 0x10,
	VerticalRetraceEnd = 0x11,
	VerticalDisplayEnd = 0x12,
	Offset = 0x13,
	UnderlineLocation = 0x14,
	StartVerticalBlanking = 0x15,
	EndVerticalBlanking = 0x16,
	CRCTModeControl = 0x17,
	LineCompare = 0x18,
};

enum class ColReg
{
	DACAddrWriteMode,
	DACAddrReadMode,
	DACData,
	DACState,
};

enum class ExtReg
{
	MiscOutput,
	FeatureControl,
	InputStatus0,
	InputStatus1
};

class EGAVGA: public Video
{
private:

protected:
	bool ioAddressSelect = false;
	bool gotColour = true;

	bool hasUndocumentedFlopFlopStatus = false;
	void detectUndocumentedCRTC24();
	bool getUndocumentedCRTC24Bit();

	uint8_t accessAttrib(int offsetReg, uint8_t writeVal, bool write);
	uint8_t accessSeqGfxCRTC(int offsetReg, int addrReg, int dataReg, uint8_t writeVal, bool write);

	uint8_t readRegister(GfxReg reg);
	uint8_t readRegister(SeqReg reg);
	uint8_t readRegister(AttribReg reg);
	uint8_t readRegister(CRTCReg reg);
	uint8_t readRegister(ColReg reg);
	uint8_t readRegister(ExtReg reg);

	void writeRegister(GfxReg reg, uint8_t val);
	void writeRegister(SeqReg reg, uint8_t val);
	void writeRegister(AttribReg reg, uint8_t val);
	void writeRegister(CRTCReg reg, uint8_t val);
	void writeRegister(ColReg reg, uint8_t val);
	void writeRegister(ExtReg reg, uint8_t val);

	uint8_t vinb(uint16_t port);
	void voutb(uint16_t port, uint8_t val);

public:
	EGAVGA();

	void init();

	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands
};

#endif