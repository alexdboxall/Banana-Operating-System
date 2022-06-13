#include "../firmware.h"

#define MAIN_DISK_MEGABYTES 64

#define MAIN_DISK_FIRST_SECTOR 0x3A		//0x48
#define FLOPPY_DISK_FIRST_SECTOR 33

void main();
extern bool floppy;

void _start()
{
	uint8_t* diskNumPtr = (uint8_t*)0x6FFFF;
	floppy = *diskNumPtr == 0 || *diskNumPtr == 1;
	main();
}

bool debug = false;
bool floppy = false;
bool skipFormatting = false;
#define MAX_WINDOWS 4

int currentDiskette = 0;	//zero based

bool isZero(uint32_t lbaOffsetWithinImage)
{
	uint8_t* spot = (uint8_t*)(0x8000 + lbaOffsetWithinImage / 8);
	uint8_t data = *spot;

	int bit = 7 - (lbaOffsetWithinImage % 8);
	return data & (1 << bit);
}


void floppyReadSector(uint32_t imageLBA, uint8_t* data);

void read2KSectorFromInstallMedia(uint32_t sector, uint8_t* data)
{
	if (floppy) {
		sector -= MAIN_DISK_FIRST_SECTOR;
		sector *= 4;

		floppyReadSector(sector + 0, data);
		floppyReadSector(sector + 1, data + 0x200);
		floppyReadSector(sector + 2, data + 0x400);
		floppyReadSector(sector + 3, data + 0x600);

	} else {
		readSectorFromCDROM(sector, data);
	}
}

typedef struct Window
{
	char title[32];

	int x;
	int y;
	int w;
	int h;

	void (*repaint)(struct Window*);

} Window;

Window* windows[MAX_WINDOWS];
bool fadeWindows1And2 = false;

/*
0 = system requirements
1 = partition
2 = formatting
3 = copying
4 = finalising
5 = restart
*/

bool disclaimPart2 = false;

#define PHASE_CHECK_REQ		0
#define PHASE_PARTITION		1
#define PHASE_FORMATTING	2
#define PHASE_COPYING		3
#define PHASE_FINALISING	4
#define PHASE_DONE			5
#define PHASE_LEGAL_1		6

int installPhase = 0;

