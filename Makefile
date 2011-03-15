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

KERNEL = sophia.elf
FLOPPY_IMAGE = fd.img

BOCHS_CONF = bochsrc

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
	@echo "Usage: make [ all | clean | help | bochs] " 
	@echo "         all     - Make kernel binary"
	@echo "         fdimg   - Make a floppy image with GRUB Legacy"
	@echo "         help    - Display help" 
	@echo "         -------------------------------------------"
	@echo "         clean   - Clean objects and temporary files" 
	@echo "         rmdocs  - Remove documentation files" 
	@echo "         dist    - Clean all files" 
	@echo "         -------------------------------------------"
	@echo "         bochs   - Run Sophia in bochs" 
	@echo "         qemu    - Run Sophia in qemu" 
	@echo "         -------------------------------------------"
	@echo "         docs    - Make documentation using doxygen"
	@echo "         latex   - Make latex documentation"
	@echo

# Creating floppy with GRUB
fdimg:  $(KERNEL)
	make -C grub floppy
	
# Compiling Kernel
$(KERNEL):
	make -C src
	
# Lauching with bochs
bochs: $(BOCHS_CONF) $(FLOPPY_IMAGE)
	yes c | bochs -q

# Lauching with qemu	
qemu: 
	@echo "Feature not supported."
	
# Create documentation
docs:
	make -C doc

# Create latex documentation
latex: docs
	make -C doc latex

# Clean objects and temporary files
clean:
	make -C src clean	
	make -C grub clean
	$(RM) $(KERNEL)
	
# Remove documentation files
dist: clean
	$(RM) fd.img
	
# Remove documentation files
rmdocs:
	make -C doc clean

