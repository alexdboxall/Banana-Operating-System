#include <stdint.h>

void begin(void*);
void beginx(void* a)
{
    begin(a);
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/computer.hpp"
#include "thr/elf.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "reg/registry.hpp"
#include "reg/cm.hpp"
#include "thr/prcssthr.hpp"
#include "hal/buzzer.hpp"
#include "hal/clock.hpp"
#include "fs/vfs.hpp"

//MAIN SCRIPT


#define ACPI_SIZE size_t

int
memcmp(
    void* VBuffer1,
    void* VBuffer2,
    ACPI_SIZE               Count)
{
    char* Buffer1 = (char*) VBuffer1;
    char* Buffer2 = (char*) VBuffer2;


    for (; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++) {
    }

    return ((Count == ACPI_SIZE_MAX) ? 0 : ((unsigned char) *Buffer1 -
            (unsigned char) *Buffer2));
}

void*
memmove(
    void* Dest,
    const void* Src,
    ACPI_SIZE               Count)
{
    char* New = (char*) Dest;
    char* Old = (char*) Src;


    if (Old > New) {
        while (Count) {
            *New = *Old;
            New++;
            Old++;
            Count--;
        }
    } else if (Old < New) {
        New = New + Count - 1;
        Old = Old + Count - 1;
        while (Count) {
            *New = *Old;
            New--;
            Old--;
            Count--;
        }
    }

    return (Dest);
}


#include <stdint.h>
#include <stddef.h>


void*
memset(
    void* Dest,
    int                     Value,
    ACPI_SIZE               Count)
{
    char* New = (char*) Dest;


    while (Count) {
        *New = (char) Value;
        New++;
        Count--;
    }

    return (Dest);
}


ACPI_SIZE
strlen(
    const char* String)
{
    UINT32                  Length = 0;


    while (*String) {
        Length++;
        String++;
    }

    return (Length);
}


char*
strpbrk(
    const char* String,
    const char* Delimiters)
{
    const char* Delimiter;


    for (; *String != '\0'; ++String) {
        for (Delimiter = Delimiters; *Delimiter != '\0'; Delimiter++) {
            if (*String == *Delimiter) {
                return (ACPI_CAST_PTR(char, String));
            }
        }
    }

    return (NULL);
}

char* SavedPtr;
char*
strtok(
    char* String,
    const char* Delimiters)
{
    char* Begin = String;


    if (Begin == NULL) {
        if (SavedPtr == NULL) {
            return (NULL);
        }
        Begin = SavedPtr;
    }

    SavedPtr = strpbrk(Begin, Delimiters);
    while (SavedPtr == Begin) {
        *Begin++ = '\0';
        SavedPtr = strpbrk(Begin, Delimiters);
    }

    if (SavedPtr) {
        *SavedPtr++ = '\0';
        return (Begin);
    } else {
        return (NULL);
    }
}

char*
strcpy(
    char* DstString,
    const char* SrcString)
{
    char* String = DstString;

    while (*SrcString) {
        *String = *SrcString;

        String++;
        SrcString++;
    }

    *String = 0;
    return (DstString);
}

char*
strncpyxx(
    char* DstString,
    const char* SrcString,
    ACPI_SIZE               Count)
{
    char* String = DstString;


    for (String = DstString;
         Count && (Count--, (*String++ = *SrcString++)); ) {
        ;
    }

    while (Count--) {
        *String = 0;
        String++;
    }

    return (DstString);
}

int
strcmp(
    const char* String1,
    const char* String2)
{


    for (; (*String1 == *String2); String2++) {
        if (!*String1++) {
            return (0);
        }
    }

    return ((unsigned char) *String1 - (unsigned char) *String2);
}

char*
strchr(
    const char* String,
    int                     ch)
{


    for (; (*String); String++) {
        if ((*String) == (char) ch) {
            return ((char*) String);
        }
    }

    return (NULL);
}

int
strncmp(
    const char* String1,
    const char* String2,
    ACPI_SIZE               Count)
{


    for (; Count-- && (*String1 == *String2); String2++) {
        if (!*String1++) {
            return (0);
        }
    }

    return ((Count == ACPI_SIZE_MAX) ? 0 : ((unsigned char) *String1 -
            (unsigned char) *String2));
}

char*
strcat(
    char* DstString,
    const char* SrcString)
{
    char* String;

    for (String = DstString; *String++; ) {
        ;
    }

    for (--String; (*String++ = *SrcString++); ) {
        ;
    }

    return (DstString);
}

char*
strncat(
    char* DstString,
    const char* SrcString,
    ACPI_SIZE               Count)
{
    char* String;


    if (Count) {
        for (String = DstString; *String++; ) {
            ;
        }

        for (--String; (*String++ = *SrcString++) && --Count; ) {
            ;
        }

        if (!Count) {
            *String = 0;
        }
    }

    return (DstString);
}


char*
strstr(
    char* String1,
    char* String2)
{
    ACPI_SIZE               Length;


    Length = strlen(String2);
    if (!Length) {
        return (String1);
    }

    while (strlen(String1) >= Length) {
        if (memcmp(String1, String2, Length) == 0) {
            return (String1);
        }
        String1++;
    }

    return (NULL);
}


void rmtree(char* basePath)
{
	char path[300];
	memset(path, 0, 300);

	struct dirent _dp;
	struct dirent* dp = &_dp;

	int br;
	Directory* dir = new Directory(basePath, currentTaskTCB->processRelatedTo);
	FileStatus openstatus = dir->open();
	
	if (openstatus != FileStatus::Success) {
		delete dir;
		return;
	}

	while (1) {
		FileStatus st = dir->read(sizeof(struct dirent), dp, &br);
		if (st != FileStatus::Success) {
			break;
		}

		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			if (dp->d_type & DT_DIR) {
				rmtree(path);
			} else {
				strcpy(path, basePath);
				strcat(path, "/");
				strcat(path, dp->d_name);

				File* f = new File(path, currentTaskTCB->processRelatedTo);
				f->unlink();
				delete f;
			}
		}
	}

	dir->close();
	dir->unlink();
	delete dir;
}

