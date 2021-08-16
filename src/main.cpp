#include <Arduino.h>
#include <steeringControl.h>
#include <reflectanceSensor.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2
unsigned long convToBin(unsigned int);

void setup() {
  Serial.begin(115200);
  initialize_servo(15);
  pinMode(13, OUTPUT);
  sensorSetup();
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
  //sensorUpdate();
  //int x = getSensorData;
  Serial.println((int)getSensorData(), BIN);
  Serial.println("Stop");
}

