#include <math.h>
#include <Servo.h>

Servo servoIncline;
Servo servoBoot;
const float pi = 3.14;
const double g = -981;       // Gravity in cm/s^2

void setup()
{
unsigned int x;                      // Distance Horizontal in cm
unsigned int y;                      // Distance Vertial in cm
double vo;                  // Initial Velocity in cm/s
double theta;               // Angle in radians
Serial.begin(9600);
servoIncline.attach(10);
servoBoot.attach(8);

x = 100;                   // Replace with sensor horizontal distance
y = 0;                     // Replace with sensor vertical distance
vo = 50;                  // Replace with initial velocity

theta = atan(CalculateAngle(x,g,vo,y));
Serial.print("\nTheta = ");
Serial.print(theta);

theta *= 360/(2*pi);
Serial.print("\nTheta in degrees =");
Serial.print(theta);

moveServo(servoIncline,45);
moveServo(servoIncline, 0);
moveServo(servoIncline, theta);
delay(1000);
moveServo(servoBoot, 90);
moveServo(servoBoot, 135);
moveServo(servoBoot, 90);
moveServo(servoBoot, 135);
moveServo(servoBoot, 90);

moveServo(servoIncline, 0);

Serial.print("\nJob's done");

}

void moveServo(Servo servo, int angle)
{
  servo.write(angle);
  Serial.println(angle);
  delay(1000);
}

double CalculateAngle(unsigned int x, int g, double vo, unsigned int y)
{
  float a = (g*x*x)/(2*vo*vo);    // First constant
  int b = x;                      // Second constant
  float c = (g*x*x)/(2*vo*vo)-y;  // Third constant
  double nPlus;
  double nMinus;
  
  nPlus = ((-b) + sqrt((b*b)-(4*a*c)))/(2*a);
  nMinus = ((-b) - sqrt((b*b)-(4*a*c)))/(2*a);

  Serial.print("Value of A: ");
  Serial.print(a);
  Serial.print("\nValue of B: ");
  Serial.print(b);
  Serial.print("\nValue of C: ");
  Serial.print(c);
  
  Serial.print("\n\nValue of nPlus: ");
  Serial.print(nPlus);
  Serial.print("\nValue of nMinus: ");
  Serial.print(nMinus);

  return nMinus;
}

void loop()
{}
