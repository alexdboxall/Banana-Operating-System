#ifndef __VFS_HPP__
#define __VFS_HPP__

#include <stddef.h>
#include <stdint.h>
#include "core/main.hpp"
#include "thr/prcssthr.hpp"
#include "core/unixfile.hpp"
#include "hal/logidisk.hpp"

class LogicalDisk;
class PhysicalDisk;

//do not change the order or apps will become confused
enum class FileOpenMode
{
	Read = 1,
	Write = 2,
	Append = 4,
	CreateNew = 8,
	CreateAlways = 16,
};

//do not change the order or apps will become confused
enum class FATAttribute
{
	ReadOnly = 1,
	Archive = 2,
	System = 4,
	Hidden = 8,
};

#define FILE_OPEN_READ FileOpenMode::Read
#define FILE_OPEN_WRITE_EXISTING FileOpenMode::Write
#define FILE_OPEN_WRITE_NORMAL ((FileOpenMode) (((int) FileOpenMode::Write) | ((int) FileOpenMode::CreateAlways)))
#define FILE_OPEN_APPEND ((FileOpenMode) (((int) FileOpenMode::Write) | ((int) FileOpenMode::Append)))

class Filesystem
{
private:

protected:

public:
	Filesystem* next;

	virtual char* getName() = 0;

	Filesystem();
	virtual ~Filesystem();
	virtual bool tryMount(LogicalDisk* disk, int diskNum) = 0;
	virtual FileStatus open(const char* filename, void** ptr, FileOpenMode mode) = 0;
	virtual FileStatus read(void* ptr, size_t bytes, void* where, int* bytesRead) = 0;
	virtual FileStatus write(void* ptr, size_t bytes, void* where, int* bytesWritten) = 0;
	virtual FileStatus close(void* ptr) = 0;
	virtual FileStatus closeDir(void* ptr) = 0;
	virtual FileStatus seek(void* ptr, uint64_t offset) = 0;
	virtual FileStatus tell(void* ptr, uint64_t* pos) = 0;

	virtual FileStatus stat(void* ptr, uint64_t* size) = 0;
	virtual FileStatus stat(const char* filename, uint64_t* size, bool* directory) = 0;
	
	virtual FileStatus chfatattr(const char* path, uint8_t andMask, uint8_t orFlags) = 0;
	virtual FileStatus unlink(const char* file) = 0;
	virtual FileStatus mkdir(const char* file) = 0;
	virtual FileStatus rename(const char* old, const char* _new) = 0;
	virtual bool exists(const char* file) = 0;

	virtual FileStatus format(LogicalDisk* disk, int disknum, const char* type, int allocationUnit) = 0;

	virtual FileStatus openDir(const char* filename, void** ptr) = 0;
	virtual FileStatus readDir(void* ptr, size_t bytes, void* where, int* bytesRead) = 0;

	virtual FileStatus getlabel(LogicalDisk* disk, int diskNum, char* returnBuffer, uint32_t* serial);
	virtual FileStatus setlabel(LogicalDisk* disk, int diskNum, char* label);

	virtual uint64_t getFileFirstSector(const char* filename);
};

extern Filesystem* installedFilesystems;

class File : public UnixFile
{
private:
		
protected:
	bool fileOpen;

	char filepath[256];
	uint8_t driveNo;

public:
	void* fsSpecificData;

	File(const char* filename, Process* process);		//process required to obtain the trust certificates
	~File();
	virtual bool isAtty();

	FileStatus open(FileOpenMode mode);

	//these rely on the file being OPEN
	FileStatus read(uint64_t bytes, void* where, int* bytesRead);
	FileStatus write(uint64_t bytes, void* where, int* bytesWritten);
	FileStatus close();
	FileStatus rewind();
	FileStatus seek(uint64_t offset);
	FileStatus tell(uint64_t* pos);

	//these rely on the file being CLOSED
	FileStatus unlink();
	FileStatus rename(const char* new_);
	FileStatus chfatattr(uint8_t clearBits, uint8_t setBits);

	//this can be called either
	FileStatus stat(uint64_t* size, bool* directory);

	//don't know about this one
	bool exists();
};

typedef uint64_t time_t;

extern "C" {
#define __KERNEL_DIRENT_INCLUDE
#define _TIME_T_DECLARED
#include "../libraries/newlib-3.3.0/newlib/libc/sys/banana/sys/dirent.h"
#undef __KERNEL_DIRENT_INCLUDE
}

class Directory: public UnixFile
{
private:

protected:
	bool fileOpen;

	char filepath[256];
	uint8_t driveNo;

	void* fsSpecificData;

public:
	virtual bool isAtty();

	Directory(const char* filename, Process* process);		//process required to obtain the trust certificates
	~Directory();

	FileStatus open();

	//these rely on the file being OPEN
	FileStatus read(uint64_t bytes, void* where, int* bytesRead);
	FileStatus read(struct dirent* p);
	FileStatus write(uint64_t bytes, void* where, int* bytesWritten);
	FileStatus close();

	//these rely on the file being CLOSED
	FileStatus unlink();
	FileStatus rename(const char* new_);
	FileStatus create();

	bool exists();
};

namespace Fs
{
	int getcwd(Process* process, char* buffer, int bytes);
	int setcwd(Process* process, char* buffer);

	void standardiseFiles(char* outBuffer, const char* filename, const char* cwd);
	void initVFS();
}


#endif