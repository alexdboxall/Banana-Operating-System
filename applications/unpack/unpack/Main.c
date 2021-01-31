
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "D:/Users/Alex/Desktop/Banana/kernel/core/syscalls.hpp"

#include "miniz.h"

typedef struct FileHeader
{
    //before this comes the filename

    uint32_t currentLength : 28;
    uint32_t hidden : 1;
    uint32_t system : 1;
    uint32_t readonly : 1;
    uint32_t compressed: 1;
    
    uint32_t checksum;

} FileHeader;

#define COPYSIZE 65536 * 6
char rawdatabuffer[COPYSIZE];

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Invalid number of arguments.\nExpected:\n    unpack.exe source.cab destination\n");
        return 0;
    }

    char* src = argv[1];
    char* dest = argv[2];

    FILE* f = fopen(src, "rb");
    if (!f) {
        printf("Could not open source file.\n");
        return 1;
    }
    fseek(f, 0L, SEEK_END);
    long filelength = ftell(f);
    rewind(f);

    char sig[5];
    memset(sig, 0, 5);
    fread(sig, 4, 1, f);
    if (strcmp(sig, "BCAB")) {
        printf("Not a valid cabinet file.\n");
        return 1;
    }

    char moresig[3];
    fread(moresig, 3, 1, f);

    uint8_t version = moresig[0];

    int makeDirStatus = mkdir(dest, 0700);
    if (makeDirStatus) {
        printf("Could not create output directory.\n");
        return 1;
    }
    
    int fail = chdir(dest);
    if (fail) {
        printf("Could not open directory.\n");
        return 1;
    }

    int depth = 0;
    while (1) {
        long pos = ftell(f);

        uint8_t c = fgetc(f);
        if (c == 0x00) {
            break;

        } else if (c == 0xFB) {
            //create file
            char name[256];
            memset(name, 0, 256);
            fread(name, fgetc(f), 1, f);

            int chars = printf("\r %2d%%    %s", pos * 100 / filelength, name);
            int x = 74 - chars;
            if (x < 0) x = 0;
            for (int i = 0; i < x; ++i) {
                putchar(' ');
            }
            fflush(stdout);

            FileHeader header;
            fread(&header, sizeof(header), 1, f);

            if (header.compressed) {
                // High level decompression functions :
                // tinfl_decompress_mem_to_heap() decompresses a block in memory to a heap block allocated via malloc().
                // On entry:
                //  pSrc_buf, src_buf_len: Pointer and size of the Deflate or zlib source data to decompress.
                // On return:
                //  Function returns a pointer to the decompressed data, or NULL on failure.
                //  *pOut_len will be set to the decompressed data's size, which could be larger than src_buf_len on uncompressible data.
                //  The caller must call mz_free() on the returned block when it's no longer needed.
                //

                void* compressed = malloc(header.currentLength);
                fread(compressed, header.currentLength, 1, f);

                size_t rawLength;
                void* raw = tinfl_decompress_mem_to_heap(compressed, header.currentLength, &rawLength, TINFL_FLAG_PARSE_ZLIB_HEADER);

                FILE* o = fopen(name, "wb");
                fwrite(raw, rawLength, 1, o);
                fclose(o);

                mz_free(raw);
                free(compressed);

            } else {
                int sizeleft = header.currentLength;

                FILE* dest = fopen(name, "wb");
                if (!dest) {
                    printf("\nCould not create file.\n");
                    fclose(f);
                    return 1;
                }

                while (1) {
                    int actualcopysize = sizeleft;
                    if (sizeleft > COPYSIZE) {
                        actualcopysize = COPYSIZE;
                    }

                    int read = fread(rawdatabuffer, 1, actualcopysize, f);
                    int written = fwrite(rawdatabuffer, 1, actualcopysize, dest);
                    if (read != written) {
                        printf("\nCould not write to file.\n");
                        fclose(dest);
                        fclose(f);
                        return 1;
                    }

                    sizeleft -= actualcopysize;

                    if (!sizeleft) {
                        break;
                    }
                }

                fclose(dest);

                if (header.hidden || header.system || header.readonly) {
                    int clear = 0xF;
                    int set = (header.hidden ? 8 : 0) | (header.system ? 4 : 0) | (header.readonly ? 1 : 0);

                    extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
                    int res = SystemCall(SetFATAttrib, 0, clear | (set << 8), (size_t) name);
                    if (res) {
                        printf("\nCould not set attributes.\n");
                        fclose(f);
                        return 1;
                    }
                }
            }

        } else if (c >= 0xFC && c <= 0xFF) {
            uint8_t levels = 1;
            if (c == 0xFE) levels = 2;
            if (c == 0xFD) levels = 4;
            if (c == 0xFC) levels = 8;

            while (levels--) {
                if (depth == 0) {
                    if (fgetc(f) == 0x00) {
                        goto end;
                    }
                    printf("\nInvalid directory table.\n");
                    fclose(f);
                    return 1;
                }
                int fail = chdir("..");
                if (fail) {
                    printf("\nCould not open directory.\n");
                    fclose(f);
                    return 1;
                }
                --depth;
            }

        } else {
            char buffer[256];
            memset(buffer, 0, 256);
            fread(buffer, c, 1, f);

            int fail = mkdir(buffer, 0700);
            if (fail) {
                fclose(f);
                printf("\nCould not create directory.\n");
                return 1;
            }
            fail = chdir(buffer);
            if (fail) {
                fclose(f);
                printf("\nCould not open directory.\n");
                return 1;
            }
            depth++;
        }
    }

end:

    printf("\r100%%    The cabinet has been unpacked.                                         \n");
    fclose(f);

    return 0;
}
