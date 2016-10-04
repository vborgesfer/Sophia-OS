#
# Makefile
#
# This file is subject to the terms and conditions of 
# the GNU General Public License.  
# See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2011 by Victor Borges
#

export VERSION = 0
export PATCHLEVEL = 0
export SUBLEVEL = 1

# Define architecure
export ARCH = x86
#
# You must add the cross compiler to your path!
export TARGET=i686-elf

KERNEL = sophia.elf
ISO = sophia.iso

# Compiling Kernel
all: $(KERNEL)

# Display help
help:
	@echo
	@echo "Makefile for Sophia operating system, \
version" $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)
	@echo "Copyright (C) 2011 by Victor Borges"
	@echo "Please see COPYING for licensing information."
	@echo
	@echo "Usage: make [ all | clean | help ] " 
	@echo "         all     - Make kernel ELF file"
	@echo "         iso     - Make an iso image with GRUB"
	@echo "         help    - Display this help" 
	@echo "         -------------------------------------------"
	@echo "         clean   - Clean objects and temporary files" 
	@echo "         rmdocs  - Remove documentation files" 
	@echo "         dist    - Clean all files" 
	@echo "         -------------------------------------------"
	@echo "         qemu    - Run Sophia in qemu" 
	@echo "         -------------------------------------------"
	@echo "         docs    - Make documentation using doxygen"
	@echo "         latex   - Make latex documentation"
	@echo

# Creating floppy with GRUB
iso:  $(KERNEL)
	mkdir -p isodir/boot/grub
	cp grub/grub.cfg isodir/boot/grub/
	cp sophia.elf isodir/boot
	grub-mkrescue -o sophia.iso isodir

$(ISO): iso
	
# Compiling Kernel
$(KERNEL):
	make -C src
#
# Lauching with qemu	
qemu: $(ISO)
	qemu-system-i386 -cdrom $(ISO)
	
# Create documentation
docs:
	make -C doc

# Create latex documentation
latex: docs
	make -C doc latex

# Clean objects and temporary files
clean:
	make -C src clean
	$(RM) $(KERNEL)
	$(RM) -r isodir
	$(RM) sophia.iso
	
# Remove documentation files
dist: clean
	make -C doc clean
	
# Remove documentation files
rmdocs:
	make -C doc clean

