#ifndef STEERINGORIENTATION_H
#define STEERINGORIENTATION_H

#include <Arduino.h>

/**
 * Gets the positions in as int and gives back pin with higest chance of
 * 
 * @param gets 16 bits long number representing the sensor inputs: 0 = sensor sees white, 
 * 1=sensor sees black
 * @return returns an Angle between -35 and 35 that can be given to the servo Motor
*/
int getLastMiddleOfLine();

/**
 * Gives the sensor in the middle of the line
 * @param positions represents the sensor data in a sequence of 1 and 0
 * @return returns the middle of the line. Calculates that a really big change from one messurement to the next is not realistic
*/
int steeringOrientation(uint16_t);

/**
* Gives angle for servo
* @param positions represents the sensor data in a sequence of 1 and 0
* @return an angle between -35 an d 35 degree, ready to give to the servo
*/
int getSteeringAngle(uint16_t);

/**
* gives back length of sequence of zeros from a given starting position. Example
* 1110000101 <- the third digit is a 1 and is followed by 4 zeros in a row. So the function call with position 3 would return 4. Not 5, because there is a 1 seperating the in total 5 zeros
* @param positions represents the sensor data in a sequence of 1 and 0, @param i is place in sequence to look at
* @return length of sequence of zeros from a given starting position
*/
int getNumbersOfZeros(uint16_t, int);

#endif //STEERINGORIENTATION_H