int mkdir(const char* path, int permissions)
{
    Directory* d = new Directory(path, kernelProcess);
    d->create();
    delete d;

    return 0;
}


void copytree(char* basePath, char* newPath)
{
    char* path = (char*) malloc(400);
    char* npath = (char*) malloc(400);
    memset(path, 0, 400);
    memset(npath, 0, 400);

    struct dirent _dp;
    struct dirent* dp = &_dp;

    int br;
    Directory* dir = new Directory(basePath, currentTaskTCB->processRelatedTo);
    FileStatus openstatus = dir->open();
    if (openstatus != FileStatus::Success) {
        kprintf("Couldn't open base path.\n");
        delete dir;
        return;
    }

    while (1) {
        FileStatus st = dir->read(sizeof(struct dirent), dp, &br);
        if (st != FileStatus::Success) {
            break;
        }

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            strcpy(npath, newPath);
            strcat(npath, "/");
            strcat(npath, dp->d_name);

            kprintf("%s -> %s\n", path, npath);

            if (dp->d_type & DT_DIR) {
                int mres = mkdir(npath, 0700);
                if (mres != 0) {
                    KePanic("COULD NOT CREATE");
                } else {
                    copytree(path, npath);
                }

            } else {
                File* f = new File(path, currentTaskTCB->processRelatedTo); //fopen(path, "rb");
                f->open(FILE_OPEN_READ);
                if (!f) {
                    KePanic("COULD NOT COPY");
                    continue;
                }

                if (f) {
                    File* dest = new File(npath, currentTaskTCB->processRelatedTo);
                    dest->open(FILE_OPEN_WRITE_NORMAL);
                    if (!dest) {
                        KePanic("COULD NOT COPY");
                        dest->close();
                        continue;
                    }

                    char* m = (char*) malloc(4096);
                    if (!m) {
                        KePanic("NO MEMORY");
                        free(path);
                        free(npath);
                        return;
                    }
                    while (1) {
                        //read(uint64_t bytes, void* where, int* bytesRead)

                        int red;
                        int red2;
                        FileStatus st = f->read(4096, m, &red);
                        if (st != FileStatus::Success) {
                            break;
                        }
                        dest->write(red, m, &red2);
                        if (red != 4096) {
                            break;
                        }
                    }
                    free(m);

                    f->close();
                    dest->close();
                    delete f;
                    delete dest;
                }
            }
        }
    }

    free(path);
    free(npath);

    dir->close();
    delete dir;
}

void backupTree(char* basePath, uint16_t hash)
{
	char* path = (char*) malloc(400);
    memset(path, 0, 400);

    struct dirent _dp;
    struct dirent* dp = &_dp;
	
    int br;
    Directory* dir = new Directory(basePath, currentTaskTCB->processRelatedTo);
    FileStatus openstatus = dir->open();
    if (openstatus != FileStatus::Success) {
        kprintf("Couldn't open base path.\n");
        delete dir;
        return;
    }

	while (1) {
        FileStatus st = dir->read(sizeof(struct dirent), dp, &br);
		if (st != FileStatus::Success) {
			break;
		}

		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);

            uint16_t newHash = 0xADBC;

            for (int i = 0; dp->d_name[i]; ++i) {
                newHash ^= dp->d_name[i];
                newHash = (newHash << 3) | (newHash >> 13);
                newHash -= 1777;
            }

			if (dp->d_type & DT_DIR) {
                //we don't want to backup the backups, etc.
                if (strcmp(dp->d_name, "Backup")) {
                    backupTree(path, newHash);
                }

            } else {

                char bkupPath[256];
                char s[2];
                s[1] = 0;

                strcpy(bkupPath, "C:/Banana/System/Backup/");

                s[0] = basePath[10];
                strcat(bkupPath, s);

                char ss[9];
                memset(ss, 0, 9); 
                strncpyxx(ss, dp->d_name, 8);
                for (int i = 0; i < 8; ++i) {
                    if (ss[i] >= 'a' && ss[i] <= 'z') ss[i] -= 32;
                    if (ss[i] == 'Y') ss[i] = 'Q';
                    if (ss[i] == 'Z') ss[i] = 'Q';
                    if (ss[i] == ' ') ss[i] = 'Y';
                    if (ss[i] == '.') ss[i] = 'Z';
                }
                strcat(bkupPath, ss);

                s[0] = 'A' + strlen(dp->d_name);
                strcat(bkupPath, s);

                strcat(bkupPath, ".");

                uint16_t nhash = hash ^ (newHash & 0x765);

                char aa[17] = "0123456789ABCDEF";
                s[0] = aa[(nhash >> 0) & 0xF];
                strcat(bkupPath, s);
                s[0] = aa[(nhash >> 4) & 0xF];
                strcat(bkupPath, s);
                s[0] = aa[(nhash >> 8) & 0xF];
                strcat(bkupPath, s);
                s[0] = aa[(nhash >> 12) & 0xF];
                strcat(bkupPath, s);


                File* f = new File(path, currentTaskTCB->processRelatedTo); //fopen(path, "rb");
                f->open(FILE_OPEN_READ);
                if (!f) {
                    KePanic("COULD NOT COPY");
                    continue;
                }

                if (f) {
                    File* dest = new File(bkupPath, currentTaskTCB->processRelatedTo);
                    dest->open(FILE_OPEN_WRITE_NORMAL);
                    if (!dest) {
                        KePanic("COULD NOT COPY");
                        dest->close();
                        continue;
                    }

                    char m[4096];
                    while (1) {
                        int red;
                        int red2;
                        FileStatus st = f->read(4096, m, &red);
                        if (st != FileStatus::Success) {
                            break;
                        }
                        dest->write(red, m, &red2);
                        if (red != 4096) {
                            break;
                        }
                    }
                    f->close();
                    dest->close();
                    delete f;
                    delete dest;
                }
            }
		}
	}

	free(path);

	dir->close();
    delete dir;
}

