#include "drivers/utils/uint.hpp"
#include "drivers/utils/string.hpp"
#include "drivers/video/vga.hpp"

extern "C" void kmain(void)
{
    VGA::fill_screen(' ', 0x07, 80, 20);
    VGA::print_str("meow", 0x0A);
    VGA::print_sym('c', 0x0F);
    while (1);
}