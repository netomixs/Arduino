#include "BluetoothSerial.h"
#include "ESP32Servo.h"
const char *pin = "1234";
String device_name = "ESP32-BT-Slave";
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial SerialBT;
#define R1 2
#define R2 4
#define L1 12
#define L2 14
#define RXFRONT 5
#define TXFRONT 18
#define RXLEFT 26
#define TXLEFT 27
#define ENA 19
#define ENB 21
int velocidad = 200;
int distanciaMinima = 20;
float distanciaFrenteVar = 0;
float distanciaIzquierdVar = 0;
int umbral = 100;
bool isAdelante = false;
bool isGiro = false;
int zero = 0;
int mas = 0;
bool horizonte = false;
Servo motorDerechoAdelante;
void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(RXFRONT, OUTPUT);
  pinMode(TXFRONT, INPUT);
  pinMode(RXLEFT, OUTPUT);
  pinMode(TXLEFT, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  setVelocidad(velocidad);
}

void loop() {
  calcularDistanciaFront();

  if (distanciaFrenteVar == 0) {
  }
  if (horizonte == true && distanciaFrenteVar > 1 && distanciaFrenteVar < distanciaMinima + 5) {
    horizonte = false;
  }
  if (horizonte == false && distanciaFrenteVar > distanciaMinima + 5 && distanciaFrenteVar < 750) {
    horizonte = true;
  }

  if (horizonte == true) {
    if (distanciaFrenteVar >= distanciaMinima && distanciaFrenteVar <= 100) {
      int v = map(distanciaFrenteVar, distanciaMinima, 100, 125, 160);
      Serial.print("Velocidad: ");
      Serial.println(v);
      setVelocidad(v);
    } else if (distanciaFrenteVar > 100) {
      setVelocidad(200);
    }

    adelante();
  }

  else {
    detener();
    atras();

    delay(300);
    detener();
    delay(1000);
    calcularDistanciaLeft();
    bool horizonteL = false;
    if (distanciaIzquierdVar == 0) {
    }
    if (horizonteL == true && distanciaIzquierdVar > 1 && distanciaIzquierdVar < distanciaMinima) {
      horizonteL = false;
    }
    if (horizonte == false && distanciaIzquierdVar > distanciaMinima && distanciaIzquierdVar < 750) {
      horizonteL = true;
    }
    if (horizonteL == true) {
      setVelocidad(150);
      giro(1);
      delay(50);
      setVelocidad(100);
      while (distanciaFrenteVar < 20 && distanciaFrenteVar != 0) {
        delay(100);
        calcularDistanciaFront();
        giro(1);
        delay(100);
        detener();
      }
      delay(1000);
    } else {
      setVelocidad(150);
      giro(-1);
      delay(50);
      setVelocidad(100);
      while (distanciaFrenteVar < 20 && distanciaFrenteVar != 0) {
        delay(100);
        calcularDistanciaFront();
        giro(-1);
        delay(100);
        detener();
      }
      delay(1000);
    }
  }

  //Serial.println(distanciaFrenteVar);

  /* if (SerialBT.available()) {
    int incomingByte = SerialBT.read();

    Serial.write(incomingByte);
    if (incomingByte == 50) {
      adelante();
      SerialBT.println("Adelante");
    }
    if (incomingByte == 52) {
      izquierdaAdelante();
      SerialBT.println("  izquierda");
    }
    if (incomingByte == 54) {
      derechaAdelante();
      SerialBT.println("  derecha");
    }
    if (incomingByte == 56) {
      atras();
      SerialBT.println("Atras");
    }
    if (incomingByte == 48) {
      detener();
      SerialBT.println("Detener");
    }
    switch (incomingByte) {
      case 97:
        adelanteR();
        break;
      case 98:
        atrasR();
        break;
      case 99:
        adelanteL();
        break;
      case 100:
        adelanteL();
        break;
    }
    if (incomingByte == 107) {
      if (velocidad < 250) {
        velocidad = velocidad + 50;
      }
    }
    if (incomingByte == 108) {
      if (velocidad > 0) {
        velocidad = velocidad - 50;
      }
    }
  }*/
}
void setVelocidad(int v) {
  analogWrite(ENA, v);
  analogWrite(ENB, v);
}
void adelanteR() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}
void adelanteL() {

  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}
void atrasL() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
}
void atrasR() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}
void detenerL() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}
void detenerR() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}
void adelante() {
  adelanteR();
  adelanteL();
}
void atras() {
  atrasL();
  atrasR();
}
void giro(int c) {

  if (c < 0) {
    adelanteL();
    atrasR();
  }

  else if (c > 0) {
    adelanteR();
    atrasL();
  }
}
void control(int c) {
  delay(1000);
  setVelocidad(150);
  if (c < 0) {
    c = c * -1;
    int n = 0;
    adelanteL();
    atrasR();
    while (n < c) {
      adelanteL();
      atrasR();
      delay(100);
      detener();
      delay(100);
      n++;
    }
  } else if (c > 0) {
    int n = 0;
    adelanteR();
    atrasL();
    while (n < c) {
      adelanteR();
      atrasL();
      delay(100);
      detener();
      delay(100);
      n++;
    }

  } else {
    adelante();
  }
}
void izquierdaAdelante() {
  detenerL();
  adelanteR();
}
void izquierdaAtras() {
  detenerL();
  atrasR();
}
void derechaAdelante() {
  detenerR();
  adelanteL();
}
void derechaAtras() {
  detenerR();
  adelanteL();
}
void detener() {
  detenerL();
  detenerR();
}

void calcularDistanciaFront() {
  long t;

  digitalWrite(RXFRONT, LOW);
  delayMicroseconds(5);
  digitalWrite(RXFRONT, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(RXFRONT, LOW);
  t = pulseIn(TXFRONT, HIGH);

  distanciaFrenteVar = t * 0.034 / 2;
}
void calcularDistanciaLeft() {
  long t;

  digitalWrite(RXLEFT, LOW);
  delayMicroseconds(5);
  digitalWrite(RXLEFT, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(RXLEFT, LOW);
  t = pulseIn(TXLEFT, HIGH);
  distanciaIzquierdVar = t * 0.034 / 2;
}