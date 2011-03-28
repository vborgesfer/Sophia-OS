/**
 * @file stdlib.c
 * @brief It defines several general operation functions and macros.
 * @note This header is imcomplete for C99 stardard
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

/******************** STRING FUNCTIONS *********************/

#define STR_TO_NUMBER(v) 								\
	int sign = 1;										\
	while ( *s == ' ' || (unsigned int)(*s - 9) < 5u) 	\
		s++;											\
	switch (*s) 										\
	{													\
		case '-': 										\
			sign=-1;									\
		case '+': 										\
			++s;										\
	}													\
	while ((unsigned int) (*s - '0') < 10u) 			\
	{													\
		v = v*10 + *s - '0'; 							\
		++s;											\
	}													
	
int atoi(const char* s) 
{
	int v = 0;
	STR_TO_NUMBER(v);
	return (sign == -1) ? -v : v;;
}

long int atol(const char* s) 
{
	long int v = 0;
	STR_TO_NUMBER(v);
	return (sign == -1) ? -v : v;;
}

s64 atoll(const char* s) 
{
	s64 v = 0;
	STR_TO_NUMBER(v);
	return (sign == -1) ? -v : v;;
}

double atof(const char *nptr) 
{
	return strtod(nptr,0);
}

#define STR_TO_PREC_NUMBER(value, factor)				\
    register const char*  p     = s;					\
    unsigned int          expo;							\
    while ( isspace(*p) )								\
        p++;											\
														\
    switch (*p) 										\
    {													\
		case '-': 										\
			sign = -1;									\
		case '+': 										\
			p++;										\
		default : 										\
			break;										\
    }													\
														\
    while ( (unsigned int)(*p - '0') < 10u )			\
        value = value*10 + (*p++ - '0');				\
														\
    if ( *p == '.' ) 									\
    {													\
        factor = 1.;									\
        p++;											\
        while ( (unsigned int)(*p - '0') < 10u ) 		\
        {												\
            factor *= 0.1;								\
            value  += (*p++ - '0') * factor;			\
        }												\
    }													\
														\
    if ( (*p | 32) == 'e' ) 							\
    {													\
        expo   = 0;										\
        factor = 10.L;									\
														\
        switch (*++p) 									\
        {												\
			case '-': 									\
				factor = 0.1;							\
			case '+': 									\
				p++;									\
				break;									\
			case '0': 									\
			case '1': 									\
			case '2': 									\
			case '3': 									\
			case '4': 									\
			case '5': 									\
			case '6': 									\
			case '7': 									\
			case '8': 									\
			case '9':									\
				break;									\
			default : 									\
				value = 0.L;							\
				p = s;									\
				if ( endptr != NULL )					\
					*endptr = (char*)p;					\
				return value * sign;					\
        }												\
														\
        while ( (unsigned int)(*p - '0') < 10u )		\
            expo = 10 * expo + (*p++ - '0');			\
														\
        forever 										\
        {												\
            if ( expo & 1 )								\
                value *= factor;						\
            if ( (expo >>= 1) == 0 )					\
                break;									\
            factor *= factor;							\
        }												\
    }													\
	if ( endptr != NULL )								\
		*endptr = (char*)p;

float strtof(const char* s, char** endptr) 
{
    register float	value = 0.;
    int 			sign  = +1;
    float 		    factor;
	STR_TO_PREC_NUMBER(value, factor);
    return value * sign;
}

double strtod(const char* s, char** endptr) 
{
    register long double  value = 0.L;
    int                   sign  = +1;
    long double           factor;
	STR_TO_PREC_NUMBER(value, factor);
    return value * sign;
}

long int strtol(const char *nptr, char **endptr, int base)
{
	int neg = 0;
	unsigned long int v;
	const char * orig = nptr;

	while ( isspace(*nptr) ) nptr++;

	if ( *nptr == '-' && isalnum(nptr[1]) ) 
	{ 
		neg=-1; 
		++nptr; 
	}
	v = strtoul(nptr,endptr,base);
	if (endptr && *endptr==nptr) 
		*endptr = (char *)orig;
	if (v >= ABS_LONG_MIN) 
	{
		if (v == ABS_LONG_MIN && neg) 
		{
			errno = 0;
			return v;
		}
		errno = ERANGE;
		return (neg ? LONG_MIN : LONG_MAX);
	}
	return (neg ? -v : v);
}

unsigned long int strtoul(const char *ptr, char **endptr, int base)
{
	int neg = 0, overflow = 0;
	unsigned long int v=0;
	const char* orig;
	const char* nptr=ptr;

	while(isspace(*nptr)) ++nptr;

	if (*nptr == '-') 
	{ 
		neg=1; 
		nptr++; 
	}
	else if (*nptr == '+') 
		++nptr;
	
	orig=nptr;
	
	if (base==16 && nptr[0]=='0') 
		goto skip0x;
	
	if (base) 
	{
		register unsigned int b=base-2;
		if (b > 34)
		{ 
			errno = EINVAL; 
			return 0; 
		}
	} else {
		if (*nptr=='0') 
		{
			base=8;
			skip0x:
			if ((nptr[1]=='x'||nptr[1]=='X') && isxdigit(nptr[2])) 
			{
				nptr+=2;
				base=16;
			}
		} else
			base=10;
	}
	
	while (*nptr) 
	{
		register unsigned char c = *nptr;
		c = (((c >= 'a' ? (c - 'a' + 10) : (c >='A')) 
				? (c -'A' + 10) : (c <= '9')) 
				? (c -'0') : 0xff);
		if (c >= base) 
			break;	/* out of base */
		{
			register unsigned long x = (v & 0xff)*base + c;
			register unsigned long w = (v>>8)*base + (x>>8);
			if (w > (ULONG_MAX >> 8)) 
				overflow=1;
			v=(w<<8)+(x&0xff);
		}
		++nptr;
	}
	if (nptr == orig) 
	{		/* no conversion done */
		nptr = ptr;
		errno = EINVAL;
		v=0;
	}
	if (endptr) 
		*endptr = (char *)nptr;
	if (overflow) 
	{
		errno = ERANGE;
		return ULONG_MAX;
	}
	return (neg ? -v : v);
}

/********************** MATH FUNCTIONS ********************/

int abs(int i) 
{ 
	return i>=0 ? i : -i; 
}

long int labs (long int i)
{
	return i>=0 ? i : -i; 
}

s64 llabs (s64 i)
{
	return i>=0 ? i : -i; 
}

#define DIV(x, numerator, denominator) 			\
	x.quot = numerator/denominator;				\
	x.rem = numerator - x.quot*denominator;

div_t div (int numerator, int denominator) 
{
	div_t x;
	DIV(x, numerator, denominator);
	return x;
}

ldiv_t ldiv (long int numerator, long int denominator) 
{
	ldiv_t x;
	DIV(x, numerator, denominator);
	return x;
}


static unsigned int seed = 1;

static int rand_r (unsigned int* seed)
{   
/* Defined algorithme in Knuth's TAOCP */
#define	M	((1U<<31) -1)
#define	A	48271
#define	Q	44488	
#define	R	3399	
	u32 x;
	
    x = *seed;
    x = A*(x%Q) - R * (u32) (x/Q);
    if (x < 0)
		x += M;

    *seed = x;
    return x;
}

int rand(void) 
{
	return rand_r (&seed);
}

void srand(unsigned int i) 
{
	seed=i; 
}
