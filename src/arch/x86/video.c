/**
 * @file video.c
 * @brief Simple video driver for VGA, x86 implementation
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include <io/video.h>
#include <stdio.h>
#include <types.h>
#include "ioports.h"

/** Number of lines in simple mode */
#define LINES			25 
/** Number of columns in simple mode */
#define COLUMNS			80

/** Video mapped address in x86 architecture */
#define VIDEO_ADDRESS	0xb8000 

/** Cursor low port to vga index register */
#define CRT_REG_INDEX	0x3D4 
/** Cursor high port to vga index register */
#define CRT_REG_DATA	0x3D5 

/**
 * Currently struct status of the video
 */ 
struct video_status
{
	boolean title;		/**< Currently image has a title */
	unsigned int pos;	/**< Currently cursor position */
	byte color;			/**< Currently default color */
};

/** The base pointer for the video memory mapped */
static volatile pointer video = (volatile pointer) VIDEO_ADDRESS;

/** Currently video status */
static struct video_status status;

/** Calculates the new line position */
#define NEWLINE(pos, color)						\
	video[pos] = 0;								\
	video[pos+1] = color;						\
	pos = (COLUMNS*(pos/(COLUMNS << 1) + 1)) << 1

void video_update_cursor()
{
	//outb(0x0a, CRT_REG_INDEX);
	//outb((unsigned char)(status.pos & 0xFF), CRT_REG_INDEX);
	
	//outb(0x0E, CRT_REG_DATA);
	//outb((unsigned char )((status.pos>>8) & 0xFF), CRT_REG_DATA);
	video[status.pos] = '_';
	video[status.pos + 1] = status.color | VIDEO_FG_BLINKING;
}

void video_setup()
{
	status.title = FALSE;
	status.pos = 0;
	status.color = VIDEO_BG_DEFAULT | VIDEO_FG_WHITE;

	/* Access to register 0xa ("cursor start")*/
	outb(0x0a, CRT_REG_INDEX);
	/* CRT Register 0xa => bit 5 = cursor OFF */
	outb(1 << 5, CRT_REG_DATA);	
}

void video_set_title(byte color)
{
	int i;
	status.title = TRUE;
	for (i = 1; i < 2*COLUMNS; i += 2)
		video[i] = color;
	status.pos = 2*COLUMNS;	
}

void video_printc(const char c)
{
	int j;
	if (status.pos >= 2*LINES*COLUMNS)
		video_scrolling(1);
		
	if (c == '\n' || c == '\r')
	{
		NEWLINE(status.pos, status.color);
		if (status.pos >= 2*LINES*COLUMNS) 			
			video_scrolling(1);
		return;
	}
	if (c == '\t')
	{
		for (j = 0; j < 4; ++j)
		{
			video[status.pos++] = ' ';
			video[status.pos++] = status.color;
		}
		return;
	}
	video[status.pos++] = c;
	video[status.pos++] = status.color;
	video_update_cursor();
}

void video_backspace()
{
	video[status.pos] = 0;	
	video[status.pos + 1] = status.color;	
	status.pos -= 2;
	video[status.pos] = 0;
	video_update_cursor();
}

void video_done (boolean ok)
{
	int i = status.pos % (COLUMNS << 1);
	for (; i < (COLUMNS << 1) - 16; i += 2)
	{
		video[status.pos++] = '.';
		video[status.pos++] = status.color;
	}
	if (ok)
		video_print(" [DONE] ");
	else
		video_print(" [FAIL] ");
	if (status.pos >= 2*LINES*COLUMNS) 			
		video_scrolling(1);
}

void video_print(const char * str)
{
	int i = 0, j;		
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			NEWLINE(status.pos, status.color);
			if (status.pos >= 2*LINES*COLUMNS) 			
				video_scrolling(1);
			continue;
		}
		if (str[i] == '\t')
		{
			for (j = 0; j < 4; ++j)
			{
				video[status.pos++] = ' ';
				video[status.pos++] = status.color;
			}
			continue;
		}
		video[status.pos++] = str[i];
		video[status.pos++] = status.color;
	}
	video_update_cursor();
	if (status.pos >= 2*LINES*COLUMNS) 			
		video_scrolling(1);
}

/**
 *	@deprecated
 **/
void video_printf(char * format, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vprintf(format, arg_ptr);
	va_end(arg_ptr);
}

void video_newline()
{
	NEWLINE(status.pos, status.color);
	if (status.pos >= 2*LINES*COLUMNS) 			
		video_scrolling(1);
	video_update_cursor();
}

void video_clear(byte bkColor)
{
	int i;
	for (i = 0; i < 2*LINES*COLUMNS;)
	{
		video[i++] = 0;
		video[i++] = bkColor;
	}
	status.pos = 0;
	video_update_cursor();
}

void video_scrolling(int nblines)
{
	int i = (status.title ?  2*(nblines + 1)*COLUMNS : 2*nblines*COLUMNS);
	for (; i < 2*LINES*COLUMNS; i++)
		video[i - 2*nblines*COLUMNS] = video[i];
	i = (status.title ?  2*(LINES-nblines)*COLUMNS : 2*(LINES-nblines)*COLUMNS);
	for (; i < 2*LINES*COLUMNS;)
	{
		video[i++] = 0;
		video[i++] = status.color;
	}
	status.pos -= 2*nblines*COLUMNS;
	video_update_cursor();
}

void video_set_color(byte newColor)
{ 
	status.color = newColor;
}

void video_put(const char * str, byte newColor,
		const int row, const int col)
{
	int i, j;
	int position = 2*(row*COLUMNS + col);
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			NEWLINE(position, newColor);
			continue;
		}
		if (str[i] == '\t')
		{
			for (j = 0; j < 4; ++j)
			{
				video[position++] = ' ';
				video[position++] = newColor;
			}
			continue;
		}
		video[position++] = str[i];
		video[position++] = newColor;
	}
}

void video_putc(char c, const byte newColor,
		const int row, const int col)
{
	int j;
	int position = 2*(row*COLUMNS + col);
	if (c == '\n' || c == '\r')
	{
		NEWLINE(position, newColor);
		return;
	}
	if (c == '\t')
	{
		for (j = 0; j < 4; ++j)
		{
			video[position++] = ' ';
			video[position++] = newColor;
		}
		return;
	}
	video[position++] = c;
	video[position++] = newColor;
}
