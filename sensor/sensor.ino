#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>
#include <WiFi.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define WIFI_SSID "Galaxy  A54 5G 6E"
#define WIFI_PASSWORD "AcincuentayCuatro"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.init();
  int sensorValue = analogRead(14);
  Serial.println(sensorValue);
  sensorValue = analogRead(14);
  Serial.println(sensorValue);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(1000);
}

void loop() {
  int sensorValue = analogRead(14);

  Serial.println(sensorValue);
}
void pantalla(String str) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print(str);
}