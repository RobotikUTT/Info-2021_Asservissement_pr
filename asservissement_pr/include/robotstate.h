/**
 * \file robotstate.h
 * \brief Class which holds position and speed data and updates with coders.
**/

#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>
#include "pins.h"

typedef struct {float x, y, theta;} Pose;
typedef struct {float left, right;} WheelSpeeds;
typedef struct {int dleft, dright;} Delta;


class RobotState  {
public:
    /**
    * \brief Updates wheel speeds and pose from coders.
    **/
    void update();
    
    Delta getDelta(){
        return delta;
    }

    inline const Pose getPose() const { return pose; }
    inline const WheelSpeeds getWheelSpeeds() const { return wheelSpeeds; }

private:
    Delta delta = {0,0}; 
    Pose pose = {0, 0, 0}; // mm, mm, rad
    WheelSpeeds wheelSpeeds = {0,0}; // mm/s, mm/s

};

#endif
