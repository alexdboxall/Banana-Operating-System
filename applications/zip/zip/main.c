
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include "zip.h"
#include <assert.h>
#include <ctype.h>

int zip_walk(int ogpathlength, struct zip_t *zip, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char fullpath[MAX_PATH];
    struct stat s;

    
    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    if (!dir) {
        return 1;
    }
    assert(dir);

    while ((entry = readdir(dir))) {
      // skip "." and ".."
      if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
        continue;

      snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

      stat(fullpath, &s);
      if (S_ISDIR(s.st_mode))
        return zip_walk(ogpathlength, zip, fullpath);
      else {
          int res = zip_entry_open(zip, fullpath + ogpathlength);
          if (res) {
              return res;
          }
          res = zip_entry_fwrite(zip, fullpath);
          if (res) {
              return res;
          }
          res = zip_entry_close(zip);
          if (res) {
              return res;
          }
      }
    }

    closedir(dir);
    return 0;
}

int main(int argc, char * argv[]) {
    if (argc < 3) {
    argerror:
        fprintf(stderr, "Not enough arguments specified.\n");
    othererror:
        fprintf(stderr, "\nUsage: zip compress filename foldername   - compress a folder\n");
        fprintf(stderr, "       zip compressa filename foldername  - compress with absolute paths\n");
        fprintf(stderr, "       zip decompress filename foldername - decompress a zip file\n");
        fprintf(stderr, "       zip create filename filenames...   - create from a list of files\n");
        fprintf(stderr, "       zip append filename filenames...   - append files to existing zip file\n");
        fprintf(stderr, "       zip delete filename filenames...   - append files to existing zip file\n");
        fprintf(stderr, "       zip list filename                  - list contents of zip file\n");
        fprintf(stderr, "       zip createn file [file alias]...   - create from files and alt. names\n");
        fprintf(stderr, "       zip appendn file [file alias]...   - append files using alt. names\n");
        fprintf(stderr, "       zip *5 [other command...]          - set compression level (0 - 9)\n");

        fprintf(stderr, "\n");
        return 0;
    }
    
    int compression_level = ZIP_DEFAULT_COMPRESSION_LEVEL;
    
    if (argv[1][0] == '*' && isdigit(argv[1][1]) && strlen(argv[1]) == 2) {
        compression_level = argv[1][1] - '0';
        argc--;
        argv++;
    }
    
    if (!strcmp(argv[1], "compress")) {
        if (argc < 4) goto argerror;
        if (argc > 4) {
            fprintf(stderr, "Too many arguments specified.\n");
            goto othererror;
        }
        struct zip_t *zip = zip_open(argv[2], compression_level, 'w');
        if (!zip) {
            fprintf(stderr, "Could not open output file.\n");
            return 0;
        }
        int fail = zip_walk((int) strlen(argv[3]), zip, argv[3]);
        if (fail) {
            fprintf(stderr, "Error compressing directory.\n");
            return 0;
        }
        zip_close(zip);
        
    } else if (!strcmp(argv[1], "compressa")) {
        if (argc < 4) goto argerror;
        if (argc > 4) {
            fprintf(stderr, "Too many arguments specified.\n");
            goto othererror;
        }
        struct zip_t *zip = zip_open(argv[2], compression_level, 'w');
        if (!zip) {
            fprintf(stderr, "Could not open output file.\n");
            return 0;
        }
        int fail = zip_walk(0, zip, argv[3]);
        if (fail) {
            fprintf(stderr, "Error compressing directory.\n");
            return 0;
        }
        zip_close(zip);

    } else if (!strcmp(argv[1], "create")) {
        if (argc < 4) goto argerror;

        struct zip_t *zip = zip_open(argv[2], compression_level, 'w');
        if (!zip) {
            fprintf(stderr, "Error opening file.\n");
            return 0;
        }
        {
            for (int i = 3; i < argc; ++i) {
                int fail = zip_entry_open(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                fail = zip_entry_fwrite(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                zip_entry_close(zip);
            }
        }
        zip_close(zip);
        
    } else if (!strcmp(argv[1], "createn")) {
        if (argc < 4) goto argerror;
        if (!(argc & 1)) {
            fprintf(stderr, "Mismatching number of arguments specified.\n");
            goto othererror;
        }
        struct zip_t *zip = zip_open(argv[2], compression_level, 'w');
        if (!zip) {
            fprintf(stderr, "Error opening file.\n");
            return 0;
        }
        {
            for (int i = 3; i < argc; i += 2) {
                int fail = zip_entry_open(zip, argv[i + 1]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                fail = zip_entry_fwrite(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                zip_entry_close(zip);
            }
        }
        zip_close(zip);
        
    } else if (!strcmp(argv[1], "append")) {
        if (argc < 4) goto argerror;

        struct zip_t *zip = zip_open(argv[2], compression_level, 'a');
        if (!zip) {
            fprintf(stderr, "Error opening file.\n");
            return 0;
        }
        {
            for (int i = 3; i < argc; ++i) {
                int fail = zip_entry_open(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                fail = zip_entry_fwrite(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                zip_entry_close(zip);
            }
        }
        zip_close(zip);
        
    } else if (!strcmp(argv[1], "appendn")) {
        if (argc < 4) goto argerror;
        if (!(argc & 1)) {
            fprintf(stderr, "Mismatching number of arguments specified.\n");
            goto othererror;
        }
        struct zip_t *zip = zip_open(argv[2], compression_level, 'a');
        if (!zip) {
            fprintf(stderr, "Error opening file.\n");
            return 0;
        }
        {
            for (int i = 3; i < argc; i += 2) {
                int fail = zip_entry_open(zip, argv[i + 1]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                fail = zip_entry_fwrite(zip, argv[i]);
                if (fail) {
                    fprintf(stderr, "Error compressing file.\n");
                    return 0;
                }
                zip_entry_close(zip);
            }
        }
        zip_close(zip);
        
    } else if (!strcmp(argv[1], "delete")) {
        
    } else if (!strcmp(argv[1], "decompress")) {
        
    } else if (!strcmp(argv[1], "list")) {
        if (argc > 4) {
            fprintf(stderr, "Too many arguments specified.\n");
            goto othererror;
        }
        
        struct zip_t *zip = zip_open(argv[2], 0, 'r');
        if (!zip) {
            fprintf(stderr, "Error opening file.\n");
            return 0;
        }
        int i, n = (int) zip_entries_total(zip);
        for (i = 0; i < n; ++i) {
            int fail = zip_entry_openbyindex(zip, i);
            if (fail) {
                fprintf(stderr, "Error iterating over file.\n");
                return 0;
            }
            {
                const char *name = zip_entry_name(zip);
                int isdir = zip_entry_isdir(zip);
                unsigned long long size = zip_entry_size(zip);

                printf("%s %12llu   %s\n", isdir ? "<DIR>" : "     ", size, name);
            }
            zip_entry_close(zip);
        }
        zip_close(zip);
        
    } else {
        fprintf(stderr, "Invalid command specified.\n\n");
        goto othererror;
        return 0;
    }
    
    return 0;
}
