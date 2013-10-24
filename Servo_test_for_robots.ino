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

void setup() 
{ 
  // Serial speed for infra red sensor
  Serial.begin(9600);
  // Serial speed for ultrasonic sensor
  Serial.begin(115200);
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object 
  myservo2.attach(9);  // attaches the servo on pin 8 to the servo object 
//  pinMode(9, OUTPUT);  // pin for +5v
//  digitalWrite(9, HIGH);
//  pinMode(8, OUTPUT);  // pin for Ground
//  digitalWrite(8, LOW);
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
  
  // if (sensorValue < 300) { // For the infrared
  if (sensorValue > 20) { // For the ultrasonic
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

void decideWhichDirectionToTurn() {
  beep(300, 250);
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
