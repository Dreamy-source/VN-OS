#ifndef HPET_H
#define HPET_H

typedef struct {
    SDT      Header;
    uint32_t EventTimerBlockID;
    uint32_t BaseAddressLow;
    uint32_t BaseAddressHigh;
    uint8_t  HPETNumber;
    uint16_t MinimumTick;
    uint8_t  PageProtection;
} __attribute__((packed)) HPET;

#endif