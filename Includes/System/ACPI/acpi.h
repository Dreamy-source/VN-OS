#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>
#include <stddef.h>
#include "rsdp.h"
#include "rsdt.h"
#include "sdt.h"
#include "gas.h"
#include "Tables/fadt.h"
#include "Tables/madt.h"
#include "Tables/hpet.h"

static FADT* fadt = NULL;

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

static void fadt_init(RSDT* rsdt)
{
    fadt = (FADT*)locate_acpi_table(rsdt, 'F', 'A', 'C', 'P');
}

static void fadt_reboot()
{    
    if (fadt) {
        out(fadt->ResetRegister.Address, fadt->ResetValue);
    }
}

static void fadt_shutdown()
{
    if (fadt) {
        // PM1a_CNT_BLK - control port
        // SLP_TYPa = 7 (shutdown)shutdown)

        // SLP_EN = 1 << 13 (enable sleep/
        outw(fadt->PM1a_CNT_BLK, (7 << 10) | (1 << 13));
    }
}

#endif