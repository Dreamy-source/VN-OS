#ifndef ATA_H
#define ATA_H

#include <stdint.h>
#include "../../Utils/port.h"
#include "../../System/pci.h"
#include "../disk_state.h"

#define DATA              0x1F0
#define CHOOSE_DISK       0x1F6
#define COMMAND_OR_STATUS 0x1F7
#define MASTER_DISK       0xA0
#define GET_INFO          0xEC
#define BSY               0x80  // Busy bit

static void check_ata()
{
    out(CHOOSE_DISK, MASTER_DISK);     // master
    out(COMMAND_OR_STATUS, GET_INFO);  // IDENTIFY

    uint8_t status = in(COMMAND_OR_STATUS);
    if (status == 0) {
        return;
    }

    while (in(COMMAND_OR_STATUS) & BSY);  // wait BSY=0;

    uint16_t data = in(DATA);
    if (data != 0) {
        DiskState.ATA = true;
    }
}

#endif