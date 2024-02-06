#ifndef ACC_H_
#define ACC_H_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


#define Y 0
#define Z 1
#define AX 2
#define MAX 16340
#define NOISE_DEV 4


bool fallDetection();





#endif /* ACC_H_ */
