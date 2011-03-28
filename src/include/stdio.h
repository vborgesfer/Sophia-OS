/**
 * @file stdio.h
 * @brief It defines several general operation functions and macros.
 * @note This header is imcomplete for C99 stardard
 * @author Victor Borges
 * @date Mar 17, 2011
 **/
 
#include <stdarg.h>

/* TODO: This is a simple example, it will be changed */

int printf (const char * format, ...) __attribute__((__format__(__printf__,1,2)));

int sprintf (char *str, const char * format, ...) __attribute__((__format__(__printf__,2,3)));

int vprintf(const char *format, va_list ap) __attribute__((__format__(__printf__,1,0)));

int vsprintf(char * str, const char *format, va_list ap) __attribute__((__format__(__printf__,2,0)));

int putchar(int c);
