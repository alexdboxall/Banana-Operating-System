#include "core/unixfile.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "coreobjs/linkedlist.hpp"
#include "core/prcssthr.hpp"
#include "core/kconsole.hpp"
extern "C" {
#include "libk/string.h"
}
#pragma GCC optimize ("Os")

int UnixFile::nextFd = 3;// FIRST_AVAILABLE_FD;

LinkedList<UnixFile> unixFileLinkedList;

bool initialFilesAdded = false;

UnixFile::UnixFile(int _fd)
{
	fd = nextFd++;
	unixFileLinkedList.addElement(this);

	/*if (!initialFilesAdded) {
		//this must go first, otherwise we'll end up
		//in a recursion loop
		initialFilesAdded = true;

		new ReservedFilename(RESERVED_FD_AUX);
		new ReservedFilename(RESERVED_FD_CON);
		new ReservedFilename(RESERVED_FD_NUL);
		new ReservedFilename(RESERVED_FD_PNT);

		for (int i = 0; i < 9; ++i) {
			new ReservedFilename(RESERVED_FD_COM1 + i);
			new ReservedFilename(RESERVED_FD_LPT1 + i);
		}
	}*/
}

UnixFile::~UnixFile()
{
	int timeout = 0;
	while (1) {
		UnixFile* f = unixFileLinkedList.getFirstElement();
		unixFileLinkedList.removeFirst();

		if (f == this) {
			return;
		}

		unixFileLinkedList.addElement(f);

		if (timeout++ == 5000) {
			panic("DELETING UNIXFILE - CANNOT FIND");
		}
	}
}

int UnixFile::getFileDescriptor()
{
	return fd;
}

UnixFile* getFromFileDescriptor(int fdIn)
{
	UnixFile* f = unixFileLinkedList.getFirstElement();
	while (f) {
		if (f->fd == fdIn) {
			return f;
		}
		f = unixFileLinkedList.getNext(f);
	}
	return nullptr;
}

ReservedFilename::ReservedFilename(int _fd) : UnixFile(_fd)
{

}

ReservedFilename::~ReservedFilename()
{

}

FileStatus ReservedFilename::read(uint64_t bytes, void* where, int* bytesRead)
{
	if (fd == RESERVED_FD_AUX) {
		*bytesRead = 0;

	} else if (fd == RESERVED_FD_CON) {
		kprintf("READING CON\n");
		return currentTaskTCB->processRelatedTo->terminal->read(bytes, where, bytesRead);

	} else if (fd == RESERVED_FD_NUL) {
		*bytesRead = 0;

	} else if (fd == RESERVED_FD_PNT) {
		*bytesRead = 0;

	} else if (fd >= RESERVED_FD_COM1 && fd <= RESERVED_FD_COM9) {
		*bytesRead = 0;

	} else if (fd >= RESERVED_FD_LPT1 && fd <= RESERVED_FD_LPT9) {
		*bytesRead = 0;

	}
	return FileStatus::Success;
}

bool ReservedFilename::isAtty()
{
	if (fd == RESERVED_FD_AUX) {
		return false;

	} else if (fd == RESERVED_FD_CON) {
		return true;

	} else if (fd == RESERVED_FD_NUL) {
		return false;

	} else if (fd == RESERVED_FD_PNT) {
		return false;

	} else if (fd >= RESERVED_FD_COM1 && fd <= RESERVED_FD_COM9) {
		return false;

	} else if (fd >= RESERVED_FD_LPT1 && fd <= RESERVED_FD_LPT9) {
		return false;
	}

	return false;
}

FileStatus ReservedFilename::write(uint64_t bytes, void* where, int* bytesWritten)
{
	if (fd == RESERVED_FD_AUX) {
		*bytesWritten = 0;

	} else if (fd == RESERVED_FD_CON) {
		kprintf("WRITING CON\n");
		return currentTaskTCB->processRelatedTo->terminal->write(bytes, where, bytesWritten);

	} else if (fd == RESERVED_FD_NUL) {
		*bytesWritten = bytes;

	} else if (fd == RESERVED_FD_PNT) {
		*bytesWritten = 0;

	} else if (fd >= RESERVED_FD_COM1 && fd <= RESERVED_FD_COM9) {
		*bytesWritten = 0;

	} else if (fd >= RESERVED_FD_LPT1 && fd <= RESERVED_FD_LPT9) {
		*bytesWritten = 0;

	}

	return FileStatus::Success;
}