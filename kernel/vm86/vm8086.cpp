#include "vm86/vm8086.hpp"
#include "fs/vfs.hpp"
#include "hw/ports.hpp"
#include "core/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"
//
//
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

extern "C" {
	#include "libk/string.h"
}

extern "C" void goToVM86(size_t ip, size_t cs, size_t sp, size_t ss);

uint8_t inbv(uint16_t port)
{
	//kprintf("VM8086 INB 0x%X\n", port);
	return inb(port);
}

void outbv(uint16_t port, uint8_t val)
{
	//kprintf("VM8086 OUTB 0x%X, 0x%X\n", port, val);
	outb(port, val);
}

void vm8086EntryPoint(void* v)
{
	unlockScheduler();
	asm("sti");
	goToVM86(currentTaskTCB->vm86IP, currentTaskTCB->vm86CS, currentTaskTCB->vm86SP, currentTaskTCB->vm86SS);
}

uint32_t realToLinear(uint16_t seg, uint16_t off)
{
	return (((uint32_t) seg) << 4) + ((uint32_t) off);
}

uint16_t getSegment(uint32_t linear)
{
	return linear >> 16;
}

uint16_t getOffset(uint32_t linear)
{
	return linear & 0xFFFF;
}

bool loadVM8086FileAsThread(Process* p, const char* filename, uint16_t ip, uint16_t cs, uint16_t sp, uint16_t ss)
{
	lockScheduler();
	ThreadControlBlock* thread = p->createThread(vm8086EntryPoint, nullptr, 128);
	thread->vm86IP = ip;
	thread->vm86CS = cs;
	thread->vm86SP = sp;
	thread->vm86SS = ss;
	thread->vm86Task = true;

	File* f = new File(filename, p);
	if (!f) {
		panic("VM8086 FILE FAILED!");
		unlockScheduler();
		return false;
	}

	uint64_t siz;
	bool dir;
	f->stat(&siz, &dir);

	if (dir) {
		panic("VM8086 FILE STAT FAILED!");
		unlockScheduler();
		return false;
	}

	FileStatus st = f->open(FileOpenMode::Read);

	if (st != FileStatus::Success) {
		panic("VM8086 FILE OPEN FAILED!");
		unlockScheduler();
		return false;
	}

	p->vas->mapRange(0x0, 0x0, 256, PAGE_PRESENT | PAGE_USER | PAGE_WRITABLE);

	int br;
	f->read(siz, (uint8_t*) (size_t) realToLinear(cs, ip), &br);
	f->close();

	unlockScheduler();

	return true;
}

void vm8086DoISR(regs* r, int irqN, uint8_t* ip, uint16_t ss, uint16_t sp)
{
	uint16_t* ivt = (uint16_t*) (size_t) 0;
	sp -= 6;
	uint16_t* stack = (uint16_t*) (size_t) realToLinear(ss, sp);
	r->useresp = (r->useresp - 6) & 0xFFFF;

	stack[0] = r->eip + 2;
	stack[1] = r->cs;
	stack[2] = r->eflags;

	if (currentTaskTCB->vm86VIE) {
		stack[2] |= 0x200;
	} else {
		stack[2] &= ~0x200;
	}

	currentTaskTCB->vm86VIE = false;
	r->cs = ivt[irqN * 2 + 1];
	r->eip = ivt[irqN * 2 + 0];
}

