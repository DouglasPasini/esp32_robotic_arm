#include <Arduino.h>
#include "src/defs.h"
#include "src/conn.h"
#include "src/ws.h"
#include "src/drive.h"
#include "src/sensors.h"

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
