/**
 * @file memory.h
 * @brief Memory management
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <types.h>
 
/** Size of a page frame in bytes */
#define PAGE_SIZE		4096

/**
 * The corresponding memory address shift
 * @note 4kB = 2^12
 **/
#define PAGE_SHIFT		12

/**
 * This is the reserved physical interval for the 
 * x86 video memory and BIOS area.
 * TODO: Use the memory map gived by BIOS
 */
#define BIOS_VIDEO_START 0xa0000
#define BIOS_VIDEO_END   0x100000

/**
* Setup memory segmentation
**/
result memory_setup_segments();

/**
 * Initialize the physical memory pages frames system, 
 * for the physical area 
 * 
 * @param 		mem_size 		The size of the RAM 
 * @param [out] kernel_base 	The lowest address for the kernel
 * @param [out] kernel_top 	The top address for the kernel
 * 
 **/
result memory_setup_ppages (size_t mem_size,
		paddr * kernel_base, paddr * kernel_top);

/**
 * Retrive memory pages frames informations
 * @param [out] total_pages
 * @param [out] used_pages
 **/
void memory_ppages_status (count_t * total_pages,
									count_t * used_pages);

/**
 * Create a new physical memory pages
 * @return the memory pages address
 **/ 									
paddr memory_new_ppage();

/**
 * Increment the reference count for the physical memory page frame
 * @param ppage		the page frame address
 **/
result memory_incref_ppage (paddr ppage);

/**
 * Decrement the reference count for the physical memory page frame
 * @param ppage		the page frame address
 **/
result memory_decref_ppage (paddr ppage);
 
 #endif
