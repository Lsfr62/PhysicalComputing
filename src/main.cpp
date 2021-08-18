/*
 * 2WD RC SMART CAR CHASSIS
 * 
 * 
 */

#include <Arduino.h>
#include <drivecontrol.h>
#include <steeringControl.h>
#include <reflectanceSensor.h>
#include <steeringOrientation.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  initial_motor(4, 0, 16, 17,34);
  initialize_servo(15);
  pinMode(13, OUTPUT);  // TODO ist das wichtig?
  //Serial.println("B");
  sensorSetup();
}

void loop() {
  int rotation_angle = steeringOrientation(getSensorData());
  if (rotation_angle != 0) {
    break_vehicle(rotation_angle);
  }
  turn_servo(rotation_angle);
  drive();
}