void createUser(const char* name)
{
    char path[256];
    strcpy(path, "C:/Users/");
    strcat(path, name);
    mkdir(path, 0700);
    
    strcat(path, "/Desktop");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Documents");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Downloads");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Photos");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Trash Bin");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Music");
    mkdir(path, 0700);

    strcpy(path, "C:/Users/");
    strcat(path, name);
    strcat(path, "/Movies");
    mkdir(path, 0700);

    strcpy(path, "C:/Banana/Registry/User/");
    strcat(path, name);
    mkdir(path, 0700);

    copytree("C:/Banana/Registry/DefaultUser", path);
}

VgaText* term;
bool showSidebar = true;
void drawBootScreen()
{
    term->setDefaultBgColour(VgaColour::Cyan);
    term->setDefaultFgColour(VgaColour::Black);
    term->clearScreen();
    term->setTitle("");
    term->setTitleColour(VgaColour::Black);
    term->setTitleTextColour(VgaColour::Black);
    term->setCursor(0, 0);
    for (int x = 0; x < 80; ++x) {
        term->putchar(' ', VgaColour::Black, VgaColour::Black);
    }
    if (showSidebar) {
        for (int y = 0; y < 25; ++y) {
            term->setCursor(0, y);
            for (int x = 0; x < 16; ++x) {
                term->putchar(' ', VgaColour::Black, VgaColour::Black);
            }
        }
        term->setCursor(1, 1);
        term->puts("Checking\n system\n requirements\n\n Legal\n notices\n\n Choosing a\n partition\n\n Formatting\n\n Copying files\n\n Restarting\n your computer\n\n", VgaColour::White, VgaColour::Black);
        term->puts(" Finalising the\n installation", VgaColour::Yellow, VgaColour::Black);
    }
    term->setDefaultBgColour(VgaColour::White);
    term->setDefaultFgColour(VgaColour::Black);
}

void drawBasicWindowX(int wx, int wy, int ww, int wh, const char* wtitle, bool grey)
{
    wy++;

    for (int y = 0; y < wh; ++y) {
        term->setCursor(wx, wy + y);
        for (int x = 0; x < ww; ++x) {
            term->putchar(' ', grey ? VgaColour::LightGrey : VgaColour::White, grey ? VgaColour::LightGrey : VgaColour::White);
        }
    }

    term->setCursor(wx, wy);
    for (int x = 0; x < ww; ++x) {
        term->putchar(' ', VgaColour::Blue, VgaColour::Blue);
    }

    term->setCursor(wx + 1, wy + wh);
    for (int x = 0; x < ww; ++x) {
        term->putchar(' ', VgaColour::Teal, VgaColour::Teal);
    }

    for (int x = wy; x < wy + wh; ++x) {
        term->setCursor(ww + wx, 1 + x);
        term->putchar(' ', VgaColour::Teal, VgaColour::Teal);

        if (x != wy + wh - 1) {
            term->setCursor(wx, 1 + x);
            term->putchar('\xDD', VgaColour::Black, grey ? VgaColour::LightGrey : VgaColour::White);
        }
    }

    int g = (ww - strlen(wtitle)) / 2 - 1;
    term->setCursor(wx + g, wy);
    for (int j = 0; j < strlen(wtitle); ++j) {
        term->putchar(wtitle[j], VgaColour::White, VgaColour::Blue);
    }
}

void drawBasicWindow(int wx, int wy, int ww, int wh, const char* wtitle)
{
    drawBasicWindowX(wx, wy, ww, wh, wtitle, false);
}

#include "hal/keybrd.hpp"

extern void (*guiKeyboardHandler) (KeyboardToken kt, bool* keystates);
volatile char installKey = 0;
void bootInstallKeybrd(KeyboardToken kt, bool* keystates)
{
    if (keystates[(int) KeyboardSpecialKeys::Shift] && kt.halScancode == '\t') {
        installKey = 127;
        return;
    }
    if (kt.release) return;
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Left) { 
        installKey = 3; 
        return; 
    }
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Right) {
        installKey = 4; 
        return;
    }
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Up) {
        installKey = 1;
        return;
    }
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Down) {
        installKey = 2;
        return;
    }
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::PageDown) {
        installKey = 125;
        return;
    }
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::PageDown) {
        installKey = 126;
        return;
    }
    installKey = kt.halScancode;
}

void bootInstallTasks(int done)
{ 
    term->setCursor(24, 8);
    term->puts("Please wait while the install finishes.");

    term->setCursor(26, 10);
    term->puts(done == 0 ? "\x10 " : "  ");
    term->puts("Allocating the swapfile", done >= 0 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 11);
    term->puts(done == 1 ? "\x10 " : "  ");
    term->puts("Updating the registry", done >= 1 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 12);
    term->puts(done == 2 ? "\x10 " : "  ");
    term->puts("Creating user account", done >= 2 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 13);
    term->puts(done == 3 ? "\x10 " : "  ");
    term->puts("Installing packages", done >= 3 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 14);
    term->puts(done == 4 ? "\x10 " : "  ");
    term->puts("Backing up system files", done >= 4 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 15);
    term->puts(done == 5 ? "\x10 " : "  ");
    term->puts("Finishing touches", done >= 5 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);
}

uint64_t ror(uint64_t x, int L, int N)
{
    uint64_t lsbs = x & ((1 << L) - 1);
    return (x >> L) | (lsbs << (N - L));
}

uint64_t swapBits(uint64_t n, uint64_t p1, uint64_t p2)
{
    return (((n >> p1) & 1ULL) == ((n >> p2) & 1ULL) ? n : ((n ^ (1ULL << p2)) ^ (1ULL << p1)));
}

uint32_t getChecksum(uint32_t num)
{
    uint16_t checksumA = 'NI';
    uint16_t checksumB = 'ny';
    uint16_t checksumC = 'ag';
    uint16_t checksumD = (num >> 16) ^ ((num & 0xffff) * 1009);

    while (num) {
        checksumA *= (756 / num) ^ (278354 + ror(num, 5, 29));
        checksumB -= (234 / num) ^ (645893 + ror(num, 3, 31));
        checksumC += (checksumA ^ checksumB) & 1234;
        checksumC += num;
        num >>= 1;
    }

    return (checksumA ^ checksumB ^ checksumC ^ checksumD) & 0x7FFF;
}



