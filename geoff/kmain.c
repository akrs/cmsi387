#include "fb.h"
#include "serial.h"
#include "gdt.h"

int kernel_main() {
    fb_clear();
    fb_write_str("Hello World\n");
    for (int i = 0; i < 3; i++) {
        fb_write_str("Goodbye, World!\t");
    }
    fb_write_str("\n");
    for (int i = 0; i < 80; i++) {
        char num = (48 + i % 4);
        char* ptr = &num;
        fb_write(ptr, 1);
    }

    serial_write_str("Hello world!");
    gdt_load();
    fb_write_str("\nGDT Loaded.");
    return 42;
}
