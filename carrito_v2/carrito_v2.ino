#include "BluetoothSerial.h"
#include "ESP32Servo.h"
#include <math.h>
const char *pin = "1234";
String device_name = "ESP32-BT-Slave";
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
BluetoothSerial SerialBT;
#define TXLEFT 2
#define RXLEFT 4

#define TXRIGHT 5
#define RXRIGHT 18
//
#define R1 12
#define R2 14
#define L1 27
#define L2 26
//
#define ENA 13  //Derecha
#define ENB 25
int velocidad = 200;
int distanciaDeInestabilidad = 25;
void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  // put your setup code here, to run once:
  pinMode(RXRIGHT, OUTPUT);
  pinMode(TXLEFT, INPUT);
  pinMode(RXLEFT, OUTPUT);
  pinMode(TXRIGHT, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  setVelocidad(165);
  detener();
}
float distanciaIzquierdaAnterior = 0;
float distanciaDerechaAnterior = 0;
bool esAvanzar = false;
void loop() {
  int v1, v2;
   v1 = 200;
  float distanciaIzquierda = calcularDistanciaL();
  float distanciaDerecha = calcularDistanciaR();
  if(SerialBT.available()){
      SerialBT.println(distanciaIzquierda);
       SerialBT.write(distanciaIzquierda);
  }

  if (distanciaDerecha > 15) {
    Serial.println("Avanzando");
    //
    if (distanciaIzquierda > 8 && distanciaIzquierda < 15) {
      adelante(140);
    }
    if (distanciaIzquierda < 8) {
     

      Serial.println("Izquierda Nueva");
      Serial.println(distanciaIzquierda);
      adelanteL(v1);
      detenerR();
      delay(100);
      detener();
      adelante(v1);
      delay(200);
      detener();
      adelanteR(v1);
      detenerL();
      delay(100);
      detener();
      delay(100);
    }
   if (distanciaIzquierda > 15) {
      Serial.println("Izquierda Nueva");
      Serial.println(distanciaIzquierda);
      adelanteR(v1);
      detenerL();
      delay(100);
      detener();
      adelante(v1);
      delay(200);
      detener();
      adelanteL(v1);
      detenerR();
      delay(107);
      detener();
      delay(100);
    }
  } else {
    detener();
  }
}
float calcularDistanciaL() {
  long tiempoIzquerda = 0;
  //Apagar señal de envio
  digitalWrite(RXLEFT, LOW);
  //Esperar
  delayMicroseconds(5);
  //Ensender señal
  digitalWrite(RXLEFT, HIGH);
  //Eperar que la señal rebote
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  //Apagar señal
  digitalWrite(RXLEFT, LOW);
  //Leer timepo se respuesta
  tiempoIzquerda = pulseIn(TXLEFT, HIGH);
  float distanciaIzqierda = tiempoIzquerda * 0.034 / 2;
  if (distanciaIzquierdaAnterior < distanciaDeInestabilidad) {
    if (distanciaIzqierda == 0) {
      distanciaIzqierda = distanciaIzquierdaAnterior;
    } else {
      distanciaIzquierdaAnterior = distanciaIzqierda;
    }
  } else {
    distanciaIzquierdaAnterior = distanciaIzqierda;
  }
  Serial.print("Distancia Izqauqies: ");
  Serial.println(distanciaIzqierda);
  return distanciaIzqierda;
}

float calcularDistanciaR() {
  long t = 0;
  digitalWrite(RXRIGHT, LOW);
  delayMicroseconds(5);
  digitalWrite(RXRIGHT, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(RXRIGHT, LOW);
  t = pulseIn(TXRIGHT, HIGH);
  float distanciaDerecha = t * 0.034 / 2;
  if (distanciaDerechaAnterior < distanciaDeInestabilidad) {
    if (distanciaDerecha == 0) {
      distanciaDerecha = distanciaDerechaAnterior;
    } else {
      distanciaDerechaAnterior = distanciaDerecha;
    }
  } else {
    distanciaDerechaAnterior = distanciaDerecha;
  }
  Serial.print("Distancia Derecha: ");
  Serial.println(distanciaDerecha);
  return distanciaDerecha;
}
void setVelocidad(int v) {
  analogWrite(ENA, v);
  analogWrite(ENB, v);
}
void adelanteR(int vel) {
  analogWrite(ENA, vel);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}
void adelanteL(int vel) {
  analogWrite(ENB, vel);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void detenerL() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}
void detenerR() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}
void adelante(int vel) {
  adelanteR(vel);
  adelanteL(vel);
}
/*void derecha() {
  detenerR();
  adelanteL();
}*/
/*void izquierda() {
  detenerL();
  adelanteR();
}*/
/*void atrasL() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
}
void atrasR() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}*/
/*void atras() {
  atrasL();
  atrasR();
}*/
void detener() {
  detenerL();
  detenerR();
}
float angulo(float ladoA, float ladoB) {
  float ladoOpuesto = 6;
  float last = 1;
  if (ladoB < ladoA) {
    float aux = ladoB;
    ladoB = ladoA;
    ladoA = aux;
    last = -1;
  }
  float ladoAyacente = ladoB - ladoA;
  float anguloB = degrees(atan(ladoOpuesto / ladoAyacente));
  float anguloC = (90 - anguloB) * last;
  return anguloC;
}