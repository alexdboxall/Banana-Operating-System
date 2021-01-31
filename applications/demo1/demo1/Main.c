//
//  main.c
//  Banana Filesystem
//
//  Created by Alex Boxall on 4/11/17.
//  Copyright © 2017 Alex Boxall. All rights reserved.
//

/*
 NOTE! NEVER DIVIDE OR MOD BY 4096/CLUSTER_SIZE TO GET CLUSTER/OFFSET,
       INSTEAD USE USABLE_DATA_PER_CLUSTER TO DIVIDE OR MOD, AS THAT IS HOW MANY BYTES OF
       DATA CAN FIT IN A CLUSTER
 */

 /*
  INSTEAD OF CHECKING FOR A '*' OR SOMETHING FOR A FREE CLUSTER,
  HAVE A BIT ARRAY AT THE START OF THE DISK THAT SAYS IF A CLUSTER
  IS FREE OR EMPTY

  1 bit = 4096 bytes
  1 byte = 32KB

  1MB disk = 32 bytes overhead
  1GB disk = 32 kilobytes overhead
  1TB disk = 32 megabytes overhead
  32TB disk = 1 gigabyte overhead

  1/32768 of disk is used as overhead
  */

  //
  //  main.h
  //  Banana Filesystem
  //
  //  Created by Alex Boxall on 4/11/17.
  //  Copyright © 2017 Alex Boxall. All rights reserved.
  //

#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#define SECTOR_SIZE 512
#define CLUSTER_SIZE 4096
#define SECTORS_PER_CLUSTER (CLUSTER_SIZE / SECTOR_SIZE)
#define HEADER_FILE_DATA_SIZE 3718
#define USABLE_DATA_PER_CLUSTER 4087
#define MAX_CLUSTER_CACHES 16
#define DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN 28

#define ROOT_LOCATION "C:/Banana"
#define DISK_IMAGE "C:/disk.bin"
#define DISK_SIZE 1024 * 1024 * 16

#define FREESPACE_TABLE_BASE 1
#define FREESPACE_TABLE_SIZE (DISK_SIZE / CLUSTER_SIZE / 8 / CLUSTER_SIZE + 1)
#define PAGEFILE_BASE (FREESPACE_TABLE_BASE + FREESPACE_TABLE_SIZE)
#define PAGEFILE_SIZE 256
#define ROOT_CLUSTER (PAGEFILE_BASE + PAGEFILE_SIZE)



#define FILEOK 0
#define FILEERR_NOFILE 0xFFFFFFFFFFFFFFF0           //we cannot clash with cluster numbers

extern FILE* diskImage;
extern bool encryption;
extern char password[256];
extern uint64_t c;

typedef struct DATETIME
{           // 12 bytes
    int16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t reserved;

    uint32_t microseconds;

} DATETIME;

typedef enum CREATION_SYSTEM
{
    UNKNOWN,
    BANANA,
    WINDOWS,
    MACOS,
    LINUX,
    OTHER,
    DOS,
    IOS,
    ANDROID,
    CHROME,
    BSD,
    GNU,
    OS2,
    SOLARIS,
    UNIX

} CREATION_SYSTEM;

typedef struct ATTRIBUTES
{     // 4 bytes
    uint32_t hidden : 1;    // hidden
    uint32_t system : 1;    // system
    uint32_t archive : 1;    // archived
    uint32_t encrypted : 1;    // each cluster is encrypted in a way like my project manager
    uint32_t smallfile : 1;    // fit the file into the file header
    uint32_t readonly : 1;    //
    uint32_t volumelabel : 1;    // use this file as a volume label
    uint32_t device : 1;    // use this file as a device

    uint32_t directory : 1;    // directory
    uint32_t unused3 : 1;    //
    uint32_t unused4 : 1;    //
    uint32_t anyuserexe : 1;    // this file is executable
    uint32_t temporary : 1;    // temporary file
    uint32_t custom : 3;    // system specific

    uint32_t mustBe1_1 : 1;    // must be 1
    uint32_t mustBe1_2 : 1;    // must be 1
    uint32_t mustBe0_1 : 1;    // must be 0
    uint32_t mustBe1_3 : 1;    // must be 1
    uint32_t mustBe0_2 : 1;    // must be 0
    uint32_t mustBe0_3 : 1;    // must be 0
    uint32_t custom2 : 2;    // system specific

    uint32_t creationsys : 6;    // creation system
    uint32_t reserved : 2;

} ATTRIBUTES;

typedef struct FILEINFO
{
    //0
    char used[2];           // '**'
    char filename[258];    // filename

    DATETIME creationDate;
    DATETIME modifyDate;
    DATETIME openDate;
    DATETIME deletionDate;
    DATETIME restoreDate;
    DATETIME otherDate;

    uint64_t userID;
    uint64_t hash;          // the one used to get to here
    uint64_t startingCluster;
    uint64_t fileLength;        // clusters

    uint32_t checksum;      // all values + this shall equal 0

    ATTRIBUTES attributes;

    uint16_t smallFileBytesUsed : 15;
    uint16_t dirContentHelpersComplete : 1;

    union
    {
        /*
         'dirContentHelpers' are small structures that are used only for directories, in the place
         where the start of files would be if it were a file. They CAN used for quick parsing of
         directories. They show basic things about SOME of the content in the folder (it may be
         complete, the 'dirContentHelpersComplete' flag should be checked. It shows the first
         DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN characters
         of each object in a folder, as well as some basic attributes. This is used to allow quick
         implementation of 'dir' or 'ls' commands. As the data is most likely imcomplete, it should
         not be used exclusively, instead read as much data as it as possible using the helpers,
         but if a filename is longer than DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN chars,
         or there are more entries than the helpers can hold
         look up the rest of the data the normal (but slower) way.
         */

        uint8_t fileContentsIfItIsASmallFile[HEADER_FILE_DATA_SIZE];
    };

} FILEINFO;

typedef struct DATACLUSTER
{
    char used;

    uint8_t fileData[USABLE_DATA_PER_CLUSTER];

    uint64_t nextCluster : 51;       //0 = end, 1+ = nextCluster
    uint64_t bytesOfClusterUsed : 13;        //only used in the last cluster of the chain

} DATACLUSTER;

typedef enum DISK_TYPES
{
    DISK_TYPE_UNKNOWN = 11,
    DISK_TYPE_ATA = 22,
    DISK_TYPE_SATA = 33,
    DISK_TYPE_HDD = 44,   //other hard drive
    DISK_TYPE_FLOPPY = 55,
    DISK_TYPE_CD_RM = 66,   //CD-R
    DISK_TYPE_CD_RP = 77,   //CD+R
    DISK_TYPE_CD_RWM = 88,   //CD-RW
    DISK_TYPE_CD_RWP = 99,   //CD+RW
    DISK_TYPE_DVD_RM = 111,  //DVD-R
    DISK_TYPE_DVD_RP = 222,  //DVD+R
    DISK_TYPE_DVD_RWM = 333,  //DVD-RW
    DISK_TYPE_DVD_RWP = 444,  //DVD+RW
    DISK_TYPE_CD_ROM = 555,  //CD-ROM
    DISK_TYPE_DISC = 666,  //OTHER DISK
    DISK_TYPE_FLASH = 777,  //USB FLASH
    DISK_TYPE_USB_O = 888,  //USB OTHER
    DISK_TYPE_SD = 999,  //SD CARD
    DISK_TYPE_VIRTUAL = 1111, //VIRTUAL DISK

} DISK_TYPES;

typedef struct DATATABLE
{
    uint64_t sectorsPerCluster : 4;
    uint64_t driveLetter : 8;
    uint64_t mustBe1s : 3;
    uint64_t rootClusterNumber : 44;
    uint64_t driveNumber : 5;

    uint64_t serialNumber;

    uint64_t manufactureYear : 13;
    uint64_t manufactureMonth : 4;
    uint64_t manufactureDay : 9;
    uint64_t unknownManufacture : 1;
    uint64_t formatYear : 13;
    uint64_t formatMonth : 4;
    uint64_t formatDay : 9;
    uint64_t mustBe1s2 : 11;

    uint64_t totalSectors : 62;
    uint64_t mustBe1s3 : 2;

    uint64_t diskType : 14;
    uint64_t consto : 50;

    uint64_t specialSignature;      //0xCAFEBABEDEADBEEF

    uint64_t formatHour : 5;
    uint64_t formatMinute : 6;
    uint64_t formatSecond : 6;

    uint64_t legacySectorsPTrack : 7;
    uint64_t legacyTrackPHead : 15;
    uint64_t legacyHeadCount : 25;

    uint64_t numberOfBadSectors : 35;
    uint64_t numberOfBadClusters : 29;

    uint64_t formatVersionMajor : 5;
    uint64_t formatVersionMinor : 11;
    uint64_t reserved2 : 48;

    uint8_t regionCode[4];
    uint8_t languageCode[4];

    uint64_t nextFolderID;          //!very important, this value allows each 'table' cluster to be
                                    //!matched to it's folder, so data doesn't get put in the wrong folder
                                    //! MUSTN'T EVER BE ZERO

    uint64_t firstQuickFindSector;
    uint64_t numberOfQuickFindSectors;

    uint64_t pageFileBase;
    uint64_t pageFileSize;

    uint64_t freespaceArrayBase;
    uint64_t freespaceArraySize;

    uint8_t reserved[186];

    char volumeLabel[128];
    char finishCode[64];

} DATATABLE;

typedef struct ROOTCLUSTER
{
    char jmp[3];
    char b;                     //B
    char oem[8];                //ANANAOS (null)

    char filesystem[12];        //BANANA FS v1

    uint16_t sectorSize;
    uint8_t bootcode[486];

    uint8_t extendedBootcode[1024 * 3];

    DATATABLE data;

} __attribute__((packed)) ROOTCLUSTER;

typedef struct clusterCache_t
{
    uint64_t clusterNumber;
    int64_t relevancy;
    uint8_t data[CLUSTER_SIZE];
    bool dirty;

} clusterCache_t;

