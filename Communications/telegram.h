#ifndef _TELEGRAM_H_
#define _TELEGRAM_H_
#include <stdbool.h>
#include "uartController.h"
#include "esp8266.h"


#define NETWORK_WIFI_SSID "Vodafone-Chill"
#define NETWORK_WIFI_PASSWORD "veramentechill"
#define NETWORK_UDP_SERVER_IP "192.168.1.100"
#define NETWORK_UDP_SERVER_PORT 7000
bool wifiConnectToAP(UART *wifi);
bool wifiSendData(UART *wifi);
void sendTelegramMessage(UART *wifi);

#endif
