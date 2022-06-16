#include <stdint.h>

void begin(void*);
void beginx(void* a)
{
    begin(a);
}

#include "main.hpp"

#include "krnl/main.hpp"
#include "krnl/powctrl.hpp"
#include "krnl/intlformat.hpp"
#include "krnl/computer.hpp"
#include "thr/elf.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "krnl/cm.hpp"
#include "thr/prcssthr.hpp"
#include "hal/buzzer.hpp"
#include "hw/cpu.hpp"
#include "hal/clock.hpp"
#include "fs/vfs.hpp"
#include "krnl/random.hpp"

extern "C" {
#include "bcrypt.h"
}
//MAIN SCRIPT

bool safemode = false;

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
    strcat(path, "/Pictures");
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

#define BACKGROUND_COLOUR VgaColour::Cyan
#define SHADOW_COLOUR     VgaColour::Teal

VgaText* term;
bool showSidebar = true;
void drawBootScreen()
{
    term->setDefaultBgColour(safemode ? VgaColour::Black : BACKGROUND_COLOUR);
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
        if (!safemode) term->puts("Checking\n system\n requirements\n\n Legal\n notices\n\n Choosing a\n partition\n\n Formatting\n\n Copying files\n\n Restarting\n your computer\n\n", VgaColour::White, VgaColour::Black);
        term->puts(" Finalising the\n installation", safemode ? VgaColour::White : VgaColour::Yellow, VgaColour::Black);

        if (safemode) {
            term->puts("\n\n\n\n\n\n\n\n   SAFE MODE", safemode ? VgaColour::White : VgaColour::Yellow, VgaColour::Black);
        }
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
        term->putchar(' ', safemode ? VgaColour::Black : VgaColour::Blue, safemode ? VgaColour::Black : VgaColour::Blue);
    }

    term->setCursor(wx + 1, wy + wh);
    for (int x = 0; x < ww; ++x) {
        term->putchar(' ', safemode ? VgaColour::Black : SHADOW_COLOUR, safemode ? VgaColour::Black : SHADOW_COLOUR);
    }

    for (int x = wy; x < wy + wh; ++x) {
        term->setCursor(ww + wx, 1 + x);
        term->putchar(' ', safemode ? VgaColour::Black : SHADOW_COLOUR, safemode ? VgaColour::Black : SHADOW_COLOUR);

        if (x != wy + wh - 1) {
            term->setCursor(wx, 1 + x);
            term->putchar('\xDD', VgaColour::Black, grey ? VgaColour::LightGrey : VgaColour::White);
        }
    }

    int g = (ww - strlen(wtitle)) / 2 - 1;
    term->setCursor(wx + g, wy);
    for (int j = 0; j < strlen(wtitle); ++j) {
        term->putchar(wtitle[j], VgaColour::White, safemode ? VgaColour::Black : VgaColour::Blue);
    }
}

void drawBasicWindow(int wx, int wy, int ww, int wh, const char* wtitle)
{
    drawBasicWindowX(wx, wy, ww, wh, wtitle, false);
}

#include "hal/keybrd.hpp"

extern void (*guiKeyboardHandler) (KeyboardToken kt, bool* keystates);
volatile char installKey = 0;
bool blockUserTyping = false;

/*
sx          SET x
Sxyyy       SETVARxyyy
axx         SETASCII xx
+x          INCVARx
-x          DECVARx
<xy         COPYVARxy
>xy         SUBVARxy
0x          CLEARVARx
c           CLEARKEY
b           BACKSPACE
n           NEWLINE
u           UP
d           DOWN
l           LEFT       
r           RIGHT
p           PAGEUP
P           PAGEDOWN     
e           ESCAPE
t           TAB
T           SHIFTTAB
w           WAITCLEAR
k           READKEY
/           WAITPRESS
Wxx         WAIT (xx * 100) milliseconds
N           NOP
X           TERMINATE
gxxxx       GOTO byte xxxx
{           TYPE        the end of the message is delimited with a }. if you need to type a }, write the first half with this, use the next statement, then use a second { statement to finish the message
q           TYPE }      types a }
fxyyy       WAITFOR X = YYY
Fxyyy       SKIPIF X = YYY (3 digit hex), skips next 5 bytes if true
                    X      
                    0       USERKEY
                    1       USERVAR1
                    2       USERVAR2
                    3       USERVAR3
                    4       TASK NUMBER
                    5       CURSORX
                    6       CURSORY
                    7       SEL
                    8       TZSEL
                    9       SCROLL

*/

char* remoteInstallScript;// = "%W08<15wbwbwbw>15F1000g0004{Alex}wnw<15wbwbwbw>15F1000g0024{Company Name}wnwwnwwnwwnwwnwwnwwnwwnwwnwwnwwnwwnwwnw$X     ";
bool remoteInstall;

int lookupHex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'A' && c <= 'F') return c + 10 - 'A';
    else return c + 10 - 'a';
}

