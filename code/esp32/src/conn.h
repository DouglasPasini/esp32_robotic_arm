#ifndef CONN_H
#define CONN_H

#include <Arduino.h>
#include <WiFi.h>

// Nome e senha da rede Wi-Fi

#define SSID "Douglas"
#define PASSWORD "ba101222"

void connInit();
uint8_t connect();
void WiFiEvent(WiFiEvent_t event);
extern TimerHandle_t wifiReconnectTimer;

#endif
