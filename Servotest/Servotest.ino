#include <Servo.h>

Servo servo1;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  int position;

  servo1.write(0);
  Serial.print("0");
  delay(1000);
  servo1.write(20);
  Serial.print("90");
  delay(1000);
  servo1.write(45);
  Serial.print("180");
  delay(1000);
  servo1.write(166);
  Serial.print("180");
  delay(1000);
  servo1.write(90);
  Serial.print("180");
  delay(1000);
  servo1.write(180);
  Serial.print("180");
  delay(1000);
 /* servo1.write(180);
  delay(1000);
/*  servo1.write(0);
  delay(1000);*/
  
   
}
