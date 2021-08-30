#include "vehicleInterface.h"


char * showbits(__uint64_t x) {
    char * buff = (char *) malloc(64); 
    for (int i = 63; i >= 0; i--) {
       buff[i] = (x & (1uLL << i) ? '1' : '0');
    }
    return buff;
}

uint64_t refreshInformations(unsigned char lane_change, unsigned char right_angle, unsigned char right_left_curve, 
                         int rotation_angle, unsigned int speed, __uint16_t sensors) {

    vehicle_information = SHIFT_LANE_CHANGE(vehicle_information, lane_change);
    vehicle_information = SHIFT_RIGHT_ANGLE(vehicle_information, right_angle);
    vehicle_information = SHIFT_RIGHT_CURVE(vehicle_information, right_left_curve);
    vehicle_information = SHIFT_SIGN(rotation_angle) | vehicle_information;
    vehicle_information = SHIFT_ROTATION_ANGLE(vehicle_information, rotation_angle);
    vehicle_information = SHIFT_SPEED(vehicle_information, speed);
    vehicle_information = SHIFT_SENSORS(vehicle_information, sensors);
    
    return vehicle_information;
}

/**
 * takes a serial input and use
 * @param input Each bit from left to right has a specific meaning: 
 * first bit 1 = negative angle, first bit 0 = positive angle. 
 * next 7 bits = absolute value of angle. should be between 0 and 35
 * next  8 Bits = speed for motor
*/
void contolVehicleSerial(uint16_t input) {
    int angle = 0;
    for(int i = 0; i < 7; i++) {
        if(((input & (1 << (i + 8))) != 0)){
        angle = angle +  (1 << i);
        }
    }
    angle = (angle > 35)? 35 : angle;
    angle = ((input & (1 << 15)) == 0)? angle:-angle ;

    int speed = 0;
    for(int i = 0; i < 8; i++) {
        speed = speed + (input & (1 << i));
    }

    contolVehicleManual(speed, angle);
}


/**
 * controls vehicle manually via two parameters
 * @param speed is spped of motor 
 * @param angle is angle the car is orienting to
*/
void contolVehicleManual(int speed, int angle) {
    drive(speed);
    turn_servo(angle);
}

