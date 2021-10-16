
/*
	fs/symlink.cpp

	Symbolic Links

		Symlinks are implemented in two parts: an entry in the internal symlink
		registrar (C:/Banana/System/symlink.sys) and the symlink file itself.

		The details in the symlink file must match the details in the internal
		table in order for the symlink to be valid. This ensures that if e.g.,
		someone copies a symlink from one system to another, or moves or modifies
		it, etc., it will no longer function.

		It also means that someone cannot just create a symlink in e.g. notepad.
*/

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
#include <reg/cm.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

//a counter which increments with every symlink created
uint32_t kiBaseSymlinkID = 0;

//number of symlink registrations 
#define MAX_WAITING_ROOM_LINKS 4
#define SYMLINK_TABLE_BYTES 8192

//all symlink paths get hashed, which corresponds to a bit in this table
//this table is persistant
//if a bit is set, it means there is a symlink with that hash
//if the bit isn't set, there is no symlink with that hash (and therefore name)
uint8_t kiSymlinkHashTable[SYMLINK_TABLE_BYTES];

//store newly created symlinks is memory instead of on the disk to save time
char kiNewlyCreatedSymlinks[MAX_WAITING_ROOM_LINKS][256];
uint64_t kiNewlyCreatedIDs[MAX_WAITING_ROOM_LINKS];
int kiNumWaitingRoomSymlinks = 0;


//gets a 16 bit symlink hash from a filepath
static uint16_t KiGetSymlinkHash(const char* filepath)
{
	uint32_t crc = KeCalculateCRC32((uint8_t*) filepath, strlen(filepath));
	return (crc & 0xFFFF) ^ (crc >> 16);
}

//checks if a given hash is in the table
static bool KiIsHashInTable(uint16_t hash)
{
	return (kiSymlinkHashTable[hash >> 3] >> (hash & 7)) & 1;
}

//sets or clears a bit in the hash table
static void KiSetHashInTable(uint16_t hash, bool state)
{
	if (state) {
		kiSymlinkHashTable[hash >> 3] |= 1 << (hash & 7);
	} else {
		kiSymlinkHashTable[hash >> 3] &= ~(1 << (hash & 7));
	}
}

//generate a unique symlink ID for a new symlink
static uint64_t KiCreateSymlinkID()
{
	int insanityCounter = 0;
	uint64_t id;
	//get a non-zero ID made up of two components:
	//		- random number
	//		- increasing number (persistant)
	do {
		id = KeRand();
		id <<= 31;

		id ^= kiBaseSymlinkID++;

		if (++insanityCounter == 666) {
			KePanic("INSANITY");
		}

	} while (!id);

	return id;
}

//writes any changes to symlinks from the waiting room back to the disk
static void KiFlushSymlinkChanges()
{
	//try to open the file
	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f) {
		KePanic("CANNOT WRITE SYMLINKS (A)");
	}
	
	FileStatus status = f->open(FILE_OPEN_APPEND);
	if (status != FileStatus::Success) {
		KePanic("CANNOT WRITE SYMLINKS (B)");
	}

	//for everyone in the waiting room, write the filename,
	//and then the ID
	int br;
	for (int i = 0; i < kiNumWaitingRoomSymlinks; ++i) {
		f->write(256, kiNewlyCreatedSymlinks[i], &br);
		if (br != 256) {
			KePanic("CANNOT WRITE SYMLINKS (C)");
		}

		f->write(8, &kiNewlyCreatedIDs[i], &br);
		if (br != 8) {
			KePanic("CANNOT WRITE SYMLINKS (D)");
		}
	}

	f->close();
	delete f;

	kiNumWaitingRoomSymlinks = 0;
}

//wrapper for the atexit handler as KiFlushSymlinkChanges takes no arguments
void KiDeinitialiseSymlinks(void* context)
{
	KiFlushSymlinkChanges();
}

//register a new symlink
void KeRegisterSymlink(const char* linkName, uint64_t linkID)
{
	//add the ID, and filename to the waiting room
	kiNewlyCreatedIDs[kiNumWaitingRoomSymlinks] = linkID;
	memset(kiNewlyCreatedSymlinks[kiNumWaitingRoomSymlinks], 0, 256);
	strcpy(kiNewlyCreatedSymlinks[kiNumWaitingRoomSymlinks], linkName);

	//create the hash, and set that in the table
	uint16_t hash = KiGetSymlinkHash(linkName);
	KiSetHashInTable(hash, true);

	++kiNumWaitingRoomSymlinks;

	//flush the waiting room if full
	if (kiNumWaitingRoomSymlinks >= MAX_WAITING_ROOM_LINKS) {
		KiFlushSymlinkChanges();
	}
}

//initialises the symlink subsystem, which involves loading some
//things from the disk, hence it must be called after we have a filesystem
//also, it must be called before any other symlink things are done
void KeInitialiseSymlinks()
{
	//initialise variables
	kiBaseSymlinkID = 0;
	kiNumWaitingRoomSymlinks = 0;
	memset(kiSymlinkHashTable, 0, sizeof(kiSymlinkHashTable));

	//we need changes to be flushed on shutdown
	KeRegisterAtexit(KiDeinitialiseSymlinks, nullptr);

	//try to open the symlink file
	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f) {
		KePanic("CANNOT CREATE SYMLINK FILE A");
	}
	if (!f->exists()) {
		//if it doesn't exist, create it
		FileStatus status = f->open(FILE_OPEN_WRITE_NORMAL);
		if (status != FileStatus::Success) {
			KePanic("CANNOT CREATE SYMLINK FILE B");
		}
		f->close();

	} else {
		//otherwise, open it for reading
		FileStatus status = f->open(FILE_OPEN_READ);
		if (status != FileStatus::Success) {
			KePanic("CANNOT READ SYMLINK FILE A");
		}

		//for as long a possible, read in the data
		while (1) {
			++kiBaseSymlinkID;				//recreate this number (increments when
											//a symlink is created)
			
			char nm[256];
			uint64_t id;
			int br;
			f->read(256, nm, &br);			//read the filepath of the link
			if (br != 256) break;
			f->read(8, &id, &br);			//read the ID of the link
			if (br != 8) break;

			//mark this file hash as being a symlink
			KiSetHashInTable(KiGetSymlinkHash(nm), true);
		}

		f->close();
	}

	delete f;
}

