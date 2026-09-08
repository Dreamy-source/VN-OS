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
} __attribute__((packed)) SDT;

typedef struct {
  SDT        Header;
  uint32_t   Entries[];
} __attribute__ ((packed)) RSDT;

////////////////// FADT /////////////////
typedef struct {
    SDT      Header;
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;
    uint8_t  Reserved;
    uint8_t  PreferredPMProfile;
    uint16_t SCI_INT;
    uint32_t SMI_CMD;
    uint8_t  AcpiEnable;
    uint8_t  AcpiDisable;
    uint8_t  S4BIOS_REQ;
    uint8_t  PSTATE_CNT;
    uint32_t PM1a_EVT_BLK;
    uint32_t PM1b_EVT_BLK;
    uint32_t PM1a_CNT_BLK;
    uint32_t PM1b_CNT_BLK;
    uint32_t PM2_CNT_BLK;
    uint32_t PM_TMR_BLK;
    uint32_t GPE0_BLK;
    uint32_t GPE1_BLK;
    uint8_t  PM1_EVT_LEN;
    uint8_t  PM1_CNT_LEN;
    uint8_t  PM2_CNT_LEN;
    uint8_t  PM_TMR_LEN;
    uint8_t  GPE0_LEN;
    uint8_t  GPE1_LEN;
    uint8_t  GPE1_BASE;
    uint8_t  CST_CNT;
    uint16_t P_LVL2_LAT;
    uint16_t P_LVL3_LAT;
    uint16_t FlushSize;
    uint16_t FlushStride;
    uint8_t  DUTY_OFFSET;
    uint8_t  DUTY_WIDTH;
    uint8_t  DAY_ALRM;
    uint8_t  MON_ALRM;
    uint8_t  CENTURY;
    uint16_t IAPC_BOOT_ARCH;
    uint8_t  Reserved2;
    uint32_t Flags;
} __attribute__((packed)) FADT;

////////////////// MADT /////////////////
typedef struct {
    SDT      Header;
    uint32_t LAPICAddress;
    uint32_t Flags;
} __attribute__((packed)) MADT;

typedef struct {
    uint8_t Type;
    uint8_t Length;
} __attribute__((packed)) MADT_Entry;

////////////////// HPET /////////////////
typedef struct {
    SDT      Header;
    uint32_t EventTimerBlockID;
    uint32_t BaseAddressLow;
    uint32_t BaseAddressHigh;
    uint8_t  HPETNumber;
    uint16_t MinimumTick;
    uint8_t  PageProtection;
} __attribute__((packed)) HPET;

static RSDP* locate_rsdp()
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

static void* locate_acpi_table(RSDT* rsdt, unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
    unsigned int entries = (rsdt->Header.Length - sizeof(SDT)) / 4;

    for (int i = 0; i < entries; i++) {
        SDT *header = (SDT *) rsdt->Entries[i];
        if (header->Signature[0] == b0 &&
            header->Signature[1] == b1 &&
            header->Signature[2] == b2 &&
            header->Signature[3] == b3)
            { return (void *)header; }
    }

    return NULL;
}

#endif