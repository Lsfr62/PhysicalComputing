// #ifndef DRIVECONTROL_H
// #define DRIVECONTROL_H

#pragma once

int initial_motor(int pinnum1, int pinnum2, int ultnum, int eepnum, int taste);
int drive_forward(int value);
int drive_backward(int value);
int turn_motor_off();
void drive();
void break_vehicle(int rotation_angle);
// #endif //DRIVECONTROL_H