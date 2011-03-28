/**
 * @file ctype.c
 * @brief Implementation of standard ctype functions
 * @note In the standard, these functions return an integer,
 * 		here, they return a boolean defined in types.h
 * @author Victor Borges
 * @date Mar 17, 2011
 **/
 
#include <ctype.h>

boolean isalnum(int ch) 
{
	return isalpha(ch) || isdigit(ch);
}

boolean isalpha(int ch) 
{
	return (unsigned int)((ch | 0x20) - 'a') < 26u;
}

boolean isascii ( int ch ) 
{
    return (unsigned int)ch < 128u;
}

boolean isblank ( int ch )
{
    return ch == ' '  ||  ch == '\t';
}

boolean iscntrl ( int ch ) 
{
    return (unsigned int)ch < 32u  ||  ch == 127;
}

boolean isdigit ( int ch ) 
{
    return (unsigned int)(ch - '0') < 10u;
}

boolean isgraph ( int ch ) 
{
  return (unsigned int)(ch - '!') < 127u - '!';
}

boolean islower ( int ch ) 
{
    return (unsigned int) (ch - 'a') < 26u;
}

boolean isprint (int ch) 
{
	ch &= 0x7f;
	return (ch>=32 && ch<127);
}

boolean ispunct ( int ch ) 
{
    return isprint (ch)  &&  !isalnum (ch)  &&  !isspace (ch);
}

boolean isspace ( int ch )
{
    return (unsigned int)(ch - 9) < 5u  ||  ch == ' ';
}

boolean isupper ( int ch )
{
    return (unsigned int)(ch - 'A') < 26u;
}

boolean isxdigit ( int ch )
{
    return (unsigned int)( ch         - '0') < 10u  || 
           (unsigned int)((ch | 0x20) - 'a') <  6u;
}

int tolower(int ch) 
{
	if ( (unsigned int)(ch - 'A') < 26u )
		ch += 'a' - 'A';
	return ch;
}

int toupper(int ch) 
{
	if ( (unsigned int)(ch - 'a') < 26u )
		ch += 'A' - 'a';
	return ch;
}
