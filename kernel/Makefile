#these may be changed to suit your needs

WARNINGS = -Werror -Wall -Wextra -Wcast-align -Wchar-subscripts -W -Wuninitialized -Wpointer-arith  -Wno-error=unused-variable -Wno-error=unused-parameter \
	   -Wcast-align -Wno-error=unused-const-variable -Wno-error=sign-compare -Wno-unused-parameter

SOURCEDIR = D:/Users/Alex/Desktop/Banana/kernel
MOREKRNLDIR = D:/Users/Alex/Desktop/Banana/packages/morekrnl/32/0001

FIRMWAREDIR = D:/Users/Alex/Desktop/Banana/firmware
SYSROOTDIR = D:/Users/Alex/Desktop/Banana/sysroot
INCPATH = D:/Users/Alex/Desktop/Banana/kernel

CC32 = i386-banana-gcc
CXX32 = i386-banana-g++
OBJCOPY32 = i386-banana-objcopy

TARGET32_386 = Banana32_i386
kernel386: common32 $(TARGET32_386)

TARGET32_486 = Banana32_i486
kernel486: common32 $(TARGET32_486)

TARGET32_Pentium = Banana32_Pentium
kernelPentium: common32 $(TARGET32_Pentium)

TARGET32_Pentium2 = Banana32_Pentium2
kernelPentium2: common32 $(TARGET32_Pentium2)

TARGET32_Pentium3 = Banana32_Pentium3
kernelPentium3: common32 $(TARGET32_Pentium3)

TARGET32_Pentium4 = Banana32_Pentium4
kernelPentium4: common32 $(TARGET32_Pentium4)

TARGET32_Core2 = Banana32_Core2
kernelCore2: common32 $(TARGET32_Core2)

TARGET32_Nehalem = Banana32_Nehalem
kernelNehalem: common32 $(TARGET32_Nehalem)

TARGET32_Westmere = Banana32_Westmere
kernelWestmere: common32 $(TARGET32_Westmere)

TARGET32_Sandy = Banana32_Sandy
kernelSandy: common32 $(TARGET32_Sandy)

TARGET32_Ivy = Banana32_Ivy
kernelIvy: common32 $(TARGET32_Ivy)

TARGET32_Haswell = Banana32_Haswell
kernelHaswell: common32 $(TARGET32_Haswell)

TARGET32_Broadwell = Banana32_Broadwell
kernelBroadwell: common32 $(TARGET32_Broadwell)

TARGET32_Skylake = Banana32_Skylake
kernelSkylake: common32 $(TARGET32_Skylake)

TARGET32_Cannonlake = Banana32_Cannonlake
kernelCannonlake: common32 $(TARGET32_Cannonlake)

#
OPTIMISATIONS = -msoft-float -O0 -fno-strict-aliasing -fpeephole2 -fauto-inc-dec -fno-unwind-tables -freorder-functions -ftoplevel-reorder -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -fdelete-null-pointer-checks -fcompare-elim -fcprop-registers -fdce -fif-conversion -fif-conversion2 -fmerge-constants -fno-reorder-blocks  -fno-reorder-blocks-and-partition -fno-prefetch-loop-arrays -falign-functions=4 -falign-loops=4 -falign-labels=4 -falign-jumps=4 

#
CFLAGSCOMMON = $(WARNINGS) $(ACPI) $(OPTIMISATIONS) -march=$(TUNING) -mtune=$(TUNING) -mcld -ffreestanding -fmax-errors=5 -I $(INCPATH) -I $(LIBKPATH) -DKERNEL_CODE -D_libk
CFLAGS32 = -c -m32 -DTHIRTYTWOBIT $(CFLAGSCOMMON) -fvisibility=hidden
#C code has visibility hidden so that all of the ACPICA stuff doesn't clog it up

CXXFLAGS32 = -c -m32 -DTHIRTYTWOBIT $(CFLAGSCOMMON) -fno-exceptions -fno-rtti -fvisibility=protected $(ACPI) $(OPTIMISATIONS)
LDFLAGS32 = -lkgcc -L$(SOURCEDIR) -L$(SOURCEDIR)/libk -lm32 -ffreestanding $(LD_OPTIMISE_LEVEL) -nostdlib -flto -Wl,-Map=kernel32.map 
#-lsoftfp

