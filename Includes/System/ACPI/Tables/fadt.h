#ifndef FADT_H
#define FADT_H

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

    GAS      ResetRegister;
    uint8_t  ResetValue;
} __attribute__((packed)) FADT;

#endif