#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include "utils.h"

#define TAB_WIDTH 4
#define CNTRL_CHAR_LIMIT 32

size_t strlen(const char *str) {
    size_t i = 0;
    while (str[i++] != '\0') {}
    return i;
}

int iscntrl(int i) {
    return i < CNTRL_CHAR_LIMIT;
}

struct digit_stack {
    char digit;
    struct digit_stack next;
};


// Inspired by http://www.eskimo.com/~scs/cclass/int/sx11b.html
int raw_printf(void (*write_char)(char), const char *fmt, ...) {
    va_list arg;
    
    va_start(arg, fmt);

    for (const char *pos = fmt; *pos != '\0'; pos++) {
        if (iscntrl(*pos)) {
            switch (*pos) {
                case '\a':
                    break; // TODO: handle?
                case '\b':
                    break; // TODO: handle?
                case '\t':
                    for (int i = 0; i < TAB_WIDTH; i++) {
                        write_char(' ');
                    }
                    break;
                case '\r':
                    break; // LOL NOPE
                case '\n': // These all require write_char to handle them
                case '\f':
                case '\v':
                default:
                    write_char(*pos);
                    break;
            }
        }
        else if (*pos == '%') {
            char c;
            int i;
            unsigned int ui;
            //int base;
            //char str[20]; // Enough for a long
            switch (*(++pos)) {
                case 'c':
                    c = va_arg(arg, int);
                    write_char(c);
                    break;
                case 'd': // TODO: this code could probably be reused partly for hex and octal
                case 'i':
                    i = va_arg(arg, int);
                    if (i < 0) {
                        write_char('-');
                        i = -i;
                    }
                case 'u':
                    if (*pos == 'u') {
                        ui = va_arg(arg, unsigned int);
                    } else {
                        ui = (unsigned int) i;
                    }
                    while (ui > 0) {
                        char c = (char)(((int)'0') + (ui % 10));
                        write_char(c);
                        ui /= 10;
                    }
                    break;
                case 's':
                    for (char *str = va_arg(arg, char*); *str != '\0'; str++) {
                        write_char(*str);
                    }
                    break;
                default:
                    break;
            }
        } else {
            write_char(*pos);
        }
    }
    return 0;
}
