/**
 * @file i8259.h
 * @brief PIC Intel 8259A manager
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#ifndef _i8259_H_
#define _i8259_H_

#include <types.h>

/**
 * Setup Intel PIC 8259A
 **/
void i8259_setup();

/**
 * Enable the IRQ line to accept interruptions
 * @param irq_level		The interrupt request level (IRQL)
 **/
void i8259_enable_irq_line (int irq_level);

/**
 * Disable the IRQ line to accept interruptions
 * @param irq_level		The interrupt request level (IRQL)
 **/
void i8259_disable_irq_line (int irq_level);

#endif /* _i8259_H_ */
