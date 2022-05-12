#include "control.h"

#include "robotstate.h"
#include "collisions.h"

Control control;

extern RobotState robotState;
extern Collisions collisions;
static float lastSpeed = 0;
static int lastpwm = 0;
namespace { // private functions

float filterLinearSpeed(float speed, float maxSpeed = 0) {
    //Serial.println("filterLinearSpeed()");
    
    
    if (!maxSpeed) {
        maxSpeed = MAX_SPEED;
    }
    if (speed >= 0) {
        if (speed > collisions.getMaxSpeed()) {
            speed = collisions.getMaxSpeed();
        }
        if (speed > maxSpeed) {
                speed = maxSpeed;
        }
        if (speed - lastSpeed > MAX_ACCELERATION_DIFFERENCE) {
            speed = lastSpeed + MAX_ACCELERATION_DIFFERENCE;
        } else if (speed - lastSpeed < - MAX_BRAKE_DIFFERENCE) {
            //speed = lastSpeed - MAX_BRAKE_DIFFERENCE;
        }

        if (speed > maxSpeed) {
                speed = maxSpeed;
        }
    } else { // speed < 0 : going backwards
        if (speed < - collisions.getMaxSpeed()) {
            speed = - collisions.getMaxSpeed();
        }
        if (speed < - maxSpeed) {
            speed = - maxSpeed;
        }
        if (speed - lastSpeed < -MAX_ACCELERATION_DIFFERENCE) {
            speed = lastSpeed - MAX_PWM_DIFFERENCE;
        } else if (speed - lastSpeed > MAX_BRAKE_DIFFERENCE) {
            speed = lastSpeed + MAX_BRAKE_DIFFERENCE;
        }  
        if (speed < - maxSpeed) {
            speed = - maxSpeed;
        } 
    }

    
    /*Serial.print("speed : ");
    Serial.println(speed);*/
    lastSpeed = speed;
    return speed;
}

void sendPWM(PID pid, float error, int FORWARD_PIN, int BACKWARDS_PIN, int PWM_PIN) {
    
    int pwm;
    if (digitalRead(INTER)== LOW) {
        pwm = pid.output(error);
        
        if (pwm > 255) {
            pwm = 255;
        } else if (pwm < - 255) {
            pwm = - 255;
        }
        if (pwm - lastpwm > MAX_PWM_DIFFERENCE) {
            pwm = pwm + MAX_PWM_DIFFERENCE;
            
        } else if (pwm - lastpwm < - MAX_PWM_DIFFERENCE) {
            pwm = lastpwm - MAX_PWM_DIFFERENCE;
            
        }

        if (pwm >= 0) {
            digitalWrite(FORWARD_PIN, HIGH);
            digitalWrite(BACKWARDS_PIN, LOW);
            analogWrite(PWM_PIN, pwm);
        } else {
            digitalWrite(FORWARD_PIN, LOW);
            digitalWrite(BACKWARDS_PIN, HIGH);
            analogWrite(PWM_PIN, - pwm);
        }
   }
    else{
        digitalWrite(FORWARD_PIN, 0);
        digitalWrite(BACKWARDS_PIN, LOW);
        digitalWrite(FORWARD_PIN, LOW);
        digitalWrite(BACKWARDS_PIN, 0);
        //Serial.println("INTER: OFF");
    }
    Serial.print("lastPWM: ");
    Serial.println(lastpwm);
    lastpwm = pwm;
}

} // anonymous namespace

void Control::resetPIDs() {
    //Serial.println("Control::resetPIDs()");
    linearPID.resetErrors();
    angularPID.resetErrors();
    leftWheelPID.resetErrors();
    rightWheelPID.resetErrors();
}


void Control::updateSpeeds(float distanceError, float thetaError, float maxLinearSpeed) {
    targetLinearSpeed = filterLinearSpeed(linearPID.output(distanceError), maxLinearSpeed);
    targetAngularSpeed = angularPID.output(thetaError); // no collisions or speed check on angular speed
    updatePWM();
    //Serial.println(linearPID.output(distanceError));
}

void Control::updatePWM() {
    
    //Serial.print("targetLinearSpeed : ");
    //Serial.println(targetLinearSpeed);
    float targetLeftSpeed = targetLinearSpeed - targetAngularSpeed;
    float targetRightSpeed = targetLinearSpeed + targetAngularSpeed;
    float leftError = 0;
    float rightError =0;

    if (abs(robotState.getWheelSpeeds().left)>abs(targetLeftSpeed)){
        leftError = 0;
    }
    else {
        leftError = targetLeftSpeed - robotState.getWheelSpeeds().left;
    }
    if (abs(robotState.getWheelSpeeds().right)>abs(targetRightSpeed)){
        rightError =0;
    }
    else {
        rightError = targetRightSpeed - robotState.getWheelSpeeds().right;
    }
    sendPWM(leftWheelPID, leftError, FORWARD_LEFT, BACKWARDS_LEFT, PWM_LEFT);
    sendPWM(rightWheelPID, rightError, FORWARD_RIGHT, BACKWARDS_RIGHT, PWM_RIGHT);
}


