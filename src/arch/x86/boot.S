/** 
 * Multiboot standard, as defined by the Grub documentation
 * Author: Victor Borges
 * Creation: Feb 28, 2011
 */
	
#define BOOT_S

#include <boot/multiboot.h>

	/* The multiboot header */
.section ".multiboot"
	/* Multiboot header must be aligned on a 4-byte boundary */
	.align 4
multiboot_header:
	/* Magic Number */ 
	.long MULTIBOOT_HEADER_MAGIC 
	.long MULTIBOOT_HEADER_FLAGS
	/* Checksum */
	.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS) 
	.long multiboot_header
	.long __b_kernel
	.long __e_load
	.long __e_kernel
	.long multiboot_entry

.text
.globl __start
__start:
multiboot_entry:
	/* Set up a stack */
	movl $(stack + MULTIBOOT_STACK_SIZE), %ebp
	movl %ebp, %esp

	/* Set EFLAGS to 0 */
	pushl $0
	/* pop stack into the EFLAGS register */
	popf

	/*
	 * Push the magic and the address on the stack, so that they
	 * will be the parameters of the main function 
	 */
	pushl %ebx
	pushl %eax
	
	/* Call the main function (main.c) */
	.extern main
	call main

	/* Should never get there */
loop:
	hlt
	jmp loop
	
	 
/* Here is the stack */
.section ".bootstrap_stack", "aw", @nobits
.size stack, MULTIBOOT_STACK_SIZE
stack:
	.space MULTIBOOT_STACK_SIZE


/* Some data characterizing the stack addresses */
.data
	.globl bootstrap_stack_bottom
bootstrap_stack_bottom: .long stack

	.globl bootstrap_stack_size
bootstrap_stack_size: .long MULTIBOOT_STACK_SIZE
