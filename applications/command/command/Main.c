
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/banana.h>
#include "tinyexpr.h"

#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"

#define MAX_BATCH_RECURSION 12

#define VERSION_STRING "Banana 0.1.3"
char prompt[64] = "$P$G";

int errorLevel = 0;

#define MAX_DIR_STACK 20

typedef struct Label
{
	char* label;
	int line;
	bool used;

} Label;


void runBatchFile(char* filename, int batchNesting);

double mathVars[26];

int dirStackPtr = 0;
char* dirStackArray[MAX_DIR_STACK];
int errStackPtr = 0;
int errStackArray[MAX_DIR_STACK];

bool fileExists(char* filename)
{
	FILE* f = fopen(filename, "rb");
	if (!f) {
		return false;
	}
	fclose(f);
	return true;
}

void copytree(char* basePath, char* newPath)
{
	char* path = calloc(400, 1);
	char* npath = calloc(400, 1);

	struct dirent* dp;
	DIR* dir = opendir(basePath);

	if (!dir) return;

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);

			strcpy(npath, newPath);
			strcat(npath, "/");
			strcat(npath, dp->d_name);

			if (dp->d_type & DT_DIR) {
				int mres = mkdir(npath, 0700);
				if (mres != 0) {
					fprintf(stderr, "Directory %s could not be created.\n", npath);
				} else {
					copytree(path, npath);
				}

			} else {
				FILE* f = fopen(path, "rb");
				if (!f) {
					fprintf(stderr, "File %s could not be copied.\n", path);
					continue;
				}

				if (f) {
					FILE* dest = fopen(npath, "wb");
					if (!dest) {
						fprintf(stderr, "File %s could not be created.\n", npath);
						fclose(f);
						continue;
					}

					char* m = malloc(4096);
					if (!m) {
						fprintf(stderr, "Memory error!\n");
						free(path);
						free(npath);
						return;
					}
					while (1) {
						int red = fread(m, 1, 4096, f);
						fwrite(m, 1, red, dest);
						if (red != 4096) {
							break;
						}
					}
					free(m);

					fclose(f);
					fclose(dest);
				}
			}
		}
	}

	free(path);
	free(npath);

	closedir(dir);
}

char* getPossibleExecutableName(char* in)
{
	char* file = malloc(strlen(in) + 16);
	if (!file) {
		fprintf(stderr, "Memory error!\n");
		exit(-1);
	}
	strcpy(file, in);

	//first, check for the raw filename
	if (fileExists(file)) {
		return file;
	}

	//next, try with .exe on the end
	strcat(file, ".exe");
	if (fileExists(file)) {
		return file;
	}

	//return to the original
	strcpy(file, in);

	char* opath = getenv("PATH");
	char* path = malloc(strlen(opath) + 64);
	char* tok = path;
	char* end = path;
	strcpy(path, opath);

	while (tok != NULL) {
		strsep(&end, ";");

		char* new = malloc(strlen(tok) + strlen(file) + 8);
		if (!new) {
			printf("Memory error!\n");
			exit(-1);
		}
		strcpy(new, tok);
		strcat(new, "/");
		strcat(new, file);

		//check without .exe
		if (fileExists(new)) {
			free(file);
			return new;
		}

		strcat(new, ".exe");
		//check with .exe
		if (fileExists(new)) {
			free(file);
			return new;
		}

		free(new);

		tok = end;
	}

	free(path);
	return 0;
}


void delTree(char* basePath, int root)
{
	char path[1000];
	memset(path, 0, 1000);

	struct dirent* dp;
	DIR* dir = opendir(basePath);

	if (!dir) {
		fprintf(stderr, "Failed to open directory!\n");
		return;
	}

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			if (dp->d_type & DT_DIR) {
				delTree(path, root + 5);
			} else {
				strcpy(path, basePath);
				strcat(path, "/");
				strcat(path, dp->d_name);
				printf("Deleting %s... ", path);

				int x = remove(path);
				if (x == 0) {
					printf("Deleted\n");
				} else {
					printf("Access denied\n");
				}
			}
		}
	}

	printf("Deleting %s... ", basePath);
	int x = rmdir(basePath);
	if (x == 0) {
		printf("Deleted\n");
	} else {
		printf("Access denied\n");
	}

	closedir(dir);
}

void printCWD()
{
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s", cwd);
	} else {
		printf("Path no longer valid");
	}
}

char getCurrentDrive()
{
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	return cwd[0];
}

void displayPrompt()
{
	for (int i = 0; prompt[i]; ++i) {
		if (prompt[i] == '$') {
			++i;
			if (!prompt[i]) return;

			switch (prompt[i]) {
			case 'A':
			case 'a':
				putchar('&');
				break;
			case 'B':
			case 'b':
				putchar('|');
				break;
			case 'C':
			case 'c':
				putchar('(');
				break;
			case 'D':
			case 'd':
				printf("0/0/2020");
				break;
			case 'E':
			case 'e':
				putchar(27);
				break;
			case 'F':
			case 'f':
				putchar(')');
				break;
			case 'G':
			case 'g':
				putchar('>');
				break;
			case 'H':
			case 'h':
				putchar('\b');
				break;
			case 'L':
			case 'l':
				putchar('<');
				break;
			case 'N':
			case 'n':
				putchar(getCurrentDrive());
				break;
			case 'P':
			case 'p':
				printCWD();
				break;
			case 'Q':
			case 'q':
				putchar('=');
				break;
			case 'S':
			case 's':
				putchar(' ');
				break;
			case 'T':
			case 't':
				printf("24:00:00");
				break;
			case 'V':
			case 'v':
				printf(VERSION_STRING);
				break;
			case '_':
				putchar('\n');
				break;
			case '$':
				putchar('$');
				break;
			default:
				break;
			}

		} else {
			putchar(prompt[i]);
		}
	}

	fflush(stdout);
}

