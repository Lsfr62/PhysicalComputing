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
#include <VehicleInforamations.h>

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
  uint16_t sensorData = getSensorData();
  int rotationAngle = steeringOrientation(sensorData);
  turn_servo(rotationAngle);
  drive();
  // TODO: lane change and right angle should be changed
  refreshInformations('Y', 'Y', (rotationAngle < 0 ? 'L' : 'R'), rotationAngle, speed, sensorData);
}
