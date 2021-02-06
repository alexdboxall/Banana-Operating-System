#pragma once

#ifndef _TSS_HPP_
#define _TSS_HPP_

#include <stdint.h>
#include <stddef.h>

struct TSSEntry
{
	uint32_t reserved;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldtr;
	uint16_t reserved2;
	uint32_t iopb;
};

class TSS
{
private:

protected:
	int gdtEntry;
	TSSEntry* entry = nullptr;

public:
	TSS();
	void flush();
	void setESP(size_t esp);
	int setup(size_t esp, size_t eip = 0);
};

#endif