#include "goal.h"

#include <math.h>
#include "control.h"
#include "robotstate.h"

extern RobotState robotState;
extern Control control;


void Rot::process() {
    float thetaError = theta - robotState.getPose().theta;
    if (abs(thetaError) < THETA_ERROR_TOLERANCE) {
        reached = true;
    }
    //Serial.println("Rot::process()");
    control.updateSpeeds(0, thetaError);
}

void Goto::process() {

    float dx = x - robotState.getPose().x;
    float dy = y - robotState.getPose().y;
    /*Serial.print("dx: ");
    Serial.println(dx );
    Serial.print("dy: ");
    Serial.println(dy);*/

    float distanceError = sqrt(pow(dx, 2) + pow(dy, 2));
    float thetaError = atan2(dy, dx) - robotState.getPose().theta;
    //thetaError = fmod(thetaError, 2*M_PI);

    if (distanceError < DIST_ERROR_TOLERANCE){ //&& abs(thetaError) < THETA_ERROR_TOLERANCE ) {
        reached = true;
        Serial.println("Goto Reached");
        /*while (true){
            Serial.println("-----DONE-----");
        }*/
    }

    /*if (thetaError < THETA_ERROR_TOLERANCE  && type==0) {
        // rotate only
        distanceError = 0;
    }*/ 
    //Serial.println("Goto::process()");
    /*Serial.print("thetaError: ");
    Serial.println(thetaError);
    Serial.print("dError: ");
    //Serial.println(distanceError);*/
    control.updateSpeeds(distanceError, thetaError, maxSpeed);
}

