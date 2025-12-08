#include "esp32-hal-gpio.h"
#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "src/defs.h"

// Inicialização dos sensores
void sensorInit();

inline bool fc(){return digitalRead(FC_PIN) == LOW;}     // Fim de curso da junta 56
inline bool fco1(){return digitalRead(FCO1_PIN) == HIGH;} // Fim de curso da base
inline bool fco2(){return digitalRead(FCO2_PIN) == LOW;} // Fim de curso da junta 2
inline bool fco3(){return digitalRead(FCO3_PIN) == LOW;} // Fim de curso da junta 3
inline bool fco4(){return digitalRead(FCO4_PIN) == LOW;} // Fim de curso da junta 4

#endif
