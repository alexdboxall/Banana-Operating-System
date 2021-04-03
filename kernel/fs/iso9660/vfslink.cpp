#include "fs/iso9660/vfslink.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "hal/logidisk.hpp"

/*
This ISO 9660 driver is 'sketchy as hell'
It is based on code I wrote at an athletics carnival (!) a few years ago.

A badly formatted disk will cause array indices to exceed boundaries,
overwriting random data on the stack and (hopefully) crashing the OS,
or if we are not lucky, will silently corrupt memory and cause random bugs.
*/

extern "C" {
	#include "libk/string.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint8_t* __memmem(uint8_t* big, int bigLen, uint8_t* small, int smallLen)
{
	//may have an 'off by one' error, but this won't matter, as all
	//names end in ';1'
	for (int i = 0; i < bigLen - smallLen; ++i) {
		bool yes = true;
		for (int j = 0; j < smallLen; ++j) {
			if (small[j] != big[i + j]) {
				yes = false;
				break;
			}
		}
		if (yes) {
			return big + i;
		}
	}
	return 0;
}

uint8_t recentBuffer[2048];
uint32_t recentSector = 0;
char recentDriveletter = '0';

void readSectorFromCDROM(uint32_t sector, uint8_t* data, char driveletter)
{
	if (sector != recentSector || recentDriveletter != driveletter) {
		recentSector = sector;
		recentDriveletter = driveletter;
		disks[driveletter - 'A']->read(sector, 1, recentBuffer);
	}

	memcpy(data, recentBuffer, 2048);
}

bool readRoot(uint32_t* lbaOut, uint32_t* lenOut, char driveletter)
{
	uint8_t sector[2048];
	readSectorFromCDROM(16, sector, driveletter);
	uint8_t root[34];
	memcpy(root, sector + 156, 34);

	*lbaOut = root[2] | (root[3] << 8) | (root[4] << 16) | (root[5] << 24);
	*lenOut = root[10] | (root[11] << 8) | (root[12] << 16) | (root[13] << 24);

	return true;
}

bool readRecursively(char* filename, uint32_t startSec, uint32_t startLen, \
					 uint32_t* lbaOut, uint32_t* lenOut, char driveletter, int* dirout)
{
	if (filename[1] == ':') {
		filename += 2;
	}
	while (filename[0] == '/') filename++;

	char firstPart[256];
	memset(firstPart, 0, 256);
	bool dir = false;
	for (int i = 0; filename[i]; ++i) {
		if (filename[i] == '/') {
			filename += i + 1;
			dir = true;
			break;
		}
		firstPart[i] = filename[i];
		if (firstPart[i] >= 'a' && firstPart[i] <= 'z') {
			firstPart[i] -= 'a';
			firstPart[i] += 'A';
		}
	}

	uint32_t newLba, newLen;
	uint8_t* data = (uint8_t*) malloc(startLen);

	for (int i = 0; (uint32_t) i < (startLen + 2047) / 2048; ++i) {
		readSectorFromCDROM(startSec + i, data + i * 2048, driveletter);
	}

	uint8_t* o = __memmem(data, startLen, (uint8_t*) firstPart, strlen(firstPart));
	if (o == 0) {
		free(data);
		return false;
	}
	o -= 33;            //we searched by filename using memmem, which starts at 33
						//so subtract 33 to get the actual start of the directory entry
	newLba = o[2] | (o[3] << 8) | (o[4] << 16) | (o[5] << 24);
	newLen = o[10] | (o[11] << 8) | (o[12] << 16) | (o[13] << 24);
	bool isDir = (o[25] & 2) ? 1 : 0;

	if (dir) {
		free(data);
		return readRecursively(filename, newLba, newLen, lbaOut, lenOut, driveletter, dirout);
	} else {
		*lbaOut = newLba;      //data
		*lenOut = newLen;      //data
		*dirout = isDir;
		free(data);
		return true;
	}

	return false;
}

bool getFileData(char* filename, uint32_t* lbaOut, uint32_t* lenOut, char driveletter, int* dirout)
{
	uint32_t lba = 0, len = 0;
	*lbaOut = -1;
	*lenOut = -1;
	readRoot(&lba, &len, driveletter);

	if (strlen(filename) <= 3) {
		*lbaOut = lba;
		*lenOut = len;
		*dirout = 1;
		return true;
	}

	return readRecursively(filename, lba, len, lbaOut, lenOut, driveletter, dirout);
}

ISO9660::ISO9660() : Filesystem()
{

}

ISO9660::~ISO9660()
{

}

FileStatus ISO9660::format(LogicalDisk* disk, int disknum, const char* type, int allocationUnit)
{
	return FileStatus::FormatNotSupported;
}

bool ISO9660::tryMount(LogicalDisk* disk, int diskNum)
{
	char bf[2048];
	readSectorFromCDROM(16, (uint8_t*) bf, diskNum + 'A');
	if (bf[1] != 'C') return false;
	if (bf[2] != 'D') return false;
	if (bf[3] != '0') return false;
	if (bf[4] != '0') return false;
	if (bf[5] != '1') return false;
	
	return true;
}

FileStatus ISO9660::open(const char* __fn, void** ptr, FileOpenMode mode)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	if (mode != FileOpenMode::Read) {
		kprintf("write protect error on ISO9660 open.\n");
		return FileStatus::WriteProtect;
	}

	*ptr = malloc(sizeof(isoFile_t));
	isoFile_t* file = (isoFile_t*) *ptr;

	uint32_t lbaO;
	uint32_t lenO;

	int dir;
	bool res = getFileData((char*) __fn, &lbaO, &lenO, __fn[0], &dir);
	if (!res || dir) {
		file->error = true;
		return FileStatus::Failure;
	}

	file->error = false;
	file->seekMark = 0;
	file->fileStartLba = lbaO;
	file->fileLength = lenO;
	file->driveLetter = __fn[0];
	
	return FileStatus::Success;
}