//checks if a filepath is a symlink which has been registered in the registrar
//returns zero if it is not, or the symlink ID if it is
uint64_t KiIsSymlinkRegistered(const char* linkName)
{
	//all symlink file paths have a bit stored in the hash table
	if (!KiIsHashInTable(KiGetSymlinkHash(linkName))) {
		//if the has of the requested file isn't in the has table,
		//then we know that that isn't a symlink
		return 0;
	}

	//otherwise, check if it is in the waiting room (i.e. registered 
	//recently and not yet flushed)
	for (int i = 0; i < kiNumWaitingRoomSymlinks; ++i) {
		if (!strcmp(linkName, kiNewlyCreatedSymlinks[i])) {
			return kiNewlyCreatedIDs[i];
		}
	}

	//otherwise we must open the registrar
	File* f = new File("C:/Banana/System/symlinks.sys", kernelProcess);
	if (!f || !f->exists()) {
		KePanic("CANNOT READ SYMLINK FILE B");
	}

	FileStatus status = f->open(FILE_OPEN_READ);
	if (status != FileStatus::Success) {
		KePanic("CANNOT READ SYMLINK FILE C");
	}

	//for as long as we have file,
	while (1) {
		char nm[256];
		uint64_t id;
		int br;
		f->read(256, nm, &br);		//load the filepath
		if (br != 256) break;
		f->read(8, &id, &br);		//load the ID
		if (br != 8) break;

		//if the filename matches the ID, return the ID
		if (!strcmp(linkName, nm)) {
			f->close();
			delete f;
			return id;
		}
	}

	//if we get here, was a hash collision, but not a symlink

	f->close();
	delete f;

	return 0;
}

//gets the target filepath from a symbolic link filepath
//returns the number of dereferences which occured (either 0 or 1),
//or -1 on disk failure.
//the target filepath is returned in the buffer pointer passed in
int KeDereferenceSymlink(const char* linkName, char* dereferencedBuffer)
{
	//if not registered, return no deferences (0)
	uint64_t registrationID = KiIsSymlinkRegistered(linkName);
	if (!registrationID) {
		return 0;
	}

	//otherwise, open the link file
	File* fil = new File(linkName, kernelProcess);
	if (!fil) {
		return -1;
	}

	FileStatus status = fil->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		delete fil;
		return -1;
	}

	//read the signature "SYMLINK!" (not actually checked yet)
	char buffer[9];
	int br;
	status = fil->read(8, buffer, &br);
	if (status != FileStatus::Success || br != 8) {
		fil->close();
		delete fil;
		return -1;
	}

	//read the ID
	uint64_t id;
	status = fil->read(8, &id, &br);
	if (status != FileStatus::Success || br != 8) {
		fil->close();
		delete fil; 
		return -1;
	}

	//check that it matches the ID we have stored in the internal table
	//this ensures that modifying a symlink doesn't modify the target
	//(it instead renders it invalid)
	if (id != registrationID) {
		return 0;
	}

	//read the size of the file
	uint64_t siz = 0;
	bool dir;
	fil->stat(&siz, &dir);
	
	//failure if it is a directory or too small
	if (dir || siz < 16) {
		fil->close();
		delete fil; 
		return -1;
	}

	//remove the signature and ID
	siz -= 16;

	//filenames can only be 255 characters
	if (siz > 255) {
		return -1;
	}

	//read the filename
	memset(dereferencedBuffer, 0, siz + 1);
	status = fil->read(siz, dereferencedBuffer, &br);
	if (status != FileStatus::Success || br != siz) {
		fil->close();
		delete fil;
		return -1;
	}

	fil->close();
	delete fil;

	//one derefence was done here (the VFS handles double-dereferences)
	return 1;
}

int KeCreateSymlink(const char* existing, const char* linkName)
{
	//create the link file
	File* fil = new File(linkName, kernelProcess, false);
	if (!fil) {
		return 1;
	}
	FileStatus status = fil->open(FILE_OPEN_WRITE_NORMAL);
	if (status != FileStatus::Success) {
		delete fil;
		return 1;
	}

	//write the signature (not actually checked at the moment)
	int br;
	char symsig[] = "SYMLINK!";
	status = fil->write(8, symsig, &br);
	if (br != 8 || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	//create a symlink ID, and then write it to the file
	uint64_t id = KiCreateSymlinkID();
	status = fil->write(8, &id, &br);
	if (br != 8 || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	//write the filepath
	status = fil->write(strlen(existing), (void*) existing, &br);
	if (br != strlen(existing) || status != FileStatus::Success) {
		fil->close();
		delete fil;
		return 1;
	}

	//we must also put it in the registrar so the system knows
	//it is an actual symlink
	KeRegisterSymlink(linkName, id);
	
	fil->close();
	delete fil;

	return 0;
}