#include "drivers/utils/uint.hpp"
#include "drivers/utils/string.hpp"
#include "drivers/video/vga.h"

void kmain(void)
{
    VGA::print_str("meow", 0x0A);

    while (1);
}