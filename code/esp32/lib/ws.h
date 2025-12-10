#ifndef WS_H
#define WS_H

#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include "defs.h"
#include "drive.h"

using namespace websockets;
extern WebsocketsClient webSocket;

// --- Inicialização e conexão do WebSocket ---

void wsInit();
void wsConnect();

// --- Tratamento de mensagens ---

void onEventsCallback(WebsocketsEvent event, String data);
void onMessageCallback(WebsocketsMessage message);

// --- Envio de mensagens ---

void sendSensor(const char *id, int state); // função que envia estado do sensor

// --- Loop ---

void webSocketRun();

#endif
