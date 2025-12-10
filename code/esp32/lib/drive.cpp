#include "drive.h"

// Engine global
FastAccelStepperEngine engine;

// Motores
FastAccelStepper* stepper1 = nullptr;
FastAccelStepper* stepper2 = nullptr;
FastAccelStepper* stepper3 = nullptr;
FastAccelStepper* stepper4 = nullptr;
FastAccelStepper* stepper5 = nullptr;
FastAccelStepper* stepper6 = nullptr;
FastAccelStepper* stepper7 = nullptr;

Servo gripper;

void motorInit() {
  engine.init();  // Inicializa o RMT/hardware

  // Conecta motores aos pinos STEP
  stepper1 = engine.stepperConnectToPin(S_STP1);
  stepper2 = engine.stepperConnectToPin(S_STP2);
  stepper3 = engine.stepperConnectToPin(S_STP3);
  stepper4 = engine.stepperConnectToPin(S_STP4);
  stepper5 = engine.stepperConnectToPin(S_STP5);
  stepper6 = engine.stepperConnectToPin(S_STP6);
  stepper7 = engine.stepperConnectToPin(S_STP7);

  // Direção
  stepper1->setDirectionPin(D_STP1);
  stepper2->setDirectionPin(D_STP2);
  stepper3->setDirectionPin(D_STP3);
  stepper4->setDirectionPin(D_STP4);
  stepper5->setDirectionPin(D_STP5);
  stepper6->setDirectionPin(D_STP6);
  stepper7->setDirectionPin(D_STP7);

  // Auto-enable (desliga o driver quando parado) - não implementado
  /*
  stepper1->setAutoEnable(true);
  stepper2->setAutoEnable(true);
  stepper3->setAutoEnable(true);
  stepper4->setAutoEnable(true);
  stepper5->setAutoEnable(true);
  stepper6->setAutoEnable(true);
  stepper7->setAutoEnable(true);
  */

  // Motor de rotação da junta 4
  stepper1->setSpeedInHz(STP1_SPEED);
  stepper1->setAcceleration(STP1_ACCEL);

  // Motores da junta 56
  stepper2->setSpeedInHz(STP2_SPEED);
  stepper2->setAcceleration(STP2_ACCEL);

  stepper3->setSpeedInHz(STP3_SPEED);
  stepper3->setAcceleration(STP3_ACCEL);

  // Motor da junta 1 (base)
  stepper4->setSpeedInHz(STP4_SPEED);
  stepper4->setAcceleration(STP4_ACCEL);

  // motor da junta 3
  stepper5->setSpeedInHz(STP5_SPEED);
  stepper5->setAcceleration(STP5_ACCEL);

  // Motores da junta 2
  stepper6->setSpeedInHz(STP6_SPEED);
  stepper6->setAcceleration(STP6_ACCEL);

  stepper7->setSpeedInHz(STP7_SPEED);
  stepper7->setAcceleration(STP7_ACCEL);

  // Motor da garra
  gripper.attach(SERVO_PIN);
}

// Funções de homing - por enqunto desabilitadas

void home56() {
  stepper2->setSpeedInHz(STP2_SPEED / 3);
  stepper3->setSpeedInHz(STP3_SPEED / 3);

  const uint32_t timeout_ms = 5000;  // 5 segundos de segurança
  uint32_t start = millis();

  stepper2->move(-5000);
  stepper3->move(5000);

  while (!fc()) {
    if (millis() - start > timeout_ms) {  // se passou do tempo ele para
      Serial.println("ERRO: Timeout no homing da junta 56!");
      stepper3->forceStop();
      stepper3->forceStop();
      return;
    }
    delay(1);
  }

  stepper2->forceStop();
  stepper3->forceStop();

  stepper2->setCurrentPosition(0);
  stepper3->setCurrentPosition(0);

  stepper2->setSpeedInHz(STP2_SPEED);
  stepper3->setSpeedInHz(STP3_SPEED);
}

