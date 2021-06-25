/**
 * \file collisions.h
 * \brief Class which holds a maximal speed value based on the proximity of obstacles.
**/

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "parameters.h"

//typedef struct {float ahead, behind;} Obstacle;

class Collisions  {
public:
    /**
     * Updates the maximal speed based on the distance to the nearest obstacle.
    **/
    void update();
    float readSensors(short triggerpin, short echopin );
    inline const float getMaxSpeed() const { return maxSpeed; }
    
private:
    int maxSpeed = MAX_SPEED; // mm/s
    //Obstacle obst = {0,0};
};

#endif // COLLISIONS_H
