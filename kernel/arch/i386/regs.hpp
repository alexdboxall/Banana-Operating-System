#pragma once

//if you change this, very bad stuff could happen if you don't change the matching assembly
//(warning: THIS INCLUDES THE FORKING CODE, SYSCALLS AND INTERRUPTS, TASK CREATION, TASK SWITCHING, XADD VOODOO, ETC.!)
struct regs
{
	//PUSHED LATER				PUSHED EARLIER
	//POPPED EARLIER			POPPED LATER
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;

	//VM8086 ONLY
	unsigned int v86es, v86ds, v86fs, v86gs;
};