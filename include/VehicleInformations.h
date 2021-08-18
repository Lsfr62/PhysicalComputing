#ifndef VEHICLEINFORMATIONS_H
#define VEHICLEINFORMATIONS_H

#pragma once

char * showbits(__uint64_t x);
void refreshInformations(unsigned char lane_change, unsigned char right_angle, unsigned char right_left_curve, 
                         int rotation_angle, unsigned int speed, __uint16_t sensors);

extern __uint64_t vehicle_information;

#endif //VEHICLEINFORMATIONS_H