extern bool cachesOn;
extern clusterCache_t cluster_caches[MAX_CLUSTER_CACHES];

#endif /* main_h */

uint64_t MurmurHash64A(const void* key, int len, unsigned int seed);

//
//  utils.h
//  Banana Filesystem
//
//  Created by Alex Boxall on 4/11/17.
//  Copyright © 2017 Alex Boxall. All rights reserved.
//

#ifndef utils_h
#define utils_h

//THESE SHOULD NEVER BE CALLED OUTSIDE OF THE READ/WRITE CLUSTER WRAPPERS
//SO THEY SHOULD NOT BE MADE PUBLIC. ALSO CAUSES SOME VERY, VERY UGLY ERRORS
//IF THIS IS USED INSTEAD OF THE CLUSTER VERSION DURING PROGRAM CODE
//void writeSector  (uint64_t sectorNumber,  uint8_t* data);
//uint8_t* readSector  (uint64_t sectorNumber);

bool checkForSpaceAtLocation(uint64_t clusterNumber);
void setSpaceAtLocation(uint64_t clusterNumber, bool value);

uint64_t getFileTableEntryByte(char* filename);
void addObjectNoAllocatedClusterWithByteLocation \
(uint64_t hash, bool dir, uint64_t startCluster, uint64_t datalocation);

void writeCluster(uint64_t clusterNumber, uint8_t* data);
uint8_t* readCluster(uint64_t clusterNumber);

uint64_t createHash(char* string);

uint64_t addObject(uint64_t hash, bool dir, uint64_t startCluster);
uint64_t getFileStartPoint(char* filename);
uint64_t findBlankCluster(void);
void clearFileEntry(char* filename);

uint64_t generateUniqueFolderID(void);
void turnOffCaches(void);
void turnOnCaches(void);

#endif /* utils_h */


bool cachesOn = true;
FILE* diskImage;
bool encryption = true;
char password[256] = "This is a password";
clusterCache_t cluster_caches[MAX_CLUSTER_CACHES];

uint64_t c = ROOT_CLUSTER;

void formatDisk(char* disk)
{
    for (int i = 0; i < MAX_CLUSTER_CACHES; ++i) {
        cluster_caches[i].clusterNumber = 0xFFFFFFFFFFFFFFFF;
    }

    turnOffCaches();

    ROOTCLUSTER root;
    memset(&root, 0, 1024 * 4);

    root.b = 'B';
    root.bootcode[484] = 0x55;
    root.bootcode[485] = 0xAA;
    memcpy(root.filesystem, "BANANA FS v1", 12);
    memcpy(root.oem, "ANANAOS\0", 8);
    root.sectorSize = SECTOR_SIZE;
    root.data.rootClusterNumber = ROOT_CLUSTER;
    root.data.sectorsPerCluster = CLUSTER_SIZE / SECTOR_SIZE;
    root.data.driveLetter = 'C';
    root.data.driveNumber = 0;
    root.data.serialNumber = 0xEFCDAB8967452301;
    root.data.mustBe1s = 7;

    root.data.freespaceArrayBase = FREESPACE_TABLE_BASE;
    root.data.freespaceArraySize = FREESPACE_TABLE_SIZE;
    root.data.pageFileBase = PAGEFILE_BASE;
    root.data.pageFileSize = PAGEFILE_SIZE;

    time_t now = time(NULL);
    struct tm* tm_struct = localtime(&now);

    root.data.manufactureYear = tm_struct->tm_year;
    root.data.manufactureMonth = tm_struct->tm_mon;
    root.data.manufactureDay = tm_struct->tm_yday;
    root.data.unknownManufacture = false;

    root.data.formatYear = tm_struct->tm_year;
    root.data.formatMonth = tm_struct->tm_mon;
    root.data.formatDay = tm_struct->tm_yday;
    root.data.formatHour = tm_struct->tm_hour;
    root.data.formatMinute = tm_struct->tm_min;
    root.data.formatSecond = tm_struct->tm_sec;

    root.data.mustBe1s2 = 0b11111111111;
    root.data.mustBe1s3 = 3;

    root.data.legacySectorsPTrack = 63;
    root.data.legacyTrackPHead = DISK_SIZE / SECTOR_SIZE / 256 / 63;
    root.data.legacyHeadCount = 255;

    root.data.totalSectors = DISK_SIZE / SECTOR_SIZE;
    root.data.diskType = DISK_TYPE_VIRTUAL;

    root.data.specialSignature = 0xCAFEBABEDEADBEEF;
    root.data.numberOfBadSectors = 0;
    root.data.numberOfBadClusters = 0;

    root.data.formatVersionMajor = 1;
    root.data.formatVersionMinor = 0;

    root.data.numberOfQuickFindSectors = 16;

    root.data.nextFolderID = 2;             //! the root folder will use 1, but it doesn't call the normal
                                            //! function as this data hasn't been pushed to the disk yet
                                            //! (it hardcodes '1')

    memcpy(root.data.regionCode, "AUS ", 4);
    memcpy(root.data.languageCode, "en  ", 4);
    strcpy(root.data.volumeLabel, "MY HARD DRIVE");

    memcpy(root.data.finishCode, "THIS DISK USES THE BANANA FILESYSTEM. ***", 64);

    root.jmp[0] = 0xEB;
    root.jmp[1] = 36;
    root.jmp[2] = 0x90;

    uint8_t zero[CLUSTER_SIZE] = { 0 };
    for (int i = 0; i < DISK_SIZE / CLUSTER_SIZE; ++i) {
        writeCluster(i, zero);
    }

    uint8_t rootEntry[CLUSTER_SIZE] = \
    {0, 0, 0, 0, 0, 0, 0, 0x80, \
        0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };

    //! make bytes 32-39 contain an 8 byte unique folder ID
    //! for identification by the function that looks for 32 byte entries
    *(((uint64_t*) rootEntry) + 4) = 1;
    *(((uint64_t*) rootEntry) + 5) = 0xFFFFFFFFFFFFFFFF;     //! 'RESERVED'
    *(((uint64_t*) rootEntry) + 6) = 0x4445565245534552;     //! 'RESERVED'
    *(((uint64_t*) rootEntry) + 7) = 0x4445565245534552;     //! 'RESERVED'

    writeCluster(0, (uint8_t*) &root);
    writeCluster(ROOT_CLUSTER, rootEntry);

    turnOnCaches();
}

void setSomeAttributes(FILEINFO* data)
{
    time_t now = time(NULL);
    struct tm* tm_struct = localtime(&now);

    data->creationDate.day = tm_struct->tm_mday;
    data->creationDate.hour = tm_struct->tm_hour;
    data->creationDate.microseconds = rand();
    data->creationDate.minute = tm_struct->tm_min;
    data->creationDate.month = tm_struct->tm_mon;
    data->creationDate.second = tm_struct->tm_sec;
    data->creationDate.year = tm_struct->tm_year;

    data->openDate.day = tm_struct->tm_mday;
    data->openDate.hour = tm_struct->tm_hour;
    data->openDate.microseconds = rand();
    data->openDate.minute = tm_struct->tm_min;
    data->openDate.month = tm_struct->tm_mon;
    data->openDate.second = tm_struct->tm_sec;
    data->openDate.year = tm_struct->tm_year;

    data->modifyDate.day = tm_struct->tm_mday;
    data->modifyDate.hour = tm_struct->tm_hour;
    data->modifyDate.microseconds = rand();
    data->modifyDate.minute = tm_struct->tm_min;
    data->modifyDate.month = tm_struct->tm_mon;
    data->modifyDate.second = tm_struct->tm_sec;
    data->modifyDate.year = tm_struct->tm_year;

    data->attributes.creationsys = BANANA;
    data->attributes.mustBe1_1 = 1;
    data->attributes.mustBe1_2 = 1;
    data->attributes.mustBe1_3 = 1;

    data->userID = 'RESU';
    data->userID |= (uint64_t) 'EMAN' << 32;

    data->used[0] = '*';
    data->used[1] = '*';

    uint32_t count = 0;

    for (int i = 0; i < 4096; ++i) {
        count += *((uint8_t*) data + i);
    }

    data->checksum = 0 - count;
}

void createFile(char* name)
{
    //here we have to split the filename from the directory name
    //and work out the directory's starting cluster

    char directoryn[256];
    memset(directoryn, 0, 256);
    strcpy(directoryn, name);
    char* v = strrchr(directoryn, '/');
    bool inroot = true;
    if (v) {
        *v = 0;
        inroot = false;
    }

    uint64_t directoryStartCluster = inroot ? ROOT_CLUSTER : getFileStartPoint(directoryn);
    char* fkname = strrchr(name, '/') ? strrchr(name, '/') + 1 : name;
    puts(fkname);

    uint64_t hash = createHash(fkname);
    uint64_t fileDataCluster = addObject(hash, false, directoryStartCluster);

    FILEINFO data;
    memset(&data, 0, sizeof(data));
    strcpy(data.filename, fkname);
    data.hash = hash;
    setSomeAttributes(&data);

    writeCluster(fileDataCluster, (uint8_t*) &data);

    //76067164 6E756F53



    /*uint64_t* direntry = (uint64_t*) readCluster(directoryStartCluster);
    uint64_t dirDataSector = direntry[5];

    if (dirDataSector != 0 && dirDataSector != 0xFFFFFFFFFFFFFFFF && dirDataSector != 0xFFFFFFFFFFFFFFEE) {
        FILEINFO abc;
        memcpy(&abc, readCluster(dirDataSector), sizeof(abc));

        int i = 0;
        while (abc.dirContentHelpers[i].used) {
            if (i >= (sizeof(abc.dirContentHelpers) / sizeof(dir_content_helper_t))) {
                puts("FULL");
                abc.dirContentHelpersComplete = false;
                return;
            }
            i++;
        }
        abc.dirContentHelpers[i].used = true;
        abc.dirContentHelpers[i].folder = false;
        abc.dirContentHelpers[i].attribsUpToDate = false;
        memcpy(abc.dirContentHelpers[i].startOfFileName, fkname, \
               strlen(fkname) >= DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN ?
               DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN : strlen(fkname));

        abc.dirContentHelpers[i].complete = strlen(fkname) <= DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN;
        puts(abc.dirContentHelpers[i].startOfFileName);
        writeCluster(dirDataSector, (uint8_t*) &abc);
    }*/
}

