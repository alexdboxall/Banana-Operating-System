#include "sys/syscalls.hpp"
#include "core/common.hpp"
#include "core/kheap.hpp"
#include "libk/string.h"
#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "core/virtmgr.hpp"
#include "thr/elf.hpp"
#include "hal/timer.hpp"
#include "core/unixfile.hpp"
#include "core/pipe.hpp"
#include "core/terminal.hpp"
#include "hal/clock.hpp"
#include "fs/vfs.hpp"
#include "hw/cpu.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint64_t (*systemCallHandlers[128])(regs* r);

namespace Sys
{
	uint64_t yield(regs* r);
	uint64_t exit(regs* r);
	uint64_t sbrk(regs* r);
	uint64_t write(regs* r);
	uint64_t read(regs* r);

	uint64_t loadDLL(regs* r);
}

uint64_t sysCallGetPID(regs* r)
{
	return currentTaskTCB->processRelatedTo->pid;
}

uint64_t sysCallGetCwd(regs* r)
{
	return getcwd(currentTaskTCB->processRelatedTo, (char*) r->ebx, r->ecx);
}

uint64_t sysCallSetCwd(regs* r)
{
	return setcwd(currentTaskTCB->processRelatedTo, (char*) r->ebx);
}

int string_ends_with(const char* str, const char* suffix)
{
	int str_len = strlen(str);
	int suffix_len = strlen(suffix);

	return
		(str_len >= suffix_len) &&
		(0 == strcmp(str + (str_len - suffix_len), suffix));
}

uint64_t sysCallOpen(regs* r)
{
	if (!r->ebx) {
		return -1;
	}
	if (!r->edx) {
		return -1;
	}

	char fname[256];
	standardiseFiles(fname, (const char*) r->edx, "Z:/");

	for (int i = strlen(fname) - 1; i; --i) {
		if (fname[i] == '.' || fname[i] == ':') {
			fname[i] = 0;
			break;
		}
		fname[i] = 0;
	}

	if (string_ends_with((const char*) r->edx, "/con") || string_ends_with((const char*) r->edx, "\\con") || !strcmp((const char*) r->edx, "con") || string_ends_with(fname, "/con")) {
		*((uint64_t*) r->ebx) = RESERVED_FD_CON;
		kprintf("con fd = 0x%X\n", (uint32_t) (*((uint64_t*) r->ebx)));
		kprintf("opened con!\n");
		return 0;
	}
	if (string_ends_with((const char*) r->edx, "/nul") || string_ends_with((const char*) r->edx, "\\nul") || !strcmp((const char*) r->edx, "nul") || string_ends_with(fname, "/nul")) {
		*((uint64_t*) r->ebx) = RESERVED_FD_NUL;
		return 0;
	}

	File* f = new File((const char*) r->edx, currentTaskTCB->processRelatedTo);
	if (!f) {
		return -1;
	}

	int mode = 0;
	r->ecx &= 0xFF;

	if (r->ecx & 1) {
		mode |= (((int) mode) | ((int) FileOpenMode::Read));
	}

	if (r->ecx & 2) {
		mode |= (((int) mode) | ((int) FileOpenMode::Write));
	}

	if (r->ecx & 4) {
		mode |= (((int) mode) | ((int) FileOpenMode::Append));
	}

	if (r->ecx & 8) {
		mode |= (((int) mode) | ((int) FileOpenMode::CreateNew));
		mode |= (((int) mode) | ((int) FileOpenMode::Write));
	}

	if (r->ecx & 16) {
		mode |= (((int) mode) | ((int) FileOpenMode::CreateAlways));
		mode |= (((int) mode) | ((int) FileOpenMode::Write));
	}

	FileStatus s = f->open((FileOpenMode) mode);
	if (s != FileStatus::Success) {
		return -1;
	}

	*((uint64_t*) r->ebx) = ((UnixFile*) f)->getFileDescriptor();
	
	return 0;
}

uint64_t sysCallSeek(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Seeking special file. %d\n", r->ebx);
		return -1;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	FileStatus st = ((File*) file)->seek(r->ecx);

	if (st != FileStatus::Success) {
		return -1;
	}

	return 0;
}

uint64_t sysCallTell(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Telling special file. %d\n", r->ebx);
		*((uint64_t*) r->ecx) = 0;
		return 0;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	FileStatus st = ((File*) file)->tell ((uint64_t*) r->ecx);

	if (st != FileStatus::Success) {
		return -1;
	}

	return 0;
}

uint64_t sysCallSizeFromFilename(regs* r)
{
	char* filename = (char*) r->ebx;
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Statting special file. %d\n", r->ebx);
		*((uint64_t*) r->ecx) = 0;
		return 0;
	} else {
		file = new File(filename, currentTaskTCB->processRelatedTo);
	}

	bool dummy;
	FileStatus st = ((File*) file)->stat((uint64_t*) r->ecx, &dummy);

	delete file;

	if (st != FileStatus::Success) {
		return -1;
	}

	return 0;
}

uint64_t sysCallSize(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Statting special file. %d\n", r->ebx);
		*((uint64_t*) r->ecx) = 0;
		return 0;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	bool dummy;
	FileStatus st = ((File*) file)->stat((uint64_t*) r->ecx, &dummy);

	if (st != FileStatus::Success) {
		return -1;
	}

	return 0;
}

uint64_t sysCallClose(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx == RESERVED_FD_CON) {
		kprintf("closing con.\n");
		return 0;
	} else if (r->ebx == RESERVED_FD_NUL) {
		kprintf("closing nul.\n");
		return 0;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Closing non-con/nul special file. %d\n", r->ebx);
		return -1;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	((File*) file)->close();
	delete ((File*) file);

	return 0;
}

uint64_t sysCallOpenDir(regs* r)
{
	if (!r->ebx) {
		return -1;
	}

	Directory* f = new Directory((const char*) r->edx, currentTaskTCB->processRelatedTo);
	if (!f) {
		return -1;
	}

	FileStatus s = f->open();
	if (s != FileStatus::Success) {
		return -1;
	}

	*((uint64_t*) r->ebx) = ((UnixFile*) f)->getFileDescriptor();

	return 0;
}

//	return SystemCall(ReadDir, 0, fd, (size_t) dirp);		// 0 = success, 1 = EOF / ERROR

uint64_t sysCallReadDir(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ecx <= 2) {
		return 1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Readdir special file (oops!). %d\n", r->ebx);
		return -1;
	} else {
		file = getFromFileDescriptor(r->ecx);
	}

	if (file == nullptr) {
		return -1;
	}

	int br = 0;

	FileStatus status = file->read(sizeof(struct dirent), (void*) r->edx, &br);
	struct dirent* de = (struct dirent*) (size_t) r->edx;

	if (status == FileStatus::Success) {
		return 0;
	} else if (status == FileStatus::DirectoryEOF) {
		return 1;
	}

	return 2;
}

uint64_t sysCallSeekDir(regs* r)
{
	return 0;
}

uint64_t sysCallTellDir(regs* r)
{
	return 0;
}

uint64_t sysCallMakeDir(regs* r)
{
	Directory* d = new Directory((const char*) r->edx, currentTaskTCB->processRelatedTo);
	if (d) {
		FileStatus st = d->create();
		d->close();
		delete d;

		if (st == FileStatus::Success) {
			return 0;
		}
	}

	return -1;
}

uint64_t sysCallCloseDir(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		kprintf("Closedir special file (oops!). %d\n", r->ebx);
		return -1;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	((Directory*) file)->close();
	delete ((Directory*) file);

	return 0;
}

uint64_t sysCallVerify(regs* r)
{
	return r->ebx;
}

uint64_t sysCallWait(regs* r)
{
	return waitTask(r->ebx, (int*) r->edx, r->ecx);
}

uint64_t sysCallFork(regs* r)
{
	return -1;
}

uint64_t sysCallExecve(regs* r)
{
	return -1;
}

uint64_t sysCallRmdir(regs* r)
{
	char* name = (char*) r->edx;

	File* f = new File(name, currentTaskTCB->processRelatedTo);
	FileStatus res = f->unlink();
	delete f;
	
	if (res == FileStatus::Success) {
		return 0;
	}

	return -1;
}

uint64_t sysCallUnlink(regs* r)
{
	char* name = (char*) r->edx;

	File* f = new File(name, currentTaskTCB->processRelatedTo);
	FileStatus res = f->unlink();
	delete f;

	if (res == FileStatus::Success) {
		return 0;
	}

	return -1;
}

uint64_t sysCallGetArgc(regs* r)
{
	return currentTaskTCB->processRelatedTo->argc;
}

uint64_t sysCallGetArgv(regs* r)
{
	if ((int) r->ebx < 0 || (int) r->ebx >= currentTaskTCB->processRelatedTo->argc) {
		return 0;
	}

	if (!currentTaskTCB->processRelatedTo->argv[r->ebx]) {
		return 1;
	}

	strcpy((char*) r->edx, currentTaskTCB->processRelatedTo->argv[r->ebx]);
	return 0;
}

uint64_t sysCallRealpath(regs* r)
{
	if (r->ecx == 0 || r->edx == 0) {
		return 1;
	}

	char* path = (char*) r->ecx;
	standardiseFiles((char*) r->edx, path, currentTaskTCB->processRelatedTo->cwd);
	return 0;
}

uint64_t sysCallTTYName(regs* r)
{
	if (r->edx == 0) {
		return 1;
	}

	UnixFile* file;
	if (r->ebx <= 2 || r->ebx == RESERVED_FD_CON) {
		file = currentTaskTCB->processRelatedTo->terminal;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}
	if (!file) {
		return 1;
	}

	if (!file->isAtty()) {
		return 2;
	}

	VgaText* terminal = static_cast<VgaText*>(file);
	strcpy((char*) r->edx, terminal->name);
	return 0;
}

