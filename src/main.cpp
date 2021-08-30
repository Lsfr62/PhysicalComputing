#include "main.h"

bool taste = false;

void setup() {
  Serial.begin(baudRate);
  initial_motor(15, 21, 22, 23,34);
  initialize_servo(19);
  sensorSetup();
}

void loop() {

  //Starts DC-motor, when button is pressed 
  if(Serial.available()){
    String s = Serial.readStringUntil('\n'); 
    taste = !taste;
    }

  // Starts SensorCallibrations, when key on an attached Computer is pressed
  if(taste) {
    callibriereThreshold();
    taste = false;
    }

  //Debug output for 90°-Corner (G), lane switch right (R) and lane switch left (L) 
  if(fullLine()) Serial.println("G");
  else if(halfLineLeft()) Serial.println("L");
  else if(halfLineRight()) Serial.println("R");
  else Serial.println(" ");

  //Drive Sequenz for simple line following
  uint16_t sensorData = getSensorData();
  int rotationAngle = steeringOrientation(sensorData);
  turn_servo(rotationAngle);
  drive(200);
  
}