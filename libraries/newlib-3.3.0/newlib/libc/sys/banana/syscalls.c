#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>

#pragma GCC push_options
#pragma GCC optimize ("O0")

#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"

uint64_t SystemCall(size_t a, size_t b, size_t c, size_t d)
{
	volatile uint32_t resA;
	volatile uint32_t resD;

	asm volatile (
		"int $96"  :                //assembly
		"=d" (resD),                //output
		"=a" (resA) :                //output
		"a" (a),                 //input
		"b" (b),                     //input
		"c" (c),                     //input
		"d" (d) :                    //input
		"memory", "cc");            //clobbers

	uint64_t res = (uint64_t) resD;
	res <<= 32;
	res |= (uint64_t) resA;
	return res;
}

void _exit(int code)
{
	SystemCall(Exit, code, 0, 0);
}

int close(int file)
{
	if (file == 0 || file == 1 || file == 2) {
		//the entire thing comes crashing to a halt if this goes through
		return 0;
	}

	return SystemCall(Close, file, 0, 0);
}

#define MAX_ENVIRONMENT_VARIABLES 128
char** environ;
char* __env[MAX_ENVIRONMENT_VARIABLES] = { 0 };

void _environ_setup()
{
	environ = __env;
	for (int i = 0; i < MAX_ENVIRONMENT_VARIABLES; ++i) {
		int size = SystemCall(GetEnv, i, 0, 0);
		if (!size) break;
		__env[i] = malloc(size);
		SystemCall(GetEnv, i, 1, (size_t) __env[i]);
		if (!__env[i]) break;
	}
}

int execve(char* name, char** argv, char** env)
{
	SystemCall(Execve, (size_t) name, (size_t) argv, (size_t) env);
	errno = ENOMEM;
	return -1;
}

int	chmod(const char* __path, mode_t __mode)
{
	errno = ENOMEM;
	return -1;
}

int fchmod(int __fd, mode_t __mode)
{
	errno = ENOMEM;
	return -1;
}

int fork()
{
	return SystemCall(Fork, 0, 0, 0);
}

int fstat(int file, struct stat* st)
{
	if (file == 0 || file == 1 || file == 2) {
		st->st_mode = S_IFCHR;
		return 0;
	}

	uint64_t fileSize = 0;
	int res = SystemCall(Size, file, &fileSize, 0);

	st->st_size = fileSize;
	st->st_mode = S_IFREG;

	return res;
}

int getpid()
{
	return SystemCall(GetPID, 0, 0, 0);
}

int isatty(int file)
{
	int it = SystemCall(IsATTY, file, 0, 0);

	if (it == 1) {
		return 1;
	} else if (it == 0) {
		errno = ENOTTY;
		return 0;
	}

	errno = EBADF;
	return 0;

	/*if (file <= 2) {
		return 1;
	} else {
		errno = ENOTTY;
	}
	return 0;*/
}


int link(char* old, char* new)
{
	return -1;
}

off_t lseek(int file, off_t ptr, int whence)
{
	uint64_t realPos = 0;

	if (whence == SEEK_SET) {
		realPos = ptr;

	} else if (whence == SEEK_CUR) {
		uint64_t filePos = 0;
		SystemCall(Tell, file, &filePos, 0);
		realPos = filePos + ptr;

	} else if (whence == SEEK_END) {
		uint64_t fileSize = 0;
		SystemCall(Size, file, &fileSize, 0);
		realPos = fileSize + ptr;

	} else {
		errno = EINVAL;
		return -1;
	}

	int res = SystemCall(Seek, file, realPos, 0);
	if (res) {
		return -1;
	}

	return realPos;
}

