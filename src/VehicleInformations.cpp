#include <stdio.h>
#include <stdlib.h>

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

__uint64_t vehicle_information;
/**
 * @param x is the int value
 * @return an array with the bits if x
*/
void showbits(__uint64_t x) {
    for (int i = 63; i >= 0; i--) {
        putchar(x & (1uLL << i) ? '1' : '0');
        if (i % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

/**
 * @param lane_change the lane should be changed, value: 'Y', 'N'
 * @param right_angle a right curve is comming, value: 'Y', 'N'
 * @param right_left_curve the curve is goning right or left, value: 'R', 'L'
 * @param rotation_angle the angle, the servo is rotated
 * @param speed the speed of the vehicle
 * @param sensors an int of 16 bits
 * In this functions are the informations of the vehicle saved into a 64-bit int. Only the last 48 bits are used
*/
void refreshInformations(unsigned char lane_change, unsigned char right_angle, unsigned char right_left_curve, 
                         int rotation_angle, unsigned int speed, __uint16_t sensors) {
    vehicle_information = 0;
    vehicle_information = SHIFT_LANE_CHANGE(vehicle_information, lane_change);
    vehicle_information = SHIFT_RIGHT_ANGLE(vehicle_information, right_angle);
    vehicle_information = SHIFT_RIGHT_CURVE(vehicle_information, right_left_curve);
    vehicle_information = SHIFT_SIGN(rotation_angle) | vehicle_information;
    vehicle_information = SHIFT_ROTATION_ANGLE(vehicle_information, rotation_angle);
    vehicle_information = SHIFT_SPEED(vehicle_information, speed);
    vehicle_information = SHIFT_SENSORS(vehicle_information, sensors);
    
    // showbits(vehicle_information);
}

