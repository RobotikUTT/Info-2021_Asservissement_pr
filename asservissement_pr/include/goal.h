/**
 * \file goal.h
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#ifndef GOAL_H
#define GOAL_H
#include "robotstate.h"
#include "parameters.h"

/**
 * \brief Mother goal class. Represents an empty goal.
**/


class Goal {
public:
    /**
     * \brief Sends the position error to @see control.h.
     * subclasses must override this function.
    **/
    virtual void process() {
        reached = true;
        Serial.println("Goal::process()");
    }

    inline bool isReached() const { return reached;
    // TODO Save gob
     }
    
protected:
    bool reached = false;
};

/**
 * \brief Rotates to a given angle in radians.
**/
class Rot : public Goal {
public:
    Rot() = delete;
    Rot(char type, float theta) : Goal(), type(type), theta(theta) {}

    virtual void process();

private:
    float theta; // rad
    char type ;
};

/**
 * \brief Goes to a given (x,y) absolute position in mm
**/
class Goto : public Goal {
public:
    Goto() = delete;

    /**
     * \brief constructor of Goto order.
     * \param x x coordinate in mm
     * \param y y coordinate in mm
     * \param maxSpeed max speed at which we want to go in mm/s. Cannot exceed MAX_SPEED. 0 for default.
    **/
    Goto(char type, float x, float y, float maxSpeed = 0) : Goal(), type(type), x(x), y(y), maxSpeed(maxSpeed) {}

    //virtual void isReached();
    virtual void process();

private:
    float x, y, maxSpeed; // mm, mm, mm/s
    char type ;
};

// add new goals here and override process()

#endif // GOAL_H