void drawScreen()
{
	cursorX = 0;
	cursorY = 0;

	writeString("  Banana Setup");

	for (int y = 0; y < 25; ++y) {
		for (int x = 0; x < 16; ++x) {
			writeCharacter(x, y, ' ', TCBlack, TCBlack);
		}
	}

	int x;
	int y = 1;

	{
		char s[] = "Checking\nsystem\nrequirements\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 0 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Legal\nnotices\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 6 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Choosing a\npartition\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 1 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Formatting\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 2 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Copying files\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 3 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Restarting\nyour computer\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 5 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}
	{
		char s[] = "Finalising the\ninstallation\n";
		for (int i = 0, x = 1; s[i]; ++i) { char c = s[i]; if (c == '\n') { x = 1; ++y; } else { writeCharacter(x++, y, c, installPhase == 123 ? TCYellow : TCWhite, TCBlack); } }
		++y;
	}


	for (int y = 1; y < 25; ++y) {
		for (int x = 16; x < 80; ++x) {
			if (debug) {
				writeCharacter(x, y, ' ', TCSky, TCSky);
			} else {
				writeCharacter(x, y, ' ', TCCyan, TCCyan);
			}
		}
	}

	for (int i = 0; i < MAX_WINDOWS; ++i) {
		if (windows[i]) {
			uint8_t bgc = i < 2 && fadeWindows1And2 ? TCLightGrey : TCWhite;

			for (int y = windows[i]->y; y < windows[i]->y + windows[i]->h; ++y) {
				for (int x = windows[i]->x; x < windows[i]->x + windows[i]->w; ++x) {
					writeCharacter(x + 16, y + 1, ' ', bgc, bgc);
				}
			}


			for (int x = windows[i]->x; x < windows[i]->x + windows[i]->w; ++x) {
				writeCharacter(x + 16, windows[i]->y + 1, ' ', TCBlue, TCBlue);
			}

			for (int x = windows[i]->x; x < windows[i]->x + windows[i]->w; ++x) {
				writeCharacter(x + 17, windows[i]->y + 1 + windows[i]->h, ' ', TCTeal, TCTeal);
			}
			for (int x = windows[i]->y; x < windows[i]->y + windows[i]->h; ++x) {
				writeCharacter(16 + windows[i]->w + windows[i]->x, 2 + x, ' ', TCTeal, TCTeal);

				if (x != windows[i]->y + windows[i]->h - 1) writeCharacter(16 + windows[i]->x, 2 + x, '\xDD', TCBlack, bgc);
			}

			int g = (windows[i]->w - __strlen(windows[i]->title)) / 2 - 1;

			for (int j = 0; j < __strlen(windows[i]->title); ++j) {
				writeCharacter(windows[i]->x + 16 + g + j, windows[i]->y + 1, windows[i]->title[j], TCWhite, TCBlue);
			}

			if (windows[i]->repaint) {
				windows[i]->repaint(windows[i]);
			}
		}
	}


}

void windowWrite(Window* w, int x, int y, char* t)
{
	bool q = (windows[0] == w || windows[1] == w) && fadeWindows1And2;

	for (int j = 0; j < __strlen(t); ++j) {
		writeCharacter(w->x + x + j + 18, w->y + y + 3, t[j], TCBlack, q ? TCLightGrey : TCWhite);
	}
}

void windowWriteCol(Window* w, int x, int y, char* t, int col)
{
	bool q = (windows[0] == w || windows[1] == w) && fadeWindows1And2;

	for (int j = 0; j < __strlen(t); ++j) {
		writeCharacter(w->x + x + j + 18, w->y + y + 3, t[j], col, q ? TCLightGrey : TCWhite);
	}
}


void reallyQuitRepaint(Window* w)
{
	windowWrite(w, 0, 0, "To quit   setup, press ENTER");
	windowWrite(w, 0, 1, "To resume setup, press ESC");
}

void reallyWipeRepaint(Window* w)
{
	windowWrite(w, 0, 0, "To ERASE ALL DATA, hold the");
	windowWrite(w, 0, 1, "shift key and press X");
	windowWrite(w, 0, 2, "(this action can't be undone)");
	windowWrite(w, 0, 4, "To cancel, press ESC or ENTER");
}


void initWinRepaint(Window* w)
{
	windowWrite(w, 0, 0, "Welcome to Banana Setup");
	windowWrite(w, 0, 2, "Congratulations on choosing Banana, the");
	windowWrite(w, 0, 3, "operating system most likely cause you great");
	windowWrite(w, 0, 4, "pain!");

	windowWrite(w, 0, 6, "Setup will determine if Banana can run on this");
	windowWrite(w, 0, 7, "computer, and then install Banana onto it.");

	windowWrite(w, 0, 12, "To proceed, press ENTER");
	windowWrite(w, 0, 13, "To turn back before it's too late, press ESC");
}

void initWinRepaint2(Window* w)
{
	windowWrite(w, 0, 0, "Some tests will now be run to test if your");
	windowWrite(w, 0, 1, "computer can run Banana.");

	windowWrite(w, 0, 12, "To proceed, press ENTER");
	windowWrite(w, 0, 13, "To cancel the installation, press ESC");
}


void ramTest1(Window* w)
{
	windowWrite(w, 0, 0, "Please wait while Setup checks your");
	windowWrite(w, 0, 1, "computer's hardware configuration.");

	windowWrite(w, 0, 5, "Installed RAM...");
}


char ramStr[7];
void ramTest2(Window* w)
{
	windowWrite(w, 0, 0, "On your system there are: ");
	windowWrite(w, 0, 2, ramStr);
	windowWrite(w, 0, 4, "megabytes of RAM installed.");

	windowWrite(w, 0, 12, "To continue, press ENTER");
	windowWrite(w, 0, 13, "To cancel the installation, press ESC");
}

void disclaimer(Window* w)
{
	windowWriteCol(w, 0, 0, "Please read the following terms:", TCRed);
	windowWrite(w, 0, 1, "This software is provided by the copyright holders");
	windowWrite(w, 0, 2, "and contributors \"AS IS\" and any express or implied");
	windowWrite(w, 0, 3, "warranties, including, but not limited to, the");
	windowWrite(w, 0, 4, "implied warranties of merchantability and fitness for");
	windowWrite(w, 0, 5, "a particular purpose are discliamed. In no event shall");
	windowWrite(w, 0, 6, "the copyright owner or contributors be liable for any");
	windowWrite(w, 0, 7, "direct, indirect, incidental, special, exemplary, or");
	windowWrite(w, 0, 8, "consequential damages (including, but not limited to,");
	windowWrite(w, 0, 9, "loss of data; or hardware damage; or personal injury)");
	windowWrite(w, 0, 10, "however caused and on any theory of liability, whether");
	windowWrite(w, 0, 11, "in contract, strict liability, or tort (including");
	windowWrite(w, 0, 12, "negligence or otherwise) arising in any way out of the");
	windowWrite(w, 0, 13, "use of this software, even if advised of the");
	windowWrite(w, 0, 14, "possibility of such damage.");
	windowWriteCol(w, 0, 16, "To install and/or use this software you must agree to ", TCBlue);

	if (disclaimPart2) {
		windowWriteCol(w, 0, 17, "the above terms. Press ENTER to install, or ESC to quit.", TCBlue);
	} else {
		windowWriteCol(w, 0, 17, "the above terms.", TCBlue);
	}
}

void disclaimer3(Window* w)
{
	windowWriteCol(w, 0, 0, "License Agreement", TCRed);
	windowWrite(w, 0, 2, "This work is licensed under the Creative Commons");
	windowWrite(w, 0, 3, "Attribution-NonCommercial 4.0");
	windowWrite(w, 0, 4, "International License.");
	windowWrite(w, 0, 6, "To view a summary of this license, please visit:");
	windowWrite(w, 0, 7, "http://creativecommons.org/licenses/by-nc/4.0/");
	windowWriteCol(w, 0, 9, "To read the full license, press S", TCBlue);

	windowWrite(w, 0, 11, "Portions of this software use open source libraries");
	windowWrite(w, 0, 12, "and code. See C:/Banana/Legal/COPYRIGHT for details.");
	windowWrite(w, 0, 13, "This file contains no additional terms to agree to.");

	windowWriteCol(w, 0, 16, "To install and/or use this software you must agree to ", TCBlack);
	windowWriteCol(w, 0, 17, "the above terms. Press ENTER to install, or ESC to quit.", TCBlack);
}

void disclaimer2(Window* w)
{
	windowWriteCol(w, 0, 0, "DANGER!", TCRed);
	windowWrite(w, 0, 2, "This is software is to be used at the user's own risk.");
	windowWrite(w, 0, 4, "Installing Banana will likely cause irreversible data");
	windowWrite(w, 0, 5, "loss, even on other partitions. Expect that all data");
	windowWrite(w, 0, 6, "(including files, programs and other operating");
	windowWrite(w, 0, 7, "systens) on the computer be irreversibly erased.");

	windowWrite(w, 0, 9, "Although they have never happened, it is possible that");
	windowWrite(w, 0, 10, "the following could occur:");
	windowWriteCol(w, 0, 11, "   - Irreversible damage to the computer's hardware;", TCBlue);
	windowWriteCol(w, 0, 12, "     including monitor failures and fire risks", TCBlue);
	windowWrite(w, 0, 14, "The user must accept the risks to install and/or");

	if (disclaimPart2) {
		windowWrite(w, 0, 15, "use this software. To accept the risks and install");
		windowWrite(w, 0, 16, "this software, press ENTER. Otherwise, press ESC.");
	} else {
		windowWrite(w, 0, 15, "use this software.");
	}
}

void lackMath(Window* w)
{
	windowWrite(w, 0, 0, "Your computer does not have a math");
	windowWrite(w, 0, 1, "processor.");

	windowWrite(w, 0, 3, "Some functionality may not work correctly");
	windowWrite(w, 0, 4, "until it is installed. Some programs may");
	windowWrite(w, 0, 5, "not be able to run, or they may be unstable.");

	windowWrite(w, 0, 11, "To cancel the installation, press ESC");
	windowWrite(w, 0, 13, "To proceed regardless, press ENTER");
}

void lackPent(Window* w)
{
	windowWrite(w, 0, 0, "Your CPU is not Pentium compatible.");
	windowWrite(w, 0, 2, "Banana is designed to run on Pentium or");
	windowWrite(w, 0, 3, "newer computers. If you wish to continue");
	windowWrite(w, 0, 4, "installation, some features may not work or");
	windowWrite(w, 0, 5, "be available, and the system may be sluggish");
	windowWrite(w, 0, 6, "and less stable.");

	windowWrite(w, 0, 11, "To cancel the installation, press ESC");
	windowWrite(w, 0, 13, "To proceed regardless, press ENTER");
}

void lackRAMSoft(Window* w)
{
	windowWrite(w, 0, 0, "Your computer may not enough RAM");
	windowWrite(w, 0, 1, "run Banana.");
	windowWrite(w, 0, 3, "It is recommended to have at least 8 MB");
	windowWrite(w, 0, 4, "of RAM to use Banana.");

	windowWrite(w, 0, 11, "To cancel the installation, press ESC");
	windowWrite(w, 0, 13, "To proceed regardless, press ENTER");
}

void lackRAM(Window* w)
{
	windowWrite(w, 0, 0, "There is not enough RAM in your computer to");
	windowWrite(w, 0, 1, "run Banana.");
	windowWrite(w, 0, 3, "Banana requires at least 8 MB");
	windowWrite(w, 0, 4, "of RAM to run.");

	windowWrite(w, 0, 13, "To cancel the installation, press ESC");
}

#define MAIN_LAYER 0
#define PART_SIZE_LAYER 2
#define EXIT_POPUP 3


void guiDisk1(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #1");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk2(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #2");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk3(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #3");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk4(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #4");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk5(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #5");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk6(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #6");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk7(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #7");
	windowWrite(w, 0, 1, "and press ENTER");
}

void guiDisk8(Window* w)
{
	windowWrite(w, 0, 0, "Please insert DISKETTE #8");
	windowWrite(w, 0, 1, "and press ENTER");
}

void (*guiDisketteTable[8])(Window*) = {
	guiDisk1, guiDisk2, guiDisk3, guiDisk4,
	guiDisk5, guiDisk6, guiDisk7, guiDisk8,
};

int bufferBase = -188;

int nonZeroSectorsWrittenSoFar = 0;
int zeroSectorsWrritenSoFar = 0;

//uint8_t floppyBuffer[16 * 512];
void floppyReadSector(uint32_t imageLBA, uint8_t* data)
{
	if (isZero(imageLBA)) {
		for (int i = 0; i < 512; ++i) {
			data[i] = 0;
		}
		++zeroSectorsWrritenSoFar;
		return;
	}

	static int highestInputLBA = 0;
	static int matchingOutputLBA = 0;

	int actualLBA = 0;
	int i = 0;

	if (imageLBA > highestInputLBA) {
		i = highestInputLBA;
		actualLBA = matchingOutputLBA;
	}

	for (; i < imageLBA; ++i) {
		if (!isZero(i)) {
			actualLBA++;
		}
	}

	if (imageLBA > highestInputLBA) {
		highestInputLBA = imageLBA;
		matchingOutputLBA = actualLBA;
	}

	int floppySector = (actualLBA % 2600) + FLOPPY_DISK_FIRST_SECTOR;
	int floppyNum = actualLBA / 2600;

	if (currentDiskette != floppyNum) {
		fadeWindows1And2 = true;
		bufferBase = -188;


		readSector(0, (void*)0x7C000, getFirstFloppy());
		uint8_t* pos = (uint8_t*)(0x7C000 + 511);

		bool skip = false;

		if (floppyNum == 0 && (*pos == 0xAA || *pos == 0x55)) {
			fadeWindows1And2 = false;
			currentDiskette = floppyNum;
			skip = true;

		} else if (*pos == floppyNum - 1) {
			fadeWindows1And2 = false;
			currentDiskette = floppyNum;
			skip = true;

		} else {

		}

		if (!skip) {
			Window wx;
			wx.x = 8;
			wx.y = 4;
			wx.w = 32;
			wx.h = 10;
			if (floppyNum < 0 || floppyNum > 7) {
				wx.repaint = guiDisketteTable[0];
				__memcpy(wx.title, "  ERROR ", __strlen("  ERROR "));
				windows[EXIT_POPUP] = &wx;
				drawScreen();
				beep(440);
				millisleep(500);
				beep(0);
				while (1);
			}

			wx.repaint = guiDisketteTable[floppyNum];
			__memcpy(wx.title, "    Insert Floppy  ", __strlen("    Insert Floppy  "));
			windows[EXIT_POPUP] = &wx;
			drawScreen();

			int debugCnt = 0;

			beep(440);
			millisleep(500);
			beep(0);

			while (1) {
				char c = blockingKeyboard();

				if (c == '\n') {
					readSector(0, (void*)0x7C000, getFirstFloppy());
					uint8_t* pos = (uint8_t*)(0x7C000 + 511);

					if (floppyNum == 0 && (*pos == 0xAA || *pos == 0x55)) {
					} else if (*pos == floppyNum + 1) {
					} else {
						c = ' ';
						if (debug) {
							debugCnt++;
							if (debugCnt > 2) {
								fadeWindows1And2 = false;
								currentDiskette = floppyNum;
								windows[EXIT_POPUP] = 0;
								drawScreen();
								break;
							}
						}
						continue;
					}

					fadeWindows1And2 = false;
					currentDiskette = floppyNum;
					windows[EXIT_POPUP] = 0;
					drawScreen();
					break;
				}
			}
		}
	}

	uint8_t* floppyBuffer = (uint8_t*)0x7C000;

	if (!(floppySector >= bufferBase && floppySector < bufferBase + 18)) {
		bufferBase = floppySector / 18;
		bufferBase *= 18;
		int success = readSector(bufferBase, floppyBuffer, getFirstFloppy());
		if (!success) {
			writeHex(success);
			writeString(", ");
		}
	}

	__memcpy(data, floppyBuffer + (floppySector - bufferBase) * 0x200, 0x200);
	++nonZeroSectorsWrittenSoFar;
}

void exitInstall()
{
	setFgCol(TCLightGrey);
	clearScreenToColour(TCBlack);
	writeString("\n  Please restart your computer.");
	while (1);
}

char fulltext[] = "\
 Creative Commons Attribution-NonCommercial 4.0 International Public License\n\
 By exercising the Licensed Rights (defined below), You acceptand agree to be \n\
 bound by the terms and conditions of this \n\
 Creative Commons Attribution - NonCommercial 4.0 International Public License\n\
 (\"Public License\"). To the extent this Public License may be interpreted as\n\
 a contract, You are granted the Licensed Rights in consideration of Your \n\
 acceptance of these termsand conditions, and the Licensor grants You such \n\
 rights in consideration of benefits the Licensor receives from making the\n\
 Licensed Material available under these termsand conditions.\n\
\n\
 Section 1 - Definitions.\n\
\n\
 a. Adapted Material means material subject to Copyright and Similar Rights\n\
  that is derived from or based upon the Licensed Material and in which the\n\
  Licensed Material is translated, altered, arranged, transformed, or otherwise\
   modified in a manner requiring permission under the Copyright and Similar \n\
  Rights held by the Licensor. For purposes of this Public License, where the\n\
  Licensed Material is a musical work, performance, or sound recording, Adapted\
   Material is always produced where the Licensed Material is synched in timed\n\
  relation with a moving image.\n\
 b. Adapter's License means the license You apply to Your Copyright and Similar\
   Rights in Your contributions to Adapted Material in accordance with the \n\
  terms and conditions of this Public License.\n\
 c. Copyright and Similar Rights means copyright and /or similar rights closely\
   related to copyright including, without limitation, performance, broadcast,\n\
  sound recording, and Sui Generis Database Rights, without regard to how the\n\
  rights are labeled or categorized.For purposes of this Public License, the \n\
  rights specified in Section 2(b) (1) - (2) are not Copyright and Similar \n\
  Rights.\n\
 d. Effective Technological Measures means those measures that, in the absence\n\
  of proper authority, may not be circumvented under laws fulfilling \n\
  obligations under Article 11 of the WIPO Copyright Treaty adopted on \n\
  December 20, 1996, and /or similar international agreements.\n\
 e. Exceptions and Limitations means fair use, fair dealing, and /or any other\n\
  exception or limitation to Copyright and Similar Rights that applies to Your\n\
  use of the Licensed Material.\n\
 f. Licensed Material means the artistic or literary work, database, or other \n\
  material to which the Licensor applied this Public License.\n\
 g. Licensed Rights means the rights granted to You subject to the terms and \n\
  conditions of this Public License, which are limited to all Copyright and\n\
  Similar Rights that apply to Your use of the Licensed Material and that the\n\
  Licensor has authority to license.\n\
 h. Licensor means the individual(s) or entity(ies) granting rights under this\n\
  Public License.\n\
 i. NonCommercial means not primarily intended for or directed towards \n\
  commercial advantage or monetary compensation.For purposes of this Public \n\
  License, the exchange of the Licensed Material for other material subject to\n\
  Copyright and Similar Rights by digital file - sharing or similar means is \n\
  NonCommercial provided there is no payment of monetary compensation in \n\
  connection with the exchange.\n\
 j. Share means to provide material to the public by any means or process that\n\
  requires permission under the Licensed Rights, such as reproduction, public \n\
  display, public performance, distribution, dissemination, communication, or \n\
  importation, and to make material available to the public including in ways \n\
  that members of the public may access the material from a placeand at a time\n\
  individually chosen by them.\n\
 k. Sui Generis Database Rights means rights other than copyright resulting \n\
  from Directive 96/9/EC of the European Parliament and of the Council of \n\
  11 March 1996 on the legal protection of databases, as amended and/or \n\
  succeeded, as well as other essentially equivalent rights anywhere in the \n\
  world.\n\
 l. You means the individual or entity exercising the Licensed Rights under \n\
  this Public License. Your has a corresponding meaning.\n\
\n\
 Section 2 - Scope.\n\
\n\
 a. License grant.\n\
  1. Subject to the terms and conditions of this Public License, the Licensor\n\
   hereby grants You a worldwide, royalty-free, non-sublicensable, \n\
   non-exclusive, irrevocable license to exercise the Licensed Rights in the\n\
   Licensed Material to:\n\
   A. reproduce and Share the Licensed Material, in whole or in part, for \n\
      NonCommercial purposes only; and\n\
   B. produce, reproduce, and Share Adapted Material for NonCommercial\n\
      purposes only.\n\
  2. Exceptions and Limitations. For the avoidance of doubt, where Exceptions\n\
   and Limitations apply to Your use, this Public License does not apply, and\n\
   You do not need to comply with its terms and conditions.\n\
  3. Term. The term of this Public License is specified in Section 6(a).\n\
  4. Media and formats; technical modifications allowed. The Licensor \n\
   authorizes You to exercise the Licensed Rights in all media and formats\n\
   whether now known or hereafter created, and to make technical modifications\n\
   necessary to do so. The Licensor waives and/or agrees not to assert any \n\
   right or authority to forbid You from making technical modifications \n\
   necessary to exercise the Licensed Rights, including technical modifications\
    necessary to circumvent Effective Technological Measures. For purposes of\n\
   this Public License, simply making modifications authorized by this \n\
   Section 2(a) (4) never produces Adapted Material.\n\
  5. Downstream recipients.\n\
   A. Offer from the Licensor - Licensed Material. Every recipient of the\n\
    Licensed Material automatically receives an offer from the Licensor to \n\
    exercise the Licensed Rights under the terms and conditions of this Public\n\
    License.\n\
   B. No downstream restrictions. You may not offer or impose any additional \n\
    or different terms or conditions on, or apply any Effective Technological\n\
    Measures to, the Licensed Material if doing so restricts exercise of the\n\
    Licensed Rights by any recipient of the Licensed Material.\n\
  6. No endorsement. Nothing in this Public License constitutes or may be \n\
   construed as permission to assert or imply that You are, or that Your use of\
    the Licensed Material is, connected with, or sponsored, endorsed, or granted\
    official status by, the Licensor or others designated to receive attribution\
    as provided in Section 3(a) (1)(A)(i).\n\
\n\
  b. Other rights.\n\
   1. Moral rights, such as the right of integrity, are not licensed under \n\
    this Public License, nor are publicity, privacy, and /or other similar \n\
    personality rights; however, to the extent possible, the Licensor waives\n\
    and/or agrees not to assert any such rights held by the Licensor to the\n\
    limited extent necessary to allow You to exercise the Licensed Rights, \n\
    but not otherwise.\n\
   2. Patent and trademark rights are not licensed under this Public License.\n\
   3. To the extent possible, the Licensor waives any right to collect \n\
    royalties from You for the exercise of the Licensed Rights, whether \n\
    directly or through a collecting society under any voluntary or waivable\n\
    statutory or compulsory licensing scheme.In all other cases the Licensor\n\
    expressly reserves any right to collect such royalties, including when\n\
    the Licensed Material is used other than for NonCommercial purposes.\n\
\n\
 Section 3 - License Conditions.\n\
\n\
 Your exercise of the Licensed Rights is expressly made subject to the \n\
 following conditions.\n\
\n\
 a. Attribution.\n\
  1. If You Share the Licensed Material(including in modified form), You must:\n\
   A. retain the following if it is supplied by the Licensor with the Licensed\n\
    Material:\n\
     i. identification of the creator(s) of the Licensed Material and any \n\
      others designated to receive attribution, in any reasonable manner \n\
      requested by the Licensor (including by pseudonym if designated);\n\
     ii. a copyright notice;\n\
     iii. a notice that refers to this Public License;\n\
     iv. a notice that refers to the disclaimer of warranties;\n\
     v. a URI or hyperlink to the Licensed Material to the extent reasonably\n\
      practicable;\n\
   B. indicate if You modified the Licensed Materialand retain an indication\n\
    of any previous modifications; and\n\
   C. indicate the Licensed Material is licensed under this Public License, \n\
    and include the text of, or the URI or hyperlink to, this Public License.\n\
  2. You may satisfy the conditions in Section 3(a) (1) in any reasonable\n\
   manner based on the medium, means, and context in which You Share the \n\
   Licensed Material. For example, it may be reasonable to satisfy the \n\
   conditions by providing a URI or hyperlink to a resource that includes \n\
   the required information.\n\
  3. If requested by the Licensor, You must remove any of the information\n\
   required by Section 3(a) (1)(A) to the extent reasonably practicable.\n\
  4. If You Share Adapted Material You produce, the Adapter's License You \n\
   apply must not prevent recipients of the Adapted Material from complying\n\
   with this Public License.\n\
\n\
 Section 4 - Sui Generis Database Rights.\n\
\n\
 Where the Licensed Rights include Sui Generis Database Rights that apply to\n\
 Your use of the Licensed Material:\n\
\n\
  a. for the avoidance of doubt, Section 2(a) (1) grants You the right to \n\
   extract, reuse, reproduce, and Share all or a substantial portion of the\n\
   contents of the database for NonCommercial purposes only;\n\
  b. if You include all or a substantial portion of the database contents in \n\
   a database in which You have Sui Generis Database Rights, then the database\n\
   in which You have Sui Generis Database Rights(but not its individual \n\
   contents) is Adapted Material; and\n\
  c. You must comply with the conditions in Section 3(a) if You Share all or a\n\
   substantial portion of the contents of the database.\n\
\n\
 For the avoidance of doubt, this Section 4 supplements and does not replace \n\
 Your obligations under this Public License where the Licensed Rights include\n\
 other Copyright and Similar Rights.\n\
\n\
 Section 5 - Disclaimer of Warranties and Limitation of Liability.\n\
\n\
 a. Unless otherwise separately undertaken by the Licensor, to the extent \n\
  possible, the Licensor offers the Licensed Material as - is and \n\
  as - available, and makes no representations or warranties of any kind \n\
  concerning the Licensed Material, whether express, implied, statutory, or \n\
  other. This includes, without limitation, warranties of title,\n\
  merchantability, fitness for a particular purpose, non - infringement, \n\
  absence of latent or other defects, accuracy, or the presence or absence of\n\
  errors, whether or not known or discoverable.Where disclaimers of warranties\n\
  are not allowed in full or in part, this disclaimer may not apply to You.\n\
 b. To the extent possible, in no event will the Licensor be liable to You \n\
  on any legal theory (including, without limitation, negligence) or otherwise\n\
  for any direct, special, indirect, incidental, consequential, punitive, \n\
  exemplary, or other losses, costs, expenses, or damages arising out of this\n\
  Public License or use of the Licensed Material, even if the Licensor has been\
   advised of the possibility of such losses, costs, expenses, or damages. Where\
    a limitation of liability is not allowed in full or in part, this limitation\n\
  may not apply to You.\n\
 c. The disclaimer of warranties and limitation of liability provided above \n\
  shall be interpreted in a manner that, to the extent possible, most closely\n\
  approximates an absolute disclaimerand waiver of all liability.\n\
\n\
 Section 6 - Term and Termination.\n\
\n\
 a. This Public License applies for the term of the Copyright and Similar\n\
  Rights licensed here. However, if You fail to comply with this Public \n\
  License, then Your rights under this Public License terminate automatically.\n\
 b. Where Your right to use the Licensed Material has terminated under \n\
  Section 6(a), it reinstates:\n\
   1. automatically as of the date the violation is cured, provided it is \n\
    cured within 30 days of Your discovery of the violation; or\n\
   2. upon express reinstatement by the Licensor.\n\
  For the avoidance of doubt, this Section 6(b) does not affect any right\n\
  the Licensor may have to seek remedies for Your violations of this Public \n\
  License.\n\
 c. For the avoidance of doubt, the Licensor may also offer the Licensed \n\
  Material under separate terms or conditions or stop distributing the \n\
  Licensed Material at any time; however, doing so will not terminate this\n\
  Public License.\n\
 d. Sections 1, 5, 6, 7, and 8 survive termination of this Public License.\n\
\n\
 Section 7 - Other Terms and Conditions.\n\
\n\
 The Licensor shall not be bound by any additional or different terms or \n\
 conditions communicated by You unless expressly agreed.\n\
 Any arrangements, understandings, or agreements regarding the Licensed \n\
 Material not stated herein are separate from and independent of the terms\n\
 and conditions of this Public License.\n\
\n\
 Section 8 - Interpretation.\n\
\n\
 a. For the avoidance of doubt, this Public License does not, and shall not be\n\
  interpreted to, reduce, limit, restrict, or impose conditions on any use of\n\
  the Licensed Material that could lawfully be made without permission under \n\
  this Public License.\n\
 b. To the extent possible, if any provision of this Public License is deemed \n\
  unenforceable, it shall be automatically reformed to the minimum extent\n\
  necessary to make it enforceable.If the provision cannot be reformed, it \n\
  shall be severed from this Public License without affecting the\n\
  enforceability of the remaining termsand conditions.\n\
 c. No term or condition of this Public License will be waived and no failure\n\
  to comply consented to unless expressly agreed to by the Licensor.\n\
 d. Nothing in this Public License constitutes or may be interpreted as a\n\
  limitation upon, or waiver of, any privilegesand immunities that apply to\n\
  the Licensor or You, including from the legal processes of any jurisdiction\n\
  or authority.\n\n\
  **END OF LICENSE**\n\n\n      Press ESC to close the license page.\n";

bool displayLicensePage(int pg)
{
	setFgCol(TCLightGrey);
	clearScreenToColour(TCBlack);

	char ssstrp[] = "  ESC: Close the license     ENTER: Next page      BACKSPACE: Previous page    ";
	for (int i = 0; ssstrp[i]; ++i) {
		writeCharacter(i, 23, ssstrp[i], TCBlack, TCLightGrey);
	}
	writeCharacter(2, 24, 'P', TCLightGrey, TCBlack);
	writeCharacter(3, 24, 'a', TCLightGrey, TCBlack);
	writeCharacter(4, 24, 'g', TCLightGrey, TCBlack);
	writeCharacter(5, 24, 'e', TCLightGrey, TCBlack);

	if (pg > 8) writeCharacter(7, 24, (pg + 1) / 10 + '0', TCLightGrey, TCBlack);
	writeCharacter(8, 24, (pg + 1) % 10 + '0', TCLightGrey, TCBlack);
	writeCharacter(9, 24, '/', TCLightGrey, TCBlack);
	writeCharacter(10, 24, '1', TCLightGrey, TCBlack);
	writeCharacter(11, 24, '3', TCLightGrey, TCBlack);
	cursorY = 1;

	int newlines = 0;
	bool display = false;
	int x = 0;
	int y = 0;
	for (int i = 0; fulltext[i]; ++i) {
		if (newlines == pg * 18) display = true;
		if (newlines == pg * 18 + 18) return true;

		if (fulltext[i] == '\n') {
			newlines++;
			if (display) {
				cursorX = 0;
				cursorY++;
			}
		} else if (display) {
			writeCharacter(cursorX++, cursorY, fulltext[i], TCLightGrey, TCBlack);
			if (cursorX == 80) {
				cursorX = 0;
				cursorY++;
			}
		}
	}
	return false;
}

void licenseSummary()
{
	int page = 0;

	displayLicensePage(page);

	int lastPage = -1;

	while (1) {
		char c = blockingKeyboard();
		if (c == '\e') {
			drawScreen();
			return;
		}
		if (c == '\n' && page != lastPage) {
			page++;
			bool did = displayLicensePage(page);
			if (!did) {
				lastPage = page;
			}
		}
	}
}

void reallyQuit()
{
	fadeWindows1And2 = true;

	Window wx;
	wx.x = 8;
	wx.y = 4;
	wx.w = 32;
	wx.h = 10;
	wx.repaint = reallyQuitRepaint;
	__memcpy(wx.title, "  Confirmation ", __strlen("  Confirmation "));
	windows[EXIT_POPUP] = &wx;
	drawScreen();

	while (1) {
		char c = blockingKeyboard();
		if (c == '\n') {
			exitInstall();

		} else if (c == '\e') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			drawScreen();
			return;
		}
	}
}


