#ifndef IDT_HPP
#define IDT_HPP

namespace IDT {

typedef struct {
    uint16_t Low;
    uint16_t CodeSegment;
    uint8_t  Zero;
    uint8_t  Flags;
    uint16_t High;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	Limit;
	uint32_t	Base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10)))
static inline idt_entry_t idt[256];

static idtr_t idtr;

extern "C" {
    void nothing_handler_pic(void);
    void nothing_handler_apic(void);
}

inline void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_t* descriptor = &idt[vector];

    descriptor->Low          = (uint32_t)isr & 0xFFFF;
    descriptor->CodeSegment  = 0x08;
    descriptor->Flags        = flags;
    descriptor->High         = (uint32_t)isr >> 16;
    descriptor->Zero         = 0;
}

inline void idt_init_pic(void)
{
    idtr.Base  = (uintptr_t)&idt[0];
    idtr.Limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;
    
    for (uint8_t vector = 0; vector < 32; vector++)
    {
        idt_set_descriptor(vector, (void*)nothing_handler_pic, 0x8E);
    }

    asm volatile("lidt %0" : : "m"(idtr));
}

inline void idt_init_apic(void)
{
    idtr.Base  = (uintptr_t)&idt[0];
    idtr.Limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;
    
    for (uint8_t vector = 0; vector < 32; vector++)
    {
        idt_set_descriptor(vector, (void*)nothing_handler_apic, 0x8E);
    }

    asm volatile("lidt %0" : : "m"(idtr));
}

}  // namespace

#endif