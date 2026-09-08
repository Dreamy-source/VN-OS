#ifndef RSDP_H
#define RSDP_H

#define RSDP_ALIGNMENT 16

typedef struct {
    char     Signature[8];
    uint8_t  Checksum;
    char     OEMID[6];
    uint8_t  Revision;
    uint32_t RsdtAddress;
} __attribute__((packed)) RSDP;

#endif