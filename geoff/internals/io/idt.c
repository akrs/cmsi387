#include <stdint.h>
#include "setidt.h"
#include "generate_interrupt_handlers.h"

struct IDT {
    uintptr_t base;
    uint16_t limit;
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
    target[3] = (uint16_t)source.offset >> 16;
}

int64_t idt_table[256];
struct IDT idt;
void idt_load () {
    struct IDTEntry type;
    type.selector = 0x8;
    type.privilege_level = 0;
    type.entry_type = INT_GATE;
    type.offset = (uintptr_t)interrupt_handler_0;
    build_IDT_entry((uint16_t*)&idt_table[0], type);
    type.offset = (uintptr_t)interrupt_handler_1;
    build_IDT_entry((uint16_t*)&idt_table[1], type);
    type.offset = (uintptr_t)interrupt_handler_2;
    build_IDT_entry((uint16_t*)&idt_table[2], type);
    type.offset = (uintptr_t)interrupt_handler_3;
    build_IDT_entry((uint16_t*)&idt_table[3], type);
    type.offset = (uintptr_t)interrupt_handler_4;
    build_IDT_entry((uint16_t*)&idt_table[4], type);
    type.offset = (uintptr_t)interrupt_handler_5;
    build_IDT_entry((uint16_t*)&idt_table[5], type);
    type.offset = (uintptr_t)interrupt_handler_6;
    build_IDT_entry((uint16_t*)&idt_table[6], type);
    type.offset = (uintptr_t)interrupt_handler_7;
    build_IDT_entry((uint16_t*)&idt_table[7], type);
    idt.base = (uintptr_t)&idt_table;
    idt.limit = 256 * 8 - 1;
    load_idt((void*)&idt);
}
