#include <Wire.h>
#include <map>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "Galaxy  A54 5G 6E"
#define WIFI_PASSWORD "AcincuentayCuatro"
#define API_KEY "AIzaSyDNY12blUUkzduPtITjKPz5e2YRSRgqrlY"
#define DATABASE_URL "https://detectoragua-default-rtdb.firebaseio.com/"
const long gmtOffset_sec = -21600;
const char* ntpServer = "pool.ntp.org";
const int daylightOffset_sec = 0;
#define sensor_turbidez 33
LiquidCrystal_I2C lcd(0x27, 16, 2);
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
void setup() {

  //pinMode(sensor_turbidez, INPUT);
  lcd.init();
  Serial.begin(115200);
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
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h
  FirebaseJson json;
  json.set("param1", 123);
  json.set("param2", "valor");
  json.set("param4", 45.67);
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}


void registrarEnFirebase(const char* path, std::map<String, String> data) {
  FirebaseJson json;
  for (const auto& pair : data) {
    json.set(pair.first, pair.second);
  }
  if (Firebase.RTDB.push(&fbdo, path, &json)) {
    Serial.println("Data pushed successfully");
  } else {
    Serial.println("Failed to push data");
    Serial.println(fbdo.errorReason());
  }
}

void loop() {
  int sensorValue = analogRead(sensor_turbidez);

 
  int turbidez = map(sensorValue, 4096,0 , 100, 0);


 struct tm timeinfo;
  std::map<String, String> data;
 Serial.println( sensorValue);
  Serial.println( turbidez);
  data["agua"] = String(turbidez);
 if (getLocalTime(&timeinfo)) {
      data["tiempo"] =  timeToString(timeinfo);
  } else {
    Serial.println("Error al obtener la hora");
  }
    pantalla("Calidad:"+data["agua"] ,"" +  data["tiempo"] );
  registrarEnFirebase("/datos", data);
  delay(1000);
}
void pantalla(String str,String str2) {
lcd.clear();
    lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print(str);
    lcd.setCursor(0, 1);
  lcd.print(str2);
}
String timeToString(struct tm timeinfo) {
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &timeinfo);
  return String(buffer);
}