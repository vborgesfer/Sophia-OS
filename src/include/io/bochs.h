/**
 * @file bochs.h
 * @brief Bochs communication routines
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#ifndef _BOCHS_H_
#define _BOCHS_H_

#ifdef NDEBUG
#define bochs_putc(c) 				(void*)0
#define bochs_print(str) 			(void*)0
#define bochs_printf(str,...) 		(void*)0
#else

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

/**
 * Print formatted string in bach for debug purpose
 * @param str	String
 **/
void bochs_printf(char * format, ...);

#endif /* NDEBUG */
#endif /* _BOCHS_H_ */
