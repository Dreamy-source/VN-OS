#ifndef VIDEO_H
#define VIDEO_H

#include "../Interrupts/Handlers/irq0.h"

static int cursor_pos = 0;
static int cursor_pos_after_request = 0;

static inline void print_str(const char* msg, const char attribute)
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;

    for (int i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == '\n') {
            cursor_pos += 80 - (cursor_pos % 80);
            continue;
        }
        video[cursor_pos * 2] = msg[i];
        video[cursor_pos * 2 + 1] = attribute;
        cursor_pos++;
    }
}

static inline void print_sym(const char symbol, const char attribute)
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    video[cursor_pos * 2] = symbol;
    video[cursor_pos * 2 + 1] = attribute;
    cursor_pos++;
}

static inline void clear_screen()
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x00;
    }
}

static inline void scroll_screen()
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    
    for (int i = 0; i < 80 * 24; i++) {
        video[i * 2] = video[(i + 80) * 2];
        video[i * 2 + 1] = video[(i + 80) * 2 + 1];
    }

    for (int i = 80 * 24; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x0F;
    }

    cursor_pos = 80 * 24;
}

static inline void console_request(const char* msg, const char attribute)
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    for (int i = 0; msg[i] != '\0'; i++) {
        video[cursor_pos * 2] = msg[i];
        video[cursor_pos * 2 + 1] = attribute;
        cursor_pos++;
    }
    cursor_pos_after_request = cursor_pos;
}

static inline void cursor_blink(const char show_symbol, const char hide_symbol, const char show_attribute, const char hide_attribute, unsigned int time)
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    while (1) {
        video[cursor_pos * 2] = show_symbol;
        video[cursor_pos * 2 + 1] = show_attribute;
        sleep_ms(time);
        video[cursor_pos * 2] = hide_symbol;
        video[cursor_pos * 2 + 1] = hide_attribute;
        sleep_ms(time);
    }
}

static inline void cursor_clear_symbol()
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    video[cursor_pos * 2] = ' ';
    video[cursor_pos * 2 + 1] = 0x0F;
}

#endif