char lookupA[] = "QWRTYUPSDFGHKZCB";
char lookupB[] = "HQYUTSDRBPFGWKCZ";
char lookupC[] = "GSBPDTCHWURZQYMN";

void createKey(char* buffer, uint32_t iter)
{
    strcpy(buffer, "QQ-000-000-000-Q");

    uint64_t bits = ((uint64_t) iter) << 15ULL;
    bits |= getChecksum(iter);

    for (int i = 0; i < 9436; ++i) {
        bits ^= 0x37B5E43895ULL;
        bits = swapBits(bits, 3, 8);
        bits = swapBits(bits, 13, 12);
        bits = swapBits(bits, 37, 22);
        bits = ror(bits, 19, 42);
    }

    int alpha1 = bits & 0xF;
    bits >>= 4;
    int alpha2 = bits & 0xF;
    bits >>= 4;
    int alpha3 = bits & 0xF;
    bits >>= 4;

    int num1 = bits & 1023;
    bits >>= 10;
    int num2 = bits & 1023;
    bits >>= 10;
    int num3 = bits & 1023;
    bits >>= 10;

    buffer[0] = lookupA[alpha1];
    buffer[1] = lookupA[alpha2];
    buffer[15] = lookupA[alpha3];

    buffer[3] = (num1 / 100) % 10 + '0';
    buffer[4] = (num1 / 10) % 10 + '0';
    buffer[5] = (num1 / 1) % 10 + '0';

    buffer[7] = (num2 / 100) % 10 + '0';
    buffer[8] = (num2 / 10) % 10 + '0';
    buffer[9] = (num2 / 1) % 10 + '0';

    buffer[11] = (num3 / 100) % 10 + '0';
    buffer[12] = (num3 / 10) % 10 + '0';
    buffer[13] = (num3 / 1) % 10 + '0';
}

uint64_t retrieveBits(char* buffer)
{
    //AB-123-456-789-C
    //0123456789012345
    //0000000000111111

    int alpha1 = -1;
    int alpha2 = -1;
    int alpha3 = -1;
    for (int i = 0; i < 16; ++i) {
        if (lookupA[i] == buffer[0]) {
            alpha1 = i;
        }
        if (lookupB[i] == buffer[1]) {
            alpha2 = i;
        }
        if (lookupC[i] == buffer[15]) {
            alpha3 = i;
        }
    }

    if (alpha1 == -1 || alpha2 == -1 || alpha3 == -1) return false;

    uint64_t num1 = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0') * 1;
    uint64_t num2 = (buffer[7] - '0') * 100 + (buffer[8] - '0') * 10 + (buffer[9] - '0') * 1;
    uint64_t num3 = (buffer[11] - '0') * 100 + (buffer[12] - '0') * 10 + (buffer[13] - '0') * 1;

    uint64_t bits = (num1 << 0ULL) | (num2 << 10ULL) | (num3 << 20ULL);
    bits <<= 12;
    bits |= (alpha1 << 0) | (alpha2 << 4) | (alpha3 << 8);

    for (int i = 0; i < 9436; ++i) {
        bits = ror(bits, 19, 42);
        bits = swapBits(bits, 3, 8);
        bits = swapBits(bits, 13, 12);
        bits = swapBits(bits, 37, 22);
        bits ^= 0x37B5E43895ULL;
    }

    return bits;
}

#define KEY_TYPE_INVALID        0
#define KEY_TYPE_STANDARD       1
#define KEY_TYPE_PROFESSIONAL   2

int checkKey(char* buffer)
{
    uint64_t bits = retrieveBits(buffer);

    uint32_t minor = bits & 0x7FFF;
    uint32_t major = (uint32_t) (bits >> 15ULL);

    if (getChecksum(major) != minor) return KEY_TYPE_INVALID;

    return bits & 7;
}

bool changeKeyType(char* buffer, int type)
{
    uint64_t bits = retrieveBits(buffer);
    bits &= ~7ULL;
    bits |= type;

    createKey(buffer, bits);

    return checkKey(buffer);
}

int checkExtendedKey(char* modified)
{
    ///0123456789012345
    // AB-12345-67890-C     MODIFIED FORM

    ///0123456789012345
    // AB-123-456-789-C     REGULAR FORM

    char regular[20];
    regular[ 0] = modified[0];
    regular[ 1] = modified[1];
    regular[ 2] = modified[2];
    regular[ 3] = modified[3];
    regular[ 4] = modified[4];
    regular[ 5] = modified[5];
    regular[ 6] = '-';
    regular[ 7] = modified[6];
    regular[ 8] = modified[7];
    regular[ 9] = modified[9];
    regular[10] = '-';
    regular[11] = modified[10];
    regular[12] = modified[11];
    regular[13] = modified[12];
    regular[14] = '-';
    regular[15] = modified[15];

    regular[3] -= 1;
    if (regular[3] + 1 == '0') regular[3] = '9';
    regular[9] -= 1;
    if (regular[9] + 1 == '0') regular[9] = '9';

    if (modified[13] != modified[12]) {
        return KEY_TYPE_INVALID;
    }

    if (regular[3] < '0' || regular[3] > '9') return KEY_TYPE_INVALID;
    if (regular[4] < '0' || regular[4] > '9') return KEY_TYPE_INVALID;
    if (regular[5] < '0' || regular[5] > '9') return KEY_TYPE_INVALID;

    if (regular[7] < '0' || regular[7] > '9') return KEY_TYPE_INVALID;
    if (regular[8] < '0' || regular[8] > '9') return KEY_TYPE_INVALID;
    if (regular[9] < '0' || regular[9] > '9') return KEY_TYPE_INVALID;

    if (regular[11] < '0' || regular[11] > '9') return KEY_TYPE_INVALID;
    if (regular[12] < '0' || regular[12] > '9') return KEY_TYPE_INVALID;
    if (regular[13] < '0' || regular[13] > '9') return KEY_TYPE_INVALID;

    return checkKey(regular);
}

char currName[48] = "Alex";
char currComp[48] = "";
char pkeybuf[18];

char* timezoneStrings[200];

