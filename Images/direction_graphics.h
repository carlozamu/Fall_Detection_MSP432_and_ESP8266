
#ifndef DIRECTION_GRAPHICS_H_
#define DIRECTION_GRAPHICS_H_



#include "images_definitions.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "contextGraphic.h"
#include "images.h"
// redraw direction images when the current direction is FORWARD
void drawDirectionUp();

// redraw direction images when the current direction is BACKWARD
void drawDirectionDown();

// redraw direction images when the current direction is LEFT
void drawDirectionLeft();

// redraw direction images when the current direction is RIGHT
void drawDirectionRight();
void drawDirectionNone();
void drawCorrect();
void drawWrong();



#endif /* DIRECTION_GRAPHICS_H_ */