int dirsize(FILE* outfile, char* basePath, int level)
{
	char path[266];
	memset(path, 0, 266);

	struct dirent* dp;
	DIR* dir = opendir(basePath);

	if (!dir) return 0;

	int size = 0;

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			if (dp->d_type == DT_REG) {
				struct stat st;
				char* name = malloc(256);
				memset(name, 0, 256);
				strcpy(name, basePath);
				strcat(name, "/");
				strcat(name, dp->d_name);
				stat(name, &st);
				size += (st.st_size + 511) & ~511;
				free(name);

			} else {
				strcpy(path, basePath);
				strcat(path, "/");
				strcat(path, dp->d_name);

				char* name = malloc(256);
				strcpy(name, dp->d_name);
				int ds = dirsize(outfile, path, level + 1) + 512;
				size += ds;

				if (level == 0) {
					bool mb = false;
					ds = (ds + 4095) / 4096;
					fprintf(outfile, " %4d %cB    %s\n", ds, mb ? 'M' : 'K', name);
				}
				free(name);
			}
		}
	}

	closedir(dir);
	return size;
}

void tree(FILE* out, char* basePath, int root)
{
	char path[266];
	memset(path, 0, 266);

	struct dirent* dp;
	DIR* dir = opendir(basePath);

	if (!dir) return;

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			for (int i = 0; i < root; ++i) {
				if (i % 5 == 0 || i == 0) {
					fprintf(out, "%c", '|');
				} else {
					fprintf(out, " ");
				}
			}

			fprintf(out, "|----%s\n", dp->d_name);

			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			tree(out, path, root + 5);
		}
	}

	closedir(dir);
}

struct dirent* findNextMatch(DIR* dir, char* inputSpec, char* outbuffer)
{
	memset(outbuffer, 0, 256);

	char pathspec[280];
	memset(pathspec, 0, 280);

	if (inputSpec[0] == '.') {
		pathspec[0] = '*';
		strcpy(pathspec + 1, inputSpec);
	} else {
		strcpy(pathspec, inputSpec);
	}

	if (strlen(pathspec) > 2 && pathspec[strlen(pathspec) - 1] == '*' && pathspec[strlen(pathspec) - 2] == '.' && pathspec[strlen(pathspec) - 3] == '*') {
		pathspec[strlen(pathspec) - 1] = 0;
		pathspec[strlen(pathspec) - 1] = 0;
	}

	bool matchNoExt = pathspec[strlen(pathspec) - 1] == '.';
	if (matchNoExt) {
		pathspec[strlen(pathspec) - 1] = 0;
	}

	while (1) {
		struct dirent* ent;
		ent = readdir(dir);
		if (ent == NULL) {
			return NULL;
		}

		//skip '.' and '..'
		if (ent->d_name[0] == '.' && ent->d_name[1] == '.' && !ent->d_name[2]) continue;
		if (ent->d_name[0] == '.' && !ent->d_name[1]) continue;

		char expanded[280];
		memset(expanded, 0, 280);
		int i = 0;
		int j = 0;
		int k = 0;
		bool matched = true;

		while (pathspec[j]) {
			if (pathspec[j] == '*') {
				for (int l = k; l < ent->d_name[l]; ++l) {
					expanded[l] = '?';
				}
				while (ent->d_name[i] && ent->d_name[i] != '.') {
					expanded[k++] = ent->d_name[i++];
				}
				if (ent->d_name[i] == '.' && matchNoExt) {
					ent->d_name[0] = '/';       //stick an invalid character in and break
					break;
				}
				++j;
			} else if (pathspec[j] == '?' && ent->d_name[i] == '.') {
				++j;
			} else {
				expanded[k++] = pathspec[j++];
				++i;
			}
		}
		if (!j || pathspec[j - 1] != '*') expanded[k] = 0;
		for (int l = 0; ent->d_name[l]; ++l) {
			if (tolower(ent->d_name[l]) != tolower(expanded[l]) && expanded[l] != '?') {
				matched = false;
				break;
			}
		}
		if (!matched) continue;
		for (int l = (int) strlen(ent->d_name); expanded[l]; ++l) {
			if (expanded[l] != '?') {
				matched = false;
				break;
			}
		}
		if (!matched) continue;

		strcpy(outbuffer, ent->d_name);
		return ent;
	}
}