void createDirectory(char* name)
{
    char directoryn[256];
    memset(directoryn, 0, 256);
    strcpy(directoryn, name);
    char* v = strrchr(directoryn, '/');
    bool inroot = true;
    if (v) {
        *v = 0;
        inroot = false;
    }

    uint64_t directoryStartCluster = inroot ? ROOT_CLUSTER : getFileStartPoint(directoryn);

    char* fkname = strrchr(name, '/') ? strrchr(name, '/') + 1 : name;

    puts(fkname);

    uint64_t hash = createHash(fkname);
    uint64_t fileDataCluster = addObject(hash, false, directoryStartCluster);

    FILEINFO data;
    memset(&data, 0, sizeof(data));
    strcpy(data.filename, fkname);
    data.attributes.directory = 1;
    data.dirContentHelpersComplete = true;
    data.hash = hash;
    setSomeAttributes(&data);

    //mark it used before we hunt for another cluster
    writeCluster(fileDataCluster, (uint8_t*) &data);

    data.startingCluster = findBlankCluster();
    writeCluster(fileDataCluster, (uint8_t*) &data);

    uint8_t rootEntry[4096] = \
    {0, 0, 0, 0, 0, 0, 0, 0x80, \
        0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, \
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };

    //! make bytes 32-39 contain an 8 byte unique folder ID
   //! for identification by the function that looks for 32 byte entries
    *(((uint64_t*) rootEntry) + 4) = generateUniqueFolderID();
    *(((uint64_t*) rootEntry) + 5) = fileDataCluster;   //0x4445565245534552;     //! 'RESERVED'
    *(((uint64_t*) rootEntry) + 6) = 0x4445565245534552;     //! 'RESERVED'
    *(((uint64_t*) rootEntry) + 7) = 0x4445565245534552;     //! 'RESERVED'

    writeCluster(data.startingCluster, rootEntry);



    /*uint64_t* direntry = (uint64_t*) readCluster(directoryStartCluster);
    uint64_t dirDataSector = direntry[5];

    if (dirDataSector != 0 && dirDataSector != 0xFFFFFFFFFFFFFFFF && dirDataSector != 0xFFFFFFFFFFFFFFEE) {
        FILEINFO abc;
        memcpy(&abc, readCluster(dirDataSector), sizeof(abc));

        int i = 0;
        while (abc.dirContentHelpers[i].used) {
            if (i >= (sizeof(abc.dirContentHelpers) / sizeof(dir_content_helper_t))) {
                puts("FULL");
                abc.dirContentHelpersComplete = false;
                return;
            }
            i++;
        }
        abc.dirContentHelpers[i].used = true;
        abc.dirContentHelpers[i].folder = true;
        abc.dirContentHelpers[i].attribsUpToDate = false;
        memcpy(abc.dirContentHelpers[i].startOfFileName, fkname, \
               strlen(fkname) >= DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN ?
               DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN : strlen(fkname));

        abc.dirContentHelpers[i].complete = strlen(fkname) <= DIR_CONTENT_HELPER_FILENAME_TRUNC_LEN;
        puts(abc.dirContentHelpers[i].startOfFileName);
        writeCluster(dirDataSector, (uint8_t*) &abc);
    }*/
}

void setFileContents(char* file, uint8_t* contents, uint64_t len, uint64_t bytepointer)
{
    uint64_t fileDataCluster = getFileStartPoint(file);

    FILEINFO data;
    memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

    uint64_t currentCluster = (data.startingCluster * USABLE_DATA_PER_CLUSTER + bytepointer) / USABLE_DATA_PER_CLUSTER;
    uint64_t contentPointer = HEADER_FILE_DATA_SIZE;
    uint64_t o = (bytepointer) % USABLE_DATA_PER_CLUSTER;

    DATACLUSTER check;
    DATACLUSTER current;
    //memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);

    // only works if you set byte the first time or change bytes under 1810 the second+ time

    data.smallFileBytesUsed = len > HEADER_FILE_DATA_SIZE ? HEADER_FILE_DATA_SIZE : len;
    memcpy(data.fileContentsIfItIsASmallFile + bytepointer, contents, data.smallFileBytesUsed);
    writeCluster(fileDataCluster, (uint8_t*) &data);

    turnOffCaches();

    if (len + bytepointer < HEADER_FILE_DATA_SIZE) {         //if it only used the small part
        return;
    }

    // it is quite likely that we have no data cluster here...

    if (data.startingCluster == 0) {
        uint64_t nx = findBlankCluster();
        data.startingCluster = nx;

        DATACLUSTER dta;
        memset(dta.fileData, 0, USABLE_DATA_PER_CLUSTER);
        dta.nextCluster = 0;
        dta.bytesOfClusterUsed = 0;
        dta.used = '*';

        writeCluster(nx, (uint8_t*) &dta);
        writeCluster(fileDataCluster, (uint8_t*) &data);

        currentCluster = (nx * USABLE_DATA_PER_CLUSTER + bytepointer) / USABLE_DATA_PER_CLUSTER;
    }

    do {
        memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
        memcpy(&check, &current, CLUSTER_SIZE);

        if (len - contentPointer <= USABLE_DATA_PER_CLUSTER) {
            if (len - contentPointer + o > current.bytesOfClusterUsed) {
                current.bytesOfClusterUsed = len - contentPointer + o;
            }
            memcpy(current.fileData + o, contents + contentPointer, len - contentPointer);

        } else {
            memcpy(current.fileData + o, contents + contentPointer, USABLE_DATA_PER_CLUSTER - o);
        }

        if (!current.nextCluster && len - contentPointer > USABLE_DATA_PER_CLUSTER) {
            writeCluster(currentCluster, (uint8_t*) &current);      //write the cluster early to ensure it is used
            uint64_t nx = findBlankCluster();
            current.nextCluster = nx;

            DATACLUSTER dta;
            memset(dta.fileData, 0, USABLE_DATA_PER_CLUSTER);
            dta.nextCluster = 0;
            dta.bytesOfClusterUsed = 0;
            dta.used = '*';

            writeCluster(nx, (uint8_t*) &dta);
        }

        if (memcmp(&current, &check, CLUSTER_SIZE)) {                 //only write if they are different
            writeCluster(currentCluster, (uint8_t*) &current);
        }

        currentCluster = current.nextCluster;
        contentPointer += USABLE_DATA_PER_CLUSTER - o;
        o = 0;

    } while (contentPointer < len);
    turnOnCaches();
}

void truncateFile(char* file, uint64_t byte)
{
    uint64_t cluster = (byte - HEADER_FILE_DATA_SIZE) / USABLE_DATA_PER_CLUSTER;
    uint64_t offset = (byte - HEADER_FILE_DATA_SIZE) % USABLE_DATA_PER_CLUSTER;

    printf("%llu, %llu\n", cluster, offset);

    if (byte < HEADER_FILE_DATA_SIZE) {
        uint64_t fileDataCluster = getFileStartPoint(file);
        FILEINFO data;
        memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);
        data.fileContentsIfItIsASmallFile[byte] = 0;        //just so we can see things better in the hex editor
        data.smallFileBytesUsed = byte;                     //the actual change
        writeCluster(fileDataCluster, (uint8_t*) &data);

        uint64_t currentCluster = data.startingCluster;
        uint8_t nulls[CLUSTER_SIZE];
        memset(nulls, 0, CLUSTER_SIZE);
        DATACLUSTER current;

        while (currentCluster) {
            memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
            writeCluster(currentCluster, nulls);
            setSpaceAtLocation(currentCluster, false);
            currentCluster = current.nextCluster;
        }

        return;
    }

    if (cluster != 0) {
        uint64_t fileDataCluster = getFileStartPoint(file);
        FILEINFO data;
        memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

        DATACLUSTER current;
        DATACLUSTER lastone;
        uint64_t currentCluster = data.startingCluster;

        for (int i = 0; i < cluster; ++i) {
            memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
            currentCluster = current.nextCluster;
        }

        memcpy(&lastone, readCluster(currentCluster), CLUSTER_SIZE);
        currentCluster = current.nextCluster;

        uint64_t next = lastone.nextCluster;

        lastone.bytesOfClusterUsed = offset;
        lastone.nextCluster = 0;

        printf("The last cluster we want is on cluster %llu, stopping at byte %llu\n", currentCluster, offset);

        if (currentCluster < c) {
            c = currentCluster;         //slight speedup
        }

        writeCluster(currentCluster, (uint8_t*) &lastone);

        current.nextCluster = next;
        currentCluster = lastone.nextCluster;

        uint8_t nulls[CLUSTER_SIZE];
        memset(nulls, 0, CLUSTER_SIZE);

        while (currentCluster) {
            memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
            writeCluster(currentCluster, nulls);
            currentCluster = current.nextCluster;
            setSpaceAtLocation(currentCluster, false);
        }

    } else {
        uint64_t fileDataCluster = getFileStartPoint(file);
        FILEINFO data;
        memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

        DATACLUSTER current;
        DATACLUSTER ncur;

        uint64_t currentCluster = data.startingCluster;
        memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
        ncur = current;
        ncur.nextCluster = 0;
        ncur.bytesOfClusterUsed = offset;
        writeCluster(currentCluster, (uint8_t*) &ncur);
        currentCluster = current.nextCluster;

        uint8_t nulls[CLUSTER_SIZE];
        memset(nulls, 0, CLUSTER_SIZE);

        while (currentCluster) {
            memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
            writeCluster(currentCluster, nulls);
            currentCluster = current.nextCluster;
            setSpaceAtLocation(currentCluster, false);
        }
    }
}

