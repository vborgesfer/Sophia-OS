/**
 * @file types.h
 * @brief Basic types definition
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>

/** 
 * Looping forever 
 **/
#define forever for(;;)

/* Boolean values */
#define FALSE 	0 /**< False boolean value */
#define TRUE	1 /**< True boolean value */

/**
 * Virtual address memory
 **/
typedef unsigned int		vaddr;

/**
 * Physical address memory
 **/
typedef unsigned int		paddr;

/**
 * Generic count of objects
 **/
typedef unsigned int		count_t;

/* Low-level unsigned sizes */
typedef unsigned long long	u64; /**< Unsigned number of 64 bits */
typedef unsigned long int	u32; /**< Unsigned number of 32 bits */
typedef unsigned short int	u16; /**< Unsigned number of 16 bits */
typedef unsigned char		byte;/**< Unsigned number of 8 bits */

/** Pointer to an adress in memory */
typedef char*				pointer;

/* Low-level signed sizes */
typedef signed long long	s64; /**< Signed number of 64 bits */
typedef signed long int 	s32; /**< Signed number of 32 bits */
typedef signed short int 	s16; /**< Signed number of 16 bits */

/** Boolean type */
typedef int					boolean;

/** Return value code */
typedef unsigned int 		result;

#endif /* TYPES_H_ */
