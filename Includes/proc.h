#ifndef PROC_H
#define PROC_H

static inline void freez_prc()
{
    __asm__ volatile ("hlt");
}

static inline void disable_interrupts()
{
    __asm__ volatile ("cli");
}

static inline void enable_interrupts()
{
    __asm__ volatile ("sti");
}

static inline void infinite_yield()
{
    for (;;) {
        __asm__ volatile ("hlt");
    }
}

static inline void catch_return_from_interrupt()
{
    __asm__ volatile ("jmp $");
}

#endif