/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
//#pragma GCC optimize ("Os")

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

extern int fatToVFSRemaps[10];

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

extern int fatWrapperReadDisk(BYTE vfsDisk,		/* Physical drive nmuber to identify the drive */
							  BYTE* buff,		/* Data buffer to store read data */
							  LBA_t sector,	/* Start sector in LBA */
							  UINT count		/* Number of sectors to read */);
extern int fatWrapperWriteDisk(BYTE vfsDisk,		/* Physical drive nmuber to identify the drive */
							  BYTE* buff,		/* Data buffer to store read data */
							  LBA_t sector,	/* Start sector in LBA */
							  UINT count		/* Number of sectors to read */);
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	return fatWrapperReadDisk(fatToVFSRemaps[pdrv], buff, sector, count);
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	return fatWrapperWriteDisk(fatToVFSRemaps[pdrv], (BYTE*) buff, sector, count);
}

#endif


extern DRESULT fatWrapperIoctl(
	BYTE vfsdisk,
	BYTE cmd,
	void* buff
);

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return fatWrapperIoctl(fatToVFSRemaps[pdrv], cmd, buff);
}

