#include <ESP32Servo.h>
#define R1 2
#define R2 4
#define L1 12
#define L2 14
#define ENA 19
#define ENB 21
Servo motorDerechoF;
Servo motorDerechoA;
void setup() {
  //Pines  de velocidad
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  setVelocidad(200);
  motorDerechoF.attach(R1);
  motorDerechoF.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
}
void setVelocidad(int v) {
  analogWrite(ENA, v);
  analogWrite(ENB, v);
}