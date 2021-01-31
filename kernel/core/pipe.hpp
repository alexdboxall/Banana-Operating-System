#pragma once

#ifndef _PIPE_HPP_
#define _PIPE_HPP_

#include "core/unixfile.hpp"

class Pipe : public UnixFile
{
private:

protected:
	uint8_t* buffer;
	int bufferBase;
	int bufferLength;
	int maxSize;

public:
	bool blockOnRead;

	Pipe(int bufferSize = 20480);
	~Pipe();

	bool isAtty();
	FileStatus read(uint64_t bytes, void* where, int* bytesRead);
	FileStatus write(uint64_t bytes, void* where, int* bytesWritten);
};

#endif