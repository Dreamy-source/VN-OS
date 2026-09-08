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
#include "../Includes/System/acpi.h"
#include "../Includes/System/pci.h"

extern void asm_irq0();
extern void asm_irq1();

static void check_disks()
{
    print_str("[vn]: detecting disk...\n", 0x07);
    print_str("[vn]: trying SATA...\n", 0x07);
    sata_check();
    if (DiskState.SATA) {
        print_str("[vn]: SATA found\n", 0x0A);
    }
    print_str("[vn]: trying NVMe...\n", 0x07);
    nvme_check();
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
    
    print_str("[vn]: allocating rsdp...\n", 0x07);
    RSDP* rsdp = allocate_rsdp();
    if (rsdp) {
        print_str("[vn]: rsdp found\n", 0x0A);
    } else {
        print_str("[vn]: rsdp not found\n", 0x0C);
    }
    print_str("[vn]: allocating facp...\n", 0x07);
    facp = allocate_facp();
    if (facp) {
        print_str("[vn]: facp found\n", 0x0A);
    } else {
        print_str("[vn]: facp not found\n", 0x0C);
    }

    print_str("\n", 0x07);

    console_request("[#]: ", 0x07);
    cursor_pos_after_print = cursor_pos;

    for (;;) {
        cursor_blink('_', ' ', 0x0F, 0x07, 300);
        __asm__ volatile ("hlt");
    }
}