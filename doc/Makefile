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

DOXYGE_CONF = doc.conf

# Create documentation
docs: $(DOXYGE_CONF)
	doxygen $(DOXYGE_CONF)
	
# Create latex documentation
latex: docs
	make -C latex

# Clean 
clean:
	$(RM) -r html latex

