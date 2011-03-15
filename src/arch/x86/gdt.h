/**
 * @file gdt.h
 * @brief GDT Manager
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#ifndef _GDT_H_
#define _GDT_H_

#include <types.h>

/* Number of segments */
#define GDT_NUM_SEGMENTS		3  /**< Number of segment */

/*
 * Global segment selectors (GDT) for x86.
 */
#define GDT_SEGMENT_NULL 		0 	/**< NULL segment, unused by the procesor */
#define GDT_SEGMENT_KCODE		1 	/**< Kernel code segment */
#define GDT_SEGMENT_KDATA		2 	/**< Kernel data segment */

/**
 * Setup GDT
 */
void gdt_setup(void);

#endif /* _GDT_H_ */
