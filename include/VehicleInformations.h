#ifndef VEHICLEINFORMATIONS_H
#define VEHICLEINFORMATIONS_H

#pragma once
#include <stdlib.h>

int translateValues(__uint16_t interface);
__uint8_t getLaneInfos(unsigned char lane_change, unsigned char right_angle, unsigned char r_l_curve);
__uint8_t getSpeed(unsigned int speed);
__uint8_t getAngle(int rotation);
__uint16_t getSensors(__uint16_t sensors);

extern __uint64_t vehicle_information;

#endif //VEHICLEINFORMATIONS_H