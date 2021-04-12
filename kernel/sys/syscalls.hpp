#ifndef _SYSCALLS_HPP_
#define _SYSCALLS_HPP_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
struct regs;
namespace Sys
{
	void loadSyscalls();
	uint64_t systemCall(regs* r, void* context);

}
#endif

#define _APPSETTINGS_VALIDATION_V1			'N'

#define _APPSETTINGS_MODE_UNKNOWN			0
#define _APPSETTINGS_MODE_SET_NAME			1
#define _APPSETTINGS_MODE_SET_DESCRIPTION	2
#define _APPSETTINGS_MODE_SET_KEYWORDS		3
#define _APPSETTINGS_MODE_SET_AUTHOR		4
#define _APPSETTINGS_MODE_SET_COPYRIGHT		5
#define _APPSETTINGS_MODE_SET_VERSION		6
#define _APPSETTINGS_MODE_SET_FLAGS			7
#define _APPSETTINGS_MODE_SET_TITLECOLOUR	8

typedef struct AppSettings_t
{
	union
	{
		char string[256];
		char keywords[16][16];
	};

	uint32_t mode				: 5;
	uint32_t valid				: 8;
	uint32_t noConsole			: 1;
	uint32_t unbufferedKeyboard : 1;

	uint32_t intData;

} AppSettings_t;

enum
#ifdef __cplusplus
class
#endif
SystemCallNumber
{
	Yield,
	Exit,
	Sbrk,
	Write,
	Read,
	GetPID,
	GetCwd,
	SetCwd,
	Open,
	Close,
	OpenDir,
	ReadDir,
	SeekDir,
	TellDir,
	MakeDir,
	CloseDir,
	Seek,
	Tell,
	Size,
	Verify,
	Wait,
	Fork,
	Execve,
	Rmdir,
	Unlink,
	GetArgc,
	GetArgv,
	Realpath,
	TTYName,
	IsATTY,
	USleep,
	SizeFromFilename,
	Spawn,
	GetEnv,
	AppSettings,
	FormatDisk,
	SetDiskVolumeLabel,
	GetDiskVolumeLabel,
	SetFATAttrib,
	Panic,
	Shutdown,
	Pipe,
	GetUnixTime,
	LoadDLL,
	SetTime,
	Timezone,
	Eject,
	WSBE,
	GetRAMData,
};


#endif