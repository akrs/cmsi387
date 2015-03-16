#include <fb.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <io.h>
#include <multiboot.h>
#include <stdint.h>

int kernel_main(uintptr_t ebx) {
    fb_clear();
    fb_write_str("Hello world, I'm Geoff.\n");

    gdt_load();

    idt_load();
    asm("int 3");
    

    setup_pic();

    multiboot_info_t *mbinfo = (multiboot_info_t *)ebx;
    module_t* modules = (module_t*) mbinfo->mods_addr;
    uintptr_t address_of_module = modules[0].mod_start;

    fb_write_hex(address_of_module);
    typedef void (*call_module_t)(void);
    call_module_t start_program = (call_module_t) address_of_module;
    asm("xchg bx, bx");
    start_program();

    return 0;
}
