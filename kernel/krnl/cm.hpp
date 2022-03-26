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

/// <summary>
/// An registry hive object obtained by opening a registry file.
/// Should be created with CmOpen, and closed with CmClose
/// </summary>
typedef struct Reghive_Tag {
    File* f;                    // the registry file. this remains open until CmClose is called
    bool valid;                 // whether or not this objects is valid
    
    struct Header {             // the header of the file
        char sig[8];            // signature, must be "REGISTRY"
        uint32_t numExtents;    // the total number of extents in the hive currently
        uint8_t reserved[31];   // unused
    } header;                   
        
} Reghive;

typedef struct Extent_Tag {
    uint32_t type : 8;          // the type of extent
    uint32_t next : 24;         // a reference to the next extent in this folder
        
    union {
        struct {
            uint8_t data[39];
        } x;                    // string data
        
        struct {
            uint8_t name[18];
            uint8_t extents[21];
        } s;                    // string header
    
        struct {
            uint8_t name[18];
            uint64_t data;
            
        } i;                    // integers
        
        struct {
            uint8_t name[18];
            uint32_t start : 24;    // the extent of the first sub-extent in the directory
            uint32_t : 8;
        } d;                    // directory
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
int CmCreateDirectory(Reghive* reg, int parent, const char* name);

#pragma pack(pop)
