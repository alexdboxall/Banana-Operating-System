#include <reg/cm.hpp>

#include "core/common.hpp"
#include "core/physmgr.hpp"
#include "hal/vcache.hpp"
#include "hal/bus.hpp"
#include "hal/diskphys.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

extern "C" {
#include <libk/string.h>
#include <libk/ctype.h>
}


Reghive* CmOpen(const char* filename)
{
    int br;
    bool dir;
    uint64_t size;

    Reghive* reg = (Reghive*) malloc(sizeof(Reghive));

    reg->f = new File(filename, kernelProcess);
    reg->f->stat(&siz, &dir);
    reg->f->open(FileOpenMode::Read);

    uint8_t* data = malloc(size);
    reg->f->read(size, data, &br);
    reg->f->close();

    reg->f->open((FileOpenMode) (((int) FileOpenMode::Read) | ((int) FileOpenMode::Write) | ((int) FileOpenMode::CreateAlways)));
    reg->f->write(size, data, &br);
    free(data);

    if (!reg->f) {
        KePanic("BAD REGISTRY (A)");
    }

    reg->f->seek(0);
    reg->f->read(sizeof(reg->header), &reg->header, &br);
    reg->f->seek(0);

    if (memcmp(reg->header.sig, "REGISTRY", 8)) {
        KePanic("BAD REGISTRY (B)");
    }

    reg->valid = true;

    return reg;
}

void CmClose(Reghive* reg)
{
    if (!reg->valid) {
        return;
    }

    reg->f->close();
}

int CmCreateExtent(Reghive* reg, int parent, int type, uint8_t* data)
{
    int child = CmFindUnusedExtent(reg);

    Extent parentData;
    memset(&parentData, 0, EXTENT_LENGTH);
    if (parent) CmReadExtent(reg, parent, (uint8_t*) &parentData);

    Extent childData;
    memcpy(&childData, data, EXTENT_LENGTH);

    if (parent) {
        if (parentData.next) {
            childData.next = parentData.next;
            parentData.next = child;
        } else {
            childData.next = 0;
            parentData.next = child;
        }
    } else {
        childData.next = 0;
    }

    CmWriteExtent(reg, child, (uint8_t*) &childData);

    if (parent) {
        CmWriteExtent(reg, parent, (uint8_t*) &parentData);
    }

    return child;
}

int CmCreateString(Reghive* reg, int parent, const char* name)
{
    Extent ext;
    memset(&ext, 0, sizeof(Extent));

    CmConvertToInternalFilename(name, ext.s.name);
    ext.type = EXTENT_STRING;

    memset(ext.s.extents, 0, 21);

    return CmCreateExtent(reg, parent, 0, (uint8_t*) &ext);
}

void CmFreeExtent(Reghive* reg, int num)
{
    uint8_t data[EXTENT_LENGTH];
    memset(data, 0, EXTENT_LENGTH);
    CmWriteExtent(reg, num, data);
}

void CmGetString(Reghive* reg, int extnum, char* out)
{
    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);

    for (int i = 0; i < 7; ++i) {

        int num = ext.s.extents[i * 3 + 2];
        num <<= 8;
        num |= ext.s.extents[i * 3 + 1];
        num <<= 8;
        num |= ext.s.extents[i * 3 + 0];

        if (num != 0) {
            Extent data;
            CmReadExtent(reg, num, (uint8_t*) &data);

            memcpy(out + i * 39, data.x.data, 39);
        }
    }
}

void CmSetString(Reghive* reg, int extnum, const char* data)
{
    int components = (int) (strlen(data) + 38) / 39;
    if (components > 7) {
        KePanic("CmSetString TOO LONG");
    }

    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);

    for (int i = 0; i < 7; ++i) {

        int num = ext.s.extents[i * 3 + 2];
        num <<= 8;
        num |= ext.s.extents[i * 3 + 1];
        num <<= 8;
        num |= ext.s.extents[i * 3 + 0];

        if (i < components) {
            if (num == 0) {
                Extent blank;
                blank.type = EXTENT_STRING_DATA;
                num = CmCreateExtent(reg, 0, 0, (uint8_t*) &blank);

                ext.s.extents[i * 3] = num & 0xFF;
                ext.s.extents[i * 3 + 1] = (num >> 8) & 0xFF;
                ext.s.extents[i * 3 + 2] = (num >> 16) & 0xFF;
            }

            Extent compo;
            CmReadExtent(reg, num, (uint8_t*) &compo);
            memset(compo.x.data, 0, 39);
            strncpy((char*) compo.x.data, data + i * 39, 39);           //strncpy is correct here
            CmWriteExtent(reg, num, (uint8_t*) &compo);

        } else {
            if (num != 0) {
                CmFreeExtent(reg, num);

                ext.s.extents[i * 3] = 0;
                ext.s.extents[i * 3 + 1] = 0;
                ext.s.extents[i * 3 + 2] = 0;
            }
        }
    }

    CmWriteExtent(reg, extnum, (uint8_t*) &ext);
}

int CmEnterDirectory(Reghive* reg, int num)
{
    Extent ext;
    CmReadExtent(reg, num, (uint8_t*) &ext);
    if (ext.type == EXTENT_DIRECTORY) {
        return ext.d.start;
    }
    return -1;
}

