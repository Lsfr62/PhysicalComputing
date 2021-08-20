#ifndef VEHICLEINFORMATIONS_H
#define VEHICLEINFORMATIONS_H

#pragma once
#include <stdlib.h>

/**
 * @param interface is a 16 bit int, which includes the rotation angle and the speed
 * @return 1 if it is successfuly runed, 0 if not
 * in this function can a 2-byte int translated in two values (speed, angle). 
 * The functions turn_survo and drive_forward will be called with values speed and angle
 * How should be the 2-byte int built? it is 16 bits 00000000 00000000
 * The first 8 bits will be to the angle translated: last bit for the sign and the rest are for the value
 * The last 8 bits are to the speed translated
*/
int translateValues(__uint16_t interface);

/**
 * @param line_change is the info if the car have to change the line, value = 'Y' for yes or 'N'
 * @param right_angle indicates whether a 90-degree curve is coming soon
 * @param r_l_curve indicated whether a right-curve or left-curve is coming, value = 'R', 'L'
 * @return 8-bit int, which includes the informations in bits
 * In this function are the values in a 8-bit int translated, 00000000 only the last 3 bits are needed
 * The last bit is for the line change
 * The 6th bit (1 if Y) for the right_angle (1 if Y) 
 * The 5th one for r_l_curve (1 if R)
*/
__uint8_t getLaneInfos(unsigned char line_change, unsigned char right_angle, unsigned char r_l_curve);

/**
 * @param speed is value of the speed 0 - 255 
 * @return 8-bit int, which includes the value of the speed
*/
__uint8_t getSpeed(unsigned int speed);

/**
 * @param rotation is rotation angle value -35 - 35
 * @return 8-bit int, that includes the value of the angle. 
 * The last bit is translated to the sign (1 negative, 0 positive value)
 * The rest bits are the positive value
*/
__uint8_t getAngle(int rotation);

/**
 * @param sensors a 16-bit int, that includes the value of the 16 sensors
 * @return the sensors 
*/
__uint16_t getSensors(__uint16_t sensors);

#endif //VEHICLEINFORMATIONS_H