/**
 * \file control.h
 * \brief Class which sends PWM values to motors to regulate them at given speeds.
**/

#ifndef CONTROL_H
#define CONTROL_H

#include "pid.h"

class Control {
public:
    /**
     * \brief updates the motor speeds according to the given errors.
     * \param distanceError distance from the goal in mm
     * \param thetaError angle difference in rad
     * \param maxSpeed maximum speed constraint, 0 for default.
    **/
    void updateSpeeds(float distanceError, float thetaError, float maxSpeed = 0);
    void resetPIDs();
    
private:
    PID linearPID = PID(.8, .4, .4, 5000);
    PID angularPID = PID(.8, 0, 0, 0);
    PID leftWheelPID = PID(.4, .5, 0, 1000);
    PID rightWheelPID = PID(.4, .5, 0, 1000);

    float targetLinearSpeed = 0;
    float targetAngularSpeed = 0;

    void updatePWM();
};

#endif // CONTROL_H