int parse(int argc, char* argv[], FILE* out, Label labels[64], int batchNesting)
{
	if (argc == 0) {
		return -9999999;
	}

	if (!strcasecmp(argv[0], "call")) {
		if (!argv[1] || !argv[1][0]) {
			fprintf(stderr, "Filename required for call statement.\n");
			return -1;
		}
		if (batchNesting >= MAX_BATCH_RECURSION) {
			fprintf(stderr, "Recursion limit reached.\n");
			return -1;
		}
		runBatchFile(argv[1], batchNesting + 1);

	} else if (!strcasecmp(argv[0], "goto")) {
		if (!argv[1] || !argv[1][0]) {
			fprintf(stderr, "Label required for goto statement.\n");
			return -1;
		}
		for (int i = 0; i < 64; ++i) {
			if (!labels[i].used || !labels[i].label[0]) {
				break;
			}
			if (!strcmp(labels[i].label, argv[1])) {
				return labels[i].line;
			}
		}
		fprintf(stderr, "The specified label could not be found.\n");
		return -2;

	} else if (!strcasecmp(argv[0], "prompt")) {
		if (argc == 1) {
			strcpy(prompt, "$P$G");
		} else if (argc >= 2) {
			strcpy(prompt, argv[1]);
			for (int i = 2; i < argc; ++i) {
				strcat(prompt, " ");
				strcat(prompt, argv[i]);
			}
		}

	} else if (!strcasecmp(argv[0], "dir")) {
		struct dirent* ent;
		DIR* dir;
		char dirname[256];
		memset(dirname, 0, 256);

		int lastSlash = 0;
		bool hasWC = false;
		bool nodir = false;

		if (argc == 1) {
			getcwd(dirname, 255);
		} else {
			char* olddir = malloc(256);
			getcwd(olddir, 255);

			bool requiredLastSlash = false;
			for (int i = 0; argv[1][i]; ++i) {
				if (argv[1][i] == '?' || argv[1][i] == '*') hasWC = true;
				if (argv[1][i] == '/' || argv[1][i] == '\\') {
					if (argv[1][i + 1]) {
						lastSlash = i + 1;
						if (hasWC) {
							fprintf(stderr, "Invalid wildcard usage.\n");
							return 1;
						}
					}
				}
			}

			char* halfdir = malloc(256);

			if (hasWC) {
				memset(halfdir, 0, 256);
				memcpy(halfdir, argv[1], lastSlash);
				if (!strlen(halfdir)) {
					strcpy(halfdir, olddir);
				}
				nodir = chdir(halfdir) != 0;

			} else {
				nodir = chdir(argv[1]) != 0;
			}

			getcwd(dirname, 255);
			free(halfdir);

			chdir(olddir);
			free(olddir);
		}

		if (nodir) {
			fprintf(stderr, "Directory not found.\n", dirname);
			return 1;
		}

		fprintf(out, " Directory of %s\n\n", dirname);

		if ((dir = opendir(dirname)) != NULL) {
			char* ob = malloc(256);

			int filecnt = 0;
			int dircnt = 0;

			while (1) {
				struct dirent* ent = findNextMatch(dir, hasWC ? (argv[1] + lastSlash) : "*", ob);
				if (!ent) break;

				struct stat st;
				char name[256];
				memset(name, 0, 255);
				strcpy(name, dirname);
				strcat(name, "/");
				strcat(name, ent->d_name);
				stat(name, &st);
				if (ent->d_type == DT_DIR) dircnt++;
				else filecnt++;
				fprintf(out, "%s %11lld %-48s \n", ent->d_type == DT_DIR ? "<DIR>" : "     ", st.st_size, ent->d_name);
			}

			closedir(dir);

			free(ob);
			fprintf(out, "\n    %d file(s)\n    %d dir(s)\n", filecnt, dircnt);

		} else {
			if (argc == 1) {
				fprintf(stderr, "The directory couldn't be opened.\n");
			} else {
				fprintf(stderr, "The directory specified could not be found, or couldn't be opened.\n");
			}
		}

	} else if (!strcasecmp(argv[0], "rmtree")) {
		char dirname[256];
		memset(dirname, 0, 256);
		if (argc == 1) {
			getcwd(dirname, 255);
		} else {
			strcpy(dirname, argv[1]);
		}

		char cwd[256];
		memset(cwd, 0, 256);
		getcwd(cwd, 255);

		printf("WARNING!\n");
		printf("Directory '%s' and ALL CONTENTS will be deleted.\n", dirname);
		printf("Files and directories CANNOT BE RECOVERED.\n");
		bool onCwd = false;
		if (argc == 1) {
			onCwd = true;
			printf("\n* THIS IS THE CURRENT DIRECTORY, NO ARGUMENT SUPPLIED *\n");
		}
		if (strlen(dirname) <= 3 && dirname[1] == ':') {
			printf("\n* THIS IS THE ROOT DIRECTORY, THIS WILL DELETE EVERYTHING * \n");
		}
		bool noAsk = argc == 3 && !strcmp(argv[2], "-s");
		if (!noAsk) printf("\nProceed? Y/n: ");

		char c = noAsk ? 'Y' : getchar();
		char oldC = c;
		if (!noAsk) {
			if (c != '\n' && c != EOF) while ((c = getchar()) != '\n' && c != EOF) {}
		}

		c = oldC;

		if (c == 'Y' || c == 'y') {
			if (strlen(dirname) <= 3 && dirname[1] == ':') {
				printf("THIS IS THE ROOT DIRECTORY, EVERYTHING WILL BE DELETED \n");
				printf("\nProceed? Y/n: ");
				char c = getchar();
				if (c == 'Y' || c == 'y') {
					printf("Uh oh...\n");

				} else {
					return -1;
				}
			}

			char resolvedname[300];
			realpath(dirname, resolvedname);

			delTree(resolvedname, 0);
			if (onCwd) {
				chdir("..");
			}
		}

	} else if (!strcasecmp(argv[0], "pause")) {
		printf("Press ENTER to continue... ");
		int c = getchar();
		if (c != '\n' && c != EOF) while ((c = getchar()) != '\n' && c != EOF) {}

	} else if (!strcasecmp(argv[0], "tree")) {
		char dirname[256];
		if (argc <= 1) {
			getcwd(dirname, 255);
		} else {
			strcpy(dirname, argv[1]);
		}
		fprintf(out, "%s\n", dirname);
		tree(out, dirname, 0);

	} else if (!strcasecmp(argv[0], "dirsize")) {
		char dirname[256];
		if (argc <= 1) {
			getcwd(dirname, 255);
		} else {
			strcpy(dirname, argv[1]);
		}
		int size = dirsize(out, dirname, 0);
		bool mb = false;
		size = (size + 4095) / 4096;
		if (size > 9999) {
			size = (size + 4095) / 4096;
			mb = true;
		}
		fprintf(out, "\nTotal size: %d %cB\n", size, mb ? 'M' : 'K');

	} else if (!strcasecmp(argv[0], "echo")) {
		for (int i = 1; i < argc; ++i) {
			fprintf(out, "%s", argv[i]);
			if (i != argc - 1) fprintf(out, " ");
		}
		printf("\n");

	} else if (!strcasecmp(argv[0], "resclink")) {
		extern int _bna_misc_size;
		printf("0x%X\n", _bna_misc_size);

		printf("0x%X\n", &_bna_misc_size);
		printf("%s\n", ((char*) &_bna_misc_size) - _bna_misc_size);

	} else if (!strcasecmp(argv[0], "cls") || !strcasecmp(argv[0], "clear")) {
		printf("\x1B[2J");

	} else if (!strcasecmp(argv[0], "ansi")) {
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

		printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
		printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
		printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
		printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
		printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
		printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");

	} else if (!strcasecmp(argv[0], "copytree")) {
		if (!argv[1] || !argv[1][0]) {
			fprintf(stderr, "Please enter a directory name to copy.\n");
			return -1;
		}
		if (!argv[2] || !argv[2][0]) {
			fprintf(stderr, "Please enter a destination path for the copied directory.\n");
			return -1;
		}

		int res = mkdir(argv[2], 0700);

		DIR* dest = opendir(argv[2]);
		if (!dest) {
			fprintf(stderr, "The destination directory could not be opened.\n");
			return -1;
		}
		closedir(dest);

		copytree(argv[1], argv[2]);
		printf("\n");

	} else if (!strcasecmp(argv[0], "copy") || !strcasecmp(argv[0], "cp")) {
		struct dirent* ent;
		DIR* dir;
		char dirname[256];
		memset(dirname, 0, 256);

		int lastSlash = 0;
		bool hasWC = false;
		bool actualHasWC = false;
		bool nodir = false;

		if (argc == 1) {
			fprintf(stderr, "Please enter a file or directory name to copy.\n");
			return -1;

		} else if (argc == 2) {
			fprintf(stderr, "Please enter a destination path for the copied file/directory.\n");
			return -1;

		} else {
			char* olddir = malloc(256);
			getcwd(olddir, 255);

			bool requiredLastSlash = false;
			for (int i = 0; argv[1][i]; ++i) {
				if (argv[1][i] == '?' || argv[1][i] == '*') hasWC = true;
				if (argv[1][i] == '/' || argv[1][i] == '\\') {
					if (argv[1][i + 1]) {
						lastSlash = i + 1;
						if (hasWC) {
							fprintf(stderr, "Invalid wildcard usage.\n");
							return 1;
						}
					}
				}
			}
			actualHasWC = hasWC;

			char* halfdir = malloc(256);

			if (hasWC) {
				memset(halfdir, 0, 256);
				memcpy(halfdir, argv[1], lastSlash);
				if (!strlen(halfdir)) {
					strcpy(halfdir, olddir);
				}
				nodir = chdir(halfdir) != 0;

			} else {
				hasWC = true;
				strcpy(halfdir, olddir);
				nodir = chdir(halfdir) != 0;
			}
			free(halfdir);

			getcwd(dirname, 255);

			chdir(olddir);
			if (chdir(argv[2]) && actualHasWC) {
				nodir = true;
			}
			chdir(olddir);
			free(olddir);
		}

		if (nodir) {
			fprintf(stderr, "Directory not found.\n", dirname);
			return 1;
		}

		if ((dir = opendir(dirname)) != NULL) {
			char* ob = malloc(256);

			while (1) {
				struct dirent* ent = findNextMatch(dir, hasWC ? (argv[1] + lastSlash) : "*", ob);
				if (!ent) break;

				struct stat st;
				char name[256];
				memset(name, 0, 255);
				strcpy(name, dirname);
				strcat(name, "/");
				strcat(name, ent->d_name);
				stat(name, &st);

				if (ent->d_type == DT_DIR) {
					continue;
				}

				char destpath[256];
				strcpy(destpath, argv[2]);
				if (actualHasWC) {
					strcat(destpath, "/");
					strcat(destpath, ent->d_name);
				}

				fprintf(out, "Copying %s to %s\n", name, destpath);

				FILE* f = fopen(name, "rb");
				FILE* dest = fopen(destpath, "wb");
				if (!dest) {
					free(ob);
					fprintf(stderr, "The destination file could not be opened.\n");
					return -1;
				}
				if (!f) {
					free(ob);
					fprintf(stderr, "The source file could not be opened.\n");
					return -1;
				}
				int copysize = 4096 * 16;
				char* m = malloc(copysize);
				if (!m) {
					fprintf(stderr, "Memory error!\n");
					free(ob);
					fclose(f);
					fclose(dest);
					return -2;
				}
				while (1) {
					int red = fread(m, 1, copysize, f);
					fwrite(m, 1, red, dest);
					if (red != copysize) {
						break;
					}
				}
				free(m);

				fclose(f);
				fclose(dest);
			}

			closedir(dir);
			free(ob);

		} else {
			fprintf(stderr, "The file(s) could not be copied.\n");
		}

	} else if (!strcasecmp(argv[0], "ver")) {
		fprintf(out, "%s\n", VERSION_STRING);

	} else if (!strcasecmp(argv[0], "rmdir")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter directory path to delete.\n");
			return -1;
		}

		int res = rmdir(argv[1]);
		if (res) {
			fprintf(stderr, "Error deleting directory.\nMaybe the directory isn't empty? Use rmtree to delete contents as well.\n");
		}

	} else if (!strcasecmp(argv[0], "eject")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter a drive name to eject.\n");
			return -1;
		}
		if (argc != 2) {
			fprintf(stderr, "Please only enter one drive name.\n");
			return -1;
		}
		if (strlen(argv[1]) > 3) {
			fprintf(stderr, "Not a drive.\n");
			return -1;
		}
		if (strlen(argv[1]) >= 2 && argv[1][1] != ':') {
			fprintf(stderr, "Not a drive.\n");
			return -1;
		}
		if (strlen(argv[1]) == 3 && argv[1][2] != '/' && argv[1][2] != '\\') {
			fprintf(stderr, "Not a drive.\n");
			return -1;
		}

		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		int res = SystemCall(Eject, argv[1][0], 0, 0);
		if (res == -1) {
			fprintf(stderr, "Not a removable drive.\n");
			return -1;
		} else if (res == -2) {
			fprintf(stderr, "Not a drive.\n");
			return -1;
		}  else if (res != 0) {
			fprintf(stderr, "The drive cannot eject the disk.\n");
			return -1;
		}

	} else if (!strcasecmp(argv[0], "mkdir") || !strcasecmp(argv[0], "md")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter directory path to create.\n");
			return -1;
		}

		struct stat st = { 0 };

		if (stat(argv[1], &st) == -1) {
			int res = mkdir(argv[1], 0700);
			if (res) {
				fprintf(stderr, "The directory could not be created.\n");
			}
		} else {
			fprintf(stderr, "Directory already exists.\n");
		}

	} else if (!strcasecmp(argv[0], "ttyname")) {
		char* x = ttyname(fileno(stdout));
		if (x) {
			fprintf(out, "%s\n", x);
		} else {
			fprintf(stderr, "Not a terminal.\n");
		}

	} else if (!strcasecmp(argv[0], "calc")) {
		char* joinedargs = malloc(512);
		memset(joinedargs, 0, 512);
		char var = 0;

		int i = 1;
		if (argc > 3) {
			if (!strcmp(argv[2], "=")) {
				i = 3;
				if (strlen(argv[1]) != 1) {
					fprintf(stderr, "Invalid variable name, can only be a single letter.\n");
					return -1;
				}
				var = tolower(argv[1][0]);
				if (!isalpha(var)) {
					fprintf(stderr, "Invalid variable name, can only be a single letter.\n");
					return -1;
				}
			}
		}
		if (!var && argc >= 2) {
			if (argv[1][1] == '=') {
				var = tolower(argv[1][0]);
				i = 2;
				if (!isalpha(var)) {
					fprintf(stderr, "Invalid variable name, can only be a single letter.\n");
					return -1;
				}
				if (strlen(argv[1]) > 2) {
					argv[1][0] = ' ';
					argv[1][1] = ' ';
					i = 1;
				}
			}
		}
		for (; i < argc; ++i) {
			strcat(joinedargs, argv[i]);
		}
		if (!var && strlen(joinedargs) >= 2 && joinedargs[1] == '=') {
			var = joinedargs[0];
			joinedargs[0] = ' ';
			joinedargs[1] = ' ';
		}

		te_variable vars[] = { 
			{"a", &mathVars[0]}, 
			{"b", &mathVars[1]}, 
			{"c", &mathVars[2]}, 
			{"d", &mathVars[3]}, 
			{"e", &mathVars[4]}, 
			{"f", &mathVars[5]}, 
			{"g", &mathVars[6]}, 
			{"h", &mathVars[7]}, 
			{"i", &mathVars[8]}, 
			{"j", &mathVars[9]}, 
			{"k", &mathVars[10]}, 
			{"l", &mathVars[11]}, 
			{"m", &mathVars[12]}, 
			{"n", &mathVars[13]}, 
			{"o", &mathVars[14]}, 
			{"p", &mathVars[15]}, 
			{"q", &mathVars[16]}, 
			{"r", &mathVars[17]}, 
			{"s", &mathVars[18]}, 
			{"t", &mathVars[19]}, 
			{"u", &mathVars[20]}, 
			{"v", &mathVars[21]}, 
			{"w", &mathVars[22]}, 
			{"x", &mathVars[23]}, 
			{"y", &mathVars[24]}, 
			{"z", &mathVars[25]}, 
		};

		/*int error = 0;
		double res = te_interp(joinedargs, &error);*/

		int error = 0;
		te_expr* n = te_compile(joinedargs, vars, 26, &error);

		if (n) {
			double res = te_eval(n);
			fprintf(out, "%g\n", res);
			if (var) {
				mathVars[var - 'a'] = res;
			}
			te_free(n);
		} else {
			fprintf(stderr, "Error: %s\n       %*s^\n", joinedargs, error - 1, "");
		}

		free(joinedargs);

	} else if (!strcasecmp(argv[0], "vol")) {
		char drive = 'C';

		if (argc == 2) {
			if (strlen(argv[1]) == 1) drive = argv[1][0];
			else if (strlen(argv[1]) == 2 && argv[1][1] == ':') drive = argv[1][0];
			else if (strlen(argv[1]) == 3 && argv[1][1] == ':' && argv[1][2] == '/') drive = argv[1][0];
			else if (strlen(argv[1]) == 3 && argv[1][1] == ':' && argv[1][2] == '\\') drive = argv[1][0];
			else {
				fprintf(stderr, "Invalid drive.\n");
				return -1;
			}
		} else if (argc == 1) {
			char cwd[262];
			getcwd(cwd, 255);
			drive = cwd[0];
		}

		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		char labelbuf[50];
		memset(labelbuf, 0, 50);
		uint32_t serial;
		int res = SystemCall(GetDiskVolumeLabel, drive - 'A', &serial, labelbuf);

		fprintf(out, "Volume label of %c: is %s\nVolume serial number is %04X-%04X\n", drive, labelbuf, serial >> 16, serial & 0xFFFF);

	} else if (!strcasecmp(argv[0], "install")) {
		extern int installmain(int argc, char* argv[]);
		installmain(argc, argv);

	} else if (!strcasecmp(argv[0], "unpack")) {
		unpackmain(argc, argv);

	} else if (!strcasecmp(argv[0], "help") || !strcasecmp(argv[0], "?")) {
		FILE* f = fopen("C:/Banana/Help/cmdhelp.txt", "r");
		if (!f) {
			fprintf(stderr, "Uh oh, the help file couldn't be found! Sorry!\n");
		} else {
			fprintf(out, "\x1b[47m\x1b[30m\x1B[2J");
			char s;
			char line[90];
			int count = 0;
			while (fgets(line, 89, f) != NULL) {
				fprintf(out, "%s", line);
				if (count++ == 20) {
					count = 0;
					printf("\nPress ENTER to continue");
					int c;
					while ((c = getchar()) != '\n' && c != EOF) {}
					putchar('\n');
				}
			}
			fclose(f);
			printf("\nPress ENTER to finish");
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
			fprintf(out, "\x1b[0m\x1B[2J");
		}

	} else if (!strcasecmp(argv[0], "shutdown")) {
		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		SystemCall(Shutdown, 0, 0, 0);

	} else if (!strcasecmp(argv[0], "loaddll")) {
		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		if (argc == 2) {
			int ret = SystemCall(LoadDLL, (size_t) argv[1], 0, 0);
			if (ret == 0)		fprintf(stdout, "Driver has been loaded.\n");
			else if (ret == 2)	fprintf(stderr, "The driver could not be found.\n");
			else if (ret == 3)	fprintf(stderr, "The driver could not be loaded into memory.\n");
			else if (ret == 4)	fprintf(stderr, "The driver has relocations which cannnot be resolved.\n");
			else				fprintf(stderr, "An unknown error occured.\n");

		} else {
			fprintf(stderr, "Please enter driver filename.\n");
		}

	} else if (!strcasecmp(argv[0], "getenv")) {
		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		if (argc == 2) {
			char* env = getenv(argv[1]);
			if (env) {
				fprintf(out, "%s\n", env);
			}

		} else {
			fprintf(stderr, "Please enter an environment variable name.\n");
		}

	} else if (!strcasecmp(argv[0], "restart")) {
		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		SystemCall(Shutdown, 2, 0, 0);

	} else if (!strcasecmp(argv[0], "sleep")) {
		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		SystemCall(Shutdown, 1, 0, 0);

	} else if (!strcasecmp(argv[0], "format")) {
		//ebx = disknum
		//ecx = allocation unit (0 = default)
		//edx = filesystem string

		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		char fstype[12] = "FAT32";
		char drive = 'C';

		if (argc != 3 && argc != 4) {
			fprintf(stderr, "Incorrect parameters. Expected:\n    format drive filesystem\n    e.g. format C: FAT32\n");
			return -1;
		}
		if (strlen(argv[1]) != 2 || argv[1][1] != ':') {
			fprintf(stderr, "Invalid drive specification.\n");
			return -1;
		}

		strcpy(fstype, argv[2]);
		drive = argv[1][0];
		bool quiet = argc == 4 && !strcmp(argv[3], "-quiet");
		if (!quiet) {
			fprintf(out, "WARNING: All data and files on this drive will be deleted and cannot be\nrecovered.\n\nProceed? Y/N: ");
			int yn = getchar();
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
			if (!(yn == 'Y' || yn == 'y')) {
				return -1;
			}
		}

		fprintf(out, "Formatting...\n");

		int res = SystemCall(FormatDisk, drive - 'A', 0, (size_t) fstype);

		if (res == 0) {
			fprintf(out, "\aThe drive was formatted successfully.\n");

		} else if (res == 1) {
			fprintf(stderr, "Invalid parameters.\n");
		} else if (res == 2) {
			fprintf(stderr, "An error occured while formatting the drive.\nThe filesystem may not be in a usable state.\n");
		} else if (res == 3) {
			fprintf(stderr, "Filesystem type not supported.\n");
		} else {
			fprintf(stderr, "An unknown error occured.\n");
		}

	} else if (!strcasecmp(argv[0], "settimezone") || !strcasecmp(argv[0], "settz") || !strcasecmp(argv[0], "timezone")) {
		FILE* f = fopen("C:/Banana/System/timezone.txt", "r");

		fprintf(out, "Please find the ID number of your timezone:\n\n");

		char buffer[256];
		int lineNum = 0;
		while (fgets(buffer, 255, f)) {
			fprintf(out, "    %d: ", lineNum + 1);
			for (int i = 0; buffer[i]; ++i) {
				if (buffer[i] == '\n' || buffer[i] == '\r') break;
				if (buffer[i] == '\t') {
					fprintf(out, ", ");
					continue;
				}
				fputc(buffer[i], out);
			}
			fputc('\n', out);

			if ((lineNum % 15) == 14) {
				fprintf(out, "\nPress ENTER to continue\n");
				int c = getchar();
				if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
			}
			
			++lineNum;
		}

		fclose(f);
		fflush(stdin);
		fprintf(out, "\nEnter your timezone ID: ");

		char num[32];
		int tzID = -1;
		fgets(num, 31, stdin);
		sscanf(num, "%d", &tzID);
		tzID -= 1;
		if (tzID == -1 || tzID < 0 || tzID >= lineNum) {
			fprintf(out, "The timezone was not set.\n");
		} else {
			extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
			int failed = SystemCall(Timezone, tzID, 1, 0);
			if (failed) {
				fprintf(out, "The timezone failed to be set.\n");
			} else {
				fprintf(out, "The timezone was set.\n", tzID);
			}
		}

	} else if (!strcasecmp(argv[0], "setdate") || !strcasecmp(argv[0], "settime")) {
	retry:;
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		fprintf(out, "Current time is: %02d/%02d/%04d %02d:%02d:%02d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		fprintf(out, "                 DD/MM/YYYY HH:MM:SS\n");
		fprintf(out, "Enter new time : ");

		int day = -1;
		int month = -1;
		int year = -1;
		int hour = -1;
		int minute = -1;
		int seconds = -1;
		char line[256];
		fgets(line, 255, stdin);
		fflush(stdin);
		sscanf(line, "%d/%d/%d %d:%d:%d", &day, &month, &year, &hour, &minute, &seconds);

		if (year < 100 && year != -1) {
			year += 2000;
		}

		if (year == -1) year = timeinfo->tm_year + 1900;
		if (month == -1) month = timeinfo->tm_mon + 1;
		if (day == -1) day = timeinfo->tm_mday;
		if (hour == -1) hour = timeinfo->tm_hour;
		if (minute == -1) minute = timeinfo->tm_min;
		if (seconds == -1) seconds = timeinfo->tm_sec;

		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		uint32_t b = seconds + minute * 60 + hour * 3600;
		uint32_t c = (day - 1) + month * 32;
		uint32_t d = year;
		int res = SystemCall(SetTime, b, c, d);
		if (res) {
			fprintf(out, "The time could not be set.\n");
		} else {
			fprintf(out, "The time was set.\n");
		}

	} else if (!strcasecmp(argv[0], "date") || !strcasecmp(argv[0], "time")) {
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		char days[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		
		fprintf(out, "%s %d/%d/%d %d:%02d:%02d\n", days[timeinfo->tm_wday], timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	} else if (!strcasecmp(argv[0], "attrib")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter file name.\n");
			return -1;
		}

		int clear = 0;
		int set = 0;

		char* filename = 0;

		for (int i = 1; i < argc; ++i) {
			if (!strcasecmp(argv[i], "+r")) set |= 1;
			else if (!strcasecmp(argv[i], "+a")) set |= 2;
			else if (!strcasecmp(argv[i], "+s")) set |= 4;
			else if (!strcasecmp(argv[i], "+h")) set |= 8;
			else if (!strcasecmp(argv[i], "-r")) clear |= 1;
			else if (!strcasecmp(argv[i], "-a")) clear |= 2;
			else if (!strcasecmp(argv[i], "-s")) clear |= 4;
			else if (!strcasecmp(argv[i], "-h")) clear |= 8;
			else {
				if (filename != 0) {
					fprintf(stderr, "Too many files specified.\n");
					return -1;
				}
				filename = argv[i];
			}
		}

		if (filename == 0) {
			fprintf(stderr, "Please enter file name.\n");
			return -1;
		}

		printf("TODO: accept wildcards...\n");

		extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
		int res = SystemCall(SetFATAttrib, 0, clear | (set << 8), (size_t) filename);
		if (res) {
			fprintf(stderr, "Failed to modify attributes.\n");
			return -1;
		}

	} else if (!strcasecmp(argv[0], "type")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter file name.\n");
			return -1;
		}

		FILE* f = fopen(argv[1], "r");
		if (!f) {
			fprintf(stderr, "Error opening file.\n");
		} else {
			char s;
			while ((s = fgetc(f)) != EOF) {
				fprintf(out, "%c", s);
			}
			fclose(f);
		}

	} else if (!strcasecmp(argv[0], "more")) {
		if (argc == 1) {
			fprintf(stderr, "Please enter file name.\n");
			return -1;
		}

		FILE* f = fopen(argv[1], "r");
		if (!f) {
			fprintf(stderr, "Error opening file.\n");
		} else {
			char s;
			int x = 0;
			int y = 0;
			while ((s = fgetc(f)) != EOF) {
				fprintf(out, "%c", s);
				if (s == '\n') {
					x = 0;
					y++;
				} else {
					x++;
					if (x == 80) {
						y++;
						x = 0;
					}
				}

				if (y == 22) {
					printf("Press ENTER to continue... ");
					int c = getchar();
					if (c != '\n' && c != EOF) while ((c = getchar()) != '\n' && c != EOF) {}
					y = 0;
				}
			}
			fclose(f);
		}

	} else if (!strcasecmp(argv[0], "status")) {
		if (argc == 1) {
			fprintf(out, "%d", errorLevel);
			if (out == stdout) putchar('\n');
		} else {
			printf("TODO: IMPLEMENT!\n");
			//sscanf(argv[1], "%d", &errorLevel);
		}

	} else if (!strcasecmp(argv[0], "pushd")) {
		if (dirStackPtr == MAX_DIR_STACK) {
			fprintf(stderr, "Cannot push any futher.\n");

		} else {
			dirStackArray[dirStackPtr] = calloc(256, 1);
			getcwd(dirStackArray[dirStackPtr], 255);
			++dirStackPtr;
		}

	} else if (!strcasecmp(argv[0], "popd")) {
		if (dirStackPtr > 0) {
			--dirStackPtr;
			chdir(dirStackArray[dirStackPtr]);
			free(dirStackArray[dirStackPtr]);
		}

	} else if (!strcasecmp(argv[0], "pushe") || !strcasecmp(argv[0], "pushs")) {
		if (errStackPtr == MAX_DIR_STACK) {
			fprintf(stderr, "Cannot push any futher.\n");

		} else {
			errStackArray[errStackPtr] = errorLevel;
			++errStackPtr;
		}

	} else if (!strcasecmp(argv[0], "pope") || !strcasecmp(argv[0], "pops")) {
		if (errStackPtr > 0) {
			--errStackPtr;
			errorLevel = errStackArray[errStackPtr];
		}

	} else if (!strcasecmp(argv[0], "exit")) {
		exit(0);

	} else if (!strcasecmp(argv[0], "rem") || !strcmp(argv[0], "//")) {

	} else if (!strcasecmp(argv[0], "cd") || !strcasecmp(argv[0], "pwd") || !strcasecmp(argv[0], "cwd") || !strcasecmp(argv[0], "chdir")) {
		if (!strcasecmp(argv[0], "cwd")) argc = 1;
		if (!strcasecmp(argv[0], "pwd")) argc = 1;

		if (argc == 1) {
			char cwd[256];
			getcwd(cwd, 255);
			fprintf(out, "%s\n", cwd);

		} else {
			int res = chdir(argv[1]);
			if (res == 0) {

			} else {
				if (errno == ENOTDIR) {
					fprintf(stderr, "Not a directory or invalid drive.\n");

				} else if (errno == EACCES) {
					fprintf(stderr, "Access denied.\n");

				} else if (errno == ENAMETOOLONG || errno == ELOOP) {
					fprintf(stderr, "The path name is invalid.\n");

				} else {
					fprintf(stderr, "The specified directory could not be found.\n");
				}
			}
		}

	} else if (!argv[0]) {
		return -9999999;

	} else {
		if (!argv[0] || !argv[0][0]) {
			fprintf(stderr, "Executable filepath required.\n");
			return -1;
		}

		if (!strcasecmp(argv[0], "start")) {
			for (int i = 0; i < argc - 1; ++i) {
				argv[i] = argv[i + 1];
			}
			argv[argc - 1] = 0;
		}
		if (!argv[0] || !argv[0][0]) {
			fprintf(stderr, "Executable filepath required.\n");
			return -1;
		}
		
		bool waitForChild = true;
		if (!strcmp(argv[0], "+")) {
			waitForChild = false;
			for (int i = 0; i < argc - 1; ++i) {
				argv[i] = argv[i + 1];
			}
			argv[argc - 1] = 0;
		}
		if (!argv[0] || !argv[0][0]) {
			fprintf(stderr, "Executable filepath required.\n");
			return -1;
		}

		char* possibleExecutableName = 0;

		if (!argv[0] || !argv[0][0]) {
			fprintf(stderr, "Executable filepath required.\n");
			free(possibleExecutableName);
			return -1;
		}

		if ((possibleExecutableName = getPossibleExecutableName(argv[0]))) {		//assignment intended
			pid_t pid;

			extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
			argv[0] = possibleExecutableName;
			pid = SystemCall(Spawn, 0, (size_t) argv, (size_t) argv[0]);
			if (pid && waitForChild) {
				waitpid(pid, &errorLevel, 0);
			} else {
				fprintf(stderr, "The program could not be started.\n");
			}
			free(possibleExecutableName);

		} else {
			fprintf(stderr, "'%s' is not recognised as a program, batch file, file or directory.\n", argv[0]);
		}
	}

	return -1;
}

