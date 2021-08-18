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
  //Serial.println();
  turn_servo(steeringOrientation(getSensorData()));
  drive();
  //delay(300);
  //Serial.println((int)getSensorData(), BIN);
  /*Serial.println("Start");
  // TEST: Es wird komplett nach links und dann nach Rechts gelenkt
  for (int i = 0; i < 36; i++) {
    turn_servo(i);
    delay(20);
  }

  for (int i = 0; i > -36; i--) {
    turn_servo(i);
    delay(20);
  }
  //sensorUpdate();
  //int x = getSensorData;
  Serial.println((int)getSensorData(), BIN);
  Serial.println("Stop");
  drive()*/
}