void deleteFile(char* file)
{
    //http://www.algolist.net/Data_structures/Binary_search_tree/Removal

    // THIS ONLY WORKS IF THERE ARE 0/1 CHILD NODES!

    char nulls[CLUSTER_SIZE];
    memset(nulls, 0, CLUSTER_SIZE);

    uint64_t fileDataCluster = getFileStartPoint(file);
    FILEINFO data;
    memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

    DATACLUSTER current;
    uint64_t currentCluster = data.startingCluster;

    writeCluster(fileDataCluster, (uint8_t*) nulls);
    setSpaceAtLocation(fileDataCluster, false);

    while (currentCluster) {
        memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
        writeCluster(currentCluster, (uint8_t*) nulls);
        setSpaceAtLocation(currentCluster, false);
        currentCluster = current.nextCluster;
    }

    clearFileEntry(file);
}

uint8_t* readFile(char* filename, uint64_t bytes)
{
    uint8_t* returnval = calloc(bytes, 1);

    uint64_t fileDataCluster = getFileStartPoint(filename);

    printf("starts at: %d\n", fileDataCluster);
    FILEINFO data;
    memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

    memcpy(returnval, data.fileContentsIfItIsASmallFile, data.smallFileBytesUsed > bytes ? bytes : data.smallFileBytesUsed);
    printf(">>> %d\n", data.smallFileBytesUsed);

    DATACLUSTER current;
    uint64_t currentCluster = data.startingCluster;
    printf("> %llX\n", currentCluster);
    uint64_t bytesDone = data.smallFileBytesUsed;

    while (currentCluster) {
        memcpy(&current, readCluster(currentCluster), CLUSTER_SIZE);
        puts((char*) &current);
        memcpy(returnval + bytesDone, &current, \
               (bytesDone + CLUSTER_SIZE) >= bytes ? bytes % CLUSTER_SIZE : CLUSTER_SIZE);

        currentCluster = current.nextCluster;
        bytesDone += CLUSTER_SIZE;
        if (bytesDone >= bytes) {
            break;
        }
    }

    return returnval;
}

void renameFile(char* file, char* name)
{
    //! THIS FUNCTION:
    //!     REMEMBERS THE FILE'S INFORMATION CLUSTER
    //!     DELETES THE TABLE ENTRY
    //!     ADDS THE NEW TABLE ENTRY
    //!     POINTS IT TO THE OLD DATA

    //uint64_t entryByte = getFileTableEntryByte(file);
    uint64_t fileDataCluster = getFileStartPoint(file);
    FILEINFO data;
    memcpy(&data, readCluster(fileDataCluster), CLUSTER_SIZE);

    //! remember the information cluster of the file so that when we
    //! re-add the entry we can point it the right way
    uint64_t currentCluster = data.startingCluster;

    char directoryn[256];
    memset(directoryn, 0, 256);
    strcpy(directoryn, name);
    char* v = strrchr(directoryn, '/');
    bool inroot = true;
    if (v) {
        *v = 0;
        inroot = false;
    }
    printf("%% ** %s\n", directoryn);

    uint64_t directoryStartCluster = inroot ? ROOT_CLUSTER : getFileStartPoint(directoryn);
    printf("%% root = %u, starts here: %u. used root? %d\n", (unsigned) ROOT_CLUSTER, (unsigned) directoryStartCluster, inroot);

    char* fkname = strrchr(name, '/') ? strrchr(name, '/') + 1 : name;

    puts(fkname);

    uint64_t hash = createHash(fkname);
    addObjectNoAllocatedClusterWithByteLocation(hash, false, directoryStartCluster, currentCluster);

    clearFileEntry(file);
}

void gen_random(char* s, const int len)
{
    for (int i = 0; i < len; ++i) {
        int randomChar = rand() % (26 + 26 + 10);
        if (randomChar < 26)
            s[i] = 'a' + randomChar;
        else if (randomChar < 26 + 26)
            s[i] = 'A' + randomChar - 26;
        else
            s[i] = '0' + randomChar - 26 - 26;
    }
    s[len] = 0;
}

void filemaketime()
{
    for (int i = 0; i < 1000; ++i) {
        char bf[512];
        sprintf(bf, "FILE%X.TXT", i);
        createFile(bf);

        int x = 10 * 1024;
        char* r = malloc(x);
        gen_random(r, x);
        setFileContents(bf, (uint8_t*) r, x, 0);
        free(r);

        if (x % 2) {
            deleteFile(bf);
        }
    }
}

/*void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name))) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path, indent + 2);
        } else {
            char path[1024];
            sprintf(path, "%s/%s", name, entry->d_name);
            puts(path);
            createFile(path);
            FILE* f = fopen(path, "rb");
            fseek(f, 0, SEEK_END);
            long a = ftell(f);
            rewind(f);
            char* b = malloc(a);
            fread(b, a, 1, f);
            fclose(f);
            setFileContents(path, b, a, 0);
            free(b);
        }
    }
    closedir(dir);
}*/

void listdir(char* dir)
{
    DIR* dp;
    struct dirent* entry;
    struct stat statbuf;
    //char *subdir;

    if ((dp = opendir(dir)) == NULL) {
        printf("cannot open directory: %s\n", dir);
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        char path[1024];
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &statbuf) == 0) {
            if (statbuf.st_mode & S_IFDIR) {
                char path[1024];
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
                listdir(path);

            } else {
                char pathx[1024];
                sprintf(pathx, "%s/%s", dir, entry->d_name);
                char* path = pathx + strlen(ROOT_LOCATION);
                while (path[0] == '/') {
                    path++;
                }
                createFile(path);
                FILE* f = fopen(pathx, "rb");
                fseek(f, 0, SEEK_END);
                long a = ftell(f);
                rewind(f);
                char* b = malloc(a);
                fread(b, a, 1, f);
                fclose(f);

                setFileContents(path, (uint8_t*) b, a, 0);
                free(b);
            }
        }
    }

    closedir(dp);
}

int main(int argc, const char* argv[])
{
    diskImage = fopen(DISK_IMAGE, "wb+");

    formatDisk(DISK_IMAGE);

    clock_t t;
    t = clock();

    /*
     Generated via a Python script:

     import os
     os.chdir('/Users/alex_boxall21/Desktop/Banana Backup/Root')
     l = [x[0] for x in os.walk('.')]
     for i in l:
        print('createDirectory("' + i.replace('./', '') + '");')

     */

    createDirectory("Directory");
    createFile("File.txt");
    createFile("Document.doc");
    createFile("Directory/File.txt");

    /*createDirectory("Banana");
    createDirectory("Banana/Cursors");
    createDirectory("Banana/Developer");
    createDirectory("Banana/Developer/source");
    createDirectory("Banana/Developer/source/gnustep-objc");
    createDirectory("Banana/Developer/source/gnustep-objc/modified source");
    createDirectory("Banana/Developer/source/gnustep-objc/modified source/objc");
    createDirectory("Banana/Developer/startfiles");
    createDirectory("Banana/Developer/startfiles/Source");
    createDirectory("Banana/Developer/usr");
    createDirectory("Banana/Developer/usr/CompilerBuiltin");
    createDirectory("Banana/Developer/usr/include");
    createDirectory("Banana/Developer/usr/include/Banana");
    createDirectory("Banana/Developer/usr/include/Exceptions");
    createDirectory("Banana/Developer/usr/include/freetype");
    createDirectory("Banana/Developer/usr/include/freetype/config");
    createDirectory("Banana/Developer/usr/include/freetype2");
    createDirectory("Banana/Developer/usr/include/sys");
    createDirectory("Banana/Developer/usr/lib");
    createDirectory("Banana/Developer/usr/lib/pkgconfig");
    createDirectory("Banana/Developer/usr/share");
    createDirectory("Banana/Developer/usr/share/aclocal");
    createDirectory("Banana/Developer/usr/share/man");
    createDirectory("Banana/Developer/usr/share/man/man1");
    createDirectory("Banana/Developer/usr/share/man/man3");
    createDirectory("Banana/Developer/usr/System");
    createDirectory("Banana/Developer/usr/System/Common");
    createDirectory("Banana/Developer32");
    createDirectory("Banana/Developer32/startfiles");
    createDirectory("Banana/Developer32/startfiles/Source");
    createDirectory("Banana/Developer32/usr");
    createDirectory("Banana/Developer32/usr/CompilerBuiltin");
    createDirectory("Banana/Developer32/usr/include");
    createDirectory("Banana/Developer32/usr/include/Banana");
    createDirectory("Banana/Developer32/usr/include/Exceptions");
    createDirectory("Banana/Developer32/usr/include/sys");
    createDirectory("Banana/Developer32/usr/lib");
    createDirectory("Banana/Developer32/usr/System");
    createDirectory("Banana/Developer32/usr/System/Common");
    createDirectory("Banana/Drivers");
    createDirectory("Banana/Fonts");
    createDirectory("Banana/FontsTTF");
    createDirectory("Banana/Icons");
    createDirectory("Banana/Keymaps");
    createDirectory("Banana/Logs");
    createDirectory("Banana/Logs/Applications");
    createDirectory("Banana/Logs/System");
    createDirectory("Banana/Program Data");
    createDirectory("Banana/Programs");
    createDirectory("Banana/Registry");
    createDirectory("Banana/Resources");
    createDirectory("Banana/Resources/File Associations");
    createDirectory("Banana/Settings");
    createDirectory("Banana/Settings/Alex");
    createDirectory("Banana/Sounds");
    createDirectory("Banana/System");
    createDirectory("Banana/Temporary Files");
    createDirectory("Banana/UserData");
    createDirectory("Users");
    createDirectory("Users/Alex");
    createDirectory("Users/Alex/Desktop");
    createDirectory("Users/Alex/Documents");
    createDirectory("Users/Alex/Music");
    createDirectory("Users/Alex/Pictures");
    createDirectory("Users/Alex/Trash*/

    //listdir (ROOT_LOCATION);

    deleteFile("Banana/System/Login.exe");
    deleteFile("Banana/Icons/Startmnu.gfx");
    deleteFile("Banana/Cursors/DRESIZE1.CUR");
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds

    printf("It took %f seconds to create create a Banana disk image\n\
ROOTCLUSTER %lu\nDATACLUSTER %lu\nFILEINFO    %lu\n", \
time_taken, sizeof(struct ROOTCLUSTER), sizeof(struct DATACLUSTER), sizeof(struct FILEINFO));

    fclose(diskImage);
    printf("Finished!\n");

    return 0;
}