void reallyWipe()
{
	fadeWindows1And2 = true;

	Window wx;
	wx.x = 8;
	wx.y = 4;
	wx.w = 32;
	wx.h = 10;
	wx.repaint = reallyWipeRepaint;
	__memcpy(wx.title, "  Confirmation ", __strlen("  Confirmation "));
	windows[EXIT_POPUP] = &wx;
	drawScreen();

	while (1) {
		char c = blockingKeyboard();
		if (c == '\e' || c == '\e') {
			exitInstall();

		} else if (c == 'X') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			drawScreen();
			return;
		}
	}
}


#define PORT 0x3f8          // COM1

int serial_received()
{
	return inb(PORT + 5) & 1;
}

char read_serial()
{
	while (serial_received() == 0);
	return inb(PORT);
}

int init_serial()
{
	outb(PORT + 1, 0x00);    // Disable all interrupts
	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
	outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

	// Check if serial is faulty (i.e: not same byte as sent)
	if (inb(PORT + 0) != 0xAE) {
		//return 1;
	}

	// If serial is not faulty set it in normal operation mode
	// (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	outb(PORT + 4, 0x0F);
	return 0;
}

bool halfDebug = false;

void continueOrExitWithSerial()
{
	while (1) {
		char c = nonBlockingKeyboard();
		if (c == 'N') {
			halfDebug = true;
		} else if (c == 'Y' && halfDebug) {
			halfDebug = false;
			debug ^= true;
			drawScreen();
		} else {
			halfDebug = false;
		}

		char abc = ' ';
		bool received = serial_received();
		while (received) {
			abc = inb(PORT);
			received = serial_received();
		}
		if (abc == 'R') {
			clearScreenToColour(TCRed);
		}

		if (debug && c == '$') {
			floppy ^= true;
			if (floppy) writeString("FLOPPY MODE");
			else writeString("CD-ROM MODE");
			millisleep(2000);
		}

		if (c == '\n') {
			break;
		} else if (c == '\e') {
			reallyQuit();
		}
	}
}

