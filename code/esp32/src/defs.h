#ifndef DEFS_H
#define DEFS_H

#include <Arduino.h>

// --- Configuração do Websocket ---

extern const char* websockets_server;

//  --- Definição dos pinos ---

// Sensores
// FC -Fim de Curso
// FCO - Fim de Curso Optico

constexpr int FC_PIN = 25;
constexpr int FCO1_PIN = 34; //Resisitor Pull-Up externo
constexpr int FCO2_PIN = 35; //Resisitor Pull-Up externo
constexpr int FCO3_PIN = 32;
constexpr int FCO4_PIN = 33;

// Motores 
// D - Direção
// S - Passo(Step)

constexpr int SERVO_PIN = 26; // Sinal do servo

constexpr uint8_t D_STP1 = 15;
constexpr uint8_t D_STP2 = 4;
constexpr uint8_t D_STP3 = 5;
constexpr uint8_t D_STP4 = 19;
constexpr uint8_t D_STP5 = 22;
constexpr uint8_t D_STP6 = 13;
constexpr uint8_t D_STP7 = 14;

constexpr uint8_t S_STP1 = 2;
constexpr uint8_t S_STP2 = 17; // TX2
constexpr uint8_t S_STP3 = 18;
constexpr uint8_t S_STP4 = 21;
constexpr uint8_t S_STP5 = 23;
constexpr uint8_t S_STP6 = 12;
constexpr uint8_t S_STP7 = 27;


// --- Algumas constantes de cada motor ---

// Valores encontrados durante os testes

// Quantidade de passos por revolução 
// Depende da configuração de microstep

constexpr uint8_t STP1_SPR = 400; // Motor da junta 4 - para rotação
constexpr uint8_t STP2_SPR = 800; // Motor da junta 56 - para a rotação
constexpr uint8_t STP3_SPR = 200; // Motor da junta 56 - para a inclinação
constexpr uint8_t STP4_SPR = 1000; // Motor da base - para rotação
constexpr uint8_t STP5_SPR = 750; // Motor da junta 3
constexpr uint8_t STP6_SPR = 750; // Motor da juinta 2
constexpr uint8_t STP7_SPR = 750; // Motor da juinta 2

// Velocidade

constexpr uint8_t STP1_SPEED = 400; 
constexpr uint8_t STP2_SPEED = 450; 
constexpr uint8_t STP3_SPEED = 450; 
constexpr uint8_t STP4_SPEED = 500; 
constexpr uint8_t STP5_SPEED = 900; 
constexpr uint8_t STP6_SPEED = 900; 
constexpr uint8_t STP7_SPEED = 900; 

// Aceleração

constexpr uint8_t STP1_ACCEL = 600; 
constexpr uint8_t STP2_ACCEL = 410; 
constexpr uint8_t STP3_ACCEL = 410; 
constexpr uint8_t STP4_ACCEL = 1200; 
constexpr uint8_t STP5_ACCEL = 900; 
constexpr uint8_t STP6_ACCEL = 900; 
constexpr uint8_t STP7_ACCEL = 900; 



#endif