void runRemoteInstall(void* v)
{
    unlockScheduler();

    remoteInstallScript = (char*) 0x2800;

    int remotePos = 0;

    int USERKEY;
    int uvar[3];
    memset(uvar, 0, sizeof(uvar));

    while (1) {
        char c0 = remoteInstallScript[remotePos];
        char c1 = remoteInstallScript[remotePos + 1];
        char c2 = remoteInstallScript[remotePos + 2];
        char c3 = remoteInstallScript[remotePos + 3];
        char c4 = remoteInstallScript[remotePos + 4];

        kprintf("%c: %c%c%c%c\n", c0, c1, c2, c3, c4);

        if (c0 == 's') {
            installKey = c1;
            remotePos += 2;
        } else if (c0 == 'F' || c0 == 'f') {
            int val = 0;
            retry:
            val = lookupHex(c2) * 0x100;
            val += lookupHex(c3) * 0x10;
            val += lookupHex(c4) * 0x1;
            remotePos += 5;

            int comp = 0;
            if (c1 == '0') comp = USERKEY;
            if (c1 == '1') comp = uvar[0];
            if (c1 == '2') comp = uvar[1];
            if (c1 == '3') comp = uvar[2];
            if (c1 == '4') comp = term->cursorX;
            if (c1 == '5') comp = term->cursorY;

            if (c0 == 'F' && comp == val) {
                remotePos += 5;
            } else if (c0 == 'f' && comp != val) {
                milliTenthSleep(100);
                goto retry;
            }

        } else if (c0 == '{') {
            ++remotePos;

            while (true) {
                char c = remoteInstallScript[remotePos++];
                if (c == '}') break;
                installKey = c;
                while (installKey) { milliTenthSleep(100); }
            }

        } else if (c0 == 'q') {
            remotePos += 1;
            installKey = '}';
            while (installKey) { milliTenthSleep(100); }
        } else if (c0 == 'W') {
            int delay = lookupHex(c1) * 0x10;
            delay += lookupHex(c2) * 0x1;
            remotePos += 3;
            kprintf("waiting %d millisec\n", delay * 100);
            milliTenthSleep(delay * 1000);
        } else if (c0 == 'g') {
            int delay = lookupHex(c1) * 0x1000;
            delay += lookupHex(c2) * 0x100;
            delay += lookupHex(c3) * 0x10;
            delay += lookupHex(c4) * 0x1;
            remotePos = delay;
        } else if (c0 == 'N') {
            remotePos += 1;
        } else if (c0 == 'X') {
            remoteInstall = false;
            blockUserTyping = false;
            break;
        } else if (c0 == 'S') {
            uvar[c1 - '1'] = lookupHex(c2) * 0x100;
            uvar[c1 - '1'] += lookupHex(c3) * 0x10;
            uvar[c1 - '1'] += lookupHex(c4) * 0x1;
            remotePos += 5;
        } else if (c0 == '+') {
            uvar[c1 - '1']++;
            remotePos += 2;
        } else if (c0 == '-') {
            uvar[c1 - '1']--;
            remotePos += 2;
        } else if (c0 == '0') {
            uvar[c1 - '1'] = 0;
            remotePos += 2;
        } else if (c0 == '<') {
            int comp = 0;
            if (c2 == '0') comp = USERKEY;
            if (c2 == '1') comp = uvar[0];
            if (c2 == '2') comp = uvar[1];
            if (c2 == '3') comp = uvar[2];
            if (c2 == '5') comp = term->cursorX;
            if (c2 == '6') comp = term->cursorY;
            if (c1 == '1') uvar[0] = comp;
            if (c1 == '2') uvar[1] = comp;
            if (c1 == '3') uvar[2] = comp;
            remotePos += 3;
        } else if (c0 == '>') {
            int comp = 0;
            if (c2 == '0') comp = USERKEY;
            if (c2 == '1') comp = uvar[0];
            if (c2 == '2') comp = uvar[1];
            if (c2 == '3') comp = uvar[2];
            if (c2 == '5') comp = term->cursorX;
            if (c2 == '6') comp = term->cursorY;
            if (c1 == '1') uvar[0] -= comp;
            if (c1 == '2') uvar[1] -= comp;
            if (c1 == '3') uvar[2] -= comp;
            remotePos += 3;
        } else if (c0 == 'c') {
            installKey = 0;
            remotePos += 1;
        } else if (c0 == 'b') {
            installKey = '\b';
            remotePos += 1;
        } else if (c0 == 'n') {
            installKey = '\n';
            remotePos += 1;
        } else if (c0 == '%') {
            blockUserTyping = true;
            ++remotePos;
        } else if (c0 == '$') {
            blockUserTyping = false;
            ++remotePos;
        } else if (c0 == 'u') {
            installKey = 1;
            remotePos += 1;
        } else if (c0 == 'd') {
            installKey = 2;
            remotePos += 1;
        } else if (c0 == 'l') {
            installKey = 3;
            remotePos += 1;
        } else if (c0 == 'r') {
            installKey = 4;
            remotePos += 1;
        } else if (c0 == 'p') {
            installKey = 125;
            remotePos += 1;
        } else if (c0 == 'P') {
            installKey = 126;
            remotePos += 1;
        } else if (c0 == 't') {
            installKey = '\t';
            remotePos += 1;
        } else if (c0 == 'T') {
            installKey = 127;
            remotePos += 1;
        } else if (c0 == 'e') {
            installKey = '\e';
            remotePos += 1;
        } else if (c0 == 'k') {
            USERKEY = installKey;
            remotePos += 1;
        } else if (c0 == 'w') {
            remotePos += 1;
            while (installKey) {
                milliTenthSleep(50);
            }
        } else if (c0 == '/') {
            remotePos += 1;
            while (!installKey) {
                milliTenthSleep(50);
            }
        }
    }

    blockUserTyping = false;

    while (1) {
        sleep(5);
    }
}

