#ifndef _DIRENT_INTERNAL_H
#define _DIRENT_INTERNAL_H

#include <stdint.h>
#include <sys/types.h>

#ifndef __machine_ino_t_defined
#if (defined(__i386__) && (defined(GO32) || defined(__MSDOS__))) || \
    defined(__sparc__) || defined(__SPU__)
typedef unsigned long __ino_t;
#else
typedef unsigned short __ino_t;
#endif
#endif

#define DT_UNKNOWN  0
#define DT_REG      1
#define DT_DIR      2

struct dirent {
    __ino_t d_ino;
    uint64_t d_namlen;  //name, without the \0 (strlen)
    int d_type;         //the type
    char d_name[256];

	//you must add things at the bottom of this struct, as application code and kernel code share it
};

#ifndef __KERNEL_DIRENT_INCLUDE
typedef struct {
    uint64_t _object_ID;
    
} DIR;


DIR*           opendir(const char*);
struct dirent* readdir(DIR *);
int            readdir_r(DIR*, struct dirent*, struct dirent **);
int            closedir(DIR* );

void           rewinddir(DIR*);
void           seekdir(DIR*, long int);
long int       telldir(DIR *);
#endif

#endif //_DIRENT_INTERNAL_H

