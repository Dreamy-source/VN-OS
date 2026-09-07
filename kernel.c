static int cursor_pos_after_print = 0;

#include <stdint.h>
#include "Includes/proc.h"
#include "Includes/port.h"
#include "Includes/video.h"
#include "Includes/pic.h"
#include "Includes/idt.h"
#include "Includes/irq0.h"
#include "Includes/irq1.h"
#include "Includes/pc_speaker.h"

extern void asm_irq0();
extern void asm_irq1();

void kmain() {
    pic_init(0x20, 0x28);
    print_str("[vn]: pic initialized\n", 0x07);

    idt_new_irq(32, (uint32_t)asm_irq0);
    idt_new_irq(33, (uint32_t)asm_irq1);
    idt_init();
    print_str("[vn]: idt initialized\n", 0x07);
    
    enable_interrupts();
    print_str("[vn]: interrupts enabled\n", 0x07);
    print_str("\n", 0x07);

    cursor_pos_after_print = cursor_pos;

    for (;;) {
        cursor_blink('_', 0x07);
        __asm__ volatile ("hlt");
    }
}