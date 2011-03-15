/**
 * @file multiboot.h
 * @brief Multiboot standard, as defined by the Grub documentation
 * @author Victor Borges
 * @date Feb 28, 2011
 */

#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

/** The Multiboot header.  */
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002

/** The flags for the Multiboot header.  */
#define MULTIBOOT_HEADER_FLAGS		0x00010003

/** The magic number passed by a Multiboot-compliant boot loader.  */
#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

/** The size of stack (16KB).  */
#define MULTIBOOT_STACK_SIZE	        0x4000

#ifndef BOOT_S
/* Do not include this in boot.S.  */

/**
 * The Multiboot header defined by the multiboot standard
 **/
struct multiboot_header
{
  unsigned long magic;
  unsigned long flags;
  unsigned long checksum;
  unsigned long header_addr;
  unsigned long load_addr;
  unsigned long load_end_addr;
  unsigned long bss_end_addr;
  unsigned long entry_addr;
};

/**
 * Used for a binary kernel using symbol table for a.out.  
 **/
struct multiboot_aout_symbol_table
{
  unsigned long tabsize;
  unsigned long strsize;
  unsigned long addr;
  unsigned long reserved;
};

/**
 * Used for a binary kernel using symbol table for ELF
 **/
struct multiboot_elf_section_header_table
{
  unsigned long num;
  unsigned long size;
  unsigned long addr;
  unsigned long shndx;
};

/** 
 * Information gave by the multiboot loader to the OS  
 **/
struct multiboot_info
{
  unsigned long flags;
  unsigned long mem_lower;
  unsigned long mem_upper;
  unsigned long boot_device;
  unsigned long cmdline;
  unsigned long mods_count;
  unsigned long mods_addr;
  union
  {
    struct multiboot_aout_symbol_table aout_sym;
    struct multiboot_elf_section_header_table elf_sec;
  } u;
  unsigned long mmap_length;
  unsigned long mmap_addr;
  unsigned long drives_length;
  unsigned long drives_addr;
  unsigned long config_table;
  unsigned long boot_loader_name;
  unsigned long apm_table;
} multiboot_info_t;

/** 
 * Modules supported by the host detected by the multiboot loader 
 **/
struct multiboot_module
{
  unsigned long mod_start;
  unsigned long mod_end;
  unsigned long string;
  unsigned long reserved;
};

/** 
 * Memory map of the host detected by the multiboot loader 
 **/
struct multiboot_memory_map
{
  unsigned long size;
  unsigned long base_addr_low;
  unsigned long base_addr_high;
  unsigned long length_low;
  unsigned long length_high;
  unsigned long type;
};

/** 
 * APM informations detected by the multiboot loader 
 **/
struct multiboot_apm_table
{
	unsigned short version;
	unsigned short cseg;
	unsigned long offset;
	unsigned short cseg_16;
};

#endif /* ! BOOT_S */

#endif /* _MULTIBOOT_H_ */
