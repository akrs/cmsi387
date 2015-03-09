#include <stdint.h>
#include "fb.h"
int x;
void interrupt_handler(uint32_t error_code, uint32_t interrupt) {
    fb_write_str("Interrupt handled");
    x = error_code + interrupt;
}
