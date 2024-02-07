#include "direction_graphics.h"


typedef enum {NONE, UP, DOWN, LEFT, RIGHT} Direction_t;

// keep track of the direction during the execution to avoid useless redrawing
Direction_t currentDirection = NONE;


// CONSTANTS FOR IMAGE PLACEMENT

const uint8_t RIGHT_DIRECTION_OFFSET_X = 76;
const uint8_t RIGHT_DIRECTION_OFFSET_Y = 46;

const uint8_t LEFT_DIRECTION_OFFSET_X = 8;
const uint8_t LEFT_DIRECTION_OFFSET_Y = 46;

const uint8_t DOWN_DIRECTION_OFFSET_X = 46;
const uint8_t DOWN_DIRECTION_OFFSET_Y = 76;

const uint8_t UP_DIRECTION_OFFSET_X = 46;
const uint8_t UP_DIRECTION_OFFSET_Y = 8;

const uint8_t CORRECT_OFFSET_X = 0;
const uint8_t CORRECT_OFFSET_Y = 0;

const uint8_t WRONG_OFFSET_X = 0;
const uint8_t WRONG_OFFSET_Y = 0;

// IMAGES FOR THE DIRECTIONS

const tImage CORRECT_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    wrong_width,
    wrong_height,
    wrong_size,
    palette_GREEN_WHITE_1BPP_UNCOMP,
    pixel_CORRECT_1BPP_UNCOMP,
};


const tImage WRONG_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    correct_width,
    correct_height,
    correct_size,
    palette_BLACK_RED_1BPP_UNCOMP,
    pixel_WRONG_1BPP_UNCOMP,
};

const tImage DOWN_RED_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    backward_width,
    backward_height,
    backward_size,
    palette_BLACK_RED_1BPP_UNCOMP,
    pixel_DOWN_1BPP_UNCOMP,
};

const tImage DOWN_WHITE_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    backward_width,
    backward_height,
    backward_size,
    palette_BLACK_WHITE_1BPP_UNCOMP,
    pixel_DOWN_1BPP_UNCOMP,
};

const tImage LEFT_RED_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    left_width,
    left_height,
    left_size,
    palette_BLACK_RED_1BPP_UNCOMP,
    pixel_LEFT_1BPP_UNCOMP,
};

const tImage LEFT_WHITE_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    left_width,
    left_height,
    left_size,
    palette_BLACK_WHITE_1BPP_UNCOMP,
    pixel_LEFT_1BPP_UNCOMP,
};

const tImage RIGHT_RED_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    right_width,
    right_height,
    right_size,
    palette_BLACK_RED_1BPP_UNCOMP,
    pixel_RIGHT_1BPP_UNCOMP,
};

const tImage RIGHT_WHITE_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    right_width,
    right_height,
    right_size,
    palette_BLACK_WHITE_1BPP_UNCOMP,
    pixel_RIGHT_1BPP_UNCOMP,
};

const tImage DIRECTIONS_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    directions_width,
    directions_height,
    directions_size,
    palette_BLACK_WHITE_1BPP_UNCOMP,
    pixel_DIRECTIONS_1BPP_UNCOMP,
};

const tImage UP_RED_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    FORWARD_width,
    FORWARD_height,
    FORWARD_size,
    palette_BLACK_RED_1BPP_UNCOMP,
    pixel_UP_1BPP_UNCOMP,
};

const tImage UP_WHITE_1BPP_UNCOMP = {
    IMAGE_FMT_1BPP_UNCOMP,
    FORWARD_width,
    FORWARD_height,
    FORWARD_size,
    palette_BLACK_WHITE_1BPP_UNCOMP,
    pixel_UP_1BPP_UNCOMP,
};


// redraw direction images when the current direction is FORWARD
void drawDirectionUp(){
    Graphics_drawImage(&g_sContext, &UP_RED, UP_DIRECTION_OFFSET_X, UP_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &DOWN_WHITE, DOWN_DIRECTION_OFFSET_X, DOWN_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &LEFT_WHITE, LEFT_DIRECTION_OFFSET_X, LEFT_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &RIGHT_WHITE, RIGHT_DIRECTION_OFFSET_X, RIGHT_DIRECTION_OFFSET_Y);
}

// redraw direction images when the current direction is BACKWARD
void drawDirectionDown(){
    Graphics_drawImage(&g_sContext, &UP_WHITE, UP_DIRECTION_OFFSET_X, UP_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &DOWN_RED, DOWN_DIRECTION_OFFSET_X, DOWN_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &LEFT_WHITE, LEFT_DIRECTION_OFFSET_X, LEFT_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &RIGHT_WHITE, RIGHT_DIRECTION_OFFSET_X, RIGHT_DIRECTION_OFFSET_Y);
}

// redraw direction images when the current direction is LEFT
void drawDirectionLeft(){
    Graphics_drawImage(&g_sContext, &UP_WHITE, UP_DIRECTION_OFFSET_X, UP_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &DOWN_WHITE, DOWN_DIRECTION_OFFSET_X, DOWN_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &LEFT_RED, LEFT_DIRECTION_OFFSET_X, LEFT_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &RIGHT_WHITE, RIGHT_DIRECTION_OFFSET_X, RIGHT_DIRECTION_OFFSET_Y);
}

// redraw direction images when the current direction is RIGHT
void drawDirectionRight(){
    Graphics_drawImage(&g_sContext, &UP_WHITE, UP_DIRECTION_OFFSET_X, UP_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &DOWN_WHITE, DOWN_DIRECTION_OFFSET_X, DOWN_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &LEFT_WHITE, LEFT_DIRECTION_OFFSET_X, LEFT_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &RIGHT_RED, RIGHT_DIRECTION_OFFSET_X, RIGHT_DIRECTION_OFFSET_Y);
}

// redraw direction images when the current direction is NONE
void drawDirectionNone(){
    Graphics_drawImage(&g_sContext, &UP_WHITE, UP_DIRECTION_OFFSET_X, UP_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &DOWN_WHITE, DOWN_DIRECTION_OFFSET_X, DOWN_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &LEFT_WHITE, LEFT_DIRECTION_OFFSET_X, LEFT_DIRECTION_OFFSET_Y);
    Graphics_drawImage(&g_sContext, &RIGHT_WHITE, RIGHT_DIRECTION_OFFSET_X, RIGHT_DIRECTION_OFFSET_Y);
}

void drawCorrect(){
    Graphics_drawImage(&g_sContext, &CORRECT_GREEN, CORRECT_OFFSET_X, CORRECT_OFFSET_Y);

}

void drawWrong(){
    Graphics_drawImage(&g_sContext, &WRONG_RED, WRONG_OFFSET_X, WRONG_OFFSET_Y);
}


