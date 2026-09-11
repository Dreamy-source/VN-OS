#ifndef IRQ_HPP
#define IRQ_HPP

class IRQ {
public:
    virtual void handler() = 0;
};

#endif