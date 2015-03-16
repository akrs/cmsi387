#include <fb.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <io.h>
#include <multiboot.h>
#include <stdint.h>

int kernel_main() {
    fb_clear();
    fb_write_str("Hello world, I'm Geoff.\n");

    gdt_load();

    idt_load();
    asm("int 3");
    

    setup_pic();

    multiboot_info_t *mbinfo;
    asm("mov %0, ebx" : "=g" (mbinfo));
    uintptr_t address_of_module = mbinfo->mods_addr;
    fb_write_hex(address_of_module);
    asm("xchg bx, bx");
    typedef void (*call_module_t)(void);
    call_module_t start_program = (call_module_t) &address_of_module;
    start_program+=0;
    fb_write_str("Flags: ");
    fb_write_num(mbinfo->flags);
    fb_write_str("\nmods_count: ");
    fb_write_num(mbinfo->mods_count);
    asm("xchg bx, bx");
    start_program();

    return 0;
}
