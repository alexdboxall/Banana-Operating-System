#include "core/main.hpp"
#include "thr/prcssthr.hpp"
#include "fs/vfs.hpp" 
#include "hal/logidisk.hpp"
#include "libk/string.h"
#include "fs/symlink.hpp"

extern "C" {
#include "libk/string.h"
}

#include <krnl/random.hpp>
#include <krnl/atexit.hpp>
#include <krnl/crc32.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint32_t KiBaseSymlinkID = 0;

#define MAX_WAITING_ROOM_LINKS 4
#define SYMLINK_TABLE_BYTES 8192

uint8_t KiSymlinkHashTable[SYMLINK_TABLE_BYTES];
char KiNewlyCreatedSymlinks[MAX_WAITING_ROOM_LINKS][256];
uint64_t KiNewlyCreatedIDs[MAX_WAITING_ROOM_LINKS];
int KiNumWaitingRoomSymlinks = 0;

static uint16_t KiGetSymlinkHash(const char* filepath)
{
	uint32_t crc = KeCalculateCRC32((uint8_t*) filepath, strlen(filepath));
	return (crc & 0xFFFF) ^ (crc >> 16);
}

static bool KiIsHashInTable(uint16_t hash)
{
	return (KiSymlinkHashTable[hash >> 3] >> (hash & 7)) & 1;
}

static void KiSetHashInTable(uint16_t hash, bool state)
{
	if (state) {
		KiSymlinkHashTable[hash >> 3] |= 1 << (hash & 7);
	} else {
		KiSymlinkHashTable[hash >> 3] &= ~(1 << (hash & 7));
	}
}

static uint64_t KiCreateSymlinkID()
{
	int insanityCounter = 0;
	uint64_t id;
	do {
		id = KeRand();
		id <<= 27;

		id ^= KiBaseSymlinkID++;

		if (++insanityCounter == 666) {
			KePanic("INSANITY");
		}

	} while (!id);
	return id;
}

static void KiFlushSymlinkChanges()
{
	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f) {
		KePanic("CANNOT WRITE SYMLINKS (A)");
	}
	
	FileStatus status = f->open(FILE_OPEN_APPEND);
	if (status != FileStatus::Success) {
		KePanic("CANNOT WRITE SYMLINKS (B)");
	}

	int br;
	for (int i = 0; i < KiNumWaitingRoomSymlinks; ++i) {
		f->write(256, KiNewlyCreatedSymlinks[i], &br);
		if (br != 256) {
			KePanic("CANNOT WRITE SYMLINKS (C)");
		}

		f->write(8, &KiNewlyCreatedIDs[i], &br);
		if (br != 8) {
			KePanic("CANNOT WRITE SYMLINKS (D)");
		}
	}

	f->close();
	delete f;

	KiNumWaitingRoomSymlinks = 0;

	//TODO: write KiBaseSymlinkID back to disk
}

void KiDeinitialiseSymlinks(void* context)
{
	KiFlushSymlinkChanges();
}

void KeRegisterSymlink(const char* linkName, uint64_t linkID)
{
	KiNewlyCreatedIDs[KiNumWaitingRoomSymlinks] = linkID;
	memset(KiNewlyCreatedSymlinks[KiNumWaitingRoomSymlinks], 0, 256);
	strcpy(KiNewlyCreatedSymlinks[KiNumWaitingRoomSymlinks], linkName);

	uint16_t hash = KiGetSymlinkHash(linkName);
	KiSetHashInTable(hash, true);

	++KiNumWaitingRoomSymlinks;

	if (KiNumWaitingRoomSymlinks >= MAX_WAITING_ROOM_LINKS) {
		KiFlushSymlinkChanges();
	}
}

