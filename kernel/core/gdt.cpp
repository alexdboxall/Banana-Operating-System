#include "core/gdt.hpp"
#include "core/main.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

void GDTEntry::setBase(uint32_t base)
{
	baseLow = base & 0xFFFFFF;
	baseHigh = (base >> 24) & 0xFF;
}

void GDTEntry::setLimit(uint32_t limit)
{
	limitLow = limit & 0xFFFF;
	limitHigh = (limit >> 16) & 0xF;
}


GDT::GDT()
{
	entryCount = 0;
}

int GDT::addEntry(GDTEntry entry)
{
	entries[entryCount] = entry.val;
	return (entryCount++) * 8;
}

int GDT::getNumberOfEntries()
{
	return entryCount;
}

GDTDescriptor gdtDescr;

extern "C" void loadGDT();

void GDT::flush()
{
	gdtDescr.size = entryCount * 8 - 1;
	gdtDescr.offset = (size_t) (void*) entries;

	loadGDT();
}

void GDT::setup()
{
	GDTEntry null;
	null.setBase(0);
	null.setLimit(0);
	null.readWrite = 0;
	null.directionAndConforming = 0;
	null.access = 0;
	null.flags = 0;

	GDTEntry code;
	code.setBase(0);
	code.setLimit(PLATFORM_ID == 64 ? 0 : 0xFFFFFF);
	code.bit64 = PLATFORM_ID == 64;
	code.size = PLATFORM_ID != 64;
	code.gran = 1;
	code.readWrite = 1;
	code.priv = 0;
	code.present = 1;
	code.executable = 1;
	code.type = 1;
	code.directionAndConforming = 0;

	GDTEntry data;
	data.setBase(0);
	data.setLimit(PLATFORM_ID == 64 ? 0 : 0xFFFFFF);
	data.bit64 = PLATFORM_ID == 64;
	data.size = PLATFORM_ID != 64;
	data.gran = 1;
	data.readWrite = 1;
	data.priv = 0;
	data.present = 1;
	data.executable = 0;
	data.type = 1;
	data.directionAndConforming = 0;

	GDTEntry userCode = code;
	userCode.priv = 3;

	GDTEntry userData = data;
	userData.priv = 3;

	addEntry(null);
	addEntry(code);
	addEntry(data);
	addEntry(userCode);
	addEntry(userData);
	flush();
}