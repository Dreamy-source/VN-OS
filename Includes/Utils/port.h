#ifndef PORT_H
#define PORT_H

static inline uint8_t in(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void out(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint32_t inl(uint16_t port)
{
    uint32_t ret;
    __asm__ volatile ( "inl %w1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void outl(uint16_t port, uint32_t val)
{
    __asm__ volatile ( "outl %0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

#endif