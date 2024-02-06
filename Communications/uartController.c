#include "uartController.h"
#include <stdarg.h>

// use these references in interrupt handler
UART *eusciA0BaseInstance = NULL;
UART *eusciA2BaseInstance = NULL;


bool isBufferEmpty(UART *uart) {
    return uart->readIndex == uart->writeIndex;
}

bool isBufferFull(UART *uart) {
    return uart->writeIndex == (uart->writeIndex + 1) % UART_BUFFER_SIZE;
}

void incrementReadIndex(UART *uart) {
    MAP_Interrupt_disableMaster();
    uart->readIndex++;
    MAP_Interrupt_enableMaster();
}

void incrementWriteIndex(UART *uart) {
    uart->writeIndex++;
}

void insertCharInBuffer(UART *uart, uint8_t c) {
    if (isBufferFull(uart)) {
        /*TODO: Buffer Overflow, add handler here*/
    } else {
        uart->buffer[uart->writeIndex] = c;
        incrementWriteIndex(uart);
    }
}

void UART_init(UART *uart) {
    switch (uart->uart) {
        case EUSCI_A0_BASE:
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3,
                                                           GPIO_PRIMARY_MODULE_FUNCTION);
            MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
            eusciA0BaseInstance = uart;
            break;
        case EUSCI_A2_BASE:
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3,
                                                           GPIO_PRIMARY_MODULE_FUNCTION);
            MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
            eusciA2BaseInstance = uart;
            break;
        default:
            break;
    }

    MAP_UART_initModule(uart->uart, &uart->uartConfig);
    MAP_UART_enableModule(uart->uart);
    MAP_UART_enableInterrupt(uart->uart, EUSCI_A_UART_RECEIVE_INTERRUPT);
}

void UART_write(UART *uart, uint8_t *data, uint32_t size) {
    uint32_t i;
    for (i = 0; i < size; i++) {
        MAP_UART_transmitData(uart->uart, data[i]);
    }
}

uint32_t UART_read(UART *uart, uint8_t *data, uint32_t size) {
    uint32_t i;
    int8_t c;

    for (i = 0; i < size; i++) {
        if (isBufferEmpty(uart)) {
            return i;
        }

        c = uart->buffer[uart->readIndex];
        incrementReadIndex(uart);
        data[i] = c;

    }

    return i;
}


void UART_printChar(UART *uart, char c) {
    /*Send the char through the selected UART*/
    UART_write(uart, (uint8_t *) &c, 1);
}

void UART_printString(UART *uart, char *string) {
    /*while the string is not the null character*/
    while (*string) {
        UART_printChar(uart, *string);
        string++;
    }
}

void UART_printInteger(UART *uart, int integer) {
    if (integer == 0) {
        UART_printChar(uart, '0');
    }

    if (integer < 0) {
        UART_printChar(uart, '-');
    }

    char b[10];
    int digit = integer;

    uint8_t i = 0;
    while (digit) {
        b[i++] = digit % 10;
        digit /= 10;
    }

    while (i) {
        UART_printChar(uart, '0' + b[i - 1]);
        i--;
    }
}

/*A basic printf for UART.
 * The following formats are supported:
 * %c = for char variables
 * %s = for string variables
 * %i = for unsigned integers
 * UART_printf(UARTObj, "Formatted string %c, %s, %i", character, string, integer)
 *
 */
void UART_printf(UART *uart, const char *fs, ...) {
    va_list valist;
    va_start(valist, fs);
    int i;
    char *s;

    while (*fs) {
        if (*fs != '%') {
            UART_write(uart, (uint8_t *) fs, 1);
            fs++;
        } else {
            switch (*++fs) {
                case 'c':
                    i = va_arg(valist, int);
                    UART_printChar(uart, (char) i);
                    break;
                case 's':
                    s = va_arg(valist, char*);
                    UART_printString(uart, s);
                    break;
                case 'i':
                    i = va_arg(valist, int);
                    UART_printInteger(uart, i);
                    break;
                case 'd':
                    i = va_arg(valist, int);
                    UART_printInteger(uart, i);
                    break;
            }

            ++fs;
        }
    }
}

int UART_gets(UART *uart, char *b, int size) {
    char c;
    uint32_t i = 0;

    while (1) {
        if (UART_read(uart, (uint8_t *) &c, 1) != 0) {
            /*put a '\n' and '\r' if it fits on the buffer*/
            if (c == '\n' || c == '\r') {
                if (i + 3 > size) {
                    return size + 1;
                }

                b[i++] = '\r';
                b[i++] = '\n';
                b[i++] = 0;

                return i;
            }
                /*erase data from buffer if backspace is received*/
            else if (c == 127 || c == 8) {
                i--;
                b[i] = 0;
            }
                /*store character on the buffer*/
            else {
                if (i < size) {
                    b[i++] = c;
                } else {
                    return size + 1;
                }
            }
        }
    }
}

uint32_t UART_available(UART *uart) {
    return uart->writeIndex - uart->readIndex;
}

void UART_flush(UART *uart) {
    uart->readIndex = 0;
    uart->writeIndex = 0;
}

void EUSCIA0_IRQHandler(void) {
    if (eusciA0BaseInstance == NULL) {
        return;
    }
    uint8_t c;
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);


    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) {
        c = MAP_UART_receiveData(EUSCI_A0_BASE);
        insertCharInBuffer(eusciA0BaseInstance, c);
    }
}

void EUSCIA2_IRQHandler(void) {
    if (eusciA2BaseInstance == NULL) {
        return;
    }
    uint8_t c;
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) {
        c = MAP_UART_receiveData(EUSCI_A2_BASE);
        insertCharInBuffer(eusciA2BaseInstance, c);
    }
}