//
//  utils.c
//  Banana Filesystem
//
//  Created by Alex Boxall on 4/11/17.
//  Copyright © 2017 Alex Boxall. All rights reserved.
//


void writeSector(uint64_t sectorNumber, uint8_t* data)
{
    char b[SECTOR_SIZE];
    memcpy(b, data, SECTOR_SIZE);
    /*for (int i = 0; i < SECTOR_SIZE; ++i) {
        b[i] ^= 0xFF;
    }*/

    if (sectorNumber > (uint64_t) 9223372036854775813ULL) {     //LONG_MAX - 1
        printf("Was going to write to an invalid sector %llu/0x%llX, cancelling!\n", sectorNumber, sectorNumber);
        return;
    }
    rewind(diskImage);
    fseek(diskImage, sectorNumber * SECTOR_SIZE, SEEK_CUR);
    fwrite(b, SECTOR_SIZE, 1, diskImage);
    fflush(diskImage);
}

uint8_t* readSector(uint64_t sectorNumber)
{
    rewind(diskImage);
    fseek(diskImage, sectorNumber * SECTOR_SIZE, SEEK_CUR);
    uint8_t* data = malloc(SECTOR_SIZE);
    fread(data, SECTOR_SIZE, 1, diskImage);

    return data;
}

uint8_t* readWriteWithCaches(uint64_t clusterNumber, uint8_t* data, bool write)
{
    bool found = false;
    uint8_t* toReturn = calloc(CLUSTER_SIZE, 1);

    int64_t lowestRelevancy = 0x7FFFFFFFFFFFFFFF;
    int lowestRelevancyCacheNumber = MAX_CLUSTER_CACHES + 999999;

    for (int i = 0; i < MAX_CLUSTER_CACHES; ++i) {
        if (cluster_caches[i].clusterNumber == 0xFFFFFFFFFFFFFFFF) {
            lowestRelevancyCacheNumber = i;
            lowestRelevancy = 0;
            continue;
        }
        --cluster_caches[i].relevancy;
        if (cluster_caches[i].clusterNumber == clusterNumber) {
            found = true;
            cluster_caches[i].relevancy += 4;
            if (cluster_caches[i].relevancy < 10) {
                cluster_caches[i].relevancy = 10;
            }
            if (write) {
                cluster_caches[i].dirty = true;
                memcpy(cluster_caches[i].data, data, CLUSTER_SIZE);
            } else {
                memcpy(toReturn, cluster_caches[i].data, CLUSTER_SIZE);
            }
            //printf("Read/write from cache %d: %llu, 0x%llX\n", i, clusterNumber, clusterNumber);
        }
        if (cluster_caches[i].relevancy < lowestRelevancy) {
            lowestRelevancy = cluster_caches[i].relevancy;
            lowestRelevancyCacheNumber = i;
        }
    }

    if (lowestRelevancy == 0x7FFFFFFFFFFFFFFF) {
        lowestRelevancyCacheNumber = 0;
    }

    if (!found) {
        //by default, writeCluster will call this function
        cachesOn = false;

        //printf("loading cache %d. write? %c. cluster %llu, 0x%llX.\n", lowestRelevancyCacheNumber, write ? 'y' : 'n', clusterNumber, clusterNumber);

        for (int i = 0; i < MAX_CLUSTER_CACHES; ++i) {
            //printf("\tC %d: Cluster %llu, 0x%llX\n", i, cluster_caches[i].clusterNumber, cluster_caches[i].clusterNumber);
        }

        //save the old content of the cache to the disk
        if (cluster_caches[lowestRelevancyCacheNumber].clusterNumber != 0xFFFFFFFFFFFFFFFF) {
            writeCluster(cluster_caches[lowestRelevancyCacheNumber].clusterNumber, cluster_caches[lowestRelevancyCacheNumber].data);
        }

        if (write) {
            //load the new data into the cache (not the disk, that will happen after
            //this cache cluster gets moved back to the disk)
            memcpy(cluster_caches[lowestRelevancyCacheNumber].data, data, CLUSTER_SIZE);

            cluster_caches[lowestRelevancyCacheNumber].clusterNumber = clusterNumber;
            cluster_caches[lowestRelevancyCacheNumber].relevancy = 20;
            cluster_caches[lowestRelevancyCacheNumber].dirty = true;

        } else {
            //load the data into the cache for future use
            uint8_t* readc = readCluster(clusterNumber);
            memcpy(cluster_caches[lowestRelevancyCacheNumber].data, readc, CLUSTER_SIZE);
            cluster_caches[lowestRelevancyCacheNumber].clusterNumber = clusterNumber;
            cluster_caches[lowestRelevancyCacheNumber].relevancy = 20;

            //and return the actual data that was just read
            memcpy(toReturn, cluster_caches[lowestRelevancyCacheNumber].data, CLUSTER_SIZE);
            free(readc);
        }
        //it is safe to turn them on, as they must've been on to get here
        turnOnCaches();
    }

    return toReturn;
}

void turnOffCaches()
{
    cachesOn = false;

    for (int i = 0; i < MAX_CLUSTER_CACHES; ++i) {
        if (cluster_caches[i].clusterNumber != 0xFFFFFFFFFFFFFFFF && cluster_caches[i].dirty) {
            writeCluster(cluster_caches[i].clusterNumber, cluster_caches[i].data);
            cluster_caches[i].dirty = false;
        }
    }
}

void turnOnCaches()
{
    cachesOn = false;   //true;
}

void writeCluster(uint64_t clusterNumber, uint8_t* data)
{
    if (cachesOn) {
        free(readWriteWithCaches(clusterNumber, data, true));
    } else {
        for (int i = 0; i < SECTORS_PER_CLUSTER; ++i) {
            writeSector(clusterNumber * SECTORS_PER_CLUSTER + i, data + i * SECTOR_SIZE);
        }
    }
}

uint8_t* readCluster(uint64_t clusterNumber)
{
    if (cachesOn) {
        return readWriteWithCaches(clusterNumber, 0, false);
    } else {
        uint8_t* data = malloc(CLUSTER_SIZE);
        for (int i = 0; i < SECTORS_PER_CLUSTER; ++i) {
            memcpy(data + i * SECTOR_SIZE, readSector(clusterNumber * SECTORS_PER_CLUSTER + i), SECTOR_SIZE);
        }
        return data;
    }
}

uint64_t createHash(char* string)
{
    return MurmurHash64A(string, (int) strlen(string), 0xCAFE6614);

    /*uint64_t ss = 0;
    uint32_t aa = 0;
    for (int i = 0; i < (strlen(string) > 5 ? 5 : strlen(string)); ++i) {
        ss <<= 8;
        ss |= string[i];
    }
    for (int i = 0; i < strlen(string); ++i) {
        aa ^= string[i];
        aa <<= 3;
        aa -= string[i];
    }

    aa = MurmurHash64A (string, (int)strlen(string), 0xCAFE6614);

    ss <<= 24;
    ss |= aa & 0xFFFFFF;
    return ss;*/
}

uint64_t lastTimeCluster = -1;
uint8_t* lastTimeData = 0;

bool checkForSpaceAtLocation(uint64_t clusterNumber)
{

    uint64_t cluster = FREESPACE_TABLE_BASE + (clusterNumber / CLUSTER_SIZE / 8);
    uint32_t byte = (clusterNumber % (CLUSTER_SIZE * 8)) / 8;
    uint32_t bit = (clusterNumber % (CLUSTER_SIZE * 8)) % 8;

    //printf("READ: %llX, %d, %d\n", cluster, byte, bit);

    uint8_t* data;
    if (cluster == lastTimeCluster && lastTimeData) {
        data = malloc(CLUSTER_SIZE);
        memcpy(data, lastTimeData, CLUSTER_SIZE);

    } else {
        if (lastTimeData != 0) {
            free(lastTimeData);
        }
        data = malloc(CLUSTER_SIZE);
        data = readCluster(cluster);
        lastTimeData = malloc(CLUSTER_SIZE);
        memcpy(lastTimeData, data, CLUSTER_SIZE);
    }

    lastTimeCluster = cluster;

    //printf("READ: data[byte] = 0x%X\n", data[byte]);

    bool ret = data[byte] & (1 << bit);
    free(data);
    return ret;
}

void setSpaceAtLocation(uint64_t clusterNumber, bool value)
{
    //invalidate cache
    lastTimeData = 0;

    uint64_t cluster = FREESPACE_TABLE_BASE + (clusterNumber / CLUSTER_SIZE / 8);
    uint32_t byte = (clusterNumber % (CLUSTER_SIZE * 8)) / 8;
    uint32_t bit = (clusterNumber % (CLUSTER_SIZE * 8)) % 8;

    //printf("WRITE: %llX, %d, %d\n", cluster, byte, bit);

    uint8_t* data = malloc(CLUSTER_SIZE);
    data = readCluster(cluster);
    if (value) {
        data[byte] |= (1 << bit);
    } else {
        data[byte] &= ~(1 << bit);
    }
    writeCluster(cluster, data);
}

