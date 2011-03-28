/**
 * @file time.c
 * @brief It provides several functions useful for reading and 
 * 		converting the current time and date. 
 * @author Victor Borges
 * @date Mar 18, 2011
 **/

#include <time.h>

#define SEC_PER_MIN 	60
#define SEC_PER_HOUR	(60*SEC_PER_MIN)
#define SEC_PER_DAY 	(24*SEC_PER_HOUR)
#define SEC_PER_YEAR 	(365*SEC_PER_DAY)


/**
 * This structure is statically allocated and shared by gmtime, 
 * localtime and ctime functions. Each time one of these functions 
 * is called the content of the structure is overwritten.
 **/ 
static struct tm tm_time;

/**
 * The string pointed is statically allocated and shared by ctime 
 * and asctime functions. Each time one of these functions is called 
 * the content of the string is overwritten. ctime also uses 
 * internally the buffer used by gmtime and localtime as return 
 * value, so a call to this function will overwrite this.
 **/
//static char char_time[26];

/**
 * Helper structure used on mktime function
 **/
static int days_month[12] = {
	0,
	(31),
	(31+29),
	(31+29+31),
	(31+29+31+30),
	(31+29+31+30+31),
	(31+29+31+30+31+30),
	(31+29+31+30+31+30+31),
	(31+29+31+30+31+30+31+31),
	(31+29+31+30+31+30+31+31+30),
	(31+29+31+30+31+30+31+31+30+31),
	(31+29+31+30+31+30+31+31+30+31+30)
};

