#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 5, 18, 19, 21);
#define ADC_VREF_mV 3300.0  // in millivolt
#define ADC_RESOLUTION 4096.0
int sensor = 14;
float temperatura = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adcVal = analogRead(sensor);
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  temperatura = milliVolt / 10;
  //temperatura = (5.0 * temperatura * 100.0)/1024.0;
  Serial.println(temperatura);
  lcd.setCursor(0, 0);  //Con este comando decimos en que línea queremos escribir
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.setCursor(5, 1);
  lcd.print("\337C");
  delay(500);
}
