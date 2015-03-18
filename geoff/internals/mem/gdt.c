#include <stdint.h>
#include "setgdt.h"

struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t type;
};

/**
 * \param target A pointer to the 8-byte GDT entry
 * \param source An arbitrary structure describing the GDT entry
 */
void encode_gdt_entry(uint8_t *target, struct GDT source) {
    // Check the limit to make sure that it can be encoded

    if (source.limit > 65536) {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    } else {
        target[6] = 0x40;
    }

    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0xF;

    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // And... Type
    target[5] = source.type;
}

uint64_t global_descriptor_table[4];
void gdt_load() {
    struct GDT source[4];
    source[0].base=0;
    source[0].limit=0;
    source[0].type=0;            // Selector 0x00 cannot be used
    source[1].base=0;
    source[1].limit=0xffffffff;
    source[1].type=0x9A;         // Selector 0x08 will be our code
    source[2].base=0;
    source[2].limit=0xffffffff;
    source[2].type=0x92;         // Selector 0x10 will be our data
    // TODO: Task State Segment after we get context swtiching stuff

    for (int i = 0; i < 4; i++) {
        encode_gdt_entry((uint8_t*)&global_descriptor_table[i], source[i]);
    }

    set_gdt(&global_descriptor_table, sizeof(global_descriptor_table));
}
