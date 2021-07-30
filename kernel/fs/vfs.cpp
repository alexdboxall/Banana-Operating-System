#include "core/main.hpp"
#include "thr/prcssthr.hpp"
#include "fs/vfs.hpp" 
#include "fs/symlink.hpp" 
#include "hal/logidisk.hpp"
#include "libk/string.h"

#include "fs/fat/vfslink.hpp" 
#include "fs/iso9660/vfslink.hpp" 
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

Filesystem* installedFilesystems = nullptr;

Filesystem::Filesystem()
{
	this->next = installedFilesystems;
	installedFilesystems = this;
}

Filesystem::~Filesystem()
{

}

namespace Fs
{
	int getcwd(Process* process, char* buffer, int bytes)
	{
		int i = 0;
		for (i = 0; i < bytes; ++i) {
			buffer[i] = process->cwd[i];
			if (buffer[i] == 0) return 0;
		}
		buffer[i] = 0;
		return 0;
	}

	int setcwd(Process* process, char* buffer)
	{
		char tmpbuffer[512];
		Fs::standardiseFiles(tmpbuffer, buffer, process->cwd);

		//i.e. the root directory, for which 'stat' won't work on (it has no directory entry)
		if (strlen(tmpbuffer) <= 2 || (strlen(tmpbuffer) == 3 && tmpbuffer[2] == '/')) {
			int diskNo = tmpbuffer[0] - 'A';

			if (disks[diskNo] && disks[diskNo]->fs == nullptr) {
				disks[diskNo]->mount();
			}

			if (diskNo >= 0 && diskNo <= 25) {
				if (disks[diskNo] == nullptr) {
					return 5;
				}
				if (disks[diskNo]->fs == nullptr) {
					return 6;
				}

				strcpy(process->cwd, tmpbuffer);
				return 0;

			} else {
				return 3;
			}
			return 4;
		}

		File* f = new File(tmpbuffer, process);

		uint64_t sz;
		bool dir = false;

		FileStatus status = f->stat(&sz, &dir);

		if (status == FileStatus::NotExist) {
			delete f;
			return 1;

		} else if (dir == false) {
			delete f;
			return 2;

		} else if (status != FileStatus::Success) {
			delete f;
			return 1;
		}

		delete f;
		strcpy(process->cwd, tmpbuffer);
		return 0;
	}

	void initVFS()
	{
		//just so the constructors can be called, so it gets added to the filesystem list
		FAT* f = new FAT();
		ISO9660* i = new ISO9660();
	}

	void standardiseFiles(char* outBuffer, const char* filename, const char* cwd, bool followSymlinks)
	{
		char middleBuffer[1024];
		memset(middleBuffer, 0, 1024);

		//if the filename has its own directory
		if (filename[1] == ':') {
			//copy it directly in
			strcpy(middleBuffer, filename);

		} else if (filename[0] == '/' || filename[0] == '\\') {
			//copy it directly in
			middleBuffer[0] = cwd[0] >= 'a' ? cwd[0] - 32 : cwd[0];
			middleBuffer[1] = ':';
			middleBuffer[2] = '/';
			strcat(middleBuffer, filename);

		} else {
			//otherwise, copy them both in 
			strcpy(middleBuffer, cwd);
			strcat(middleBuffer, "/");
			strcat(middleBuffer, filename);
		}

		//ensure things are correct
		middleBuffer[0] = middleBuffer[0] >= 'a' ? middleBuffer[0] - 32 : middleBuffer[0];
		middleBuffer[1] = ':';
		middleBuffer[2] = '/';

		outBuffer[0] = middleBuffer[0];
		outBuffer[1] = middleBuffer[1];
		outBuffer[2] = middleBuffer[2];
		outBuffer[3] = 0;

		int op = 3;
		int mp = 3;

		while (middleBuffer[mp]) {
			if ((middleBuffer[mp] == '/' || middleBuffer[mp] == '\\') && outBuffer[op - 1] != '/') {
				outBuffer[op++] = '/';
				++mp;

			} else if (middleBuffer[mp - 1] == '/' && middleBuffer[mp] == '.' && middleBuffer[mp + 1] != '.' && middleBuffer[mp + 2] != '.') {
				do {
					++mp;
				} while (middleBuffer[mp] == '/' || middleBuffer[mp] == '\\');

			} else if (middleBuffer[mp - 1] == '/' && middleBuffer[mp] == '.' && middleBuffer[mp + 1] == '.' && middleBuffer[mp + 2] != '.') {
				if (op == 3) {
					++mp;
					continue;
				}
				++mp;
				do {
					++mp;
				} while (middleBuffer[mp] == '/' || middleBuffer[mp] == '\\');

				--op;

				//go back past the slash, erasing as we go
				while (outBuffer[op] == '/') {
					outBuffer[op] = 0;
					--op;
				}

				//now that we're on a character, keep going until we hit a slash, erasing as we go
				while (outBuffer[op] != '/') {
					outBuffer[op] = 0;
					--op;
				}
				++op;		//move off the slash

			} else if (middleBuffer[mp] != '/' && middleBuffer[mp] != '\\') {
				outBuffer[op++] = middleBuffer[mp++];

			} else {
				mp++;
			}

		}
		outBuffer[op] = 0;
		while ((outBuffer[strlen(outBuffer) - 1] == '.' || outBuffer[strlen(outBuffer) - 1] == '/') && outBuffer[strlen(outBuffer) - 2] != ':') outBuffer[strlen(outBuffer) - 1] = 0;
		kprintf("OUTBF: %s, %c, %c\n", outBuffer, outBuffer[strlen(outBuffer) - 1], outBuffer[strlen(outBuffer) - 2]);

		if (outBuffer[strlen(outBuffer) - 1] == '@' && outBuffer[strlen(outBuffer) - 2] == '@') {
			outBuffer[strlen(outBuffer) - 1] = 0;
			outBuffer[strlen(outBuffer) - 1] = 0;
			kprintf("AVOIDED SYMLINK: %s\n", outBuffer);
			return;
		}

		int symrecur = 0;
		while (followSymlinks) {
			strcpy(middleBuffer, outBuffer);

			int deref = KeDereferenceSymlink(middleBuffer, outBuffer);
			if (deref != 1) break;

			if (symrecur++ == 20) {
				KePanic("TODO: HANDLE TOO MANY NESTED SYMLINKS");
			}
		}
	}
}

