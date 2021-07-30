#include "core/computer.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hal/clock.hpp"
#include "hal/timer.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Truncates a file to a certain size.
/// </summary>
/// <param name="ebx">The number of bytes the file should be truncated to.</param>
/// <param name="ecx">Set to zero if a file descriptor is in ecx, or 1 if a file path is used.</param>
/// <param name="edx">The file descriptor or a pointer to a file path string.</param>
/// <returns>Returns zero on success, non-zero otherwise.</returns>
/// 
uint64_t SysTruncate(regs* r)
{
	uint64_t size = r->ebx;
	
	if (r->ecx) {
		char* path = (char*) r->edx;

		File* f = new File(path, currentTaskTCB->processRelatedTo);
		if (!f) return 3;

		FileStatus status = f->open(FileOpenMode::Write);
		if (status != FileStatus::Success) {
			delete f;
			return 4;
		}

		f->truncate(f, size);

		f->close();
		delete f;

	} else {
		int fildes = r->edx;

		if (fildes <= 2) {
			return 1;

		} else {
			UnixFile* file = KeGetFileFromDescriptor(r->ebx);

			if (file == nullptr) {
				return 2;
			}

			FileStatus status = file->truncate(file, size);

			return status;
		}
	}

	return 0;
}
