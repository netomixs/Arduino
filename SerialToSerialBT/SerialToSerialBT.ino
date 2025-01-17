//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234";  // Change this to more secure PIN.

String device_name = "ESP32-BT-Slave";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define LED 23
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
//Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif
  pinMode(LED, OUTPUT);
}

 
void loop() {
  if (Serial.available()) {
    int incomingByte = Serial.read();
    SerialBT.write(incomingByte);
    if (incomingByte == 49) {  // 1 en ASCII
      // LED Encendido
      digitalWrite(LED, HIGH);
      SerialBT.println("LED encendido");  // Envía el mensaje de texto a través de BT Serial
    }
        if (incomingByte == 48) {
      digitalWrite(LED, HIGH);    // 0 en ASCII
                                  // LED Apagado
      SerialBT.println("LED apagado");  // Envía el mensaje de texto a través de BT Serial
    }
    if (incomingByte == 1) {
      Serial.println("Hola mundo");
    }
  }

  if (SerialBT.available()) {
    int incomingByte = SerialBT.read();
    Serial.write(incomingByte);
    if (incomingByte == 49) {  // 1 en ASCII
      // LED Encendido
      digitalWrite(LED, HIGH);
      SerialBT.println("LED encendido");  // Envía el mensaje de texto a través de BT Serial
    }
        if (incomingByte == 48) {
      digitalWrite(LED, LOW);    // 0 en ASCII
                                  // LED Apagado
      SerialBT.println("LED apagado");  // Envía el mensaje de texto a través de BT Serial
    }
    if (incomingByte == 1) {
      Serial.println("Hola mundo");
    }
  }


  delay(20);
}
