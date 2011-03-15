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

KERNEL = sophia.elf
FLOPPY_IMAGE = ../fd.img

GRUB_IMAGE = grub_disk.img
GRUB_CONF = menu.cfg

GRUB_SIZE = 750
	
# Creating floppy
floppy: $(GRUB_IMAGE) ../$(KERNEL) $(GRUB_CONF)
	sudo cp $(GRUB_IMAGE) $(FLOPPY_IMAGE)
	sudo mkdir tmp
	sudo mount -v -t vfat -o loop $(FLOPPY_IMAGE) tmp
	sudo cp $(GRUB_CONF) tmp/boot/
	sudo cp ../$(KERNEL) tmp/system/
	sudo umount -v tmp
	sudo rm -rf tmp
		
	
# Creating GRUB configuration file
$(GRUB_CONF):
	echo timeout	0 > $@
	echo default	0 >> $@
	echo title		Sophia $(VERSION).$(PATCHLEVEL).$(SUBLEVEL) >> $@
	echo "root		(fd0)" >> $@
	echo kernel		/system/$(KERNEL) >> $@
	
clean:
	$(RM) menu.cfg
