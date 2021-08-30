#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include <Arduino.h>

/**
 * Binds all pins given to its designated role.
 * 
 *@param pinnum1 the first motor controll pin
 *@param pinnum2 the second motor controll pin
 *@param tastenum the Pin for the Button (34) is now input.
 *@param eepnum just enable in the start, corresponds to the eep
 *@param ultnum  just enable in the start, corresponds to the ult 
 */
void initial_motor(int pinnum1, int pinnum2, int ultnum, int eepnum, int taste);

/**
 *  Slows the vehicle when cornering mapped to the current rotation angle as input
 *
 *  @param rotationAngle : current rotation angle deduced from Sensors
 */
void break_vehicle(int rotationAngle);

/*
 * starts the motor with the given speed in the forward direction
 * @param value : speed to set
 */
void drive_forward(int value);

/**
 * dirve backward.. for later when someone need it 
 */
void drive_backward(int value);

/*
 * Turns the motor off.
 */
void turn_motor_off();

/*
 * Drives the vehicle when button is pressed
 * @param speed : speed at with to drive
 */
void drive(int speed);

#endif //DRIVECONTROL_H