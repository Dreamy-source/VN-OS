#ifndef VGA_HPP
#define VGA_HPP

namespace VGA {

volatile uint8_t *VGA_VIDEO = (volatile uint8_t*)0xB8000;

inline void print_str(const char* str, const char attribute)
{
    for (uint32_t i = 0; str[i] != '\0'; i++)
    {
        VGA_VIDEO[i * 2] = str[i];
        VGA_VIDEO[i * 2 + 1] = attribute;
    }
}

}  // namespace

#endif