#ifndef IDT_H
#define IDT_H

typedef struct {
    uint16_t low_bits;
    uint16_t segment;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t high_bits;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

static inline void idt_set_gate(uint8_t index, uint32_t base, uint16_t segment, uint8_t flags)
{
    idt[index].low_bits  = base & 0xFFFF;
    idt[index].high_bits = (base >> 16) & 0xFFFF;
    idt[index].segment   = segment;
    idt[index].zero      = 0;
    idt[index].flags     = flags;
}

static inline void idt_init()
{
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)idt;

    __asm__ volatile ("lidt %0" : : "m"(idtr));
}

static inline void idt_new_irq(uint8_t irq, uint32_t asm_irq)
{
    idt_set_gate(irq, asm_irq, 0x08, 0x8E);
}

__attribute__((noreturn))
static void default_handler()
{
    __asm__ volatile (
        "cli\n"
        "hlt"
    );
    __builtin_unreachable();
}

#endif