/**
 * @file i8259.c
 * @brief Implementation of the PIC Intel 8259A manager
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#include "ioports.h"
#include "i8259.h"

#define PIC_MASTER 0x20
#define PIC_SLAVE  0xa0

void i8259_setup(void)
{
	/* Send ICW1: 8086 mode + NOT Single ctrl + call address
	 interval=8 */
	outb(0x11, PIC_MASTER);
	outb(0x11, PIC_SLAVE);

	/* Send ICW2: ctrl base address */
	outb(0x20, PIC_MASTER+1);
	outb(0x28, PIC_SLAVE+1);

	/* Send ICW3 master: mask where slaves are connected */
	outb(0x4, PIC_MASTER+1);
	/* Send ICW3 slave: index where the slave is connected on master */
	outb(0x2, PIC_SLAVE+1);

	/* Send ICW4: 8086 mode, fully nested, not buffered, no implicit EOI */
	outb(0x1, PIC_MASTER+1);
	outb(0x1, PIC_SLAVE+1);

	/* Send OCW1:
	* Closing all IRQs : waiting for a correct handler The only IRQ
	* enabled is the cascade (that's why we use 0xFB for the master) */
	outb(0xFB, PIC_MASTER+1);
	outb(0xFF, PIC_SLAVE+1);
}


void i8259_enable_irq_line(int numirq)
{
	if(numirq < 8)
		/*  irq on master PIC */
		outb((inb(PIC_MASTER+1) & ~(1 << numirq)), PIC_MASTER+1);
	else
		/*  irq on slave PIC */
		outb((inb(PIC_SLAVE+1) & ~(1 << (numirq-8))), PIC_SLAVE+1);
}


void i8259_disable_irq_line(int numirq)
{
	if(numirq < 8)
		/*  irq on master PIC */
		outb((inb(PIC_MASTER+1) | (1 << numirq)), PIC_MASTER+1);
	else
		/*  irq on slave PIC */
		outb((inb(PIC_SLAVE+1) | (1 << (numirq-8))), PIC_SLAVE+1);
}
