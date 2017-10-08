#ifndef MOTORS_H
#define MOTORS_H
#endif

#define ON 1
#define OFF 0

#define RIGHT_SPEED 4
#define RIGHT_FORWARD 9
#define RIGHT_REVERSE 8

#define LEFT_SPEED 3
#define LEFT_FORWARD 6
#define LEFT_REVERSE 7


void motors_setup();
void motors(int leftSpeed, int rightSpeed);
