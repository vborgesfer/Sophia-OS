/**
 * @file video.c
 * @brief Simple video driver for VGA, x86 implementation
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include <io/video.h>
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
	unsigned int pos;	/**< Currently cursor position */
	byte color;			/**< Currently default color */
};

/** The base pointer for the video memory mapped */
static volatile pointer video = (volatile pointer) VIDEO_ADDRESS;

/** Currently video status */
static struct video_status status;

/** Calculates the new line position */
#define NEWLINE(pos)						\
	pos = (COLUMNS*(pos/(COLUMNS << 1) + 1)) << 1

void video_update_cursor()
{
	outb(0x0F, CRT_REG_INDEX);
	outb((unsigned char)(status.pos & 0xFF), CRT_REG_INDEX);
	
	outb(0x0E, CRT_REG_DATA);
	outb((unsigned char )((status.pos>>8) & 0xFF), CRT_REG_DATA);
}

void video_setup()
{
	status.pos = 0;
	status.color = VIDEO_BG_DEFAULT | VIDEO_FG_WHITE;
	
	/* Access to register 0xa ("cursor start")*/
	outb(0x0a, CRT_REG_INDEX);
	/* CRT Register 0xa => bit 5 = cursor OFF */
	outb(1 << 5, CRT_REG_DATA);	
}

void video_printc(const char c)
{
	if (c == '\n' || c == '\r')
	{
		NEWLINE(status.pos);
		if (status.pos >= 2*LINES*COLUMNS) 			
			video_scrolling(1);
		return;
	}
	video[status.pos++] = c;
	video[status.pos++] = status.color;
}

void video_print(const char * str)
{
	int i = 0;		
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			NEWLINE(status.pos);
			if (status.pos >= 2*LINES*COLUMNS) 			
				video_scrolling(1);
			continue;
		}
		video[status.pos++] = str[i];
		video[status.pos++] = status.color;
	}
}

static void toString(int number, char * buff, int base)
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

static void toHex(int number, char * buff)
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

void video_printf(char * format, ...)
{
	char *p;
	int c;
	char buff[32];
	char ** arg = (char**) &format;
	
	arg++;
	
	c = *format++;
	while(c)
	{
		if (c != '%')
			video_printc(c);
		else
		{
			c = *format++;
			switch (c)
			{
				case 'u':
				case 'd':				
					toString(*((int *) arg++), buff, 10);
					video_print(buff);
					break;
				case 'x':
					toHex(*((int *) arg++), buff);
					video_print(buff);
					break;
				case 'b':
					toString(*((int *) arg++), buff, 2);
					video_print(buff);
					break;
				case 's':
					p = *arg++;
					if (!p)
						p = "(null)";
					video_print(p);
					break;
				default:
					video_printc(*((int *) arg++));
					break;
			}
		}
		c = *format++;
	}
}

void video_newline()
{
	NEWLINE(status.pos);
	if (status.pos >= 2*LINES*COLUMNS) 			
		video_scrolling(1);
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
}

void video_scrolling(int nblines)
{
	int i;
	for (i = 2*nblines*COLUMNS; i < 2*LINES*COLUMNS; i++)
		video[i - 2*nblines*COLUMNS] = video[i];
	for (i = 2*(LINES-nblines)*COLUMNS; i < 2*LINES*COLUMNS;)
	{
		video[i++] = 0;
		video[i++] = status.color;
	}
	status.pos -= nblines*COLUMNS;
}

void video_set_color(byte newColor)
{ 
	status.color = newColor;
}

void video_put(const char * str, byte newColor,
		const int row, const int col)
{
	int i;
	int position = 2*(row*COLUMNS + col);
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			NEWLINE(position);
			continue;
		}
		video[position++] = str[i];
		video[position++] = newColor;
	}
}

void video_putc(char c, const byte newColor,
		const int row, const int col)
{
	int position = 2*(row*COLUMNS + col);
	if (c == '\n' || c == '\r')
	{
		NEWLINE(position);
		return;
	}
	video[position++] = c;
	video[position++] = newColor;
}
