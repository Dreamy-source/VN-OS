#ifndef ATA_H
#define ATA_H

#include <stdint.h>
#include "../Utils/port.h"
#include "disk_state.h"

static void check_ata()
{
    out(0x1F6, 0xA0);  // master
    out(0x1F7, 0xEC);  // IDENTIFY

    uint8_t status = in(0x1F7);
    if (status == 0) {
        return;
    }

    while (in(0x1F7) & 0x80);  // wait BSY=0;

    uint16_t data = in(0x1F0);
    if (data != 0) {
        DiskState.ATA = true;
    }
}

#endif