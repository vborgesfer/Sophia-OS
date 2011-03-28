/**
 * @file sys.h
 * @brief Some system functions
 * @author Victor Borges
 * @date Mar 22, 2011
 */
 
#include <types.h>
 
#define SCROLLOCK_LED 	1
#define NUMLOCK_LED 	2
#define CAPSLOCK_LED 	4
 
void reboot() __attribute__((__noreturn__));

void halt() __attribute__((__noreturn__));

void kbd_update_leds(byte status);
