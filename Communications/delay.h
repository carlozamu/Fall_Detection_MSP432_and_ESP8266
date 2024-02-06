#ifndef _DELAY_H_
#define _DELAY_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


#define DELAY_WITH_TIMER

#define DELAY_RUNNING 0
#define DELAY_GONE 1
#define DELAY_TIMER_FREQUENCY_HZ 128000

extern void delay_init(void);

extern void delay(uint32_t sec);

#endif /* _DELAY_H_ */
