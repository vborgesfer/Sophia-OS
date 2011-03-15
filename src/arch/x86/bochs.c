/**
 * @file bochs.c
 * @brief Impementation of bochs communication routines
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include "ioports.h"
#include "bochs.h"

/**
 * Address port used by bochs to communicate with the OS
 */
#define BOCHS_IOPORT 0xe9

void bochs_putc(const char c)
{
	outb((c), BOCHS_IOPORT);
}

void bochs_print(char * str)
{
	int i;
	for (i = 0; str[i]; i++)
		outb((str[i]), BOCHS_IOPORT);
}
