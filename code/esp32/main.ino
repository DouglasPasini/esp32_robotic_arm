#include <Arduino.h>
#include "lib/defs.h"
#include "lib/conn.h"
#include "lib/ws.h"
#include "lib/drive.h"
#include "lib/sensors.h"

void setup() {
  // Inicialização da serial
  Serial.begin(115200);

  // Inicialização dos sensores
  sensorInit();

  // Inicialização e conexão do wi-fi
  connInit();
  connect();

  // Inicialização e conexão do websocket
  wsInit();
  wsConnect();

  // Inicialização dos motores
  motorInit();
}

void loop() {
  webSocketRun();
}
