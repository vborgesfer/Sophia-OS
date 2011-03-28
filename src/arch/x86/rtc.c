/**
 * @file ktime.h
 * @brief The RTC keeps track of the date and time, even when the 
 * 		computer's power is off.
 * @author Victor Borges
 * @date Mar 18, 2011
 **/

#include <timer.h>
#include <stdio.h>
#include "ioports.h"

#define CMOS_STATUS_A		0xA
#define CMOS_STATUS_B		0xB
#define CMOS_SECONDS		0
#define CMOS_MINUTES		2
#define CMOS_HOURS			4
#define CMOS_WEEKDAYS		6
#define CMOS_DAYS			7
#define CMOS_MONTH			8
#define CMOS_YEAR			9
#define CMOS_CENTURY		0x32
#define CMOS_CMD_PORT		0x70
#define CMOS_DATA_PORT		0x71

struct rtc_status
{
	/**
	 * |7|6|5|4|3|2|1|0|  RTC Status Register A
	 *  | | | | `---------- rate selection Bits for divider output
	 *  | | | |		 frequency (set to 0110 = 1.024kHz, 976.562æs)
	 *  | `-------------- 22 stage divider, time base being used;
	 *  |			  (initialized to 010 = 32.768kHz)
	 *  `-------------- 1=time update in progress, 
	 * 					0=time/date available
	 **/
	byte status_a;
	
	/**
	 * |7|6|5|4|3|2|1|0|  RTC Status Register B
	 *  | | | | | | | `---- 1=enable daylight savings, 0=disable
	 *  | | | | | | `----- 1=24 hour mode, 0=12 hour mode (24 default)
	 *  | | | | | `------ 1=time/date in binary, 0=BCD (BCD default)
	 *  | | | | `------- 1=enable square wave frequency, 0=disable
	 *  | | | `-------- 1=enable update ended interrupt, 0=disable
	 *  | | `--------- 1=enable alarm interrupt, 0=disable
	 *  | `---------- 1=enable periodic interrupt, 0=disable
	 *  `----------- 1=disable clock update, 0=update count normally
	 **/
	byte status_b;
};

static struct rtc_status rtc_info;

#define CMOS_READ(addr) 						\
	({ 											\
		outb_p((1<<7)|addr,CMOS_CMD_PORT); 		\
		inb_p(CMOS_DATA_PORT); 					\
	})

#define BCD_TO_BINARY(n)						\
	((n)=((n)&15) + ((n)>>4)*10)
	
inline static void update_status()
{
	rtc_info.status_a = (byte)CMOS_READ(CMOS_STATUS_A);
	rtc_info.status_b = (byte)CMOS_READ(CMOS_STATUS_B);
}

time_t read_rtc (struct tm * time_readed)
{
	short int century;
	update_status();
	
	/* Loop while update RTC bit (7) is on */
	do {
		time_readed->tm_sec = CMOS_READ(CMOS_SECONDS);
		time_readed->tm_min = CMOS_READ(CMOS_MINUTES);
		time_readed->tm_hour = CMOS_READ(CMOS_HOURS);
		time_readed->tm_mday = CMOS_READ(CMOS_DAYS);
		time_readed->tm_mon = CMOS_READ(CMOS_MONTH) - 1;
		time_readed->tm_year = CMOS_READ(CMOS_YEAR);
		century = CMOS_READ(CMOS_CENTURY);
		time_readed->tm_wday = CMOS_READ(CMOS_WEEKDAYS);
	} while (time_readed->tm_sec != CMOS_READ(CMOS_SECONDS));
	
	/* If RTC is in BCD mode */
	if (rtc_info.status_b && 0x4)
	{
		BCD_TO_BINARY(time_readed->tm_sec);
		BCD_TO_BINARY(time_readed->tm_min);
		BCD_TO_BINARY(time_readed->tm_hour);
		BCD_TO_BINARY(time_readed->tm_mday);
		BCD_TO_BINARY(time_readed->tm_mon);
		BCD_TO_BINARY(time_readed->tm_year);
		BCD_TO_BINARY(century);
		BCD_TO_BINARY(time_readed->tm_wday);
		time_readed->tm_year += century*100;
	}
	
	/* If RTC is in 12 hours mode */
	if (rtc_info.status_b && 0x2 == 0)
	{
		if (time_readed->tm_hour == 12)
			time_readed->tm_hour = 0;
		time_readed->tm_hour += 12;
	}
	
	return mktime(time_readed);
}
