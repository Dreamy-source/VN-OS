#ifndef DISK_STATE_H
#define DISK_STATE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool ATA;
    bool SATA;
    bool NVMe;
} __attribute__((packed)) diskState;

static diskState DiskState;

#endif