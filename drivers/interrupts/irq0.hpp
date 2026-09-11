#ifndef IRQ0_HPP
#define IRQ0_HPP

extern "C" void asm_irq0_handler(void);

class IRQ0 : public IRQ {
public:
    static inline uint32_t timer_ticks = 0;

    void handler() override {
        timer_ticks++;
        IO::outb(0x20, 0x20);
    }
};

static IRQ0 irq0_instance;
extern "C" void irq0_handler_cpp(void)
{
    irq0_instance.handler();
}

#endif