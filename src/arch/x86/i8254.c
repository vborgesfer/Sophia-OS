/**
 * @file video.h
 * @brief Configure the timer of the 82c54 chip as a rate generator
 * @author Victor Borges
 * @date Mar 18, 2011
 */
 
#include <timer.h>
#include <errno.h>
#include "ioports.h"

/** 82c54 clock frequency */
#define I8254_MAX_FREQ 1193182

/* Ports to communicate with the 82c54 */
#define I8254_TIMER0  0x40
#define I8254_TIMER1  0x41
#define I8254_TIMER2  0x42
#define I8254_CONTROL 0x43

result pit_setup (unsigned int freq)
{
  unsigned int nb_tick;

  if (freq <= 0)
    return errno = EINVAL;

  /* Compute counter value */
  nb_tick = I8254_MAX_FREQ / freq;

  /* Counter must be between 1 and 65536 */
  if (nb_tick > 65536)
    return errno = EINVAL;
  if (nb_tick <= 0)
    return errno = EINVAL;

  /* The i8254 interprets 0 to mean counter == 65536, because 65536
     cannot be coded on 16bits */
  if (nb_tick == 65536)
    nb_tick = 0;
  
  /* we configure timer in mode 2, as a rate generator */
  outb_p(0x34, I8254_CONTROL);

  /* Send LSB of counter first */
  outb_p((nb_tick & 0xFF), I8254_TIMER0);

  /* Send MSB of counter */
  outb_p((nb_tick >> 8) & 0xFF, I8254_TIMER0);

  return OK;
}
