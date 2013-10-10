// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;
                // a maximum of eight servo objects can be created 
 
int pos = 90;    // variable to store the servo position 
int pos2 = 90;

int leftDistanceToObject = 0;
int rightDistanceToObject = 0;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object 
  myservo2.attach(9);  // attaches the servo on pin 8 to the servo object 
//  pinMode(9, OUTPUT);  // pin for +5v
//  digitalWrite(9, HIGH);
//  pinMode(8, OUTPUT);  // pin for Ground
//  digitalWrite(8, LOW);
} 
 
 
void loop() 
{ 
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue < 300) {
    driveForward(100);
  } else {
//    driveBackward(1000);
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
  delay(600);
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

void decideWhichDirectionToTurn() {
  beep(300, 250);
  turn(60);
  beep(100, 750);
  int sensorValue = analogRead(A0);
  rightDistanceToObject = sensorValue;
  turn(120);
  turn(120);
  beep(100, 750);
  int sensorValueTwo = analogRead(A0);
  leftDistanceToObject = sensorValueTwo;
  if (leftDistanceToObject > rightDistanceToObject) {
    // Keep going
  } else {
    // Turn around
    turn(60);
    turn(60);
  }
}

void turnOffServos(Servo servoName) {
  servoName.detach();
}
