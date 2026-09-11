#ifndef STRING_HPP
#define STRING_HPP

#include "drivers/utils/uint.hpp"

namespace String {

inline void* memcpy(void* dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((uint8_t*)dest)[i] = ((const uint8_t*)src)[i];
    }

    return dest;
}

}  // namespace

#endif
