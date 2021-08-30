#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include "steeringOrientation.h"

/**
 * Store measurements in messwerte[] array.
*/
void sensorUpdate();
   
/**
 * prepares sensors for usage
*/
void sensorSetup();

/**
 * Gets data from sensor
 * 
 * @return integer of 16 Bits, where 1 = black, white = 0
 * 
 * Example function call: 
 * Serial.println((int)getSensorData(), BIN);
 * 
 * Warning: also returns 0, if sensor is not found
*/
uint16_t getSensorData();

/**
 * returns bool:  Has double orthogonal line been detected on left side of line?
 * 
 * @return Has double orthogonal line been detected on left side of line?
*/
bool halfLineLeft();

/**
 * returns bool:  Has double orthogonal line been detected on right side of line?
 * 
 * @return Has double orthogonal line been detected on right side of line?
*/
bool halfLineRight();

/**
 * returns bool:  Has double orthogonal line been detected on hole line?
 * 
 * @return Has double orthogonal line been detected on hole line?
*/
bool fullLine();

/**
 * Measures thresholds for every sensor after enter-key is pressed
*/
void callibriereThreshold();