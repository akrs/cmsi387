#include <stdint.h>
#include "fb.h"

struct cpu_state {
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
} __attribute__((packed));

struct cpu_state *x; // keeps the 'unused variable' monsters away

/*
  CPU state is pushed onto the stack by our little function. We don't have to
  use it at all, but not having it makes our other things not line up.

  TODO: refactor the assembly code to not push the CPU state before it pushes the
        important stuff.
*/
void interrupt_handler(struct cpu_state cpu, uint32_t interrupt, uint32_t error_code) {
    x = &cpu;

    fb_write_str("Interrupt handled\n");
    fb_write_hex(interrupt);
    fb_write_str("\n");
    fb_write_hex(error_code);
    fb_write_str("\n");
}
