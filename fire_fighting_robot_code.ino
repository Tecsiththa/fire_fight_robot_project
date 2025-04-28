//*------ Arduino Fire Fighting Robot project---- *//
 
#include <Servo.h>

Servo myservo;
 
int pos = 0;    
boolean fire = false;

#define Left 4          // left sensor
#define Right 5         // right sensor
#define Forward 6       //front sensor
#define LM1 8           // left motor
#define LM2 9           // left motor
#define RM1 10          // right motor
#define RM2 11          // right motor
#define pump 12         //water pump

void setup()
{
  Serial.begin(115200);
  
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(13);
  myservo.write(90); 
}
 



void put_off_fire()
{

   digitalWrite(LM1, HIGH);
   digitalWrite(LM2, HIGH);
   digitalWrite(RM1, HIGH);
   digitalWrite(RM2, HIGH);
   
    digitalWrite(pump,HIGH);
    delay(50);
 
    for (pos = 50; pos <= 110; pos += 1) { 
      myservo.write(pos); 
      delay(10);  
    }
    for (pos = 110; pos >= 50; pos -= 1) { 
      myservo.write(pos); 
      delay(10);
    }

    
    digitalWrite(pump,LOW);
    myservo.write(90);
    delay(500); 
    fire = false;
}
 
void loop()
{
  myservo.write(90);  
  
  // Read sensor values
  int leftSensor = digitalRead(Left);
  int rightSensor = digitalRead(Right);
  int frontSensor = digitalRead(Forward);

  // Print sensor values for Serial Plotter (format: Left Right Front)
  Serial.print(leftSensor);
  Serial.print("");
  Serial.print(rightSensor);
  Serial.print(" ");
  Serial.println(frontSensor);
  Serial.print(" ");
  
  if (leftSensor == 1 && rightSensor == 1 && frontSensor == 1) 
  {
    delay(100);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }
  else if (frontSensor == 0) 
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
  }
  else if (leftSensor == 0)
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }
  else if (rightSensor == 0) 
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  delay(150); // Adjust delay for responsiveness
  
  while (fire == true)
  {
    put_off_fire();
    Serial.println("Fire Detected.");
  }
}