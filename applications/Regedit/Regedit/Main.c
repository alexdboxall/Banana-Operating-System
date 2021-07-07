
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"
extern uint64_t SystemCall(size_t, size_t, size_t, size_t);

char sstr[500];
void regtree(void* reg, int a, int n, int showcontent)
{
	while (a > 0) {
		char nm[50];
		memset(nm, 0, 50);

		int type = SystemCall(RegistryGetNameAndTypeFromExtent, (size_t) reg, (size_t) a, (size_t) nm);
		if (!strcmp(nm, "DUMMY")) {
			a = SystemCall(RegistryGetNext, (size_t) reg, a, 0);
			continue;
		}
		for (int i = 0; i < n; ++i) putchar(' ');


/// <param name="ebx">The registry pointer.</param>
/// <param name="ecx">The extent number, with the 31st bit determining whether to read an integer (bit set), or a string (bit clear).</param>
/// <param name="edx">The path to write string data.</param>
/// <returns>Returns the integer data, else 0 if success, or non-zero on failure.</returns>
		if (showcontent) {
			if (type == 0xC1) {
				SystemCall(RegistryReadExtent, (size_t) reg, a, (size_t) sstr);
				printf("/%s  << %s >> s\n", nm, sstr);

			} else if (type >= 0x6A && type <= 0x71) {
				uint64_t iint = SystemCall(RegistryReadExtent, (size_t) reg, a | (1 << 31), 0);
			
				if (showcontent == 2) {
					if (type == 0x6E) printf("/%s  << %02X >> i8\n", nm, (int) iint);
					if (type == 0x6F) printf("/%s  << %04X >> i16\n", nm, (int) iint);
					if (type == 0x70) printf("/%s  << %08X >> i32\n", nm, (int) iint);
					if (type == 0x71) printf("/%s  << %016llX >> i64\n", nm, (long long int) iint);
					if (type == 0x6A) printf("/%s  << %02X >> u8\n", nm, (unsigned) iint);
					if (type == 0x6B) printf("/%s  << %04X >> u16\n", nm, (unsigned) iint);
					if (type == 0x6C) printf("/%s  << %08X >> u32\n", nm, (unsigned) iint);
					if (type == 0x6D) printf("/%s  << %016llX >> u64\n", nm, (long long unsigned) iint);
				} else {
					if (type == 0x6E) printf("/%s  << %d >> i8\n", nm, (int) iint);
					if (type == 0x6F) printf("/%s  << %d >> i16\n", nm, (int) iint);
					if (type == 0x70) printf("/%s  << %d >> i32\n", nm, (int) iint);
					if (type == 0x71) printf("/%s  << %lld >> i64\n", nm, (long long int) iint);
					if (type == 0x6A) printf("/%s  << %u >> u8\n", nm, (unsigned) iint);
					if (type == 0x6B) printf("/%s  << %u >> u16\n", nm, (unsigned) iint);
					if (type == 0x6C) printf("/%s  << %u >> u32\n", nm, (unsigned) iint);
					if (type == 0x6D) printf("/%s  << %llu >> u64\n", nm, (long long unsigned) iint);
				}
			} else {
				printf("/%s\n", nm);
			}

		} else {
			printf("/%s\n", nm);
		}

		if (type == 0x4E) {
			regtree(reg, SystemCall(RegistryEnterDirectory, (size_t) reg, a, 0), n + 4, showcontent);
		}

		a = SystemCall(RegistryGetNext, (size_t) reg, a, 0);
	}
}

void begin(void* reg, int argc, char* argv[])
{
	if (argc == 1 || !strcmp(argv[1], "help")) {
		printf("Commands: help, tree, treex, treehx\nExample usage: regedit tree\n");

	} else if (!strcmp(argv[1], "tree")) {
		regtree(reg, 1, 0, 0);

	} else if (!strcmp(argv[1], "treex")) {
		regtree(reg, 1, 0, 1);

	} else if (!strcmp(argv[1], "treehx")) {
		regtree(reg, 1, 0, 2);

	} else {
		printf("Unsupported command.\n");
	}
}

int main (int argc, char *argv[])
{
	void* reg = SystemCall(RegistryOpen, 0, 0, "C:/Banana/Registry/System/SYSTEM.REG");
	begin(reg, argc, argv);
	SystemCall(RegistryClose, (size_t) reg, 0, 0);

	return 0;
}

/*
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include <reg/cm.hpp>

extern "C" {
#include <libk/string.h>
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Gets the registry type from a path.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="edx">The path.</param>
/// <returns>Returns the type ID or -1 on failure.</returns>
///
uint64_t SysRegistryGetTypeFromPath(regs* r)
{
	char name[256];
	int x = CmFindObjectFromPath(((Reghive*) r->ebx), (const char*) r->edx);
	if (!x) return -1;
	int type = CmGetNameAndTypeFromExtent(((Reghive*) r->ebx), x, name);

	return type;
}

uint64_t SysRegistryReadExtent(regs* r)
{
	return 0;
}

/// <summary>
/// Gets the registry extent number from a path.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="edx">The path.</param>
/// <returns>Returns the extent number.</returns>
///
uint64_t SysRegistryPathToExtentLookup(regs* r)
{
	return CmFindObjectFromPath(((Reghive*) r->ebx), (const char*) r->edx);
}

/// <summary>
/// Gets the subdirectory registry extent number from an extent number.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="ecx">The extent.</param>
/// <returns>Returns the extent number.</returns>
///
uint64_t SysRegistryEnterDirectory(regs* r)
{
	return CmEnterDirectory(((Reghive*) r->ebx), r->ecx);
}

uint64_t SysRegistryGetNext(regs* r)
{
	return CmGetNext(((Reghive*) r->ebx), r->ecx);
}

uint64_t SysRegistryGetNameAndTypeFromExtent(regs* r)
{
	char name[256];
	int type = CmGetNameAndTypeFromExtent(((Reghive*) r->ebx), r->ecx, name);
	strcpy((char*) r->edx, name);
	return type;
}

uint64_t SysRegistryOpen(regs* r)
{
	return (uint64_t) CmOpen((const char*) r->edx);
}

uint64_t SysRegistryClose(regs* r)
{
	return 0;
}*/