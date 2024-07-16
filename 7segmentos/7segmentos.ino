#define L1 2
#define L2 4
#define L3 5
#define L4 18
#define L5 19
#define L6 13
#define L7 12
int segmentos[10] = {
  0b0000001,   // 0
  0b0000110,   // 1
  0b0001101,   // 2
  0b0001111,   // 3
  0b00001100,  // 4
  0b00011001,  // 5
  0b00010001,  // 6
  0b00011111,  // 7
  0b00000000,  // 8
  0b00001110   // 9
};
void setup() {

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(L7, OUTPUT);
}
int i = 1;
void loop() {
  // put your main code here, to run repeatedly:


  scribir(i);
  delay(1000);
  i++;
  if (i == 9) {
    i = 0;
  }
}
  void reset(){
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
      digitalWrite(L5, LOW);
      digitalWrite(L6, LOW);
      digitalWrite(L7, LOW);
  }
void scribir(int numero) {


 reset();
  switch (numero) {
    case 1:
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      break;
    case 2:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L5, HIGH);
      digitalWrite(L7, HIGH);
      break;
    case 3:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L7, HIGH);
      break;
    case 4:
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L6, HIGH);
      digitalWrite(L7, HIGH);
      break;
    case 5:
      digitalWrite(L1, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L6, HIGH);
      digitalWrite(L7, HIGH);
      break;
    case 6:
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L5, HIGH);
      digitalWrite(L6, HIGH);
      digitalWrite(L7, HIGH);

      break;
    case 7:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);

      break;
    case 8:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L5, HIGH);
      digitalWrite(L6, HIGH);
      digitalWrite(L7, HIGH);


      break;
    case 9:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L6, HIGH);


      break;
    case 0:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
      digitalWrite(L5, HIGH);
      digitalWrite(L6, HIGH);



      break;
  }

}
