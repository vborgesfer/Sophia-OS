/**
 * @file memory.c
 * @brief Implementation of memory management for x86 architecture
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
 #include <mem/memory.h>
 #include "gdt.h"
 
 void memory_setup_segments()
 {
	 gdt_setup();
 }
 