COBJECTS32 = $(patsubst %.c, %.32, $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c) $(wildcard **/*.c))
CNOACPI32 = $(patsubst %.c, %.32, $(wildcard *.c) acpica/utclib.c $(wildcard [b-z]*/*.c) $(wildcard [b-z]*/*/*.c) $(wildcard */*/*/*.c))
CXXOBJECTS32 = $(patsubst %.cpp, %.32, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp) $(wildcard **/*.cpp))
ASMOBJECTS32 = $(patsubst %.s, %.32, $(wildcard hw/*/x86/*.s) $(wildcard hw/*/x86/*/*.s) $(wildcard hw/*/*/x86/*.s)) $(wildcard hw/*/*/x86/*/*.s)

OBJECTS32 = $(COBJECTS32) $(CXXOBJECTS32) $(ASMOBJECTS32)
OBJECTSNOACPI32 = $(CNOACPI32) $(CXXOBJECTS32) $(ASMOBJECTS32)

EXTRAFILES32 := $(SOURCEDIR)/morenasm.32

CRTBEGIN_OBJ32:=$(shell $(CXX32) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ32:=$(shell $(CXX32) $(CFLAGS) -print-file-name=crtend.o)

CRTI_OBJ32:=crti.32
CRTN_OBJ32:=crtn.32

common32:
	nasm -O0 -f bin $(SOURCEDIR)/vm86/VGASET.S -o $(SYSROOTDIR)/Banana/System/VGA.COM   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/vm86/VESASET.S -o $(SYSROOTDIR)/Banana/System/VESA.COM   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/vm86/EDID.S -o $(SYSROOTDIR)/Banana/System/EDID.COM   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/vm86/INT13.S -o $(SYSROOTDIR)/Banana/System/DUCTTAPE.COM   -w+orphan-labels
	nasm $(SOURCEDIR)/x86/boot.asm     -felf32 -O0 -o $(SOURCEDIR)/boot.32
	nasm $(SOURCEDIR)/x86/hardware.asm -felf32 -O0 -o $(SOURCEDIR)/morenasm.32
	nasm -O0 -f bin $(SOURCEDIR)/boot/TRAMP.S -o $(SOURCEDIR)/TRAMP.EXE   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/boot/BOOT1.ASM -o $(SOURCEDIR)/STAGE1.bin   -w+orphan-labels
	nasm -O0 -f bin $(SOURCEDIR)/boot/FIRMWARE.ASM -o $(SOURCEDIR)/FIRMWARE.LIB -w+orphan-labels -i $(SOURCEDIR)/boot/
	

$(TARGET32_386): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(SOURCEDIR)/KERNEL32.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_486): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNL486.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)
	
$(TARGET32_Pentium): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNL586.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)
	
$(TARGET32_Pentium2): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLP2.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Pentium3): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLP3.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)
	
$(TARGET32_Pentium4): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLP4.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Core2): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLCOR2.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Nehalem): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLNHLM.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Westmere): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLWMER.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Sandy): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLSAND.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Ivy): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLIVY.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Haswell): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLHWEL.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Broadwell): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLBWEL.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Skylake): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLSKY.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

$(TARGET32_Cannonlake): $(OBJECTS32)
	$(CC32) -T $(SOURCEDIR)/x86/linker.ld -o $(MOREKRNLDIR)/KRNLCNON.EXE $(SOURCEDIR)/boot.32 $(CRTI_OBJ32) $(CRTBEGIN_OBJ32) $(EXTRAFILES32) $^ $(CRTEND_OBJ32) $(CRTN_OBJ32) $(LDFLAGS32) -L$(SYSROOTDIR)

clean:
	/usr/bin/find . -type f -name '*.32' -exec rm {} +
	cp crti.322 crti.32 
	cp crtn.322 crtn.32

%.32: %.c
	$(CC32) $(CFLAGS32) $^ -o $@ 
	
%.32: %.cpp
	$(CXX32) $(CXXFLAGS32) $^ -o $@
	
%.32: %.s
	nasm -O0 -felf32 $^ -o $@

%.com: %.s
	nasm -O0 -f bin $^ -o $@

