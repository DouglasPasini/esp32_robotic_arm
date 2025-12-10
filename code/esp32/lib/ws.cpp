#include "HardwareSerial.h"
#include "ws.h"

// Cliente websocket
WebsocketsClient webSocket;

// --- Inicialização ---

void wsInit() {
  webSocket.onMessage(onMessageCallback);
  webSocket.onEvent(onEventsCallback);
}

void wsConnect() {
  if (webSocket.connect(websockets_server)) {
    Serial.println("[WS] Conectado ao servidor");
    webSocket.send("{\"type\": \"client\",\"who\": \"esp\"}");  // Envia uma mensagem dizendo quem é
    webSocket.ping();                                           // Envia um ping
  } else {
    Serial.println("[WS] Erro ao conectar");
  }
}

// --- EVentos Websocket ---

void onEventsCallback(WebsocketsEvent event, String data) {
  switch (event) {
    case WebsocketsEvent::ConnectionOpened:
      Serial.println("[WS] Conexão aberta");
      break;

    case WebsocketsEvent::ConnectionClosed:
      Serial.println("[WS] Conexão fechada");
      break;

    case WebsocketsEvent::GotPing:
      Serial.println("[WS] Ping recebido");
      break;

    case WebsocketsEvent::GotPong:
      Serial.println("[WS] Pong recebido");
      break;
  }
}

// --- Roteamento de Comandos ---

void handleGripper(JsonObject obj) {
  int angle = obj["angle"];
  gripperOpening(angle);
}

void handleJoint56(JsonObject obj) {
  const char* move = obj["move"];
  int value = obj["step"];

  if (strcmp(move, "rotate") == 0) {
    joint56Rotate(value*80);
  } else if (strcmp(move, "tilt") == 0) {
    joint56Tilt(value*20);
  }
}

void handleJoint4(JsonObject obj) {
  const char* move = obj["move"];
  int value = obj["step"];

  if (strcmp(move, "rotate") == 0) {
    joint4Rotate(value*50);
  }
}

void handleJoint3(JsonObject obj) {
  const char* move = obj["move"];
  int value = obj["step"];

  if (strcmp(move, "tilt") == 0) {
    joint3Tilt(value*1500);
  }
}

void handleJoint2(JsonObject obj) {
  const char* move = obj["move"];
  int value = obj["step"];

  if (strcmp(move, "tilt") == 0) {
    joint2Tilt(value*1500);
  }
}

void handleBase(JsonObject obj) {
  const char* move = obj["move"];
  int value = obj["step"];

  if (strcmp(move, "rotate") == 0) {
    baseRotate(value * 50);
  }
}

// --- Callback de mensagens ---

void onMessageCallback(WebsocketsMessage message) {

  Serial.print("[WS] Mensagem: ");
  Serial.println(message.data());

  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, message.data());
  if (error) {
    Serial.println("[WS] Erro JSON");
    return;
  }

  const char* type = doc["type"];
  JsonObject obj = doc.as<JsonObject>();

  if (strcmp(type, "joint56") == 0) handleJoint56(obj);
  else if (strcmp(type, "joint4") == 0) handleJoint4(obj);
  else if (strcmp(type, "joint3") == 0) handleJoint3(obj);
  else if (strcmp(type, "joint2") == 0) handleJoint2(obj);
  else if (strcmp(type, "base") == 0) handleBase(obj);
  else if (strcmp(type, "gripper") == 0) handleGripper(obj);
}

void sendSensor(const char *id, int state) { // função que envia estado do sensor
    StaticJsonDocument<128> doc;
    doc["type"] = "sensor";
    doc["sensor"] = id;
    doc["state"] = state;
    String json;
    serializeJson(doc, json);
    webSocket.send(json);
}

// --- Loop ---

void webSocketRun() {
  webSocket.poll();
}
