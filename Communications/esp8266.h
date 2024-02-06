#ifndef _ESP8266_H_
#define _ESP8266_H_

#include <string.h>
#include <stdlib.h>
#include "delay.h"
#include "uartController.h"

#define AT              "AT"
#define AT_RST          "AT+RST"
#define AT_RESTORE      "AT+RESTORE"
#define AT_GMR          "AT+GMR"
#define AT_GSLP         "AT+GSLP"
#define ATE             "ATE"
#define AT_CWMODE       "AT+CWMODE"
#define AT_CWJAP        "AT+CWJAP"
#define AT_CWLAP        "AT+CWLAP"
#define AT_CWQAP        "AT+CWQAP"
#define AT_CWLIF        "AT+CWLIF"
#define AT_CWDHCP       "AT+CWDHCP"
#define AT_CIPSTAMAC    "AT+CIPSTAMAC"
#define AT_CIPAPMAC     "AT+CIPAPMAC"
#define AT_CIPSTA       "AT+CIPSTA"
#define AT_CIPAP        "AT+CIPAP"
#define AT_CIPSTATUS    "AT+CIPSTATUS"
#define AT_CIPSTART     "AT+CIPSTART"
#define AT_CIPSEND      "AT+CIPSEND"
#define AT_CIPCLOSE     "AT+CIPCLOSE"
#define AT_CIFSR        "AT+CIFSR"
#define AT_CIPMUX       "AT+CIPMUX"
#define AT_CIPSERVER    "AT+CIPSTO"
#define AT_CIPMODE      "AT+CIPMODE"
#define AT_CIPSTO       "AT+CIPSTO"
#define AT_CIUPDATE     "AT+CIUPDATE"

#define ESP8266_WIFI_MODE_CLIENT    '1'
#define ESP8266_WIFI_MODE_HOST      '2'
#define ESP8266_WIFI_MODE_DUAL      '3'

#define ESP8266_BUFFER_SIZE     2048
#define ESP8266_RECEIVE_TRIES   10

#define ESP8266_TCP             0
#define ESP8266_UDP             1

bool ESP8266_factoryReset(UART *uart);

bool ESP8266_checkUartCommunication(UART *uart);

bool ESP8266_setWifiMode(UART *uart, char wifiMode);

bool ESP8266_availableAPs(UART *uart);

bool ESP8266_connectToAP(UART *uart, char *ssid, char *password);

bool ESP8266_disconnectFromAP(UART *uart);

uint32_t ESP8266_getIPAddress(UART *uart, char *buffer, int bufferSize);

bool ESP8266_setSingleConnectionMode(UART *uart);

bool ESP8266_setMultipleConnectionMode(UART *uart);

bool ESP8266_establishSingleConnection(UART *uart, uint8_t type, char *address, int port);

bool ESP8266_establishConnection(UART *uart, char ID, uint8_t type, char *address, int port);

bool ESP8266_closeConnection(UART *uart);

bool ESP8266_sendDataSingleConnection(UART *uart, char *data, uint32_t dataSize);

bool ESP8266_sendData(UART *uart, char id, char *data, uint32_t dataSize);


#endif /* DEVICES_ESP8266_H_ */
