#include "HwInit.h"


//-------------------------------AUDIO-------------------------------
/* Timer_A Compare Configuration Parameter  (PWM) */
Timer_A_CompareModeConfig compareConfig_PWM = {
TIMER_A_CAPTURECOMPARE_REGISTER_4, // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE, // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET, // Toggle output but
        10000 // Duty Cycle initially
        };

/* Timer_A Up Configuration Parameter */

const Timer_A_UpModeConfig upConfig = {
TIMER_A_CLOCKSOURCE_SMCLK, // Change clock source if necessary
        TIMER_A_CLOCKSOURCE_DIVIDER_1, // Modify clock divider to increase frequency  TIMER_A_CLOCKSOURCE_DIVIDER_1 standard
        20000, //Modify timer period to obtain desired frequency
        TIMER_A_TAIE_INTERRUPT_DISABLE, //Disable timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE, //Disable timer interrupt based on CCR0
        TIMER_A_DO_CLEAR //clear timer
 };

void _buzzerInit()
{
    /* Configures P2.7 to PM_TA0.4 for using Timer PWM to control the buzzer */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7,
    GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A0 for Up Mode and starting */
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Initialize compare registers to generate PWM */
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM); // For P2.7
    // Azzera il duty cycle per fermare il suono
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4,
                            0);
}

//--------------------------------------------------------------


void _graphicsInit()
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_clearDisplay(&g_sContext);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontCmss18b);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "FALL",
    AUTO_STRING_LENGTH,
                                64, 40,
                                OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "DETECTOR",
    AUTO_STRING_LENGTH,
                                64, 60,
                                OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t*) "SYSTEM",
    AUTO_STRING_LENGTH,
                                64, 80,
                                OPAQUE_TEXT);


}
void _configureButtons()
{
    // Configure buttons S1 and S2
    GPIO_setAsInputPinWithPullUpResistor(BUTTON_S1_PORT, BUTTON_S1_PIN);
    GPIO_enableInterrupt(BUTTON_S1_PORT, BUTTON_S1_PIN);

    GPIO_setAsInputPinWithPullUpResistor(BUTTON_S2_PORT, BUTTON_S2_PIN);
    GPIO_enableInterrupt(BUTTON_S2_PORT, BUTTON_S2_PIN);

    // Configure interrupts for the buttons
    Interrupt_enableInterrupt(INT_PORT5);
    Interrupt_enableInterrupt(INT_PORT3);

    //Set default status as not pressed
    GPIO_setOutputHighOnPin(BUTTON_S1_PORT, BUTTON_S1_PIN);
    GPIO_setOutputHighOnPin(BUTTON_S2_PORT, BUTTON_S2_PIN);
}

void _ledInit()
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void _accelSensorInit()
{
    // Pin 4.0, 4.2, 6.1 as ADC input
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
    GPIO_PIN0 | GPIO_PIN2,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
    GPIO_PIN1,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

void _joystickInit()
{
    // Pin 6.0, 4.4 as ADC input
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
    GPIO_PIN0,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
    GPIO_PIN4,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

void _ADC_enable()
{
    // Enabling the interrupt when a conversion is complete
    ADC14_enableInterrupt(ADC_INT4);

    // Enabling Interrupts
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();
}

void _initUART()
{
    eUSCI_UART_ConfigV1 UART115200Config =
           {
                   EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                   13,
                   0,
                   37,
                   EUSCI_A_UART_NO_PARITY,
                   EUSCI_A_UART_LSB_FIRST,
                   EUSCI_A_UART_ONE_STOP_BIT,
                   EUSCI_A_UART_MODE,
                   EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
           };

    eUSCI_UART_ConfigV1 UART9600Config =
           {
                   EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                   156,
                   4,
                   0,
                   EUSCI_A_UART_NO_PARITY,
                   EUSCI_A_UART_LSB_FIRST,
                   EUSCI_A_UART_ONE_STOP_BIT,
                   EUSCI_A_UART_MODE,
                   EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
           };


    // Init delay functionality
    delay_init();

    // Esp8266 uart communication
    esp8266Uart.uart = EUSCI_A2_BASE;
    esp8266Uart.uartConfig = UART115200Config;
    UART_init(&esp8266Uart);

    // USB communication
    pc.uart = EUSCI_A0_BASE;
    pc.uartConfig = UART9600Config;
    UART_init(&pc);


}
void _ADC_init()
{
    _accelSensorInit();
    _joystickInit();

    // Initializing ADC (ADCOSC/64/8)
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8,
                     0);

    // Configuring ADC Memory (ADC_MEM0 - ADC_MEM4 with no repeat)
    // with internal 2.5v reference
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM4, true);

    // Accelerometer X - MEM0 - A14
    ADC14_configureConversionMemory(ADC_MEM0,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

    // Accelerometer Y - MEM1 - A13
    ADC14_configureConversionMemory(ADC_MEM1,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

    // Accelerometer Z - MEM2 - A11
    ADC14_configureConversionMemory(ADC_MEM2,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);

    // Joystick X - MEM3 - A15
    ADC14_configureConversionMemory(ADC_MEM3,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

    // Joystick Y - MEM4 - A9
    ADC14_configureConversionMemory(ADC_MEM4,
    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

    // Setting up the sample timer to automatically step through the sequence
    // convert
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    // Triggering the start of the sample
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void _hwInit()
{
    // Halting WDT and disabling master interrupts
    WDT_A_holdTimer();
    Interrupt_disableMaster();

    // Set the core voltage level to VCORE1
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    // Set 2 flash wait states for Flash bank 0 and 1
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Initializes Clock System
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); //48 MHz
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);


    _graphicsInit();
    _buzzerInit();
    _configureButtons();
    _ledInit();
    _ADC_init();
    _ADC_enable();
    _initUART();



}
