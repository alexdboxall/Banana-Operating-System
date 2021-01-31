#include "registry/registry.hpp"
#include "core/main.hpp"
#include "fs/vfs.hpp"
#include "core/kheap.hpp"

extern "C" {
	#include "libk/string.h"
}

#pragma GCC optimize ("Os")

namespace Registry
{
	bool findLineFromLoadedData(char* data, char* key, char* output)
	{
		//store the start of the section
		//this value isn't used if sections aren't used
		char* requiredSection = key + 1;

		//check if the key uses sections
		bool needsSections = key[0] == '@';

		//if it does, find the start point of the key
		if (needsSections) {
			//advance the pointer until a colon is found, or the string ends
			while (*key && *key != ':') {
				key++;
			}

			//if a colon wasn't found, then it is an invalid key, so return
			if (!(*key)) {
				return false;
			}

			//remove the last byte of the section key, as it will be a '['
			//this also terminates the section string
			// *(key - 1) = 0;

			//terminates the section string and
			//advance the pointer to the actual start of the key
			*key++ = 0;
		}

		//store the current line being examined
		char tempLine[200];
		int tempLinePtr = 0;

		//no section defined yet
		char currentSection[64];
		memset(currentSection, 0, 64);

		for (int i = 0; data[i]; ++i) {
			//bounds checking
			if (tempLinePtr >= 200) {
				return false;
			}

			//if it is a newline
			if (data[i] == '\n') {	
				//terminate the string
				tempLine[tempLinePtr++] = 0;

				//ignore comments, nulls, newlines, etc.
				if (!tempLine[0] || tempLine[0] == '#' || tempLine[0] == '\n' || tempLine[0] == ' ' || tempLine[0] == '\t') {
					
				//check for sections
				} else if (tempLine[0] == '[') {
					//only do this if needed
					if (needsSections) {
						//bounds checking
						if (strlen(tempLine + 1) >= sizeof(currentSection)) {
							return false;
						}

						//set the section
						strcpy(currentSection, tempLine + 1);

						//remove the ']'
						currentSection[strlen(currentSection) - 2] = 0;
					}

				//this is a line with a statement
				} else {
					//check if we are in the right section if sections are needed
					if (!needsSections || !strcmp(currentSection, requiredSection)) {
						//now check if the key matches
						char* value = tempLine;

						//advance the pointer until an equals sign is found, or the string ends
						while (*value && *value != '=') {
							value++;
						}

						//if an equals sign wasn't found, there is nothing in the key, so return
						if (!(*value)) {
							return false;
						}

						//otherwise, blank out the equals sign, and advance the pointer so
						//it points to the value part of the string
						*value++ = 0;

						//check that tempLine (which due to the line above is null terminated)
						//at the end of the key, matches the key we want
						if (!strcmp(key, tempLine)) {
							//if it does, return the value part of the string
							strcpy(output, value);
							return true;
						}
					}
				}

				//get ready for the next loop
				tempLinePtr = 0;

			//otherwise just build the line
			} else {
				tempLine[tempLinePtr++] = data[i];
			}
		}

		//not found
		return false;
	}

	bool getLineFromRegistry(char* file, char* path, char* key, char* output)
	{
		//validate filename lengths
		if (strlen(path) + strlen(file) + 5 > 255) {
			return false;
		}

		//generate the filepath
		char filepath[256];
		strcpy(filepath, file);
		strcat(filepath, "/");
		strcat(filepath, path);
		strcat(filepath, ".ini");

		//create the file object
		File* f = new File(filepath, kernelProcess);
		if (f == nullptr) {
			return false;
		}
		
		//open the file
		FileStatus st = f->open(FILE_OPEN_READ);
		if (st != FileStatus::Success) {
			delete f;
			return false;
		}

		//read the file size
		uint64_t size;
		bool directory;
		f->stat(&size, &directory);

		//blank files have no keys
		if (size == 0) {
			f->close();
			delete f;
			return false;
		}

		//load the file into memory
		char* data = (char*) malloc(size);
		int bytesRead;
		st = f->read(size, data, &bytesRead);

		//check for errors
		if (st != FileStatus::Success || bytesRead != (int) size) {
			f->close();
			delete f;
			return false;
		}

		//close the file
		f->close();
		delete f;

		//find the actual line
		bool found = findLineFromLoadedData(data, key, output);

		//cleanup
		free(data);

		return found;
	}

	bool getLine(char* path, char* key, char* output)
	{
		//first check the user registry
		bool got = getLineFromRegistry((char*) "C:/Banana/Registry/User/**USERNAME**", path, key, output);
		if (got) {
			return true;
		}

		//if not, fall back on the system registry
		//if it can't be found, NULL will be returned to the caller
		got = getLineFromRegistry((char*) "C:/Banana/Registry/System/", path, key, output);
		return got;
	}

	bool readInt(char* path, char* key, int* out)
	{
		//get the line
		char line[200];
		bool got = getLine(path, key, line);

		//if it doesn't exist, there is no key
		if (!got) {
			return false;
		}

		//prepare to parse the line
		int value = 0;
		bool negative = false;
		int i = 0;

		//check for signs
		if (line[i] == '+') {
			++i;
		} else if (line[i] == '-') {
			++i;
			negative = true;
		}
		
		//parse the line
		for (; line[i] && line[i] != '\r'; ++i) {
			value *= 10;
			value += line[i] - '0';
		}

		//account for signs
		if (negative) {
			value = -value;
		}

		//return the value
		*out = value;

		return true;
	}

	bool readString(char* path, char* key, char* out, int maxLen)
	{
		//get the line
		char line[200];
		bool got = getLine(path, key, line);

		//if it doesn't exist, there is no key
		if (!got) {
			return false;
		}

		//copy across, null terminating as it goes
		for (int i = 0; line[i] && i < maxLen - 1; ++i) {
			out[i] = line[i];
			out[i + 1] = 0;
		}

		//remove carriage return
		if (out[strlen(out) - 1] == '\r') {
			out[strlen(out) - 1] = 0;
		}

		return true;
	}

	bool readBool(char* path, char* key, bool* out)
	{
		//booleans are integers, so this is a wrapper around readInt
		int o;
		bool retVal = readInt(path, key, &o);
		*out = o;
		return retVal;
	}


	bool readBoolWithDefault(char* path, char* key, bool defaultVal)
	{
		//try reading the key
		bool out;
		bool found = readBool(path, key, &out);

		//if it was found, return that value
		if (found) {
			return out;
		}

		//otherwise return the default
		return defaultVal;
	}

	int readIntWithDefault(char* path, char* key, int defaultVal)
	{
		//try reading the key
		int out;
		bool found = readInt(path, key, &out);

		//if it was found, return that value
		if (found) {
			return out;
		}

		//otherwise return the default
		return defaultVal;
	}

	char* readStringWithDefault(char* path, char* key, char* buffer, int maxLen, char* defaultVal)
	{
		//try reading the key
		bool found = readString(path, key, buffer, maxLen);

		//if it was found, return that value
		if (found) {
			return buffer;
		}

		//otherwise return the default
		return defaultVal;
	}
}



