#include <math.h>

void setup()
{
int x;                      // Distance Horizontal in cm
int y;                      // Distance Vertial in cm
double g = -9.81/100;       // Gravity in cm/s^2
double vo;                  // Initial Velocity in cm/s
double theta;               // Angle in radians

x = 20;                     // Replace with sensor horizontal distance
y = 2;                      // Replace with sensor vertical distance
vo = 10;                    // Replace with initial velocity

theta = atan(CalculateAngle(x,g,vo,y));


}

double CalculateAngle(int x, double g, double vo, int y)
{
  double a = (g*x*x)/(2*vo);       // First constant
  double b = x;          // Second constant
  double c = (g*x*x)/(2*vo)+y;
  double nPlus;
  double nMinus;
  
  nPlus = (-b + sqrt(b*b+4*a*c))/(2*a);
  nMinus = (-b - sqrt(b*b+4*a*c))/(2*a);

  Serial.begin(9600);
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
}

void loop()
{}
