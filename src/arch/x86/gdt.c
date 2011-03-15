/**
 * @file gdt.c
 * @brief GDT Manager
 * @author Victor Borges
 * @date Mar 15, 2011
 */

#include "gdt.h"

/**
 * The sructure of a segment descriptor, defined by Intel
 */
struct gdt_segment_descriptor
{
	/* Lowest dword */
	u16 limit_15_0;             /**< Segment limit, bits 15..0 */
	u16 base_15_0;  			/**< Base address, bits 15..0 */

	/* Highest dword */
	byte  base_23_16; 			/**< Base address bits 23..16 */
	
	/* Access Byte */
	byte  segment_type:4;
	byte  descriptor_type:1;     /**< 0=System, 1=Code/Data */
	byte  dpl:2;
	byte  present:1;
	
	byte  limit_19_16:4;         /**< Segment limit, bits 19..16 */
	
	/* Flags */
	byte  custom:1;
	byte  zero:1;
	byte  op_size:1;             /**< 0=16bits instructions, 1=32bits */
	byte  granularity:1;         /**< 0=limit in bytes, 1=limit in pages */

	byte  base_31_24; 			 /**< Base address bits 31..24 */
} __attribute__ ((packed, aligned (8)));


/**
 * The GDT register, which stores the address and size of the
 * GDT.
 */
struct gdt_register {
	/** The maximum GDT offset allowed to access an entry */
	u16 limit;
	/** Base table address */
	u32 baseAddr;
} __attribute__((packed, aligned(8)));


#define GDT_USER_PRIVILEDGE		3
#define GDT_KERNEL_PRIVILEDGE	0            
	      
/**
 * Macro that builds a flat segment descriptor
 * @param priviledge 	 User/Kernel priviledges
 * @param is_code		 Code/Data segment
 * @note
 * 	For privilegdes:
 *   - Code (bit 3 = 1): 
 *     bit 0: 1=Accessed 
 *     bit 1: 1=Readable 
 *     bit 2: 0=Non-Conforming
 *   - Data (bit 3 = 0):  
 *     bit 0: 1=Accessed  
 *     bit 1: 1=Writable 
 *     bit 2: 0=Expand up (stack-related) 
 */
#define BUILD_GDTE(priviledge,is_code)               		 \
  (struct gdt_segment_descriptor) {     	                 \
	.limit_15_0   = 	   0xffff,                           \
    .base_15_0    =  	   0,                                \
    .base_23_16   = 	   0,                                \
    .segment_type = 	   ((int)(is_code)?0xb:0x3),         \
    .descriptor_type =     1,  /* 1=Code/Data */             \
    .dpl          =		   ((priviledge) & 0x3),  		     \
    .present      =        1,                                \
    .limit_19_16  =        0xf,                              \
    .custom       =        0,                                \
    .zero         =        0,                                \
    .op_size      =        1,  /* 32 bits instr/data */      \
    .granularity  =        1,  /* limit is in 4kB Pages */   \
    .base_31_24   =        0                                 \
  }

static struct gdt_segment_descriptor gdt[GDT_NUM_SEGMENTS];

void gdt_setup(void)
{
	struct gdt_register gdtr;
	
	/* Setting GDT */
	gdt[GDT_SEGMENT_NULL]  = (struct gdt_segment_descriptor){0, };
	gdt[GDT_SEGMENT_KCODE] = BUILD_GDTE(GDT_KERNEL_PRIVILEDGE, TRUE);
	gdt[GDT_SEGMENT_KDATA] = BUILD_GDTE(GDT_KERNEL_PRIVILEDGE, FALSE);

	/* Setting GDT register */
	gdtr.baseAddr = (u32) gdt;
	gdtr.limit     = sizeof(gdt) - 1;

	/* 
	 * Commit the GDT into the CPU, 
	 * and update the segment registers. 
	 */
	asm volatile ("lgdt %0        \n\
				 ljmp %1,$1f      \n\
				 1:               \n\
				 movw %2, %%ax    \n\
				 movw %%ax,  %%ss \n\
				 movw %%ax,  %%ds \n\
				 movw %%ax,  %%es \n\
				 movw %%ax,  %%fs \n\
				 movw %%ax,  %%gs"
		:
		:"m"(gdtr),
		 "i"(GDT_SEGMENT_KCODE << 3),
		 "i"(GDT_SEGMENT_KDATA << 3)
		:"memory","eax");
		
}
