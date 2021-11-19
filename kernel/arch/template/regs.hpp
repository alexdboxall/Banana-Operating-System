#pragma once

// very bad stuff could happen if you don't change the matching assembly
struct regs
{
	// must contain registers with these names, even if the underlying system calls them something else
	// 		eax					-> system call number
	//		ebx, ecx, edx		-> system call arguments
	// 		others...?

	//PUSHED LATER				PUSHED EARLIER
};