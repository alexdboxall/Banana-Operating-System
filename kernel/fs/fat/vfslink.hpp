#ifndef __FAT_LINK_HPP__
#define __FAT_LINK_HPP__

#include <stddef.h>
#include <stdint.h>
#include "core/main.hpp"
#include "fs/vfs.hpp"

class FAT : public Filesystem
{
private:

protected:
	static int vfsToFatRemaps[26];
	static int fats;
	void fixFilepath(char* path);

public:
	char* getName();

	FAT();
	virtual ~FAT();
	bool tryMount(LogicalDisk* disk, int diskNum);

	FileStatus format(LogicalDisk* disk, int disknum, const char* type, int allocationUnit);
	FileStatus open(const char* filename, void** ptr, FileOpenMode mode);
	FileStatus read(void* ptr, size_t bytes, void* where, int* bytesRead);
	FileStatus write(void* ptr, size_t bytes, void* where, int* bytesWritten);
	FileStatus close(void* ptr);
	FileStatus closeDir(void* ptr);
	FileStatus seek(void* ptr, uint64_t position);
	FileStatus truncate(void* ptr, uint64_t position);
	FileStatus tell(void* ptr, uint64_t* position);
	FileStatus unlink(const char* file);
	FileStatus rename(const char* old, const char* _new);
	FileStatus stat(void* ptr, uint64_t* size);
	FileStatus stat(const char* filename, uint64_t* size, bool* directory);
	FileStatus mkdir(const char* file);

	FileStatus openDir(const char* filename, void** ptr);
	FileStatus readDir(void* ptr, size_t bytes, void* where, int* bytesRead);

	virtual FileStatus getlabel(LogicalDisk* disk, int diskNum, char* returnBuffer, uint32_t* serial) override;
	virtual FileStatus setlabel(LogicalDisk* disk, int diskNum, char* label) override;

	bool exists(const char* file);

	virtual uint64_t allocateSwapfile(const char* filename, int megs) override;
	virtual FileStatus chfatattr(const char* path, uint8_t andMask, uint8_t orFlags) override;
};

#endif