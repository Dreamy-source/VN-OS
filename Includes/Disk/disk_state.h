#ifndef DISK_STATE_H
#define DISK_STATE_H

#include <stdbool.h>

typedef struct {
    bool ATA;
    bool SATA;
    bool NVMe;
    uint32_t total_sectors;
} __attribute__((packed)) diskState;

static diskState DiskState;

#endif