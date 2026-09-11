#ifndef APIC_HPP
#define APIC_HPP

namespace APIC {

inline bool has_apic()
{
    uint32_t eax, ebx, ecx, edx;
    asm volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(1));
    return (edx & (1 << 9)) != 0;
}

}  // namespace

#endif