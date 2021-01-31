#ifndef __ISO9660_LINK_HPP__
#define __ISO9660_LINK_HPP__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "core/main.hpp"
#include "fs/vfs.hpp"

typedef struct isoFile_t
{
	uint64_t fileStartLba;
	uint64_t fileLength;

	uint64_t seekMark;
	bool error;

	char driveLetter;

} isoFile_t;

class ISO9660 : public Filesystem
{
private:

protected:

public:	
	char* getName();

	ISO9660();
	virtual ~ISO9660();
	bool tryMount(LogicalDisk* disk, int diskNum);

	FileStatus open(const char* filename, void** ptr, FileOpenMode mode);
	FileStatus read(void* ptr, size_t bytes, void* where, int* bytesRead);
	FileStatus write(void* ptr, size_t bytes, void* where, int* bytesWritten);
	FileStatus close(void* ptr);
	FileStatus closeDir(void* ptr);
	FileStatus seek(void* ptr, uint64_t position);
	FileStatus tell(void* ptr, uint64_t* position);
	FileStatus unlink(const char* file);
	FileStatus rename(const char* old, const char* _new);
	FileStatus stat(void* ptr, uint64_t* size);
	FileStatus stat(const char* filename, uint64_t* size, bool* directory);
	FileStatus mkdir(const char* file);

	FileStatus openDir(const char* filename, void** ptr);
	FileStatus readDir(void* ptr, size_t bytes, void* where, int* bytesRead);
	FileStatus format(LogicalDisk* disk, int disknum, const char* type, int allocationUnit);

	bool exists(const char* file);
};

#endif