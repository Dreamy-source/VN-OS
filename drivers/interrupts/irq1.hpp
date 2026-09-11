#ifndef IRQ1_HPP
#define IRQ1_HPP

const char scancode_ascii[128] = {
    0,    27,   '1',  '2',  '3',  '4',  '5',  '6',   // 0x00-0x07
    '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',  // 0x08-0x0F
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   // 0x10-0x17
    'o',  'p',  '[',  ']',  '\n', 0,    'a',  's',   // 0x18-0x1F
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',   // 0x20-0x27
    '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',   // 0x28-0x2F
    'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',   // 0x30-0x37
    0,    ' ',  0,    0,    0,    0,    0,    0,     // 0x38-0x3F
    0,    0,    0,    0,    0,    0,    0,    '7',   // 0x40-0x47
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',   // 0x48-0x4F
    '2',  '3',  '0',  '.',  0,    0,    0,    0,     // 0x50-0x57
    0,    0,    0,    0,    0,    0,    0,    0,     // 0x58-0x5F
    0,    0,    0,    0,    0,    0,    0,    0,     // 0x60-0x67
    0,    0,    0,    0,    0,    0,    0,    0,     // 0x68-0x6F
    0,    0,    0,    0,    0,    0,    0,    0,     // 0x70-0x77
    0,    0,    0,    0,    0,    0,    0,    0,     // 0x78-0x7F
};

char     buffer[4096];
uint32_t buffer_pos = 0;

extern "C" void asm_irq1_handler(void);

class IRQ1 : public IRQ {
public:
    void handler() override {
        uint8_t scancode = IO::inb(0x60);
        if (scancode & 0x80)
        {} else {
            uint8_t c = scancode_ascii[scancode];

            if (scancode == 0x1C)
            {
                buffer[buffer_pos] = '\0';

                if (STRING::strncmp(buffer, "echo", 4) == 0)
                {
                    VGA::cursor_pos += 80 - (VGA::cursor_pos % 80);
                    VGA::prints(buffer + 5, 0x07);
                    VGA::prints("\n", 0x07);
                }

                VGA::cursor_pos += 80 - (VGA::cursor_pos % 80);
                buffer_pos = 0;
                VGA::final_pos = VGA::cursor_pos;
            }
            if (scancode == 0x0E)
            {
                if (VGA::cursor_pos > VGA::final_pos)
                {
                    VGA::cursor_pos--;
                    VGA::VGA_VIDEO[VGA::cursor_pos * 2] = ' ';
                    VGA::VGA_VIDEO[VGA::cursor_pos * 2 + 1] = 0x07;
                    if (buffer_pos > 0)
                    {
                        buffer_pos--;
                        buffer[buffer_pos] = 0x00;
                    }
                } 
            }
            if (scancode != 0x1C && scancode != 0x0E)
            {
                buffer[buffer_pos] = c;
                buffer_pos++;
                VGA::VGA_VIDEO[VGA::cursor_pos * 2] = c;
                VGA::VGA_VIDEO[VGA::cursor_pos * 2 + 1] = 0x07;
                VGA::cursor_pos++;
            }
        }
        IO::outb(0x20, 0x20);
    }
};

static IRQ1 irq1_instance;
extern "C" void irq1_handler_cpp(void)
{
    irq1_instance.handler();
}

#endif