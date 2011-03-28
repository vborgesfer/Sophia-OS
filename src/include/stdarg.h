/**
 * @file stdarg.h
 * @brief It defines several macros used to get the arguments 
 * 		in a function when the number of arguments is not known.
 * 		It was inspired by gcc support files
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#ifndef __STDARG_H_
#define __STDARG_H_

/** Type of object holding context information */
typedef void * va_list;

/** Helper macro for rounded size variables */
#define __va_rounded_size(TYPE) \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

/** 
 * Initialisation macro which must be called once before any 
 * unnamed argument is accessed
 * @note The GCC macro __builtin_next_arg (lastarg) returns 
 * 		the address of the first anonymous stack argument, 
 * 		as type void *
 **/
#define va_start(AP, LASTARG) \
  (AP = ((void *) __builtin_next_arg (LASTARG)))

/**
 * Termination macro which must be called once after argument 
 * processing and before exit from function.
 **/
#define va_end(AP) \
  ((void)0)

/** 
 * Yields value of the type (type) and value of the next 
 * unnamed argument.
 **/
#define va_arg(AP, TYPE) \
  (AP = (void *) ((char *) (AP) + __va_rounded_size (TYPE)),  \
   *((TYPE *) (void *) ((char *) (AP) - __va_rounded_size (TYPE))))

#endif /* _STDARG_H_ */
