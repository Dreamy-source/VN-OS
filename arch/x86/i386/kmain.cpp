#include "drivers/services/baseapi.hpp"
#include "drivers/services/hook.hpp"

extern "C" void kmain(void)
{
    VGA::fill(' ', 0x07, 80, 20);
    VGA::prints("starting system boot initialization\n", 0x07);
    VGA::prints(" [ ] starting kinit hook...\n", 0x07);
    HOOK::starthook("kinit");

    VGA::prints("\n\nWelcome to ", 0x07);
    VGA::prints("Vanilla", 0x0F);
    VGA::printsm('!', 0x07);
    VGA::prints("\n\n", 0x07);

    VGA::final_pos = VGA::cursor_pos;

    while (1)
    {
        // VGA cursor
        IO::outb(0x3D4, 0x0F);
        IO::outb(0x3D5, (uint8_t)(VGA::cursor_pos & 0xFF));
        IO::outb(0x3D4, 0x0E);
        IO::outb(0x3D5, (uint8_t)((VGA::cursor_pos >> 8) & 0xFF));
    };
}