#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include <idt.h>

int kernel_main() {
    fb_clear();
    fb_write_str("Hello world, I'm Geoff.\n");

    gdt_load();

    idt_load();
    __asm__("int $4");

    return 42;
}
