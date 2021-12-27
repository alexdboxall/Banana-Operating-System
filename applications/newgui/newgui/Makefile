OUTPUT32="C:/Users/Alex/Desktop/Banana/packages/banana/32/0001/newgui.exe"
OUTPUT64="C:/Users/Alex/Desktop/Banana/packages/banana/64/0001/newgui.exe"

AS32=i386-banana-as
AS64=x86_64-banana-as

CC32=i386-banana-gcc
CC64=x86_64-banana-gcc

CXX32=i386-banana-g++
CXX64=x86_64-banana-g++

ASFLAGS=
CCFLAGS=-std=c11 -c
LDFLAGS=-s

COBJECTS32 = $(patsubst %.c, %.o, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
CXXOBJECTS32 = $(patsubst %.cpp, %.o, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
OBJECTS32 = $(COBJECTS32) $(CXXOBJECTS32)

build: $(OBJECTS32)
	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o
	$(CC32) -s -Wl,_R32.o -Wl,-Map=C:/Users/Alex/Desktop/app32.map -o $(OUTPUT32) $^ -lm -ludraw

%.o: %.c
	$(CC32) -Os $(CCFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX32) -Os -fno-exceptions -fno-rtti -c $^ -o $@

#build:
#	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o
#	$(CC32) $(CCFLAGS) -s *.c -Wl,_R32.o -o $(OUTPUT32) -lm 
