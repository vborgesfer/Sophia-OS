/**
 * @file ktime.h
 * @brief It provides several functions kernel timing
 * @author Victor Borges
 * @date Mar 18, 2011
 **/

#include <types.h>
#include <time.h>

/**
 * Number of ticks since computer is on
 **/
extern clock_t		clock_ticks;

/**
 * RTC date time
 **/ 
extern time_t		timestamp;

/**
 * PC programmable timer
 * Programmable timer routines.
 * @param freq		Timer frequency
 * @return OK		- Success \n
 * 		   EINVAL   - Invalid arguments
 **/
result pit_setup (unsigned int freq);

/**
 * Call PIT setup and set up timer handler
 * Programmable timer routines.
 * @return OK		- Success \n
 * 		   EINVAL   - Invalid arguments
 **/
result timer_setup (void);

time_t read_rtc (struct tm * time_readed);