/************* STATIC STRING CONSTANTS FOR ENGLISH **********/
static const char sweekdays [7] [4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static const char weekdays [7] [10] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", 
    "Thursday", "Friday", "Saturday"
};
static const char smonths [12] [4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char* months [12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};
static const char ampm [4] [3] = {
    "am", "pm",
    "AM", "PM"
};

/**
 * Helper function to convert a number in a string
 **/
static void to_string(char * buff, int number)
{
	char inv_buff[16];
	int offset = 0;
	int m10;
	int i = 0;
	
	do {
		m10 = number % 10;
		m10 = (m10 < 0) ? -m10 : m10;
		inv_buff[offset++] = (char)('0'+ m10);
		number = number/10;
	} while (number);
	
	offset--;
	for (i = 0; offset >= 0; offset--, i++)
		buff[i] = inv_buff[offset];
	
	buff[i] = '\0';
}

clock_t clock (void)
{
	return -1;
}

double difftime(time_t time1, time_t time2) 
{
    return (double)time1 - (double)time2;
}

time_t mktime (struct tm * tp)
{
	int year = tp->tm_year - 1970;
	time_t time = tp->tm_sec;
	
	time += tp->tm_min*SEC_PER_MIN;
	time += tp->tm_hour*SEC_PER_HOUR;
	time += (tp->tm_mday - 1)*SEC_PER_DAY;
	time += days_month[tp->tm_mon]*SEC_PER_DAY;
	if (tp->tm_mon > 1 && ((year + 2) % 4))
		time -= SEC_PER_DAY;
	time += SEC_PER_YEAR*year + SEC_PER_DAY*((year + 1)/4);
	
	return time;
}

char *ctime(const time_t *timep) 
{
	//return asctime(localtime(timep));
	return NULL;
}

struct tm* gmtime(const time_t *t) 
{
	return NULL;
}

static int magic_month_number [12] = {
	1, 4, 5, 0, 2, 5, 0, 3, 6, 1, 4, 6
};

/* 1700 to 2100 */
static int magic_century_number [5] = {
	4, 2, 0, 6, 4
};

struct tm* localtime (const time_t *t)
{
	register time_t tmp = *t;
	tm_time.tm_year = (tmp - (SEC_PER_DAY >> 2))/(SEC_PER_YEAR + (SEC_PER_DAY >> 2)) + 1970;
	tm_time.tm_yday = ((tmp / SEC_PER_DAY) - ((tm_time.tm_year-1969) >> 2)) % 365 + 1;
	for (tm_time.tm_mon = 0; tm_time.tm_mon < 12; tm_time.tm_mon++)
		if (days_month[tm_time.tm_mon] > tm_time.tm_yday)
		{
			tm_time.tm_mon--;
			break;
		}
	tm_time.tm_mday = tm_time.tm_yday % days_month[tm_time.tm_mon] + 1;	
	
	
	tm_time.tm_wday = (tm_time.tm_year % 100) / 4 + tm_time.tm_mday 
		+ magic_month_number[tm_time.tm_mon] 
		+ magic_century_number[tm_time.tm_year/100];
	if (tm_time.tm_mon > 1 && ((tm_time.tm_yday + 2) % 4))
		tm_time.tm_wday--;
	tm_time.tm_wday = (tm_time.tm_mday % 7) - 1;
	
	tm_time.tm_hour = (tmp % SEC_PER_DAY) / SEC_PER_HOUR + 1;
	tm_time.tm_min = (tmp % SEC_PER_HOUR) / SEC_PER_MIN;
	tm_time.tm_sec = tmp % SEC_PER_MIN;
	return &tm_time;
}

size_t  strftime ( char* dst, size_t max, const char* format, const struct tm* tm )
{
    char*         p = dst;
    const char*   src;
    unsigned long no;
    char          buf [5];

    if (!max) 
		return 0;
    for ( ; *format != '\0'; format++ ) 
    {
		if (*format == '%') 
		{
			if (*++format == '%') {
				*p++ = '%';
			}
			else
	again:
			switch (*format) 
			{
				case 'n': 
					*p++ = '\n';
					break;
				case 't': 
					*p++ = '\t'; 	
					break;
				case 'O': 
				case 'E': 
					++format; 
					goto again;
				case 'c': 
					src = "%b %a %d %k:%M:%S %Z %Y";        	 
					goto _strf;
				case 'r': 
					src = "%I:%M:%S %p";                    	 
					goto _strf;
				case 'R': 
					src = "%H:%M";      			 
					goto _strf;
				case 'x': 
					src = "%b %a %d";   			 
					goto _strf;
				case 'X': 
					src = "%k:%M:%S";   			 
					goto _strf;
				case 'D': 
					src = "%m/%d/%y";   			 
					goto _strf;
				case 'T': 
					src = "%H:%M:%S";
				_strf: 
					p  += strftime (p, (size_t)(dst+max-p), src, tm); 	 
					break;
				case 'a': 
					src = sweekdays [tm->tm_wday]; 		 
					goto _str;
				case 'A': 
					src = weekdays  [tm->tm_wday]; 		 
					goto _str;
				case 'h':
				case 'b': 
					src = smonths   [tm->tm_mon];  		 
					goto _str;
				case 'B': 
					src = months    [tm->tm_mon];  		 
					goto _str;
				case 'p': 
					src = ampm [tm->tm_hour >= 12 ? 1 : 0]; 
					goto _str;
				case 'P': 
					src = ampm [tm->tm_hour >= 12 ? 3 : 2]; 
					goto _str;
				case 'C': 
					no  = tm->tm_year/100 + 19; 		 
					goto _no;
				case 'd': 
					no  = tm->tm_mday;          		 
					goto _no;
				case 'e': 
					no  = tm->tm_mday;          		 
					goto _nos;
				case 'H': 
					no  = tm->tm_hour;          		 
					goto _no;
				case 'I': 				
					if (tm->tm_hour == 12)
						no = 12;
					else
						no  = tm->tm_hour % 12;
					goto _no;
				case 'j': 
					no  = tm->tm_yday;          		 
					goto _no;
				case 'k': 
					no  = tm->tm_hour;          		 
					goto _nos;
				case 'l': 
					no  = tm->tm_hour % 12;     		 
					goto _nos;
				case 'm': 
					no  = tm->tm_mon + 1;         		 
					goto _no;
				case 'M': 
					no  = tm->tm_min;           		 
					goto _no;
				case 'S': 
					no  = tm->tm_sec;           		
					goto _no;
				case 'u': 
					no  = tm->tm_wday ? tm->tm_wday : 7; 	 
					goto _no;
				case 'w': 
					no  = tm->tm_wday;              		 
					goto _no;
				case 'U': 
					no  = (tm->tm_yday - tm->tm_wday + 7) / 7; 
					goto _no;
				case 'W': 
					no  = (tm->tm_yday - (tm->tm_wday - 1 + 7) % 7 + 7) / 7; 
					goto _no;
				case 's': 
				{
					time_t t = mktime((struct tm*)tm);
					char buf[101];
					char* c;
					buf[100] = 0;
					for (c = buf + 99; c > buf; --c) 
					{
						*c = (t % 10) + '0';
						t /= 10;
						if (!t) 
							break;
					}
					src=c;
					goto _str;
				}
				case 'Z':
					src = "[unknown timezone]";
					goto _str;
				case 'Y':
					to_string (buf, (unsigned int)(tm->tm_year));
					src = buf;
					goto _str;
				case 'y': 
					no  = tm->tm_year % 100; 			 
					goto _no;
				_no: 
					to_string ( buf, no );	/* append number 'no' */
					src = buf;
					goto _str;
				_nos: 
					to_string ( buf, no );	/* the same, but '0'->' ' */
					if (buf[0] == '0')
						buf[0] = ' ';
					src = buf;
				_str: 
					while (*src  &&  p < dst+max) /* append string */
						*p++ = *src++;
					break;
			};
		} else {
			*p++ = *format;
		}

		if (p >= dst+max)
			break;
    }

    *p = '\0';
    return p - dst;
}
