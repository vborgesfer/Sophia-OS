/**
 * @file main.c
 * @brief Entry point for Sophia OS
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include <boot/multiboot.h>

#include <types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <timer.h>
#include <sys.h>

#include <mem/memory.h>
#include <io/bochs.h>
#include <io/video.h>
#include <io/irq.h>
#include <io/keyboard.h>

#include "../test/test.h"

void multiboot_loader_info(struct multiboot_info *mbi)
{
	struct multiboot_memory_map *mmap;	
	printf("\n\nComputer informations from %s: \n"
		" - RAM is %dMB, uper_mem = %x, lower_mem = %x",
		(char *) mbi->boot_loader_name,
		(int)((mbi->mem_upper >> 10) + 1), 
		(int)mbi->mem_upper, (int)mbi->mem_lower);
				
	printf ("\n - Flags: %d\n - Boot Device: %d",
			(int)(mbi->flags), (int)(mbi->boot_device));

	printf("\n - Cmd Line: %s", (char *)(mbi->cmdline));

	printf ("\n - nmmap_addr = %x, mmap_length = %x", 
		(unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
		
	for ( mmap = (struct multiboot_memory_map *) mbi->mmap_addr;
		  (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
		  mmap = (struct multiboot_memory_map *) ((unsigned long) mmap
				+ mmap->size + sizeof (mmap->size))
		)
	{
		printf ("\n  > size = %x, base_addr = %x,"
						" length = %x, type = %x",
						 (unsigned) mmap->size,
						 (unsigned int) mmap->base_addr_low,
						 (unsigned int) mmap->length_low,
						 (unsigned int) mmap->type);
	}

	printf("\n - Config table: %x", 
				(unsigned)(mbi->config_table));
	printf("\n - APM table: %x", 
				(unsigned)(mbi->apm_table));

	printf ("\n - Mods Count: %d  Mods Addr: %d",
			(int)(mbi->mods_count), (int)(mbi->mods_addr));
	printf ("\n - Mmap Length: %d  Mmap Addr: %d",
			(int)(mbi->mmap_length), (int)(mbi->mmap_addr));
	printf ("\n - Drives length: %d  Drives Addr: %d",
			(int)(mbi->drives_length), (int)(mbi->drives_addr));

}

static void kshell()
{
	video_print("\n\nsophia$ ");
	forever
	{
		if (kb_cache.stream[kb_cache.size-1] == '\n')
		{
			if (strncmp((const char*)kb_cache.stream, "halt", kb_cache.size-1) == 0)
				printf("Halting the system...\n");
			else if (strncmp((const char*)kb_cache.stream, "help", kb_cache.size-1) == 0)
			{	
				printf("Commands currently available :\n");
				printf("\thelp     -  display this help\n");
				printf("\thalt     -  halt the system\n");
				printf("\treboot   -  reboot the system (Ctrl-Alt-Del)\n");
			}
			else if (strncmp((const char*)kb_cache.stream, "reboot", kb_cache.size-1) == 0)
			{
				printf("Rebooting the system...\n");
				reboot();
			}
			else if (kb_cache.size != 1 /* there is always a \n */)
			{
				kb_cache.stream[kb_cache.size-1] = '\0';
				printf("%s: command not found\n", kb_cache.stream);
				printf("Write 'help' for more informations...\n");
			}
			video_print("sophia$ ");
			kb_cache.size = 0;
			kb_cache.stream[0] = '\0';
		}
		asm ("hlt\n");
	}
}




/**
 * Start point of Sophia OS
 * @param magic		Magic number gave by the multiboot loader
 * @param mbi		Informations received by the multiboot loader
 **/
void main(unsigned long magic, struct multiboot_info *mbi) 
{
	paddr kernel_base, kernel_top;
	
	video_setup();
	video_clear(VIDEO_BG_BLUE);
	video_set_color(VIDEO_BG_BLUE | VIDEO_FG_WHITE);
	
	video_print("> Welcome to Sophia OS by Victor Borges, 2011\n");
	
	video_set_title(VIDEO_BG_BLUE | VIDEO_FG_WHITE);
	
	bochs_print("\nWriting on bochs for debug purpose!\n");
	
	if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
		multiboot_loader_info(mbi);
	
	video_print("\n * Setting memory segmentation ");
	video_done(memory_setup_segments() == OK);
	
	video_print(" * Setting inturruptions ");
	video_done(irq_setup() == OK);
	
	video_print(" * Setting timer ");
	video_done(timer_setup() == OK);
	
	video_print(" * Setting keyboard interruption handler ");
	video_done(kb_setup() == OK);

	video_print(" * Setting memory page frames ");
	video_done(memory_setup_ppages((int)((mbi->mem_upper << 10) 
		+ (1 << 20)), &kernel_base, &kernel_top) == OK);	
	
	printf("Kernel boundaries : [%x; %x]\n", kernel_base, kernel_top);
	
	/* Enabling HW interrupts */
	asm volatile ("sti\n");
	
	test_ppage();
	
	kshell();
	
	forever asm ("hlt\n");
}
