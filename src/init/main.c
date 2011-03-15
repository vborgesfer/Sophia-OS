/**
 * @file main.c
 * @brief Entry point for Sophia OS
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include <boot/multiboot.h>

#include <types.h>

#include <mem/memory.h>
#include <bochs.h>
#include <io/video.h>


/**
 * Start point of Sophia OS
 * @param magic		Magic number gave by the multiboot loader
 * @param mbi		Informations received by the multiboot loader
 **/
void main(unsigned long magic, struct multiboot_info *mbi) 
{
	struct multiboot_memory_map *mmap;
	
	video_setup();
	video_clear(VIDEO_BG_BLUE);
	video_set_color(VIDEO_BG_BLUE | VIDEO_FG_WHITE);
	
	video_print("> Welcome to Sophia OS by Victor Borges, 2011\n");
	
	bochs_print("\nWriting on bochs for debug purpose!\n");
	
	video_print("\n * Setting memory segmentation ");
	memory_setup_segments();
	video_print("....... [DONE]");
	
	if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
	{
		
		video_printf("\n\nComputer informations from %s: \n"
			" - RAM is %dMB, uper_mem = %x, lower_mem = %x",
			(char *) mbi->boot_loader_name,
			(mbi->mem_upper >> 10) + 1, 
			 mbi->mem_upper, mbi->mem_lower);
	
		video_printf ("\n - Flags: %d\n - Boot Device: %d",
				(int)(mbi->flags), (int)(mbi->boot_device));
	
		video_printf("\n - Cmd Line: %s", (char *)(mbi->cmdline));

		video_printf ("\n - nmmap_addr = %x, mmap_length = %x", 
			(unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
			
		for ( mmap = (struct multiboot_memory_map *) mbi->mmap_addr;
			  (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
			  mmap = (struct multiboot_memory_map *) ((unsigned long) mmap
					+ mmap->size + sizeof (mmap->size))
			)
		{
			video_printf ("\n  > size = %x, base_addr = %x,"
							" length = %x, type = %x",
							 (unsigned) mmap->size,
							 mmap->base_addr_low,
							 mmap->length_low,
							 (unsigned) mmap->type);
		}
	
		video_printf("\n - Config table: %x", 
					(unsigned)(mbi->config_table));
		video_printf("\n - APM table: %x", 
					(unsigned)(mbi->apm_table));
	
		video_printf ("\nMods Count: %d  Mods Addr: %d",
				(int)(mbi->mods_count), (int)(mbi->mods_addr));
		video_printf ("\nMmap Length: %d  Mmap Addr: %d",
				(int)(mbi->mmap_length), (int)(mbi->mmap_addr));
		video_printf ("\nDrives length: %d  Drives Addr: %d",
				(int)(mbi->drives_length), (int)(mbi->drives_addr));
	
		video_print("\n\nsophia$");
		
	}
	
	forever asm ("hlt\n");
}
