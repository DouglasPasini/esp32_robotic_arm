#include "conn.h"

TimerHandle_t wifiReconnectTimer;

void connInit(){
  WiFi.onEvent(WiFiEvent);
  wifiReconnectTimer = xTimerCreate(
    "wifiTimer", 
    pdMS_TO_TICKS(2000), 
    pdFALSE, (void*)0, 
    reinterpret_cast<TimerCallbackFunction_t>(connect));
}

uint8_t connect(){  
  
  Serial.println("[Wi-Fi] Conectando à rede");
  Serial.println(SSID);
  
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);  

  WiFi.begin(SSID, PASSWORD);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    i++;
    if (i >= 60) { 
      return 1;
    }
  }
  return 0;
}

void WiFiEvent(arduino_event_id_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("[Wi-Fi] Conectado");
      Serial.print("[Wi-Fi] IP: ");
      Serial.println(WiFi.localIP());
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("[Wi-Fi] Conexão perdida");
      WiFi.disconnect(true);
      xTimerStart(wifiReconnectTimer, 0); 
      break;
    default:  
      break;   
  }
}
