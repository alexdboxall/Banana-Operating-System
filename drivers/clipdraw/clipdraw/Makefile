OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/banana/32/0001/clipdraw.dll"
OUTPUT32X="D:/Users/Alex/Desktop/Banana/packages/banana/32/0001/clipdrwx.dll"
OUTPUT64="D:/Users/Alex/Desktop/Banana/packages/banana/64/0001/clipdraw.dll"

AS32=i386-banana-as
AS64=x86_64-banana-as

CXX32=i386-banana-g++
CC32=i386-banana-gcc
LD32=i386-banana-ld

CXX64=x86_64-banana-g++
CC64=x86_64-banana-gcc
LD64=x86_64-banana-ld

ASFLAGS=
CFLAGS=-Os -fno-reorder-functions -fomit-frame-pointer
CXXFLAGS=-Os -fomit-frame-pointer
LDFLAGS=-g -T D:/Users/Alex/Desktop/Banana/drivers/dlink.ld -fno-reorder-functions

CXXOBJECTS32 = $(patsubst %.cpp, %.32, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
COBJECTS32 = $(patsubst %.c, %.32, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
CXXOBJECTS32X = $(patsubst %.cpp, %.32X, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
COBJECTS32X = $(patsubst %.c, %.32X, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))

TARGET32 = BananaDriver32
TARGET32X = BananaDriver32X

OBJECTS32 = $(CXXOBJECTS32) $(COBJECTS32)
OBJECTS32X = $(CXXOBJECTS32X) $(COBJECTS32X)

all: build32 build32x
build32: $(TARGET32) 
build32x: $(TARGET32X) 

$(TARGET32): $(OBJECTS32)
	$(LD32) $(LDFLAGS) -shared -q -o $(OUTPUT32) $^ -Map=D:/Users/Alex/Desktop/driver32.map

$(TARGET32X): $(OBJECTS32X)
	$(LD32) $(LDFLAGS) -shared -q -o $(OUTPUT32X) $^ -Map=D:/Users/Alex/Desktop/driver32x.map

%.32: %.cpp
	$(CXX32) $(CXXFLAGS) -mno-mmx -mno-sse -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.32: %.c
	$(CC32) $(CFLAGS) -mno-mmx -mno-sse -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel

%.32X: %.cpp
	$(CXX32) $(CXXFLAGS) -mmmx -msse4 -mavx -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel -fno-exceptions -fno-rtti
	
%.32X: %.c
	$(CC32) $(CFLAGS) -mmmx -msse4 -mavx -c $^ -o $@ -ID:/Users/Alex/Desktop/Banana/kernel

