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

uint64_t SysYield(regs* r);
uint64_t SysExit(regs* r);
uint64_t SysSbrk(regs* r);
uint64_t SysWrite(regs* r);
uint64_t SysRead(regs* r);
uint64_t SysGetPID(regs* r);
uint64_t SysGetCwd(regs* r);
uint64_t SysSetCwd(regs* r);
uint64_t SysLoadDLL(regs* r);
uint64_t SysSetTime(regs* r);
uint64_t SysTimezone(regs* r);
uint64_t SysEject(regs* r);
uint64_t SysWsbe(regs* r);
uint64_t SysGetRAMData(regs* r);
uint64_t SysGetVGAPtr(regs* r);

int string_ends_with(const char* str, const char* suffix)
{
	int str_len = strlen(str);
	int suffix_len = strlen(suffix);

	return
		(str_len >= suffix_len) &&
		(0 == strcmp(str + (str_len - suffix_len), suffix));
}

uint64_t SysOpen(regs* r)
{
	if (!r->ebx) {
		return -1;
	}
	if (!r->edx) {
		return -1;
	}

	char fname[256];
	Fs::standardiseFiles(fname, (const char*) r->edx, "Z:/");

	for (int i = strlen(fname) - 1; i; --i) {
		if (fname[i] == '.' || fname[i] == ':') {
			fname[i] = 0;
			break;
		}
		fname[i] = 0;
	}

	if (string_ends_with((const char*) r->edx, "/con") || string_ends_with((const char*) r->edx, "\\con") || !strcmp((const char*) r->edx, "con") || string_ends_with(fname, "/con")) {
		*((uint64_t*) r->ebx) = RESERVED_FD_CON;
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

uint64_t SysSeek(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
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

uint64_t SysTell(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		*((uint64_t*) r->ecx) = 0;
		return 0;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	FileStatus st = ((File*) file)->tell((uint64_t*) r->ecx);

	if (st != FileStatus::Success) {
		return -1;
	}

	return 0;
}

uint64_t SysSizeFromFilename(regs* r)
{
	char* filename = (char*) r->ebx;
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
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

uint64_t SysSize(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
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

uint64_t SysClose(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx == RESERVED_FD_CON) {
		return 0;
	} else if (r->ebx == RESERVED_FD_NUL) {
		return 0;
	} else if (r->ebx > RESERVED_FD_START) {
		return -1;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	((File*) file)->close();
	delete ((File*) file);

	return 0;
}

uint64_t SysOpenDir(regs* r)
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

uint64_t SysReadDir(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ecx <= 2) {
		return 1;
	} else if (r->ebx > RESERVED_FD_START) {
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

uint64_t SysSeekDir(regs* r)
{
	return 0;
}

uint64_t SysTellDir(regs* r)
{
	return 0;
}

uint64_t SysMakeDir(regs* r)
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

uint64_t SysCloseDir(regs* r)
{
	UnixFile* file = nullptr;

	if (r->ebx <= 2) {
		return -1;
	} else if (r->ebx > RESERVED_FD_START) {
		return -1;
	} else {
		file = getFromFileDescriptor(r->ebx);
	}

	((Directory*) file)->close();
	delete ((Directory*) file);

	return 0;
}

uint64_t SysVerify(regs* r)
{
	return r->ebx;
}

uint64_t SysWait(regs* r)
{
	return waitTask(r->ebx, (int*) r->edx, r->ecx);
}

uint64_t SysNotImpl(regs* r)
{
	KePanic("UNIMPLEMENTED SYSTEM CALL");
	return -1;
}

uint64_t SysRmdir(regs* r)
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

uint64_t SysUnlink(regs* r)
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

uint64_t SysGetArgc(regs* r)
{
	return currentTaskTCB->processRelatedTo->argc;
}

uint64_t SysGetArgv(regs* r)
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

uint64_t SysRealpath(regs* r)
{
	if (r->ecx == 0 || r->edx == 0) {
		return 1;
	}

	char* path = (char*) r->ecx;
	Fs::standardiseFiles((char*) r->edx, path, currentTaskTCB->processRelatedTo->cwd);
	return 0;
}

uint64_t SysTTYName(regs* r)
{
	return 1;

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
	strcpy((char*) r->edx, "<NO NAME>");
	return 0;
}

uint64_t SysIsATTY(regs* r)
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

uint64_t SysUSleep(regs* r)
{
	//ensure they both go to 64 bit
	uint64_t low = r->ebx;
	uint64_t high = r->ecx;

	uint64_t micro = low | high << 32;

	milliTenthSleep(micro / 100);
	return 0;
}

uint64_t SysSpawn(regs* r)
{
	if (!r->edx) return 0;

	Process* p = new Process((const char*) r->edx, r->ebx ? nullptr : currentTaskTCB->processRelatedTo, (char**) r->ecx);
	if (p->failedToLoadProgram) {
		return 0;
	}

	p->createUserThread();
	return p->pid;
}

uint64_t SysGetEnv(regs* r)
{
	char* addr = (char*) r->edx;
	int num = r->ebx;
	int count = Krnl::getProcessTotalEnvCount(currentTaskTCB->processRelatedTo);

	if (num >= count) {
		if (addr) {
			*addr = 0;
		}
		return 0;
	}

	EnvVar ev = Krnl::getProcessEnvPair(currentTaskTCB->processRelatedTo, num);
	if (r->ecx == 0) {
		return strlen(ev.key) + strlen(ev.value) + 1;
	}

	*addr = 0;
	strcpy(addr, ev.key);
	strcat(addr, "=");
	strcat(addr, ev.value);

	return 0;
}

uint64_t SysFormatDisk(regs* r)
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

uint64_t SysSetDiskVolumeLabel(regs* r)
{
	if (r->ebx > 25 || !disks[r->ebx] || !r->edx || !disks[r->ebx]->fs) return -2;
	return (int) disks[r->ebx]->fs->setlabel(disks[r->ebx], r->ebx, (char*) r->edx);
}

uint64_t SysGetDiskVolumeLabel(regs* r)
{
	if (r->ebx > 25 || !disks[r->ebx] || !r->edx || !r->ecx || !disks[r->ebx]->fs) return -2;
	return (int) disks[r->ebx]->fs->getlabel(disks[r->ebx], r->ebx, (char*) r->edx, (uint32_t*) r->ecx);
}

uint64_t SysSetFatAttrib(regs* r)
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

uint64_t SysPanic(regs* r)
{
	KePanic((char*) r->edx);
	return 1;
}

uint64_t SysShutdown(regs* r)
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

uint64_t SysPipe(regs* r)
{
	int* readEnd = (int*) r->ebx;
	int* writeEnd = (int*) r->ecx;

	Pipe* p = new Pipe();
	*readEnd = p->getFileDescriptor();
	*writeEnd = p->getFileDescriptor();

	return 0;
}

uint64_t SysGetUnixTime(regs* r)
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

uint64_t(*systemCallHandlers[])(regs* r) = {
	SysYield,
	SysExit,
	SysSbrk,
	SysWrite,
	SysRead,
	SysGetPID,
	SysGetCwd,
	SysSetCwd,
	SysOpen,
	SysClose,
	SysOpenDir,
	SysReadDir,
	SysSeekDir,
	SysTellDir,
	SysMakeDir,
	SysCloseDir,
	SysSeek,
	SysTell,
	SysSize,
	SysVerify,
	SysWait,
	SysNotImpl,
	SysNotImpl,
	SysRmdir,
	SysUnlink,
	SysGetArgc,
	SysGetArgv,
	SysRealpath,
	SysTTYName,
	SysIsATTY,
	SysUSleep,
	SysSizeFromFilename,
	SysSpawn,
	SysGetEnv,
	SysNotImpl,
	SysFormatDisk,
	SysSetDiskVolumeLabel,
	SysGetDiskVolumeLabel,
	SysSetFatAttrib,
	SysPanic,
	SysShutdown,
	SysPipe,
	SysGetUnixTime,
	SysLoadDLL,
	SysSetTime,
	SysTimezone,
	SysEject,
	SysWsbe,
	SysGetRAMData,
	SysGetVGAPtr,
};

uint64_t KeSystemCall(regs* r, void* context)
{
	kprintf("SYSTEM CALL %d\n", r->eax);
	if (r->eax < sizeof(systemCallHandlers) / sizeof(systemCallHandlers[0]) && systemCallHandlers[r->eax]) {
		r->eax = systemCallHandlers[r->eax](r);

		if (currentTaskTCB->processRelatedTo->gotCtrlC) {
			terminateTask(-1);
		}

	} else {
		kprintf("Invalid syscall %d\n", r->eax);
	}

	return 0xDEADBEEF;
}