int loadTimezoneStrings()
{
    File* f = new File("C:/Banana/System/timezones.txt", kernelProcess);
    f->open(FileOpenMode::Read);
    uint64_t siz;
    bool dir;
    f->stat(&siz, &dir);
    int br;
    char* bf = (char*) malloc(siz);
    memset(bf, 0, siz);
    f->read(siz, bf, &br);
    f->close();

    kprintf("siz = %d\n", (int) siz);

    int num = 0;
    for (int i = 0; i < 200; ++i) {
        timezoneStrings[i] = (char*) malloc(120);
        strcpy(timezoneStrings[i], " ");
    }
    int j = 0;

    while (1) {
        char s[2];
        s[0] = bf[j++];
        s[1] = 0;
        if (s[0] == '\r') continue;
        if (s[0] == '\t') {
            while (strlen(timezoneStrings[num]) < 9) {
                strcat(timezoneStrings[num], " ");
            }
            
            continue;
        }
        if (s[0] == '\n') {
            while (strlen(timezoneStrings[num]) < 54) {
                strcat(timezoneStrings[num], " ");
            }
            num++;
            if (j >= siz) break;
            continue;
        }
        if (strlen(timezoneStrings[num]) < 50) {
            strcat(timezoneStrings[num], s);
        } else if (strlen(timezoneStrings[num]) == 50) {
            strcat(timezoneStrings[num], "... ");

        }
        //kprintf("%d: %s (%s)\n", num, timezoneStrings[num], s);
    }

    free(bf);

    for (int i = 0; i < 200; ++i) {
        kprintf("%d; %s\n", i, timezoneStrings[num]);
    }

    return num;
}

