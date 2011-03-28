/**
 * @file ktime.h
 * @brief It provides several functions kernel timing
 * @author Victor Borges
 * @date Mar 18, 2011
 **/
 
#include <timer.h>
#include <errno.h>
#include <io/irq.h>

#include <stdio.h>
#include <io/video.h>

#define HZ		1000

#define CMOS_READ(addr) 			\
	({ 								\
		outb_p(0x80 |addr,0x70); 	\
		inb_p(0x71); 				\
	})
 
clock_t		clock_ticks;

time_t		timestamp;

static struct tm actual_time;

static void timer_handler (int id)
{
	static char buff [30];
	clock_ticks++;
	if (clock_ticks % 10000 == 0)
	{
		timestamp++;
		actual_time.tm_sec++;
		if (actual_time.tm_sec >= 60)
		{
			actual_time.tm_min++;
			actual_time.tm_sec = 0;
		}
		if (actual_time.tm_min >= 60)
		{
			actual_time.tm_hour++;
			actual_time.tm_min = 0;
		}
		strftime(buff, 30, "%a, %b %d %Y, %H:%M:%S", &actual_time);
		video_put(buff, VIDEO_BG_BLUE | VIDEO_FG_WHITE, 0, 54);
	}
}

result timer_setup(void)
{
	timestamp = read_rtc(&actual_time);
	pit_setup(HZ);
	irq_set_routine(IRQ_TIMER, timer_handler);
	return OK;
}
