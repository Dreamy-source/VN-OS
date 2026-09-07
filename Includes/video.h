#ifndef VIDEO_H
#define VIDEO_H

static int cursor_pos = 0;

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

static inline void cursor_blink(const char symbol, const char attribute)
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    video[cursor_pos * 2] = symbol;
    video[cursor_pos * 2 + 1] = attribute;
}

static inline void cursor_clear_symbol()
{
    volatile unsigned char* video = (volatile unsigned char*)0xB8000;
    video[cursor_pos * 2] = ' ';
    video[cursor_pos * 2 + 1] = 0x0F;
}

#endif