/**
 * @file ctype.h
 * @brief It is used for testing and converting characters. 
 * 		A control character refers to a character that is not part 
 * 		of the normal printing set. In the ASCII character set, 
 * 		the control characters are the characters from 0 (NUL) 
 * 		through 0x1F (US), and the character 0x7F (DEL). 
 * 		Printable characters are those from 0x20 (space) 
 * 		to 0x7E (tilde)
 * @note In the standard, these functions return an integer,
 * 		here, they return a boolean defined in types.h
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#ifndef _CTYPE_H_
#define _CTYPE_H_
 
#include <types.h>

/**
 * Return true if it is a letter (A to Z or a to z) 
 * or a digit (0 to 9)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isalnum (int c) __attribute__ ((__const__));

/**
 * Return true if it is a letter (A to Z or a to z)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isalpha (int c) __attribute__ ((__const__));

/**
 * Return true if it is a ASCII character
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isascii (int c) __attribute__ ((__const__));

/**
 * Return true if it is blank = ' ' or a tab character
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isblank (int c) __attribute__ ((__const__));

/**
 * Return true if it is any control character (0x00 to 0x1F or 0x7F)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean iscntrl(int c) __attribute__ ((__const__));

/**
 * Return true if it is a digit (0 to 9)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isdigit (int c) __attribute__ ((__const__));

/**
 * Return true if it is any printing character except for the 
 * space character (0x21 to 0x7E)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isgraph (int c) __attribute__ ((__const__));

/**
 * Return true if it is a lowercase letter (a to z)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean islower (int c) __attribute__ ((__const__));

/**
 * Return true if it is any printing character (0x20 to 0x7E)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isprint(int c) __attribute__ ((__const__));

/**
 * Return true if it is any punctuation character 
 * (any printing character except for space character or isalnum)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean ispunct(int c) __attribute__ ((__const__));

/**
 * Return true if it is a whitespace character 
 * (space, tab, carriage return, new line, 
 * vertical tab, or formfeed)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isspace (int c) __attribute__ ((__const__));

/**
 * Return true if it is an uppercase letter (A to Z
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isupper (int c) __attribute__ ((__const__));

/**
 * Return true if it is a hexadecimal 
 * digit (0 to 9, A to F, or a to f)
 * @param c		Character to evaluate
 * @return a boolean
 **/
inline boolean isxdigit (int c) __attribute__ ((__const__));

/**
 * If the character is an uppercase character (A to Z), 
 * then it is converted to lowercase (a to z)
 * @param c		Character to evaluate
 * @return a char
 **/
inline int tolower(int c) __attribute__ ((__const__));

/**
 * If the character is a lowercase character (a to z), 
 * then it is converted to uppercase (A to Z)
 * @param c		Character to evaluate
 * @return a char
 **/
inline int toupper(int c) __attribute__ ((__const__));

#endif /* _CTYPES_H_ */