uint64_t sysCallIsATTY(regs* r)
{
	UnixFile* file;
	if (r->ebx <= 2 || r->ebx == RESERVED_FD_CON) {
		file = currentTaskTCB->processRelatedTo->terminal;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	if (!file) {
		return -1;
	}

	int is = file->isAtty();
	return is;
}

uint64_t sysCallUSleep(regs* r)
{
	//ensure they both go to 64 bit
	uint64_t low = r->ebx;
	uint64_t high = r->ecx;

	uint64_t micro = low | high << 32;

	nanoSleep(micro * 1000);
	return 0;
}

uint64_t sysCallSpawn(regs* r)
{
	if (r->edx == 0) return 0;

	kprintf("Spwaning!\n");

	Process* p = new Process((const char*) r->edx, currentTaskTCB->processRelatedTo, (char**) r->ecx);
	if (p->failedToLoadProgram) {
		return 0;
	}

	kprintf("Spwaning B!\n");

	p->createUserThread();
	return p->pid;
}

uint64_t sysCallGetEnv(regs* r)
{
	char* addr = (char*) r->edx;
	int num = r->ebx;

	kprintf("sysCallGetEnv\n");

	if (r->ecx == 0) {
		//get length
		if (num == 0) {
			return strlen("PATH=C:/Banana/System;C:/Banana/Applications;C:/Banana/Applications/System;");
		} else {
			
		}
	} else {
		if (num == 0) {
			strcpy(addr, "PATH=C:/Banana/System;C:/Banana/Applications;C:/Banana/Applications/System;");
		} else {
			*addr = 0;
		}
	}
	

	return 0;
}

uint64_t sysAppSettings(regs* r)
{
	AppSettings_t* appset = (AppSettings_t*) r->edx;

	if (appset->valid != _APPSETTINGS_VALIDATION_V1) {
		return 1;
	}

	if (appset->mode == _APPSETTINGS_MODE_SET_NAME) {
		memset(currentTaskTCB->processRelatedTo->taskname, 0, sizeof(currentTaskTCB->processRelatedTo->taskname));
		memcpy(currentTaskTCB->processRelatedTo->taskname, appset->string, sizeof(currentTaskTCB->processRelatedTo->taskname) - 1);
		currentTaskTCB->processRelatedTo->terminal->setTitle(currentTaskTCB->processRelatedTo->taskname);

	} else if (appset->mode == _APPSETTINGS_MODE_SET_FLAGS) {
		currentTaskTCB->processRelatedTo->terminal->unbufferedKeyboard = appset->unbufferedKeyboard;

	} else if (appset->mode == _APPSETTINGS_MODE_UNKNOWN) {
		return 2;

	} else if (appset->mode == _APPSETTINGS_MODE_SET_TITLECOLOUR) {
		currentTaskTCB->processRelatedTo->terminal->setTitleColour((VgaColour) (appset->intData & 0xF));
		currentTaskTCB->processRelatedTo->terminal->setTitleTextColour((VgaColour) ((appset->intData >> 4) & 0xF));

	} else {
		return appset->mode + 1000;
	}

	return 0;
}

uint64_t sysFormatDisk(regs* r)
{
	Filesystem* current = installedFilesystems;
	while (current) {
		FileStatus status = current->format(disks[r->ebx], r->ebx, (const char*) r->edx, r->ecx);
		if (status != FileStatus::FormatNotSupported) {
			if (status == FileStatus::Success) {
				return 0;
			} else if (status == FileStatus::FormatDidntStart) {
				return 1;
			} else {
				return 2;
			}
		}
		current = current->next;
	}
	return 3;
}

uint64_t sysSetDiskVolumeLabel(regs* r)
{
	if (r->ebx > 25 || !disks[r->ebx] || !r->edx) return -2;
	return (int) disks[r->ebx]->fs->setlabel(disks[r->ebx], r->ebx, (char*) r->edx);
}

uint64_t sysGetDiskVolumeLabel(regs* r)
{
	if (r->ebx > 25 || !disks[r->ebx] || !r->edx || !r->ecx) return -2;
	return (int) disks[r->ebx]->fs->getlabel(disks[r->ebx], r->ebx, (char*) r->edx, (uint32_t*) r->ecx);
}

uint64_t sysSetFatAttrib(regs* r)
{
	char* name = (char*) r->edx;

	File* f = new File(name, currentTaskTCB->processRelatedTo);
	FileStatus res = f->chfatattr(r->ecx & 0xFF, (r->ecx >> 8) & 0xFF);
	delete f;

	if (res == FileStatus::Success) {
		return 0;
	}

	return -1;
}

uint64_t sysPanic(regs* r)
{
	panic((char*) r->edx);
	panic("COULDN'T PANIC");
	return 1;
}

uint64_t sysShutdown(regs* r)
{
	if (r->ebx == 0) {
		computer->close(0, 0, nullptr);
		return -1;

	} else if (r->ebx == 1) {
		extern void (*systemSleepFunction)();
		if (systemSleepFunction) {
			systemSleepFunction();
		}
		return 0;

	} else if (r->ebx == 2) {
		computer->close(1, 0, nullptr);
		return -1;

	}

	return -1;
}

uint64_t sysPipe(regs* r)
{
	int* readEnd = (int*) r->ebx;
	int* writeEnd = (int*) r->ecx;

	Pipe* p = new Pipe();
	*readEnd = p->getFileDescriptor();
	*writeEnd = p->getFileDescriptor();

	return 0;
}

uint64_t sysGetUnixTime(regs* r)
{
	//subtract 70 years, because we use a 1900 epoch, unix has a 1970 epoch
	return computer->clock->timeInSecondsLocal();
}


#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void setupSystemCalls()
{
	systemCallHandlers[(int) SystemCallNumber::Yield] = Sys::yield;
	systemCallHandlers[(int) SystemCallNumber::Exit] = Sys::exit;
	systemCallHandlers[(int) SystemCallNumber::Sbrk] = Sys::sbrk;
	systemCallHandlers[(int) SystemCallNumber::Write] = Sys::write;
	systemCallHandlers[(int) SystemCallNumber::Read] = Sys::read;
	systemCallHandlers[(int) SystemCallNumber::GetPID] = sysCallGetPID;
	systemCallHandlers[(int) SystemCallNumber::GetCwd] = sysCallGetCwd;
	systemCallHandlers[(int) SystemCallNumber::SetCwd] = sysCallSetCwd;
	systemCallHandlers[(int) SystemCallNumber::Close] = sysCallClose;
	systemCallHandlers[(int) SystemCallNumber::Open] = sysCallOpen;
	systemCallHandlers[(int) SystemCallNumber::OpenDir] = sysCallOpenDir;
	systemCallHandlers[(int) SystemCallNumber::ReadDir] = sysCallReadDir;
	systemCallHandlers[(int) SystemCallNumber::SeekDir] = sysCallSeekDir;
	systemCallHandlers[(int) SystemCallNumber::TellDir] = sysCallTellDir;
	systemCallHandlers[(int) SystemCallNumber::MakeDir] = sysCallMakeDir;
	systemCallHandlers[(int) SystemCallNumber::CloseDir] = sysCallCloseDir;
	systemCallHandlers[(int) SystemCallNumber::Seek] = sysCallSeek;
	systemCallHandlers[(int) SystemCallNumber::Tell] = sysCallTell;
	systemCallHandlers[(int) SystemCallNumber::Size] = sysCallSize;
	systemCallHandlers[(int) SystemCallNumber::Verify] = sysCallVerify;
	systemCallHandlers[(int) SystemCallNumber::Wait] = sysCallWait;
	systemCallHandlers[(int) SystemCallNumber::Fork] = sysCallFork;
	systemCallHandlers[(int) SystemCallNumber::Execve] = sysCallExecve;
	systemCallHandlers[(int) SystemCallNumber::Rmdir] = sysCallRmdir;
	systemCallHandlers[(int) SystemCallNumber::Unlink] = sysCallUnlink;
	systemCallHandlers[(int) SystemCallNumber::GetArgc] = sysCallGetArgc;
	systemCallHandlers[(int) SystemCallNumber::GetArgv] = sysCallGetArgv;
	systemCallHandlers[(int) SystemCallNumber::Realpath] = sysCallRealpath;
	systemCallHandlers[(int) SystemCallNumber::TTYName] = sysCallTTYName;
	systemCallHandlers[(int) SystemCallNumber::IsATTY] = sysCallIsATTY;
	systemCallHandlers[(int) SystemCallNumber::USleep] = sysCallUSleep;
	systemCallHandlers[(int) SystemCallNumber::SizeFromFilename] = sysCallSizeFromFilename;
	systemCallHandlers[(int) SystemCallNumber::Spawn] = sysCallSpawn;
	systemCallHandlers[(int) SystemCallNumber::GetEnv] = sysCallGetEnv;
	systemCallHandlers[(int) SystemCallNumber::AppSettings] = sysAppSettings;
	systemCallHandlers[(int) SystemCallNumber::FormatDisk] = sysFormatDisk;
	systemCallHandlers[(int) SystemCallNumber::SetDiskVolumeLabel] = sysSetDiskVolumeLabel;
	systemCallHandlers[(int) SystemCallNumber::GetDiskVolumeLabel] = sysGetDiskVolumeLabel;
	systemCallHandlers[(int) SystemCallNumber::SetFATAttrib] = sysSetFatAttrib;
	systemCallHandlers[(int) SystemCallNumber::Panic] = sysPanic;
	systemCallHandlers[(int) SystemCallNumber::Shutdown] = sysShutdown;
	systemCallHandlers[(int) SystemCallNumber::Pipe] = sysPipe;
	systemCallHandlers[(int) SystemCallNumber::GetUnixTime] = sysGetUnixTime;
	systemCallHandlers[(int) SystemCallNumber::LoadDLL] = Sys::loadDLL;
}

uint64_t systemCall(regs* r, void* context)
{	
	if (r->eax < 128 && systemCallHandlers[r->eax]) {
		kprintf("syscall 0x%X\n", r->eax);
		r->eax = systemCallHandlers[r->eax](r);
		kprintf("syscall done.\n");
	} else {
		kprintf("Invalid syscall %d\n", r->eax);
	}

	return 0xDEADBEEF;
}