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
#include <EEPROM.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  initial_motor(15, 21, 22, 23,34);
  initialize_servo(19);
  sensorSetup();
}

bool taste = false;
void loop() {
  
  
  int angle = getSteeringAngle(getSensorData());
  //Serial.println(angle);
  if(Serial.available()){
    String s = Serial.readStringUntil('\n'); 
    taste = !taste;
    }
  if(taste) {
    callibriereThreshold();
    taste = false;
    }
    
  
  //break_vehicle(angle);
  //Serial.print(angle);
  
  /*Serial.print(~getSensorData() + (1 << 17), BIN);
  Serial.print(" ");
  Serial.print(getLastMiddleOfLine());
  Serial.print(" ");*/

  if(fullLine()) Serial.println("G");
  else if(halfLineLeft()) Serial.println("R");
  else if(halfLineRight()) Serial.println("L");
  else Serial.println(" ");
 
  turn_servo(angle);

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
  int rotation_angle = steeringOrientation(getSensorData());
  if (rotation_angle != 0) {
    break_vehicle(rotation_angle);
  }
  turn_servo(rotation_angle);
  drive(); */
}
