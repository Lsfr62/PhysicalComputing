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
  initial_motor(15, 21, 22, 23,34);
  initialize_servo(19);
  sensorSetup();
}


void loop() {
  
  int angle = getSteeringAngle(getSensorData());
  
  //break_vehicle(angle);
  //Serial.print(angle);
  bool fl = fullLine();
  bool hll = halfLineLeft();
  bool hlr = halfLineRight();
  
  Serial.print(~getSensorData() + (1 << 17), BIN);
  Serial.print(" ");
  Serial.print(getLastMiddleOfLine());
  Serial.print(" ");

  if(fl) Serial.println("G");
  else if(hlr) Serial.println("R");
  else if(hll) Serial.println("L");
  else Serial.println(" ");
  //turn_servo(angle);

  //drive();



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
  int rotation_angle = steeringOrientation(getSensorData());
  if (rotation_angle != 0) {
    break_vehicle(rotation_angle);
  }
  turn_servo(rotation_angle);
  drive(); */
}
