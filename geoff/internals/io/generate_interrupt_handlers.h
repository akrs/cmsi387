#ifndef _GEN_INT_HAND
#define _GEN_INT_HAND

// From http://stackoverflow.com/questions/8045108/use-label-in-assembly-from-c
// We want to have the address of the first interrupt handler for our IDT.
extern void* interrupt_handler_0;
extern void* interrupt_handler_3;
extern void* interrupt_handler_13;
extern void* interrupt_handler_32;
extern void* interrupt_handler_33;

#endif
