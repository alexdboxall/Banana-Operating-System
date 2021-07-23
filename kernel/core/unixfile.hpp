#pragma once

#ifndef _UNIXFILE_HPP_
#define _UNIXFILE_HPP_

#include <stdint.h>
#include <stddef.h>

enum class FileStatus
{
	Success = 0,
	Failure = 1,
	NotExist = 2,
	WriteProtect = 3,
	InvalidArgument = 4,
	FileNotOpen = 5,
	FileOpen = 6,
	DirectoryEOF = 7,
	FormatNotSupported = 8,
	FormatDidntStart = 9,
	NotSupported = 10,
	NoFilesystem = 11,
};

//these need to be way up here becuase newlib decided a signed short
//was long enough for file descriptors...
#define RESERVED_FD_NUL		0x0FFFFF00
#define RESERVED_FD_CON		0x0FFFFF01
#define RESERVED_FD_PNT		0x0FFFFF02
#define RESERVED_FD_AUX		0x0FFFFF03
#define RESERVED_FD_COM1	0x0FFFFF10
#define RESERVED_FD_COM9	0x0FFFFF18
#define RESERVED_FD_LPT1	0x0FFFFF20
#define RESERVED_FD_LPT9	0x0FFFFF28

#define RESERVED_FD_START	RESERVED_FD_NUL

class UnixFile;
UnixFile* KeGetFileFromDescriptor(int fd);

class UnixFile
{
private:

protected:
	friend UnixFile* KeGetFileFromDescriptor(int fd);

	int fd;	
	static int nextFd;


public:
	UnixFile* next;
	virtual bool isAtty() = 0;

	UnixFile(int fd = 0);
	virtual ~UnixFile();

	int getFileDescriptor();

	virtual FileStatus read(uint64_t bytes, void* where, int* bytesRead) = 0;
	virtual FileStatus write(uint64_t bytes, void* where, int* bytesWritten) = 0;
};

class ReservedFilename: public UnixFile
{
protected:

public:
	bool isAtty();

	ReservedFilename(int fd);
	~ReservedFilename();

	FileStatus read(uint64_t bytes, void* where, int* bytesRead);
	FileStatus write(uint64_t bytes, void* where, int* bytesWritten);
};

#endif