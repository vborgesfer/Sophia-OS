/**
 * @file stdio.c
 * @brief It defines several general operation functions and macros.
 * @note This header is imcomplete for C99 stardard
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <io/video.h>

#define BUFFER_SIZE 1024

inline static void to_string(int number, char * buff, int base);
inline static void to_hex(int number, char * buff);

int printf(const char *format,...)
{
	int n;
	char buff [BUFFER_SIZE];	
	va_list ap;
	va_start(ap, format);
	n = vsprintf(buff, format, ap);
	va_end(ap);
	video_print(buff);
	return n;
}

int sprintf(char * buff, const char *format, ...)
{
	int n;
	va_list ap;
	va_start(ap, format);
	n = vsprintf(buff, format, ap);
	va_end(ap);
	return n;
}

int vprintf(const char *format, va_list ap)
{
	int n;
	char buff [BUFFER_SIZE];	
	n = vsprintf(buff, format, ap);
	video_print(buff);
	return n;	
}

int vsprintf(char * buff, const char *format, va_list ap)
{
	unsigned int len = 0;
	char *p;
	int c;
	char tmp[32];
	
	if (!buff || !format)
	{
		errno = EINVAL;
		return -errno;
	}
	
#	define CAT_BUFF(str)	\
	buff[len] = '\0';		\
	len += strlen(str);		\
	strcat(buff, str)
	
	c = *format++;
	while(c)
	{
		while (c != '%' && c != 0)
		{
			buff[len++] = (char)c;
			c = *format++;
		}
		if (!c)
			break;
		c = *format++;
		switch (c)
		{
			case 'u':
			case 'd':				
				to_string(va_arg(ap,int), tmp, 10);
				CAT_BUFF(tmp);					
				break;
			case 'x':
				to_hex(va_arg(ap,int), tmp);
				CAT_BUFF(tmp);
				break;
			case 'b':
				to_string(va_arg(ap,int), tmp, 2);
				CAT_BUFF(tmp);
				break;
			case 's':
				p = va_arg(ap,char*);
				if (!p)
					p = "(null)";
				CAT_BUFF(p);
				break;
			default:
				buff[len++] = (char)va_arg(ap,int);
				break;
		}
		c = *format++;
	}
	buff[len++] = '\0';	
	return (int)len;
}

void to_string(int number, char * buff, int base)
{
	char inv_buff[16];
	int offset = 0;
	int m10;
	int i = 0;
	
	do {
		m10 = number % base;
		m10 = (m10 < 0) ? -m10 : m10;
		inv_buff[offset++] = (char)('0'+ m10);
		number = number/base;
	} while (number);
	
	offset--;
	for (i = 0; offset >= 0; offset--, i++)
		buff[i] = inv_buff[offset];
	
	buff[i] = '\0';
}

void to_hex(int number, char * buff)
{
	boolean skipZeros = TRUE;
	int offset = 0;
	unsigned int hexa;
	int i;
	
	buff[offset++] = '0';
	buff[offset++] = 'x';
	
	for (i = 0; i < 8; i++)
	{
		hexa = (unsigned int)(number << (i << 2));
		hexa = (hexa >> 28) & 0xf;
		if (hexa == 0)
		{
			if (!skipZeros)
				buff[offset++] = '0';
		}
		else
		{
			skipZeros = FALSE;
			if (hexa < 10)
				buff[offset++] = '0' + hexa;
			else
				buff[offset++] = 'a' + (hexa - 10);
		}
	}
	if (skipZeros)
		buff[offset++] = '0';
		
	buff[offset] = '\0';
}

int putchar(int c)
{
	video_printc((char)c);
	return c;
}