void continueOrExit()
{
	while (1) {
		char c = blockingKeyboard();
		if (c == 'N') {
			halfDebug = true;
		} else if (c == 'Y' && halfDebug) {
			halfDebug = false;
			debug ^= true;
			drawScreen();
		} else {
			halfDebug = false;
		}

		if (debug && c == '$') {
			floppy ^= true;
			if (floppy) writeString("FLOPPY MODE");
			else writeString("CD-ROM MODE");
			millisleep(2000);
		}

		if (c == '\n') {
			break;
		} else if (c == '\e') {
			reallyQuit();
		}
	}
}


void scanPartitionDisplay(Window* w)
{
	windowWrite(w, 0, 0, "Please wait while setup scans your hard");
	windowWrite(w, 0, 1, "drive for partitions...");
}


void corruptMBRDisplay(Window* w)
{
	windowWrite(w, 0, 0, "Your hard drive's MBR is corrupt or");
	windowWrite(w, 0, 1, "non-existent.");
	windowWrite(w, 0, 3, "Setup can overwrite it with a new one");
	windowWrite(w, 0, 4, "but ALL EXISTING DATA on the entire drive");
	windowWrite(w, 0, 5, "WILL BE LOST.");

	windowWrite(w, 0, 12, "To continue, press ENTER");
	windowWrite(w, 0, 13, "To cancel the installation, press ESC");

}