File::File(const char* filename, Process* process) : UnixFile()
{
	Fs::standardiseFiles(this->filepath, filename, process->cwd, process != kernelProcess);

	this->driveNo = this->filepath[0] - 'A';
	fileOpen = false;

	if (disks[driveNo] && disks[driveNo]->fs == nullptr) {
		disks[driveNo]->mount();
	}
}

File::~File()
{

}

FileStatus File::open(FileOpenMode mode)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	FileStatus r = disks[driveNo]->fs->open(filepath, &fsSpecificData, mode);
	if (r == FileStatus::Success) {
		fileOpen = true;
	}
	return r;
}

FileStatus File::read(uint64_t bytes, void* where, int* bytesRead)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->read(fsSpecificData, bytes, where, bytesRead);
}

FileStatus File::write(uint64_t bytes, void* where, int* bytesWritten)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->write(fsSpecificData, bytes, where, bytesWritten);
}

FileStatus File::close()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;
	fileOpen = false;
	return disks[driveNo]->fs->close(fsSpecificData);
}

FileStatus File::seek(uint64_t offset)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->seek(fsSpecificData, offset);
}

FileStatus File::truncate(uint64_t offset)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->truncate(fsSpecificData, offset);
}

FileStatus File::tell(uint64_t* pos)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->tell(fsSpecificData, pos);
}

FileStatus File::rewind()
{
	return seek(0);
}

FileStatus File::unlink()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->unlink(filepath);
}

FileStatus File::rename(const char* new_)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->rename(filepath, new_);
}

FileStatus File::chfatattr(uint8_t andMask, uint8_t orFlags)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->chfatattr(filepath, andMask, orFlags);
}

bool File::exists()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return false;
	return disks[driveNo]->fs->exists(filepath);
}

FileStatus File::stat(uint64_t* size, bool* directory)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;

	if (fileOpen) {
		FileStatus res = disks[driveNo]->fs->stat(fsSpecificData, size);
		*directory = false;
		return res;

	} else {
		return disks[driveNo]->fs->stat(filepath, size, directory);
	}
}







Directory::Directory(const char* filename, Process* process) : UnixFile()
{
	Fs::standardiseFiles(this->filepath, filename, process->cwd, process != kernelProcess);

	this->driveNo = this->filepath[0] - 'A';
	fileOpen = false;

	if (disks[driveNo] && disks[driveNo]->fs == nullptr) {
		disks[driveNo]->mount();
	}
}

Directory::~Directory()
{

}

FileStatus Directory::open()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	FileStatus r = disks[driveNo]->fs->openDir(filepath, &fsSpecificData);

	if (r == FileStatus::Success) {
		fileOpen = true;
	}

	return r;
}

FileStatus Directory::read(uint64_t bytes, void* where, int* bytesRead)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->readDir(fsSpecificData, bytes, where, bytesRead);
}

FileStatus Directory::write(uint64_t bytes, void* where, int* bytesWritten)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;

	return FileStatus::Failure;

	/*if (!fileOpen) return FileStatus::FileNotOpen;

	return disks[driveNo]->fs->writeDir(fsSpecificData, bytes, where, bytesWritten);*/
}

FileStatus Directory::close()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (!fileOpen) return FileStatus::FileNotOpen;
	fileOpen = false;
	return disks[driveNo]->fs->closeDir(fsSpecificData);

	/*if (!fileOpen) return FileStatus::FileNotOpen;
	fileOpen = false;
	return disks[driveNo]->fs->closeDir(fsSpecificData);*/
}

FileStatus Directory::unlink()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->unlink(filepath);
}

FileStatus Directory::rename(const char* new_)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->rename(filepath, new_);
}

bool Directory::exists()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return false;
	return disks[driveNo]->fs->exists(filepath);
}

FileStatus Directory::read(struct dirent* p)
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	int br;
	return read(sizeof(struct dirent), (void*) p, &br);
}

FileStatus Directory::create()
{
	if (driveNo > 25 || !disks[driveNo] || !disks[driveNo]->fs) return FileStatus::NoFilesystem;
	if (fileOpen) return FileStatus::FileOpen;

	return disks[driveNo]->fs->mkdir(filepath);
}

bool File::isAtty()
{
	return false;
}

bool Directory::isAtty()
{
	return false;
}

FileStatus Filesystem::getlabel(LogicalDisk* disk, int diskNum, char* returnBuffer, uint32_t* serial)
{
	return FileStatus::NotSupported;
}

FileStatus Filesystem::setlabel(LogicalDisk* disk, int diskNum, char* label)
{
	return FileStatus::NotSupported;
}

FileStatus Filesystem::chfatattr(const char* path, uint8_t andMask, uint8_t orFlags)
{
	return FileStatus::NotSupported;
}

uint64_t Filesystem::allocateSwapfile(const char* filename, int megs)
{
	return 0;
}