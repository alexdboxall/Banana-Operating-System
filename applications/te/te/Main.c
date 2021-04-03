#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Line
{
	struct Line* next;
	char* text;

} Line;

Line* root = 0;
Line* last = 0;

Line* createNewLineAtStart(char* text)
{
	Line* oldRoot = root;
	Line* newLine = malloc(sizeof(Line));
	newLine->next = oldRoot;
	newLine->text = malloc(strlen(text) + 1);
	strcpy(newLine->text, text);
	root = newLine;
	if (last == 0) {
		last = newLine;
	}
	return newLine;
}

Line* createNewLine(char* text, Line* afterThis)
{
	if (afterThis == 0) {
		printf("Line could not be created.\n");
		return 0;
	}
	Line* cond = root;
	while (cond) {
		if (cond == afterThis) {
			Line* oldNext = cond->next;
			cond->next = malloc(sizeof(Line));
			if (!cond->next) {
				puts("Failed to allocate memory!");
				return 0;
			}
			cond = cond->next;
			cond->next = oldNext;
			cond->text = malloc(strlen(text) + 1);
			strcpy(cond->text, text);
			if (afterThis == last) {
				last = cond;
			}
			return cond;
		}
		cond = cond->next;
	}
	return 0;
}

void printLineSummary(char* text, int ln)
{
	printf("%5d ", ln);

	int index = 0;
	for (int i = 0; text[i]; ++i) {
		if (text[i] == '\r') continue;
		else if (text[i] == '\n') break;
		else if (text[i] == '\t' && index < 70) {
			do {
				putchar(' ');
				++index;
			} while (index % 4);
		} else {
			putchar(text[i]);
			if (++index == 70) {
				printf("...\n");
				return;
			}
		}
	}
	putchar('\n');
}

void printLineFull(char* text)
{
	int index = 0;
	for (int i = 0; text[i]; ++i) {
		if (text[i] == '\t') {
			do {
				putchar(' ');
				++index;
			} while (index % 4);
		} else if (text[i] == '\r') continue;
		else if (text[i] == '\n') {
			putchar('\n');
			index = 0;
		} else {
			putchar(text[i]);
			++index;
		}
	}
	if (index && index % 80) putchar('\n');
}

void printLineSlow(char* text, int* line)
{
	int index = 0;
	bool wrap = false;
	for (int i = 0; text[i]; ++i) {
		while (index >= 80) {
			wrap = true;
			index -= 80;
			(*line) += 1;
			if (*line >= 24) {
				printf("\nPlease press enter... ");
				int c = getchar();
				if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
				(*line) = 0;
			}
		}
		if (text[i] == '\t') {
			do {
				putchar(' ');
				++index;
			} while (index % 4);
		} else if (text[i] == '\r') continue;
		else if (text[i] == '\n') {
			putchar('\n');
			(*line) += 1;
			printf("%d\n", *line);
			if (*line >= 24) {
				printf("\nPlease press enter... ");
				int c = getchar();
				if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
				(*line) = 0;
			}
			index = 0;
		} else {
			putchar(text[i]);
			++index;
		}
	}
	if (!(!wrap && (index % 80 == 0))) {
		putchar('\n');
		(*line) += 1;
		if (*line >= 24) {
			printf("\nPlease press enter... ");
			int c = getchar();
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
			(*line) = 0;
		}
	}
}

void print()
{
	Line* cond = root;
	while (cond) {
		printLineFull(cond->text);
		cond = cond->next;
	}
	putchar('\n');
}

void printSlow()
{
	system("cls");
	Line* cond = root;
	int line = 0;
	while (cond) {
		printLineSlow(cond->text, &line);
		cond = cond->next;
	}
	putchar('\n');
}

