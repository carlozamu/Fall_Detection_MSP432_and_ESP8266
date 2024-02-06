#include "delay.h"

#ifdef DELAY_WITH_TIMER
// use to actively check if delay time is gone
volatile uint32_t wakeUp;

const Timer_A_ContinuousModeConfig continuousModeConfig =
        {
                TIMER_A_CLOCKSOURCE_ACLK,           // ACLK Clock Source
                TIMER_A_CLOCKSOURCE_DIVIDER_1,      // ACLK/1 = 32.768khz
                TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
                TIMER_A_DO_CLEAR                    // Clear Counter
        };
#endif

void delay_init(void) {
#ifdef DELAY_WITH_TIMER

    // Setting ACLK to REFO at 128Khz for LF mode
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_ACLK,
                           CS_REFOCLK_SELECT,
                           CS_CLOCK_DIVIDER_1);

    // Configuring Continuous Mode
    Timer_A_configureContinuousMode(TIMER_A0_BASE, &continuousModeConfig);

    MAP_Interrupt_enableMaster();
#endif
}

void delay_1sec() {
#ifndef DELAY_WITH_TIMER
    for (int32_t i = 0; i < 700000; i++) {

    }
#endif

#ifdef DELAY_WITH_TIMER
    wakeUp = DELAY_RUNNING;
    Interrupt_enableInterrupt(INT_TA0_N);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);

    while (wakeUp == DELAY_RUNNING) {}
#endif
}

void delay(uint32_t sec) {
    int i;
    for ( i = 0; i < sec; i++) {
        delay_1sec();
    }
}

#ifdef DELAY_WITH_TIMER
void TA0_N_IRQHandler(void) {
    wakeUp = DELAY_GONE;
    Timer_A_clearInterruptFlag(TIMER_A0_BASE);
    Timer_A_stopTimer(TIMER_A0_BASE);
}
#endif
