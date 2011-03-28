/**
 * @file assert.h
 * @brief ISO C99 Standard: 7.2 Diagnostics
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef NDEBUG

/**
 * This macro is ignored if NDEBUG is defined.
 **/
#define assert(x) ((void)(0))

#else

/**
 * Print error mensage and terminate execution.
 * @param exp	Expression asserted
 * @param file	File name
 * @param line	Line number in file
 **/
void __attribute__((__noreturn__)) 
	assert_fail(const char * exp, const char * file, unsigned int line);

/**
 * Macro used for internal error detection. 
 * If expression equals zero, message printed and assert_fail called 
 * to terminate execution.
 * @note This macro is ignored if NDEBUG is defined.
 * @param x		Expression to verify
 **/
#define assert(x) \
	((x) ? (void) 0 : assert_fail(#x, __FILE__, __LINE__))


#endif /* NDEBUG */
#endif /* _ASSERT_H_ */
