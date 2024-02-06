#ifndef GAME_H_
#define GAME_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <stdbool.h>
#include "../Images/contextGraphic.h"
#include "../Images/direction_graphics.h"
#include "../Hardware/Sounds/BuzzerSound.h"

#define ATTEMPT 2 // Number of correct attempts required, default '3'

void drawMove(int moveNumber);
void drawSequence(char c);
void drawArrow(char c);
char generateRandomDirection();
bool playGame(int t,int correct);
bool GameManager();
void randInit();


#endif /* GAME_H_ */
