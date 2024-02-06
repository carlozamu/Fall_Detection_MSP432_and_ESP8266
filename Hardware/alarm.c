#include "alarm.h"


void flashLights()
{
    // Toggle P1.0 P2.0 output
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);

}
void flashRedScreen()
{

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    GrContextFontSet(&g_sContext, &g_sFontCmtt26);
    Graphics_clearDisplay(&g_sContext);

    Graphics_drawStringCentered(&g_sContext, (int8_t*) "FALL!",
    AUTO_STRING_LENGTH,
                                64, 20,
                                OPAQUE_TEXT);
    GrContextFontSet(&g_sContext, &g_sFontCmss14b);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "Press 1 if SAFE",
    AUTO_STRING_LENGTH,
                                64, 50,
                                OPAQUE_TEXT);


    Graphics_drawStringCentered(&g_sContext, (int8_t*) "Press 2 for SOS",
    AUTO_STRING_LENGTH,
                                64, 75,
                                OPAQUE_TEXT);
    flashLights();
    __delay_cycles(3000000);

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontCmtt26);
    Graphics_clearDisplay(&g_sContext);

    Graphics_drawStringCentered(&g_sContext, (int8_t*) "FALL!",
    AUTO_STRING_LENGTH,
                                64, 20,
                                OPAQUE_TEXT);
    GrContextFontSet(&g_sContext, &g_sFontCmss14b);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "Press 1 if SAFE",
    AUTO_STRING_LENGTH,
                                64, 50,
                                OPAQUE_TEXT);


    Graphics_drawStringCentered(&g_sContext, (int8_t*) "Press 2 for SOS",
    AUTO_STRING_LENGTH,
                                64, 75,
                                OPAQUE_TEXT);

    flashLights();
    __delay_cycles(3000000);
}

void alarm()
{

    _buzzerInit();

    //Generate sound
   generateBeepFall();

    flashRedScreen();


}
void GenerateCallSOS()
{
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmtt26);

    Graphics_drawStringCentered(&g_sContext, (int8_t*) "SOS!",
    AUTO_STRING_LENGTH,
                                64, 55,
                                OPAQUE_TEXT);
    int i;
    for (i = 0; i < 8; i++)
    {
        generateBeepSOS();
        _delay_cycles(4000000);
    }
    _delay_cycles(3000000);

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss18b);

    Graphics_drawStringCentered(&g_sContext, (int8_t*) "Sending SOS",
    AUTO_STRING_LENGTH,
                                64, 45, OPAQUE_TEXT);

    Graphics_drawStringCentered(&g_sContext, (int8_t*) "message...",
    AUTO_STRING_LENGTH,
                                64, 65, OPAQUE_TEXT);

    SoundDialer();
    sendTelegramMessage(&esp8266Uart);

}
