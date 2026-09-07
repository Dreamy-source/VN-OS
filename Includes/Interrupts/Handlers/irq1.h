#ifndef IRQ1_H
#define IRQ1_H

#include "../../Video/vga.h"
#include "../pic.h"

static unsigned char buffer[80];
static unsigned char history[80];
static unsigned char history_interrupted = 0;
static unsigned char shift_pressed = 0;
static int buffer_pos = 0;
static int arrow_prefix = 0;

static const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    0, 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const char scancode_to_ascii_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
    0, 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void irq1_handler()
{
    unsigned char scancode = in(0x60);

    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
    }

    if (scancode == 0xE0) {
        arrow_prefix = 1;
        send_eoi(1);
        return;
    }

    if (scancode == 0x1C) {  // Enter
        buffer[buffer_pos] = '\0';
        cursor_clear_symbol();

        if (buffer[0] == 'e' && buffer[1] == 'c' && buffer[2] == 'h' && buffer[3] == 'o') {
            char color = 0x07;
            int bufstart = 5;

            if (buffer[5] == '%' && buffer[6] == 'a') {
                color = 0x0A;
                bufstart = 8;
            }
            for (int i = 0; i < 80; i++) {
                history[i] = buffer[i];
            }

            history_interrupted++;
            buffer_pos = 0;
            cursor_pos += 80 - (cursor_pos % 80);
            for (int i = bufstart; buffer[i] != '\0'; i++) {
                print_sym(buffer[i], color);
            }
            for (int i = 0; i < 80; i++) {
                buffer[i] = 0;
            }
            print_str("\n", 0x07);
        }
        if (buffer[0] == 'c' && buffer[1] == 'l' && buffer[2] == 'e' && buffer[3] == 'a' && buffer[4] == 'n') {
            clear_screen();
            cursor_pos = 0;
            cursor_pos_after_print = 0;
        }
        
        if (cursor_pos >= 80 * 25) {
            clear_screen();
            cursor_clear_symbol();
            cursor_pos = 0;
        }
    } else if (scancode == 0x0E) {  // Backspace
        if (cursor_pos > cursor_pos_after_print) {
            cursor_pos--;
            if (buffer_pos > 0) buffer_pos--;
            print_sym(' ', 0x07);
            cursor_clear_symbol();
            cursor_pos--;
        }

    } else if (scancode == 0x39) {  // Space
        buffer[buffer_pos++] = ' ';
        print_sym(' ', 0x07);

    } else if (arrow_prefix) {
        arrow_prefix = 0;

        if (scancode == 0x48) {
            for (int i = 0; i < 80; i++) {
                buffer[i] = 0;
            }

            for (int i = 0; i < 80; i++) {
                buffer[i] = history[i];
            }

            buffer_pos = 0;
            while (buffer[buffer_pos] != 0 && buffer_pos < 80) {
                buffer_pos++;
            }

            if (history_interrupted > 0) {
                for (int i = 0; buffer[i] != 0; i++) {
                    print_sym(buffer[i], 0x07);
                }
            }
        }

    } else if (shift_pressed) {  // Shift
        if (scancode == 0x02) {
            print_sym('!', 0x07);
            buffer[buffer_pos++] = '!';
        }
        if (scancode == 0x03) {
            print_sym('@', 0x07);
            buffer[buffer_pos++] = '@';
        }
        if (scancode == 0x04) {
            print_sym('#', 0x07);
            buffer[buffer_pos++] = '#';
        }
        if (scancode == 0x05) {
            print_sym('$', 0x07);
            buffer[buffer_pos++] = '$';
        }
        if (scancode == 0x06) {
            print_sym('%', 0x07);
            buffer[buffer_pos++] = '%';
        }
        if (scancode == 0x07) {
            print_sym('^', 0x07);
            buffer[buffer_pos++] = '^';
        }
        if (scancode == 0x08) {
            print_sym('&', 0x07);
            buffer[buffer_pos++] = '&';
        }
        if (scancode == 0x09) {
            print_sym('*', 0x07);
            buffer[buffer_pos++] = '*';
        }
        if (scancode == 0x0A) {
            print_sym('(', 0x07);
            print_sym(')', 0x07);
            buffer[buffer_pos++] = '(';
            buffer[buffer_pos++] = ')';
        }
        if (scancode == 0x0B) {
            print_sym(')', 0x07);
            buffer[buffer_pos++] = ')';
        }
        if (scancode == 0x0C) {
            print_sym('_', 0x07);
            buffer[buffer_pos++] = '_';
        }
        if (scancode == 0x0D) {
            print_sym('+', 0x07);
            buffer[buffer_pos++] = '+';
        }
        // TODO: обработать SHIFT буквы

    } else if (scancode < 128) {
        char c = scancode_to_ascii[scancode];
        if (c != 0) {
            buffer[buffer_pos++] = c;
            print_sym(c, 0x07);
        }
    }
    
    send_eoi(1);
}

#endif