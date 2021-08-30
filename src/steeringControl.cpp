#include "steeringControl.h"

#define MAX_ANGLE 140
#define MIN_ANGLE 70

Servo servo;

void initialize_servo(int pinnum) {
  pinMode(pinnum, OUTPUT);
  servo.attach(pinnum);
}

void turn_servo(int a) {
  int angle = map(a,35,-35, MIN_ANGLE, MAX_ANGLE);
  
  if (angle < MIN_ANGLE) {
    angle = MIN_ANGLE;
  } else if (angle > MAX_ANGLE) {
    angle = MAX_ANGLE;
  }

  servo.write(angle);
}