uint8_t firstSec[512] __attribute__((aligned(512)));

unsigned char goodMBRData[512] __attribute__((aligned(512))) = {
	0x33, 0xC0, 0x8E, 0xD0, 0xBC, 0x00, 0x7C, 0xFB, 0x50, 0x07, 0x50, 0x1F,
	0xFC, 0xBE, 0x1B, 0x7C, 0xBF, 0x1B, 0x06, 0x50, 0x57, 0xB9, 0xE5, 0x01,
	0xF3, 0xA4, 0xCB, 0xBE, 0xBE, 0x07, 0xB1, 0x04, 0x38, 0x2C, 0x7C, 0x09,
	0x75, 0x15, 0x83, 0xC6, 0x10, 0xE2, 0xF5, 0xCD, 0x18, 0x8B, 0x14, 0x8B,
	0xEE, 0x83, 0xC6, 0x10, 0x49, 0x74, 0x16, 0x38, 0x2C, 0x74, 0xF6, 0xBE,
	0x10, 0x07, 0x4E, 0xAC, 0x3C, 0x00, 0x74, 0xFA, 0xBB, 0x07, 0x00, 0xB4,
	0x0E, 0xCD, 0x10, 0xEB, 0xF2, 0x89, 0x46, 0x25, 0x96, 0x8A, 0x46, 0x04,
	0xB4, 0x06, 0x3C, 0x0E, 0x74, 0x11, 0xB4, 0x0B, 0x3C, 0x0C, 0x74, 0x05,
	0x3A, 0xC4, 0x75, 0x2B, 0x40, 0xC6, 0x46, 0x25, 0x06, 0x75, 0x24, 0xBB,
	0xAA, 0x55, 0x50, 0xB4, 0x41, 0xCD, 0x13, 0x58, 0x72, 0x16, 0x81, 0xFB,
	0x55, 0xAA, 0x75, 0x10, 0xF6, 0xC1, 0x01, 0x74, 0x0B, 0x8A, 0xE0, 0x88,
	0x56, 0x24, 0xC7, 0x06, 0xA1, 0x06, 0xEB, 0x1E, 0x88, 0x66, 0x04, 0xBF,
	0x0A, 0x00, 0xB8, 0x01, 0x02, 0x8B, 0xDC, 0x33, 0xC9, 0x83, 0xFF, 0x05,
	0x7F, 0x03, 0x8B, 0x4E, 0x25, 0x03, 0x4E, 0x02, 0xCD, 0x13, 0x72, 0x29,
	0xBE, 0x75, 0x07, 0x81, 0x3E, 0xFE, 0x7D, 0x55, 0xAA, 0x74, 0x5A, 0x83,
	0xEF, 0x05, 0x7F, 0xDA, 0x85, 0xF6, 0x75, 0x83, 0xBE, 0x3F, 0x07, 0xEB,
	0x8A, 0x98, 0x91, 0x52, 0x99, 0x03, 0x46, 0x08, 0x13, 0x56, 0x0A, 0xE8,
	0x12, 0x00, 0x5A, 0xEB, 0xD5, 0x4F, 0x74, 0xE4, 0x33, 0xC0, 0xCD, 0x13,
	0xEB, 0xB8, 0x00, 0x00, 0x80, 0x52, 0x15, 0x20, 0x56, 0x33, 0xF6, 0x56,
	0x56, 0x52, 0x50, 0x06, 0x53, 0x51, 0xBE, 0x10, 0x00, 0x56, 0x8B, 0xF4,
	0x50, 0x52, 0xB8, 0x00, 0x42, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x5A, 0x58,
	0x8D, 0x64, 0x10, 0x72, 0x0A, 0x40, 0x75, 0x01, 0x42, 0x80, 0xC7, 0x02,
	0xE2, 0xF7, 0xF8, 0x5E, 0xC3, 0xEB, 0x74, 0x49, 0x6E, 0x76, 0x61, 0x6C,
	0x69, 0x64, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69, 0x74, 0x69, 0x6F, 0x6E,
	0x20, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x2E, 0x20, 0x53, 0x65, 0x74, 0x75,
	0x70, 0x20, 0x63, 0x61, 0x6E, 0x6E, 0x6F, 0x74, 0x20, 0x63, 0x6F, 0x6E,
	0x74, 0x69, 0x6E, 0x75, 0x65, 0x2E, 0x00, 0x45, 0x72, 0x72, 0x6F, 0x72,
	0x20, 0x6C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x20, 0x6F, 0x70, 0x65,
	0x72, 0x61, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65,
	0x6D, 0x2E, 0x20, 0x53, 0x65, 0x74, 0x75, 0x70, 0x20, 0x63, 0x61, 0x6E,
	0x6E, 0x6F, 0x74, 0x20, 0x63, 0x6F, 0x6E, 0x74, 0x69, 0x6E, 0x75, 0x65,
	0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x8B, 0xFC, 0x1E, 0x57, 0x8B, 0xF5, 0xCB, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0xAF, 0x52, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

bool alreadyWiped = false;

void badHDD(Window* w)
{
	windowWrite(w, 0, 0, "Your hard drive doesn't work, or is");
	windowWrite(w, 0, 1, "write protected.");
	windowWrite(w, 0, 3, "Banana could not be installed.");

	windowWrite(w, 0, 13, "To cancel the installation, press ESC");
}

void corruptMBR(Window* w)
{
	w->repaint = corruptMBRDisplay;
	drawScreen();
	continueOrExit();
	reallyWipe();

	writeSector(0, goodMBRData, getFirstHDD());
	readSector(0, firstSec, getFirstHDD());

	writeHex(firstSec);
	writeString(" ");
	writeHex(goodMBRData);

	if (firstSec[510] != 0x55 || firstSec[511] != 0xAA) {
		w->repaint = badHDD;
		drawScreen();
		while (1) {
			char c = blockingKeyboard();
			if (c == '\e') {
				exitInstall();
			}
		}
	}
}

typedef struct Partition
{
	uint64_t lba;
	uint64_t length;
	uint64_t sectorHeldIn;

	uint8_t attrib;
	uint8_t type;
	bool extended;
	bool free;

	int internalID;

} Partition;

Partition partitionsTEMP[16];
Partition partitions[32];
int nextPartition = 0;
int partitionCursor = 0;

void setActivePartition()
{
	return;

	if (partitions[partitionCursor].extended == 0 && !partitions[partitionCursor].free) {
		readSector(0, firstSec, getFirstHDD());
		*((uint8_t*)(firstSec + 0x1BE)) = 0;
		*((uint8_t*)(firstSec + 0x1CE)) = 0;
		*((uint8_t*)(firstSec + 0x1DE)) = 0;
		*((uint8_t*)(firstSec + 0x1FE)) = 0;
		*((uint8_t*)(firstSec + 0x1BE + partitions[partitionCursor].internalID * 16 + 0)) = 0x80;
		writeSector(0, firstSec, getFirstHDD());
	}
}

void actualPartitionDelete()
{
	if (partitions[partitionCursor].extended == 0 && partitions[partitionCursor].sectorHeldIn == 0) {
		readSector(0, firstSec, getFirstHDD());
		*((uint32_t*)(firstSec + 0x1BE + partitions[partitionCursor].internalID * 16 + 8)) = 0;
		*((uint32_t*)(firstSec + 0x1BE + partitions[partitionCursor].internalID * 16 + 12)) = 0;
		writeSector(0, firstSec, getFirstHDD());
	}
}

void actualPartitionCreate(uint64_t size)
{
	readSector(0, firstSec, getFirstHDD());

	for (int i = 0; i < 4; ++i) {
		uint8_t attrib = firstSec[0x1BE + i * 16 + 0];
		uint8_t type = firstSec[0x1BE + i * 16 + 4];
		uint32_t lba = *((uint32_t*)(firstSec + 0x1BE + i * 16 + 8));
		uint32_t len = *((uint32_t*)(firstSec + 0x1BE + i * 16 + 12));

		if ((lba | len) == 0) {
			*((uint32_t*)(firstSec + 0x1BE + i * 16 + 8)) = partitions[partitionCursor].lba;
			*((uint32_t*)(firstSec + 0x1BE + i * 16 + 12)) = size;
			writeSector(0, firstSec, getFirstHDD());
			break;
		}
	}
}

void loadPartitions()
{
	for (int i = 0; i < 4; ++i) {
		uint8_t attrib = firstSec[0x1BE + i * 16 + 0];
		uint8_t type = firstSec[0x1BE + i * 16 + 4];
		uint32_t lba = *((uint32_t*)(firstSec + 0x1BE + i * 16 + 8));
		uint32_t len = *((uint32_t*)(firstSec + 0x1BE + i * 16 + 12));

		if ((lba | len) != 0) {
			partitionsTEMP[nextPartition].lba = lba;
			partitionsTEMP[nextPartition].length = len;
			partitionsTEMP[nextPartition].attrib = attrib;
			partitionsTEMP[nextPartition].type = type;
			partitionsTEMP[nextPartition].sectorHeldIn = 0;
			partitionsTEMP[nextPartition].extended = 0;
			partitionsTEMP[nextPartition].free = 0;
			partitionsTEMP[nextPartition].internalID = i;

			++nextPartition;
		}
	}
}

void sortPartitions()
{
	while (1) {
		bool swap = false;
		for (int i = 0; i < nextPartition - 1; ++i) {
			if (partitionsTEMP[i].lba > partitionsTEMP[i + 1].lba) {
				Partition tmp = partitionsTEMP[i];
				partitionsTEMP[i] = partitionsTEMP[i + 1];
				partitionsTEMP[i + 1] = tmp;
				swap = true;
			}
		}
		if (!swap) break;
	}
}

uint64_t getHDDSize()
{
	uint64_t best = 0;
	uint64_t try = 1;

	bool res = readSector(try, firstSec, getFirstHDD());
	if (res) {
		try = (try + best) / 2;
		if (try == best) {
			return try;
		}
	} else {
		best = try;
		try *= 2;
	}
}

void putFreeAreasInGaps()
{
	int oldNextPartition = nextPartition;
	int j = 0;

	for (int i = 0; i < oldNextPartition; ++i) {
		//sketchy!!!
		if (partitionsTEMP[i].length && partitionsTEMP[i].lba) {
			//copy old
			partitions[j++] = partitionsTEMP[i];

			//free space
			partitions[j].free = 1;
			partitions[j].lba = partitionsTEMP[i].length + partitionsTEMP[i].lba;

			if (i + 1 == oldNextPartition) {
				partitions[j].length = /*getHDDSize()*/ 9999999 - (partitionsTEMP[i].lba + partitionsTEMP[i].length);
			} else {
				partitions[j].length = partitionsTEMP[i + 1].lba - (partitionsTEMP[i].lba + partitionsTEMP[i].length);
			}

			if (partitions[j].length >= 1024 * 2) {
				//only count larger gaps
				++j;
			}
		}
	}

	if (!oldNextPartition) {
		partitions[j].free = 1;
		partitions[j].lba = 0x80;
		partitions[j].length = /*getHDDSize()*/ 9999999 - partitions[j].lba;
		++j;
	}

	nextPartition = j;
}

void displayPartitions(Window* w)
{
	int numPartsFoundSoFar = 0;
	for (int i = 0; i < nextPartition; ++i) {
		if (partitionCursor == i) {
			windowWrite(w, 0, i + 7, " > ");
		} else {
			windowWrite(w, 0, i + 7, "   ");
		}

		if (partitions[i].free) {
			windowWrite(w, 4, i + 7, "Free Space");
		} else {
			char ptn[] = "Partition 1";
			ptn[10] = '1' + numPartsFoundSoFar;
			++numPartsFoundSoFar;
			windowWrite(w, 4, i + 7, ptn);
		}

		int mbs = partitions[i].length;
		bool kbs = false;
		mbs /= 2;			//sectors to KBs
		if (mbs < 1024) {
			kbs = true;
		} else {
			mbs /= 1024;
		}

		char megstr[8];
		__memset(megstr, 0, 8);

		bool allzeros = false;
		for (int i = 0; i < 8; ++i) {
			megstr[7 - i] = mbs % 10 + '0';
			mbs /= 10;
		}
		for (int i = 0; i < 7; ++i) {
			if (megstr[i] == '0') megstr[i] = ' ';
			else break;
		}

		windowWrite(w, 20, i + 7, megstr);
		windowWrite(w, 28, i + 7, kbs ? " KB" : " MB");

		if (!partitions[i].free && (partitions[i].attrib & 0x80)) {
			windowWrite(w, 34, i + 7, "Active");
		}
	}
}

void partitionRepainter(Window* w)
{
	windowWrite(w, 0, 0, "Please select at partition to install");
	windowWrite(w, 0, 1, "Banana on.");

	windowWrite(w, 0, 3, "Press C to create a partition in free space, ");
	windowWrite(w, 0, 4, "D to delete a partition, and A to set a");
	windowWrite(w, 0, 5, "partition as active.");
}

void reallyDeletePartition(Window* w)
{
	windowWrite(w, 0, 0, "Really delete this partiton?");
	windowWrite(w, 0, 2, "ALL DATA ON IT WILL BE LOST");
	windowWrite(w, 0, 3, "and cannot be recovered.");

	windowWrite(w, 0, 5, "Press ESC to cancel, or hold");
	windowWrite(w, 0, 6, "shift and press X to confirm.");
}

void deletePartition()
{
	fadeWindows1And2 = true;

	Window wx;
	wx.x = 8;
	wx.y = 4;
	wx.w = 32;
	wx.h = 10;
	wx.repaint = reallyDeletePartition;
	__memcpy(wx.title, "  Confirmation ", __strlen("  Confirmation "));
	windows[EXIT_POPUP] = &wx;
	drawScreen();

	while (1) {
		char c = blockingKeyboard();
		if (c == '\e' || c == '\e') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			return;

		} else if (c == 'X') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			drawScreen();
			actualPartitionDelete();
			return;
		}
	}
}

