#include "setidt.h"
#include <stdint.h>

struct IDT {
    uint32_t limit;
    uint32_t base;
} __attribute__((packed));
/*
typedef enum {
    TASK_GATE = 0x5,
    INT_GATE = 0xE,
    TRAP_GATE = 0xF
} IDT_Entry_type;

struct IDTEntry { // THIS ISN'T A REAL DESCRIPTOR entry. it is only a convenience.
   uint32_t offset; // offset bits
   uint16_t selector; // a code segment selector in GDT
   IDT_Entry_type entry_type; // type and attributes, see below
};

void build_IDT_entry (uint16_t *target, struct IDTEntry source) {
    target[0] = source.offset & 0xFFFF;
    target[1] = source.selector;
    target[2] =

    target[3]
}
*/

void idt_load () {
    struct IDT idt;
    int64_t idt_table[256];
    idt.base = (uint32_t)&idt_table;
    idt.limit = 256 * 8;
    load_idt((void*)&idt);
}