int CmFindInDirectory(Reghive* reg, int direntry, const char* name)
{
    Extent ext;

    uint8_t wantName[18];
    memset(wantName, 0xFF, 18);
    CmConvertToInternalFilename(name, wantName);

    int num = direntry;
    while (true) {
        if (!num) {
            return -1;
        }
        CmReadExtent(reg, num, (uint8_t*) &ext);
        if (ext.type == EXTENT_STRING_DATA && ext.type == EXTENT_BLANK) {
            KePanic("CmFindInDirectory ASSERTION FAILED");
        }
        if (!memcmp(wantName, ext.s.name, 18)) {
            return num;
        }
        num = ext.next;
    }
}

int CmCreateInteger(Reghive* reg, int parent, const char* name, uint64_t value, int type)
{
    Extent ext;
    memset(&ext, 0, sizeof(Extent));

    CmConvertToInternalFilename(name, ext.i.name);
    ext.type = type;
    ext.i.data = value;

    return CmCreateExtent(reg, parent, 0, (uint8_t*) &ext);
}

int CmGetNext(Reghive* reg, int extnum)
{
    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);
    return ext.next;
}

int CmCreateDirectory(Reghive* reg, int parent, const char* name)
{
    Extent ext;
    memset(&ext, 0, sizeof(Extent));

    CmConvertToInternalFilename(name, ext.d.name);
    ext.type = EXTENT_DIRECTORY;
    ext.d.start = 0;

    int a = CmCreateExtent(reg, parent, 0, (uint8_t*) &ext);

    CmReadExtent(reg, a, (uint8_t*) &ext);
    ext.d.start = CmCreateInteger(reg, a, "DUMMY", 0, EXTENT_INTEGER32);
    CmWriteExtent(reg, a, (uint8_t*) &ext);

    return ext.d.start;
}

void CmReadExtent(Reghive* reg, int extnum, uint8_t* data)
{
    if (!reg->valid) {
        return;
    }

    int br;
    reg->f->seek(extnum * EXTENT_LENGTH);
    reg->f->read(EXTENT_LENGTH, data, &br);

    if (extnum) {
        uint32_t* d = (uint32_t*) data;

        for (int i = 0; i < 1; ++i) {
            uint64_t val = (uint64_t) *d;

            if (val) {
                val = val * 387420489ULL % 4000000000ULL;
                val -= extnum * (19 + i);
            }

            *d++ = (uint32_t) val;
        }
    }
}

void CmWriteExtent(Reghive* reg, int extnum, uint8_t* data)
{
    if (!reg->valid) {
        return;
    }

    if (extnum) {
        uint32_t* d = (uint32_t*) data;

        for (int i = 0; i < 1; ++i) {
            uint64_t val = (uint64_t) *d;

            if (val) {
                val += extnum * (19 + i);
                val = val * 3513180409ULL % 4000000000ULL;
            }

            *d++ = (uint32_t) val;
        }
    }

    int br;
    reg->f->seek(extnum * EXTENT_LENGTH);
    reg->f->write(EXTENT_LENGTH, data, &br);
}

void CmUpdateHeader(Reghive* reg)
{
    if (!reg->valid) {
        return;
    }

    CmWriteExtent(reg, 0, (uint8_t*) &reg->header);
}

int CmExpand(Reghive* reg, int extents)
{
    if (!reg->valid) {
        return -1;
    }

    reg->f->seek(reg->header.numExtents * EXTENT_LENGTH);

    uint8_t data[EXTENT_LENGTH];
    memset(data, 0, EXTENT_LENGTH);
    for (int i = 0; i < extents; ++i) {
        int br;
        reg->f->write(EXTENT_LENGTH, data, &br);
    }

    int retv = reg->header.numExtents;
    reg->header.numExtents += extents;

    CmUpdateHeader(reg);
    return retv;
}

int CmFindUnusedExtent(Reghive* reg)
{
    if (!reg->valid) {
        return -1;
    }

    reg->f->seek(0);

    int extNum = 0;
    while (extNum < reg->header.numExtents) {
        uint8_t type;
        int br;
        reg->f->read(1, &type, &br);
        if (type == 0) {
            return extNum;
        }

        extNum++;
        reg->f->seek(EXTENT_LENGTH * extNum);
    }

    return CmExpand(reg, 64);
}

char components[64][4] = {
    "TH", "HE", "IN", "ER", "AN", "RE", "ND", "AT", "ON", "NT", "HA", "ES",
    "ST", "EN", "ED", "TO", "IT", "OU", "EA", "HI", "IS", "OR", "TI", "AS",
    "TE", "ET", "NG", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
    "6", "7", "8", "9", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
    "0", "1", "2", "3", "4", "5", "V", "W", "X", "Y", "Z", 0,
};

int getMatch(char* digraph, char* mono, bool tryDigraph, bool* matchedDigraph)
{
    if (tryDigraph) {
        *matchedDigraph = true;
        for (int i = 0; i < 63; ++i) {
            if (!strcmp(digraph, components[i])) return i;
        }
    }
    *matchedDigraph = false;
    for (int i = 0; i < 63; ++i) {
        if (!strcmp(mono, components[i])) return i;
    }

    return -1;
}