void tooSmall()
{
	fadeWindows1And2 = true;

	Window wx;
	wx.x = 8;
	wx.y = 4;
	wx.w = 40;
	wx.h = 8;
	wx.repaint = 0;
	__memcpy(wx.title, "Partition Too Small", __strlen("Partition Too Small"));
	fadeWindows1And2 = true;

	windows[EXIT_POPUP] = &wx;
	drawScreen();

	windowWrite(&wx, 0, 0, "The selected partition is too small");
	windowWrite(&wx, 0, 1, "to install Banana on.");
	windowWrite(&wx, 0, 3, "Banana requires at least 64 MB of");
	windowWrite(&wx, 0, 4, "space to be installed.");

	blockingKeyboard();

	fadeWindows1And2 = false;
	windows[EXIT_POPUP] = 0;
}

int percent = 1;

void realInstallRedrawFloppyWait(Window* w)
{
	windowWrite(w, 0, 0, "Please wait...");
	windowWrite(w, 0, 3, "Do not eject the installation disc or");
	windowWrite(w, 0, 4, "turn off the power.");
}

void realInstallRedraw1(Window* w)
{
	//windowWrite(w, 0, 0, "Please wait while Setup formats the");
	//windowWrite(w, 0, 1, "partition.");
	//windowWrite(w, 0, 3, "Do not eject the installation disc or");
	//windowWrite(w, 0, 4, "turn off the power.");

	windowWrite(w, 0, 0, "Please wait while Setup deletes Windows");
	windowWrite(w, 0, 1, "and all of your files.");
	windowWrite(w, 0, 3, "If this doesn't sound good, yank out the");
	windowWrite(w, 0, 4, "power cable ASAP!");

	if (percent < 100) {
		if (percent / 10) writeCharacter(25, 13, percent / 10 + '0', TCBlack, TCWhite);
		else writeCharacter(25, 13, '0', TCBlack, TCWhite);
		writeCharacter(26, 13, percent % 10 + '0', TCBlack, TCWhite);
		writeCharacter(27, 13, '%', TCBlack, TCWhite);
	} else {
		writeCharacter(25, 13, '1', TCBlack, TCWhite);
		writeCharacter(26, 13, '0', TCBlack, TCWhite);
		writeCharacter(27, 13, '0', TCBlack, TCWhite);
		writeCharacter(28, 13, '%', TCBlack, TCWhite);
	}

	int filled = percent * 40 / 100;
	if (filled > 40) filled = 40;
	if (filled) for (int i = 0; i < filled; ++i) writeCharacter(25 + i, 15, ' ', TCBlue, TCBlue);
	for (int i = filled; i < 40; ++i) writeCharacter(25 + i, 15, ' ', TCLightGrey, TCLightGrey);
}

