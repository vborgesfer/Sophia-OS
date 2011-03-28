/**
 * @file memory.c
 * @brief Implementation of keyboard management
 * @author Victor Borges
 * @date Mar 15, 2011
 */
 
#include <io/irq.h>
#include <io/keyboard.h>
#include <io/video.h>
#include <sys.h>
#include <ctype.h>
#include "ioports.h"

#define KB_PORT 	0x60

#define KBD_LCTRL_PRESSED 		(1<<0)
#define KBD_LALT_PRESSED  		(1<<1)
#define KBD_DEL_PRESSED  		(1<<2)
#define KBD_RCTRL_PRESSED 		(1<<3)
#define KBD_RALT_PRESSED  		(1<<4)
#define KBD_LSHFT_PRESSED 		(1<<5)
#define KBD_RSHFT_PRESSED  		(1<<6)
#define KBD_CAPSLOCK_PRESSED  	(1<<7)


static unsigned char kbd_us[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* 42 - Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* 54 - Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* 58 - Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

struct kb_stream kb_cache;

static byte kb_status = 0;

/**
 * Simple Keyboard handler routine
 **/
static void kb_handler(int id_irq)
{	
	unsigned char c;
	boolean key_up = FALSE;
	unsigned char mask = 0;
	
	c = inb(KB_PORT);
	
	if (c == 0xe0)
    {
      inb(KB_PORT);
      return;
    }
	
	if (c < 0x80)
	{
		if (kbd_us[c] == '\b')
		{
			video_backspace();
			kb_cache.size--;
			return;
		}
		if (kb_cache.size >= 256)
		{
			kb_cache.stream[kb_cache.size] = '\0';
			video_print("\nMaximum cache size!\n");
			kb_cache.size = 0;
			kb_cache.stream[0] = '\0';
			return;
		}
		if (kbd_us[c] != 0)
		{
			if (kb_status & (KBD_LSHFT_PRESSED | KBD_RSHFT_PRESSED
								| KBD_CAPSLOCK_PRESSED))
				video_printc(toupper(kbd_us[c]));
			else
				video_printc(kbd_us[c]);
			kb_cache.stream[kb_cache.size++] = kbd_us[c];
		}
	} 
	
	if (c >= 0x80)
	{
		key_up = TRUE;
		c -= 0x80;
	}
	
	switch (c)
	{
		case 42: /* Left Shift */
			mask = KBD_LSHFT_PRESSED;
			break;
		case 54: /* Right Shift */
			mask = KBD_RSHFT_PRESSED;
			break;
		case 58: /* Capslock */
			if (key_up == FALSE)
			{
				if (kb_status & KBD_CAPSLOCK_PRESSED)
					kb_status &= ~KBD_CAPSLOCK_PRESSED;
				else
					kb_status |= KBD_CAPSLOCK_PRESSED;
				kbd_update_leds(CAPSLOCK_LED);
			}
			break;
		case 29: /* Left Ctrl */
			mask = KBD_LCTRL_PRESSED;
			break;
		case 56 /* Left ALT */:
			mask = KBD_LALT_PRESSED;
			break;
		case 83: /* Del */
			mask = KBD_DEL_PRESSED;
			break;
		default:
			break;
	}
	
	if (key_up)
		kb_status &= ~mask;
	else
		kb_status |= mask;

	if (kb_status == (KBD_LALT_PRESSED | KBD_LCTRL_PRESSED 
					|KBD_DEL_PRESSED))
		reboot();
}

result kb_setup()
{
	return irq_set_routine(IRQ_KEYBOARD, kb_handler);
}
