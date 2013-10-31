// A small robot built with cardboard and sticky tape to teach basic robotics
// by sighmon & pix
// Please re-use, re-mix, copy, paste as desired

#include <Servo.h>
#include <NewPing.h>
// Download NewPing library: http://playground.arduino.cc/Code/NewPing
// and apply this fix: http://code.google.com/p/arduino-new-ping/wiki/HELP_Error_Vector_7_When_Compiling

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define HAZARD_PIN         A0
#define INDICATOR_LEFT_PIN A1
#define INDICATOR_RIGHT_PIN A2

int lastHazard = 0;
int hazardState = 0;

int lastIndicator = 0;
int indicatorState = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;  // create servo object to control a servo 
Servo myservo2;
                // a maximum of eight servo objects can be created 
 
int pos = 90;    // variable to store the servo position 
int pos2 = 90;

int leftDistanceToObject = 0;
int rightDistanceToObject = 0;

int eyes = A0;
//int eyes = A1;

int freeCount = 0;

void setup() 
{ 
  // Serial speed for infra red sensor
  Serial.begin(9600);
  // Serial speed for ultrasonic sensor
  //Serial.begin(115200);
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object 
  myservo2.attach(9);  // attaches the servo on pin 8 to the servo object 
//  pinMode(9, OUTPUT);  // pin for +5v
//  digitalWrite(9, HIGH);
//  pinMode(8, OUTPUT);  // pin for Ground
//  digitalWrite(8, LOW);

  pinMode(10,OUTPUT); // red
  pinMode(12,OUTPUT); // yellow
  pinMode(13,OUTPUT); // green
  
  pinMode(HAZARD_PIN,OUTPUT);
  pinMode(INDICATOR_LEFT_PIN,OUTPUT);
  pinMode(INDICATOR_RIGHT_PIN,OUTPUT);

}
 
void loop() 
{ 
  // Infrared sensor
  // int sensorValue = analogRead(eyes);
  // Serial.println(sensorValue);
  // Ultrasonic sensor
  unsigned int sensorValue = sonar.ping() / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(sensorValue); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
  int now = millis();
  if(lastHazard+500 < now) {
    lastHazard = now;
    hazardState = !hazardState;
    if(hazardState) {
      digitalWrite(HAZARD_PIN,HIGH);
    }  else { 
      digitalWrite(HAZARD_PIN,LOW);
    }
  }

  // We don't have a sensor yet, so set the sensorValue;
  sensorValue = 30;

  if(lastIndicator+800 < now) {
    lastIndicator = now;
    indicatorState = !indicatorState;
    if(indicatorState) {
      digitalWrite(INDICATOR_LEFT_PIN,HIGH);
      digitalWrite(INDICATOR_RIGHT_PIN,LOW);
    }  else { 
      digitalWrite(INDICATOR_LEFT_PIN,LOW);
      digitalWrite(INDICATOR_RIGHT_PIN,HIGH);
    }
  }
  
  // if (sensorValue < 300) { // For the infrared
  if (sensorValue > 20) { // For the ultrasonic
    freeCount++;
    if(freeCount==50) {
      freedomDance();
      freeCount=0;
    }
    driveForward(100);
  } else {
//    driveBackward(1000);
    freeCount = 0;
    decideWhichDirectionToTurn();
  }
//  squareDance();
} 

void driveBackward(int time) {
  pos = 120;
  pos2 = 60;
  myservo.write(pos);
  myservo2.write(pos2);
  delay(time);
  pos = 90;
  pos2 = 90;
  myservo.write(pos);
  myservo2.write(pos2);
}

void driveForward(int time) {
  pos = 60;
  pos2 = 120;
  myservo.write(pos);
  myservo2.write(pos2);
  delay(time);
  pos = 90;
  pos2 = 90;
  myservo.write(pos);
  myservo2.write(pos2);
}

void turn(int pos) {
  myservo.write(pos);
  myservo2.write(pos);
  delay(300);
  pos = 90;
  pos2 = 90;
  myservo.write(pos);
  myservo2.write(pos2);
}

void squareDance() {
  driveForward(1000);
  turn(120);
  driveForward(1000);
  turn(120);
  driveForward(1000);
  turn(120);
  driveForward(1000);
  turn(120);
}

void beep(int time, int frequency) {
  tone(11, frequency);
  delay(time);
  tone(11, frequency/5);
  delay(time);
  noTone(11);
}

void freedomDance() {
  for(int i=random(10,20);i>=0;i--) {
    digitalWrite(10,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    tone(11,random(100,500));
    if(random(2)) {
      turn(120);
    } else {
      turn(60);
    }
  }
  noTone(11);
}

void decideWhichDirectionToTurn() {
  digitalWrite(10,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  // screech
  for(int i=0;i<100;i++) {
    //beep(random(20,2000),10);
    tone(11,random(1000,2000));
    delay(1);
  }
  digitalWrite(10,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  // screech
  for(int i=0;i<200;i++) {
    //beep(random(20,2000),10);
    tone(11,random(2000,3000));
    delay(1);
  }
  digitalWrite(10,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  // screech
  for(int i=0;i<300;i++) {
    //beep(random(20,2000),10);
    tone(11,random(3000,4000));
    delay(1);
  }
  digitalWrite(10,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  noTone(11);
  
  //beep(300, 250);
  
  turn(60);
  beep(100, 750);
  //int sensorValue = analogRead(eyes);
  //rightDistanceToObject = sensorValue;
  rightDistanceToObject = sonar.ping() / US_ROUNDTRIP_CM;
  turn(120);
  turn(120);
  beep(100, 750);
  //int sensorValueTwo = analogRead(eyes);
  //leftDistanceToObject = sensorValueTwo;
  leftDistanceToObject = sonar.ping() / US_ROUNDTRIP_CM;
  // if (leftDistanceToObject < rightDistanceToObject) { // For infrared
  if (leftDistanceToObject > rightDistanceToObject) { // For ultrasonic
    // Keep going
  } else {
    // Turn right
    turn(60);
    turn(60);
  }
}

void turnOffServos(Servo servoName) {
  servoName.detach();
}
