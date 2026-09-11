#ifndef VGA_HPP
#define VGA_HPP

namespace VGA {

volatile uint8_t* VGA_VIDEO = (volatile uint8_t*)0xB8000;
uint32_t cursor_pos = 0;
uint32_t final_pos = 0;

inline void prints(const char* str, const char attribute)
{
    for (uint32_t i = 0; str[i] != '\0'; i++, cursor_pos++)
    {
        if (str[i] == '\n')
        {
            cursor_pos += 80 - (cursor_pos % 80) - 1;
            continue;
        }
        VGA_VIDEO[cursor_pos * 2] = str[i];
        VGA_VIDEO[cursor_pos * 2 + 1] = attribute;
        final_pos = cursor_pos;
    }
}

inline void printsm(uint8_t sym, const char attribute)
{
    VGA_VIDEO[cursor_pos * 2] = sym;
    VGA_VIDEO[cursor_pos * 2 + 1] = attribute;
    cursor_pos++;
    final_pos = cursor_pos;
}
inline void printsmp(uint8_t sym, const char attribute, uint32_t pos)
{
    if (sym == '\n')
    {
        cursor_pos += 80 - (cursor_pos % 80) - 1;
        final_pos = cursor_pos;
        return;
    }
    VGA_VIDEO[pos * 2] = sym;
    VGA_VIDEO[pos * 2 + 1] = attribute;
    final_pos = cursor_pos;
}

inline void fill(uint8_t sym, const char attribute, uint8_t width, uint32_t height)
{
    for (uint32_t i = 0; i != width * height; i++)
    {
        VGA_VIDEO[i * 2] = sym;
        VGA_VIDEO[i * 2 + 1] = attribute;
    }
}

}  // namespace

#endif