/**
 * @file stdlib.h
 * @brief It defines several general operation functions and macros.
 * @note This header is imcomplete for C99 stardard
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#include <types.h>

/******************** STRING FUNCTIONS *********************/

/**
 * The string pointed to by the argument str is converted to a 
 * floating-point number (type double). Any initial whitespace 
 * characters are skipped (space, tab, carriage return, new line, 
 * vertical tab, or formfeed). The number may consist of an 
 * optional sign, a string of digits with an optional decimal 
 * character, and an optional e or E followed by a optionally 
 * signed exponent. Conversion stops when the first unrecognized 
 * character is reached.
 * @param str	The string to convert
 * @return On success the converted number is returned. 
 * 		If no conversion can be made, zero is returned. 
 * 		If the value is out of range of the type double, then 
 * 		ERANGE is stored in the variable errno. 
 * 		If the value is too small to be returned in the type double, 
 * 		then zero is returned and ERANGE is stored in the variable 
 * 		errno.
 **/
double atof (const char * str);

/**
 * The string pointed to by the argument str is converted to an integer 
 * (type int). Any initial whitespace characters are skipped 
 * (space, tab, carriage return, new line, vertical tab, or formfeed). 
 * The number may consist of an optional sign and a string of digits. 
 * Conversion stops when the first unrecognized character is reached.
 * @param str	The string to convert
 * @return On success the converted number is returned. 
 * 		If the number cannot be converted, then 0 is returned.
 **/
int atoi (const char * str);

/**
 * The string pointed to by the argument str is converted to a long 
 * integer (type long int). Any initial whitespace characters are 
 * skipped (space, tab, carriage return, new line, vertical tab, or 
 * formfeed). The number may consist of an optional sign and a string 
 * of digits. Conversion stops when the first unrecognized character 
 * is reached.
 * @param str	The string to convert
 * @return On success the converted number is returned. 
 * 		If the number cannot be converted, then 0 is returned.
 **/
long int atol (const char * str);

/**
 * The string pointed to by the argument str is converted to a 64 bits 
 * integer (type long long int). Any initial whitespace characters are 
 * skipped (space, tab, carriage return, new line, vertical tab, or 
 * formfeed). The number may consist of an optional sign and a string 
 * of digits. Conversion stops when the first unrecognized character 
 * is reached.
 * @param str	The string to convert
 * @return On success the converted number is returned. 
 * 		If the number cannot be converted, then 0 is returned.
 **/
s64 atoll (const char * str);

/**
 * The string pointed to by the argument str is converted to a 
 * floating-point number (type float). Any initial whitespace 
 * characters are skipped (space, tab, carriage return, new line, 
 * vertical tab, or formfeed). The number may consist of an optional 
 * sign, a string of digits with an optional decimal character, and 
 * an optional e or E followed by a optionally signed exponent. 
 * Conversion stops when the first unrecognized character is reached\n
 * The argument endptr is a pointer to a pointer. The address of 
 * the character that stopped the scan is stored in the pointer 
 * that endptr points to.
 * @param str		The string to convert
 * @param endptr	Point to the end of the string
 * @return On success the converted number is returned. 
 * 		If no conversion can be made, zero is returned. 
 * 		If the value is out of range of the type double, then 
 * 		ERANGE is stored in the variable errno. 
 * 		If the value is too small to be returned in the type double, 
 * 		then zero is returned and ERANGE is stored in the variable 
 * 		errno.
 **/
float strtof (const char * str, char ** endptr);

/**
 * The string pointed to by the argument str is converted to a 
 * floating-point number (type double). Any initial whitespace 
 * characters are skipped (space, tab, carriage return, new line, 
 * vertical tab, or formfeed). The number may consist of an optional 
 * sign, a string of digits with an optional decimal character, and 
 * an optional e or E followed by a optionally signed exponent. 
 * Conversion stops when the first unrecognized character is reached\n
 * The argument endptr is a pointer to a pointer. The address of 
 * the character that stopped the scan is stored in the pointer 
 * that endptr points to.
 * @param str		The string to convert
 * @param endptr	Point to the end of the string
 * @return On success the converted number is returned. 
 * 		If no conversion can be made, zero is returned. 
 * 		If the value is out of range of the type double, then 
 * 		ERANGE is stored in the variable errno. 
 * 		If the value is too small to be returned in the type double, 
 * 		then zero is returned and ERANGE is stored in the variable 
 * 		errno.
 **/
double strtod (const char * str, char ** endptr);