int parseLine(char* line, Label labels[64], int batchNesting)
{
	if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;

	while (isspace(line[0])) ++line;

	if (line[0] == 0) {
		return -9999999;
	}

	char* args[32];
	memset(args, 0, 32 * sizeof(char*));
	int argno = 0;
	int argptr = 0;

	bool escape = false;
	bool quotes = false;
	args[argno] = calloc(256, 1);
	for (int i = 0; line[i]; ++i) {
		if (line[i] == '\\' && !escape) {
			escape = true;
			continue;
		}
		if (line[i] == '"' && !escape) {
			quotes ^= 1;
			continue;
		}

		if ((line[i] == ' ' || line[i] == '>' || line[i] == '|' || line[i] == '<') && !escape && !quotes) {
			if (argptr) argno++;
			if (argno > 30) {
				printf("Too many arguments given.\n");
				return -2;
			}
			argptr = 0;
			args[argno] = calloc(256, 1);
			if (line[i] == '>') {
				args[argno][argptr++] = '>';
				if (line[i + 1] == '>') {
					args[argno][argptr++] = '>';
					++i;
				}
				argno++;
				argptr = 0;
				args[argno] = calloc(256, 1);
			}
			if (line[i] == '<') {
				args[argno][argptr++] = '<';
				argno++;
				argptr = 0;
				args[argno] = calloc(256, 1);
			}
			if (line[i] == '|') {
				args[argno][argptr++] = '|';
				argno++;
				argptr = 0;
				args[argno] = calloc(256, 1);
			}
		} else {
			args[argno][argptr++] = line[i];
		}

		escape = false;
	}
	++argno;

	int givenArgno = argno;
	FILE* newStdout = stdout;
	bool needToCloseStream = false;

	for (int i = 0; i < argno; ++i) {
		if (!strcmp(args[i], ">") || !strcmp(args[i], ">>")) {
			bool append = !strcmp(args[i], ">>");
			args[i] = 0;
			if (givenArgno == argno) givenArgno = i;

			if (i + 1 < argno) {
				++i;
				FILE* f = fopen(args[i], append ? "a" : "w");
				if (f) {
					newStdout = f;
					needToCloseStream = true;
				} else {
					fprintf(stderr, "The redirection file couldn't be opened.\n");
					return 1;
				}
			} else {
				fprintf(stderr, "The redirection syntax is invalid.\n");
				return 1;
			}
		}
	}

	int retv = parse(givenArgno, args, newStdout, labels, batchNesting);

	if (needToCloseStream) {
		fclose(newStdout);
	}
	for (int i = 0; i < argno; ++i) {
		free(args[argno]);
	}
	return retv;
}