uint8_t readByteFromReal(uint16_t seg, uint16_t off)
{
	uint8_t* ptr = (uint8_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	return *ptr;
}

uint16_t readWordFromReal(uint16_t seg, uint16_t off)
{
	uint16_t* ptr = (uint16_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	return *ptr;
}

uint32_t readDwordFromReal(uint16_t seg, uint16_t off)
{
	uint32_t* ptr = (uint32_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	return *ptr;
}

void writeByteFromReal(uint16_t seg, uint16_t off, uint8_t byte)
{
	uint8_t* ptr = (uint8_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	*ptr = byte;
}

void writeWordFromReal(uint16_t seg, uint16_t off, uint16_t byte)
{
	uint16_t* ptr = (uint16_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	*ptr = byte;
}

void writeDwordFromReal(uint16_t seg, uint16_t off, uint32_t byte)
{
	uint32_t* ptr = (uint32_t*) (size_t) ((uint32_t) seg * 16 + (uint32_t) off);
	*ptr = byte;
}

bool vm8086FaultHandler(regs* r)
{
	//YOU NEED TO VALIDATE CS, EIP, SS AND ESP HERE

	uint8_t* ip = (uint8_t*) (size_t) realToLinear(r->cs, r->eip);
	uint16_t* stack = (uint16_t*) (size_t) realToLinear(r->ss, r->useresp);
	uint32_t* stack32 = (uint32_t*) stack;
	uint16_t* ivt = (uint16_t*) (size_t) 0;

	static uint8_t pause = 0;

	/*if (((++pause) & 0x7F) == 0) {
		while (1) {
			uint8_t key = inbv(0x60);
			if (key == 0x1C || key == 0x5A) {
				while (key == 0x1C || key == 0x5A) key = inbv(0x60);
				break;
			}
		}
	}*/
	//kprintf("<%X, %X %X%X> ", r->cs * 16 + r->eip, ip, ip[0], ip[1], ip[2]);

	bool operand32 = false;
	bool address32 = false;

	uint8_t segmentOverride = 6;			//0 = CS, 1 = DS, 2 = ES, 3 = FS, 4 = GS, 5 = SS, 6 = DEFAULT

	while (1) {
		switch (ip[0]) {
		case 0x26:		//ES
			//kprintf("ES ");
			segmentOverride = 2;
			r->eip++;
			ip++;
			break;
			
		case 0x2E:		//CS
			//kprintf("CS ");
			segmentOverride = 0;
			r->eip++;
			ip++;
			break;

		case 0x3E:		//DS
			//kprintf("DS ");
			segmentOverride = 1;
			r->eip++;
			ip++;
			break;

		case 0x64:		//FS
			//kprintf("FS ");
			segmentOverride = 3;
			r->eip++;
			ip++;
			break;

		case 0x65:		//GS
			//kprintf("GS ");
			segmentOverride = 4;
			r->eip++;
			ip++;
			break;

		case 0x36:		//SS
			//kprintf("SS ");
			segmentOverride = 5;
			r->eip++;
			ip++;
			break;

		case 0x66:
			//kprintf("O32 ");
			operand32 = true;
			r->eip++;
			ip++;
			break;

		case 0x67:
			address32 = true;
			//kprintf("A32 %d ", address32);
			r->eip++;
			ip++;
			break;

		case 0xF3:					//REP
			//kprintf("REP!\n");
			r->eip++;
			ip++;
			break;

		case 0x9C:		//PUSHF
			//kprintf("phf ");
			if (operand32) {
				r->useresp = (r->useresp - 4) & 0xFFFF;
				stack32--;
				stack32[0] = r->eflags & 0xDFF;

				if (currentTaskTCB->vm86VIE) {
					stack32[0] |= 0x200;
				} else {
					stack32[0] &= ~0x200;
				}
			} else {
				r->useresp = (r->useresp - 2) & 0xFFFF;
				stack--;
				stack[0] = r->eflags;

				if (currentTaskTCB->vm86VIE) {
					stack[0] |= 0x200;
				} else {
					stack[0] &= ~0x200;
				}
			}

			r->eip++;
			return true;

		case 0x9D:		//POPF
			//kprintf("ppf ");
			if (operand32) {
				r->eflags = 0x20200 | (stack32[0] & 0xDFF);
				currentTaskTCB->vm86VIE = (stack32[0] & 0x200) != 0;
				r->useresp = (r->useresp + 4) & 0xFFFF;
			} else {
				r->eflags = 0x20200 | stack[0];
				currentTaskTCB->vm86VIE = (stack[0] & 0x200) != 0;
				r->useresp = (r->useresp + 2) & 0xFFFF;
			}

			r->eip++;
			return true;

		case 0xCD:		//INT N
			//kprintf("int 0x%X ", ip[1]);

			if (ip[1] == 0xFF) {
				terminateTask(r->eax);
				return true;
			}

			vm8086DoISR(r, ip[1], ip, r->ss, r->useresp);
			return true;

		case 0xFA:		//CLI
			//kprintf("/ ");

			currentTaskTCB->vm86VIE = false;
			r->eip++;
			return true;

		case 0xFB:		//STI
			//kprintf("\\ ");

			currentTaskTCB->vm86VIE = true;
			r->eip++;
			return true;

		case 0xCF:
			//kprintf("iret ");

			r->eip = stack[0];
			r->cs = stack[1];
			r->eflags = 0x20200 | stack[2];

			//kprintf("RELOADING IP AS 0x%X, CS AS 0x%X, (STACK AT 0x%X)\n", r->eip, r->cs, stack);
			currentTaskTCB->vm86VIE = (stack[2] & 0x200) != 0;

			r->useresp = (r->useresp + 6) & 0xFFFF;

			return true;

		case 0x6C:					//INS
		{
			///TODO: NEEDS ADDRESS32 SUPPORT
			//kprintf("! ");

			uint16_t seg = 0;
			/*switch (segmentOverride) {
			case 0:
				seg = r->cs;
				break;
			case 1:
			case 6:
				seg = r->ds;
				break;
			case 2:
				seg = r->es;
				break;
			case 3:
				seg = r->fs;
				break;
			case 4:
				seg = r->gs;
				break;
			case 5:
				seg = r->ss;
				break;
			}*/
			seg = r->es;

			if (address32 && r->edi > 0xFFFF) {
				//kprintf("VM8086 ADDRESSING FAULT 0x%X (%X%X%X%X%X%X)\n", ip[0], ip[0], ip[1], ip[2], ip[3], ip[4], ip[5]);
				return false;
			}

			writeByteFromReal(seg, r->edi & 0xFFFF, inbv(r->edx));

			if (r->eflags & 0x400) {
				r->edi = (r->edi - 1) & 0xFFFF;

			} else {
				r->edi = (r->edi + 1) & 0xFFFF;
			}

			r->eip += 1;
			return true;
		}

		case 0x6D:					//INS
		{			
			///TODO: NEEDS ADDRESS32 SUPPORT

			//kprintf("@ ");

			uint16_t seg = 0;
			/*switch (segmentOverride) {
			case 0:
				seg = r->cs;
				break;
			case 1:
			case 6:
				seg = r->ds;
				break;
			case 2:
				seg = r->es;
				break;
			case 3:
				seg = r->fs;
				break;
			case 4:
				seg = r->gs;
				break;
			case 5:
				seg = r->ss;
				break;
			}*/

			seg = r->es;

			if (address32 && r->edi > 0xFFFF) {
				//kprintf("VM8086 ADDRESSING FAULT 0x%X (%X%X%X%X%X%X)\n", ip[0], ip[0], ip[1], ip[2], ip[3], ip[4], ip[5]);
				return false;
			}

			if (operand32) {
				writeDwordFromReal(seg & 0xFFFF, r->edi & 0xFFFF, inl(r->edx));

				if (r->eflags & 0x400) {
					r->edi = (r->edi - 4) & 0xFFFF;

				} else {
					r->edi = (r->edi + 4) & 0xFFFF;
				}

			} else {
				writeWordFromReal(seg & 0xFFFF, r->edi & 0xFFFF, inw(r->edx));

				if (r->eflags & 0x400) {
					r->edi = (r->edi - 2) & 0xFFFF;

				} else {
					r->edi = (r->edi + 2) & 0xFFFF;
				}
			}

			r->eip += 1;
			return true;
		}

		case 0x6E:
		{			
			///TODO: NEEDS ADDRESS32 SUPPORT

			//kprintf("# ");

			uint16_t seg = 0;
			switch (segmentOverride) {
			case 0:
				seg = r->cs;
				break;
			case 1:
			case 6:
				seg = r->ds;
				break;
			case 2:
				seg = r->es;
				break;
			case 3:
				seg = r->fs;
				break;
			case 4:
				seg = r->gs;
				break;
			case 5:
				seg = r->ss;
				break;
			}

			if (address32 && r->esi > 0xFFFF) {
				//kprintf("VM8086 ADDRESSING FAULT 0x%X (%X%X%X%X%X%X)\n", ip[0], ip[0], ip[1], ip[2], ip[3], ip[4], ip[5]);
				return false;
			}

			outbv(r->edx, readByteFromReal(seg & 0xFFFF, r->esi & 0xFFFF));

			if (r->eflags & 0x400) {
				r->esi = (r->esi - 1) & 0xFFFF;

			} else {
				r->esi = (r->esi + 1) & 0xFFFF;
			}

			r->eip += 1;
			return true;
		}

		case 0x6F:
		{		
			///TODO: NEEDS ADDRESS32 SUPPORT

			//kprintf("$ ");

			uint16_t seg = 0;
			switch (segmentOverride) {
			case 0:
				seg = r->cs;
				break;
			case 1:
			case 6:
				seg = r->ds;
				break;
			case 2:
				seg = r->es;
				break;
			case 3:
				seg = r->fs;
				break;
			case 4:
				seg = r->gs;
				break;
			case 5:
				seg = r->ss;
				break;
			}

			if (address32 && r->esi > 0xFFFF) {
				//kprintf("VM8086 ADDRESSING FAULT 0x%X (%X%X%X%X%X%X)\n", ip[0], ip[0], ip[1], ip[2], ip[3], ip[4], ip[5]);
				return false;
			}

			if (operand32) {
				outl(r->edx, readDwordFromReal(seg & 0xFFFF, r->esi & 0xFFFF));

				if (r->eflags & 0x400) {
					r->esi = (r->esi - 4) & 0xFFFF;

				} else {
					r->esi = (r->esi + 4) & 0xFFFF;
				}

			} else {
				outw(r->edx, readWordFromReal(seg & 0xFFFF, r->esi & 0xFFFF));

				if (r->eflags & 0x400) {
					r->esi = (r->esi - 2) & 0xFFFF;

				} else {
					r->esi = (r->esi + 2) & 0xFFFF;
				}
			}

			r->eip += 1;
			return true;
		}

		case 0xE4:
			//kprintf("I%X ", ip[1]);

			r->eax &= ~0xFF;
			r->eax |= inbv(ip[1]);

			r->eip += 2;
			return true;

		case 0xE5:
			//kprintf("i%X ", ip[1]);

			if (operand32) {
				r->eax = inl(ip[1]);
			} else {
				r->eax &= ~0xFFFF;
				r->eax |= inw(ip[1]);
			}

			r->eip += 2;
			return true;

		case 0xE6:
			//kprintf("O%X%X ", ip[1], r->eax);

			outbv(ip[1], r->eax & 0xFF);
			r->eip += 2;
			return true;

		case 0xE7:
			//kprintf("o%X%X ", ip[1], r->eax);

			if (operand32) {
				outl(ip[1], r->eax);
			} else {
				outw(ip[1], r->eax & 0xFFFF);
			}

			r->eip += 2;
			return true;

		case 0xEC:
			//kprintf("J%X ", r->edx);
			r->eax &= ~0xFF;
			r->eax |= inbv(r->edx & 0xFFFF);

			r->eip++;

			return true;

		case 0xED:
			//kprintf("j%X ", r->edx);

			if (operand32) {
				r->eax = inl(r->edx & 0xFFFF);
			} else {
				r->eax &= ~0xFFFF;
				r->eax |= inw(r->edx & 0xFFFF);
			}

			r->eip++;
			
			return true;

		case 0xEE:
			//kprintf("P%X%X ", r->edx, r->eax);
			outbv(r->edx & 0xFFFF, r->eax & 0xFF);

			r->eip++;

			return true;

		case 0xEF:
			//kprintf("p%X%X ", r->edx, r->eax);
			if (operand32) {
				outl(r->edx & 0xFFFF, r->eax);
			} else {
				outw(r->edx & 0xFFFF, r->eax & 0xFFFF);
			}

			r->eip++;

			return true;

		default:
			kprintf("UNHANDLED VM8086 OPCODE 0x%X (%X%X%X%X%X%X)\n", ip[0], ip[0], ip[1], ip[2], ip[3], ip[4], ip[5]);
			while (1) {
				uint8_t key = inbv(0x60);
				if (key == 0x1C || key == 0x5A) {
					while (key == 0x1C || key == 0x5A) key = inbv(0x60);
					break;
				}
			}
			return false;
		}
	}
	
	return false;
}