int open(const char* name, int flags, ...)
{
	//the ... may contain a 'mode', which is an integer
	//which contains unix permissions.
	//we will ignore this, as we don't have permissions

	bool _read = false;
	bool _write = false;
	bool append = false;
	bool truncate = false;      //reset file to length zero on write
	bool createIfNotExist = false;

	if (flags == O_RDONLY) _read = true;
	if (flags == O_WRONLY) _write = true;
	if (flags == O_RDWR) {
		_read = true;
		_write = true;
	}

	if (flags & O_APPEND) append = true;
	if (flags & O_CREAT) createIfNotExist = true;
	if (flags & O_TRUNC) truncate = true;

	int syscallFlags = 0;
	if (_read) {
		syscallFlags |= 1;
	}
	if (_write) {
		syscallFlags |= 2;
	}
	if (append) {
		syscallFlags |= 2;
		syscallFlags |= 4;
	}
	if (truncate) {
		syscallFlags |= 16;
	}
	if (createIfNotExist) {
		syscallFlags |= 16;
	}

	int fileDesc = -1;
	if (flags & 0x200000 /*O_DIRECTORY*/) {
		uint64_t outFileDesc = 0;
		int res = SystemCall(OpenDir, &outFileDesc, 0, name);
		if (res == 0 && outFileDesc) {
			fileDesc = outFileDesc;
		}
	} else {
		uint64_t outFileDesc = 0;
		int res = SystemCall(Open, &outFileDesc, syscallFlags | (flags << 8), name);
		if (res == 0 && outFileDesc) {
			fileDesc = outFileDesc;
		}
	}

	return fileDesc;
}

int read(int file, char* ptr, int len)
{
	return SystemCall(Read, file, len, (size_t) ptr);
}

caddr_t sbrk(int incr)
{
	return SystemCall(Sbrk, incr, 0, 0);
}

int stat(const char* file, struct stat* st)
{
	if (file == 0 || file == 1 || file == 2) {
		st->st_mode = S_IFCHR;
		return 0;
	}

	uint64_t fileSize = 0;
	int a = 0;
	int res = SystemCall(SizeFromFilename, (size_t) file, &fileSize, (size_t) &a);

	st->st_size = fileSize;
	if (a == 0) {
		st->st_mode = S_IFREG;
	} else if (a == 1) {
		st->st_mode = S_IFDIR;
	} else if (a == 2) {
		st->st_mode = S_IFLNK;
	} else {
		st->st_mode = S_IFREG;
	}

	return res;
}

int lstat(const char* file, struct stat* st)
{
	if (file == 0 || file == 1 || file == 2) {
		st->st_mode = S_IFCHR;
		return 0;
	}

	uint64_t fileSize = 0;
	int a = 0;
	int res = SystemCall(SizeFromFilenameNoSymlink, (size_t) file, &fileSize, (size_t) &a);

	st->st_size = fileSize;
	if (a == 0) {
		st->st_mode = S_IFREG;
	} else if (a == 1) {
		st->st_mode = S_IFDIR;
	} else if (a == 2) {
		st->st_mode = S_IFLNK;
	} else {
		st->st_mode = S_IFREG;
	}
	

	return res;
}

clock_t times(struct tms* buf)
{
	return -1;
}

int unlink(char* name)
{
	return SystemCall(Unlink, 0, 0, (size_t) name);
}

int wait(int* status)
{
	return waitpid(-1, status, 0);
}

int write(int file, char* ptr, int len)
{
	return SystemCall(Write, file, len, (size_t) ptr);
}


int gettimeofday(struct timeval* __restrict p, void* __restrict z)
{
	if (p != NULL) { 
		p->tv_usec = 0;										//microseconds;
		p->tv_sec = SystemCall(GetUnixTime, 0, 0, 0);		//seconds since Unix Epoch
	}

	/*if (z != NULL) {
		//apparently this is obsolete, so it probably doesn't
		//matter if we don't actually set these correctly

		z->tz_minuteswest = 0;		//minutes west of Greenwich;
		z->tz_dsttime = 0;			//type of DST correction
	}*/

	return 0;
}

#include <dirent.h>

int kill(pid_t pid, int sig)
{
	return SystemCall(Kill, sig, pid, 0);
}

#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int) {
	int fail = SystemCall(RegisterSignal, sig, 0, (size_t) func);
	if (fail) {
		return SIG_ERR;
	}
	return func;
}

int _readdir(unsigned int fd, struct dirent* dirp,
			 unsigned int count)
{
	//fill the *dirp with the directory data for directory fd.
	//'count' has the number of bytes the 'dirent' is, but can probably be ignored
	//as they're always the same size

	uint64_t file64 = fd;
	return SystemCall(ReadDir, 0, fd, (size_t) dirp);		// 0 = success, 1 = EOF / ERROR
}


DIR* opendir(const char* dirname)
{
	int fp = open(dirname, O_RDONLY | 0x200000 /*O_DIRECTORY*/);
	if (fp == -1 || fp == 0) {
		return 0;
	}
	DIR* dir = malloc(sizeof(dir));
	dir->_object_ID = fp;
	return dir;
}