void realInstallRedraw2(Window* w)
{
	windowWrite(w, 0, 0, "Please wait while Setup copies files");
	windowWrite(w, 0, 1, "onto the partition.");
	windowWrite(w, 0, 3, "Do not eject the installation disc or");
	windowWrite(w, 0, 4, "turn off the power.");

	if (percent < 100) {
		if (percent / 10) writeCharacter(25, 13, percent / 10 + '0', TCBlack, TCWhite);
		else writeCharacter(25, 13, '0', TCBlack, TCWhite);
		writeCharacter(26, 13, percent % 10 + '0', TCBlack, TCWhite);
		writeCharacter(27, 13, '%', TCBlack, TCWhite);
	} else {
		writeCharacter(25, 13, '1', TCBlack, TCWhite);
		writeCharacter(26, 13, '0', TCBlack, TCWhite);
		writeCharacter(27, 13, '0', TCBlack, TCWhite);
		writeCharacter(28, 13, '%', TCBlack, TCWhite);
	}

	int filled = percent * 40 / 100;
	if (filled > 40) filled = 40;
	if (filled) for (int i = 0; i < filled; ++i) writeCharacter(25 + i, 15, ' ', TCBlue, TCBlue);
	for (int i = filled; i < 40; ++i) writeCharacter(25 + i, 15, ' ', TCLightGrey, TCLightGrey);
}

void setupCompleteRepaint(Window* w)
{
	windowWrite(w, 0, 0, "Banana has successfully installed");
	windowWrite(w, 0, 1, "onto your computer.");
	windowWrite(w, 0, 3, "Please restart your computer or press");
	windowWrite(w, 0, 4, "ENTER to start Banana.");
}

void pleaseRestart(Window* w)
{
	windowWrite(w, 0, 0, "Please manually restart your computer.");
}

void xxoutb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t xxinb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
		: "=a"(ret)
		: "Nd"(port));
	return ret;
}

void realInstall()
{
	setActivePartition();

	Window wx;
	wx.x = 5;
	wx.y = 2;
	wx.w = 50;
	wx.h = 19;
	wx.repaint = realInstallRedraw1;
	windows[MAIN_LAYER] = &wx;

	installPhase = PHASE_FORMATTING;
	__memcpy(wx.title, "Formatting\0\0\0\0\0\0\0\0", __strlen("Formatting        "));
	percent = 1;
	drawScreen();

	uint64_t size = partitions[partitionCursor].length;
	uint64_t lba = partitions[partitionCursor].lba;


	uint8_t bf[2048];
	uint64_t imageLba = MAIN_DISK_FIRST_SECTOR;
	uint64_t imageLen;

	for (int i = 0; i < 4; ++i) {
		read2KSectorFromInstallMedia(imageLba, bf);
		millisleep(500);
	}

	read2KSectorFromInstallMedia(imageLba, bf);
	read2KSectorFromInstallMedia(imageLba, bf);

	uint32_t numSectors = *(uint32_t*)(bf + 0x20);
	uint16_t reserved = *(uint16_t*)(bf + 0xE);
	uint8_t numFATs = *(uint8_t*)(bf + 0x10);

	uint32_t sectorsPerFATNew = (size - reserved) >> 7;
	uint32_t sectorsPerFATOld = *(uint32_t*)(bf + 0x24);

	uint32_t oldDataStartOffset = numFATs * sectorsPerFATOld + (uint32_t)reserved;
	uint32_t newDataStartOffset = numFATs * sectorsPerFATNew + (uint32_t)reserved;

	__memset(bf, 0, 512);



	uint8_t xx = 0;
	if (!skipFormatting) {
		for (uint64_t i = lba; i < lba + newDataStartOffset + 2; ++i) {
			if ((i & 3) == 0) {
				realInstallRedraw1(&wx);
				percent = (i - lba) * 100 / (newDataStartOffset + 2) + 1;
			}
			writeSector(i, bf, getFirstHDD());
		}
	}

	realInstallRedraw1(&wx);
	millisleep(500);

	int zerosSectorsTotal = 0;
	int nonZeroSectorsTotal = 0;

	if (floppy) {
		for (int i = 0; i < MAIN_DISK_MEGABYTES * 1024 * 1024 / 512; ++i) {
			if (isZero(i)) zerosSectorsTotal++;
			else nonZeroSectorsTotal++;
		}

		nonZeroSectorsWrittenSoFar = 0;
		zeroSectorsWrritenSoFar = 0;
	}

	installPhase = PHASE_COPYING;
	wx.repaint = realInstallRedraw2;
	percent = 1;
	__memcpy(wx.title, " Copying Files \0\0", __strlen(" Copying Files ") + 1);
	drawScreen();

	read2KSectorFromInstallMedia(imageLba, bf);

	*(uint32_t*)(bf + 0x1C) = lba;
	*(uint32_t*)(bf + 0x20) = size;
	*(uint32_t*)(bf + 0x24) = sectorsPerFATNew;

	//put the filename string in
	/*bf[0x34] = 'F';
	bf[0x35] = 'I';
	bf[0x36] = 'R';
	bf[0x37] = 'M';
	bf[0x38] = 'W';
	bf[0x39] = 'A';
	bf[0x3A] = 'R';
	bf[0x3B] = 'E';
	bf[0x3C] = 'L';
	bf[0x3D] = 'I';
	bf[0x3E] = 'B';
	bf[0x3F] = ' ';
	bf[0x42] = 0x28;*/

	writeSector(lba + 0, bf + 0x000, getFirstHDD());
	writeSector(lba + 1, bf + 0x200, getFirstHDD());
	writeSector(lba + 2, bf + 0x400, getFirstHDD());
	writeSector(lba + 3, bf + 0x600, getFirstHDD());

	//you don't want to know...
	uint32_t count = (MAIN_DISK_MEGABYTES * 2 * 1024) / 4 - 1;
	uint32_t inverseCount = 0;


	while (count) {
		read2KSectorFromInstallMedia((MAIN_DISK_MEGABYTES * 2 * 1024) / 4 - count + MAIN_DISK_FIRST_SECTOR, bf);

		uint32_t writeLBA = MAIN_DISK_MEGABYTES * 2 * 1024;
		writeLBA -= count * 4;

		if (writeLBA >= oldDataStartOffset) {
			writeLBA += newDataStartOffset;
			writeLBA -= oldDataStartOffset;
		}

		writeLBA += lba;

		writeSector(writeLBA + 0, bf + 0x000, getFirstHDD());
		writeSector(writeLBA + 1, bf + 0x200, getFirstHDD());
		writeSector(writeLBA + 2, bf + 0x400, getFirstHDD());
		writeSector(writeLBA + 3, bf + 0x600, getFirstHDD());

		--count;

		++inverseCount;
		if ((++xx == 5) || (floppy && (xx & 15) == 0)) {
			if (floppy) {
				percent = (((nonZeroSectorsWrittenSoFar * 15 + zeroSectorsWrritenSoFar) * 100) / (nonZeroSectorsTotal * 15 + zerosSectorsTotal)) + 1;
				//percent = (nonZeroSectorsWrittenSoFar * 100 / nonZeroSectorsTotal) + 1;

				//nonZeroSectorsWrittenSoFar
				//nonZeroSectorsTotal
			} else {
				percent = inverseCount * 100 / (MAIN_DISK_MEGABYTES * 2 * 1024 / 4) + 1;
			}
			realInstallRedraw2(&wx);
		}
	}

	installPhase = PHASE_FINALISING;

	//TODO: getting the right kernel for the system 

	installPhase = PHASE_DONE;

	beep(440);
	millisleep(500);
	beep(0);

	wx.repaint = setupCompleteRepaint;
	percent = 1;
	__memcpy(wx.title, " Setup Complete \0\0", __strlen(" Setup Complete ") + 1);
	drawScreen();

	while (1) {
		char c = blockingKeyboard();
		if (c == '\n') {
			wx.repaint = pleaseRestart;
			percent = 1;
			__memcpy(wx.title, " Setup Complete \0\0", __strlen(" Setup Complete ") + 1);
			drawScreen();

			uint8_t good = 0x02;
			while (good & 0x02) good = xxinb(0x64);
			xxoutb(0x64, 0xFE);

			while (1) {
				asm("cli; hlt");
			}

		}
	}
}


void installHere()
{
	fadeWindows1And2 = true;

	Window wx;
	wx.x = 8;
	wx.y = 4;
	wx.w = 44;
	wx.h = 14;
	wx.repaint = 0;
	__memcpy(wx.title, "Install Here", __strlen("Install Here"));
	fadeWindows1And2 = true;

	windows[EXIT_POPUP] = &wx;
	drawScreen();

	windowWrite(&wx, 0, 0, "Install Banana here?");
	windowWrite(&wx, 0, 2, "EVERYTHING on the selected partition");
	windowWrite(&wx, 0, 3, "will be lost and it cannot be recovered.");

	windowWrite(&wx, 0, 5, "Press ESC to cancel, or hold shift and");
	windowWrite(&wx, 0, 6, "press I to install.");

	windowWriteCol(&wx, 1, 8, " \"Take a gulp and take a breath", TCBlue);
	windowWriteCol(&wx, 1, 9, "   and go ahead and sign the scroll!\"", TCBlue);

	while (1) {
		char c = blockingKeyboard();
		if (c == '\e' || c == '\e') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			return;

		} else if (c == 'I') {
			fadeWindows1And2 = false;
			windows[EXIT_POPUP] = 0;
			drawScreen();
			realInstall();
			return;

		} else if (c == 'J' && debug) {
			fadeWindows1And2 = false;
			skipFormatting = true;
			windows[EXIT_POPUP] = 0;
			drawScreen();
			realInstall();
			return;
		}
	}

	fadeWindows1And2 = false;
	windows[EXIT_POPUP] = 0;
}

