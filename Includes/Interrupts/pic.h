#ifndef PIC_H
#define PIC_H

#define PIC1_COMMAND	0x20
#define PIC1_DATA	    0x21

#define PIC2_COMMAND	0xA0
#define PIC2_DATA	    0xA1

#define ICW1_ICW4	0x01
#define ICW1_INIT	0x10

#define ICW4_8086	0x01
#define CASCADE_IRQ 2
static inline void pic_init(int offset1, int offset2)
{
	out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

	out(PIC1_DATA, offset1);
	out(PIC2_DATA, offset2);

	out(PIC1_DATA, 1 << CASCADE_IRQ);
	out(PIC2_DATA, CASCADE_IRQ);
	
	out(PIC1_DATA, ICW4_8086);
	out(PIC2_DATA, ICW4_8086);

	out(PIC1_DATA, 0);
	out(PIC2_DATA, 0);

    out(PIC1_DATA, 0b11111100);
	out(PIC2_DATA, 0b11111111);
}

static inline void send_eoi(unsigned char irq)
{
    if (irq >= 8)
        out(0xA0, 0x20);

    out(0x20, 0x20);
}

#endif