/**
 * @file string.h
 * @brief It provides many functions useful for manipulating strings
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#ifndef _STRING_H_
#define _STRING_H_

#include <types.h>

/**
 * Searches for the first occurrence of the character c 
 * (an unsigned char) in the first n bytes of the string 
 * pointed to by the argument str.
 * @param str	Main string
 * @param c		Character to search
 * @param n		Number of bytes
 * @return A pointer pointing to the first matching character, 
 * 		or null if no match was found
 **/
void* memchr(const void* str, int c, size_t n) 
		__attribute__((__nonnull__(1), __pure__));

/**
 * Compares the first n bytes of str1 and str2. 
 * Does not stop comparing even after the null character 
 * (it always checks n characters).
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return Returns zero if the first n bytes of str1 and str2 are equal. 
 * 		Returns less than zero or greater than zero 
 * 		if cs is less than or greater than ct respectively.
 **/
int memcmp(const void* str1, const void* str2, size_t n) 
	__attribute__((__nonnull__(1,2)));
	
/**
 * Copies n characters from str2 to str1. 
 * If str1 and str2 overlap, the behavior is undefined.
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return the argument str1
 **/		
void* memcpy(void* srt1, const void* srt2, size_t n) 
	__attribute__((__nonnull__(1,2)));

/**
 * Copies n characters from str2 to str1. 
 * If str1 and str2 overlap the information is 
 * first completely read from str1 and then written to str2 
 * so that the characters are copied correctly
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return the argument str1
 **/
void* memmove(void* str1, const void* str2, size_t n) 
	__attribute__((__nonnull__(1,2), __pure__));

/**
 * Copies the character c (an unsigned char) to the first 
 * n characters of the string pointed to by the argument str.
 * @param str	Main string
 * @param c		Character to copy
 * @param n		Number of bytes
 * @return the argument str
 **/
void* memset(void* str, int c, size_t n) 
	__attribute__((__nonnull__(1), __pure__));

/**
 * Appends the string pointed to by str2 to the end of the s
 * tring pointed to by str1. The terminating null character of 
 * str1 is overwritten. 
 * Copying stops once the terminating null character of str2 
 * is copied. If overlapping occurs, the result is undefined.
 * @param str1	First string
 * @param str2	Second string
 * @return the argument str1
 **/	
char* strcat(char* str1, const char* str2) 
	__attribute__((__nonnull__));

/**
 * Appends the string pointed to by str2 to the end of the 
 * string pointed to by str1 up to n characters long. 
 * The terminating null character of str1 is overwritten. 
 * Copying stops once n characters are copied or the terminating 
 * null character of str2 is copied. A terminating null character 
 * is always appended to str1. If overlapping occurs, the result 
 * is undefined
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return the argument str1
 **/
char* strncat(char* str1, const char* str2, size_t n) 
	__attribute__((__nonnull__(1,2)));
	
/**
 * Searches for the first occurrence of the character c 
 * (an unsigned char) in the string pointed to by the argument str. 
 * The terminating null character is considered to be part of 
 * the string.
 * @param str	Main string
 * @param c		Character to search
 * @return A pointer pointing to the first matching character, 
 * 		or null if no match was found
 **/	
char* strchr(const char* str, int c) 
	__attribute__((__nonnull__(1), __pure__));
	
/**
 * Compares the string pointed to by str1 to the string 
 * pointed to by str2.
 * @param str1	First string
 * @param str2	Second string
 * @return Zero if str1 and str2 are equal. 
 * 		Returns less than zero or greater than zero 
 * 		if str1 is less than or greater than str2 respectivel
 **/	
int strcmp(const char* str1, const char* str2) 
	__attribute__((__nonnull__, __pure__));
	
/**
 * Compares at most the first n bytes of str1 and str2. 
 * Stops comparing after the null character.
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return Zero if the first n bytes (or null terminated length) 
 * 		of str1 and str2 are equal. Returns less than zero 
 * 		or greater than zero if str1 is less than or greater 
 * 		than str2 respectively
 **/
int strncmp(const char* tr1s, const char* str2, size_t n) 
	__attribute__((__nonnull__(1,2)));
	
/**
 * Compares string str1 to str2.
 * @param str1	First string
 * @param str2	Second string
 * @return Zero if str1 and str2 are equal. 
 * 		Returns less than zero or greater than zero if str1 is 
 * 		less than or greater than str2 respectively.
 * @note Equal to strcmp, it was put here just for compatibility
 * 		with C99 standard
 **/
int strcoll(const char* str1, const char* str2) 
	__attribute__((__nonnull__));
	
