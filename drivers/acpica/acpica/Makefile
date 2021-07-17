OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/banana/32/0002/acpica.sys"
OUTPUT64="D:/Users/Alex/Desktop/acpica64.sys"

AS32=i386-banana-as
AS64=x86_64-banana-as

CXX32=i386-banana-g++
CC32=i386-banana-gcc
LD32=i386-banana-ld

CXX64=x86_64-banana-g++
CC64=x86_64-banana-gcc
LD64=x86_64-banana-ld

ASFLAGS=
CXXFLAGS=-fno-toplevel-reorder -march=i386 -mtune=i386 -msoft-float -O0 -fno-strict-aliasing -fpeephole2 -fauto-inc-dec -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -fno-align-functions -falign-loops=1 -falign-labels=1 -falign-jumps=1 
CFLAGS=-march=i386 -mtune=i386 -msoft-float -O0 -fno-strict-aliasing -fpeephole2 -fauto-inc-dec -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -fno-align-functions -falign-loops=1 -falign-labels=1 -falign-jumps=1 
LDFLAGS=-O0 -g -T D:/Users/Alex/Desktop/Banana/drivers/dlink.ld

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
	$(LD32) $(LDFLAGS) -shared -q -o $(OUTPUT32) $^ -Map=D:/Users/Alex/Desktop/driver32.map

%.32: %.cpp
	$(CXX32) $(CXXFLAGS) -fvisibility=hidden -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.32: %.c
	$(CC32) $(CFLAGS) -fvisibility=hidden -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel


$(TARGET64): $(OBJECTS64)
	$(LD64) $(LDFLAGS) -shared -q -o $(OUTPUT64) $^ -Map=D:/Users/Alex/Desktop/driver64.map

%.64: %.cpp
	$(CXX64) $(CXXFLAGS) -fvisibility=hidden -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.64: %.c
	$(CC64) $(CFLAGS) -fvisibility=hidden -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel

