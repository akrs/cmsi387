#include "fb.h"

int kernel_main() {
    /* for (int i = 0; i < 2000; i++) {
        fb_write_cell(i, '\0', BLACK, BLACK);
    } */
    fb_write('A', 1);
    return 42;
}
