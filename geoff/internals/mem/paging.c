#include <stdint.h>
#define NUM_PAGES 1024
#include <fb.h>

uint32_t page_directory[NUM_PAGES] __attribute__((aligned(4096)));
uint32_t page_table[NUM_PAGES] __attribute__((aligned(4096)));
void enable_paging() {
    // With much help from osdev.org - http://wiki.osdev.org/Setting_Up_Paging
    for (int i = 0; i < NUM_PAGES; i++) {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }

    for (int i = 0; i < NUM_PAGES; i++) { // We want to start mapping the pages at the beginning of memory
        // As the address is page aligned, it will always leave 12 bits zeroed
        // to be used as attributes. 
        page_table[i] = (i << 12) | 3;
    }

    // attributes: supervisor level, read/write, present
    page_directory[0] = ((uintptr_t)page_table) | 3;
    // Set address of page_directory to cr3, where the MMU is expecting it
    asm volatile("mov cr3, %0":: "r" (page_directory));
    asm volatile("mov eax, cr0;"
                 "or eax, 0x80000000;"
                 "mov cr0, eax;":::"eax");

}

