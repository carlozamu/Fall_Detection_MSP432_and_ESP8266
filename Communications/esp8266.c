#include "esp8266.h"

bool ESP8266_waitForAnswer(UART *uart) {
    uint32_t c;
    uint32_t i = 0;

    uint32_t tries = ESP8266_RECEIVE_TRIES;

    while (tries) {
        if (UART_available(uart)) {
            while (UART_available(uart)) {
                UART_read(uart, (uint8_t *) &c, 1);

                if (i > ESP8266_BUFFER_SIZE) {
                    return false;
                } else {
                    uart->buffer[i++] = (char) c;
                }
            }

            uart->buffer[i] = 0;
            return true;
        }
        tries--;
        delay(1);
    }

    return false;
}

bool ESP8266_checkUartCommunication(UART *uart) {
    UART_printf(uart, "%s\r\n", AT);

    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_factoryReset(UART *uart) {
    UART_printf(uart, "%s\r\n", AT_RESTORE);

    delay(3);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_setWifiMode(UART *uart, char wifiMode) {
    UART_printf(uart, "%s=%c\r\n", AT_CWMODE, wifiMode);

    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_availableAPs(UART *uart) {
    UART_printf(uart, "%s\r\n", AT_CWLAP);
    delay(10);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_connectToAP(UART *uart, char *SSID, char *Password) {
    UART_printf(uart, "%s=\"%s\",\"%s\"\r\n", AT_CWJAP, SSID, Password);

    delay(15);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_disconnectFromAP(UART *uart) {
    UART_printf(uart, "%s\r\n", AT_CWQAP);

    delay(5);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_setSingleConnectionMode(UART *uart) {
    UART_printf(uart, "%s=%c\r\n", AT_CIPMUX, '0');

    delay(1);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_setMultipleConnectionMode(UART *uart) {
    UART_printf(uart, "%s=%c\r\n", AT_CIPMUX, '1');

    delay(1);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_establishSingleConnection(UART *uart, uint8_t type, char *address, int port) {
    return ESP8266_establishConnection(uart, '\0', type, address, port);
}

bool ESP8266_establishConnection(UART *uart, char id, uint8_t type, char *address, int port) {
    if (id == '\0') {
        //no id, is a single connection mode
        UART_printf(uart, "%s=\"%s\",\"%s\",%d\r\n", AT_CIPSTART, type == ESP8266_TCP ? "TCP":"UDP", address, port);
    } else {
        UART_printf(uart, "%s=%c,\"%s\",\"%s\",%d\r\n", AT_CIPSTART, id, type == ESP8266_TCP ? "TCP":"UDP", address, port);
    }


    delay(1);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_sendDataSingleConnection(UART *uart, char *data, uint32_t dataSize) {
    return ESP8266_sendData(uart, '\0', data, dataSize);
}

bool ESP8266_sendData(UART *uart, char id, char *data, uint32_t dataSize) {
    char size[5];

    sprintf(size, "%lu", dataSize);

    if (id == '\0') {
        UART_printf(uart, "%s=%s\r\n", AT_CIPSEND, size);
    } else {
        UART_printf(uart, "%s=%c,%s\r\n", AT_CIPSEND, id, size);
    }

    delay(1);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, ">") == NULL) {
        return false;
    }

    // wait the > char, esp is waiting data to send
    UART_printf(uart, data);

    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

bool ESP8266_closeConnection(UART *uart) {
    UART_printf(uart, "%s\r\n", AT_CIPCLOSE);

    delay(1);
    if (!ESP8266_waitForAnswer(uart)) {
        return false;
    }

    if (strstr((char *) uart->buffer, "OK") == NULL) {
        return false;
    }

    return true;
}

uint32_t ESP8266_getIPAddress(UART *uart, char *buffer, int bufferSize) {
    //TODO implement
    return 0;
}