void bootInstallKeybrd(KeyboardToken kt, bool* keystates)
{
    if (blockUserTyping) return;

    if (keystates[(int) KeyboardSpecialKeys::Shift] && kt.halScancode == '\t') {
        installKey = 127;
        return;
    }
    if (kt.release) return;
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::Escape) {
        installKey = '\e';
        return;
    }
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
    if (kt.halScancode == (uint16_t) KeyboardSpecialKeys::PageUp) {
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
char currComp[48] = "Company Name";
char passwbufA[80] = "";
char passwbufB[80] = "";
char passwhash[80];
char passwsalt[80];
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
    }

    free(bf);

    return num;
}

extern "C" uint32_t _bcrypt_rand()
{
    return KeRand();
}

int _bcrypt_errno = 0;
int tzsel;
bool createNewUserMode = false;
bool firstTimeEnteringTimezone = true; 
int modesel;
void firstRun(bool onlyPkey)
{
    extern uint32_t keBootSettings;
    remoteInstall = keBootSettings & 32768;
    remoteInstall = false;
    if (remoteInstall) {
        currentTaskTCB->processRelatedTo->createThread(runRemoteInstall, nullptr, 128);
    }

    showSidebar = !onlyPkey;
    if (createNewUserMode) {
        showSidebar = false;
        strcpy(currName, "");
        strcpy(currComp, "");
        strcpy(passwbufA, "");
        strcpy(passwbufB, "");
    }

    guiKeyboardHandler = bootInstallKeybrd;

	KeSetBootMessage("Setting up the system for the first time");

    VgaText::hiddenOut = false;

    activeTerminal->puts("\n\n\n\n\n\n");
    kernelProcess->terminal->puts("\n\n\n\n\n\n");

    term = new VgaText("Test");
    setActiveTerminal(term);
    drawBootScreen();

    int timePtr = 0;
    char dateTime[64];
    char saltbf[100];
    int res;
    int work;
    if (onlyPkey) {
        strcpy(pkeybuf, "AA-00000-00000-A");
    } else {
        strcpy(pkeybuf, "WW-88388-55555-N");
    }

    if (!onlyPkey) {
        int sel;
        int scroll;
        int numEntries;
        int barHeight;
        datetime_t dt;
        scroll = 0;
        tzsel = 0;
        modesel = 0;
    screen1:
        drawBootScreen();
        sel = 0;
        installKey = 0;
        drawBasicWindow(22, 3, 50, 18, createNewUserMode ? "Create New User" : "Banana Setup");
        term->setCursor(24, 6); term->puts("Please enter your details. Press TAB to switch");
        term->setCursor(24, 7); term->puts(!createNewUserMode ? "between fields." : "between fields, or ESC to cancel.");
        term->setCursor(24, 9); term->puts("Name");
        if (!createNewUserMode) {
            term->setCursor(24, 11);
            term->puts("Company");
        }
        term->setCursor(24, 13); term->puts("Password");
        term->setCursor(24, 15); term->puts("Confirm");
        term->setCursor(24, 16); term->puts("password");

        /*
        char passwbufA[48] = "";
char passwbufB[48] = "";
char passwhash[80];*/

        while (1) {

            term->setCursor(33, 9);
            term->puts("                                    ", VgaColour::Black, VgaColour::LightGrey);
            term->puts(sel == 0 ? " \x11" : "   ", VgaColour::Black, VgaColour::White);
            term->setCursorX(33);
            term->puts(currName, VgaColour::Black, VgaColour::LightGrey);

            if (!createNewUserMode) {
                term->setCursor(33, 11);
                term->puts("                                    ", VgaColour::Black, VgaColour::LightGrey);
                term->puts(sel == 1 ? " \x11" : "   ", VgaColour::Black, VgaColour::White);
                term->setCursorX(33);
                term->puts(currComp, VgaColour::Black, VgaColour::LightGrey);
            }

            term->setCursor(33, 13);
            term->puts("                                    ", VgaColour::Black, VgaColour::LightGrey);
            term->puts(sel == 2 ? " \x11" : "   ", VgaColour::Black, VgaColour::White);
            term->setCursorX(33);
            for (int i = 0; i < strlen(passwbufA); ++i) {
                term->puts("*", VgaColour::Black, VgaColour::LightGrey);
            }

            term->setCursor(33, 15);
            term->puts("                                    ", VgaColour::Black, VgaColour::LightGrey);
            term->puts(sel == 3 ? " \x11" : "   ", VgaColour::Black, VgaColour::White);
            term->setCursorX(33);
            for (int i = 0; i < strlen(passwbufB); ++i) {
                term->puts("*", VgaColour::Black, VgaColour::LightGrey);
            }

            term->setCursor(24, 20);
            term->puts(sel == 4 ? "Press ENTER to submit" : "                      ", safemode ? VgaColour::Black : VgaColour::DarkGrey, VgaColour::White);
            //term->setCursor(24, 19);
            //term->puts(sel == 4 ? "" : "           ", VgaColour::DarkGrey, VgaColour::White);

            term->setCursor(60, 20);
            if (sel != 4) term->puts("   OK   ", VgaColour::White, VgaColour::DarkGrey);
            else          term->puts("   OK   ", VgaColour::White, safemode ? VgaColour::Black : VgaColour::Blue);
            term->puts(sel == 4 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);

            if (sel == 0) term->setCursor(33 + strlen(currName), 9);
            if (sel == 1) term->setCursor(33 + strlen(currComp), 11);
            if (sel == 2) term->setCursor(33 + strlen(passwbufA), 13);
            if (sel == 3) term->setCursor(33 + strlen(passwbufB), 15);
            if (sel == 4) term->setCursor(0, 2);

            while (installKey == 0);
            memset(term->keybufferInternal, 0, 16);
            memset(term->keybufferSent, 0, 16);
            if (installKey == '\t' || installKey == '\n') {
                if (sel == 4 && installKey == '\n') {
                    installKey = 0;

                    if (!strcmp(passwbufA, passwbufB)) {

                        if (strlen(currName) < 1) {
                            sel = 0;
                        } else {
                            break;
                        }

                    } else {
                        sel = 2;
                        memset(passwbufA, 0, 48);
                        memset(passwbufB, 0, 48);
                    }
                } else {
                    sel += 1;
                    if (createNewUserMode && sel == 1) sel = 2;
                    if (sel == 5) sel = 0;
                }
                
                milliTenthSleep(300);

            } else if (installKey >= 32 && installKey < 127) {
                char ss[2];
                ss[0] = installKey;
                ss[1] = 0;
                if (sel == 0 && strlen(currName) < 35) {
                    if ((installKey >= 'A' && installKey >= 'Z') || \
                        (installKey >= 'a' && installKey >= 'z') || \
                        (installKey >= '0' && installKey >= '9') || \
                        installKey == '_' || installKey == ' ') {
                        strcat(currName, ss);
                    }
                }
                if (sel == 1 && strlen(currComp) < 35) strcat(currComp, ss);
                if (sel == 2 && strlen(passwbufA) < 35) strcat(passwbufA, ss);
                if (sel == 3 && strlen(passwbufB) < 35) strcat(passwbufB, ss);

            } else if (installKey == '\e' && createNewUserMode) {
                createNewUserMode = false;
                return;

            } else if (installKey == '\b') {
                if (sel == 0 && strlen(currName)) currName[strlen(currName) - 1] = 0;
                if (sel == 1 && strlen(currComp)) currComp[strlen(currComp) - 1] = 0;
                if (sel == 2 && strlen(passwbufA)) passwbufA[strlen(passwbufA) - 1] = 0;
                if (sel == 3 && strlen(passwbufB)) passwbufB[strlen(passwbufB) - 1] = 0;

            } else if (installKey == 127) {
                // Shift + TAB
                sel--;
                if (sel == -1) {
                    sel = 0;
                }
                if (sel == 1 && createNewUserMode) {
                    sel = 0;
                }
                milliTenthSleep(300);
            }

            installKey = 0;
        }

        installKey = 0;
        milliTenthSleep(2000);
        drawBootScreen();

        work = 8;

        _bcrypt_errno = 0;
        res = bcrypt_gensalt(work, saltbf);
        if (res || _bcrypt_errno) {
            sel = 0;
            strcpy(currName, "COULD NOT SAVE");
            strcpy(currComp, "YOUR PASSWORD (A)");
            memset(passwbufA, 0, 80);
            memset(passwbufB, 0, 80);
            goto screen1;
        }        
        strcpy(passwsalt, saltbf);
        res = bcrypt_hashpw(passwbufA, saltbf, passwhash);
        if (res || _bcrypt_errno) {
            sel = 0;
            strcpy(currName, "COULD NOT SAVE");
            strcpy(currComp, "YOUR PASSWORD (B)");
            memset(passwbufA, 0, 80);
            memset(passwbufB, 0, 80);
            goto screen1;
        }

        memset(passwbufA, 0, 80);
        memset(passwbufB, 0, 80);

        if (createNewUserMode) {
            createUser(currName);
            return;
        }

        milliTenthSleep(2000);
    screen2:
        installKey = 0;

        drawBootScreen();
        drawBasicWindow(22, 2, 50, 13, "Date and Time");

        dt = computer->clock->timeInDatetimeUTC();

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

        term->setCursor(17, 24); term->puts("ESC: Go back a screen", safemode ? VgaColour::White : SHADOW_COLOUR, safemode ? VgaColour::Black : BACKGROUND_COLOUR);
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
                    dt.minute = ii;
                    dt.second = ss;
                    dt.hour = hh;
                    dt.day = dd;
                    dt.month = mm;
                    dt.year = yy;
                    computer->clock->setTimeInDatetimeUTC(dt);
                    break;
                }
            } else if (installKey == '\e') {
                goto screen1;
            } 

            milliTenthSleep(500);
            installKey = 0;
        }

        installKey = 0;
        milliTenthSleep(4000);
    screen3:
        installKey = 0;

        if (firstTimeEnteringTimezone) {
            firstTimeEnteringTimezone = false;
            tzsel = 57;
            scroll = 48;
        }

        drawBootScreen();
        drawBasicWindow(18, 1, 60, 20, "Date and Time");
        term->setCursor(20, 4); term->puts("Please select your timezone and then press ENTER.");
        term->setCursor(17, 24); term->puts("ESC: Go back a screen", safemode ? VgaColour::White : SHADOW_COLOUR, safemode ? VgaColour::Black : BACKGROUND_COLOUR);

        numEntries = loadTimezoneStrings();
        barHeight = 15 * 14 / numEntries;

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

            } else if (installKey == '\n') {
                break;
            } else if (installKey == '\e') {
                goto screen2;
            }

            milliTenthSleep(500);
            installKey = 0;
        }
        
      

        installKey = 0;
        milliTenthSleep(4000);
    screen4:
        drawBootScreen();
        milliTenthSleep(7000);
        installKey = 0;

        drawBootScreen();
        drawBasicWindow(20, 3, 55, 16, "User Interface");
        term->setCursor(22, 6); term->puts("Please select the user interface you want Banana");
        term->setCursor(22, 7); term->puts("to boot into by default when you start the computer.");
        term->setCursor(17, 24); term->puts("ESC: Go back a screen", safemode ? VgaColour::White : SHADOW_COLOUR, safemode ? VgaColour::Black : BACKGROUND_COLOUR);

        numEntries = 3;

        char* modeStrings[] = { 
            " Boot to command line               ",
            " Boot to graphical interface (VGA)  ", 
            " Boot to graphical interface (VESA) " };

        while (1) {
            for (int i = 0; i < numEntries; ++i) {
                term->setCursor(22, 9 + i);
                term->puts(modeStrings[i], \
                            i == modesel ? VgaColour::White : VgaColour::Black, \
                            i == modesel ? VgaColour::Black : VgaColour::White);
            }

            while (installKey == 0);
            memset(term->keybufferInternal, 0, 4);
            memset(term->keybufferSent, 0, 4);
            if (installKey == 1) {
                modesel--;
                if (modesel < 0) modesel = 0;

            } else if (installKey == 2) {
                modesel++;
                if (modesel > numEntries - 1) modesel = numEntries - 1;

            } else if (installKey == '\n') {
                break;
            } else if (installKey == '\e') {
                goto screen3;
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

    timePtr = 0;

retryProductKey:
    installKey = 0;

    drawBootScreen();
    drawBasicWindow(22, 2, 50, 14, "Product Key");
    term->setCursor(17, 24); term->puts("ESC: Go back a screen", safemode ? VgaColour::White : SHADOW_COLOUR, safemode ? VgaColour::Black : BACKGROUND_COLOUR);

 
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

        } else if (installKey == '\e') {
            goto screen4;

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

                /*KeBeep(440, 800, true);
                milliTenthSleep(2000);
                KeBeep(330, 800, true);
                milliTenthSleep(2000);
                KeBeep(311 / 2, 2000, true);*/

                // G        1
                // E        1 (but with a Eb in the middle of it) (so like 0.4, 0.2, 0.4)
                // F        1
                // E        1
                //          1
                // G#       1
                // A        0.5
                // low A    4

                KeBeep(392, 600, true);
                KeBeep(330, 320, true);
                KeBeep(311, 80, true);
                KeBeep(330, 320, true);
                KeBeep(349, 800, true);
                KeBeep(330, 800, true);
                milliTenthSleep(8000);
                KeBeep(415, 600, true);
                KeBeep(440, 700, true);
                milliTenthSleep(1000);
                KeBeep(55, 1200, true);

                /*
                KeBeep(311, 670, true);
                milliTenthSleep(1000);
                KeBeep(262, 670, true);
                milliTenthSleep(1000);
                KeBeep(370, 970, true);
                for (int i = 0; i < 12; ++i) {
                    KeBeep(370, 76, true);
                    KeBeep(352, 76, true);
                }
                KeBeep(370, 1000, true);
                milliTenthSleep(1000);
                KeBeep(370 / 8, 400, true);
                */

                installKey = 0;
                milliTenthSleep(500);
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
    kprintf("SYSTEM.DLL TODO: registry read\n");
    int megabytes = 12;// Reg::readIntWithDefault((char*)"system", (char*)"@memory:swapfile", 12);
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
    VgaText::hiddenOut = !safemode;
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

void getRegsafeName(char* in, char* out)
{
    strcpy(out, in);

    for (int i = 0; out[i]; ++i) {
        if (out[i] >= 'a' && out[i] <= 'z') {
            out[i] -= 'a';
            out[i] += 'A';
        } else if (out[i] >= 'A' && out[i] <= 'Z') {

        } else {
            out[i] = 'Z';
        }
    }
}

void begin(void* a)
{
    bool firstTime = false;
    extern uint32_t keBootSettings;
    safemode = keBootSettings & 2;

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

    keIsPreemptionOn = true;

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
    Reghive* reg;
    char regsafename[64];
    char userBasePath[128];
    char pkey[500];
    uint64_t autogui;

    if (firstTime) {
        usertask = new Process("C:/Banana/System/command.exe", nullptr, argvv);
        usertask->createUserThread();

        VgaText::hiddenOut = false;
        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        bootInstallTasks(3);
        VgaText::hiddenOut = !safemode;
        if (safemode) {
            setActiveTerminal(usertask->terminal);
            usertask->terminal->setDefaultBgColour(VgaColour::Black);
            usertask->terminal->setDefaultFgColour(VgaColour::White);
        }
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
            sleep(1);
        }

        VgaText::hiddenOut = false;
        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        bootInstallTasks(4);

        //backupTree("C:/Banana/Drivers/", 0xDDDD);
        //backupTree("C:/Banana/System/", 0xEEEE);
        //backupTree("C:/Banana/Registry/", 0xFFFF);

    createNewUserGoto:

        bootInstallTasks(5);
        reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
        if (!createNewUserMode) CmCreateDirectory(reg, 0, "BANANA");

        getRegsafeName(currName, regsafename);
        kprintf("regsafename = %s\n", regsafename);

        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        kprintf("userBasePath = %s\n", userBasePath);

        if (!createNewUserMode) {
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "SETUP");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "BOOT");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "TIME");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "USERS");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA")), "FILEASSOC");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "OPEN");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "EDIT");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "PRINT");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "ICON");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "DESCR");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "CUSTOMVERB");
            CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC")), "CUSTOMPROG");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/TIME")), "TIMEZONE");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "NAME");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "COMPANY");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/SETUP")), "PRODUCTKEY");
        }
        CmCreateDirectory(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/USERS")), regsafename);
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "SALT");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "PASSWORD");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "DISPLAYNAME");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "DESKTOP");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "DOCUMENTS");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "DOWNLOADS");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "PICTURES");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "MOVIES");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "MUSIC");
        CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, userBasePath)), "RECYCLEBIN");
        if (!createNewUserMode) {
            CmCreateInteger(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/BOOT")), "AUTOGUI", modesel, EXTENT_INTEGER8);
            CmCreateInteger(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/TIME")), "TIMEZONEID", tzsel, EXTENT_INTEGER8);
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/TIME/TIMEZONE"), timezoneStrings[tzsel] + 1);
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/NAME"), currName);
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/COMPANY"), currComp);
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/PRODUCTKEY"), pkeybuf);

            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/ICON")), "TXT");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/DESCR")), "TXT");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/OPEN")), "TXT");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/EDIT")), "TXT");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/PRINT")), "TXT");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/ICON/TXT"), "C:/Banana/Icons/colour/text.tga");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/DESCR/TXT"), "Text Document");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/OPEN/TXT"), "C:/Banana/System/typewriter.app/program.exe");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/EDIT/TXT"), "C:/Banana/System/typewriter.app/program.exe");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/PRINT/TXT"), "C:/Banana/System/typewriter.app/program.exe");

            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/ICON")), "ISO");
            CmCreateString(reg, CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/DESCR")), "ISO");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/ICON/ISO"), "C:/Banana/Icons/colour/cd.tga");
            CmSetString(reg, CmFindObjectFromPath(reg, "BANANA/FILEASSOC/DESCR/ISO"), "Disc Image File");
        }

        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/PASSWORD");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), passwhash);

        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/SALT");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), passwsalt);

        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/DISPLAYNAME");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), currName);


        char userDesktop[256];
        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Desktop");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/DESKTOP");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Documents");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/DOCUMENTS");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Downloads");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/DOWNLOADS");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Pictures");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/PICTURES");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Movies");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/MOVIES");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Music");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/MUSIC");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        strcpy(userDesktop, "C:/Users/");
        strcat(userDesktop, regsafename);
        strcat(userDesktop, "/Trash Bin");
        strcpy(userBasePath, "BANANA/USERS/");
        strcat(userBasePath, regsafename);
        strcat(userBasePath, "/RECYCLEBIN");
        CmSetString(reg, CmFindObjectFromPath(reg, userBasePath), userDesktop);

        CmClose(reg);

       
        if (createNewUserMode) {
            goto finishCreateNewUserGoto;
        } else {
            size_t utc = computer->clock->timeInSecondsUTC();
            KeSetTimezone(tzsel);
            computer->clock->setTimeInSecondsLocal(utc);
        }

        //finishing touches go here

        kprintf("TODO: detect normal kernel vs KRNLP2\n");
        if (0) { //(computer->features.hasSSE || (computer->features.hasMMX && CPU::current()->features.hasPAE)) {
            File* f = new File("C:/Banana/System/KERNEL32.EXE", kernelProcess);
            f->rename("C:/Banana/System/KRNLBKUP.EXE");
            delete f;

            f = new File("C:/Banana/System/KRNLP2.EXE", kernelProcess);
            f->rename("C:/Banana/System/KERNEL32.EXE");
        }

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

        KeRestart();

    } else {
        KeLoadTimezone();
        KeInitialiseLocale();

        reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
       
        CmGetString(reg, CmFindObjectFromPath(reg, "BANANA/SETUP/PRODUCTKEY"), pkey);
        CmGetInteger(reg, CmFindObjectFromPath(reg, "BANANA/BOOT/AUTOGUI"), &autogui);
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

            KeRestart();
        }

        showSidebar = false;
        term = new VgaText("Test");
        setActiveTerminal(term);
        
        int numEntries;
        int usersel;
        int userExtent;

        char* userStrings[32];
        char* userStringsA[32];
        
        usersel = 0;

    selectUsernameStart:
        numEntries = 0;
        installKey = 0;
        memset(userStrings, 0, sizeof(userStrings));
        memset(userStringsA, 0, sizeof(userStringsA));

        reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
        userExtent = CmEnterDirectory(reg, CmFindObjectFromPath(reg, "BANANA/USERS"));
        while (userExtent) {
            char name[80];
            memset(name, 0, 80);
            int type = CmGetNameAndTypeFromExtent(reg, userExtent, name);
            if (type == EXTENT_DIRECTORY) {
                userStringsA[numEntries] = (char*) malloc(80);
                strcpy(userStringsA[numEntries], name);

                char name2[80];
                strcpy(name2, "BANANA/USERS/");
                strcat(name2, name);
                strcat(name2, "/DISPLAYNAME");

                CmGetString(reg, CmFindObjectFromPath(reg, name2), name);

                userStrings[numEntries] = (char*) malloc(80);
                strcpy(userStrings[numEntries], " ");
                strcat(userStrings[numEntries], name);
                while (strlen(userStrings[numEntries]) < 50) {
                    strcat(userStrings[numEntries], " ");
                }

 
                numEntries++;
            }

            userExtent = CmGetNext(reg, userExtent);
        }
        CmClose(reg);

        userStrings[numEntries] = (char*) malloc(80);
        strcpy(userStrings[numEntries], " Create new user...                               ");
        numEntries++;

        guiKeyboardHandler = bootInstallKeybrd;
        char passwbufC[128];

    getUsername:
        installKey = 0;
        drawBootScreen();
        drawBasicWindow(12, 3, 57, 16, "Login");
        term->setCursor(14, 6); term->puts("Please select your username and press ENTER.", VgaColour::Black, VgaColour::White);
        while (1) {
            if (numEntries == 1) {
                usersel = 0;
                break;
            }

            for (int i = 0; i < numEntries; ++i) {
                term->setCursor(15, 8 + i);
                term->puts(userStrings[i], \
                           i == usersel ? VgaColour::White : VgaColour::Black, \
                           i == usersel ? VgaColour::Black : VgaColour::White);
            }
            while (installKey == 0);
            memset(term->keybufferInternal, 0, 4);
            memset(term->keybufferSent, 0, 4);
            if (installKey == 1) {
                usersel--;
                if (usersel < 0) usersel = 0;

            } else if (installKey == 2) {
                usersel++;
                if (usersel > numEntries - 1) usersel = numEntries - 1;

            } else if (installKey == '\n') {
                break;
            }

            milliTenthSleep(500);
            installKey = 0;
        }

        if (usersel == numEntries - 1) {
            createNewUserMode = true;
            firstRun(false);
            if (!createNewUserMode) {
                memset(term->keybufferInternal, 0, 4);
                memset(term->keybufferSent, 0, 4);
                installKey = 0;
                --usersel;
                goto selectUsernameStart;
            }
            goto createNewUserGoto;
        finishCreateNewUserGoto:
            createNewUserMode = false;
            memset(term->keybufferInternal, 0, 4);
            memset(term->keybufferSent, 0, 4);
            installKey = 0;
            goto selectUsernameStart;
        }

        char requiredHash[128];
        char gotSalt[80];
        strcpy(passwbufC, "BANANA/USERS/");
        strcat(passwbufC, userStringsA[usersel]);
        strcat(passwbufC, "/PASSWORD");
        reg = CmOpen("C:/Banana/Registry/System/SYSTEM.REG");
        CmGetString(reg, CmFindObjectFromPath(reg, passwbufC), requiredHash);

        strcpy(passwbufC, "BANANA/USERS/");
        strcat(passwbufC, userStringsA[usersel]);
        strcat(passwbufC, "/SALT");
        CmGetString(reg, CmFindObjectFromPath(reg, passwbufC), gotSalt);

        CmClose(reg);
        memset(passwbufC, 0, 128);

        drawBootScreen();
        drawBasicWindowX(12, 3, 57, 16, "Login", true);
        term->setCursor(14, 6); term->puts("Please select your username and press ENTER.", VgaColour::Black, VgaColour::LightGrey);
        
        if (numEntries > 0) {
            for (int i = 0; i < numEntries; ++i) {
                term->setCursor(15, 8 + i);
                term->puts(userStrings[i], \
                            i == usersel ? VgaColour::LightGrey : VgaColour::Black, \
                            i == usersel ? VgaColour::Black : VgaColour::LightGrey);
            }
        }

        drawBasicWindow(28, 10, 45, 11, "Login");

        bool doPass = true;

        char gotHash[128];
        bcrypt_hashpw(passwbufC, gotSalt, gotHash);
        if (!strcmp(requiredHash, gotHash)) {
            doPass = false;
        }
        memset(gotHash, 0, 128);

        while (doPass) {
            term->setCursor(30, 13);
            term->puts("Please type your password and press ENTER");
            term->setCursor(30, 14);
            term->puts("or press ESC to go back.");

            term->setCursor(30, 16);
            term->puts("                                    ", VgaColour::Black, VgaColour::LightGrey);
            term->setCursorX(30);
            for (int i = 0; i < strlen(passwbufC); ++i) {
                term->puts("*", VgaColour::Black, VgaColour::LightGrey);
            }
         
            term->setCursor(30 + strlen(passwbufC), 16);
            
            while (installKey == 0);
            memset(term->keybufferInternal, 0, 16);
            memset(term->keybufferSent, 0, 16);
            if (installKey == '\n') {
                installKey = 0;
                char gotHash[128];
                bcrypt_hashpw(passwbufC, gotSalt, gotHash);
                kprintf("REQUIRED: %s\nGOT: %s\nSALT: %s\n", requiredHash, gotHash, gotSalt);
                if (!strcmp(requiredHash, gotHash)) {
                    break;
                }
                memset(gotHash, 0, 128);

            } else if (installKey >= 32 && installKey < 127) {
                char ss[2];
                ss[0] = installKey;
                ss[1] = 0;
                if (strlen(passwbufC) < 35) strcat(passwbufC, ss);

            } else if (installKey == '\b') {
                if (strlen(passwbufC)) passwbufC[strlen(passwbufC) - 1] = 0;

            } else if (installKey == '\e') {
                goto getUsername;
            }

            installKey = 0;
        }
        guiKeyboardHandler = nullptr;

        for (int i = 0; i < numEntries; ++i) {
            if (userStrings[i]) {
                free(userStrings[i]);
                userStrings[i] = nullptr;
            }
            if (userStringsA[i]) {
                free(userStringsA[i]);
                userStringsA[i] = nullptr;
            }
        }

        VgaText::hiddenOut = false;
        usertask = new Process("C:/Banana/System/command.exe");
        setActiveTerminal(usertask->terminal);

        for (int y = 0; y < 25; ++y) {
            for (int x = 0; x < 80; ++x) {
                HalConsoleWriteCharacter(' ', 7, 0, x, y);
            }
        }

        extern uint32_t keBootSettings;
        if (safemode) {
            for (int i = 0; " SAFE MODE"[i]; ++i) {
                HalConsoleWriteCharacter(" SAFE MODE"[i], 15, 0, 68 + i, 23);
            }
        }
       
        usertask->createUserThread();

        extern void startGUI(void* a);
        extern void startGUIVESA(void* a);

        if (!safemode) {
            if (autogui == 1) kernelProcess->createThread(startGUI, nullptr, 1);
            if (autogui == 2) kernelProcess->createThread(startGUIVESA, nullptr, 1);
        } 
        
        int wstatus;
        waitTask(usertask->pid, &wstatus, 0);
    }

    computer->close(0, 0, nullptr);
    KePanic("It is safe to turn off your PC");
    while (1);
}
