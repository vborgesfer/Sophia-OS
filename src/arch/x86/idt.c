/** 
 * @file idt.c
 * @brief Implementation of the Interrupt Descriptor Table manager
 * @author Victor Borges
 * @date Mar 13, 2011
 */

#include <errno.h>
 
#include "idt.h"
#include "gdt.h"


/**
 * Number of IDT entries.
 * Intel doc limits this is 256 entries.
 */
#define IDT_NUM      256

/**
 * An entry in the IDT, ie a reference to a interrupt/trap routine 
 * or a task gate to handle the sw/hw interrupts and exceptions.
 */
struct idt_entry
{
	/* Low dword */
	u16 lowOffset;  	  /**< 15..0, offset of the routine in the segment */
	u16 segmentSelector;  /**< 31..16, the ID of the segment */

	/* High dword */
	byte reserved:5;   	/**< 4..0 */
	byte flags:3;      	/**< 7..5 */
	byte type:3;  		/**< 10..8 (interrupt gate, trap gate...) */
	byte op_size:1;	    /**< 11 (0=16bits instructions, 1=32bits instr.) */
	byte zero:1;		/**< 12 */
	byte dpl:2;    	    /**< 14..13 */
	byte present:1;		/**< 15 */
	
	u16 highOffset;   	/**< 31..16 */
	
} __attribute__((packed));


/**
 * The IDT register, which stores the address and size of the IDT.
 */
struct idt_register
{
	/** The maximum GDT offset allowed to access an entry in the GDT */
	u16  limit;

	/** Base address */
	u32 base_addr;
} __attribute__((packed, aligned (8)));

static struct idt_entry idt[IDT_NUM];

void idt_setup()
{
	int i;
	struct idt_register idtr;
	
	for (i = 0; i < IDT_NUM; i++)
	{
		idt[i].segmentSelector = GDT_SEGMENT_KCODE << 3; /* Maybe */
		idt[i].reserved 	= 0;
		idt[i].flags 		= 0;
		idt[i].type 		= 0x6;	/* Interrupt gate */
		idt[i].op_size 		= 1;	/* 32b instructions */
		idt[i].zero 		= 0;
		
		idt[i].lowOffset 	= 0;
		idt[i].highOffset 	= 0;
		idt[i].dpl 			= 0;
		idt[i].present		= 0;
	}
		
	idtr.base_addr = (u32) idt;
	/* The limit is the maximum offset in bytes from the base address */
	idtr.limit = sizeof(idt) - 1;
	
	/* Register IDT into CPU */
	asm volatile ("lidt %0\n"::"m"(idtr):"memory");
}

result idt_set_handler (int index, vaddr handler_addr, int priviledge)
{
	if ((index < 0) || (index >= IDT_NUM))
		return EINVAL;
	if ((priviledge < 0) || (priviledge > 3))
		return EINVAL;

	if (handler_addr)
	{
		idt[index].lowOffset 	= handler_addr & 0xffff;
		idt[index].highOffset 	= (handler_addr >> 16) & 0xffff;
		idt[index].dpl 			= priviledge;
		idt[index].present		= 1;
	} else {
		idt[index].lowOffset 	= 0;
		idt[index].highOffset 	= 0;
		idt[index].dpl 			= 0;
		idt[index].present		= 0;
	}
	
	return OK;
}


result idt_get_handler (int index, vaddr * handler_addr, 
			int * priviledge)
{
	if ((index < 0) || (index >= IDT_NUM))
		return EINVAL;

	if (handler_addr)
		*handler_addr = idt[index].lowOffset 
						| (idt[index].highOffset << 16);
	if (priviledge)
		*priviledge = idt[index].dpl;

	return OK;
}
