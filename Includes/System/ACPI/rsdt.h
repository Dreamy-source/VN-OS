#ifndef RSDT_H
#define RSDT_H

#include "sdt.h"

typedef struct {
  SDT        Header;
  uint32_t   Entries[];
} __attribute__ ((packed)) RSDT;

#endif