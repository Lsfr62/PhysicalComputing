#include <stdio.h>
#include <stdlib.h>
#include <drivecontrol.h>
#include <steeringControl.h>

#define SHIFT8(info, bits) ((__uint8_t) info << bits)
#define SHIFT16(info, bits) ((__uint16_t) info << bits)
#define SHIFT16R(info, bits) ((__uint16_t) info >> bits)
#define GET_FIRST_8_BITS(info) SHIFT16R((info & ~SHIFT16(255, 0)), 8)
#define GET_LAST_8_BITS(info) (info & SHIFT16(255, 0))
#define GET_SIGN(info) (((__uint8_t) info) >> 7)
#define GET_SPEED(info) (((__uint8_t) info) & ~(1 << 7))

#define MAX_16_Bits 65535
#define MAX_8_Bits 255

__uint64_t vehicle_information;

/**
 * @param x is the int value
 * @return an array with the bits if x
*/
void showbits(unsigned int x, int bitsnum) {
    for (int i = bitsnum - 1; i >= 0; i--) {
        putchar(x & (1 << i) ? '1' : '0');
        if (i % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int translateValues(__uint16_t interface) {
    if (interface > MAX_16_Bits) {
        return 0;
    }

    unsigned int firstBits = GET_FIRST_8_BITS(interface);
    int angle = GET_SPEED(firstBits) * (GET_SIGN(firstBits) == 1 ? -1 : 1);
    turn_servo(angle);

    int speed = GET_LAST_8_BITS(interface);
    drive_forward(speed);
    return 1;
}

__uint8_t getLaneInfos(unsigned char line_change, unsigned char right_angle, unsigned char r_l_curve) {
    __uint8_t result;

    result  = line_change == 'Y' || line_change == 'y' ? SHIFT8(1, 7) : 0;
    result |= right_angle == 'Y' || right_angle == 'y' ? SHIFT8(1, 6) : 0;
    result |= r_l_curve   == 'R' || r_l_curve   == 'r' ? SHIFT8(1, 5) : 0;
    
    return result;
}

__uint8_t getSpeed(unsigned int speed) {
    return speed > 0 && speed <= MAX_8_Bits ? (__uint8_t) speed : 0;
}

__uint8_t getAngle(int rotation) {
    __uint8_t result;

    if (rotation < -35) {
        rotation = -35;
    } else if (rotation > 35) {
        rotation = 35;
    }

    result = rotation < 0 ? SHIFT8(1, 7) : 0;
    result |= abs(rotation);
    return result;
}

__uint16_t getSensors(__uint16_t sensors) {
    return sensors <= MAX_16_Bits ? sensors : 0;
}
