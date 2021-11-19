/* libc/sys/linux/sys/dirent.h - Directory entry as returned by readdir */

/* Written 2000 by Werner Almesberger */

// COPIED STRAIGHT FROM THE linux folder

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

/* Copyright (C) 1996, 1997 Free Software Foundation, Inc.
 This file is part of the GNU C Library.
 
 The GNU C Library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 The GNU C Library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, write to the Free
 Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307 USA.  */

#ifndef _SYS_DIRENT_H
# error "Never use <bits/dirent.h> directly; include <dirent.h> instead."
#endif

struct dirent
{
#ifndef __USE_FILE_OFFSET64
    __ino_t d_ino;
    __off_t d_off;
#else
    __ino64_t d_ino;
    __off64_t d_off;
#endif
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];        /* We must not include limits.h! */
};

#ifdef __USE_LARGEFILE64
struct dirent64
{
    __ino64_t d_ino;
    __off64_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];        /* We must not include limits.h! */
};
#endif

#define d_fileno    d_ino    /* Backwards compatibility.  */

#undef  _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_OFF
#define _DIRENT_HAVE_D_TYPE

#define _LIBC 1
#define  NOT_IN_libc 1
#include <sys/lock.h>
#undef _LIBC

#define HAVE_NO_D_NAMLEN    /* no struct dirent->d_namlen */
#define HAVE_DD_LOCK          /* have locking mechanism */

#define MAXNAMLEN 255        /* sizeof(struct dirent.d_name)-1 */


typedef struct {
    int dd_fd;        /* directory file */
    int dd_loc;        /* position in buffer */
    int dd_seek;
    char *dd_buf;    /* buffer */
    int dd_len;        /* buffer length */
    int dd_size;    /* amount of data in buffer */
    _LOCK_RECURSIVE_T dd_lock;
} DIR;


#define __dirfd(dir) (dir)->dd_fd

/* --- redundant --- */

DIR *opendir(const char *);
struct dirent *readdir(DIR *);
int readdir_r(DIR *__restrict, struct dirent *__restrict,
              struct dirent **__restrict);
void rewinddir(DIR *);
int closedir(DIR *);

/* internal prototype */
void _seekdir(DIR *dir, long offset);
DIR *_opendir(const char *);

#ifndef _POSIX_SOURCE
long telldir (DIR *);
void seekdir (DIR *, off_t loc);

int scandir (const char *__dir,
             struct dirent ***__namelist,
             int (*select) (const struct dirent *),
             int (*compar) (const struct dirent **, const struct dirent **));

int alphasort (const struct dirent **__a, const struct dirent **__b);
#endif /* _POSIX_SOURCE */

#endif
