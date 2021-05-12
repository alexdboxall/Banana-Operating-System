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
#include "thr/prcssthr.hpp"
#include "hal/buzzer.hpp"
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
strncpy(
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
                    panic("COULD NOT CREATE");
                } else {
                    copytree(path, npath);
                }

            } else {
                File* f = new File(path, currentTaskTCB->processRelatedTo); //fopen(path, "rb");
                f->open(FILE_OPEN_READ);
                if (!f) {
                    panic("COULD NOT COPY");
                    continue;
                }

                if (f) {
                    File* dest = new File(npath, currentTaskTCB->processRelatedTo);
                    dest->open(FILE_OPEN_WRITE_NORMAL);
                    if (!dest) {
                        panic("COULD NOT COPY");
                        dest->close();
                        continue;
                    }

                    char* m = (char*) malloc(4096);
                    if (!m) {
                        panic("NO MEMORY");
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
                strncpy(ss, dp->d_name, 8);
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
                    panic("COULD NOT COPY");
                    continue;
                }

                if (f) {
                    File* dest = new File(bkupPath, currentTaskTCB->processRelatedTo);
                    dest->open(FILE_OPEN_WRITE_NORMAL);
                    if (!dest) {
                        panic("COULD NOT COPY");
                        dest->close();
                        continue;
                    }

                    kprintf("Copying: %s -> %s\n", path, bkupPath);

                    char m[4096];
                    while (1) {
                        int red;
                        int red2;
                        FileStatus st = f->read(4096, m, &red);
                        kprintf("read  = %d\n", red);
                        if (st != FileStatus::Success) {
                            break;
                        }
                        dest->write(red, m, &red2);
                        kprintf("write = %d\n", red2);
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
void drawBootScreen()
{
    term->setDefaultBgColour(VgaColour::Cyan);
    term->setDefaultFgColour(VgaColour::Black);
    term->clearScreen();
    term->setTitle("");
    term->setTitleColour(VgaColour::Black);
    term->setTitleTextColour(VgaColour::Black);

    for (int y = 0; y < 25; ++y) {
        term->setCursor(0, y);
        for (int x = 0; x < 16; ++x) {
            term->putchar(' ', VgaColour::Black, VgaColour::Black);
        }
    }
    term->setCursor(1, 0);
    term->puts("Checking\n system\n requirements\n\n Legal\n notices\n\n Choosing a\n partition\n\n Formatting\n\n Copying files\n\n Restarting\n your computer\n\n", VgaColour::White, VgaColour::Black);
    term->puts(" Finalising the\n installation", VgaColour::Yellow, VgaColour::Black);
    term->setDefaultBgColour(VgaColour::White);
    term->setDefaultFgColour(VgaColour::Black);
}

void drawBasicWindow(int wx, int wy, int ww, int wh, const char* wtitle)
{
    for (int y = 0; y < wh; ++y) {
        term->setCursor(wx, wy + y);
        for (int x = 0; x < ww; ++x) {
            term->putchar(' ', VgaColour::White, VgaColour::White);
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
            term->putchar('\xDD', VgaColour::Black, VgaColour::White);
        }
    }

    int g = (ww - strlen(wtitle)) / 2 - 1;
    term->setCursor(wx + g, wy);
    for (int j = 0; j < strlen(wtitle); ++j) {
        term->putchar(wtitle[j], VgaColour::White, VgaColour::Blue);
    }
}

#include "hal/keybrd.hpp"

extern void (*guiKeyboardHandler) (KeyboardToken kt, bool* keystates);
volatile char installKey = 0;
void bootInstallKeybrd(KeyboardToken kt, bool* keystates)
{
    if (kt.release) return;
    installKey = kt.halScancode;
}

void bootInstallTasks(int done)
{ 
    term->setCursor(24, 7);
    term->puts("Please wait while the install finishes.");

    term->setCursor(26, 9);
    term->puts(done == 0 ? "\x10 " : "  ");
    term->puts("Allocating the swapfile", done >= 0 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 10);
    term->puts(done == 1 ? "\x10 " : "  ");
    term->puts("Updating the registry", done >= 1 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 11);
    term->puts(done == 2 ? "\x10 " : "  ");
    term->puts("Creating user account", done >= 2 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 12);
    term->puts(done == 3 ? "\x10 " : "  ");
    term->puts("Installing packages", done >= 3 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 13);
    term->puts(done == 4 ? "\x10 " : "  ");
    term->puts("Backing up system files", done >= 4 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);

    term->setCursor(26, 14);
    term->puts(done == 5 ? "\x10 " : "  ");
    term->puts("Finishing touches", done >= 5 ? VgaColour::Black : VgaColour::LightGrey, VgaColour::White);
}

void firstRun()
{
    guiKeyboardHandler = bootInstallKeybrd;

	Krnl::setBootMessage("Setting up the system for the first time");

    VgaText::hiddenOut = false;

    activeTerminal->puts("\n\n\n\n\n\n");
    kernelProcess->terminal->puts("\n\n\n\n\n\n");

    term = new VgaText("Test");
    setActiveTerminal(term);
    drawBootScreen();

    char currName[48] = "Alex";
    char currComp[48] = "";

    int sel = 0;
    drawBasicWindow(22, 2, 50, 13, "Banana Setup");
    term->setCursor(24, 4); term->puts("Please enter your details. Press TAB to switch");
    term->setCursor(24, 5); term->puts("between fields.");
    term->setCursor(24, 7); term->puts("Name");
    term->setCursor(24, 9); term->puts("Company");

    while (1) {
        term->setCursor(33, 7);
        term->puts("                         ", VgaColour::Black, VgaColour::LightGrey);
        term->puts(sel == 0 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);
        term->setCursorX(33);
        term->puts(currName, VgaColour::Black, VgaColour::LightGrey);

        term->setCursor(33, 9);
        term->puts("                         ", VgaColour::Black, VgaColour::LightGrey);
        term->puts(sel == 1 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);
        term->setCursorX(33);
        term->puts(currComp, VgaColour::Black, VgaColour::LightGrey);

        term->setCursor(24, 11);
        term->puts(sel == 2 ? "Press ENTER" : "           ", VgaColour::DarkGrey, VgaColour::White);
      
        term->setCursor(50, 11);
        if (sel != 2) term->puts("   OK   ", VgaColour::White, VgaColour::DarkGrey);
        else          term->puts("   OK   ", VgaColour::White, VgaColour::Blue);
        term->puts(sel == 2 ? "  \x11" : "   ", VgaColour::Black, VgaColour::White);

        if (sel == 0) term->setCursor(33 + strlen(currName), 7);
        if (sel == 1) term->setCursor(33 + strlen(currComp), 9);
        if (sel == 2) term->setCursor(0, 0);

        while (installKey == 0);
        if (installKey == '\t' || installKey == '\n') {
            if (sel == 2) {
                installKey = 0;
                break;
            }
            sel += 1;
            if (sel == 3) sel = 0;

        } else if (installKey >= 32 && installKey < 127) {
            char ss[2];
            ss[0] = installKey;
            ss[1] = 0;
            if (sel == 0 && strlen(currName) < 24) strcat(currName, ss);
            if (sel == 1 && strlen(currComp) < 24) strcat(currComp, ss);

        } else if (installKey == '\b') {
            if (sel == 0 && strlen(currName)) currName[strlen(currName) - 1] = 0;
            if (sel == 1 && strlen(currComp)) currComp[strlen(currComp) - 1] = 0;
        }

        installKey = 0;
    }
    
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
    Krnl::setBootMessage("Loading extensions...");
}

void begin(void* a)
{
    bool firstTime = false;

    File* f = new File("C:/Banana/System/setupisd.one", kernelProcess);
    if (!f) {
        panic("SYSINIT FAILURE");
    }
    FileStatus fs = f->open(FileOpenMode::Read);

    if (fs == FileStatus::Success) {
        f->close();
    } else {
        firstTime = true; 
    }
    delete f;

    if (firstTime) {
        firstRun();

    } else {
        loadExtensions();
    }

    Krnl::preemptionOn = true;

    Process* usertask;

    if (firstTime) {
        char* argv[] = { "C:/Banana/System/command.exe", "call", "C:/Banana/System/init.bat", 0 };
        usertask = new Process("C:/Banana/System/command.exe", nullptr, argv);
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

        //finishing touches go here

        setActiveTerminal(term);
        drawBootScreen();
        drawBasicWindow(22, 5, 50, 13, "Finalising Installation");
        term->setCursor(24, 7);
        term->puts("The installation has been completed.\n");
        term->setCursor(24, 9);
        term->puts("Please press ENTER to restart your computer");
        term->setCursor(24, 10);
        term->puts("and start Banana.");

        installKey = 0;
        while (installKey == 0);
        installKey = 0;

        term->setCursor(24, 11);

        computer->close(1, 0, nullptr);
        term->puts("PLEASE MANUALLY RESTART YOUR COMPUTER", VgaColour::Red, VgaColour::White);

    } else {
        VgaText::hiddenOut = false;
        usertask = new Process("C:/Banana/System/command.exe");
        setActiveTerminal(usertask->terminal);
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
    panic("TURN OFF PC");
    while (1);
}