void runBatchFile(char* filename, int batchNesting)
{
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("The specified file could not be found.\n");
		return;
	}

	Label labels[64];
	memset(labels, 0, 64 * sizeof(Label));

	char buffer[256];
	memset(buffer, 0, 256);
	int labelNo = 0;
	int line = 0;
	while (fgets(buffer, 255, f)) {
		if (buffer[0] == ':' && buffer[1]) {
			if (buffer[strlen(buffer) - 1] == '\n') {
				buffer[strlen(buffer) - 1] = 0;
			}
			if (buffer[strlen(buffer) - 1] == '\r') {
				buffer[strlen(buffer) - 1] = 0;
			}
			if (buffer[strlen(buffer) - 1] == '\n') {
				buffer[strlen(buffer) - 1] = 0;
			}
			labels[labelNo].used = true;
			labels[labelNo].line = line;
			labels[labelNo].label = malloc(256);
			if (!labels[labelNo].label) {
				printf("Memory error!\n");
				fclose(f);
				return;
			}
			strcpy(labels[labelNo].label, buffer + 1);
			++labelNo;
		}
		++line;
	}

	rewind(f);

	while (fgets(buffer, 255, f)) {
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 1] = 0;
		}
		if (buffer[strlen(buffer) - 1] == '\r') {
			buffer[strlen(buffer) - 1] = 0;
		}
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 1] = 0;
		}

		bool broke = false;

		bool backslash = false;
		bool string = false;
		int base = 0;
		for (int i = 0; buffer[i]; ++i) {
			if (buffer[i] == '\\' && !backslash) {
				backslash ^= true;
				continue;
			}
			if (buffer[i] == '"' && !backslash) {
				string ^= 1;
			}
			if (buffer[i] == '&' && !string && !backslash) {
				buffer[i] = 0;
				++i;
				int res = parseLine(buffer + base, labels, batchNesting);
				if (res != -9999999) putchar('\n');
				if (res == -2) {
					fclose(f);
					return;
				}
				if (res != -1) {
					rewind(f);
					while (res--) {
						fgets(buffer, 255, f);
					}
				}
				if (buffer[i] == 0) {
					broke = true;
					break;
				}
				base += i;
			}
			backslash = false;
		}

		if (!broke) {
			int res = parseLine(buffer + base, labels, batchNesting);
			if (res != -9999999) putchar('\n');
			if (res == -2) {
				fclose(f);
				return;
			}
			if (res != -1) {
				rewind(f);
				while (res--) {
					fgets(buffer, 255, f);
				}
			}
		}
	}

	fclose(f);
}

