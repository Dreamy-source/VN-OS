#ifndef GAS_H
#define GAS_H

typedef struct {
    uint8_t  AddressSpace;
    uint8_t  BitWidth;
    uint8_t  BitOffset;
    uint8_t  AccessSize;
    uint64_t Address;
} __attribute__((packed)) GAS;

#endif