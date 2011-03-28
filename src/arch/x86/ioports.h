/**
 * @file ioports.h
 * @brief Intel-specific I/O space access routines.
 * @author Victor Borges
 * @date Mar 12, 2011
 */
 
#ifndef _IOPORTS_H_
#define _IOPORTS_H_

/** Read one byte from an I/O port 
 * @param port		Address port 
 **/
#define inb(port)                                               \
({                                                              \
  unsigned char _v;                                             \
  __asm__ volatile (                                            \
        "inb %w1,%0"                                            \
        :"=a" (_v)                                              \
        :"Nd" (port)                                            \
        );                                                      \
  _v;                                                           \
})

/** 
 * Allows to write a byte into an I/O port 
 * @param value		Value to write (it will use only the first byte)
 * @param port		Address port
 **/
#define outb(value, port)                                       \
  __asm__ volatile (                                            \
        "outb %b0,%w1"                                          \
        ::"a" (value),"Nd" (port)                               \
        )                                                       \

/** 
 * Read one byte from an I/O port and ends with a little pause
 * @param port		Address port 
 **/
#define inb_p(port) ({ 											\
unsigned char _v; 												\
__asm__ volatile ("inb %%dx,%%al\n" 							\
	"\tjmp 1f\n" 												\
	"1:\tjmp 1f\n" 												\
	"1:":"=a" (_v):"d" (port)); 								\
_v; \
})


/** 
 * Allows to write a byte into an I/O port and ends with a little pause
 * @param value		Value to write (it will use only the first byte)
 * @param port		Address port
 **/
#define outb_p(value,port) 										\
__asm__ ("outb %%al,%%dx\n" 									\
		"\tjmp 1f\n" 											\
		"1:\tjmp 1f\n" 											\
		"1:"::"a" (value),"d" (port))

#endif /* _IOPORTS_H_ */