void firstRun(bool onlyPkey)
{
    showSidebar = !onlyPkey;

    guiKeyboardHandler = bootInstallKeybrd;

	KeSetBootMessage("Setting up the system for the first time");

    VgaText::hiddenOut = false;

    activeTerminal->puts("\n\n\n\n\n\n");
    kernelProcess->terminal->puts("\n\n\n\n\n\n");

    term = new VgaText("Test");
    setActiveTerminal(term);
    drawBootScreen();

    int timePtr = 0;

    if (!onlyPkey) {
        int sel = 0;
        drawBasicWindow(22, 3, 50, 12, "Banana Setup");
        term->setCursor(24, 6); term->puts("Please enter your details. Press TAB to switch");
        term->setCursor(24, 7); term->puts("between fields.");
        term->setCursor(24, 9); term->puts("Name");
        term->setCursor(24, 11); term->puts("Company");

        while (1) {
            term->setCursor(33, 9);
            term->puts("                         ", VgaColour::Black, VgaColour::LightGrey);
            term->puts(sel == 0 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);
            term->setCursorX(33);
            term->puts(currName, VgaColour::Black, VgaColour::LightGrey);

            term->setCursor(33, 11);
            term->puts("                         ", VgaColour::Black, VgaColour::LightGrey);
            term->puts(sel == 1 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);
            term->setCursorX(33);
            term->puts(currComp, VgaColour::Black, VgaColour::LightGrey);

            term->setCursor(24, 13);
            term->puts(sel == 2 ? "Press ENTER" : "           ", VgaColour::DarkGrey, VgaColour::White);
            term->setCursor(24, 14);
            term->puts(sel == 2 ? "to submit" : "           ", VgaColour::DarkGrey, VgaColour::White);

            term->setCursor(50, 13);
            if (sel != 2) term->puts("   OK   ", VgaColour::White, VgaColour::DarkGrey);
            else          term->puts("   OK   ", VgaColour::White, VgaColour::Blue);
            term->puts(sel == 2 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);

            if (sel == 0) term->setCursor(33 + strlen(currName), 9);
            if (sel == 1) term->setCursor(33 + strlen(currComp), 11);
            if (sel == 2) term->setCursor(0, 2);

            while (installKey == 0);
            memset(term->keybufferInternal, 0, 16);
            memset(term->keybufferSent, 0, 16);
            if (installKey == '\t' || installKey == '\n') {
                if (sel == 2 && installKey == '\n') {
                    installKey = 0;
                    break;
                }
                sel += 1;
                if (sel == 3) sel = 0;
                milliTenthSleep(300);

            } else if (installKey >= 32 && installKey < 127) {
                char ss[2];
                ss[0] = installKey;
                ss[1] = 0;
                if (sel == 0 && strlen(currName) < 24) strcat(currName, ss);
                if (sel == 1 && strlen(currComp) < 24) strcat(currComp, ss);

            } else if (installKey == '\b') {
                if (sel == 0 && strlen(currName)) currName[strlen(currName) - 1] = 0;
                if (sel == 1 && strlen(currComp)) currComp[strlen(currComp) - 1] = 0;

            } else if (installKey == 127) {
                // Shift + TAB
                sel--;
                if (sel == -1) {
                    sel = 2;
                }
                milliTenthSleep(300);
            }

            installKey = 0;
        }

        installKey = 0;
        milliTenthSleep(4000);
        installKey = 0;

        drawBootScreen();
        drawBasicWindow(22, 2, 50, 13, "Date and Time");

        datetime_t dt = computer->clock->timeInDatetimeUTC();

        char dateTime[64];
        strcpy(dateTime, "14/05/2021 18:55:00");
        dateTime[0] = dt.day / 10 + '0';
        dateTime[1] = dt.day % 10 + '0';
        dateTime[3] = (dt.month + 0) / 10 + '0';
        dateTime[4] = (dt.month + 0) % 10 + '0';
        dateTime[6] = ((dt.year + 0) / 1000) % 10 + '0';
        dateTime[7] = ((dt.year + 0) / 100) % 10 + '0';
        dateTime[8] = ((dt.year + 0) / 10) % 10 + '0';
        dateTime[9] = ((dt.year + 0) / 1) % 10 + '0';
        dateTime[11] = dt.hour / 10 + '0';
        dateTime[12] = dt.hour % 10 + '0';
        dateTime[14] = dt.minute / 10 + '0';
        dateTime[15] = dt.minute % 10 + '0';
        dateTime[17] = dt.second / 10 + '0';
        dateTime[18] = dt.second % 10 + '0';

        timePtr = 0;

        term->setCursor(24, 5); term->puts("Please enter the current date and time,");
        term->setCursor(24, 6); term->puts("and then press ENTER.");
        term->setCursor(26, 9); term->puts("DD/MM/YYYY HH:MM:SS", VgaColour::LightGrey, VgaColour::White);
        while (1) {
            term->setCursor(26, 8); term->puts(dateTime);
            term->setCursor(26 + timePtr, 8);
            term->putchar(dateTime[timePtr], VgaColour::White, VgaColour::Black);

            int hr = (dateTime[11] - '0') * 10 + (dateTime[12] - '0');
            int hr12 = hr % 12;
            if (hr12 == 0) hr12 = 12;
            int mi = (dateTime[14] - '0') * 10 + (dateTime[15] - '0');

            char xyz[16];
            memset(xyz, 0, 16);
            int abc = 0;
            xyz[abc++] = '(';
            xyz[abc++] = hr12 / 10 + '0';
            xyz[abc++] = hr12 % 10 + '0';
            xyz[abc++] = ':';
            xyz[abc++] = mi / 10 + '0';
            xyz[abc++] = mi % 10 + '0';
            xyz[abc++] = ' ';
            xyz[abc++] = hr >= 12 ? 'P' : 'A';
            xyz[abc++] = 'M';
            xyz[abc++] = ')';
            term->setCursor(26 + strlen(dateTime) + 4, 8); term->puts(xyz);

            term->setCursor(26 + timePtr, 8);

            while (installKey == 0);
            memset(term->keybufferInternal, 0, 16);
            memset(term->keybufferSent, 0, 16);
            if (installKey == 3 || installKey == '\b') {
                do {
                    --timePtr;
                    if (timePtr == -1) timePtr = strlen(dateTime) - 1;
                } while (dateTime[timePtr] == ' ' || dateTime[timePtr] == '/' || dateTime[timePtr] == ':');

            } else if ((installKey >= '0' && installKey <= '9') || installKey == ' ' || installKey == 4) {
                if (installKey >= '0' && installKey <= '9') {
                    if (timePtr == 0 && installKey >= '4') {
                        dateTime[timePtr++] = '0';
                        dateTime[timePtr] = installKey;

                    } else if (timePtr == 3 && installKey >= '2') {
                        dateTime[timePtr++] = '0';
                        dateTime[timePtr] = installKey;

                    } else if (timePtr == 11 && installKey >= '3') {
                        dateTime[timePtr++] = '0';
                        dateTime[timePtr] = installKey;

                    } else if (timePtr == 14 && installKey >= '6') {
                        dateTime[timePtr++] = '0';
                        dateTime[timePtr] = installKey;

                    } else if (timePtr == 17 && installKey >= '6') {
                        dateTime[timePtr++] = '0';
                        dateTime[timePtr] = installKey;

                    } else {
                        dateTime[timePtr] = installKey;
                    }
                }
                do {
                    ++timePtr;
                    if (timePtr >= strlen(dateTime)) timePtr = 0;
                } while (dateTime[timePtr] == ' ' || dateTime[timePtr] == '/' || dateTime[timePtr] == ':');

            } else if (installKey == '\n') {
                int dd = (dateTime[0] - '0') * 10 + (dateTime[1] - '0');
                int mm = (dateTime[3] - '0') * 10 + (dateTime[4] - '0');
                int yy = (dateTime[6] - '0') * 1000 + (dateTime[7] - '0') * 100 + \
                    (dateTime[8] - '0') * 10 + (dateTime[9] - '0');

                int hh = (dateTime[11] - '0') * 10 + (dateTime[12] - '0');
                int ii = (dateTime[14] - '0') * 10 + (dateTime[15] - '0');
                int ss = (dateTime[17] - '0') * 10 + (dateTime[18] - '0');

                bool leap = ((yy & 3) == 0 && ((yy % 25) != 0 || (yy & 15) == 0));

                if (dd > 31) timePtr = 0;
                else if (dd > 30 && (mm == 2 || mm == 4 || mm == 6 || mm == 9 || mm == 11)) timePtr = 0;
                else if (dd == 29 && mm == 2 && !leap) timePtr = 0;
                else if (dd == 0) timePtr = 0;
                else if (mm > 12 || mm == 0) timePtr = 3;
                else if (yy > 2999 || yy < 1970) timePtr = 6;
                else if (hh >= 24) timePtr = 11;
                else if (ii >= 60) timePtr = 14;
                else if (ss >= 60) timePtr = 17;
                else {
                    // TODO: actually set the time
                    break;
                }
            }

            milliTenthSleep(1100);
            installKey = 0;
        }

        installKey = 0;
        milliTenthSleep(4000);
        installKey = 0;

        drawBootScreen();
        drawBasicWindow(18, 1, 60, 20, "Date and Time");
        term->setCursor(20, 4); term->puts("Please select your timezone and then press ENTER.");

        int tzsel = 0;
        int scroll = 0;
        int numEntries = loadTimezoneStrings();

        int barHeight = 15 * 14 / numEntries;

        while (1) {
            for (int i = 0; i < 14; ++i) {
                term->setCursor(75, 7 + i);
                term->putchar(' ');
            }
            for (int i = 0; i < barHeight; ++i) {
                term->setCursor(75, 7 + i + scroll * 14 / numEntries);
                term->putchar(219);
            }
            term->setCursor(75, 6);
            term->putchar(30);
            term->setCursor(75, 20);
            term->putchar(31);

            for (int i = 0; i < 15; ++i) {
                term->setCursor(20, 6 + i);
                /*term->putchar(' ', scroll + i == tzsel ? VgaColour::White : VgaColour::DarkGrey, \
                    scroll + i == tzsel ? VgaColour::Black : VgaColour::White);*/
                term->puts(timezoneStrings[scroll + i], \
                           scroll + i == tzsel ? VgaColour::White : VgaColour::Black, \
                           scroll + i == tzsel ? VgaColour::Black : VgaColour::White);
            }


            while (installKey == 0);
            memset(term->keybufferInternal, 0, 4);
            memset(term->keybufferSent, 0, 4);
            if (installKey == 1) {
                tzsel--;
                if (tzsel - scroll < 5) {
                    scroll--;
                }
                if (tzsel < 0) tzsel = 0;
                if (scroll < 0) scroll = 0;

            } else if (installKey == 2) {
                tzsel++;
                if (tzsel - scroll > 10) {
                    scroll++;
                }
                if (tzsel > numEntries - 2) tzsel = numEntries - 2;
                if (scroll > numEntries - 15 - 1) scroll = numEntries - 15 - 1;

            }/* else if (installKey == 125) {
                //page up

                for (int i = 0; i < 14; ++i) {
                    tzsel--;
                    if (tzsel - scroll < 5) {
                        scroll--;
                    }
                    if (tzsel < 0) tzsel = 0;
                    if (scroll < 0) scroll = 0;
                }

            } else if (installKey == 126) {
                //page down

                for (int i = 0; i < 14; ++i) {
                    tzsel++;
                    if (tzsel - scroll > 10) {
                        scroll++;
                    }
                    if (tzsel > numEntries - 2) tzsel = numEntries - 2;
                    if (scroll > numEntries - 15 - 1) scroll = numEntries - 15 - 1;
                }

            }*/ else if (installKey == '\n') {
                break;
            }

            milliTenthSleep(500);
            installKey = 0;
        }
    }

    if (onlyPkey) {
        showSidebar = false;
        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Invalid Product Key");
        term->setCursor(24, 8);
        term->puts("You do not have a valid product key.\n");
        term->setCursor(24, 10);
        term->puts("You need a valid product key in order to");
        term->setCursor(24, 11);
        term->puts("use Banana.");
        term->setCursor(24, 14);
        term->puts("Press ENTER to re-enter your product key.");
        installKey = 0;
        while (installKey == 0);
        installKey = 0;
    }

    installKey = 0;
    milliTenthSleep(900);
    drawBootScreen();
    milliTenthSleep(11800);

    if (onlyPkey) {
        strcpy(pkeybuf, "AA-00000-00000-A");
    } else {
        strcpy(pkeybuf, "WW-88388-55555-N");
    }
    timePtr = 0;

retryProductKey:
    installKey = 0;

    drawBootScreen();
    drawBasicWindow(22, 2, 50, 14, "Product Key");

 
    term->setCursor(24, 5); term->puts("Please enter your product key below,");
    term->setCursor(24, 6); term->puts("and then press ENTER.");


    while (1) {
        pkeybuf[16] = 0;
        pkeybuf[17] = 0;
        term->setCursor(28, 8); 
        term->puts(pkeybuf);
        term->setCursor(28 + timePtr, 8);
        term->putchar(pkeybuf[timePtr], VgaColour::White, VgaColour::Black);
        term->setCursor(28 + 16, 8);
        term->putchar(' ', VgaColour::White, VgaColour::White);
        term->setCursor(28 + timePtr, 8);

        while (installKey == 0);
        memset(term->keybufferInternal, 0, 16);
        memset(term->keybufferSent, 0, 16);
        if (installKey == 3 || installKey == '\b') {
            do {
                --timePtr;
                if (timePtr == -1) timePtr = strlen(pkeybuf) - 1;
            } while (pkeybuf[timePtr] == '-');

        } else if ((installKey >= '0' && installKey <= '9') || (installKey >= 'A' && installKey <= 'Z') || (installKey >= 'a' && installKey <= 'z') || installKey == ' ' || installKey == 4) {
            if ((installKey >= '0' && installKey <= '9') || (installKey >= 'A' && installKey <= 'Z') || (installKey >= 'a' && installKey <= 'z')) {
                pkeybuf[timePtr] = (installKey >= 'a' && installKey <= 'z') ? installKey - 32 : installKey;
            }

            do {
                ++timePtr;
                if (timePtr >= strlen(pkeybuf)) timePtr = 0;
            } while (pkeybuf[timePtr] == '-');

        } else if (installKey == '\n') {
            bool valid = checkExtendedKey(pkeybuf);

            if (valid) {
                milliTenthSleep(2800);
                drawBootScreen();

                installKey = 0;
                milliTenthSleep(900);
                drawBootScreen();
                milliTenthSleep(4800);
                installKey = 0;
                break;

            } else {
                milliTenthSleep(2800);
                drawBootScreen();

                drawBasicWindowX(22, 2, 50, 14, "Product Key", true);
                term->setCursor(24, 5); 
                term->puts("Please enter your product key below,", VgaColour::Black, VgaColour::LightGrey);
                term->setCursor(24, 6); 
                term->puts("and then press ENTER.", VgaColour::Black, VgaColour::LightGrey);

                term->setCursor(28, 8);
                term->puts(pkeybuf, VgaColour::Black, VgaColour::LightGrey);
                term->setCursor(28 + 16, 8);
                term->putchar(' ', VgaColour::LightGrey, VgaColour::LightGrey);
                term->setCursor(28 + timePtr, 8);

                drawBasicWindow(34, 10, 43, 11, "Invalid Product Key");
                term->setCursor(36, 13); term->puts("The entered product key was invalid.");
                term->setCursor(36, 15); term->puts("Press any key to continue and then");
                term->setCursor(36, 16); term->puts("enter the product key correctly.");

                installKey = 0;
                milliTenthSleep(4500);
                installKey = 0;
                
                while (installKey == 0);

                drawBootScreen();
                milliTenthSleep(6300);

                goto retryProductKey;
            }
        }
        
        installKey = 0;
    }

    if (onlyPkey) return;
    
    drawBootScreen();
    drawBasicWindow(22, 5, 50, 13, "Finalising Installation");

    bootInstallTasks(0);
    int megabytes = Reg::readIntWithDefault((char*) "system", (char*) "@memory:swapfile", 12);
    Virt::setupPageSwapping(megabytes);

    bootInstallTasks(1);
	rmtree("C:/Banana/Registry/System");
	rmtree("C:/Banana/Registry/User");
	mkdir("C:/Banana/Registry/System", 0700);
	mkdir("C:/Banana/Registry/User", 0700);
	copytree("C:/Banana/Registry/DefaultSystem", "C:/Banana/Registry/System");

    bootInstallTasks(2);
    createUser(currName);

    bootInstallTasks(3);
    VgaText::hiddenOut = true;
}

