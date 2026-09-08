#ifndef SATA_H
#define SATA_H

#include <stdint.h>
#include "../../Utils/port.h"
#include "../../System/PCI/pci.h"
#include "../disk_state.h"

#define BUS_MAX          256
#define SLOT_MAX         32
#define MSC              0x01  // Mass Storage Controller
#define PCI_CLASS_OFFSET 8

#define SATA_SUBCLASS    0x06

#define CLASS_OFFSET     24
#define SUBCLASS_OFFSET  16

// PCI class struct:
// 00000000 00000000  00000000 00000000
// ^class   ^subclass ^progif  ^revision
// progif - programming interface (Prog IF)

static void sata_check()
{
    for (uint16_t bus = 0; bus < BUS_MAX; bus++) {
        for (uint8_t slot = 0; slot < SLOT_MAX; slot++) {
            uint32_t class_code = pci_read(bus, slot, 0, PCI_CLASS_OFFSET);
            uint8_t class = (class_code >> CLASS_OFFSET) & 0xFF;

            if (class == MSC) {
                uint8_t subclass = (class_code >> SUBCLASS_OFFSET) & 0xFF;
                if (subclass == SATA_SUBCLASS) {
                    DiskState.SATA = true;
                    return;
                }
            }
        }
    }
}

#endif