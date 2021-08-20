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
 * @param right_angle
*/
__uint8_t getLaneInfos(unsigned char line_change, unsigned char right_angle, unsigned char r_l_curve);
__uint8_t getSpeed(unsigned int speed);
__uint8_t getAngle(int rotation);
__uint16_t getSensors(__uint16_t sensors);

extern __uint64_t vehicle_information;

#endif //VEHICLEINFORMATIONS_H