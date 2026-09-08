#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>
#include <stddef.h>

#define RSDP_ALIGNMENT 16

typedef struct {
    char     Signature[8];
    uint8_t  Checksum;
    char     OEMID[6];
    uint8_t  Revision;
    uint32_t RsdtAddress;
} __attribute__((packed)) RSDP;

typedef struct {
    char     Signature[4];
    uint32_t Length;
    uint8_t  Revision;
    uint8_t  Checksum;
    char     OEMID[6];
    char     OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
    uint32_t LAPICAddress;
    uint32_t Flags;
} __attribute__((packed)) MADT;

typedef struct {
    uint8_t Type;
    uint8_t Length;
} __attribute__((packed)) MADT_Entry;

typedef struct {
    char     Signature[4];
    uint32_t Length;
    uint8_t  Revision;
    uint8_t  Checksum;
    char     OEMID[6];
    char     OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} __attribute__((packed)) SDT;

typedef struct {
  SDT        Header;
  uint32_t   Entries[];
} __attribute__ ((packed)) RSDT;

static RSDP* allocate_rsdp()
{
    for (uint32_t i = 0x000E0000; i < 0x000FFFFF; i += RSDP_ALIGNMENT) {
        char *byte = (char*)i;
        if (byte[0] == 'R' &&
            byte[1] == 'S' &&
            byte[2] == 'D' &&
            byte[3] == ' ' &&
            byte[4] == 'P' &&
            byte[5] == 'T' &&
            byte[6] == 'R' &&
            byte[7] == ' '
        ) { return (RSDP*)i; }
    }

    return 0;
}

static void* allocate_facp(RSDT *rsdt)
{
    int entries = (rsdt->Header.Length - sizeof(SDT)) / 4;

    for (int i = 0; i < entries; i++)
    {
        SDT *h = (SDT *) rsdt->Entries[i];
        if (h->Signature[0] == 'F' &&
            h->Signature[1] == 'A' &&
            h->Signature[2] == 'C' &&
            h->Signature[3] == 'P') 
        { return (void *)h; }
    }

    return NULL;
}

#endif