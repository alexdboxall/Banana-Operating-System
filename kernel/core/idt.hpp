#ifndef _IDT_HPP_
#define _IDT_HPP_

#include <stdint.h>
#include <stddef.h>

struct IDTEntry
{
	union
	{
		struct
		{
			uint64_t offsetLow : 16;
			uint64_t selector : 16;
			uint64_t mustBeZero : 8;
			uint64_t type : 4;
			uint64_t storageSegment : 1;
			uint64_t priv : 2;
			uint64_t present : 1;
			uint64_t offsetHigh : 16;
		};

		uint64_t val;
	};
	

	IDTEntry(bool userspaceAllowed = false);
	void setOffset (uint32_t val);
};

#pragma pack(push,1)
struct IDTDescriptor
{
	uint16_t size;
	size_t offset;

};

#pragma pack(pop)

class IDT
{
private:

protected:
	uint64_t entries[256];

public:
	size_t getPointerToInvalidOpcodeEntryForF00F();

	IDT();
	void addEntry(IDTEntry entry, int num);
	void addEntry(int num, void (*offset)(), bool userspace = false);
	void flush();
	void setup();
};


#endif