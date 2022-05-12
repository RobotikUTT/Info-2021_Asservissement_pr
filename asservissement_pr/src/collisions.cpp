

#include "robotstate.h"
//#include "goal.h"

#include "collisions.h"

#include "pins.h"

Collisions collisions;

void Collisions::update() {
    //float distToObstacle = readSensors(TRIG, ECHO); // mm // TODO fetch it from sensors
    float distToObstacle = 5000;
    //obst.ahead = readSensors(FORWARD_TRIG, FORWARD_ECHO);
    //obst.behind = readSensors(BACKWARDS_TRIG, BACKWARDS_ECHO);
    
   // maxSpeed = COLLISIONS_SPEED_COEFF * (distToObstacle - COLLISIONS_STOP_DISTANCE);
    
   // if (maxSpeed < 0) {
       // maxSpeed = 0;
   // }
     //Serial.println("Collisions::update()");
}

float Collisions::readSensors(short triggerpin, short echopin ){
	digitalWrite(triggerpin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerpin, LOW);
	float mesure = pulseIn(echopin, HIGH); 
	float distance = mesure/58;
	Serial.print("distance : ");
	Serial.println(distance);
	return distance ;
}

const float Collisions::getMaxSpeed(){
    maxSpeed = MAX_SPEED;
     return maxSpeed;
}
