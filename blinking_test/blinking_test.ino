


/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
*/

#include <Stepper.h>

const int stepsPerRevolution = 300;

//initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup()
{
  //set the speed at 60rpm:
  myStepper.setSpeed(80);
  //initialize the serial port
  Serial.begin(9600);
}

void loop()
{
  //step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  //step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
/*
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;


// the setup routine runs once when you press reset:
  void setup() {               
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}*/






