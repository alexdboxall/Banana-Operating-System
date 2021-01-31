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

#define RESERVED_FD_NUL		5
#define RESERVED_FD_CON		6
#define RESERVED_FD_PNT		7
#define RESERVED_FD_AUX		8

#define RESERVED_FD_COM1	11
#define RESERVED_FD_COM2	12
#define RESERVED_FD_COM3	13
#define RESERVED_FD_COM4	14
#define RESERVED_FD_COM5	15
#define RESERVED_FD_COM6	16
#define RESERVED_FD_COM7 	17
#define RESERVED_FD_COM8	18
#define RESERVED_FD_COM9	19

#define RESERVED_FD_LPT1	21
#define RESERVED_FD_LPT2	22
#define RESERVED_FD_LPT3	23
#define RESERVED_FD_LPT4	24
#define RESERVED_FD_LPT5	25
#define RESERVED_FD_LPT6	26
#define RESERVED_FD_LPT7 	27
#define RESERVED_FD_LPT8	28
#define RESERVED_FD_LPT9	29

#define FIRST_AVAILABLE_FD	100

class UnixFile;
UnixFile* getFromFileDescriptor(int fd);

class UnixFile
{
private:

protected:
	friend UnixFile* getFromFileDescriptor(int fd);

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