FileStatus ISO9660::read(void* ptr, size_t bytes, void* bf, int* bytesRead)
{
	kprintf("Reading %d bytes.\n", bytes);
	uint8_t* buffer = (uint8_t*) bf;

	isoFile_t* file = (isoFile_t*) ptr;
	kprintf("isofile = 0x%X\n", file);

	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;
	if (file->error) {
		return FileStatus::Failure;
	}
	kprintf("A\n");

	int64_t ulength = (int64_t) bytes;							//1024
	uint64_t intendedSeekMark = file->seekMark + ulength;		//1024

	if (intendedSeekMark > file->fileLength) {					//1024 > 72
		uint64_t subtract = (intendedSeekMark - file->fileLength);	//952
		intendedSeekMark -= subtract;							//72
		ulength -= subtract;									//72
	}

	uint64_t bytesToRead = ulength;								//72
	
	//
	// we now have how many bytes we need in 'ulength'
	//
	kprintf("B\n");

	//33314 * 2048 + 0
	//
	uint64_t startPoint = file->fileStartLba * 2048 + file->seekMark;
	
	//read from the partial first sector (could be the entire sector though)
	uint8_t sectorBuffer[2048];
	readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);
	kprintf("C\n");

	//work out how many bytes to read
	int count = 2048 - file->seekMark % 2048;
	if (count > ulength) {
		count = ulength;
	}
	if (count == 0) {
		*bytesRead = 0;
		return FileStatus::Success;
	}
	kprintf("D\n");
	kprintf("Count = %d, buffer = 0x%X, sectorBuffer = 0x%X, seekMark = 0x%X\n", count, buffer, sectorBuffer, file->seekMark);

	//read them
	memcpy(buffer, sectorBuffer + file->seekMark % 2048, count);
	buffer += count;
	startPoint += count;
	ulength -= count;
	kprintf("E\n");

	//now we are on a sector boundry
	while (ulength >= 2048) {
		readSectorFromCDROM(startPoint / 2048, buffer, file->driveLetter);
		//kprintf("reading sector %d\n", startPoint / 2048);
		startPoint += 2048;
		buffer += 2048;
		ulength -= 2048;
	}
	kprintf("F\n");

	if (ulength) {
		//now we just have bytes left on the final sector
		kprintf("F1\n");
		readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);
		kprintf("F2\n");
		memcpy(buffer, sectorBuffer, ulength);
		kprintf("F3\n");

		//kprintf("reading sector %d, count = %d\n", startPoint / 2048, ulength);
	}
	kprintf("G\n");

	*bytesRead = bytesToRead;
	file->seekMark = intendedSeekMark;
	kprintf("DONE\n");

	return FileStatus::Success;
}

bool ISO9660::exists(const char* file)
{
	uint32_t lbaO;
	uint32_t lenO;
	int dir;
	bool res = getFileData((char*) file, &lbaO, &lenO, file[0], &dir);
	return res;
}

FileStatus ISO9660::seek(void* ptr, uint64_t offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	isoFile_t* file = (isoFile_t*) ptr;
	if (offset < file->fileLength) {
		file->seekMark = offset;
		return FileStatus::Success;
	}

	return FileStatus::Failure;
}

FileStatus ISO9660::tell(void* ptr, uint64_t* offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (offset == nullptr) return FileStatus::InvalidArgument;

	isoFile_t* file = (isoFile_t*) ptr;
	*offset = file->seekMark;

	return FileStatus::Success;
}

char* ISO9660::getName()
{
	return (char*) "ISO 9660 Filesystem Driver";
}

