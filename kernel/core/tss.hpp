#pragma once

#ifndef _TSS_HPP_
#define _TSS_HPP_

#include <stdint.h>
#include <stddef.h>

struct TSSEntry
{
	uint16_t link;
	uint16_t reserved0;
	uint32_t esp0;
	uint16_t ss0;
	uint16_t reserved1;
	uint32_t esp1;
	uint16_t ss1;
	uint16_t reserved2;
	uint32_t esp2;
	uint16_t ss2;
	uint16_t reserved3;
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
	uint16_t es;
	uint16_t reserved4;
	uint16_t cs;
	uint16_t reserved5;
	uint16_t ss;
	uint16_t reserved6;
	uint16_t ds;
	uint16_t reserved7;
	uint16_t fs;
	uint16_t reserved8;
	uint16_t gs;
	uint16_t reserved9;
	uint16_t ldtr;
	uint16_t reserved10;
	uint16_t reserved11;
	uint16_t iopb;
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