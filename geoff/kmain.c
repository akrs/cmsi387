#include <fb.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <io.h>

int kernel_main() {
    fb_clear();
    fb_write_str("Hello world, I'm Geoff.\n");

    gdt_load();

    idt_load();
    asm("int 3");

    setup_pic();

    return 42;
}
