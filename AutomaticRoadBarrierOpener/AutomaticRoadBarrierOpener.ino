
#include <Servo.h>
int trigPin = 6;
int echoPin = 7;
int pingTravelTime;
float distance;
bool barrierIsOpen = false;

int positionOpen = 90;
int positionClosed = 0;

Servo barrier;

void setup()
{ 
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  
  barrier.attach(9, 500, 2500);
  barrier.write(positionOpen);
  delay(500);
}

void loop()
{  
  float distanceFromSensor = readDistanceFromSensor ();
  if (barrierIsOpen && distanceFromSensor > 10) {
    barrier.write(positionClosed);
    Serial.println("Closing barrier");
    barrierIsOpen = false;
  }
  if (!barrierIsOpen && distanceFromSensor < 10) {
    barrier.write(positionOpen);
    Serial.println("Opening barrier");
    barrierIsOpen = true;    
  }

  delay(1000);
 
}

float readDistanceFromSensor (){
digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pingTravelTime = pulseIn(echoPin,HIGH);
  
  distance = ((pingTravelTime-200.)/60.)+1;
  Serial.println("  Distance = " + String(distance));  
  return distance;
}