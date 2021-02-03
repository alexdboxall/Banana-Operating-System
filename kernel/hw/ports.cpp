#include "hw/ports.hpp"

extern inline uint8_t inb(uint16_t port);
extern inline uint16_t inw(uint16_t port);
extern inline uint32_t inl(uint16_t port);
extern inline void insb(uint16_t port, void* addr, size_t cnt);
extern inline void insw(uint16_t port, void* addr, size_t cnt);
extern inline void insl(uint16_t port, void* addr, size_t cnt);
extern inline void outb(uint16_t port, uint8_t  val);
extern inline void outw(uint16_t port, uint16_t val);
extern inline void outl(uint16_t port, uint32_t val);
extern inline void outsb(uint16_t port, const void* addr, size_t cnt);
extern inline void outsw(uint16_t port, const void* addr, size_t cnt);
extern inline void outsl(uint16_t port, const void* addr, size_t cnt);
extern inline void outportb(unsigned short _port, unsigned char _data);