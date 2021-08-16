/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <reflectanceSensor.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2
unsigned long convToBin(unsigned int);


void setup()
{

  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(13, OUTPUT);
  sensorSetup();
}

void loop()
{
  //sensorUpdate();
  //int x = getSensorData;
  Serial.println((int)getSensorData(), BIN);
}
