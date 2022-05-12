/**
 * \file parameters.h
 * \brief All parameters used for  asserv_pr
**/
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Main loop
#define RATE_HZ 1000 // Hz
#define TIMER_MS 1000.0 / (float)RATE_HZ // ms
#define DEBUG 0
// Goals list
#define MAX_SIMULTANEOUS_GOALS 50

// Speed constants
#define MAX_SPEED 1000 // mm/s
#define MAX_ACCEL 15000 // mm/s^2
#define MAX_ACCELERATION_DIFFERENCE 100//MAX_ACCEL / RATE_HZ // mm/s
#define BRAKE_COEFF 0.3 // brakes BRAKE_COEFF times more than accelerates
#define MAX_BRAKE_DIFFERENCE MAX_ACCELERATION_DIFFERENCE * BRAKE_COEFF // mm/s
#define MAX_PWM_DIFFERENCE 30

// Robot state
#define WHEEL_DIAMETER 56 // mm
#define TICKS_PER_ROTATION (48 * 47)
#define DISTANCE_PER_TICK WHEEL_DIAMETER * 3.14159265358979323846 / TICKS_PER_ROTATION

#define ENTRAXE 217 // mm

// Collisions
#define COLLISIONS_SPEED_COEFF 0.5 
#define COLLISIONS_STOP_DISTANCE 150 // mm

// Goals
#define DIST_ERROR_TOLERANCE 10 // mm
#define THETA_ERROR_TOLERANCE 0.01 // rad


#endif // PARAMETERS_H
