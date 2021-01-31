#include "../common/main.h"

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0"
                  : "=a"(ret)
                  : "Nd"(port));
    return ret;
}

void outb(uint16_t port, uint8_t  val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

extern void x86setup();
void archSetup()
{
    asm("cli");
}

extern uint32_t(*syscalls[32])(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

void fwClearScreen()
{
    uint16_t* ptr = 0xB8000;
    for (int i = 0; i < 80 * 25 / 2; ++i) {
        *ptr++ = 0;
    }
}

void fwScrollScreen()
{
    memmove(0xB8000, 0xB8000 + 80 * 2, 79 * 40 * 2);
}

void fwBeep(int hertz)
{
    if (hertz == 0) {
        uint8_t tmp = inb(0x61) & 0xFC;
        outb(0x61, tmp);

    } else {
        uint32_t Div;
        uint8_t tmp;

        //Set the PIT to the desired frequency
        Div = 1193180 / hertz;
        outb(0x43, 0xb6);
        outb(0x42, (uint8_t) (Div));
        outb(0x42, (uint8_t) (Div >> 8));

        //And play the sound using the PC speaker
        tmp = inb(0x61);
        if (tmp != (tmp | 3)) {
            outb(0x61, tmp | 3);
        }
    }
}

void fwUpdateCursor(int x, int y)
{
    uint16_t pos = y * 80 + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void fwWriteChar(uint32_t c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg)
{		
    //arg1: char, arg2: x, arg3: y, arg4: colourbytes
    uint8_t col = (fg & 0xF) | ((bg & 0xF) << 4);
    uint16_t* ptr = 0xB8000 + (y * 80 + x) * 2;
    *ptr = (c & 0xFF) | ((col & 0xFF) << 8);
}

extern size_t x86Internal_getKey();
extern size_t x86Internal_wait100ms();

void fwWait(int millisec)
{
    int intervals = (millisec + 99) / 100;
    while (intervals--) {
        x86Internal_wait100ms();
    }
}

int x = 0;
char fwHeldKey()
{
    uint32_t bioskey = x86Internal_getKey();
    if (bioskey == 0) {
        return 0;
    }

    char asciiChar = bioskey & 0xFF;
    uint8_t scancode = (bioskey >> 8) & 0xFF;

    if (scancode == 0x3B) return SPECIAL_KEY_F1;
    if (scancode == 0x3C) return SPECIAL_KEY_F2;
    if (scancode == 0x3D) return SPECIAL_KEY_F3;
    if (scancode == 0x3E) return SPECIAL_KEY_F4;
    if (scancode == 0x3F) return SPECIAL_KEY_F5;
    if (scancode == 0x40) return SPECIAL_KEY_F6;
    if (scancode == 0x41) return SPECIAL_KEY_F7;
    if (scancode == 0x42) return SPECIAL_KEY_F8;
    if (scancode == 0x43) return SPECIAL_KEY_F9;
    if (scancode == 0x44) return SPECIAL_KEY_F10;
    if (scancode == 0x85) return SPECIAL_KEY_F11;
    if (scancode == 0x86) return SPECIAL_KEY_F12;

    if (scancode == 0x0F) return SPECIAL_KEY_TAB;
    if (scancode == 0x48) return SPECIAL_KEY_UP;
    if (scancode == 0x50) return SPECIAL_KEY_DOWN;
    if (scancode == 0x4B) return SPECIAL_KEY_LEFT;
    if (scancode == 0x4D) return SPECIAL_KEY_RIGHT;
    if (scancode == 0x47) return SPECIAL_KEY_HOME;
    if (scancode == 0x4F) return SPECIAL_KEY_END;
    if (scancode == 0x52) return SPECIAL_KEY_INSERT;
    if (scancode == 0x53) return SPECIAL_KEY_DELETE;
    if (scancode == 0x1C) return SPECIAL_KEY_ENTER;
    if (scancode == 0x0E) return SPECIAL_KEY_BACKSPACE;
    if (scancode == 0x01) return SPECIAL_KEY_ESCAPE;
    if (scancode == 0x49) return SPECIAL_KEY_PAGEUP;
    if (scancode == 0x51) return SPECIAL_KEY_PAGEDOWN;

    return asciiChar;
}

typedef struct regs_t
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
} regs_t;

regs_t abstractionCall(uint32_t spot, regs_t in)
{
    volatile uint32_t resA;
    volatile uint32_t resB;
    volatile uint32_t resC;
    volatile uint32_t resD;

    asm volatile (
        "call *%%esi"  :                //assembly
    "=a" (resA),                //output
        "=b" (resB),                //output
        "=c" (resC),                //output
        "=d" (resD) :                //output
        "a" (in.eax),                 //input
        "S" (spot),                 //input
        "b" (in.ebx),                     //input
        "c" (in.ecx),                     //input
        "d" (in.edx) :                    //input
        "memory", "cc");            //clobbers

    in.eax = resA;
    in.ebx = resB;
    in.ecx = resC;
    in.edx = resD;
    return in;
}

extern int x86InternalReadSector();
extern int x86InternalWriteSector();
uint8_t x86bbootdisk;       //set by x86.asm before main() gets called

int fwReadSector(int lba, void* location, int disk)
{
    if (disk == DISK_BOOT_MEDIA) disk = x86bbootdisk;
    if (disk == DISK_HARD_DRIVE) disk = 0x80;

    regs_t in;
    in.eax = lba;
    in.ebx = (size_t) location;
    in.edx = disk;
    in = abstractionCall((size_t) x86InternalReadSector, in);
    return in.eax == 0 ? true : false;
}

int fwWriteSector(int lba, void* location, int disk)
{
    if (disk == DISK_BOOT_MEDIA) disk = x86bbootdisk;
    if (disk == DISK_HARD_DRIVE) disk = 0x80;

    regs_t in;
    in.eax = lba;
    in.ebx = (size_t) location;
    in.edx = disk;
    in = abstractionCall((size_t) x86InternalWriteSector, in);
    return in.eax == 0 ? true : false;
}