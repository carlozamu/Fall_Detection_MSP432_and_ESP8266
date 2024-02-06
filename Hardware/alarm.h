#ifndef ALARM_H_
#define ALARM_H_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <math.h>
#include "HwInit.h"
#include <stdlib.h>
#include <stdint.h>
#include "../Images/contextGraphic.h"
#include "Sounds/BuzzerSound.h"
#include "../Communications/uartController.h"
#include "../Communications/telegram.h"


void flashLights();
void flashRedScreen();
void alarm();
void GenerateCallSOS();


#endif /* ALARM_H_ */