/**
 * The string pointed to by the argument str is converted to a long 
 * integer (type long int). Any initial whitespace characters are 
 * skipped (space, tab, carriage return, new line, vertical tab, or 
 * formfeed). The number may consist of an optional sign and a string 
 * of digits. Conversion stops when the first unrecognized character 
 * is reached.
 * If the base (radix) argument is zero, then the conversion is 
 * dependent on the first two characters. If the first character is 
 * a digit from 1 to 9, then it is base 10. If the first digit is a 
 * zero and the second digit is a digit from 1 to 7, then it is base 
 * 8 (octal). If the first digit is a zero and the second character 
 * is an x or X, then it is base 16 (hexadecimal).
 * If the base argument is from 2 to 36, then that base (radix) is 
 * used and any characters that fall outside of that base definition 
 * are considered unconvertible. For base 11 to 36, the characters A 
 * to Z (or a to z) are used. If the base is 16, then the characters 
 * 0x or 0X may precede the number.
 * @param str		The string to convert
 * @param endptr	Point to the end of the string
 * @return On success the converted number is returned. 
 * 		If no conversion can be made, zero is returned. 
 * 		If the value is out of the range of the type long int, 
 * 		then LONG_MAX or LONG_MIN is returned with the sign of 
 * 		the correct value and ERANGE is stored in the variable errno.
 **/
long int strtol (const char * str, char ** endptr, int base);

/**
 * The string pointed to by the argument str is converted to a unsigned 
 * long integer (type unsigned long int). Any initial whitespace 
 * characters are skipped (space, tab, carriage return, new line, 
 * vertical tab, or formfeed). The number may consist of an optional 
 * sign and a string of digits. Conversion stops when the first 
 * unrecognized character is reached.
 * If the base (radix) argument is zero, then the conversion is 
 * dependent on the first two characters. If the first character is 
 * a digit from 1 to 9, then it is base 10. If the first digit is a 
 * zero and the second digit is a digit from 1 to 7, then it is base 
 * 8 (octal). If the first digit is a zero and the second character 
 * is an x or X, then it is base 16 (hexadecimal).
 * If the base argument is from 2 to 36, then that base (radix) is 
 * used and any characters that fall outside of that base definition 
 * are considered unconvertible. For base 11 to 36, the characters A 
 * to Z (or a to z) are used. If the base is 16, then the characters 
 * 0x or 0X may precede the number.
 * @param str		The string to convert
 * @param endptr	Point to the end of the string
 * @return On success the converted number is returned. 
 * 		If no conversion can be made, zero is returned. 
 * 		If the value is out of the range of the type long int, 
 * 		then LONG_MAX or LONG_MIN is returned with the sign of 
 * 		the correct value and ERANGE is stored in the variable errno.
 **/
unsigned long int strtoul (const char * str, char ** endptr, int base);

/********************** MATH FUNCTIONS ********************/

/**
 * The max random number
 **/
#define RAND_MAX 	0x7ffffffe

/**
 * Division structure for integer
 **/
typedef struct 
{ 
	int quot; /**< The quotient */
	int rem;  /**< The remainder */
} div_t;

/**
 * Division structure for long integers
 **/
typedef struct 
{ 
	long quot; /**< The quotient */
	long rem;  /**< The remainder */
} ldiv_t;

/**
 * Returns the absolute value of x. 
 * @param x 	A signed number
 * @return The absolute value is returned
 **/
int abs (int x);

/**
 * Returns the absolute value of a long integer. 
 * @param x 	A signed number
 * @return The absolute value is returned
 **/
long int labs (long int x);

/**
 * Returns the absolute value of a 64 bits number. 
 * @param x 	A signed number
 * @return The absolute value is returned
 **/
s64 llabs (s64 x);

/**
 * Divides numer (numerator) by denom (denominator).
 * @param numer		The numerator
 * @param denom		The denomerator
 * @return  The value of the division is returned in the structure
 **/
div_t div (int numer, int denom);

/**
 * Divides numer (numerator) by denom (denominator) for a long integer.
 * @param numer		The numerator
 * @param denom		The denomerator
 * @return  The value of the division is returned in the structure
 **/
ldiv_t ldiv (long int numer, long int denom);

/**
 * Returns a pseudo-random number in the range of 0 to RAND_MAX
 * @return The random number is returned.
 **/
int rand (void);

/**
 * This function seeds the random number generator used 
 * by the function rand. 
 * @param seed 		Seed the random algorithm
 **/
void srand (unsigned int seed);
