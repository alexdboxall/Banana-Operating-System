SOURCEDIR = C:/Users/mord/Desktop/banana-os/System
SYSROOT = "C:/Users/mord/Desktop/banana-os"
ISYSTEM = /System

CC64 = x86_64-banana-gcc
CC32 = i686-elf-gcc

CFLAGS32 = -c -m32 -DTHIRTYTWOBIT  -std=gnu99 -Wall --sysroot=$(SYSROOT) -isystem=$(ISYSTEM) -ffreestanding -fno-strict-aliasing -Wcast-align -Wchar-subscripts -W -Wuninitialized -Wpointer-arith -Wall -Werror -Wno-error=unused-variable -Wno-error=unused-parameter
CFLAGS64 = -c -m64 -mno-red-zone   -std=gnu99 -Wall --sysroot=$(SYSROOT) -isystem=$(ISYSTEM) -ffreestanding -fno-strict-aliasing -Wcast-align -Wchar-subscripts -W -Wuninitialized -Wpointer-arith -Wall -Werror -Wno-error=unused-variable -Wno-error=unused-parameter 

LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc -s -flto

TARGET32 = BananaOS32
TARGET64 = BananaOS64

OBJECTS32 = $(patsubst %.c, %.32, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
OBJECTS64 = $(patsubst %.c, %.64, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
EXTRAFILES := $(SOURCEDIR)/morenasm.o 

all: kernel32 kernel64 other
kernel32: $(TARGET32)
kernel64: $(TARGET64)

$(TARGET32): $(OBJECTS32)
	nasm $(SOURCEDIR)/x86/boot.asm     -felf32 -O0 -o $(SOURCEDIR)/boot.o
	nasm $(SOURCEDIR)/x86/hardware.asm -felf32 -O0 -o $(SOURCEDIR)/morenasm.o 
	
	#ensure boot.o is the first file linked
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld  -o $(SOURCEDIR)/KERNEL32.EXE $(SOURCEDIR)/boot.o $^ $(EXTRAFILES) $(LDFLAGS) 

$(TARGET64): $(OBJECTS64)
	nasm $(SOURCEDIR)/x86-64/boot.asm     -felf64 -O0 -o $(SOURCEDIR)/boot.o
	nasm $(SOURCEDIR)/x86-64/hardware.asm -felf64 -O0 -o $(SOURCEDIR)/morenasm.o 
	
	#ensure boot.o is the first file linked
	$(CC64) -T $(SOURCEDIR)/x86-64/linker.ld -o $(SOURCEDIR)/KERNEL.EXE $(SOURCEDIR)/boot.o $^ $(EXTRAFILES) $(LDFLAGS) 
	
other:
	nasm -O0 -f bin $(SOURCEDIR)/boot/STAGE1.asm -o $(SOURCEDIR)/STAGE1.bin   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/boot/STAGE2.asm -o $(SOURCEDIR)/BOOTLOAD.SYS -w+orphan-labels -i $(SOURCEDIR)/boot/
	nasm -O0 -f bin $(SOURCEDIR)/boot/TRAMP.asm  -o $(SOURCEDIR)/TRAMP.EXE    -w+orphan-labels
	
%.32: %.c
	$(CC32) $(CFLAGS32) $^ -o $@
	
%.64: %.c
	$(CC64) $(CFLAGS64) $^ -o $@
	
cleanall:
	find $(SOURCEDIR)/. -type f -name '*.o' -delete || /bin/true
	find $(SOURCEDIR)/. -type f -name '*.32' -delete || /bin/true
	find $(SOURCEDIR)/. -name '*.64' -delete || /bin/true
	rm $(SOURCEDIR)/KERNEL.EXE || /bin/true
	rm $(SOURCEDIR)/KERNEL32.EXE || /bin/true
	rm $(SOURCEDIR)/TRAMP.EXE || /bin/true
	rm $(SOURCEDIR)/BOOTLOAD.SYS || /bin/true
	rm $(SOURCEDIR)/STAGE1.BIN || /bin/true
	rm $(SOURCEDIR)/JUMPER32.SYS || /bin/true
	
clean:
	rm $(SOURCEDIR)/*.o
	rm $(SOURCEDIR)/*.32
	rm $(SOURCEDIR)/*.64
	rm $(SOURCEDIR)/KERNEL.EXE
	rm $(SOURCEDIR)/KERNEL32.EXE
	rm $(SOURCEDIR)/TRAMP.EXE
	rm $(SOURCEDIR)/BOOTLOAD.SYS
	rm $(SOURCEDIR)/STAGE1.BIN
	rm $(SOURCEDIR)/JUMPER32.SYS