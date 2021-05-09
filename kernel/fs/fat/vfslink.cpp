#include "fs/fat/vfslink.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "hal/logidisk.hpp"
#include "hal/diskphys.hpp"
#include "hw/ports.hpp"

extern "C" {
	#include "fs/fat/ff.h"
	#include "fs/fat/diskio.h"
	#include "libk/string.h"

	int fatToVFSRemaps[20];

	int fatWrapperReadDisk(BYTE vfsDisk,		/* Physical drive nmuber to identify the drive */
						   BYTE* buff,		/* Data buffer to store read data */
						   LBA_t sector,	/* Start sector in LBA */
						   UINT count		/* Number of sectors to read */)
	{
		return disks[vfsDisk]->read(sector, count, (void*) buff);
	}

	int fatWrapperWriteDisk(BYTE vfsDisk,		/* Physical drive nmuber to identify the drive */
						   BYTE* buff,		/* Data buffer to store read data */
						   LBA_t sector,	/* Start sector in LBA */
						   UINT count		/* Number of sectors to read */)
	{
		return disks[vfsDisk]->write(sector, count, (void*) buff);
	}

	int fatWrapperIoctl(
		BYTE vfsdisk,
		BYTE cmd,
		void* buff
	)
	{
		if (cmd == GET_SECTOR_SIZE) {
			WORD* w = (WORD*) buff;
			*w = disks[vfsdisk]->physDisk->sectorSize;
			return RES_OK;
		
		} else if (cmd == GET_SECTOR_COUNT) {
			LBA_t* b = (LBA_t*) buff;
			*b = ((disks[vfsdisk]->physDisk->sizeInKBs * 1024) / disks[vfsdisk]->physDisk->sectorSize);
			return RES_OK;
		
		} else if (cmd == CTRL_SYNC) {
			return RES_OK;

		} else if (cmd == GET_BLOCK_SIZE) {
			DWORD* d = (DWORD*) buff;
			*d = 1;
			return 0;

		} else if (cmd == CTRL_TRIM) {
			return RES_OK;
		}

		return RES_PARERR;
	}
}

int FAT::vfsToFatRemaps[26];
int FAT::fats;


FAT::FAT() : Filesystem()
{
	fats = 0;
	for (int i = 0; i < 26; ++i) {
		vfsToFatRemaps[i] = -1;
	}	
}

FAT::~FAT()
{

}

char* FAT::getName()
{
	return (char*) "FAT Filesystem Driver";
}


FileStatus FAT::getlabel(LogicalDisk* disk, int diskNum, char* returnBuffer, uint32_t* serial)
{
	char diskCmd[3] = "0:";
	if (vfsToFatRemaps[diskNum] == -1) {
		diskCmd[0] += fats;

		//doesn't matter, as we don't increment 'fats'
		vfsToFatRemaps[diskNum] = fats;
		fatToVFSRemaps[fats] = diskNum;

	} else {
		diskCmd[0] += vfsToFatRemaps[diskNum];
	}

	FRESULT res = f_getlabel(diskCmd, returnBuffer, serial);
	if (res == FR_OK) {
		return FileStatus::Success;
	} else {
		return FileStatus::Failure;
	}
}

FileStatus FAT::setlabel(LogicalDisk* disk, int diskNum, char* label)
{
	char diskCmd[64] = "0:";
	if (vfsToFatRemaps[diskNum] == -1) {
		diskCmd[0] += fats;

		//doesn't matter, as we don't increment 'fats'
		vfsToFatRemaps[diskNum] = fats;
		fatToVFSRemaps[fats] = diskNum;

	} else {
		diskCmd[0] += vfsToFatRemaps[diskNum];
	}
	strcat(diskCmd, label);
	
	FRESULT res = f_setlabel(diskCmd);
	if (res == FR_OK) {
		return FileStatus::Success;
	} else {
		return FileStatus::Failure;
	}

	return FileStatus::Success;
}

FileStatus FAT::format(LogicalDisk* disk, int diskNum, const char* typestr, int allocationUnit)
{
	int type = 0;
	if (!strcmp(typestr, "FAT")) type = FM_FAT;
	else if (!strcmp(typestr, "FAT12")) type = FM_FAT;
	else if (!strcmp(typestr, "FAT16")) type = FM_FAT;
	else if (!strcmp(typestr, "FAT32")) type = FM_FAT32;
	else if (!strcmp(typestr, "EXFAT")) type = FM_EXFAT;
	else {
		return FileStatus::FormatNotSupported;
	}

	char diskCmd[3] = "0:";
	if (vfsToFatRemaps[diskNum] == -1) {
		diskCmd[0] += fats;

		//doesn't matter, as we don't increment 'fats'
		vfsToFatRemaps[diskNum] = fats;
		fatToVFSRemaps[fats] = diskNum;

	} else {
		diskCmd[0] += vfsToFatRemaps[diskNum];
	}

	MKFS_PARM opt;
	opt.fmt = type;
	opt.au_size = allocationUnit;
	opt.align = 0;
	opt.n_fat = 2;
	opt.n_root = 0;

	void* workBuffer = malloc(FF_MAX_SS * 16);
	FRESULT res = f_mkfs(diskCmd, &opt, (BYTE*) workBuffer, FF_MAX_SS * 16);

	if (res == FR_OK) {
		return FileStatus::Success;
	} else if (res == FR_MKFS_ABORTED) {
		return FileStatus::FormatDidntStart;
	} else {
		return FileStatus::Failure;
	}
}

bool FAT::tryMount(LogicalDisk* disk, int diskNum)
{
	if (fats == 20) {
		panic("TOO MUCH FAT!");
		return false;
	}
	if (disk->physDisk->sectorSize != 512) {
		return false;
	}

	bool mountable = false;

	if (vfsToFatRemaps[diskNum] != -1) {
		return true;
	}

	char diskCmd[3] = "0:";
	diskCmd[0] += fats;

	vfsToFatRemaps[diskNum] = fats;
	fatToVFSRemaps[fats] = diskNum;

	FATFS* fff = (FATFS*) malloc(sizeof(FATFS));

	FRESULT r = f_mount(fff, diskCmd, 0);

	if (r != FR_OK) {
		rfree(fff);
		return false;
	}

	char opentest[256];
	memset(opentest, 0, 256);
	strcat(opentest, diskCmd);
	strcat(opentest, "/DUMMY.TXT");		//doesn't need to exist

	FIL fptest;
	r = f_open(&fptest, opentest, FA_READ);

	switch (r) {
	case FR_OK:					//if it could be read, that means it exists and the FS works
	case FR_NO_PATH:			//could not file file/dir is not actually bad, as it means we
	case FR_NO_FILE:			//actually have a file system (we didn't get FR_NO_FILESYSTEM)
		mountable = true;
		f_close(&fptest);
		break;
	default:							//FR_NO_FILESYSTEM
		rfree(fff);
		f_mount(0, diskCmd, 0);                     // Unmount the drive
		return false;
	}

	if (mountable) {
		++fats;
	}

	return mountable;
}

void FAT::fixFilepath(char* path)
{
	if (path[0] >= 'A') {
		path[0] -= 'A';
		path[0] = vfsToFatRemaps[(int) path[0]] + '0';
	}
}

uint64_t FAT::allocateSwapfile(const char* filename, int megs)
{
	char buff[1024];
	int i, br;
	File* f = new File(filename, kernelProcess);
	f->unlink();
	f->open(FILE_OPEN_WRITE_NORMAL);
	FIL* fsData = (FIL*) f->fsSpecificData;
	f_expand(fsData, megs * 1024 * 1024, 1);
	f->write(1024, buff, &br);
	f->write(1024, buff, &br);
	f->write(1024, buff, &br);
	f->write(1024, buff, &br);
	f->close();

	f->open(FileOpenMode::Read);
	f->read(4, &i, &br);
	fsData = (FIL*) f->fsSpecificData;

	size_t retV = fsData->sect;

	f->close();
	return retV;
}

FileStatus FAT::open(const char* __fn, void** ptr, FileOpenMode mode)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;
	char path[256];
	strcpy(path, __fn);
	fixFilepath(path);

	BYTE fatmode = 0;

	if ((int) mode & (int)FileOpenMode::Read) {
		fatmode |= FA_READ;
	}

	if ((int) mode & (int) FileOpenMode::Append) {
		fatmode |= FA_OPEN_APPEND;
		fatmode |= FA_WRITE;
	}

	if ((int) mode & (int) FileOpenMode::Write) {
		fatmode |= FA_WRITE;
	}

	if ((int) mode & (int) FileOpenMode::CreateNew) {
		fatmode |= FA_CREATE_NEW;
	}

	if ((int) mode & (int) FileOpenMode::CreateAlways) {
		fatmode |= FA_CREATE_ALWAYS;
	}

	*ptr = malloc(sizeof(FIL));

	FRESULT res = f_open((FIL*) *ptr, path, fatmode);

	if (res != FR_OK) {
		return FileStatus::Failure;
	}

	return FileStatus::Success;
}

FileStatus FAT::openDir(const char* __fn, void** ptr)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;
	char path[256];
	strcpy(path, __fn);
	fixFilepath(path);

	*ptr = malloc(sizeof(DIR));

	FRESULT res = f_opendir((DIR*) *ptr, path);

	if (res != FR_OK) {
		return FileStatus::Failure;
	}

	return FileStatus::Success;
}

