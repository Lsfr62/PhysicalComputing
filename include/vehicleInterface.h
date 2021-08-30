#ifndef VEHICLEINFORMATIONS_H
#define VEHICLEINFORMATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include "driveControl.h"
#include "steeringControl.h"

/* the right shift operation is used to set the bits */
#define SHIFT(info, bits) (((__uint64_t) info) << bits)
/* the last/64th bit is used for the lane change value => 1 if there is a lane change, otherwise 0 */
#define SHIFT_LANE_CHANGE(infos, c) (c == 'Y' ? (SHIFT(1, 63) | (infos)) : infos)
/* the 63th bit is used for the right angle => 1 if there is a right angle, otherwise 0*/
#define SHIFT_RIGHT_ANGLE(infos, c) (c == 'Y' ? (SHIFT(1, 62) | (infos)) : infos)
/* the 62th bit is used for the right/left curve => 1 if the it is a right curve, 0 if it is a left one */
#define SHIFT_RIGHT_CURVE(infos, c) (c == 'R' ? (SHIFT(1, 61) | (infos)) : infos)  
/* the 56th bit is used for the sign of the rotation angle => 1 if it is minus, 0 if positive */
#define SHIFT_SIGN(value) (value < 0 ? SHIFT(1, 55) : 0)
/* the bits 55-49 are used for the rotation angle */
#define SHIFT_ROTATION_ANGLE(infos, angle) ((angle < 0 ? SHIFT(-1 * angle, 48) : SHIFT(angle, 48)) | infos)
/* the bits 48-41 are used for the speed */
#define SHIFT_SPEED(infos, value) (SHIFT(value, 40) | infos)
/* the bits 40-25 are used for the sensors */
#define SHIFT_SENSORS(infos, value) (SHIFT(value, 24) | infos)

extern __uint64_t vehicle_information;

/** 
 * Takes an Integer as Input and return an array with the corresponding bits
 * @param x is the int value
 * @return an array with the bits if x
*/
char * showbits(__uint64_t x);

/*
 * Refreshes and reports the state of the Vehicle
 * @param lane_change the lane should be changed, value: 'Y', 'N'
 * @param right_angle a right curve is comming, value: 'Y', 'N'
 * @param right_left_curve the curve is goning right or left, value: 'R', 'L'
 * @param rotation_angle the angle, the servo is rotated
 * @param speed the speed of the vehicle
 * @param sensors an int of 16 bits
 * @return vehicle state, see documentation for Interface description 
*/
uint64_t refreshInformations(unsigned char lane_change, unsigned char right_angle, unsigned char right_left_curve, 
                         int rotation_angle, unsigned int speed, __uint16_t sensors);


/**
 * takes a serial input and use
 * @param input Each bit from left to right has a specific meaning: 
 * first bit 1 = negative angle, first bit 0 = positive angle. 
 * next 7 bits = absolute value of angle. should be between 0 and 35
 * next  8 Bits = speed for motor
*/
void contolVehicleSerial(uint16_t input);

/**
 * controls vehicl manually
 * @param speed is spped of motor, @param angle is angle the car is orienting to
*/
void contolVehicleManual();

#endif //VEHICLEINFORMATIONS_H