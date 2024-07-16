#include "BluetoothSerial.h"
#define LED 23
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial BT;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         // Inicialización de la conexión en serie para la depuración
  BT.begin("ESP32_Control");  // Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available())

  {
      Serial.println(" Listo emparejarse");

    int incoming = BT.read();
    // Lee lo que recibimos
    Serial.print("Recibido: ");
    Serial.println(incoming);
    if (incoming == 49) {  // 1 en ASCII
      // LED Encendido
      digitalWrite(LED, HIGH);
      BT.println("LED encendido");  // Envía el mensaje de texto a través de BT Serial
    }
    if (incoming == 48) {
      digitalWrite(LED, HIGH);    // 0 en ASCII
                                  // LED Apagado
      BT.println("LED apagado");  // Envía el mensaje de texto a través de BT Serial
    }
  }
  delay(20);
}
