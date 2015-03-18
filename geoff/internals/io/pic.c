#include <io.h>
#include <fb.h>

// These are here so they don't clutter the global defines.

#define MASTER_PORT_A 0x20
#define MASTER_PORT_B 0x21

#define SLAVE_PORT_A 0xA0
#define SLAVE_PORT_B 0xA1

void ack_pic () {
    /* Send ack (End Of Interrupt) to both master and slave */
    outb(MASTER_PORT_A, 0x20); /* master PIC */
    outb(SLAVE_PORT_A, 0x20);  /* slave PIC */
}

// Go see here: https://www-s.acm.illinois.edu/sigops/roll_your_own/i386/irq.html
void setup_pic () {

    /* ICW1 */
    outb(MASTER_PORT_A, 0x11); /* Master port A */
    outb(SLAVE_PORT_A, 0x11);  /* Slave port A */

    /* ICW2 */
    outb(MASTER_PORT_B, 0x20); /* Master offset of 0x20 in the IDT */
    outb(SLAVE_PORT_B, 0x28); /* Master offset of 0x28 in the IDT */

    /* ICW3 */
    outb(MASTER_PORT_B, 0x04);  /* Slaves attached to IR line 2 */
    outb(SLAVE_PORT_B, 0x02);  /* This slave in IR line 2 of master */

    /* ICW4 */
    outb(MASTER_PORT_B, 0x05); /* Set as master */
    outb(SLAVE_PORT_B, 0x01);  /* Set as slave */

    outb(MASTER_PORT_B, 0xFD); /* Disable all but keyboard */
    outb(SLAVE_PORT_B, 0xFF);  /* Disable all */

    ack_pic();
}
