#include "core/unixfile.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "coreobjs/linkedlist.hpp"
#include "thr/prcssthr.hpp"
#include "dbg/kconsole.hpp"
extern "C" {
#include "libk/string.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

int UnixFile::nextFd = 3;

LinkedList<UnixFile> unixFileLinkedList;

bool initialFilesAdded = false;

UnixFile* sfileCon;
UnixFile* sfileAux;
UnixFile* sfilePnt;
UnixFile* sfileNul;
UnixFile* sfileCom[9];
UnixFile* sfileLpt[9];

UnixFile::UnixFile(int _fd)
{
	if (_fd >= RESERVED_FD_START) {
		return;
	}
	fd = nextFd++;
	unixFileLinkedList.addElement(this);

	if (!initialFilesAdded) {
		//this must go first, otherwise we'll end up
		//in a recursion loop
		initialFilesAdded = true;

		sfileAux = new ReservedFilename(RESERVED_FD_AUX);
		sfileCon = new ReservedFilename(RESERVED_FD_CON);
		sfileNul = new ReservedFilename(RESERVED_FD_NUL);
		sfilePnt = new ReservedFilename(RESERVED_FD_PNT);

		for (int i = 0; i < 9; ++i) {
			sfileCom[i] = new ReservedFilename(RESERVED_FD_COM1 + i);
			sfileLpt[i] = new ReservedFilename(RESERVED_FD_LPT1 + i);
		}
	}
}

UnixFile::~UnixFile()
{
	if (fd >= RESERVED_FD_START) {
		return;
	}
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
	if (fdIn < RESERVED_FD_START) {
		UnixFile* f = unixFileLinkedList.getFirstElement();
		while (f) {
			if (f->fd == fdIn) {
				return f;
			}
			f = unixFileLinkedList.getNext(f);
		}
	} else {
		kprintf("This is aspecial file of some sort...\n");
		if (fdIn == RESERVED_FD_AUX) return sfileAux;
		else if (fdIn == RESERVED_FD_CON) {
			kprintf("returning the con file.\n");
			return sfileCon;
		}
		else if (fdIn == RESERVED_FD_PNT) return sfilePnt;
		else if (fdIn == RESERVED_FD_NUL) return sfileNul;
		else if (fdIn >= RESERVED_FD_COM1 && fdIn <= RESERVED_FD_COM9) {
			return sfileCom[fdIn - RESERVED_FD_COM1];

		} else if (fdIn >= RESERVED_FD_LPT1 && fdIn <= RESERVED_FD_LPT9) {
			return sfileLpt[fdIn - RESERVED_FD_LPT1];
		}
	}
	
	return nullptr;
}

ReservedFilename::ReservedFilename(int _fd) : UnixFile(_fd)
{
	fd = _fd;
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
	kprintf("reserved file isAtty\n");
	if (fd == RESERVED_FD_AUX) {
		return false;

	} else if (fd == RESERVED_FD_CON) {
		kprintf("Yes, con is a TTY\n");
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