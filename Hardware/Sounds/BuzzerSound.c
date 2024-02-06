#include "BuzzerSound.h"

void generateBeepFall()
{

    //set duty cycle
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4,
                            10000); // Duty Cycle 100%

    __delay_cycles(5000000); //sound duration

    //reset duty cycle to stop the sound
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4,
                            0);
}

void generateBeepSOS()
{

    uint32_t desiredFrequence = 300; //[Hz]
    uint32_t PWMperiod = SystemCoreClock / desiredFrequence; //Describe the type of frequency


    Timer_A_PWMConfig pwmConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK, // system clock
            TIMER_A_CLOCKSOURCE_DIVIDER_1, //nothing
            PWMperiod,
            TIMER_A_CAPTURECOMPARE_REGISTER_4, //Change state when reach the memorized variable
            TIMER_A_OUTPUTMODE_TOGGLE_RESET, //Toggle-Reset mode when triggered
            PWMperiod / 2 // Duty Cycle 50% -> up at 50%
    };

    // Initialize Timer A
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    __delay_cycles(6000000); //sound duration

    //stop sound
    Timer_A_stopTimer(TIMER_A0_BASE);
}

void generateSoundRightAnswer()
{
    uint32_t frequencies[] = { 262, 294, 330 }; //[Hz]
    int nTones = 3;
    int i;
    for (i = 0; i < nTones; i++)
    {
        uint32_t PWMperiod = SystemCoreClock
                / (TIMER_A_CLOCKSOURCE_DIVIDER_20 * frequencies[i]);
        Timer_A_PWMConfig pwmConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,
                TIMER_A_CLOCKSOURCE_DIVIDER_20,
                PWMperiod,
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                TIMER_A_OUTPUTMODE_TOGGLE_RESET,
                PWMperiod / 2 // Duty Cycle 50%
        };


        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

        __delay_cycles(2000000); //sound duration
    }

    //stop sound
    Timer_A_stopTimer(TIMER_A0_BASE);
}

void generateSoundRightAttempt()
{
    uint32_t frequencies[] = { 262, 330 };
    int nTones = 2;
    int i;
    for (i = 0; i < nTones; i++)
    {
        uint32_t PWMperiod = SystemCoreClock
                / (TIMER_A_CLOCKSOURCE_DIVIDER_20 * frequencies[i]);
        Timer_A_PWMConfig pwmConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,
                TIMER_A_CLOCKSOURCE_DIVIDER_20,
                PWMperiod,
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                TIMER_A_OUTPUTMODE_TOGGLE_RESET,
                PWMperiod / 2 // Duty Cycle 50%
        };

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

        __delay_cycles(2000000); //sound duration
    }

    //stop sound
    Timer_A_stopTimer(TIMER_A0_BASE);
}

void generateSoundWrongAnswer()
{
    uint32_t frequencies[] = { 120, 96, 10 };
    int nTones = 3;
    int i;

    for (i = 0; i < nTones; i++)
    {
        uint32_t PWMperiod = SystemCoreClock
                / (TIMER_A_CLOCKSOURCE_DIVIDER_20 * frequencies[i]);
        Timer_A_PWMConfig pwmConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,
                TIMER_A_CLOCKSOURCE_DIVIDER_20,
                PWMperiod,
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                TIMER_A_OUTPUTMODE_TOGGLE_RESET,
                PWMperiod / 2 // Duty Cycle 50%
        };

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

        // Sound for 0.2 seconds
        __delay_cycles(600000);
        if (i == 2)
        {
            __delay_cycles(5000000);
        } //last tone has double duration

        //0.1 second pause
        Timer_A_stopTimer(TIMER_A0_BASE);
        __delay_cycles(1000000);
    }

    //stop sound
    Timer_A_stopTimer(TIMER_A0_BASE);
}

void SoundDialer()
{
    uint32_t frequencies[] = { 43, 48, 48, 48, 58, 83, 83, 83, 83, 98 };

    int nTones = 10;
    int i;
    for (i = 0; i < nTones; i++)
    {
        uint32_t periodoPWM = SystemCoreClock
                / (TIMER_A_CLOCKSOURCE_DIVIDER_20 * frequencies[i]);
        Timer_A_PWMConfig pwmConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,
                TIMER_A_CLOCKSOURCE_DIVIDER_20,
                periodoPWM,
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                TIMER_A_OUTPUTMODE_TOGGLE_RESET,
                periodoPWM / 2 // Duty Cycle 50%
        };

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

        __delay_cycles(1500000);

        Timer_A_stopTimer(TIMER_A0_BASE);
        __delay_cycles(2000000);
    }




}
