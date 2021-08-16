#include <ESP32Servo.h>

#define MAX_ANGLE 140
#define MIN_ANGLE 70

Servo servo;

/**
 * In this function is the servo initialized
 * @param pinnum the pin number, to which the signal is sent
*/
void initialize_servo(int pinnum) {
  pinMode(pinnum, OUTPUT);
  servo.attach(pinnum);
}

/**
 * In this function the servo is rotated by the angle α, for this the function write is provided by the library ESP32Servo
 * @param a is the angle the servo should be rotated, the min angle is 70 and the max is 140. The value of a will be mapped on the min and max angle
 * @return 1 when the value exceeds the limits, when the servo is rotated
*/
void turn_servo(int a) {
  int angle = map(a,35,-35, MIN_ANGLE, MAX_ANGLE);
  
  if (angle < MIN_ANGLE) {
    angle = MIN_ANGLE;
  } else if (angle > MAX_ANGLE) {
    angle = MAX_ANGLE;
  }

  servo.write(angle);
}