#ifndef STEERINGCONTROL_H
#define STEERINGCONTROL_H

#include <ESP32Servo.h>

/**
 * In this function is the servo initialized
 * @param pinnum the pin number, to which the signal is sent
*/
void initialize_servo(int pinnum);

/**
 * In this function the servo is rotated by the angle α, for this the function write is provided by the library ESP32Servo
 * @param a is the angle the servo should be rotated, the min angle is 70 and the max is 140. The value of a will be mapped on the min and max angle
 * @return 1 when the value exceeds the limits, when the servo is rotated
*/
void turn_servo(int angle);

#endif //STEERINGCONTROL_H