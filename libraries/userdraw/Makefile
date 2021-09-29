
WARNINGS = -Werror -Wall -Wextra -Wcast-align -Wchar-subscripts -W -Wuninitialized -Wpointer-arith  -Wno-error=unused-variable -Wno-error=unused-parameter \
	   -Wcast-align -Wno-error=unused-const-variable -Wno-error=sign-compare -Wno-unused-parameter

CC32 = i386-banana-gcc
CXX32 = i386-banana-g++
OBJCOPY32 = i386-banana-objcopy
AR32 = i386-banana-ar

TARGET32_386 = Banana32_i386
kernel386: $(TARGET32_386)

OPTIMISATIONS = -O0

CFLAGSCOMMON = $(WARNINGS) $(OPTIMISATIONS) -fmax-errors=5
CFLAGS32 = -c -m32 $(CFLAGSCOMMON)
CXXFLAGS32 = -c -m32 $(CFLAGSCOMMON) -fno-exceptions -fno-rtti
LDFLAGS32 =

COBJECTS32 = $(patsubst %.c, %.32, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
CXXOBJECTS32 = $(patsubst %.cpp, %.32, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))

OBJECTS32 = $(COBJECTS32) $(CXXOBJECTS32)

$(TARGET32_386): $(OBJECTS32)
	ar -crs libudraw.a $^

clean:
	/usr/bin/find . -type f -name '*.32' -exec rm {} +

%.32: %.c
	$(CC32) $(CFLAGS32) $^ -o $@ 
	
%.32: %.cpp
	$(CXX32) $(CXXFLAGS32) $^ -o $@
