OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/banana/32/0001/zip.exe"
OUTPUT64="D:/Users/Alex/Desktop/Banana/packages/banana/64/0001/zip.exe"

AS32=i386-banana-as
AS64=x86_64-banana-as

CC32=i386-banana-gcc
CC64=x86_64-banana-gcc

ASFLAGS=
CCFLAGS=-std=c11
LDFLAGS=-s

all: build

build:
	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o
	$(CC32) $(CCFLAGS) *.c -Wl,_R32.o -o $(OUTPUT32)