//this is allowed, free()ing the return value is not, so this is how we're going to do it
struct dirent readdirData;

struct dirent* readdir(DIR * dirp)
{
	memset(&readdirData, 0, sizeof(readdirData));
	struct dirent* ent = &readdirData;
	int retval = _readdir(dirp->_object_ID, ent, sizeof(struct dirent));     //copies an entry into 'ent'
	if (retval != 0) {
		return 0;		//EOF
	}
	return ent;
}

int readdir_r(DIR * dirp, struct dirent* entry, struct dirent** result)
{
	return -1;
}

int closedir(DIR * dirp)
{
	int fp = dirp->_object_ID;
	free(dirp);
	return SystemCall(CloseDir, fp, 0, 0);
}

void seekdir(DIR * dirp, long int loc)
{
	SystemCall(SeekDir, loc, 0, dirp->_object_ID);
}

void rewinddir(DIR * dirp)
{
	seekdir(dirp, 0);
}

long int telldir(DIR * dirp)
{
	return SystemCall(TellDir, 0, 0, dirp->_object_ID);
}

char* getcwd(char* buf, size_t size)
{
	SystemCall(GetCwd, (size_t) buf, size, 0);
	return buf;
}

int chdir(const char* buf)
{
	if (buf[0] == 0) {
		errno = ENOENT;
		return -1;
	}

	int res = SystemCall(SetCwd, (size_t) buf, 0, 0);
	if (res == 0) return 0;
	else if (res == 1) {
		errno = ENOENT;
	} else if (res == 2) {
		errno = ENOTDIR;
	} else if (res == 3) {
		errno = EACCES;
	} else if (res == 4) {
		errno = EACCES;
	} else if (res == 5) {
		errno = ENOTDIR;
	} else if (res == 6) {
		errno = EACCES;
	}

	return -1;
}

int mkdir(const char* path, mode_t mode)
{
	return SystemCall(MakeDir, 0, 0, (void*) path);
}

/*
uint64_t sysPipe(regs* r)
{
	int* readEnd = (int*) r->ebx;
	int* writeEnd = (int*) r->ecx;*/

int pipe (int pipefd[2])
{
	return SystemCall(Pipe, &pipefd[0], &pipefd[1], 0);
}

#include <sys/types.h>


pid_t waitpid(pid_t pid, int* stat_loc, int options)
{
	return SystemCall(Wait, pid, options, (size_t) stat_loc);
}

int rmdir(const char* path)
{
	return SystemCall(Rmdir, 0, 0, (size_t) path);
}

char* realpath(const char* __restrict file_name, char* __restrict resolved_name)
{
	if (resolved_name == NULL) {
		resolved_name = malloc(512);
	}

	int res = SystemCall(Realpath, 0, (size_t) file_name, (size_t) resolved_name);

	if (res) {
		errno = EIO;
		free(resolved_name);
		return 0;
	}

	return resolved_name;
}


char _static_data_is_allowed_for_ttyname[256];

char* ttyname(int fildes)
{
	int r = SystemCall(TTYName, fildes, 0, (size_t) _static_data_is_allowed_for_ttyname);
	if (r == 0) {
		return _static_data_is_allowed_for_ttyname;
	}

	if (r == 1) {
		errno = EBADF;
	} else {
		errno = ENOTTY;
	}

	return 0;
}

int usleep(useconds_t useconds)
{
	return SystemCall(USleep, useconds & 0xFFFFFFFF, useconds >> 32, 0);
}

unsigned sleep(unsigned seconds)
{
	return usleep(seconds * 1000 * 1000);
}

int ftruncate(int fildes, off_t length)
{
	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	int res = SystemCall(Truncate, length, 0, fildes);
	if (res) {
		errno = EROFS;
	}
	return res;
}

int truncate(const char* path, off_t length)
{
	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	int res = SystemCall(Truncate, length, 1, (size_t) path);
	if (res) {
		errno = EROFS;
	}
	return res;
}

int symlink(const char* oldname, const char* newname)
{
	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	int res = SystemCall(Symlink, 0, (size_t) oldname, (size_t) newname);
	if (res == 1) {
		errno = EROFS;
	} else if (res == 2) {
		errno = ELOOP;
	} else {
		errno = EROFS;
	}
	return res;
}

#pragma GCC pop_options