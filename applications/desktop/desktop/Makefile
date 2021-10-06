OUTPUT32="D:/Users/Alex/Desktop/Banana/packages/banana/32/0001/desktop.exe"
OUTPUT64="D:/Users/Alex/Desktop/desktop64.exe"

AS32=i386-banana-as
CXX32=i386-banana-g++

ASFLAGS=
CCFLAGS=-Os
LDFLAGS=-s

all: build

build:
	$(AS32) $(ASFLAGS) Resclink.s -o _R32.o
	$(CXX32) -s $(CCFLAGS) *.cpp -Wl,_R32.o -o $(OUTPUT32) -ludraw
