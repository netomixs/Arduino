#define in1 19
#define in2 18
#define in3 5
#define in4 17
#include <Stepper.h>

const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution, in1, in2, in3, in4);

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(5);
  // initialize the serial port
  Serial.begin(115200);

}


void loop() {
  // step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
