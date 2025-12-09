#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <FastAccelStepper.h>
#include <ESP32Servo.h>
#include "defs.h"
#include "sensors.h"

// Engine principal da biblioteca
extern FastAccelStepperEngine engine;

// Ponteiros para os motores
extern FastAccelStepper* stepper1;
extern FastAccelStepper* stepper2;
extern FastAccelStepper* stepper3;
extern FastAccelStepper* stepper4;
extern FastAccelStepper* stepper5;
extern FastAccelStepper* stepper6;
extern FastAccelStepper* stepper7;

// Servo motor
extern Servo gripper;

void motorInit();

// Funções para homing - por enquanto desabilitadas

void home56();
void home4();
void home3();
void home2();
void homeBase();


// --- Função de Controle da Garra ---

void gripperOpening(int op);

// --- Funções de Controle das Juntas ---

void joint56Rotate(int angle);
void joint56Tilt(int angle);
void joint4Rotate(int angle);
void joint3Tilt(int angle);
void joint2Tilt(int angle);
void baseRotate(int angle);

#endif