uint64_t findBlankCluster()
{
    static uint64_t c = ROOT_CLUSTER;
    bool secondTime = false;
    while (1) {
        if (!checkForSpaceAtLocation(c)) {
            //printf("CLUSTER 0x%llX FOUND\n", c);
            setSpaceAtLocation(c, true);
            return c;
        }
        ++c;
        if (c > (DISK_SIZE / CLUSTER_SIZE)) {
            c = ROOT_CLUSTER;
            if (!secondTime) {
                secondTime = true;
            } else {
                puts("OUT OF DISK SPACE! A");
                exit(1);
            }
        }
    }

    /*//turnOffCaches();
    static uint64_t c = ROOT_CLUSTER;
    bool secondTime = false;
    while (1) {
        uint8_t* data = malloc(CLUSTER_SIZE);
        data = readCluster(c);

        if (data[0] != '*') {
            bool bad = false;

            for (int i = 0; i < CLUSTER_SIZE; ++i) {
                if (data[i]) {
                    bad = true;
                    break;
                }
            }

            if (!bad) {
                turnOnCaches();
                return c;
            }
        }

        ++c;
        if (c > (DISK_SIZE / CLUSTER_SIZE)) {
            c = ROOT_CLUSTER;
            if (!secondTime) {
                secondTime = true;
            } else {
                puts("OUT OF DISK SPACE! A");
                exit(1);
            }
        }
    }*/
}

uint64_t generateUniqueFolderID()
{
    ROOTCLUSTER root;
    memcpy(&root, readCluster(0), sizeof(root));

    puts(root.filesystem);

    uint64_t id = root.data.nextFolderID;
    if (id <= 1) {
        puts("BAD DISK! FOLDER ID == 0/1");
        //! 0 = invalid
        //! 1 = must be used by the root folder, but it doesn't call this function, it hardcodes '1'
        return 0xEFBEADDEEFBEADDE;      //!make 'deadbeef' look nice in a a hex editor
    }
    ++root.data.nextFolderID;

    writeCluster(0, (uint8_t*) &root);
    return id;
}


uint64_t findNewLocation(uint64_t folderID)
{
    bool secondTime = false;
    static uint64_t c = ROOT_CLUSTER;
    uint64_t goodBlankCluster = 0;

    //turnOffCaches();

    while (1) {
        //printf(".");

        uint8_t* data = malloc(CLUSTER_SIZE);
        data = readCluster(c);

        if (!checkForSpaceAtLocation(c)) {
            uint64_t* cst = (uint64_t*) data;

            if (cst[4] == 0) {
                bool notClear = false;
                //ensure the entire cluster is clear if it has a blank directory section
                //in case it is being used by something else
                for (int i = 0; i < CLUSTER_SIZE / 8; ++i) {
                    if (cst[i]) {
                        notClear = true;
                        break;
                    }
                }
                if (!notClear) {
                    cst[0] = 0x8000000000000000;
                    cst[1] = 0;
                    cst[2] = 0;
                    cst[3] = 0xFFFFFFFFFFFFFFFF;
                    cst[4] = folderID;
                    cst[5] = 0x4445565245534552;
                    cst[6] = 0x4445565245534552;     //"RESERVED"
                    cst[7] = 0x4445565245534552;
                    writeCluster(c, data);
                }
            }

            if (cst[4] == folderID) {
                for (int i = 0; i < CLUSTER_SIZE; i += 32) {
                    bool bad = false;
                    for (int a = 0; a < 32; ++a) {
                        if (data[i + a]) {
                            bad = true;
                            break;
                        }
                    }
                    if (!bad) {
                        turnOnCaches();
                        //printf("\n");
                        return c * CLUSTER_SIZE + i;
                    }
                }
            }

            // We will try to find a blank cluster while trying to find an
            // already used directory cluster. After one is found it gets
            // stored, and will be used at the very start of the second
            // iteration. Nothing was found in the first iteration, the
            // second loop will go on and if we find one, will will
            // immediately return it

            if (!goodBlankCluster) {
                bool bad = false;

                for (int i = 0; i < CLUSTER_SIZE; ++i) {
                    if (data[i]) {
                        bad = true;
                        break;
                    }
                }

                if (!bad) {
                    goodBlankCluster = c * CLUSTER_SIZE;
                    printf("Blank cluster = %llu\n", goodBlankCluster / CLUSTER_SIZE);
                    if (secondTime) {
                        uint64_t* mm = malloc(CLUSTER_SIZE);
                        mm[0] = 0x8000000000000000;
                        mm[1] = 0;
                        mm[2] = 0;
                        mm[3] = 0xFFFFFFFFFFFFFFFF;
                        mm[4] = folderID;
                        mm[5] = 0x4445565245534552;
                        mm[6] = 0x4445565245534552;
                        mm[7] = 0x4445565245534552;
                        writeCluster(goodBlankCluster / CLUSTER_SIZE, (uint8_t*) mm);
                        free(mm);
                        turnOnCaches();
                        //printf("\n");
                        return goodBlankCluster + 64;       //skip the blank + folder ID entries
                    }
                }
            }
        }

        ++c;
        if (c > (DISK_SIZE / CLUSTER_SIZE)) {
            printf("sizeof(c) = %lu, c = %llu, DISK_SIZE = %d, DISK_SIZE / CLUSTER_SIZE = %d\n", sizeof(c), c, DISK_SIZE, DISK_SIZE / CLUSTER_SIZE);
            if (!secondTime) {
                secondTime = true;
                if (goodBlankCluster) {
                    uint64_t* mm = malloc(CLUSTER_SIZE);
                    mm[0] = 0x8000000000000000;
                    mm[1] = 0;
                    mm[2] = 0;
                    mm[3] = 0xFFFFFFFFFFFFFFFF;
                    mm[4] = folderID;
                    mm[5] = 0x4445565245534552;
                    mm[6] = 0x4445565245534552;     //"RESERVED"
                    mm[7] = 0x4445565245534552;
                    writeCluster(goodBlankCluster / CLUSTER_SIZE, (uint8_t*) mm);
                    free(mm);
                    turnOnCaches();
                    //printf("\n");

                    return goodBlankCluster + 64;       //skip the blank + folder ID entries
                }
            } else {
                puts("OUT OF DISK SPACE! B");
                exit(1);
            }
            c = ROOT_CLUSTER;
        }
    }
    return 0;
}

uint64_t getFolderID(uint64_t datacluster)
{
    uint64_t data[4096 / 8];
    memcpy((uint8_t*) data, readCluster(datacluster), 4096);
    return data[4];
}

void addObjectNoAllocatedClusterWithByteLocation(uint64_t hash, bool dir, uint64_t startCluster, uint64_t datalocation)
{
    uint64_t byteAddress = startCluster * CLUSTER_SIZE;
    uint8_t* data = 0;
    uint64_t lastTime = 0;

    while (1) {
        //only reload data if it was different than last time
        if (byteAddress / CLUSTER_SIZE != lastTime) {
            data = readCluster(byteAddress / CLUSTER_SIZE);
            lastTime = byteAddress / CLUSTER_SIZE;
        }

        uint64_t dataHash = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE));
        uint64_t left = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
        uint64_t right = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));

        if (hash > dataHash) {
            if (right) {
                byteAddress = right;
                continue;

            } else {
                uint64_t location = findNewLocation(getFolderID(byteAddress / CLUSTER_SIZE));

                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)) = location;
                writeCluster(byteAddress / CLUSTER_SIZE, data);
                free(data);

                uint8_t* data2 = malloc(CLUSTER_SIZE);
                data2 = readCluster(location / CLUSTER_SIZE);
                *((uint64_t*) (data2 + location % CLUSTER_SIZE)) = hash;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 8)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 16)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 24)) = datalocation;
                writeCluster(location / CLUSTER_SIZE, data2);
                return;
            }

        } else if (hash < dataHash) {
            if (left) {
                byteAddress = left;
                continue;

            } else {
                uint64_t location = findNewLocation(getFolderID(byteAddress / CLUSTER_SIZE));
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8)) = location;
                writeCluster(byteAddress / CLUSTER_SIZE, data);
                free(data);

                uint8_t* data2 = malloc(CLUSTER_SIZE);
                data2 = readCluster(location / CLUSTER_SIZE);
                *((uint64_t*) (data2 + location % CLUSTER_SIZE)) = hash;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 8)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 16)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 24)) = datalocation;
                writeCluster(location / CLUSTER_SIZE, data2);
                return;
            }

        } else {
            puts("HASH COLLISION!");
            exit(3);
        }
    }
}

