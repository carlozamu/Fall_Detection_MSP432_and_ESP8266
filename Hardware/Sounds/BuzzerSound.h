#ifndef _BUZZERSOUND_H_
#define _BUZZERSOUND_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>


void generateBeepFall();
void generateBeepSOS();
void generateSoundRightAnswer();
void generateSoundWrongAnswer();
void SoundDialer();
void generateSoundRightAttempt();
#endif /* _BUZZERSOUND_H_ */
