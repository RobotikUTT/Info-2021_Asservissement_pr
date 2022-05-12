#include "robotstate.h"
#include <math.h>
#include "parameters.h"

RobotState robotState;
Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
Encoder leftEnc = Encoder(A_LEFT, B_LEFT);
static int leftLastTicks = 0, rightLastTicks = 0, t_1 =0, dt = 0; 

void RobotState::update() {
    int leftTicks = leftEnc.read();
    int rightTicks = -rightEnc.read();

    
    
    
    int t = millis() ;
   
    dt = t - t_1;
    float dLeft = (float)(leftTicks - leftLastTicks)*DISTANCE_PER_TICK ; //mm
    float dRight = (float)(rightTicks - rightLastTicks)*DISTANCE_PER_TICK;
    wheelSpeeds.left = (1000*dLeft) /(dt);   // mm/s
    wheelSpeeds.right = (1000*dRight) /(dt); // mm/s
    
    float dAngle = atan2((dRight - dLeft), ENTRAXE);
    pose.theta += dAngle;
    pose.theta = fmod(pose.theta, 2 * M_PI);

    float dDistance = (dRight + dLeft) / 2.0;
    static float lastAngle = 0;
    float meanTrajAngle = (pose.theta + lastAngle) / 2.0;

    pose.x += dDistance * cos(meanTrajAngle); 
    pose.y += dDistance * sin(meanTrajAngle);
    
    if (DEBUG)
    {
        Serial.print("leftEnc.read() : ");
        Serial.println(leftTicks);
        Serial.print("- rightEnc.read() : ");
        Serial.println(rightTicks);
        
        Serial.print("leftLastTicks : ");
        Serial.println(leftLastTicks);
        Serial.print("-rightLastTicks : ");
        Serial.println(rightLastTicks);
        Serial.print("wheelSpeeds.left : ");
        Serial.println(wheelSpeeds.left);
        Serial.print("wheelSpeeds.right ");
        Serial.println(wheelSpeeds.right);
        Serial.print("theta : ");
        Serial.println(pose.theta);
        
        Serial.print("X : ");
        Serial.println(pose.x);
        Serial.print("Y : ");
        Serial.println(pose.y);
    }

    
    t_1 = t ;
    lastAngle = pose.theta;
    rightLastTicks = rightTicks;
    leftLastTicks = leftTicks;
    
}
