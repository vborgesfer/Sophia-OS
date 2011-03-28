/**
 * @file sys.c
 * @brief Some system functions
 * @author Victor Borges
 * @date Mar 22, 2011
 */
 
#include <sys.h>
#include <types.h>
#include "ioports.h"

void reboot()
{
	outb(0xFE, 0x64);
    /* if that didn't work, halt the CPU */	   
    forever asm volatile ("hlt"); 
}
 
void kbd_update_leds(byte status)
{
	while((inb(0x64)&2)!=0); //loop until zero
	outb(0x60,0xED);

	while((inb(0x64)&2)!=0); //loop until zero
	outb(0x60,status);
}
