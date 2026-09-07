#ifndef ATA_H
#define ATA_H

#include <stdint.h>
#include "../../Utils/port.h"
#include "../../System/pci.h"
#include "../disk_state.h"

#define DATA              0x1F0
#define SECTORS           0x1F2
#define SEND_BIT          0x1F3
#define CHOOSE_DISK       0x1F6
#define COMMAND_OR_STATUS 0x1F7
#define MASTER_DISK       0xA0
#define GET_INFO          0xEC
#define BSY               0x80  // Busy bit

static void ata_check()
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

static int ata_get_sectors()
{
    out(CHOOSE_DISK, MASTER_DISK);     // master
    out(COMMAND_OR_STATUS, GET_INFO);  // IDENTIFY

    uint16_t data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = in(DATA);
    }

    // data[60 - 61] - LBA28 sectors count (32-bits)
    uint32_t sectors = (data[61] << 16) | data[60];

    DiskState.total_sectors = sectors;
    return sectors;
}

static void ata_write_sector(uint32_t lba, uint16_t* data)
{
    out(CHOOSE_DISK, 0b11100000 | ((lba >> 24) & 0x0F));     // master + LBA
    out(SECTORS, 1);               // 1 sector
    out(0x1F3, lba & 0xFF);         // LBA low
    out(0x1F4, (lba >> 8) & 0xFF);  // LBA mid
    out(0x1F5, (lba >> 16) & 0xFF); // LBA high
    out(COMMAND_OR_STATUS, 0x30);   // write sectors

    while (in(COMMAND_OR_STATUS) & BSY);
    while (!(in(COMMAND_OR_STATUS) & 0x08));  // DRQ

    for (int i = 0; i < 256; i++) {
        out(DATA, data[i]);
    }
}

static void ata_read_sector(uint32_t lba, uint16_t* data)
{
    out(CHOOSE_DISK, 0b11100000 | ((lba >> 24) & 0x0F));     // master + LBA
    out(SECTORS, 1);
    out(0x1F3, lba & 0xFF);
    out(0x1F4, (lba >> 8) & 0xFF);
    out(0x1F5, (lba >> 16) & 0xFF);
    out(COMMAND_OR_STATUS, 0x20);       // read sectors

    while (in(COMMAND_OR_STATUS) & BSY);
    while (!(in(COMMAND_OR_STATUS) & 0x08));  // DRQ

    for (int i = 0; i < 256; i++) {
        data[i] = in(DATA);
    }
}


#endif