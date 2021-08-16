#include <Arduino.h>
#include <steeringControl.h>

void setup() {
  Serial.begin(115200);
  initialize_servo(15);
}

void loop() {
  Serial.println("Start");
  // TEST: Es wird komplett nach links und dann nach Rechts gelenkt
  for (int i = 0; i < 36; i++) {
    turn_servo(i);
    delay(20);
  }

  for (int i = 0; i > -36; i--) {
    turn_servo(i);
    delay(20);
  }
  Serial.println("Stop");
}