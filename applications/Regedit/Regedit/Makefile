OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/banana/32/0001/regedit.exe"

AS32=i386-banana-as
AS64=x86_64-banana-as

CC32=i386-banana-gcc
CC64=x86_64-banana-gcc

ASFLAGS=
CCFLAGS=-std=c11 -Wl,-Map=app32.map -Os

all: build

build:
	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o
	$(CC32) $(CCFLAGS) *.c -Wl,_R32.o -o $(OUTPUT32)
