#ifndef PC_SPEAKER_H
#define PC_SPEAKER_H

#include <stdint.h>
#include "../Utils/port.h"
#include "../Interrupts/Handlers/irq0.h"

#define C4  262
#define D4  294
#define E4  330
#define F4  349
#define G4  392
#define A4  440
#define Bb4 466
#define B4  494
#define C5  523

#define PLAY(note, ms) beep_sound(note, ms); sleep_ms(50)
#define PAUSE(ms) sleep_ms(ms)

static void play_sound(uint32_t freq)
{
    uint32_t div = 1193180 / freq;

    out(0x43, 0xB6);
    out(0x42, div & 0xFF);
    out(0x42, (div >> 8) & 0xFF);

    uint8_t tmp = in(0x61);
    if (tmp != (tmp | 3)) {
        out(0x61, tmp | 3);
    }
}

static void disable_sound()
{
    uint8_t tmp = in(0x61) & 0xFC;
    out(0x61, tmp);
}

void beep_sound(uint32_t freq, uint32_t ms)
{
    play_sound(freq);
    sleep_ms(ms);
    disable_sound();
}

#endif