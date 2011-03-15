/**
 * @file bochs.h
 * @brief Bochs communication routines
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#ifndef _BOCHS_H_
#define _BOCHS_H_

#include <types.h>

/**
 * Print a character in bach for debug purpose
 * @param c		Character
 **/
void bochs_putc(const char c);

/**
 * Print a string in bach for debug purpose
 * @param str	String
 **/
void bochs_print(char * str);

#endif /* _BOCHS_H_ */
