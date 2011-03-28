/**
 * @file stddef.h
 * @brief It defines several standard definitions
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#ifndef _STDDEF_H_
#define _STDDEF_H_

/** the result of subtracting two pointers */
typedef signed long 	ptrdiff_t;

/** The unsigned integer result of the sizeof keyword */
typedef unsigned long	size_t;

/** An integer type of the size of a wide character constant */
typedef int				wchar_t;

/** Null pointer constant */
#define NULL			(void*)0

/** 
 * This results in a constant integer of type size_t which 
 * is the offset in bytes of a structure member from the 
 * beginning of the structure
 * @param type		The name of the structure
 * @param member	The member-designator
 **/
#define offsetof(type, member) \
	((size_t) &((type*)0)->member)


#endif /*_STDDEF_H_ */
