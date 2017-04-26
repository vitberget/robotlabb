#ifndef MOTORS_H
#define MOTORS_H
#endif

#define ON 1
#define OFF 0

#define LEFT_SPEED 4
#define LEFT_FORWARD 7
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 5
#define RIGHT_REVERSE 6

#ifdef VERSION2

#define LEFT_SPEED 4
#define LEFT_FORWARD 9
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 7
#define RIGHT_REVERSE 6
#endif

void motors_setup();
void motors(int leftSpeed, int rightSpeed);