void find(int startingAt, int length)
{
	char substring[1024];
	printf("Enter substring: ");
	fgets(substring, 1023, stdin);
	if (substring[strlen(substring) - 1] == '\n') {
		substring[strlen(substring) - 1] = 0;
	}

	Line* cond = root;
	int ln = startingAt;
	startingAt -= 1;
	while (cond) {
		if (startingAt) {
			--startingAt;
		} else {
			if (strstr(cond->text, substring)) printLineSummary(cond->text, ln);
			ln++;
			if (length > 0) --length;
			if (length == 0) return;
		}
		cond = cond->next;
	}
	putchar('\n');
}

void summary(int startingAt, int length)
{
	Line* cond = root;
	int ln = startingAt;
	startingAt -= 1;
	while (cond) {
		if (startingAt) {
			--startingAt;
		} else {
			printLineSummary(cond->text, ln++);
			if (length > 0) --length;
			if (length == 0) return;
		}
		cond = cond->next;
	}
	putchar('\n');
}

void size()
{
	Line* cond = root;
	int bytes = 0;
	int lines = 0;
	while (cond) {
		lines++;
		bytes += strlen(cond->text);
		cond = cond->next;
	}

	printf("%d bytes, %d lines.\n\n", bytes, lines);
}

void del(int start, int length)
{
	int lines = 0;
	int deletes = 0;
	int deleted = 0;
	if (start == 1) {
		while (length && root) {
			root = root->next;
			length--;
			deleted++;
		}
		printf("Deleted %d lines.\n\n", deleted);
		return;
	}
	Line* cond = root;
	while (cond) {
		lines++;
		if (lines == start - 1) {
			deletes = length;
		}
		if (deletes) {
			--deletes;
			if (cond->next) {
				++deleted;
				cond->next = cond->next->next;
				continue;
			} else break;
		}

		cond = cond->next;
	}
	printf("Deleted %d lines.\n\n", deleted);
}

void typeFrom(Line* after)
{
	while (1) {
		char bf[2048];
		fgets(bf, 2047, stdin);

		/// Ctrl+D
		if (bf[0] == 0x4) {
			return;
		}

		after = createNewLine(bf, after);
	}
}

void typeFromBeginning()
{
	char bf[2048];
	fgets(bf, 2047, stdin);

	/// Ctrl+D
	if (bf[0] == 0x4) {
		return;
	}

	typeFrom(createNewLineAtStart(bf));
}

void typeFromEnd()
{
	typeFrom(last);
}

void typeAfterLine(int ln)
{
	Line* cond = root;
	int lines = 0;
	while (cond) {
		lines++;
		if (lines == ln) {
			typeFrom(cond);
		}
		cond = cond->next;
	}
}

char filename[256];

void realSave()
{
	FILE* f = fopen(filename, "w");
	if (!f) {
		printf("Failed to save!\n\n");
		filename[0] = 0;
		return;
	}
	Line* cond = root;
	while (cond) {
		int written = fwrite(cond->text, strlen(cond->text), 1, f);
		if (written != strlen(cond->text)) {
			fclose(f);
			printf("The file could not be saved, and may be corrupted.\n\n");
			return;
		}
		if (cond->next && cond->text[strlen(cond->text) - 1] != '\n') fputc('\n', f);
		cond = cond->next;
	}
	fclose(f);
	printf("File saved.\n\n");
}

void openFileFromName(char* fil)
{
	strcpy(filename, fil);
	if (filename[strlen(filename) - 1] == '\n') {
		filename[strlen(filename) - 1] = 0;
	}

	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Failed to open!\n\n");
		filename[0] = 0;
		return;
	}
	root = 0;
	last = 0;

	char line[2048];
	memset(line, 0, 2048);
	bool first = true;
	while (fgets(line, 2047, f)) {
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
		if (first) {
			first = false;
			createNewLineAtStart(line);
		} else {
			createNewLine(line, last);
		}
	}

	fclose(f);
	printf("File opened.\n\n");
}

