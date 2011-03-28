/** 
 * @file idt.h
 * @brief Manage the Interrupt Descriptor Table.
 * @author Victor Borges
 * @date Mar 13, 2011
 */
 
#ifndef _IDT_H_
#define _IDT_H_

#include <types.h>

/**
 *  Initialization IDT 
 **/
void idt_setup(void);

/**
 * Enable the IDT entry if handler_address != NULL, with the given
 * lowest_priviledge.
 * @param index			Index in the table
 * @param handler_addr	Handler address
 * @param priviledge	Kernel/User priviledges
 * @note IRQ Unsafe
 * @return OK		- Success \n
 * 		   EINVAL   - Invalid arguments
 */
result idt_set_handler(int index, vaddr handler_addr, int priviledge);


/**
 * Get the handler address and DPL in the 2nd and 3rd
 * parameters
 * @param index					Index in the table
 * @param [out] handler_addr	Handler address
 * @param [out] priviledge		Kernel/User priviledges
 * @note IRQ Unsafe
 * @return OK		- Success \n
 * 		   EINVAL   - Invalid arguments
 */
result idt_get_handler(int index, vaddr * handler_addr, int * priviledge);


#endif /* IDT_H_ */
