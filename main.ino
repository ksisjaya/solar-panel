#include <Servo.h>  //include servo library

Servo motor;                //declare servo object to turn motor
int initial_position = 90;  //set the initial position to 90˚
int diode1 = A0;            //define photodiode 1 pin to be A0
int diode2 = A1;            //define photodiode 2 pin to be A1
int error = 3;              //set the error bounds to 3
int servo = 2;              //set the servo pin to be GPIO 2

void setup(){

  //setup servo to position chassis to 90˚ and setup diodes to read as inputs

  motor.attach(servo);
  motor.write(initial_position);
  pinMode(diode1, INPUT);
  pinMode(diode2, INPUT);
  delay(100);

}

void loop(){

  //read the input values from the two diodes and find the difference

  int value1 = analogRead(diode1);
  int value2 = analogRead(diode2);
  int diff1 = abs(value1 - value2);
  int diff2 = abs(value2 - value1);

  //if either diff is larger than the error, change initial position
  if(diff1 > error || diff2 > error){
    if(value1 > value2)   //if photodiode 1 has a larger light value, then decrement the position
      initial_position = initial_position--;
    else                  //otherwise increment the position
      initial_position = initial_position++;
  }

  motor.write(initial_position);  //write to the motor to adjust for new position
  delay(200);
}
