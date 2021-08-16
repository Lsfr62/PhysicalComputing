#include <Arduino.h>
#include <steeringControl.h>

void setup() {
  Serial.begin(115200);
  initialize_servo(15);
}

void loop() {
  Serial.println("Start");
  if(turn_servo(141) == 1)
    Serial.println("ERROR");
  delay(2000);
  Serial.println("Stop");
}