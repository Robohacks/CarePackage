#include <NewPing.h>
#include <Servo.h>
#include <math.h>

#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     15  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

/**/

#define lw1  7
#define lw2  8

#define rw1  9
#define rw2  10

String inputString="";
char junk;

Servo servoIncline;
Servo servoBoot;
const float pi = 3.14;
const double g = 9.81;       // Gravity in cm/s^2

/**/

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Creating the NewPing Object.

Servo servo1;

int finalDistance = 0;

//The upper boundary for looking
int maxDistance = 50;
// Everything that is below minDistance we ignore;
int minDistance = 20;
//If object was detected, then it is okay if the sonar.ping() is between distance +-10cm of fault
int fault = 5;

int delayTime = 100;

//goes at the beginning of the programm
void setup() {
  Serial.begin(9600); // Begin serial com. at 115200 baud rate.
  pinMode(lw1, OUTPUT);  
   pinMode(lw2, OUTPUT);
   pinMode(rw1, OUTPUT);  
   pinMode(rw2, OUTPUT);
  servo1.attach(52);

  unsigned int possibleDistance = 0;
  unsigned int fault = 5;
  unsigned int distances[180];
  for(int i = 0; i < 180; i++)
  {
    servo1.write(i);
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Ping: ");
    unsigned int cmToObject = uS / US_ROUNDTRIP_CM;
    Serial.print(cmToObject); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial.print("cm at "); //If you would like ping
    Serial.print(i);
    Serial.println(" degrees");
    distances[i] = cmToObject;
    delay(500);
  }
  unsigned int angleStart;
  unsigned int angleFinish;
  unsigned int lastCloseDistance;
  unsigned int finalDistance = 0;
  for(int i = 0; i < 180; i++)
  {
    if(distances[i] > minDistance && finalDistance == 0)
    {
      if(isCloseTo(distances[i + 1],distances[i]) && isCloseTo(distances[i + 2],distances[i]) && isCloseTo(distances[i + 3],distances[i]))
      {
        angleStart = i;
        finalDistance = distances[i];
      }
    }
    else 
    {
      if(isCloseTo(distances[i + 1], 0) && isCloseTo(distances[i + 2], 0) && isCloseTo(distances[i + 3], 0))
      {
        angleFinish = i;
      }
    }
  }

  unsigned int x;                      // Distance Horizontal in cm
unsigned int y;                      // Distance Vertial in cm
double vo;                  // Initial Velocity in cm/s
double theta;               // Angle in radians
Serial.begin(9600);
servoIncline.attach(10);
servoBoot.attach(8);

x = finalDistance;                  // Replace with sensor horizontal distance
y = 0;                    // Replace with sensor vertical distance
vo = 10;                  // Replace with initial velocity

double result = (asin((x*g)/(vo*vo))/2)*(360/(2*pi));

Serial.print(result);
servoIncline.write(result+12);
for(int i = 12; i < result + 12; i++)
{
  servoIncline.write(i);
  delay(50);
}
delay(1000);
servoBoot.write(90);
delay(1000);
servoBoot.write(135);
delay(1000);
servoBoot.write(90);
delay(500);
servoIncline.write(0+12);
for(int i = result + 12; i < 0 + 12; i--)
{
  servoIncline.write(i);
  delay(50);
}
}

int isCloseTo(int numToCheck, int possibleDist)
{
  if(numToCheck > (possibleDist - fault) && numToCheck < (possibleDist + fault))
  {
    return 1;
  }
  return 0;
}

//infinite loop of the program
void loop() 
{
  if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(inputString == "w"){        
      goStraight();
      Serial.write("Going forward\n");  
    }else if(inputString == "a"){  
      turnLeft();
      Serial.write("Turning left!\n"); 
    }else if(inputString=="d"){
      turnRight();
      Serial.write("Turning right!\n"); 
    }else if(inputString=="x"){
      goBack();
      Serial.write("Going back!\n"); 
    }else if(inputString=="s"){
      stopMoving();
      Serial.write("Stopping now!\n"); 
    }
    inputString = "";
  }
}

void goStraight(){
  digitalWrite(lw1,HIGH);
  digitalWrite(lw2,LOW); 
  digitalWrite(rw1,HIGH);
  digitalWrite(rw2,LOW);
}

void goBack(){
  digitalWrite(lw2,HIGH);
  digitalWrite(lw1,LOW); 
  digitalWrite(rw2,HIGH);
  digitalWrite(rw1,LOW);
}

void stopMoving(){
  digitalWrite(lw1,LOW);
  digitalWrite(lw2,LOW); 
  digitalWrite(rw1,LOW);
  digitalWrite(rw2,LOW);
}
void turnRight(){
  digitalWrite(lw1,HIGH);
  digitalWrite(lw2,LOW); 
  digitalWrite(rw1,LOW);
  digitalWrite(rw2,HIGH);
  
}

void turnLeft(){
  digitalWrite(lw1,LOW);
  digitalWrite(lw2,HIGH); 
  digitalWrite(rw1,HIGH);
  digitalWrite(rw2,LOW); 
}

