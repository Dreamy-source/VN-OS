#ifndef PCI_H
#define PCI_H

#include <stdint.h>
#include "../../Utils/port.h"

#define NO_DEVICE 0xFFFF

uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    // bus - index of bus (0-255)
    // slot - device on bus (0-31)
    // func - device function (0-7) (ex: audio card: 0 = audio, 1 = HDMI)
    // offset - offset in configuration (0-255)
    // offset.VendorID - 0x00
    // offset.ClassCode - offset 0x08
    // offset.BAR0 - offset 0x10
    // device address - bus:slot:func

    // offset & 0xFC - 4 bytes align
    // config reads by 32 bits (4 bytes)
    // 0x80000000 - enable bit (read-configuration) 
    
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
  
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
  
    outl(0xCF8, address);
    return inl(0xCFC);
}

uint16_t pci_read_vendor(uint8_t bus, uint8_t slot) {
    uint32_t vendor = pci_read(bus, slot, 0, 0);
    if (vendor == NO_DEVICE) return NO_DEVICE;
    return (uint16_t)vendor;
}

#endif