void KeInitialiseSymlinks()
{
	KiNumWaitingRoomSymlinks = 0;
	memset(KiSymlinkHashTable, 0, sizeof(KiSymlinkHashTable));

	//TODO: load KiBaseSymlinkID

	KeRegisterAtexit(KiDeinitialiseSymlinks, nullptr);

	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f) {
		KePanic("CANNOT CREATE SYMLINK FILE A");
	}
	if (!f->exists()) {
		FileStatus status = f->open(FILE_OPEN_WRITE_NORMAL);
		if (status != FileStatus::Success) {
			KePanic("CANNOT CREATE SYMLINK FILE B");
		}
		f->close();

	} else {
		FileStatus status = f->open(FILE_OPEN_READ);
		if (status != FileStatus::Success) {
			KePanic("CANNOT READ SYMLINK FILE A");
		}

		while (1) {
			char nm[256];
			uint64_t id;
			int br;
			f->read(256, nm, &br);
			if (br != 256) break;
			f->read(8, &id, &br);
			if (br != 8) break;

			kprintf("On load, a symlink with name %s was loaded and hashed.\n", nm);

			KiSetHashInTable(KiGetSymlinkHash(nm), true);
		}

		f->close();
	}

	delete f;

	KeCreateSymlink("C:/Banana/System/KERNEL32.EXE", "C:/kernel.txt");
}


uint64_t KiIsSymlinkRegistered(const char* linkName)
{
	if (!KiIsHashInTable(KiGetSymlinkHash(linkName))) {
		return 0;
	}

	for (int i = 0; i < KiNumWaitingRoomSymlinks; ++i) {
		if (!strcmp(linkName, KiNewlyCreatedSymlinks[i])) {
			return KiNewlyCreatedIDs[i];
		}
	}

	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f || !f->exists()) {
		KePanic("CANNOT READ SYMLINK FILE B");
	}

	FileStatus status = f->open(FILE_OPEN_READ);
	if (status != FileStatus::Success) {
		KePanic("CANNOT READ SYMLINK FILE C");
	}

	while (1) {
		char nm[256];
		uint64_t id;
		int br;
		f->read(256, nm, &br);
		if (br != 256) break;
		f->read(8, &id, &br);
		if (br != 8) break;

		if (!strcmp(linkName, nm)) {
			kprintf("matched a symlink: %s\n", nm);
			f->close();
			delete f;
			return id;
		}
	}

	f->close();
	delete f;

	return 0;
}

int KeDereferenceSymlink(const char* linkName, char* dereferencedBuffer)
{
	uint64_t registrationID = KiIsSymlinkRegistered(linkName);
	if (!registrationID) {
		return 0;
	}

	File* fil = new File(linkName, kernelProcess);
	if (!fil) {
		return -1;
	}

	FileStatus status = fil->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		delete fil;
		return -1;
	}

	char buffer[9];
	int br;
	status = fil->read(8, buffer, &br);
	if (status != FileStatus::Success || br != 8) {
		fil->close();
		delete fil;
		return -1;
	}

	uint64_t id;
	status = fil->read(8, &id, &br);
	if (status != FileStatus::Success || br != 8) {
		fil->close();
		delete fil; 
		return -1;
	}
	if (id != registrationID) {
		return 0;
	}

	uint64_t siz = 0;
	bool dir;
	fil->stat(&siz, &dir);

	if (dir || siz < 16) {
		fil->close();
		delete fil; 
		return -1;
	}

	siz -= 16;
	if (siz > 255) {
		return -1;
	}
	memset(dereferencedBuffer, 0, siz + 1);
	status = fil->read(siz, dereferencedBuffer, &br);
	if (status != FileStatus::Success || br != siz) {
		fil->close();
		delete fil;
		return -1;
	}

	fil->close();
	delete fil;

	return 1;
}


int KeCreateSymlink(const char* existing, const char* linkName)
{
	File* fil = new File(linkName, kernelProcess, false);
	if (!fil) {
		return 1;
	}

	FileStatus status = fil->open(FILE_OPEN_WRITE_NORMAL);
	if (status != FileStatus::Success) {
		delete fil;
		return 1;
	}

	int br;
	char symsig[] = "SYMLINK!";
	status = fil->write(8, symsig, &br);
	if (br != 8 || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	uint64_t id = KiCreateSymlinkID();
	status = fil->write(8, &id, &br);
	if (br != 8 || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	status = fil->write(strlen(existing), (void*) existing, &br);
	if (br != strlen(existing) || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	KeRegisterSymlink(linkName, id);

	fil->close();
	delete fil;

	return 0;
}