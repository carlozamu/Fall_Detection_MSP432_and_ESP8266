#include "game.h"

//----------------------------------------------------------------

/* ADC results buffer */
static uint16_t resultsBuffer[2];

// Draws the move number on the display
void drawMove(int moveNumber)
{
    Graphics_clearDisplay(&g_sContext);

    char moveString[10];
    sprintf(moveString, "Move %d", moveNumber);
    GrContextFontSet(&g_sContext, &g_sFontCmtt26);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) moveString,
    AUTO_STRING_LENGTH,
                                64, 50, OPAQUE_TEXT);
    _delay_cycles(30000000);
    Graphics_clearDisplay(&g_sContext);
}
// Draws a sequence character on the display
void drawSequence(char c)
{
    Graphics_clearDisplay(&g_sContext);
    char charArray[2] = { c, '\0' }; // Crea un array di caratteri con il carattere e il terminatore di stringa
    Graphics_drawStringCentered(&g_sContext, (int8_t*) charArray,
    AUTO_STRING_LENGTH,
                                64, 30, OPAQUE_TEXT);
    _delay_cycles(50000000);
    Graphics_clearDisplay(&g_sContext);
}
// Draws an arrow based on the character input
void drawArrow(char c)
{
    /*int x = 64;
     int y = 62;
     int size = 20;*/
    Graphics_clearDisplay(&g_sContext);

    switch (c)
    {
    case 'U':

        drawDirectionUp();
        break;

    case 'D':

        drawDirectionDown();
        break;

    case 'R':

        drawDirectionRight();
        break;

    case 'L':

        drawDirectionLeft();

        break;
    }

    _delay_cycles(30000000);

}
// Generates a random direction
char generateRandomDirection()
{

    int direction = rand() % 4;

    switch (direction)
    {
    case 0:
        return 'U'; // up
    case 1:
        return 'D'; // down
    case 2:
        return 'R'; // right
    case 3:
        return 'L'; // left
    default:
        return 'C'; // Default to center in case of error
    }
}
// Initializes random number generator once
void randInit()
{
    static int srand_called = 0;
    if (!srand_called)
    {
        fflush(stdin);
        _delay_cycles(100000);
        srand(time(NULL));
        srand_called = 1;
    }
}
// Main game play function
bool playGame(int t, int correct)
{

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontCmss18b);

    if (correct == 0 && (t == 2 || t == 1))
    {
        char tryStr[15];
        sprintf(tryStr, "Attempt: %d/2", t);

        Graphics_drawStringCentered(&g_sContext, (int8_t*) tryStr,
        AUTO_STRING_LENGTH,
                                    64, 50,
                                    OPAQUE_TEXT);
        _delay_cycles(20000000);
    }

    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmtt26);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "MEMORIZE:",
    AUTO_STRING_LENGTH,
                                64, 60,
                                OPAQUE_TEXT);
    _delay_cycles(30000000); //~3 seconds
    Graphics_clearDisplay(&g_sContext);

    drawDirectionNone();
    // Generates a random sequence of 3 letters (U, D, R, L)
    _delay_cycles(30000000); //~3 seconds
    char sequence[3];
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        sequence[i] = generateRandomDirection();
        drawArrow(sequence[i]);
        _delay_cycles(3000000); //delay between the generation of directions
    }
    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmtt22);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "YOUR TURN:",
    AUTO_STRING_LENGTH,
                                64, 60, OPAQUE_TEXT);
    _delay_cycles(10000000);

    for (i = 0; i < 3; i++)
    {
        drawMove(i + 1);
        resultsBuffer[0] = ADC14_getResult(ADC_MEM3); //Joystick X
        resultsBuffer[1] = ADC14_getResult(ADC_MEM4); //Joystick Y
        char direzione = 'C';
        if (resultsBuffer[0] < 14500 && resultsBuffer[0] > 4000
                && resultsBuffer[1] > 15000)
        {
            direzione = 'U';
        }
        if (resultsBuffer[0] < 14500 && resultsBuffer[0] > 4000
                && resultsBuffer[1] < 1200)
        {
            direzione = 'D';
        }
        if (resultsBuffer[0] > 13500 && resultsBuffer[1] > 3500
                && resultsBuffer[1] < 13000)
        {
            direzione = 'R';
        }
        if (resultsBuffer[0] < 3000 && resultsBuffer[1] > 3500
                && resultsBuffer[1] < 13000)
        {
            direzione = 'L';
        }

        if (direzione != sequence[i])
        { //risposta errata
            Graphics_clearDisplay(&g_sContext);
            generateSoundWrongAnswer();
            drawWrong();
            _delay_cycles(10000000);
            return false;

        }
        else
        {
            generateSoundRightAttempt();
        }
        if (i == 2)
        { //risposta giusta
            generateSoundRightAnswer();
            drawCorrect();
            _delay_cycles(10000000);
            return true;
        }
    }
    return false;
}
// Manages the game state
bool GameManager()
{
    int counterCorrect = 0;
    int tentativiMax = ATTEMPT;
    int currentAttempt = 1;

    while (counterCorrect != ATTEMPT && tentativiMax != 0)
    {
        randInit();

        if (playGame(currentAttempt, counterCorrect))
        {
            counterCorrect++;
        }
        else
        {
            if (counterCorrect == 1)
            {
                counterCorrect--;
            }
            tentativiMax--;
            currentAttempt++;
        }
    }
    if (counterCorrect == ATTEMPT)
    {
        Graphics_clearDisplay(&g_sContext);
               GrContextFontSet(&g_sContext, &g_sFontCmtt26);
               Graphics_drawStringCentered(&g_sContext, (int8_t*) "COMPLETED",
               AUTO_STRING_LENGTH,
                                           64, 60,
                                           OPAQUE_TEXT);
               _delay_cycles(30000000); //circa 3 secondi
        Graphics_clearDisplay(&g_sContext);
        return true;
    }
    if (tentativiMax <= 0)
    {
        Graphics_clearDisplay(&g_sContext);
        GrContextFontSet(&g_sContext, &g_sFontCmtt26);
        Graphics_drawStringCentered(&g_sContext, (int8_t*) "FAILED",
        AUTO_STRING_LENGTH,
                                    64, 60,
                                    OPAQUE_TEXT);
        _delay_cycles(30000000); //~3 seconds
        Graphics_clearDisplay(&g_sContext);
        return false;
    }

    return false;
}
