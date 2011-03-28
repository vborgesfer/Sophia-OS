/**
 * @file irq.h
 * @brief Manages IRQs and Exceptions
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
 #ifndef _IRQ_H_
 #define _IRQ_H_
 
 #include <types.h>
 
/* IRQ levels */
/* WARNING: This is x86 Intel Architecture Specification */
#define IRQ_TIMER         0  /**< System timer */
#define IRQ_KEYBOARD      1  /**< Keyboard controller */
#define IRQ_SLAVE_PIC     2  /**< Slave PIC */
#define IRQ_COM2          3  /**< Serial port controller COM2 */
#define IRQ_COM1          4  /**< Serial port controller COM1 */
#define IRQ_LPT2          5  /**< LPT port 2 or sound card */
#define IRQ_FLOPPY        6  /**< Floppy disk controller */
#define IRQ_LPT1          7  /**< LPT port 1 or sound card */
#define IRQ_8_NOT_DEFINED 8  /**< Not defined IRQ level */
#define IRQ_RESERVED_1    9  /**< Usually used for SCSI host adapter */
#define IRQ_RESERVED_2    10 /**< Usually used for SCSI or NIC */
#define IRQ_RESERVED_3    11 /**< Usually used for SCSI or NIC */
#define IRQ_RESERVED_4    12 /**< Usually mouse on PS/2 */
#define IRQ_COPROCESSOR   13 /**< Math co-processor IRQL */
#define IRQ_HARDDISK      14 /**< Primary ATA channel */
#define IRQ_RESERVED_5    15 /**< Usually used for secondary ATA channel */

/** Number of IRQ levels */
#define IRQ_NUM			  16
 
/**
* IRQ handler type routine
* @param level 	The interrupt request level (IRQL)
**/
typedef void (*irq_handler)(int irq_level);
 
/**
 * Setup interruptions
 */
result irq_setup();

/**
 * Set a handler for a IRQ level
 * @param irq_level		The interrupt request level (IRQL)
 * @param routine		The IRQ routine
 * @return OK		- Success \n
 * 		   EINVAL   - Invalid arguments
 **/ 
result irq_set_routine(int irq_level, irq_handler routine);

/**
 * Get the IRQ handler for a IRQL
 * @param irq_level		The interrupt request level (IRQL)
 * @return The IRQ routine
 **/ 
irq_handler irq_get_routine(int irq_level);

/**
 * Disable interrupt
 * @param flags
 **/
inline void disable_irq(int flags);

/**
 * Enable/Restore interrupt
 * @param flags
 **/ 
inline void restore_irq(int flags);

#endif /* _IRQ_H_ */