/**
 * Copies the string pointed to by str2 to str1. 
 * Copies up to and including the null character of str2. 
 * If str1 and str2 overlap the behavior is undefined.
 * @param str1	First string
 * @param str2	Second string
 * @return The argument str1.
 **/		
char* strcpy(char* str1, const char* str2) 
	__attribute__((__nonnull__));

/**
 * Copies up to n characters from the string pointed to by str2 to str1. 
 * Copying stops when n characters are copied or the terminating null 
 * character in str2 is reached. If the null character is reached, 
 * the null characters are continually copied to str1 until n 
 * characters have been copied.
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return The argument str1.
 **/	
char* strncpy(char* str1, const char* str2, size_t n) 
	__attribute__((__nonnull__(1,2)));

/**
 * Finds the first sequence of characters in the string str1 that 
 * does not contain any character specified in str2.
 * @param str1	First string
 * @param str2	Second string
 * @return The length of this first sequence of characters found 
 * 		that do not match with
 **/	
size_t strcspn(const char* str1, const char* str2) 
	__attribute__((__nonnull__));

/**
 * Searches an internal array for the error number errnum and 
 * returns a pointer to an error message string.
 * @param n		Error code
 * @return An error message string.
 **/	
char* strerror(result n);

/**
 * Computes the length of the string str up to but not including 
 * the terminating null character
 * @param str	String
 * @return The number of characters in the string.
 **/
size_t strlen(const char* str) 
	__attribute__((__nonnull__, __pure__));

/**
 * Finds the first character in the string str1 that matches any 
 * character specified in str
 * @param str1	First string
 * @param str2	Second string
 * @return A pointer to the location of this character is returned. 
 * 		A null pointer is returned if no character in str2 exists 
 * 		in str1.
 **/
char* strpbrk(const char* str1, const char* str2) 
	__attribute__((__nonnull__));

/**
 * Searches for the last occurrence of the character c 
 * (an unsigned char) in the string pointed to by the argument str. 
 * The terminating null character is considered to be part of 
 * the string.
 * @param str	Main string
 * @param c		Character to search
 * @return A pointer pointing to the last matching character, or null if no match was found.
 **/
char* strrchr(const char* str, int c) 
	__attribute__((__nonnull__(1), __pure__));

/**
 * Finds the first sequence of characters in the string str1 that 
 * contains any character specified in str2.
 * @param str1	First string
 * @param str2	Second string
 * @return  The length of this first sequence of characters found 
 * 		that match with str2.
 **/
size_t strspn(const char* str1, const char* str2) 
	__attribute__((__nonnull__));

/**
 * Finds the first occurrence of the entire string str2 
 * (not including the terminating null character) which appears in 
 * the string str1.
 * @param str1	First string
 * @param str2	Second string
 * @return A pointer to the first occurrence of str2 in str1. 
 * 		If no match was found, then a null pointer is returned. 
 * 		If str2 points to a string of zero length, then the 
 * 		argument str1 is returned
 **/
char* strstr(const char* str1, const char* str2) 
	__attribute__((__nonnull__, __pure__));

/**
 * Breaks string str1 into a series of tokens. 
 * If str1 and str2 are not null, then the following search sequence 
 * begins. The first character in str1 that does not occur in str2 
 * is found. If str1 consists entirely of characters specified in 
 * str2, then no tokens exist and a null pointer is returned. If this 
 * character is found, then this marks the beginning of the first 
 * token. It then begins searching for the next character after that 
 * which is contained in str2. If this character is not found, then 
 * the current token extends to the end of str1. If the character is 
 * found, then it is overwritten by a null character, which terminates 
 * the current token. The function then saves the following position 
 * internally and returns. \n
 * Subsequent calls with a null pointer for str1 will cause the 
 * previous position saved to be restored and begins searching from 
 * that point. Subsequent calls may use a different value for str2 
 * each time.
 * @param str1	First string
 * @param str2	Second string
 * @return A pointer to the first token in str1. 
 * 		If no token is found then a null pointer is returned.
 **/
char* strtok(char* s, const char* t) 
	__attribute__((__nonnull__));

/**
 * Transforms the string str2 and places the result into str1. 
 * It copies at most n characters into str1 including the null 
 * terminating character. The transformation occurs such that 
 * strcmp applied to two separate converted strings returns the 
 * same value as strcoll applied to the same two strings. 
 * If overlapping occurs, the result is undefined.
 * @param str1	First string
 * @param str2	Second string
 * @param n		Number of bytes
 * @return The length of the transformed string 
 * 		(not including the null character).
 **/	
size_t strxfrm(char* s, const char* ct, size_t n) 
	__attribute__((__nonnull__(1,2)));

#endif /* _STRING_H_ */
