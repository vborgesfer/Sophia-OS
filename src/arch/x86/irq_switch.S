/**
 * @file irq_switch.S
 * @brief The adapter pattern designed to call IRQs handlers
 		when an interrupt occurs.
 * @author Victor Borges
 * @date Mar 16, 2011
 */


.file "irq_switch.S"

.text

/** 
 * The address of the table of handlers 
 * @see irq.c
 **/
.extern irq_handler_array

/* The address of the table of switch */
.globl irq_switch_array


/* These pre-handlers are for IRQ (Master PIC) */
.irp id, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15

	.p2align 2, 0x90

	irq_switch_\id:
	.type irq_switch_\id,@function

		/*
		 * Backup the CPU context
		 */

		/* Fake error code */
		pushl $0

		/* Backup the actual context */
		pushl %ebp
		movl %esp, %ebp

		pushl %edi
		pushl %esi
		pushl %edx
		pushl %ecx
		pushl %ebx
		pushl %eax
		subl  $2,%esp
		pushw %ss
		pushw %ds
		pushw %es
		pushw %fs
		pushw %gs

		/* Send EOI to PIC */	
		movb  $0x20, %al
		outb  %al, $0x20
	
		/*
		 * Call the handler with IRQ number as argument
		 */
		pushl $\id
		leal  irq_handler_array,%edi
		call  *\id*4(%edi)
		addl  $4, %esp

		/* Restore the context */
		popw  %gs
		popw  %fs
		popw  %es
	    popw  %ds
		popw  %ss
		addl  $2,%esp
		popl  %eax
		popl  %ebx
		popl  %ecx
		popl  %edx
		popl  %esi
		popl  %edi
		popl  %ebp

		/* Remove fake error code */
		addl  $4, %esp

		iret
	.endr

/** 
 * The irq_switch_array
 * @see irq.c
 **/
.section ".rodata"
.p2align 5, 0x0
irq_switch_array:
	.irp id, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
		.long (irq_switch_\id)
	.endr
