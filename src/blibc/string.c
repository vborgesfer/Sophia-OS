/**
 * @file string.c
 * @brief It provides many functions useful for manipulating strings
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#include <string.h>
#include <errno.h>

void* memchr(const void *s, int c, size_t n) 
{
	const unsigned char *pc = (unsigned char *) s;
	for (;n--;pc++)
		if (*pc == c)
			return ((void *) pc);
	return 0;
}

int memcmp(const void *dst, const void *src, size_t count) 
{
	register int r;
	register const unsigned char *d = dst;
	register const unsigned char *s = src;
	++count;
	while (--count) 
	{
		if ((r = (*d - *s)))
			return r;
		++d;
		++s;
	}
	return 0;
}

void * memcpy (void *dst, const void *src, size_t n)
{
	void           *res = dst;
	unsigned char  *c1, *c2;
	c1 = (unsigned char *) dst;
	c2 = (unsigned char *) src;
	while (n--) *c1++ = *c2++;
	return (res);
}

void *memmove(void *dst, const void *src, size_t count)
{
	char *a = dst;
	const char *b = src;
	if (src!=dst)
	{
		if (src>dst)
			while (count--) *a++ = *b++;
		else
		{
			a+=count-1;
			b+=count-1;
			while (count--) *a-- = *b--;
		}
	}
	return dst;
}

void* memset(void * dst, int s, size_t count) {
	register char * a = dst;
	count++;
	while (--count)
		*a++ = s;
	return dst;
}

char* strcat(register char* s,register const char* t)
{
	char *dest=s;
	s += strlen(s);
	forever
	{
		if (!(*s = *t)) 
			break; 
		++s; 
		++t;
	}
	return dest;
}

char* strncat(char *s, const char *t, size_t n) 
{
	char *dest = s;
	register char *max;
	s += strlen(s);
	if ((max = s + n) == s) 
		return dest;
	forever 
	{
		if (!(*s = *t)) 
			break; 
		if (++s==max) 
			break; 
		++t;
	}
	*s = 0;
	return dest;
}

char *strchr(register const char *t, int c) 
{
  register char ch;
	ch = c;
	for (;;) 
	{
		if (*t == ch)
			break; 
		if (!*t)
			return 0; 
		++t;
	}
	return (char*)t;
}

size_t strlen(const char *s) 
{
	register size_t i;
	if (!s)
		return 0;
	for (i=0; *s; ++s) ++i;
	return i;
}

int strcmp (const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
		s1++, s2++;
	return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, size_t n) 
{
	register const unsigned char* a = (const unsigned char*) s1;
	register const unsigned char* b = (const unsigned char*) s2;
	register const unsigned char* fin = a+n;
	if (n == 0)
		return EINVAL;
	while (a < fin) 
	{
		register int res = *a - *b;
		if (res) 
			return res;
		if (!*a) 
			return 0;
		++a; 
		++b;
	}
	return 0;
}

int strcoll(const char *s,const char* t)
{
	return strcmp(s, t);
}

char * strcpy (char *s1, const char *s2)
{
	char *res = s1;
	while ((*s1++ = *s2++));
	return (res);
}

/**
 * Helper function
 **/
static void *memccpy(void *dst, const void *src, int c, size_t count)
{
  char *a = dst;
  const char *b = src;
  while (count--)
  {
    *a++ = *b;
    if (*b==c)
    {
      return (void *)a;
    }
    b++;
  }
  return 0;
}

char *strncpy(char *dest, const char *src, size_t n) 
{
	dest = memset(dest,0,n);
	memccpy(dest,src,0,n);
	return dest;
}

size_t strcspn(const char *s, const char *reject)
{
	size_t l = 0;
	int i;

	for (; *s; ++s) 
	{
		for (i=0; reject[i]; ++i)
			if (*s == reject[i]) 
				return l;
		++l;
	}
	return l;
}

static char * str_error = "This function is not supported yet"; 
char * strerror(result errnum) 
{
	return str_error;
}

char *strpbrk(const char *s, const char *accept) 
{
	register unsigned int i;
	for (; *s; s++)
		for (i=0; accept[i]; i++)
			if (*s == accept[i])
				return (char*)s;
	return 0;
}

char *strrchr(const char *t, int c) 
{
	register char ch;
	register const char *l=0;

	ch = c;
	forever 
	{
		if (*t == ch) 
			l=t; 
		if (!*t) 
			return (char*)l; 
		++t;
	}
	return (char*)l;
}

size_t strspn(const char *s, const char *accept)
{
	size_t l = 0;
	const char *a;
	
	for (; *s; s++) 
	{
		for (a = accept; *a && *s != *a; a++);
		if (!*a)
			break;
		else
			l++;
	}
	return l;
}

char *strstr(const char *haystack, const char *needle) 
{	
	size_t nl=strlen(needle);
	size_t hl=strlen(haystack);
	size_t i;
	if (!nl)
		return (char*)haystack;
	if (nl>hl) 
		return 0;
	for (i=hl-nl+1; i; --i) 
	{
		if (*haystack == *needle && !memcmp(haystack,needle,nl))
			return (char*)haystack;
		++haystack;
	}
	return 0;
}

char * strtok (char* s, const char* delim) 
{
	static char * strtok_pos;
	char * tmp = 0;

	if (s == 0) 
		s = strtok_pos;
	s += strspn(s,delim);
	if (*s) 
	{
		tmp = s;
		s += strcspn(s,delim);
		if (*s) 
			*s++ = 0;
	}
	strtok_pos = s;
	return tmp;
}

size_t strxfrm(char *dest, const char *src, size_t n) 
{
	dest = memset(dest,0,n);
	memccpy(dest,src,0,n);
	return strlen(dest);
}
