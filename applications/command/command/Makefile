OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/system/32/0001/command.exe"
OUTPUT64="D:/Users/Alex/Desktop/Banana/packages/system/64/0001/command.exe"

AS32=i386-banana-as
AS64=x86_64-banana-as

CC32=i386-banana-gcc
CC64=x86_64-banana-gcc

OBJCOPY32=i386-banana-objcopy

ASFLAGS=
CCFLAGS=-std=c11 -s -Wl,-Map=app32.map -Os 

all: build

build:
	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o

	$(CC32) $(CCFLAGS) *.c -Wl,_R32.o -o $(OUTPUT32) -lm -luwsbe