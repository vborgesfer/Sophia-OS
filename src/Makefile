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
export PREFIX="${HOME}/opt/cross/"
export TARGET=i686-elf

CC			= ${TARGET}-gcc
LD			= ${TARGET}-ld

CFLAGS		= -Wall -nostdinc -fno-stack-protector -ffreestanding 
CFLAGS		+= -Iinclude -D_KERNEL_
LDFLAGS 	= --warn-common -nostdlib -T./linker.lds

KERNEL	= ../sophia.elf
OBJECTS =

include init/objects
include arch/$(ARCH)/objects
include blibc/objects
include core/objects
OBJECTS += test/test.o

# Compiling Kernel
all: $(KERNEL)

$(KERNEL): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $^
	-nm -C $(KERNEL) | cut -d ' ' -f 1,3 > symbols.map
	size $(KERNEL)

# Create objects from C source code
%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
		
# Create objects from assembler (.S) source code
%.o: %.S
	$(CC) -c $< $(CFLAGS) -D_ASM_SOURCE_ -o $@
	
# Clean objects and temporary files
clean:
	$(RM) *.o init/*.o arch/$(ARCH)/*.o blibc/*.o core/*.o test/*.o
	$(RM) symbols.map