FileStatus FAT::readDir(void* ptr, size_t bytes, void* where, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;

	UINT br;
	FILINFO finfo;
	FRESULT r = f_readdir((DIR*) ptr, &finfo);

	struct dirent dent;
	dent.d_ino = 0;
	dent.d_namlen = strlen(finfo.fname);
	dent.d_type = finfo.fattrib & AM_DIR ? DT_DIR : DT_REG;
	strcpy(dent.d_name, finfo.fname);

	memcpy(where, &dent, bytes);
	*bytesRead = sizeof(dent);

	if (!finfo.fname[0]) return FileStatus::DirectoryEOF;

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::read(void* ptr, size_t bytes, void* where, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;

	UINT br;
	FRESULT r = f_read((FIL*) ptr, where, bytes, &br);
	*bytesRead = br;

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:		
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::write(void* ptr, size_t bytes, void* where, int* bytesWritten)
{
	if (ptr == nullptr || bytesWritten == nullptr) return FileStatus::InvalidArgument;

	UINT br;
	FRESULT r = f_write((FIL*) ptr, where, bytes, &br);
	*bytesWritten = br;

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::close(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	FRESULT r = f_close((FIL*) ptr);
	free(ptr);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;	

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}


FileStatus FAT::closeDir(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	FRESULT r = f_closedir((DIR*) ptr);
	free(ptr);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::seek(void* ptr, uint64_t offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	FRESULT r = f_lseek((FIL*) ptr, offset);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::tell(void* ptr, uint64_t* offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (offset == nullptr) return FileStatus::InvalidArgument;

	*offset = f_tell(((FIL*) ptr));

	return FileStatus::Success;
}

FileStatus FAT::stat(void* ptr, uint64_t* size)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;

	*size = f_size(((FIL*) ptr));

	return FileStatus::Success;
}

FileStatus FAT::stat(const char* path, uint64_t* size, bool* directory)
{
	if (path == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;
	if (directory == nullptr) return FileStatus::InvalidArgument;

	char filename[256];
	strcpy(filename, path);
	fixFilepath(filename);

	FILINFO fno;
	FRESULT r = f_stat((const TCHAR*) filename, &fno);
	switch (r) {
	case FR_OK:
		*directory = (fno.fattrib & AM_DIR) ? 1 : 0;
		*size = fno.fsize;
		return FileStatus::Success;

	case FR_NO_FILE:
		return FileStatus::NotExist;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::unlink(const char* file)
{
	if (file == nullptr) {
		return FileStatus::InvalidArgument;
	}

	char filename[256];
	strcpy(filename, file);
	fixFilepath(filename);

	FRESULT r = f_unlink((const TCHAR*) filename);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::chfatattr(const char* path, uint8_t clearBits, uint8_t setBits)
{
	if (path == nullptr) {
		return FileStatus::InvalidArgument;
	}

	char filename[256];
	strcpy(filename, path);
	fixFilepath(filename);

	uint8_t attr = 0;
	uint8_t mask = 0;

	if (setBits & ((int) FATAttribute::ReadOnly))	attr |= AM_RDO;
	if (setBits & ((int) FATAttribute::Archive))	attr |= AM_ARC;
	if (setBits & ((int) FATAttribute::System))		attr |= AM_SYS;
	if (setBits & ((int) FATAttribute::Hidden))		attr |= AM_HID;

	if (clearBits & ((int) FATAttribute::ReadOnly))	mask |= AM_RDO;
	if (clearBits & ((int) FATAttribute::Archive))	mask |= AM_ARC;
	if (clearBits & ((int) FATAttribute::System))	mask |= AM_SYS;
	if (clearBits & ((int) FATAttribute::Hidden))	mask |= AM_HID;

	mask |= attr;

	FRESULT r = f_chmod((const TCHAR*) filename, attr, mask);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::rename(const char* old, const char* _new)
{	
	if (old == nullptr || _new == nullptr) {
		return FileStatus::InvalidArgument;
	}

	char realOld[256];
	strcpy(realOld, old);
	fixFilepath(realOld);

	char realNew[256];
	strcpy(realNew, _new);
	fixFilepath(realNew);

	FRESULT r = f_rename((const TCHAR*) realOld, (const TCHAR*) realNew);

	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

FileStatus FAT::mkdir(const char* file)
{
	if (file == nullptr) {
		return FileStatus::InvalidArgument;
	}

	char filename[256];
	strcpy(filename, file);
	fixFilepath(filename);

	FRESULT r = f_mkdir((const TCHAR*) filename);
	
	switch (r) {
	case FR_OK:
		return FileStatus::Success;

	default:
		return FileStatus::Failure;
	}

	return FileStatus::Failure;
}

bool FAT::exists(const char* file)
{
	FRESULT fr;
	FILINFO fno;

	char filename[256];
	strcpy(filename, file);
	fixFilepath(filename);

	fr = f_stat(filename, &fno);
	switch (fr) {
	case FR_OK:
		return true;

	default:
		return false;
	}

	return false;
}
