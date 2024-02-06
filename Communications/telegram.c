#include "telegram.h"
#include "uartController.h"
#include "esp8266.h"
#include <ti/devices/msp432p4xx/inc/msp.h>

// Setup  Telegram
#define TELEGRAM_BOT_TOKEN "6502989312:AAGDp6X1e2lqmhdSYSkQueKt5Kh23k2IBnI"
#define CHAT_ID "https://t.me/emergencymsp_bot"
#define MESSAGE "I Need Help!"
//------------------------------------------------------------------

bool wifiConnectToAP(UART *wifi)
{
    UART_flush(wifi);
    delay(1);
    if (!ESP8266_checkUartCommunication(wifi))
    {
        UART_printString(&pc, "No serial connection to wifi board\r\n");
        printf("No serial connection to wifi board");
        return false;
    }

    if (!ESP8266_factoryReset(wifi))
    {
        UART_printString(&pc, "Error factory reset\r\n");
        printf("Error factory reset");
        return false;
    }
    UART_flush(wifi);
    delay(1);

    // set client wifi mode
    if (!ESP8266_setWifiMode(wifi, ESP8266_WIFI_MODE_CLIENT))
    {
        UART_printString(&pc, "Error setting wifi mode\r\n");
        printf("Error setting wifi mode");
        return false;
    }

    // connect to AP
    if (!ESP8266_connectToAP(wifi, NETWORK_WIFI_SSID, NETWORK_WIFI_PASSWORD))
    {
        UART_printString(&pc, "Error connecting to wifi\r\n");
        printf("Error connecting to wifi");
        return false;
    }

    return true;

}

void sendTelegramMessage(UART *wifi)
{

    //AT COMMAND LIST:
    //AT
    //AT+CWMODE=1
    //AT+CWJAP="SSID","PASSWORD"
    //AT+CIPSTART="UDP","UDP_IP",UDP_PORT
    //AT+CIPSEND=DIM
    //SEND HTTP REQUEST

    if (wifiConnectToAP(wifi)) //connect to wifi
    {
        printf("Connected to WiFi");

        char httpRequest[512];
        char content[256];
        char cmdCIPSEND[64];
        char cmdCIPSTART[64];

        const char *chat_id = "CHAT_ID";

        // Formattazione del corpo della richiesta POST
        snprintf(content, sizeof(content), "chat_id=%s&text=%s", chat_id,
        MESSAGE);

        // Preparazione dell'header HTTP POST
        snprintf(httpRequest, sizeof(httpRequest),
                 "POST /bot%s/sendMessage HTTP/1.1\r\n"
                 "Host: %s\r\n"
                 "Content-Type: application/x-www-form-urlencoded\r\n"
                 "Content-Length: %d\r\n\r\n"
                 "%s\r\n",
                 TELEGRAM_BOT_TOKEN, chat_id, strlen(content), content);

        snprintf(cmdCIPSTART, sizeof(cmdCIPSTART),
                 "%s=\"UPD\", \"%s\" , %d\r\n", AT_CIPSTART,
                 NETWORK_UDP_SERVER_IP,
                 NETWORK_UDP_SERVER_PORT);

        snprintf(cmdCIPSEND, sizeof(cmdCIPSEND), "%s=%d\r\n", AT_CIPSEND,
                 strlen(httpRequest));

        if (ESP8266_checkUartCommunication(wifi)) //re-check
        {
            UART_printString(&esp8266Uart, cmdCIPSTART); // Connect to telegram server
            UART_printString(&esp8266Uart, cmdCIPSEND);  // Data dimension
            UART_printString(&esp8266Uart, httpRequest); // send POST request

        }

    }

}

