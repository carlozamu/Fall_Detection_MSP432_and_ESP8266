#ifndef _UART_CONTROLLER_H_
#define _UART_CONTROLLER_H_

#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/rom.h>
#include <ti/devices/msp432p4xx/driverlib/rom_map.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <ti/devices/msp432p4xx/driverlib/uart.h>
#include <ti/devices/msp432p4xx/driverlib/gpio.h>

#define UART_BUFFER_SIZE 2048

typedef struct UART {
    uint32_t uart;
    eUSCI_UART_ConfigV1 uartConfig;
    volatile uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint32_t readIndex;
    volatile uint32_t writeIndex;
} UART;

UART esp8266Uart;
UART pc;

void UART_init(UART *uart);

void UART_write(UART *uart, uint8_t *data, uint32_t size);

uint32_t UART_read(UART *uart, uint8_t *data, uint32_t size);

void UART_printChar(UART *uart, char c);

void UART_printString(UART *uart, char *string);

void UART_printInteger(UART *uart, int integer);

void UART_printf(UART *uart, const char *fs, ...);

int UART_gets(UART *uart, char *b, int size);

uint32_t UART_available(UART *uart);

void UART_flush(UART *uart);

#endif /* _UART_CONTROLLER_H_ */
