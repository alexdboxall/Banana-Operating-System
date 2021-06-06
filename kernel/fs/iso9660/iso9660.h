#pragma once

/* modified for libxenon */

/* KallistiOS 1.2.0

   fs_iso9660.c
   Copyright (C)2000,2001,2003 Dan Potter
   Copyright (C)2001 Andrew Kieschnick
   Copyright (C)2002 Bero

*/

/*

This module implements an ISO9660 file system for reading from a CDR or CD
in the DC's GD-Rom drive.

Rock Ridge support has now been implemented, thanks to Andrew Kieschnick
who donated the code. Thanks to Bero for the Joliet support here.

This FS is considerably simplified from what you'd find in a bigger kernel
like Linux or BSD, since we have the pleasure of working with only a single
device capable of ISO9660 at once =). So there are a number of things in here
that are global variables that might otherwise not be.

Some thanks are in order here to Marcus Comstedt for providing an ISO9660
implementation that was easy enough to understand without downloading the
full spec =). Thanks also in order to the creators of the BSD and Linux
ISO9660 systems, as these were used as references as well.

*/

#include <stddef.h>
#include <stdint.h>

struct direntX
{
	uint64_t d_reclen;
	char d_name[120];
};

int iso_open(const char* fn);
void iso_close(int fd);
int64_t iso_read(int fd, void* buf, size_t bytes);
int64_t iso_seek(int fd, int64_t offset, int whence);
size_t iso_total(int fd);
int64_t iso_tell(int fd);
void fn_postprocess(char* fnin);
struct direntX* iso_readdir(int fd);
int iso_reset();
int fs_iso9660_init(char drive);
int init_percd(char drive);