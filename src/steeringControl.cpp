#include <ESP32Servo.h>

#define MAX_ANGLE 140
#define MIN_ANGLE 70

Servo servo;

/**
 * @param pinnum the pin number, to which the signal is sent
*/
void initialize_servo(int pinnum) {
  pinMode(pinnum, OUTPUT);
  servo.attach(pinnum);
  return 0;
}

/**
 * @param angle is the angle the servo should be rotated, the min angle is 70 and the max is 140
 * @return 1 when the value exceeds the limits, when the servo is rotated
*/
int turn_servo(int angle) {
  if (angle < MIN_ANGLE || angle > MAX_ANGLE) {
    return 1;
  }

  servo.write(angle);
  return 0;
}