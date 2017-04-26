#include "motors.h"
#include "Arduino.h"

void motors_setup() {
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);

  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  motors(0,0);
}

void motors(int leftSpeed, int rightSpeed) {
  int l = min(255, abs(leftSpeed));
  int r = min(255, abs(rightSpeed));

  if(l>200)
    digitalWrite(LEFT_SPEED, HIGH);
  else
    analogWrite(LEFT_SPEED, l);

  if(r>200)
    digitalWrite(RIGHT_SPEED, HIGH);
  else
    analogWrite(RIGHT_SPEED, r);

  if(leftSpeed==0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, OFF);
  } else if(leftSpeed<0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, ON);
  } else {
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
  }

  if(rightSpeed==0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, OFF);
  } else if(rightSpeed<0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, ON);
  } else {
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);
  }
}