int main (int argc, char *argv[])
{
	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	
	for (int i = 0; i < 26; ++i) {
		mathVars[i] = 0;
	}

	printf("\n%s\n    (C)Copyright Alex Boxall 2016-2021\n\n", VERSION_STRING);

	//setttyname("Banana Command Prompt");

	if (!getenv("PATH")) {
		printf("Warning: The PATH is not set.\n\n");
	}

	Label labels[64];
	memset(labels, 0, 64 * sizeof(Label));
	
	bool firstLoop = true;

	while (1) {
		memset(labels, 0, 64 * sizeof(Label));

		displayPrompt();

		char command[256];
		if (argc > 1 && firstLoop) {
			memset(command, 0, 256);
			if (strlen(argv[1]) < 255) {
				strcpy(command, argv[1]);
				for (int i = 2; i < argc && strlen(command) + strlen(argv[i]) < 250; ++i) {
					strcat(command, " ");
					strcat(command, argv[i]);
				}
			}
			
		} else {
			fgets(command, 255, stdin);
		}

		firstLoop = false;

		bool broke = false;

		bool backslash = false;
		bool string = false;
		int base = 0;
		int res = -9999999;
		for (int i = 0; command[i]; ++i) {
			if (command[i] == '\\' && !backslash) {
				backslash ^= true;
				continue;
			}
			if (command[i] == '"' && !backslash) {
				string ^= 1;
			}
			if (command[i] == '&' && !string && !backslash) {
				command[i] = 0;
				++i;
				res = parseLine(command + base, labels, 0);
				if (command[i] == 0) {
					broke = true;
					break;
				}
				base += i;
			}
			backslash = false;
		}

		if (!broke) {
			res = parseLine(command + base, labels, 0);
		}

		if (res != -9999999) putchar('\n');
	}

	return 0;
}