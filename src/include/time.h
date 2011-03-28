/**
 * @file time.h
 * @brief It provides several functions useful for reading and 
 * 		converting the current time and date. 
 * @author Victor Borges
 * @date Mar 18, 2011
 **/
 
#include <stddef.h>

/**
 * The number of clock_t units per second.
 **/ 
#define CLOCKS_PER_SEC		10000l

/**
 * An arithmetic type elapsed processor representing time.
 **/
typedef unsigned long int 	clock_t;

/**
 * An arithmetic type representing calendar time.
 **/ 
typedef unsigned long int	time_t;

/**
 * Represents the components of calendar time.
 **/ 
struct tm
{
	int tm_sec;		/**< Seconds after the minute */
	int tm_min; 	/**< Minutes after the hour */
	int tm_hour;	/**< Hours since midnight */
	int tm_mday;	/**< Day of the month */
	int tm_mon;		/**< Months since January */
	int tm_year;	/**< Years since 1900 */
	int tm_wday;	/**< Days since Sunday */
	int tm_yday;	/**< Days since January 1 */
	int tm_isdst;	/**< Daylight Saving Time flag */
};

/**
 * Returns elapsed processor time used by program or -1 if not 
 * available.
 **/ 
clock_t clock(void);

/**
 * Returns current calendar time or -1 if not available. 
 * If tp is non-NULL, return value is also assigned to *tp.
 * @param [out]	tp		value to be assigned
 * @return current calendar time
 **/ 
time_t time(time_t * tp);

/**
 * Returns the difference in seconds between time2 and time1.
 * @param time2		First time type
 * @param time1		Second time type
 * @param the difference in seconds
 * @warning Difftime introduces an unnecessary floating point 
 * 			dependency.
 **/
double difftime (time_t time2, time_t time1);

/**
 * Returns the corresponding calendar time, or -1 if it cannot be 
 * represented.
 * @param tp	Time structure
 * @return strucure in calendar time
 **/
time_t mktime(struct tm* tp);

/**
 * Returns a pointer to a string which represents the day and time 
 * of the structure timeptr. The string is in the following format: 
 * DDD MMM dd hh:mm:ss YYYY
 * @param tp	Time structure
 * @return a time string
 **/
char * asctime(const struct tm* tp);

/**
 * Returns string equivalent to calendar time tp converted to local 
 * time.
 * @param tp	a calendar time
 * @return a string
 **/
char * ctime (const time_t *tp);

/**
 * Returns calendar time *tp converted to Coordinated Universal 
 * Time, or NULL if not available.
 * @param tp	a calendar time
 * @return the CUT time
 **/
struct tm * gmtime (const time_t *tp);

/**
 * Returns calendar time *tp converted into local time.
 * @param tp	a calendar time
 * @return	the local time
 **/
struct tm * localtime(const time_t * tp);

/**
 * Formats *tp into s according to fmt. A conversion character 
 * begins with the % sign and is followed by another character 
 * which defines a special value that it is to be replaced by.
 * Character	 What it is replaced by
 * %a	 abbreviated weekday name
 * %A	 full weekday name
 * %b	 abbreviated month name
 * %B	 full month name
 * %c	 appropriate date and time representation
 * %d	 day of the month (01-31)
 * %H	 hour of the day (00-23)
 * %I	 hour of the day (01-12)
 * %j	 day of the year (001-366)
 * %m	 month of the year (01-12)
 * %M	 minute of the hour (00-59)
 * %p	 am/pm designator
 * %P	 AM/PM designator
 * %S	 second of the minute (00-61)
 * %U	 week number of the year where Sunday is the first day of 
 * 		 week 1 (00-53)
 * %w	 weekday where Sunday is day 0 (0-6)
 * %W	 week number of the year where Monday is the first day of 
 *       week 1 (00-53)
 * %x	 appropriate date representation
 * %X	 appropriate time representation
 * %y	 year without century (00-99)
 * %Y	 year with century
 * %Z	 time zone (possibly abbreviated) or no characters if time 
 * 		 zone isunavailable
 * %%	 %
 * @param [out] s		buffer to be affected
 * @param 		smax	max size buffer
 * @param 		fmt	format
 * @param 		tm	the time structure
 * @return  The number of characters stored into str not including 
 * 		the terminating null character. On error zero is returned.
 **/
size_t strftime(char *s, size_t smax, const char* fmt, const struct tm * tp);