uint64_t addObject(uint64_t hash, bool dir, uint64_t startCluster)
{
    uint64_t byteAddress = startCluster * CLUSTER_SIZE;
    uint8_t* data = 0;
    uint64_t lastTime = 0;

    while (1) {
        //only reload data if it was different than last time
        if (byteAddress / CLUSTER_SIZE != lastTime) {
            data = readCluster(byteAddress / CLUSTER_SIZE);
            lastTime = byteAddress / CLUSTER_SIZE;
        }

        uint64_t dataHash = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE));
        uint64_t left = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
        uint64_t right = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));

        if (hash > dataHash) {
            if (right) {
                byteAddress = right;
                continue;

            } else {
                uint64_t location = findNewLocation(getFolderID(byteAddress / CLUSTER_SIZE));

                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)) = location;
                writeCluster(byteAddress / CLUSTER_SIZE, data);
                free(data);

                uint8_t* data2 = malloc(CLUSTER_SIZE);
                data2 = readCluster(location / CLUSTER_SIZE);
                *((uint64_t*) (data2 + location % CLUSTER_SIZE)) = hash;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 8)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 16)) = 0;

                if (findBlankCluster() == location / CLUSTER_SIZE) {
                    //if the cluster we are writing the directory entry to
                    //is blank, we must put something in it so that the
                    //file data doesn't overwrite it, as it works out what
                    //cluster to write to BEFORE we finish the dir entry write

                    writeCluster(location / CLUSTER_SIZE, data2);
                }

                uint64_t dataPointer = findBlankCluster();
                if (dir) {
                    dataPointer |= 0x8000000000000000;
                }

                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 24)) = dataPointer;
                writeCluster(location / CLUSTER_SIZE, data2);

                setSpaceAtLocation(dataPointer, true);
                //uint8_t uc[4096] = {'*', '*', 0};
                //writeCluster(dataPointer, uc);

                return dataPointer;
            }

        } else if (hash < dataHash) {
            if (left) {
                byteAddress = left;
                continue;

            } else {
                uint64_t location = findNewLocation(getFolderID(byteAddress / CLUSTER_SIZE));
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8)) = location;
                writeCluster(byteAddress / CLUSTER_SIZE, data);
                free(data);

                uint8_t* data2 = malloc(CLUSTER_SIZE);
                data2 = readCluster(location / CLUSTER_SIZE);
                *((uint64_t*) (data2 + location % CLUSTER_SIZE)) = hash;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 8)) = 0;
                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 16)) = 0;

                if (findBlankCluster() == location / CLUSTER_SIZE) {
                    //if the cluster we are writing the directory entry to
                    //is blank, we must put something in it so that the
                    //file data doesn't overwrite it, as it works out what
                    //cluster to write to BEFORE we finish the dir entry write

                    writeCluster(location / CLUSTER_SIZE, data2);
                }

                uint64_t dataPointer = findBlankCluster();
                if (dir) {
                    dataPointer |= 0x8000000000000000;
                }

                *((uint64_t*) (data2 + location % CLUSTER_SIZE + 24)) = dataPointer;
                writeCluster(location / CLUSTER_SIZE, data2);

                setSpaceAtLocation(dataPointer, true);
                //uint8_t uc[4096] = {'*', '*', 0};
                //writeCluster(dataPointer, uc);

                return dataPointer;
            }

        } else {
            puts("HASH COLLISION!");
            exit(3);
        }
    }
}

//! CAN BE A FILE OR DIRECTORY NAME.
//! MUST BE A RELATIVE PATH TO THE CLUSTER
//! EXAMPLE INPUT: getFileStart... ("FILE.TXT", ROOT_CLUSER);
//! INVALID INPUT: getFileStart... ("C:/FOLDER/FILE.TXT", ROOT_CLUSTER);

//! IF YOU WANT A RECURSIVE /FOLDER/SUB/FILE.TXT, USE 'getFileStartPoint'
//! WHICH IN TURN CALLS THIS FUNCTION

uint64_t getFileStartPointFromClusterStart(char* filename, uint64_t clusterstart)
{
    //turnOnCaches();
    uint64_t byteAddress = clusterstart * CLUSTER_SIZE;
    uint64_t hash = createHash(filename);

    uint8_t* data = 0;
    uint64_t lastTime = 0;

    while (1) {
        //only reload data if it was different than last time
        if (byteAddress / CLUSTER_SIZE != lastTime) {
            data = readCluster(byteAddress / CLUSTER_SIZE);
            lastTime = byteAddress / CLUSTER_SIZE;
        }

        uint64_t dataHash = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE));
        uint64_t left = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
        uint64_t right = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));
        uint64_t dloc = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24));

        bool dir = dloc & ((uint64_t) 0x8000000000000000);

        if (dir) {
            dloc += ((uint64_t) 0x8000000000000000);
        }

        if (hash > dataHash) {
            byteAddress = right;

        } else if (hash < dataHash) {
            byteAddress = left;

        } else {
            //turnOffCaches();
            free(data);
            return dloc;
        }

        if (!byteAddress) {      //if it is zero and we haven't matched, the file doesn't exist
            puts("NO FILE");
            //turnOffCaches();
            return FILEERR_NOFILE;
        }
    }
}

uint64_t getFileStartPoint(char* filename)
{
    int64_t ptr = 0;
    bool lastTime = false;
    char entry[256];
    uint64_t currentCluster = ROOT_CLUSTER;

    while (1) {
        if (filename[ptr + 1] == ':') {         //! ensure this is only called the first time by using ptr+1 instead of 1
            ptr = 2;
        }
        if (filename[ptr] == '/') {
            ++ptr;
        }
        if (ptr >= strlen(filename)) {
            return currentCluster;
        }

        char* position = strchr(filename + ptr, '/');
        if (position == 0) {
            lastTime = true;
        }
        position += 1;

        memset(entry, 0, 256);
        strcat(entry, filename + ptr);
        char* v = strchr(entry, '/');
        if (v) *v = 0;

        //! LOOK FOR 'FOLDER' IN THE ROOT DIR -> gives us the folder's data entry

        currentCluster = getFileStartPointFromClusterStart(entry, currentCluster);

        FILEINFO ag;
        memcpy(&ag, readCluster(currentCluster), sizeof(ag));

        if (ag.attributes.directory) {
            currentCluster = ag.startingCluster;
        } else if (!lastTime) {
            puts("POSSIBLE ERROR 0001. FILE WAS FOUND IN THE MIDDLE OF A FILE PATH INSTEAD OF A FOLDER.");
            return 0;
        }

        if (lastTime) return currentCluster;
        ptr = position - filename;
    }

    return currentCluster;
}

uint64_t getFileTableEntryByteFromClusterStart(char* filename, uint64_t clusterstart)
{
    uint64_t byteAddress = clusterstart * CLUSTER_SIZE;
    uint64_t hash = createHash(filename);

    uint8_t* data = 0;
    uint64_t lastTime = 0;

    while (1) {
        //only reload data if it was different than last time
        if (byteAddress / CLUSTER_SIZE != lastTime) {
            data = readCluster(byteAddress / CLUSTER_SIZE);
            lastTime = byteAddress / CLUSTER_SIZE;
        }

        uint64_t dataHash = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE));
        uint64_t left = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
        uint64_t right = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));
        uint64_t dloc = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24));

        bool dir = dloc & ((uint64_t) 0x8000000000000000);

        if (dir) {
            dloc += ((uint64_t) 0x8000000000000000);
        }

        if (hash > dataHash) {
            byteAddress = right;

        } else if (hash < dataHash) {
            byteAddress = left;

        } else {
            free(data);
            return byteAddress;
        }

        if (!byteAddress) {      //if it is zero and we haven't matched, the file doesn't exist
            puts("NO FILE");
            return FILEERR_NOFILE;
        }
    }
}

//! currently, this allows files to be used as folders...
uint64_t getFileTableEntryByte(char* filename)
{
    int64_t ptr = 0;
    bool lastTime = false;
    char entry[256];
    uint64_t currentCluster = ROOT_CLUSTER;

    while (1) {
        if (filename[ptr + 1] == ':') {         //! ensure this is only called the first time by using ptr+1 instead of 1
            ptr = 2;
        }
        if (filename[ptr] == '/') {
            ++ptr;
        }
        if (ptr >= strlen(filename)) {
            return currentCluster;
        }

        char* position = strchr(filename + ptr, '/');
        if (position == 0) {
            lastTime = true;
        }
        position += 1;

        memset(entry, 0, 256);
        strcat(entry, filename + ptr);
        char* v = strchr(entry, '/');
        if (v) *v = 0;

        //! LOOK FOR 'FOLDER' IN THE ROOT DIR -> gives us the folder's data entry

        currentCluster = getFileTableEntryByteFromClusterStart(entry, currentCluster);

        FILEINFO ag;
        memcpy(&ag, readCluster(currentCluster), sizeof(ag));

        if (ag.attributes.directory) {
            currentCluster = ag.startingCluster;
        } else if (!lastTime) {
            puts("POSSIBLE ERROR 0001. FILE WAS FOUND IN THE MIDDLE OF A FILE PATH INSTEAD OF A FOLDER.");
            return 0;
        }

        if (lastTime) return currentCluster;
        ptr = position - filename;
    }

    return currentCluster;
}

uint64_t findLocationOfMinNodeStartingAt(uint64_t startPoint, uint64_t lowest)
{
    static uint64_t lastTimeCluster = 0;
    static uint8_t* data = 0;

    // only load new data if the cluster is different from last time
    if (startPoint / CLUSTER_SIZE != lastTimeCluster) {
        data = readCluster(startPoint / CLUSTER_SIZE);
    }

    uint64_t dataHash = *((uint64_t*) (data + startPoint % CLUSTER_SIZE));
    uint64_t left = *((uint64_t*) (data + startPoint % CLUSTER_SIZE + 8));

    lastTimeCluster = startPoint / CLUSTER_SIZE;

    free(data);

    if (!left) {
        return lowest;
    } else {
        lowest = dataHash < lowest ? dataHash : lowest;
        return findLocationOfMinNodeStartingAt(left, lowest);
    }
}

