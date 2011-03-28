/**
 * @file assert.c
 * @brief ISO C99 Standard: 7.2 Diagnostics	Imprementation
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

#include <assert.h>
#include <io/video.h>
#include <types.h>

void assert_fail(const char * exp, const char * file, unsigned int line)
{
	video_printf("\nASSERTION FAILED : %s :  %s - %d", exp, file, line);
	forever asm("hlt\n");
}
