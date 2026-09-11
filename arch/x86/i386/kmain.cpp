#include "drivers/utils/uint.hpp"
#include "drivers/utils/string.hpp"
#include "drivers/video/vga.hpp"

extern "C" void kmain(void)
{
    VGA::print_str("meow", 0x0A);

    while (1);
}