bool addShiftCm(uint32_t* reg, int* count, uint8_t val, int bits)
{
    if (*count + bits < 32) {
        *reg |= (((uint32_t) val) << *count);
        *count += bits;
        return true;

    } else {
        return false;
    }
}

uint8_t getShiftCm(uint32_t* reg, int* count, int bits, bool* success)
{
    if (*count >= bits) {
        uint8_t ret = (*reg) & ((1 << bits) - 1);
        *reg >>= bits;
        *count -= bits;
        *success = true;
        return ret;

    } else {
        *success = false;
        return 0;
    }
}

void CmGetInteger(Reghive* reg, int extnum, uint64_t* i)
{
    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);
    *i = ext.i.data;
}

void CmSetInteger(Reghive* reg, int extnum, uint64_t i)
{
    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);
    ext.i.data = i;
    CmWriteExtent(reg, extnum, (uint8_t*) &ext);
}

int CmGetNameAndTypeFromExtent(Reghive* reg, int extnum, char* name)
{
    Extent ext;
    CmReadExtent(reg, extnum, (uint8_t*) &ext);
    CmConvertFromInternalFilename(ext.s.name, name);
    return ext.type;
}

int CmConvertFromInternalFilename(const uint8_t* in, char* out)
{
    uint8_t decoded[24];

    uint32_t sreg = 0;
    int sregcnt = 0;
    int ob = 0;

    memset(out, 0xEE, 18);

    for (int i = 0; i < 18; ++i) {
        addShiftCm(&sreg, &sregcnt, in[i], 8);

    retry:;
        bool success;
        uint8_t val = getShiftCm(&sreg, &sregcnt, 6, &success);

        if (success) {
            decoded[ob++] = val;
            goto retry;
        }
    }

    out[0] = 0;
    for (int i = 0; i < 24; ++i) {
        strcat(out, components[decoded[i]]);
    }

    return STATUS_SUCCESS;
}

int CmConvertToInternalFilename(const char* __path, uint8_t* out)
{
    char path[48];
    memset(path, 0, 48);
    for (int i = 0; i < strlen(__path); ++i) {
        path[i] = toupper(__path[i]);
    }

    uint8_t parts[24];
    int next = 0;

    memset(parts, 63, 24);

    for (int i = 0; path[i]; ++i) {
        char digraph[4];
        digraph[0] = path[i];
        digraph[1] = path[i + 1];
        digraph[2] = 0;

        char mono[3];
        mono[0] = path[i];
        mono[1] = 0;

        bool matchedDigraph;

        int thing;
        if (strlen(mono)) {
            thing = getMatch(digraph, mono, true, &matchedDigraph);
        } else {
            thing = getMatch(NULL, digraph, false, &matchedDigraph);
        }
        if (thing == -1) {
            KePanic("STATUS_NOT_ENCODABLE");
            return STATUS_NOT_ENCODABLE;
        }

        if (next == 24) {
            KePanic("STATUS_LONG_NAME");
            return STATUS_LONG_NAME;
        }

        parts[next++] = thing;
        if (matchedDigraph) {
            ++i;
        }

        if (!strlen(mono)) break;
    }

    uint32_t sreg = 0;
    int sregcnt = 0;
    int ob = 0;

    memset(out, 0xEE, 18);

    for (int i = 0; i < 100; ++i) {
        bool canAdd = i >= 24 ? false : addShiftCm(&sreg, &sregcnt, parts[i], 6);
        if (!canAdd) {
            bool success;
            uint8_t val = getShiftCm(&sreg, &sregcnt, 8, &success);

            if (success) {
                out[ob++] = val;
            } else {
                break;
            }

            --i;
        }
    }

    return STATUS_SUCCESS;
}

int CmFindObjectFromPath(Reghive* reg, const char* __name)
{
    char name[256];
    strcpy(name, __name);

    int loc = 1;
    char* p = strtok(name, "/");
    loc = CmFindInDirectory(reg, loc, p);
    p = strtok(NULL, "/");
    while (p) {
        loc = CmEnterDirectory(reg, loc);
        if (loc == -1) return -1;
        loc = CmFindInDirectory(reg, loc, p);
        p = strtok(NULL, "/");
    }

    return loc;
}

void tree(Reghive* reg, int a, int n)
{
    while (a > 0) {
        char nm[50];
        memset(nm, 0, 50);
        int type = CmGetNameAndTypeFromExtent(reg, a, nm);

        for (int i = 0; i < n; ++i) kprintf(" ");
        kprintf("%d = /%s\n", a, nm);

        if (type == EXTENT_DIRECTORY) {
            tree(reg, CmEnterDirectory(reg, a), n + 4);
        }
        a = CmGetNext(reg, a);
    }
}

char* CmSplitFinalSlashInPlace(char* str)
{
    for (int i = strlen(str) - 1; i; --i) {
        if (str[i] == '/') {
            str[i] = 0;
            return str + i + 1;
        }
    }
    return NULL;
}
