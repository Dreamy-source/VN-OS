#ifndef VGA_HPP
#define VGA_HPP

#include "drivers/utils/uint.hpp"

namespace VGA {

volatile uint8_t* VGA_VIDEO = (volatile uint8_t*)0xB8000;
uint32_t cursor_pos = 0;

inline void print_str(const char* str, const char attribute)
{
    for (uint32_t i = 0; str[i] != '\0'; i++, cursor_pos++)
    {
        VGA_VIDEO[cursor_pos * 2] = str[i];
        VGA_VIDEO[cursor_pos * 2 + 1] = attribute;
    }
}

inline void print_sym(unsigned char sym, const char attribute)
{
    VGA_VIDEO[cursor_pos * 2] = sym;
    VGA_VIDEO[cursor_pos * 2 + 1] = attribute;
    cursor_pos++;
}

inline void fill_screen(uint8_t sym, const char attribute, uint8_t width, uint32_t height)
{
    for (uint32_t i = 0; i != width * height; i++)
    {
        VGA_VIDEO[i * 2] = sym;
        VGA_VIDEO[i * 2 + 1] = attribute;
    }
}

}  // namespace

#endif