uint64_t clearFileEntryFromClusterStart(char* filename, uint64_t startingCluster)
{
    uint64_t byteAddress = startingCluster * CLUSTER_SIZE;
    uint64_t hash = createHash(filename);

    uint8_t* data = 0;
    uint64_t lastTime = 0;

    while (1) {
        //only reload data if it was different than last time
        if (byteAddress / CLUSTER_SIZE != lastTime) {
            data = readCluster(byteAddress / CLUSTER_SIZE);
            lastTime = byteAddress / CLUSTER_SIZE;
        }

        uint64_t dataHash = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE));
        uint64_t left = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
        uint64_t right = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));
        uint64_t dloc = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24));

        bool dir = dloc & ((uint64_t) 0x8000000000000000);

        if (dir) {
            dloc += ((uint64_t) 0x8000000000000000);
        }

        if (hash > dataHash) {
            byteAddress = right;

        } else if (hash < dataHash) {
            byteAddress = left;

        } else {
            if (!(left | right)) {      //no children
                puts("DELETING NODE - NO CHILDREN");
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE)) = 0;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8)) = 0;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)) = 0;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24)) = 0;
                writeCluster(byteAddress / CLUSTER_SIZE, data);

            } else if (left) {  //one child
                puts("DELETING NODE - LEFT CHILD");
                uint64_t vv = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8));
                uint8_t* xx = readCluster(vv / CLUSTER_SIZE);        //LEFT
                uint8_t* originalxx = xx;

                xx += vv % CLUSTER_SIZE;

                uint64_t CHILD_dataHash = *((uint64_t*) (xx));
                uint64_t CHILD_left = *((uint64_t*) (xx + 8));
                uint64_t CHILD_right = *((uint64_t*) (xx + 16));
                uint64_t CHILD_dloc = *((uint64_t*) (xx + 24));

                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE)) = CHILD_dataHash;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8)) = CHILD_left;          //L
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)) = CHILD_right;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24)) = CHILD_dloc;

                // both the parent and child may be in the same cluster
                if (byteAddress / CLUSTER_SIZE == vv / CLUSTER_SIZE) {
                    *((uint64_t*) (data + vv % CLUSTER_SIZE)) = 0;
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 8)) = 0;          //L
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 16)) = 0;
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 24)) = 0;

                } else {
                    *((uint64_t*) (xx)) = 0;
                    *((uint64_t*) (xx + 8)) = 0;          //L
                    *((uint64_t*) (xx + 16)) = 0;
                    *((uint64_t*) (xx + 24)) = 0;
                }

                writeCluster(byteAddress / CLUSTER_SIZE, data);

                // both the parent and child may be in the same cluster
                if (byteAddress / CLUSTER_SIZE != vv / CLUSTER_SIZE) {
                    writeCluster(vv / CLUSTER_SIZE, originalxx);

                    data = readCluster(vv / CLUSTER_SIZE);
                    bool notClear = false;
                    for (int i = 0; i < CLUSTER_SIZE; ++i) {
                        if (data[i]) {
                            notClear = true;
                            break;
                        }
                    }
                    if (!notClear) {
                        //no more remain, so free it
                        setSpaceAtLocation(vv / CLUSTER_SIZE, false);
                    }
                }

                free(originalxx);

            } else if (right) {  //one child
                puts("DELETING NODE - RIGHT CHILD");
                uint64_t vv = *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16));
                uint8_t* xx = readCluster(vv / CLUSTER_SIZE);        //LEFT
                uint8_t* originalxx = xx;

                xx += vv % CLUSTER_SIZE;

                uint64_t CHILD_dataHash = *((uint64_t*) (xx));
                uint64_t CHILD_left = *((uint64_t*) (xx + 8));
                uint64_t CHILD_right = *((uint64_t*) (xx + 16));
                uint64_t CHILD_dloc = *((uint64_t*) (xx + 24));

                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE)) = CHILD_dataHash;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 8)) = CHILD_left;          //L
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)) = CHILD_right;
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 24)) = CHILD_dloc;

                // both the parent and child may be in the same cluster
                if (byteAddress / CLUSTER_SIZE == vv / CLUSTER_SIZE) {
                    *((uint64_t*) (data + vv % CLUSTER_SIZE)) = 0;
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 8)) = 0;          //L
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 16)) = 0;
                    *((uint64_t*) (data + vv % CLUSTER_SIZE + 24)) = 0;

                } else {
                    *((uint64_t*) (xx)) = 0;
                    *((uint64_t*) (xx + 8)) = 0;          //L
                    *((uint64_t*) (xx + 16)) = 0;
                    *((uint64_t*) (xx + 24)) = 0;
                }

                writeCluster(byteAddress / CLUSTER_SIZE, data);

                // both the parent and child may be in the same cluster
                if (byteAddress / CLUSTER_SIZE != vv / CLUSTER_SIZE) {
                    writeCluster(vv / CLUSTER_SIZE, originalxx);

                    data = readCluster(vv / CLUSTER_SIZE);
                    bool notClear = false;
                    for (int i = 0; i < CLUSTER_SIZE; ++i) {
                        if (data[i]) {
                            notClear = true;
                            break;
                        }
                    }
                    if (!notClear) {
                        //no more remain, so free it
                        setSpaceAtLocation(vv / CLUSTER_SIZE, false);
                    }
                }

                free(originalxx);

            } else {                    //two children
                puts("DELETING NODE - TWO CHILDREN");

                //! NOT TESTED. MAY NOT WORK WHEN PARENT+CHILD ARE IN THE SAME CLUSTER

                // returns the start of the 32 byte entry, but that is the min value anyway
                // + 16 gives the 'right side' pointer
                uint64_t locationOfMinValue = \
                    findLocationOfMinNodeStartingAt(*((uint64_t*) (data + byteAddress % CLUSTER_SIZE + 16)), 0xFFFFFFFFFFFFFFFF);

                uint64_t* d6 = (uint64_t*) readCluster(locationOfMinValue / CLUSTER_SIZE);
                uint64_t minval = d6[(locationOfMinValue % CLUSTER_SIZE) / 8];
                *((uint64_t*) (data + byteAddress % CLUSTER_SIZE)) = minval;

                if (minval / CLUSTER_SIZE == byteAddress / CLUSTER_SIZE) {
                    uint64_t* d7 = (uint64_t*) data;
                    d7[(locationOfMinValue % CLUSTER_SIZE) / 8 + 0] = 0;        //clear value (the minimum)
                    d7[(locationOfMinValue % CLUSTER_SIZE) / 8 + 1] = 0;        //clear left side of the above
                    d7[(locationOfMinValue % CLUSTER_SIZE) / 8 + 2] = 0;        //clear right side of the above
                    d7[(locationOfMinValue % CLUSTER_SIZE) / 8 + 3] = 0;        //clear pointer to the info cluster
                } else {
                    d6[(locationOfMinValue % CLUSTER_SIZE) / 8 + 0] = 0;        //clear value (the minimum)
                    d6[(locationOfMinValue % CLUSTER_SIZE) / 8 + 1] = 0;        //clear left side of the above
                    d6[(locationOfMinValue % CLUSTER_SIZE) / 8 + 2] = 0;        //clear right side of the above
                    d6[(locationOfMinValue % CLUSTER_SIZE) / 8 + 3] = 0;        //clear pointer to the info cluster

                    writeCluster(locationOfMinValue / CLUSTER_SIZE, (uint8_t*) d6);
                    data = readCluster(locationOfMinValue / CLUSTER_SIZE);
                    bool notClear = false;
                    for (int i = 0; i < CLUSTER_SIZE; ++i) {
                        if (data[i]) {
                            notClear = true;
                            break;
                        }
                    }
                    if (!notClear) {
                        //no more remain, so free it
                        setSpaceAtLocation(locationOfMinValue / CLUSTER_SIZE, false);
                    }
                }

                writeCluster(byteAddress / CLUSTER_SIZE, data);
                free(d6);
            }

            data = readCluster(byteAddress / CLUSTER_SIZE);
            bool notClear = false;
            for (int i = 0; i < CLUSTER_SIZE; ++i) {
                if (data[i]) {
                    notClear = true;
                    break;
                }
            }
            if (!notClear) {
                //no more remain, so free it
                setSpaceAtLocation(byteAddress / CLUSTER_SIZE, false);
            }
            free(data);

            return 0;
        }

        if (!byteAddress) {      //if it is zero and we haven't matched, the file doesn't exist
            puts("NO FILE");
            return FILEERR_NOFILE;
        }
    }
}


//! currently, this allows files to be used as folders...
void clearFileEntry(char* filename)
{
    char directoryn[256];
    memset(directoryn, 0, 256);
    strcpy(directoryn, filename);
    char* v = strrchr(directoryn, '/');
    bool inroot = true;
    if (v) {
        *v = 0;
        inroot = false;
    }

    uint64_t directoryStartCluster = inroot ? ROOT_CLUSTER : getFileStartPoint(directoryn);
    char* fkname = strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename;

    clearFileEntryFromClusterStart(fkname, directoryStartCluster);
}


//-----------------------------------------------------------------------------
// MurmurHash2, 64-bit versions, by Austin Appleby

// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.
// 64-bit hash for 64-bit platforms

// RELEASED UNDER THE MIT LICENSE

uint64_t MurmurHash64A(const void* key, int len, unsigned int seed)
{
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t* data = (const uint64_t*) key;
    const uint64_t* end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char* data2 = (const unsigned char*) data;

    switch (len & 7) {
    case 7: h ^= (uint64_t) (data2[6]) << 48;
    case 6: h ^= (uint64_t) (data2[5]) << 40;
    case 5: h ^= (uint64_t) (data2[4]) << 32;
    case 4: h ^= (uint64_t) (data2[3]) << 24;
    case 3: h ^= (uint64_t) (data2[2]) << 16;
    case 2: h ^= (uint64_t) (data2[1]) << 8;
    case 1: h ^= (uint64_t) (data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}


// 64-bit hash for 32-bit platforms

uint64_t MurmurHash64B(const void* key, int len, unsigned int seed)
{
    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    unsigned int h1 = seed ^ len;
    unsigned int h2 = 0;

    const unsigned int* data = (const unsigned int*) key;

    while (len >= 8) {
        unsigned int k1 = *data++;
        k1 *= m; k1 ^= k1 >> r; k1 *= m;
        h1 *= m; h1 ^= k1;
        len -= 4;

        unsigned int k2 = *data++;
        k2 *= m; k2 ^= k2 >> r; k2 *= m;
        h2 *= m; h2 ^= k2;
        len -= 4;
    }

    if (len >= 4) {
        unsigned int k1 = *data++;
        k1 *= m; k1 ^= k1 >> r; k1 *= m;
        h1 *= m; h1 ^= k1;
        len -= 4;
    }

    switch (len) {
    case 3: h2 ^= ((unsigned char*) data)[2] << 16;
    case 2: h2 ^= ((unsigned char*) data)[1] << 8;
    case 1: h2 ^= ((unsigned char*) data)[0];
        h2 *= m;
    };

    h1 ^= h2 >> 18; h1 *= m;
    h2 ^= h1 >> 22; h2 *= m;
    h1 ^= h2 >> 17; h1 *= m;
    h2 ^= h1 >> 19; h2 *= m;

    uint64_t h = h1;

    h = (h << 32) | h2;

    return h;
}