void loadExtensions()
{
    KeSetBootMessage("Loading extensions...");
}

void rgtree(Reghive* reg, int a, int n)
{
    if (a == 1 && n == 0) {
        kprintf("\n\n:\n");
    }
    while (a > 0) {
        char nm[50];
        memset(nm, 0, 50);

        int type = CmGetNameAndTypeFromExtent(reg, a, nm);
        for (int i = 0; i < n; ++i) {
            kprintf(" ");
        }

        kprintf("/%s\n", nm);

        if (type == 0x4E) {
            rgtree(reg, CmEnterDirectory(reg, a), n + 4);
        }
        a = CmGetNext(reg, a);
    }
}

void begin(void* a)
{
    bool firstTime = false;

    File* f = new File("C:/Banana/System/setupisd.one", kernelProcess);
    if (!f) {
        KePanic("SYSINIT FAILURE");
    }
    FileStatus fs = f->open(FileOpenMode::Read);

    if (fs == FileStatus::Success) {
        f->close();
    } else {
        firstTime = true; 
    }
    delete f;

    KeIsPreemptionOn = true;

    if (firstTime) {

        if (sizeof(Extent) != EXTENT_LENGTH) {
            KePanic("EXTENT LENGTH WRONG");
        }

        firstRun(false);

    } else {
        loadExtensions();
    }

    Process* usertask;

    char* argvv[] = { "C:/Banana/System/command.exe", "call", "C:/Banana/System/init.bat", 0 };

    if (firstTime) {
        usertask = new Process("C:/Banana/System/command.exe", nullptr, argvv);
        usertask->createUserThread();

        VgaText::hiddenOut = false;
        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        bootInstallTasks(3);
        VgaText::hiddenOut = true;

        while (1) {
            File* f = new File("C:/DE.BUG", kernelProcess);
            FileStatus fs = f->open(FileOpenMode::Read);
            if (fs == FileStatus::Success) {
                f->close();
                f->unlink();
                delete f;
                break;
            }               
            delete f;
            sleep(1);
        }

        //I think a lot of RAM needs to be freed here...
        {
            //give the cleaner task some time to clear out stuff
            sleep(2);
        }

        VgaText::hiddenOut = false;
        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        bootInstallTasks(4);

        backupTree("C:/Banana/Drivers/", 0xDDDD);
        backupTree("C:/Banana/System/", 0xEEEE);
        backupTree("C:/Banana/Registry/", 0xFFFF);

        bootInstallTasks(5);
        Reghive* reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
        CmCreateDirectory(reg, 0, "BANANA");
        rgtree(reg, 1, 0);
        kprintf("banan is at location %d\n", CmFindObjectFromPath(reg, "BANANA"));
        kprintf("banana is entered at location %d\n", CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")));

        CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "SETUP");
        rgtree(reg, 1, 0);
        kprintf("setup is at location %d\n", CmFindObjectFromPath(reg, "BANANA/SETUP"));
        kprintf("setup is entered at location %d\n", CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")));
        CmClose(reg);
        KePanic("CHECK REGISTRY FILE FOR DEBUG");
        
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "NAME");
        rgtree(reg, 1, 0);
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "COMPANY");
        rgtree(reg, 1, 0);
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "PRODUCTKEY");
        rgtree(reg, 1, 0);
        CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/NAME"), "TEST NAME" /*currName*/);
        rgtree(reg, 1, 0);
        CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/COMPANY"), "TEST COMP" /*currComp*/);
        rgtree(reg, 1, 0);
        CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/PRODUCTKEY"), "WW-88388-55555-N" /*pkeybuf*/);
        
        rgtree(reg, 1, 0);
        
        CmClose(reg);

        //finishing touches go here

        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        term->setCursor(24, 8);
        term->puts("The installation has been completed.\n");
        term->setCursor(24, 10);
        term->puts("Please press ENTER to restart your computer");
        term->setCursor(24, 11);
        term->puts("and start Banana.");

        installKey = 0;
        while (installKey == 0);
        installKey = 0;

        term->setCursor(24, 12);

        computer->close(1, 0, nullptr);
        term->puts("PLEASE MANUALLY RESTART YOUR COMPUTER", VgaColour::Red, VgaColour::White);

    } else {
        Reghive* reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
        char pkey[600];
        CmGetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/PRODUCTKEY"), pkey);
        CmClose(reg);

        if (!checkExtendedKey(pkey)) {
            firstRun(true);
            
            reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
            CmCreateDirectory(reg, 0, "BANANA");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "SETUP");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "PRODUCTKEY");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/PRODUCTKEY"), pkeybuf);
            CmClose(reg);

            setActiveTerminal(term);
            drawBootScreen();
            drawBasicWindow(22, 5, 50, 13, "Product Key Updated");
            term->setCursor(24, 8);
            term->puts("Your product key has been updated.\n");
            term->setCursor(24, 10);
            term->puts("Please press ENTER to restart your computer");
            term->setCursor(24, 11);
            term->puts("and start Banana.");

            installKey = 0;
            while (installKey == 0);
            installKey = 0;

            term->setCursor(24, 12);

            computer->close(1, 0, nullptr);
            term->puts("PLEASE MANUALLY RESTART YOUR COMPUTER", VgaColour::Red, VgaColour::White);
        }

        VgaText::hiddenOut = false;
        usertask = new Process("C:/Banana/System/command.exe");
        setActiveTerminal(usertask->terminal);

        for (int y = 0; y < 25; ++y) {
            for (int x = 0; x < 80; ++x) {
                HalConsoleWriteCharacter(' ', 7, 0, x, y);
            }
        }
       
        usertask->createUserThread();

        int autogui = Reg::readIntWithDefault((char*) "shell", (char*) "autogui", 0);

        extern void startGUIVESA(void* a);
        if (autogui) {
            kprintf("AUTO GUI.\n");
            startGUIVESA(nullptr);
        }

        int wstatus;
        waitTask(usertask->pid, &wstatus, 0);
    }

    computer->close(0, 0, nullptr);
    KePanic("TURN OFF PC");
    while (1);
}