FileStatus ISO9660::stat(void* ptr, uint64_t* size)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;

	isoFile_t* file = (isoFile_t*) ptr;
	*size = file->fileLength;

	return FileStatus::Success;
}

FileStatus ISO9660::stat(const char* path, uint64_t* size, bool* directory)
{
	if (path == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;
	if (directory == nullptr) return FileStatus::InvalidArgument;

	*directory = 0;
	*size = 0;

	uint32_t lbaO;
	uint32_t lenO;
	int dir;
	bool res = getFileData((char*) path, &lbaO, &lenO, path[0], &dir);
	if (res) {
		*size = lenO;
		*directory = dir;
		if (dir) {
			*size = 0;
		}
		return FileStatus::Success;
	}

	return FileStatus::Failure;
}

FileStatus ISO9660::close(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	free(ptr);

	return FileStatus::Success;
}

FileStatus ISO9660::openDir(const char* __fn, void** ptr)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	*ptr = malloc(sizeof(isoFile_t));
	isoFile_t* file = (isoFile_t*) *ptr;

	uint32_t lbaO;
	uint32_t lenO;

	int dir;
	bool res = getFileData((char*) __fn, &lbaO, &lenO, __fn[0], &dir);
	if (!res || !dir) {
		kprintf("Error. res = %d, dir = %d\n", res, dir);
		file->error = true;
		return FileStatus::Failure;
	}

	file->error = false;
	file->seekMark = 0;
	file->fileStartLba = lbaO;
	file->fileLength = lenO;
	file->driveLetter = __fn[0];

	return FileStatus::Success;
}

FileStatus ISO9660::readDir(void* ptr, size_t bytes, void* where, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;

	isoFile_t* file = (isoFile_t*) ptr;
	if (file->fileLength == 0) {
		return FileStatus::DirectoryEOF;
	}

	uint32_t startPoint = file->fileStartLba * 2048 + file->seekMark;
	uint8_t sectorBuffer[2048];
	readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);

	uint8_t len = sectorBuffer[file->seekMark % 2048 + 0];
	if (len == 0) {
		int add = ((file->seekMark + 2047) % 2048) - file->seekMark;
		file->seekMark += add;
		if (file->fileLength <= add) {
			file->fileLength = 0;
		} else {
			file->fileLength -= add;
		}
		if (file->fileLength == 0) {
			return FileStatus::DirectoryEOF;
		}
		startPoint = file->fileStartLba * 2048 + file->seekMark;
		readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);
		len = sectorBuffer[file->seekMark % 2048 + 0];
	}

	char name[40];
	memset(name, 0, 40);

	//whoa... all of those conditions are here in an attempt to stop a page fault
	for (int i = 0; sectorBuffer[file->seekMark % 2048 + i + 33] != ';' && sectorBuffer[file->seekMark % 2048 + i + 33] != 0 && i < 40 && (file->seekMark % 2048 + i + 33) < 2048; ++i) {
		name[i] = sectorBuffer[file->seekMark % 2048 + i + 33];
	}

	struct dirent dent;
	dent.d_ino = 0;
	dent.d_namlen = strlen(name);
	dent.d_type = sectorBuffer[file->seekMark % 2048 + 25] & 2 ? DT_DIR : DT_REG;

	strcpy(dent.d_name, name);

	if (dent.d_name[0] == 0) {
		dent.d_name[0] = '.';
		dent.d_name[1] = 0;
		dent.d_namlen = 1;
		dent.d_type = DT_DIR;
	}
	if (dent.d_name[0] == 1) {
		dent.d_name[0] = '.';
		dent.d_name[1] = '.';
		dent.d_name[2] = 0;
		dent.d_namlen = 2;
		dent.d_type = DT_DIR;
	}	

	memcpy(where, &dent, bytes);

	*bytesRead = sizeof(dent);

	file->seekMark += len;
	if (file->fileLength <= len) {
		file->fileLength = 0;
	} else {
		file->fileLength -= len;
	}

	return FileStatus::Success;
}

FileStatus ISO9660::closeDir(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	free(ptr);

	return FileStatus::Success;
}

FileStatus ISO9660::chfatattr(const char* path, uint8_t andMask, uint8_t orFlags)
{
	return FileStatus::Failure;
}

FileStatus ISO9660::unlink(const char* file)
{
	return FileStatus::Failure;
}

FileStatus ISO9660::write(void* ptr, size_t bytes, void* where, int* bytesWritten)
{
	return FileStatus::Failure;
}

FileStatus ISO9660::rename(const char* old, const char* _new)
{	
	return FileStatus::Failure;
}

FileStatus ISO9660::mkdir(const char* file)
{
	return FileStatus::Failure;
}
