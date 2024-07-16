int v,v2;
void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(4,INPUT);
Serial.begin(9800);
}

void loop() {
v=analogRead(4);
Serial.println(v);
v2=v/4;
analogWrite(2,v2);
}
