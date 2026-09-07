static int cursor_pos_after_print = 0;

#include <stdint.h>
#include "../Includes/Utils/proc.h"
#include "../Includes/Utils/port.h"
#include "../Includes/Video/vga.h"
#include "../Includes/Interrupts/pic.h"
#include "../Includes/Interrupts/idt.h"
#include "../Includes/Interrupts/Handlers/irq0.h"
#include "../Includes/Interrupts/Handlers/irq1.h"
#include "../Includes/Audio/pc_speaker.h"
#include "../Includes/Disk/disk_state.h"
#include "../Includes/Disk/fs.h"
#include "../Includes/Disk/Types/ata.h"
#include "../Includes/Disk/Types/sata.h"
#include "../Includes/Disk/Types/nvme.h"

extern void asm_irq0();
extern void asm_irq1();

static void check_disks()
{
    print_str("[vn]: detecting disk...\n", 0x07);
    print_str("[vn]: trying ATA...\n", 0x07);
    check_ata();
    if (DiskState.ATA) {
        print_str("[vn]: ATA found\n", 0x0A);
    }
    print_str("[vn]: trying SATA...\n", 0x07);
    check_sata();
    if (DiskState.SATA) {
        print_str("[vn]: SATA found\n", 0x0A);
    }
    print_str("[vn]: trying NVMe...\n", 0x07);
    check_nvme();
    if (DiskState.NVMe) {
        print_str("[vn]: NVMe found\n", 0x0A);
    }
}

void kmain() {
    pic_init(0x20, 0x28);
    print_str("[vn]: pic initialized\n", 0x07);

    idt_new_irq(32, (uint32_t)asm_irq0);
    idt_new_irq(33, (uint32_t)asm_irq1);
    idt_init();
    print_str("[vn]: idt initialized\n", 0x07);
    
    enable_interrupts();
    print_str("[vn]: interrupts enabled\n", 0x07);
    check_disks();
    print_str("\n", 0x07);

    cursor_pos_after_print = cursor_pos;

    for (;;) {
        cursor_blink('_', 0x07);
        __asm__ volatile ("hlt");
    }
}