#ifndef HOOK_HPP
#define HOOK_HPP

namespace HOOK {

inline bool IGNORE_APIC_CHECK = true;

inline void starthook(const char* hook)
{
    if (STRING::strcmp(hook, "kinit") == 0)
    {
        if (APIC::has_apic() && !IGNORE_APIC_CHECK)
        {
            VGA::prints(" [X] APIC found\n", 0x07);
            // apic init
            IDT::idt_init_apic();
        } else {
            VGA::prints(" [!] APIC not found, using PIC instead\n", 0x07);
            PIC::pic_init(0x20, 0x28);
            IDT::idt_init_pic();
            IDT::idt_set_descriptor(32, (void*)asm_irq0_handler, 0x8E);
            IDT::idt_set_descriptor(33, (void*)asm_irq1_handler, 0x8E);
            asm volatile("sti");
        }
    }
}

}  // namespace

#endif