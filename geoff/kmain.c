#include "fb.h"

int kernel_main() {
    /* for (int i = 0; i < 2000; i++) {
        fb_write_cell(i, '\0', BLACK, BLACK);
    } */
    fb_clear();
    fb_write_str("Hello World\n");
    for (int i = 0; i < 3; i++) {
        fb_write_str("Goodbye, World! \t");
    }
    fb_write_str("\n");
    for (int i = 0; i < 80; i++) {
        char num = (48 + i % 4);
        char* ptr = &num;
        fb_write(ptr, 1);
    }
    return 42;
}
