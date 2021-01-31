#pragma once

#include <stdint.h>
#include <stddef.h>

extern uint8_t inb (uint16_t port);
extern uint16_t inw (uint16_t port);
extern uint32_t inl (uint16_t port);
extern void insb (uint16_t port, void *addr, size_t cnt);
extern void insw (uint16_t port, void *addr, size_t cnt);
extern void insl (uint16_t port, void *addr, size_t cnt);
extern void outb (uint16_t port, uint8_t  val);
extern void outw (uint16_t port, uint16_t val);
extern void outl (uint16_t port, uint32_t val);
extern void outsb (uint16_t port, const void *addr, size_t cnt);
extern void outsw (uint16_t port, const void *addr, size_t cnt);
extern void outsl (uint16_t port, const void *addr, size_t cnt);
extern void outportb (unsigned short _port, unsigned char _data);