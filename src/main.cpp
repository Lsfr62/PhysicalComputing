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
#include <VehicleInformations.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  initial_motor(15, 21, 22, 23,34);
  initialize_servo(19);
  //pinMode(13, OUTPUT);  // TODO ist das wichtig?
  //Serial.println("B");
  sensorSetup();
}


void loop() {
  uint16_t sensorData = getSensorData();
  int rotationAngle = steeringOrientation(sensorData);
  // break_vehicle(rotationAngle);
  turn_servo(rotationAngle);
}
