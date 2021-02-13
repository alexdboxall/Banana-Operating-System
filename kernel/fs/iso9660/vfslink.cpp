#include "fs/iso9660/vfslink.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "hal/logidisk.hpp"

extern "C" {
	#include "libk/string.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

// return disks[vfsDisk]->read(sector, count, (void*) buff);
// return disks[vfsDisk]->write(sector, count, (void*) buff);

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

void readSectorFromCDROM(uint32_t sector, uint8_t* data, char driveletter)
{
	disks[driveletter - 'A']->read(sector, 1, data);
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
					 uint32_t* lbaOut, uint32_t* lenOut, char driveletter)
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
	o -= 33;                    //33 = filename start, 2 = lba start, 31 = difference
	newLba = o[2] | (o[3] << 8) | (o[4] << 16) | (o[5] << 24);
	newLen = o[10] | (o[11] << 8) | (o[12] << 16) | (o[13] << 24);

	if (dir) {
		free(data);
		return readRecursively(filename, newLba, newLen, lbaOut, lenOut, driveletter);
	} else {
		*lbaOut = newLba;      //data
		*lenOut = newLen;      //data
		free(data);
		return true;
	}

	return false;
}

bool getFileData(char* filename, uint32_t* lbaOut, uint32_t* lenOut, char driveletter)
{
	uint32_t lba = 0, len = 0;
	*lbaOut = -1;
	*lenOut = -1;
	readRoot(&lba, &len, driveletter);
	return readRecursively(filename, lba, len, lbaOut, lenOut, driveletter);
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
	kprintf("IS09660 try mount...\n");

	char bf[2048];
	readSectorFromCDROM(16, (uint8_t*) bf, diskNum + 'A');
	if (bf[1] != 'C') return false;
	if (bf[2] != 'D') return false;
	if (bf[3] != '0') return false;
	if (bf[4] != '0') return false;
	if (bf[5] != '1') return false;
	
	kprintf("IS09660 tried mount...\n");

	return true;
}

FileStatus ISO9660::open(const char* __fn, void** ptr, FileOpenMode mode)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	kprintf("Opening an ISO9660 file: '%s'\n", __fn);

	*ptr = malloc(sizeof(isoFile_t));
	isoFile_t* file = (isoFile_t*) *ptr;

	uint32_t lbaO;
	uint32_t lenO;

	bool res = getFileData((char*) __fn, &lbaO, &lenO, __fn[0]);
	if (!res) {
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
	uint8_t* buffer = (uint8_t*) bf;

	isoFile_t* file = (isoFile_t*) ptr;

	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;
	if (file->error) {
		return FileStatus::Failure;
	}

	int64_t ulength = (int64_t) bytes;
	uint64_t intendedSeekMark = file->seekMark + ulength;

	if (intendedSeekMark > file->fileLength) {
		uint64_t subtract = (intendedSeekMark - file->fileLength);
		intendedSeekMark -= subtract;
		ulength -= subtract;
	}

	uint64_t bytesToRead = ulength;

	file->seekMark = intendedSeekMark;
	
	//
	// we now have how many bytes we need 'ulength'
	//

	uint64_t startPoint = file->fileStartLba * 2048 + file->seekMark;
	
	//read from the partial first sector (could be the entire sector though)
	uint8_t sectorBuffer[2048];
	readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);
	//kprintf("CD-ROM read sector %d\n", startPoint / 2048);

	//work out how many bytes to read
	int count = 2048 - file->seekMark % 2048;
	if (count > ulength) {
		count = ulength;
	}
	if (count == 0) {
		*bytesRead = 0;
		return FileStatus::Success;
	}

	//read them
	memcpy(buffer, sectorBuffer + file->seekMark % 2048, count);
	//kprintf("copied to buffer starting at 0x%X into sector, count = %d\n", file->seekMark % 2048, count);
	buffer += count;
	startPoint += count;
	ulength -= count;

	//now we are on a sector boundry
	while (ulength >= 2048) {
		readSectorFromCDROM(startPoint / 2048, buffer, file->driveLetter);
		//kprintf("reading sector %d\n", startPoint / 2048);
		startPoint += 2048;
		buffer += 2048;
		ulength -= 2048;
	}

	if (ulength) {
		//now we just have bytes left on the final sector
		readSectorFromCDROM(startPoint / 2048, sectorBuffer, file->driveLetter);
		memcpy(buffer, sectorBuffer, ulength);

		//kprintf("reading sector %d, count = %d\n", startPoint / 2048, ulength);
	}
	
	*bytesRead = bytesToRead;

	return FileStatus::Success;
}

bool ISO9660::exists(const char* file)
{
	return false;
}

FileStatus ISO9660::seek(void* ptr, uint64_t offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	return FileStatus::Failure;
}

FileStatus ISO9660::tell(void* ptr, uint64_t* offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (offset == nullptr) return FileStatus::InvalidArgument;

	*offset = 0;

	return FileStatus::Failure;
}

char* ISO9660::getName()
{
	return (char*) "ISO 9660 Filesystem Driver";
}

FileStatus ISO9660::stat(void* ptr, uint64_t* size)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;

	*size = 0;

	return FileStatus::Failure;
}

FileStatus ISO9660::stat(const char* path, uint64_t* size, bool* directory)
{
	if (path == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;
	if (directory == nullptr) return FileStatus::InvalidArgument;

	*directory = 0;
	*size = 0;

	return FileStatus::Failure;
}

FileStatus ISO9660::close(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	return FileStatus::Failure;
}





FileStatus ISO9660::openDir(const char* __fn, void** ptr)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	return FileStatus::Failure;
}

FileStatus ISO9660::readDir(void* ptr, size_t bytes, void* where, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;

	return FileStatus::Failure;
}

FileStatus ISO9660::closeDir(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	return FileStatus::Failure;
}

FileStatus ISO9660::chfatattr(const char* path, uint8_t andMask, uint8_t orFlags)
{
	return FileStatus::Failure;
}

















FileStatus ISO9660::unlink(const char* file)
{
	if (file == nullptr) {
		return FileStatus::InvalidArgument;
	}

	return FileStatus::Failure;
}

FileStatus ISO9660::write(void* ptr, size_t bytes, void* where, int* bytesWritten)
{
	if (ptr == nullptr || bytesWritten == nullptr) return FileStatus::InvalidArgument;

	*bytesWritten = 0;

	return FileStatus::Failure;
}

FileStatus ISO9660::rename(const char* old, const char* _new)
{	
	//REMEMBER TO MODIFY THE DRIVE USED FROM e.g. C: to A:

	kprintf("FAT RENAME NOT SUPPORTED!\n");

	return FileStatus::Failure;
}

FileStatus ISO9660::mkdir(const char* file)
{
	if (file == nullptr) {
		return FileStatus::InvalidArgument;
	}

	return FileStatus::Failure;
}
