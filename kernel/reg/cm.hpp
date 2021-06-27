#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "fs/vfs.hpp"

#pragma pack(push,1)

#define STATUS_SUCCESS          0
#define STATUS_LONG_NAME        1
#define STATUS_NOT_ENCODABLE    2
#define STATUS_UNKNOWN          3

#define EXTENT_LENGTH           43

#define EXTENT_BLANK            0x00
#define EXTENT_STRING_DATA      0x13
#define EXTENT_DIRECTORY        0x4E

#define EXTENT_INTEGER8         0x6A
#define EXTENT_INTEGER16        0x6B
#define EXTENT_INTEGER32        0x6C
#define EXTENT_INTEGER64        0x6D
#define EXTENT_SIGNED8          0x6E
#define EXTENT_SIGNED16         0x6F
#define EXTENT_SIGNED32         0x70
#define EXTENT_SIGNED64         0x71

#define EXTENT_STRING           0xC1


typedef struct Reghive_Tag {
    File* f;
    bool valid;
    
    struct Header {
        char sig[8];
        uint32_t numExtents;
        uint8_t reserved[31];
    } header;
        
} Reghive;

typedef struct Extent_Tag {
    uint32_t type : 8;
    uint32_t next : 24;
        
    union {
        struct {
            uint8_t data[39];
        } x;
        
        struct {
            uint8_t name[18];
            uint8_t extents[21];
        } s;
    
        struct {
            uint8_t name[18];
            uint64_t data;
            
        } i;
        
        struct {
            uint8_t name[18];
            uint32_t start : 24;
            uint32_t : 8;
        } d;
    };
    
} Extent;

Reghive* CmOpen(const char* filename);
void CmClose(Reghive* reg);
int CmConvertToInternalFilename(const char* __path, uint8_t* out);
int CmCreateExtent(Reghive* reg, int parent, int type, uint8_t* data);
void CmUpdateHeader(Reghive* reg);
int CmExpand(Reghive* reg, int extents);
int CmFindUnusedExtent(Reghive* reg);
void CmReadExtent(Reghive* reg, int extnum, uint8_t* data);
void CmWriteExtent(Reghive* reg, int extnum, uint8_t* data);
int CmCreateString(Reghive* reg, int parent, const char* name);
void CmSetString(Reghive* reg, int extnum, const char* data);
void CmFreeExtent(Reghive* reg, int num);
int CmFindInDirectory(Reghive* reg, int direntry, const char* name);
int CmEnterDirectory(Reghive* reg, int num);
void CmGetString(Reghive* reg, int extnum, char* out);
int CmFindObjectFromPath(Reghive* reg, const char* __name);
int CmCreateInteger(Reghive* reg, int parent, const char* name, uint64_t value, int type);
int CmGetNext(Reghive* reg, int extnum);
int CmGetNameAndTypeFromExtent(Reghive* reg, int extnum, char* name);
int CmConvertFromInternalFilename(const uint8_t* in, char* out);
void CmGetInteger(Reghive* reg, int extnum, uint64_t* i);
void CmSetInteger(Reghive* reg, int extnum, uint64_t i);
char* CmSplitFinalSlashInPlace(char* str);
int CmCreateDirectory(Reghive* reg, int parent, const char* name);

#pragma pack(pop)
