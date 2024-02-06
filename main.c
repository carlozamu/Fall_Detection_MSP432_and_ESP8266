#include "Hardware/HwInit.h"
#include "Game/game.h"


volatile bool fallDetected = false;
volatile bool buttonOnePressed = false;
volatile bool buttonTwoPressed = false;
volatile bool gameCompleted = false;



void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;    // stop watchdog timer

    _hwInit();

    int nBeep = 0;
    while (1)
    {
        PCM_gotoLPM0();
        //stay in low power mode until Accelerometer interrupt --> if fallDetected than enter if
        if(fallDetected){
            while(nBeep < 10){
                  alarm();
                  nBeep++;
                  if(buttonOnePressed){
                      gameCompleted = GameManager();
                      if(gameCompleted==false){
                          GenerateCallSOS();
                          //reset for next use;
                          buttonOnePressed=false;
                          fallDetected=false;
                      }else{
                          //reset for next use;
                          gameCompleted=false;
                          fallDetected=false;
                          buttonOnePressed=false;
                          _graphicsInit();
                          break;
                      }
                  }
                  if(buttonTwoPressed){
                      GenerateCallSOS();
                      //reset for next use;
                      buttonTwoPressed=false;
                      fallDetected=false;
                      break;
                  }
            }
            if(nBeep==10){
                GenerateCallSOS();
                //reset for next use;
                nBeep=0;
            }
        }
    }
}



// This interrupt is fired whenever a conversion is completed
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    fallDetected=fallDetection();


}

// These interrupts handles BUTTON_S1 and BUTTON_S2
void PORT5_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(BUTTON_S1_PORT);
    GPIO_clearInterruptFlag(BUTTON_S1_PORT, status);

    /* check if we received P3.5 interrupt */
    if ((status & BUTTON_S1_PIN))
    {
            buttonOnePressed=true;

    }
}

void PORT3_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(BUTTON_S2_PORT);
    GPIO_clearInterruptFlag(BUTTON_S2_PORT, status);
    if ((status & BUTTON_S2_PIN))
    {
           buttonTwoPressed=true;

    }
}
