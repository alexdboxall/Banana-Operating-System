OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/system/32/0002/floppy.sys"
OUTPUT64="D:/Users/Alex/Desktop/Banana/packages/system/64/0002/floppy.sys"

AS32=i386-banana-as
AS64=x86_64-banana-as

CXX32=i386-banana-g++
CC32=i386-banana-gcc
LD32=i386-banana-ld

CXX64=x86_64-banana-g++
CC64=x86_64-banana-gcc
LD64=x86_64-banana-ld

ASFLAGS=
CXXFLAGS=-O0
CFLAGS=-O0
LDFLAGS=-g -s

CXXOBJECTS32 = $(patsubst %.cpp, %.32, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
CXXOBJECTS64 = $(patsubst %.cpp, %.64, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
COBJECTS32 = $(patsubst %.c, %.32, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
COBJECTS64 = $(patsubst %.c, %.64, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))

TARGET32 = BananaDriver32
TARGET64 = BananaDriver64

OBJECTS32 = $(CXXOBJECTS32) $(COBJECTS32)
OBJECTS64 = $(CXXOBJECTS64) $(COBJECTS64)

all: build32
build32: $(TARGET32) 

$(TARGET32): $(OBJECTS32)
	$(LD32) $(LDFLAGS) -fno-reorder-functions -shared -q -o $(OUTPUT32) $^ -Map=D:/Users/Alex/Desktop/driver32.map

%.32: %.cpp
	$(CXX32) $(CXXFLAGS) -fno-reorder-functions -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.32: %.c
	$(C32) $(CFLAGS) -fno-reorder-functions -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel


$(TARGET64): $(OBJECTS64)
	$(LD64) $(LDFLAGS) -shared -q -o $(OUTPUT64) $^ -Map=D:/Users/Alex/Desktop/driver64.map

%.64: %.cpp
	$(CXX64) $(CXXFLAGS) -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.64: %.c
	$(C64) $(CFLAGS) -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel

