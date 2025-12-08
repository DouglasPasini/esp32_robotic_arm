#include "sensors.h"

void sensorInit() {
  pinMode(FC_PIN, INPUT_PULLUP);
  pinMode(FCO1_PIN, INPUT_PULLUP);
  pinMode(FCO2_PIN, INPUT_PULLUP);
  pinMode(FCO3_PIN, INPUT_PULLUP);
  pinMode(FCO4_PIN, INPUT_PULLUP);
}
