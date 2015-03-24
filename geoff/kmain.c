#include <fb.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <io.h>
#include <multiboot.h>
#include <stdint.h>
#include <paging.h>

int kernel_main(multiboot_info_t *mbinfo) {
    fb_clear();
    fb_write_str("Hello world, I'm Geoff.\n");

    gdt_load();

    idt_load();
    asm("int 3");
    

    setup_pic();
    enable_paging();

    module_t* modules = (module_t*) mbinfo->mods_addr;
    uintptr_t address_of_module = modules->mod_start;

    typedef void (*call_module_t)(void);
    call_module_t start_program = (call_module_t) address_of_module;
    start_program();

    return 0;
}
