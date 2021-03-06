#include <stdint.h>
#include "setidt.h"
#include "generate_interrupt_handlers.h"
#include <fb.h>

struct IDT {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));

typedef enum {
    TASK_GATE = 0x5,
    INT_GATE = 0xE,
    TRAP_GATE = 0xF
} IDT_Entry_type;

struct IDTEntry { // THIS ISN'T A REAL DESCRIPTOR entry. it is only a convenience.
   uintptr_t offset; // offset bits
   uint16_t selector; // a code segment selector in GDT
   uint8_t privilege_level; // 0 to 3
   IDT_Entry_type entry_type; // type and attributes, see above
};

void build_IDT_entry (uint16_t *target, struct IDTEntry source) {
    target[0] = (uint16_t)source.offset & 0xFFFF;
    target[1] = source.selector;
    uint8_t present = 1 << 7;
    uint8_t privilege = (source.privilege_level & 3) << 5;
    target[2] = (present | privilege | source.entry_type) << 8;
    target[3] = (uint16_t)(source.offset >> 16);
}

int64_t idt_table[256];
struct IDT idt;
void idt_load () {
    struct IDTEntry type;
    type.selector = 0x08;
    type.privilege_level = 0;
    type.entry_type = INT_GATE;
    // Divide by 0
    type.offset = (uintptr_t)&interrupt_handler_0;
    build_IDT_entry((uint16_t*)&idt_table[0], type);

    // Debug
    type.offset = (uintptr_t)&interrupt_handler_3;
    build_IDT_entry((uint16_t*)&idt_table[3], type);

    // General Protection fault
    type.offset = (uintptr_t)&interrupt_handler_13;
    build_IDT_entry((uint16_t*)&idt_table[13], type);

    // Keyboard
    type.offset = (uintptr_t)&interrupt_handler_33;
    build_IDT_entry((uint16_t*)&idt_table[33], type);

    idt.base = (uintptr_t)&idt_table;
    idt.limit = 256 * 8 - 1;

    load_idt((void*)&idt);
}