void createPartition()
{
	int maxSiz = partitions[partitionCursor].length / 2 / 1024;
	if (maxSiz == 0) {
		return;
	}

	Window w;
	w.x = 9;
	w.y = 4;
	w.w = 40;
	w.h = 11;
	w.repaint = 0;
	fadeWindows1And2 = true;
	windows[PART_SIZE_LAYER] = &w;

	__memcpy(w.title, "Select Size", __strlen("Select Size"));

	drawScreen();
	windowWrite(&w, 0, 0, "Enter the partition size:");
	windowWrite(&w, 0, 4, "Press ENTER to create the partition");
	windowWrite(&w, 0, 5, "or ESC to cancel.");

	char partSizeStr[11];
	__memset(partSizeStr, 0, 11);

	for (int i = 0; i < 7; ++i) {
		partSizeStr[6 - i] = maxSiz % 10 + '0';
		maxSiz /= 10;
	}

	while (1) {
		uint64_t siz = 0;

		for (int i = 0; i < __strlen(partSizeStr); ++i) {
			siz *= 10;
			siz += partSizeStr[i] - '0';
		}
		siz *= 1024;
		siz *= 2;

		bool valid = false;

		if (siz > partitions[partitionCursor].length) {
			windowWrite(&w, 0, 7, "Partition too big!  ");

		} else if (siz == 0) {
			windowWrite(&w, 0, 7, "Partition too small!");

		} else {
			valid = true;
			windowWrite(&w, 0, 7, "                    ");
		}

		windowWrite(&w, 0, 2, "             ");
		windowWrite(&w, 0, 2, partSizeStr);
		windowWrite(&w, __strlen(partSizeStr), 2, "_");
		windowWrite(&w, 10, 2, "MB");

		char c = blockingKeyboard();
		if (c == '\b') {
			if (__strlen(partSizeStr)) {
				partSizeStr[__strlen(partSizeStr) - 1] = 0;
			}
		} else if (c >= '0' && c <= '9') {
			if (__strlen(partSizeStr) < 7) {
				partSizeStr[__strlen(partSizeStr)] = c;
			}
		} else if (c == '\e') {
			break;
		} else if (c == '\n' && valid) {
			actualPartitionCreate(siz);
			break;
		}
	}

	windows[PART_SIZE_LAYER] = 0;
	fadeWindows1And2 = false;
}

//this is called in a loop
void scanPartitions(Window* w)
{
	w->repaint = scanPartitionDisplay;
	drawScreen();
	millisleep(400);
	readSector(0, firstSec, getFirstHDD());

	if (firstSec[511] != 0x55 && firstSec[511] != 0xAA) {
		corruptMBR(w);
		return;
	}


	nextPartition = 0;
	partitionCursor = 0;
	loadPartitions();
	sortPartitions();
	putFreeAreasInGaps();

	while (1) {
		w->repaint = partitionRepainter;
		drawScreen();
		displayPartitions(w);

		while (1) {
			char c = blockingKeyboard();
			if (c == 1) {
				if (partitionCursor) {
					--partitionCursor;
					break;
				}
			} else if (c == 2) {
				if (partitionCursor < nextPartition - 1) {
					++partitionCursor;
					break;
				}
			} else if (c == 'X' && debug) {
				corruptMBR(w);
				return;
			} else if ((c == 'c' || c == 'C') && partitions[partitionCursor].free) {
				createPartition();
				return;
			} else if ((c == 'a' || c == 'A') && !partitions[partitionCursor].free) {
				setActivePartition();
				return;
			} else if ((c == 'd' || c == 'D') && !partitions[partitionCursor].free) {
				deletePartition();
				return;
			} else if (c == '\n') {
				if (partitions[partitionCursor].free == 0) {
					if (partitions[partitionCursor].length / 1024 / 2 > 64) {
						installHere();
						break;
					} else {
						tooSmall();
						break;
					}
				}
			}
		}
	}
}

bool gotPentium = false;
bool gotFPU = false;
int cpuMHz = 0;




void main()
{
	setupAbstractionLibrary();
	debug = false;
	halfDebug = false;
	installPhase = PHASE_CHECK_REQ;

	for (int i = 0; i < MAX_WINDOWS; ++i) {
		windows[i] = 0;
	}

	fadeWindows1And2 = false;

	setFgCol(TCWhite);
	clearScreenToColour(TCBlack);

	int serialFail = init_serial();

	Window w;
	w.x = 5;
	w.y = 2;
	w.w = 50;
	w.h = 19;
	w.repaint = initWinRepaint;
	__memcpy(w.title, "Banana Setup", __strlen("Banana Setup"));

	windows[MAIN_LAYER] = &w;
	drawScreen();

	continueOrExitWithSerial();

	w.repaint = initWinRepaint2;
	drawScreen();
	continueOrExit();

	w.repaint = ramTest1;
	drawScreen();

	int ramLength = getRAMMap(0x500);

	uint64_t* ramTable = (uint64_t*)0x500;
	uint16_t ramTableLength = ramLength;

	uint64_t totalRAM = 0;

	for (int i = 0; i < ramTableLength; ++i) {
		uint64_t bottom = *(ramTable + 0);
		uint64_t length = *(ramTable + 1);
		uint64_t top = bottom + length;
		uint64_t type = *(((uint32_t*)ramTable) + 4);

		//check that the high bits are clear
		if ((bottom >> 32) || (top >> 32)) {
			break;
		}

		//check that it is usable, and that at least some of it is in the range
		//we want it to be in
		if (type == 1 && length >= 0x20000) {
			totalRAM += length;
			millisleep(200);
		}

		ramTable += 3;	//24 bytes / uint64_t = 3
	}

	totalRAM /= 1024;
	totalRAM /= 1024;

	ramStr[0] = '0';
	ramStr[1] = '0';
	ramStr[2] = '0';
	ramStr[3] = '0';
	ramStr[4] = '0';
	ramStr[5] = '0';
	ramStr[6] = '0';
	ramStr[7] = 0;

	int tr = totalRAM;
	for (int i = 0; i < 6; ++i) {
		char cc = '0' + totalRAM % 10;
		totalRAM /= 10;

		ramStr[6 - i] = cc;
	}
	totalRAM = tr;

	windowWrite(windows[0], 24, 5, "Done");

	windowWrite(windows[0], 0, 6, "Processor type... ");
	millisleep(200);
	regs_t in;
	in.eax = 0;
	in = abstractionCall(ACDetectCPUFeatures, in);
	gotPentium = in.eax;
	windowWrite(windows[0], 24, 6, "Done");


	windowWrite(windows[0], 0, 7, "Processor speed...");
	millisleep(500);
	windowWrite(windows[0], 24, 7, "Done");


	windowWrite(windows[0], 0, 8, "Math coprocessor...");
	millisleep(250);
	in.eax = 1;
	in = abstractionCall(ACDetectCPUFeatures, in);
	gotFPU = in.eax;
	windowWrite(windows[0], 24, 8, "Done");
	millisleep(250);

	if (totalRAM < 4) {
		w.repaint = lackRAM;
		drawScreen();
		while (1) {
			char c = blockingKeyboard();
			if (c == '\e') {
				exitInstall();
			} else if (debug) break;
		}
	}
	if (totalRAM < 8) {
		w.repaint = lackRAMSoft;
		drawScreen();
		continueOrExit();
	}

	w.repaint = ramTest2;
	drawScreen();
	continueOrExit();

	if (!gotPentium) {
		w.repaint = lackPent;
		drawScreen();
		continueOrExit();
	}
	if (!gotFPU) {
		w.repaint = lackMath;
		drawScreen();
		continueOrExit();
	}


	installPhase = PHASE_LEGAL_1;

	__memcpy(w.title, " Disclaimer ", __strlen(" Disclaimer "));
	w.x -= 3;
	w.y -= 1;
	w.w += 9;
	w.h += 2;

	disclaimPart2 = true;// false;
	w.repaint = disclaimer2;
	drawScreen();
	sleep(1);
	//disclaimPart2 = true;
	//drawScreen();
	while (nonBlockingKeyboard()) blockingKeyboard();
	continueOrExit();

	disclaimPart2 = true;// false;
	w.repaint = disclaimer;
	drawScreen();
	sleep(2);
	//disclaimPart2 = true;
	//drawScreen();
	while (nonBlockingKeyboard()) blockingKeyboard();
	continueOrExit();
	while (nonBlockingKeyboard()) blockingKeyboard();

	w.repaint = disclaimer3;
	drawScreen();
	millisleep(500);
	while (1) {
		char c = blockingKeyboard();

		if (c == '\n') {
			break;
		} else if (c == '\e') {
			reallyQuit();
		} else if (c == 's' || c == 'S') {
			licenseSummary();
		}
	}

	__memcpy(w.title, "Banana Setup", __strlen("Banana Setup"));
	w.x += 3;
	w.y += 1;
	w.w -= 9;
	w.h -= 2;
	installPhase = PHASE_PARTITION;

	while (1) {
		scanPartitions(&w);
	}

	while (1);

	// 0x4841594E;
}
