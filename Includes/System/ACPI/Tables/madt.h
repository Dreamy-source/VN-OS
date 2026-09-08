#ifndef MADT_H
#define MADT_H

typedef struct {
    SDT      Header;
    uint32_t LAPICAddress;
    uint32_t Flags;
} __attribute__((packed)) MADT;

typedef struct {
    uint8_t Type;
    uint8_t Length;
} __attribute__((packed)) MADT_Entry;

#endif