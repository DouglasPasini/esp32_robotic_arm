#ifndef WS_H
#define WS_H

#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include "defs.h"
#include "drive.h"

using namespace websockets;
extern WebsocketsClient webSocket;

void wsInit();
void wsConnect();
void onEventsCallback(WebsocketsEvent event, String data);
void onMessageCallback(WebsocketsMessage message);
void webSocketRun();

#endif
