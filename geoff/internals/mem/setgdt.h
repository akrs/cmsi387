#include <stddef.h>

#ifndef _SET_GDT
#define _SET_GDT

void set_gdt(void *GDT, size_t size);

#endif
