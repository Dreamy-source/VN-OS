#ifndef PIC_HPP
#define PIC_HPP

namespace PIC {

inline void pic_init(uint16_t irq0_8_offset, uint16_t irq8_15_offset)
{
    IO::outb(0x20, 0x10 | 0x01);
    IO::outb(0xA0, 0x10 | 0x01);

    IO::outb(0x21, irq0_8_offset);
    IO::outb(0xA1, irq8_15_offset);

    IO::outb(0x21, 1 << 2);
    IO::outb(0xA1, 2);

    IO::outb(0x21, 0x01);
    IO::outb(0xA1, 0x01);

    IO::outb(0x21, 0b11111000);
    IO::outb(0xA1, 0b11111111);
}

}  // namespace

#endif