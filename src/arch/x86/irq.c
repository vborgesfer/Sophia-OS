/**
 * @file irq.c
 * @brief Implementation of IRQs management for x86 architecture
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#include <io/irq.h>
#include <errno.h>

#include "i8259.h"
#include "idt.h"

/**
 * Start offset of IRQs in IDT
 **/ 
#define IRQ_BASE_OFFSET   32

/** 
 * Array of IRQ switch, primary function before handler
 * @note defined in irq_switch.S
 **/
extern vaddr irq_switch_array[IRQ_NUM];

/** 
 * Array of IRQ handlers 
 * @note Used in irq_wrappers.S
 **/
irq_handler irq_handler_array[IRQ_NUM] = {NULL, };

result irq_setup()
{
	i8259_setup();
	idt_setup();
	return OK;
}

result irq_set_routine(int irq_level, irq_handler routine)
{
	result retval;
	u32 flags = 0;

	if ((irq_level < 0) || (irq_level >= IRQ_NUM))
		return EINVAL;

	disable_irq(flags);

	retval = OK;

	/* Set the irq routine to be called by the IRQ wrapper */
	irq_handler_array[irq_level] = routine;

	if (routine)
	{
		retval = idt_set_handler(IRQ_BASE_OFFSET + irq_level,
				  (vaddr) irq_switch_array[irq_level], 0);
		/* A problem occured */
		if (retval != OK)
			irq_handler_array[irq_level] = NULL;
	}
	else /* Disable this idt entry */
	{
		retval = idt_set_handler(IRQ_BASE_OFFSET + irq_level,
				  (vaddr)NULL /* Disable IDTE */,
				  0  /* Don't care */);
	}

	/* Update the PIC only if an IRQ handler has been set */
	if (irq_handler_array[irq_level] != NULL)
		i8259_enable_irq_line(irq_level);
	else
		i8259_disable_irq_line(irq_level);

	restore_irq(flags);	
	return retval;
}

irq_handler irq_get_routine(int irq_level)
{
	if ((irq_level < 0) || (irq_level >= IRQ_NUM))
		return NULL;

	/* Expected to be atomic */
	return irq_handler_array[irq_level];
}

inline void disable_irq(int flags)
{
	asm volatile("pushfl ; popl %0":"=g"(flags)::"memory");
	asm("cli\n");
}

inline void restore_irq(int flags)
{
	asm volatile("push %0; popfl"::"g"(flags):"memory");
}
