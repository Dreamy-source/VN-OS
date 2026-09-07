#ifndef NVME_H
#define NVME_H

#include <stdint.h>
#include "../../Utils/port.h"
#include "../../System/pci.h"
#include "../disk_state.h"

#define MSC          0x01  // Mass Storage Controller
#define CLASS_OFFSET 8
#define NVME         0x08

static void check_nvme()
{
    for (uint16_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            uint32_t class_code = pci_read(bus, slot, 0, CLASS_OFFSET);
            uint8_t class = (class_code >> 24) & 0xFF;

            if (class == MSC) {
                uint8_t subclass = (class_code >> 16) & 0xFF;
                if (subclass == NVME) {
                    DiskState.NVMe = true;
                }
            }
        }
    }
}

#endif