void home4() {
  stepper1->setSpeedInHz(STP1_SPEED / 3);  // usa uma velociadade inferior

  const uint32_t timeout_ms = 5000;  // 5 segundos de segurança
  uint32_t start = millis();

  // move para trás até encontrar o sensor
  // como cada junta possui um número diferente de passos
  // por rotação, é utlizado um valor alto que funciona para todas
  stepper1->move(-50000);

  while (!fco4()) {                       // enquanto o respectivo sensor não foi acionado ele continua
    if (millis() - start > timeout_ms) {  // se passou do tempo ele para
      Serial.println("ERRO: Timeout no homing da junta 4!");
      stepper1->forceStop();
      return;
    }
    delay(1);
  }

  // encontrou o sensor

  stepper1->forceStop();
  stepper1->setCurrentPosition(0);
  stepper1->setSpeedInHz(STP1_SPEED);
}

void home3() {
  stepper5->setSpeedInHz(STP5_SPEED / 3);

  const uint32_t timeout_ms = 10000;
  uint32_t start = millis();

  stepper5->move(500000);

  while (!fco3()) {
    if (millis() - start > timeout_ms) {
      Serial.println("ERRO: Timeout no homing da junta 4!");
      stepper5->forceStop();
      return;
    }
    delay(1);
  }

  stepper5->forceStop();
  stepper5->setCurrentPosition(0);
  stepper5->setSpeedInHz(STP5_SPEED);
}

void home2() {
  stepper6->setSpeedInHz(STP6_SPEED / 3);
  stepper7->setSpeedInHz(STP7_SPEED / 3);

  const uint32_t timeout_ms = 10000;
  uint32_t start = millis();

  stepper6->move(-50000);
  stepper7->move(-50000);

  while (!fco2()) {
    if (millis() - start > timeout_ms) {
      Serial.println("ERRO: Timeout no homing da junta 2!");
      stepper6->forceStop();
      stepper7->forceStop();
      return;
    }
    delay(1);
  }

  stepper2->forceStop();
  stepper3->forceStop();

  stepper2->setCurrentPosition(0);
  stepper3->setCurrentPosition(0);

  stepper2->setSpeedInHz(STP2_SPEED);
  stepper3->setSpeedInHz(STP3_SPEED);
}


void homeBase() {
  stepper4->setSpeedInHz(STP4_SPEED / 3);

  const uint32_t timeout_ms = 5000;
  uint32_t start = millis();

  stepper4->move(-500000);

  while (!fco1()) {
    if (millis() - start > timeout_ms) {
      Serial.println("ERRO: Timeout no homing da base!");
      stepper4->forceStop();
      return;
    }
    delay(1);
  }

  stepper4->forceStop();

  stepper4->setCurrentPosition(0);

  stepper4->setSpeedInHz(STP4_SPEED);
}


// --- Função de Controle da Garra ---

void gripperOpening(int op) {
  gripper.write(op);
}

// --- Funções de Controle das Juntas ---

void joint56Rotate(int steps) {
  stepper2->move(steps);
  stepper3->move(steps);
}


void joint56Tilt(int steps) {
  stepper2->move(steps);
  stepper3->move(-steps);

  if (fc()){
    sendSensor("joint_56_tilt", 1);
  } else {
    sendSensor("joint_56_tilt", 0);
  }
}

void joint4Rotate(int steps) {
  stepper1->move(steps);

  if (fco4()){
    sendSensor("joint_4_rot", 1);
  } else {
    sendSensor("joint_4_rot", 0);
  }
}

void joint3Tilt(int steps) {  
  stepper5->move(steps);

  if (fco3()){
    sendSensor("joint_3_tilt", 1);
  } else {
    sendSensor("joint_3_tilt", 0);
  }
}

void joint2Tilt(int steps) {
  stepper6->move(steps);
  stepper7->move(steps);

  if (fco2()){
    sendSensor("joint_2_tilt", 1);
  } else {
    sendSensor("joint_2_tilt", 0);
  }
}

void baseRotate(int steps) {
  stepper4->move(steps);

  if (fco1()){
    sendSensor("base_rot", 1);
  } else {
    sendSensor("base_rot", 0);
  }
}
