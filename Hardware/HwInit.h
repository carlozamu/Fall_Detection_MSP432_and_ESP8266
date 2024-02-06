#ifndef HWINIT_H_
#define HWINIT_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>


#include "Sounds/BuzzerSound.h"
#include "alarm.h"
#include "../Communications/uartController.h"
#include "acc.h"
#include "../Communications/delay.h"


//BUTTON S1 AND S2 DEFINITIONS
#define BUTTON_S1_PORT GPIO_PORT_P5
#define BUTTON_S1_PIN GPIO_PIN1
#define BUTTON_S2_PORT GPIO_PORT_P3
#define BUTTON_S2_PIN GPIO_PIN5


void _configureButtons(); //configure and enable interrupts for button S1 and S2
void _buzzerInit();       //initialize buzzer
void _graphicsInit();     //initialize graphics
void _ledInit();          //initialize LEDs used for alarms
void _initUART();         //initialize UART protocol used to communicate with ESP8266
void _accelSensorInit();  //initialize Accelerometer
void _joystickInit();     //initialize Joystick
void _ADC_init();         //initialize ADC14 analog to digital conversions, used for Accelerometer and Joystick
void _ADC_enable();       //enable interrupt whenever a conversion is complete
void _hwInit();           //only function called in main, used to initialize all hardware at startup



#endif /* HWINIT_H_ */
