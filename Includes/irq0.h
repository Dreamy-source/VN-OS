#ifndef IRQ0_H
#define IRQ0_H

#include "pic.h"
#include "video.h"

unsigned int timer_ticks = 0;

void irq0_handler()
{
    timer_ticks += 1;
    send_eoi(0);
}

static inline int convert_ticks_to_sec(unsigned int ticks)
{
    return ticks / 1000;
}

static inline void sleep_ms(unsigned int ms) {
    unsigned int start = timer_ticks;
    while (timer_ticks - start < ms) {
        __asm__ volatile ("hlt");
    }
}

static inline void sleep_sec(unsigned int sec)
{
    sleep_ms(sec * 1000);
}

static inline void sleep_min(unsigned int min)
{
    sleep_sec(min * 60);
}

static inline void sleep_hrs(unsigned int hrs)
{
    sleep_min(hrs * 60);
}

static inline void sleep_dys(unsigned int dys)
{
    sleep_hrs(dys * 24);
}

#endif