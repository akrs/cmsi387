#include <stdint.h>
#include <fb.h>
#include <pic.h>
#include <keyboard.h>

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
uint32_t *e;
/*
  CPU state is pushed onto the stack by our little function. We don't have to
  use it at all, but not having it makes our other things not line up.

  TODO: refactor the assembly code to not push the CPU state before it pushes the
        important stuff.
*/
void interrupt_handler (struct cpu_state cpu, uint32_t interrupt, uint32_t error_code) {
    x = &cpu;
    e = &error_code;
    // Gotta be fast, and switch statements are fast. dealwithit.gif
    switch (interrupt) {
        case 0:
            fb_write_str("You have divided by 0 and displeased Geoff.\n");
            break;
        case 3:
            fb_write_str("Debug caught.\n");
            break;
        case 13:
            fb_write_str("General protection fault\n");
            break;
        case 33:
            fb_write_str("you pressed the keyboard!");
            handle_keyboard();
            ack_pic();
            break;
        default:
            fb_write_str("Uh oh: ");
            fb_write_hex(interrupt);
            fb_write_str("\n");
            ack_pic();
            break;
    }
}
