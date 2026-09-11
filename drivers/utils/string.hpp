#ifndef STRING_HPP
#define STRING_HPP

namespace STRING {

inline void* memcpy(void* dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((uint8_t*) dest)[i] = ((const uint8_t*) src)[i];
    }

    return dest;
}

inline int strcmp(const char* str0, const char* str1)
{
    while (*str0 && (*str0 == *str1))
    {
        str0++;
        str1++;
    }
    return *(const uint8_t*)str0 - *(const uint8_t*)str1;
}

inline int strncmp(const char* str0, const char* str1, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (str0[i] != str1[i])
            return (uint8_t)str0[i] - (uint8_t)str1[i];
        if (str0[i] == '\0')
            return 0;
    }
    return 0;
}

}  // namespace

#endif