void openFile()
{
	printf("Enter filename (leave blank to cancel): ");
	fgets(filename, 255, stdin);
	if (filename[0] == '\n') {
		printf("Open has been canceled.\n\n");
		filename[0] = 0;
		return;
	}
	if (filename[strlen(filename) - 1] == '\n') {
		filename[strlen(filename) - 1] = 0;
	}

	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Failed to open!\n\n");
		filename[0] = 0;
		return;
	}
	root = 0;
	last = 0;

	char line[2048];
	memset(line, 0, 2048);
	bool first = true;
	while (fgets(line, 2047, f)) {
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
		if (first) {
			first = false;
			createNewLineAtStart(line);
		} else {
			createNewLine(line, last);
		}
	}

	fclose(f);
	printf("File opened.\n\n");
}

void saveAs()
{
	printf("Enter filename (leave blank to cancel): ");
	fgets(filename, 255, stdin);
	if (filename[0] == '\n') {
		printf("Save has been canceled.\n\n");
		filename[0] = 0;
		return;
	}
	if (filename[strlen(filename) - 1] == '\n') {
		filename[strlen(filename) - 1] = 0;
	}
	realSave();
}

void save()
{
	if (filename[0]) {
		realSave();
	} else {
		saveAs();
	}
}

void editLine(Line* l)
{
	printf("Old: %s\n", l->text);
	printf("New: ");
	char bf[2048];
	fgets(bf, 2047, stdin);
	free(l->text);
	l->text = malloc(strlen(bf) + 1);
	strcpy(l->text, bf);
	printf("\n");
}

void reconLine(Line* l)
{
	char buffer[2048];
	memset(buffer, 0, 2048);
	int oldPtr = 0;
	int newPtr = 0;
	int oldScroll = 0;
	int newScroll = 0;

	char input = 0;
	while (1) {
		system("cls");

		printf("%s ", oldScroll ? "Old: ..." : "Old:    ");
		for (int i = oldScroll; i < oldScroll + 70; ++i) {
			if (l->text[i] == 0) break;
			putchar(l->text[i]);
		}
		printf("\n   :     ");
		for (int i = 0; i < oldPtr - oldScroll; ++i) putchar(' ');
		printf("*\n%s ", newScroll ? "New: ..." : "New:    ");
		for (int i = newScroll; i < newScroll + 70; ++i) {
			if (buffer[i] == 0) break;
			putchar(buffer[i]);
		}
		printf("\n   :     ");
		for (int i = 0; i < newPtr - newScroll; ++i) putchar(' ');
		printf("*\n         > ");

		int c = getchar();
		input = c;
		if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}

		if (input == '\n' || input == 0 || input == 'k') {
			buffer[newPtr++] = l->text[oldPtr++];
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 'd') {
			oldPtr++;
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 'a' && oldPtr) {
			oldPtr--;
			if (oldPtr > 40) oldScroll--;
		}
		if (input == 's') {
			oldPtr++;
			if (oldPtr > 40) oldScroll--;
		}
		if (input == 'z' && newPtr) {
			newPtr--;
			buffer[newPtr] = 0;
			if (newPtr > 40) newScroll--;
		}
		if (input == 'x') {
			newPtr++;
			if (newPtr > 40) newScroll++;
		}
		if (input == 'e') {
			while (l->text[oldPtr++]);
		}
		if (input == ' ') {
			buffer[newPtr++] = ' ';
			if (newPtr > 40) newScroll++;
		}
		if (input == 'w') {
			while (l->text[oldPtr] && l->text[oldPtr] != ' ') buffer[newPtr++] = l->text[oldPtr++];
			while (l->text[oldPtr] && l->text[oldPtr] == ' ') buffer[newPtr++] = l->text[oldPtr++];
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 'o') {
			while (l->text[oldPtr] && l->text[oldPtr] != ' ') oldPtr++;
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 'p') {
			while (l->text[oldPtr] && l->text[oldPtr] != ' ') oldPtr++;
			while (l->text[oldPtr] && l->text[oldPtr] == ' ' && l->text[oldPtr]) oldPtr++;
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 'q') {
			while (l->text[oldPtr] && l->text[oldPtr] != ' ') buffer[newPtr++] = l->text[oldPtr++];
			if (newPtr > 40) newScroll++;
			if (oldPtr > 40) oldScroll++;
		}
		if (input == 't') {
			printf("         > ");
			char newContent[1024];
			fgets(newContent, 1023, stdin);
			if (newContent[strlen(newContent) - 1] == '\n') newContent[strlen(newContent) - 1] = 0;
			strcat(buffer, newContent);
			for (int i = 0; i < strlen(newContent); ++i) {
				++newPtr;
				if (newPtr > 40) newScroll++;
			}
		}

		if (l->text[oldPtr] == 0) {
			printf("Old: %s\nNew: %s\n\n", l->text, buffer);
			while (1) {
				printf("Save changes? Yes/Restart/Discard: ");
				int c = getchar();
				if (c == 'Y' || c == 'y') {
					free(l->text);
					l->text = malloc(strlen(buffer) + 1);
					strcpy(l->text, buffer);
					printf("Changes saved.\n\n");
					if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
					return;
				}
				if (c == 'D' || c == 'd') {
					printf("Changes discarded.\n\n");
					if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
					return;
				}
				int oldc = c;
				if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
				if (oldc == 'R' || oldc == 'r') {
					reconLine(l);
					return;
				}
			}
		}
	}
}

void edit(int line)
{
	if (line == -1) {
		editLine(last);
		return;
	}

	Line* cond = root;
	int lines = 0;
	while (cond) {
		lines++;
		if (lines == line) {
			editLine(cond);
			return;
		}
		cond = cond->next;
	}
	printf("Line could not be found.\n\n");
}

void recon(int line)
{
	if (line == -1) {
		reconLine(last);
		return;
	}

	Line* cond = root;
	int lines = 0;
	while (cond) {
		lines++;
		if (lines == line) {
			reconLine(cond);
			return;
		}
		cond = cond->next;
	}
	printf("Line could not be found.\n\n");
}

void join(int line, char delim)
{
	if (line == -1) {
		printf("Cannot join last line with anything!\n\n");
		return;
	}

	Line* cond = root;
	int lines = 0;
	while (cond) {
		lines++;
		if (lines == line && cond->next) {
			char* newT = malloc(strlen(cond->text) + strlen(cond->next->text) + 2);
			strcpy(newT, cond->text);
			if (delim) {
				char n[2];
				n[0] = delim;
				n[1] = 0;
				strcat(newT, n);
			}
			strcat(newT, cond->next->text);
			del(line + 1, 1);
			free(cond->text);
			cond->text = newT;
			printf("Lines have been joined to give:\n%s\n\n", newT);
			return;
		}
		cond = cond->next;
	}
	printf("Line could not be found.\n\n");
}

void newDoc()
{
	root = 0;
	last = 0;
}

int main(int argc, char* argv[])
{
	//memset(filename, 0, 256);
	printf("te - text editor\n\n");

	if (argc == 2) {
		openFileFromName(argv[1]);
	}

	while (1) {
		char buffer[255];
		printf("> ");
		fflush(stdout);
		fgets(buffer, 255, stdin);

		char arg0[64];
		int arg1 = -2;
		int arg2 = -2;
		memset(arg0, 0, 64);

		sscanf(buffer, "%s %d %d", arg0, &arg1, &arg2);

		if (!strcasecmp(arg0, "s") || !strcasecmp(arg0, "summary")) {
			if (arg1 == -2) {
				summary(1, -1);
			} else if (arg1 > 0 && arg2 == -2) {
				summary(arg1, 1);
			} else if (arg1 > 0 && arg2 > 0) {
				summary(arg1, arg2 - arg1 + 1);
			} else if (arg1 > 0 && arg2 == -1) {
				summary(arg1, -1);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "f") || !strcasecmp(arg0, "find")) {
			if (arg1 == -2) {
				find(1, -1);
			} else if (arg1 > 0 && arg2 == -2) {
				find(arg1, 1);
			} else if (arg1 > 0 && arg2 > 0) {
				find(arg1, arg2 - arg1 + 1);
			} else if (arg1 > 0 && arg2 == -1) {
				find(arg1, -1);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "d") || !strcasecmp(arg0, "del") || !strcasecmp(arg0, "delete")) {
			if (arg1 == -2) {
				printf("To delete all lines, type 'del 1 -1'\n\n");
			} else if (arg1 > 0 && arg2 == -2) {
				del(arg1, 1);
			} else if (arg1 > 0 && arg2 > 0) {
				del(arg1, arg2 - arg1 + 1);
			} else if (arg1 > 0 && arg2 == -1) {
				del(arg1, -1);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "p") || !strcasecmp(arg0, "print")) {
			print();
		} else if (!strcasecmp(arg0, "?") || !strcasecmp(arg0, "help") || !strcasecmp(arg0, "h")) {
			printf("?  help     - Displays command list\n");
			printf("s  summary  - Shows summary of file, or a specified line or range\n");
			printf("f  find     - Find substring in file, a specified line or range\n");
			printf("d  delete   - Deletes a line, or range of lines\n");
			printf("p  print    - Shows the entire file\n");
			printf("m  more     - Shows the entire file, stopping after every screen\n");
			printf("z  size     - Displays the file size\n");
			printf("i  join     - Join a line with the next. If there is an argument,\n");
			printf("              the ASCII character specified will go in between.\n");
			printf("j  join     - Join a line with the next. Adds a space in between.\n");
			printf("o  open     - Opens a file\n");
			printf("q  quit     - Quits. To skip prompt, use qs/quitsave or qno/quitnosave\n");
			printf("n  new      - Creats a new document. To skip prompt, use ns/newsave\n");
			printf("              or nno/newnosave\n");
			printf("t  type     - Type new lines after a given line.\n");
			printf("              To insert the new lines at the start, give 0 as the argument\n");
			printf("              To insert the new lines at the end, give -1, or no argument\n\n");
			printf("e  edit     - Rewrite an existing line\n");
			printf("re recon    - Reconstruct an existing line\n");
			printf("sv save     - Saves the file\n");
			printf("sa saveas   - Saves the file to a new filename\n\n");

			printf("Press enter to continue...");
			int c = getchar();
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}

			printf("\nExamples:\n");
			printf("    t           Start adding new lines at the end of the file.\n");
			printf("                To quit, start a new line with Ctrl+D and press enter.\n");
			printf("    t 0         Start adding new lines at the start of the file.\n");
			printf("    t 5         Start adding new lines AFTER line 5.\n");
			printf("    s           Displays all lines.\n");
			printf("    s 9         Displays line 9.\n");
			printf("    s 2 7       Displays lines 2 - 9.\n");
			printf("    s 5 -1      Displays lines 5 to the end.\n");
			printf("    d 5         Delete line 5. Delete accepts ranges like summary.\n");
			printf("    e 6         Edit line 6\n");
			printf("    p           Print the entire file\n");
			printf("    sv          Save the file\n\n");

			printf("Press enter to continue...");
			c = getchar();
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}

			printf("\nCommands in 'recon':\nrecon allows characters and words from an existing line to be\nused in its replacement. Two buffers are displayed:\none for the original line, and one for the content of its replacement.\nEach buffer has a pointer (selected character), marked with *\n\n");
			printf("k or (nothing)  Keep. Copies the selected character from the old line\n");
			printf("                into the new line buffer. Increments both pointers.\n");
			printf("d               Delete. Skip a character from the old line.\n");
			printf("a               Move old line pointer backward.\n");
			printf("s               Move old line pointer forward.\n");
			printf("z               Move new buffer pointer backward.\n");
			printf("x               Move new buffer pointer forward.\n");
			printf("e               Ends reconstruction.\n");
			printf("(space)         Add a space to the new buffer.\n");
			printf("w               Copies selected word from old to new, including space.\n");
			printf("q               Copies selected word from old to new, excluding space.\n");
			printf("p               Reposition pointer on old line to end of next word,\n");
			printf("                and any spaces.\n");
			printf("o               Reposition pointer on old line to end of next word.\n");
			printf("t               Type new data for the new buffer, at the cursor position.\n");
			printf("                Does not change the old line.\n");
			printf("\n");

			printf("Press enter to continue...");
			c = getchar();
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}

		} else if (!strcasecmp(arg0, "i") || !strcasecmp(arg0, "ijoin")) {
			if (arg1 != -2) {
				join(arg1, (arg2 == -2) ? 0 : arg2);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "j") || !strcasecmp(arg0, "join")) {
			if (arg1 != -2 && arg2 == -2) {
				join(arg1, ' ');
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "m") || !strcasecmp(arg0, "more")) {
			printSlow();
		} else if (!strcasecmp(arg0, "z") || !strcasecmp(arg0, "size")) {
			size();
		} else if (!strcasecmp(arg0, "sv") || !strcasecmp(arg0, "save")) {
			save();
		} else if (!strcasecmp(arg0, "sa") || !strcasecmp(arg0, "saveas")) {
			saveAs();
		} else if (!strcasecmp(arg0, "e") || !strcasecmp(arg0, "ed") || !strcasecmp(arg0, "edit")) {
			if (arg1 != -2 && arg1 != 0 && arg2 == -2) {
				edit(arg1);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "re") || !strcasecmp(arg0, "recon") || !strcasecmp(arg0, "reconstruct")) {
			if (arg1 != -2 && arg1 != 0 && arg2 == -2) {
				recon(arg1);
			} else {
				printf("Bad line specifier.\n\n");
			}
		} else if (!strcasecmp(arg0, "t") || !strcasecmp(arg0, "type")) {
			if (arg1 == 0 || last == 0) {
				typeFromBeginning();
			} else if (arg1 == -1 || arg1 == -2) {
				typeFromEnd();
			} else {
				typeAfterLine(arg1);
			}
		} else if (!strcasecmp(arg0, "q") || !strcasecmp(arg0, "quit") || !strcasecmp(arg0, "exit")) {
			printf("Save before quitting? Y/N/Cancel: ");
			int c = getchar();
			if (c == 'y' || c == 'Y') {
				save();
				return 0;
			} else if (c == 'n' || c == 'N') {
				putchar('\n');
				return 0;
			}
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
			putchar('\n');

		} else if (!strcasecmp(arg0, "qs") || !strcasecmp(arg0, "quitsave")) {
			save();
			return 0;
		} else if (!strcasecmp(arg0, "qno") || !strcasecmp(arg0, "quitnosave")) {
			return 0;

		} else if (!strcasecmp(arg0, "o") || !strcasecmp(arg0, "open")) {
			openFile();

		} else if (!strcasecmp(arg0, "n") || !strcasecmp(arg0, "new")) {
			printf("Save before creating a new document? Y/N/Cancel: ");
			int c = getchar();
			if (c == 'y' || c == 'Y') {
				save();
				newDoc();
			} else if (c == 'n' || c == 'N') {
				newDoc();
			}
			if (c != '\n') while ((c = getchar()) != '\n' && c != EOF) {}
			putchar('\n');

		} else if (!strcasecmp(arg0, "ns") || !strcasecmp(arg0, "newsave")) {
			save();
			newDoc();
		} else if (!strcasecmp(arg0, "nno") || !strcasecmp(arg0, "newnosave")) {
			newDoc();

		} else {
			printf("?\n\n");
		}
	}

	return 0;
}


bool __atomic_compare_exchange_4(uint32_t* ptr, uint32_t* expected, uint32_t desired, bool weak, int success_memorder, int failure_memorder)
{
	if (*ptr == *expected) {
		*ptr = desired;
		return true;

	} else {
		*expected = *ptr;
	}
	return false;
}