//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NTextFormatter_hpp
#define NTextFormatter_hpp

#include <stdint.h>

extern "C" {
#define SSFN_VERSION 0x0200

#ifdef  __cplusplus
    extern "C" {
# ifndef __THROW
#  define __THROW throw()
# endif
#else
# ifndef __THROW
#  define __THROW
# endif
#endif
    /* if stdint.h was not included before us */
#ifndef _STDINT_H
    typedef unsigned char       uint8_t;
    typedef unsigned short int  uint16_t;
    typedef short int           int16_t;
    typedef unsigned int        uint32_t;
#ifndef _UINT64_T
    typedef unsigned long int   uint64_t;
#endif
#endif

    /***** file format *****/

    /* magic bytes */
#define SSFN_MAGIC "SFN2"
#define SSFN_COLLECTION "SFNC"
#define SSFN_ENDMAGIC "2NFS"

/* ligatures area */
#define SSFN_LIG_FIRST          0xF000
#define SSFN_LIG_LAST           0xF8FF

/* font family group in font type byte */
#define SSFN_TYPE_FAMILY(x)     ((x)&15)
#define SSFN_FAMILY_SERIF       0
#define SSFN_FAMILY_SANS        1
#define SSFN_FAMILY_DECOR       2
#define SSFN_FAMILY_MONOSPACE   3
#define SSFN_FAMILY_HAND        4

/* font style flags in font type byte */
#define SSFN_TYPE_STYLE(x)      (((x)>>4)&15)
#define SSFN_STYLE_REGULAR      0
#define SSFN_STYLE_BOLD         1
#define SSFN_STYLE_ITALIC       2
#define SSFN_STYLE_USRDEF1      4       /* user defined variant 1 */
#define SSFN_STYLE_USRDEF2      8       /* user defined variant 2 */

/* contour commands */
#define SSFN_CONTOUR_MOVE       0
#define SSFN_CONTOUR_LINE       1
#define SSFN_CONTOUR_QUAD       2
#define SSFN_CONTOUR_CUBIC      3

/* glyph fragments, kerning groups and hinting grid info */
#define SSFN_FRAG_CONTOUR       0
#define SSFN_FRAG_BITMAP        1
#define SSFN_FRAG_PIXMAP        2
#define SSFN_FRAG_KERNING       3
#define SSFN_FRAG_HINTING       4

/* main SSFN header, 32 bytes */
#ifndef _MSC_VER
#define _pack __attribute__((packed))
#else
#define _pack
#pragma pack(push)
#pragma pack(1)
#endif
    typedef struct
    {
        uint8_t     magic[4];               /* SSFN magic bytes */
        uint32_t    size;                   /* total size in bytes */
        uint8_t     type;                   /* font family and style */
        uint8_t     features;               /* format features and revision */
        uint8_t     width;                  /* overall width of the font */
        uint8_t     height;                 /* overall height of the font */
        uint8_t     baseline;               /* horizontal baseline in grid pixels */
        uint8_t     underline;              /* position of under line in grid pixels */
        uint16_t    fragments_offs;         /* offset of fragments table */
        uint32_t    characters_offs;        /* characters table offset */
        uint32_t    ligature_offs;          /* ligatures table offset */
        uint32_t    kerning_offs;           /* kerning table offset */
        uint32_t    cmap_offs;              /* color map offset */
    } _pack ssfn_font_t;
#ifdef _MSC_VER
#pragma pack(pop)
#endif

    /***** renderer API *****/
#define SSFN_FAMILY_ANY      0xff       /* select the first loaded font */
#define SSFN_FAMILY_BYNAME   0xfe       /* select font by its unique name */

/* additional styles not stored in fonts */
#define SSFN_STYLE_UNDERLINE   16       /* under line glyph */
#define SSFN_STYLE_STHROUGH    32       /* strike through glyph */
#define SSFN_STYLE_NOAA        64       /* no anti-aliasing */
#define SSFN_STYLE_NOKERN     128       /* no kerning */
#define SSFN_STYLE_NODEFGLYPH 256       /* don't draw default glyph */
#define SSFN_STYLE_NOCACHE    512       /* don't cache rasterized glyph */
#define SSFN_STYLE_NOHINTING 1024       /* no auto hinting grid (not used as of now) */
#define SSFN_STYLE_RTL       2048       /* render right-to-left */
#define SSFN_STYLE_ABS_SIZE  4096       /* scale absoulte height */

/* error codes */
#define SSFN_OK                 0       /* success */
#define SSFN_ERR_ALLOC         -1       /* allocation error */
#define SSFN_ERR_BADFILE       -2       /* bad SSFN file format */
#define SSFN_ERR_NOFACE        -3       /* no font face selected */
#define SSFN_ERR_INVINP        -4       /* invalid input */
#define SSFN_ERR_BADSTYLE      -5       /* bad style */
#define SSFN_ERR_BADSIZE       -6       /* bad size */
#define SSFN_ERR_NOGLYPH       -7       /* glyph (or kerning info) not found */

#define SSFN_SIZE_MAX         192       /* biggest size we can render */
#define SSFN_ITALIC_DIV         4       /* italic angle divisor, glyph top side pushed width / this pixels */
#define SSFN_PREC               4       /* precision in bits */

/* destination frame buffer context */
    typedef struct
    {
        uint8_t* ptr;                       /* pointer to the buffer */
        int16_t w;                          /* width (positive: ARGB, negative: ABGR pixels) */
        int16_t h;                          /* height */
        uint16_t p;                         /* pitch, bytes per line */
        int16_t x;                          /* cursor x */
        int16_t y;                          /* cursor y */
        uint32_t fg;                        /* foreground color */
        uint32_t bg;                        /* background color */
    } ssfn_buf_t;

    /* cached bitmap struct */
#define SSFN_DATA_MAX       ((SSFN_SIZE_MAX + 4 + (SSFN_SIZE_MAX + 4) / SSFN_ITALIC_DIV) << 8)
    typedef struct
    {
        uint16_t p;                         /* data buffer pitch, bytes per line */
        uint8_t h;                          /* data buffer height */
        uint8_t o;                          /* overlap of glyph, scaled to size */
        uint8_t x;                          /* advance x, scaled to size */
        uint8_t y;                          /* advance y, scaled to size */
        uint8_t a;                          /* ascender, scaled to size */
        uint8_t d;                          /* descender, scaled to size */
        uint8_t data[SSFN_DATA_MAX];        /* data buffer */
    } ssfn_glyph_t;

    /* character metrics */
    typedef struct
    {
        uint8_t t;                          /* type and overlap */
        uint8_t n;                          /* number of fragments */
        uint8_t w;                          /* width */
        uint8_t h;                          /* height */
        uint8_t x;                          /* advance x */
        uint8_t y;                          /* advance y */
    } ssfn_chr_t;

#ifdef SSFN_PROFILING
#include <string.h>
#include <sys/time.h>
#endif

    /* renderer context */
    typedef struct
    {
#ifdef SSFN_MAXLINES
        const ssfn_font_t* fnt[5][16];      /* static font registry */
#else
        const ssfn_font_t** fnt[5];         /* dynamic font registry */
#endif
        const ssfn_font_t* s;               /* explicitly selected font */
        const ssfn_font_t* f;               /* font selected by best match */
        ssfn_glyph_t ga;                    /* glyph sketch area */
        ssfn_glyph_t* g;                    /* current glyph pointer */
#ifdef SSFN_MAXLINES
        uint16_t p[SSFN_MAXLINES * 2];
#else
        ssfn_glyph_t*** c[17];              /* glyph cache */
        uint16_t* p;
        char** bufs;                        /* allocated extra buffers */
#endif
        ssfn_chr_t* rc;                     /* pointer to current character */
        int numbuf, lenbuf, np, ap, ox, oy, ax;
        int mx, my, lx, ly;                 /* move to coordinates, last coordinates */
        int len[5];                         /* number of fonts in registry */
        int family;                         /* required family */
        int style;                          /* required style */
        int size;                           /* required size */
        int line;                           /* calculate line height */
#ifdef SSFN_PROFILING
        uint64_t lookup, raster, blit, kern;/* profiling accumulators */
#endif
    } ssfn_t;
    }

}

#include "NRegion.hpp"

struct NFont
{
	ssfn_t ctx;

public:
	NFont();
	int loadFont(const char* filename);

	int setFont(int size, int style);
	int getBBox(const char* str, int* w, int* h, int* base);
	int render(const char* text, int x, int y, NRegion* rgn);
};

#endif