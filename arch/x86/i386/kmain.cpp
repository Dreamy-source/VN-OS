#include "drivers/utils/uint.hpp"
#include "drivers/utils/string.hpp"

void kmain(void)
{
    VGA::print_str("meow", 0x0A);

    while (1);
}