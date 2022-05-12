
/*
 * \file asservissement_pr.ino
 * \brief Holds the arduino setup and loop functions, which make the asserv run.
*/


#include <SimpleTimer.h>
#include "parameters.h"
#include "goalList.h"
#include "robotstate.h"
#include "collisions.h"
#include "goal.h"
#include <Arduino.h>


//Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
//Encoder leftEnc = Encoder(A_LEFT, B_LEFT);
extern RobotState robotState;
extern Collisions collisions;
extern GoalList goalList;

SimpleTimer timer = SimpleTimer();


void debug(){
  Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
  Encoder leftEnc = Encoder(A_LEFT, B_LEFT);

  while (!digitalRead(INTER)){
        digitalWrite(FORWARD_LEFT, LOW);
        digitalWrite(BACKWARDS_LEFT, HIGH);
        analogWrite(PWM_LEFT, 83);

        digitalWrite(FORWARD_RIGHT, HIGH);
        digitalWrite(BACKWARDS_RIGHT, LOW);
        analogWrite(PWM_RIGHT, 100);
        int leftTicks = leftEnc.read();
        int rightTicks = - rightEnc.read();
        Serial.print("leftEnc.read() : ");
        Serial.println(leftEnc.read());
        Serial.print("- rightEnc.read() : ");
        Serial.println(- rightEnc.read());
        delay(500);
   }
  
}
void fillGoals() {
    // TODO add goal dynamically with ros or custom serial / CAN protocol
    // or fetch all goals from xml / json / whatever
    goalList.addGoal( new Goto(1,500, 0.0, 300));
    goalList.addGoal(new Rot(0,3.14/2));
    goalList.addGoal( new Goto(1, 500.0, 500.0, 300));
    goalList.addGoal(new Rot(0,3.14));
    goalList.addGoal( new Goto(1, 0.0, 500.0, 300));
    goalList.addGoal(new Rot(0,(3*3.14)/2));
    goalList.addGoal( new Goto(1,0.0, 0.0, 200));
    goalList.addGoal(new Rot(0,0.0));
    //goalList.addGoal(new Goto(0, 1000, 1000));
    //goalList.addGoal(new Rot(3.14/2));
    //goalList.addGoal(new Goto(-1000, 0));
    //goalList.addGoal(new Rot(3.14/2));
    //goalList.addGoal(new Goto(0, -1000));

}

void asservLoop() {
    robotState.update();
    collisions.update();
    goalList.processCurrentGoal();  
}
void setup() {
    Serial.begin(115200);
    timer.setInterval(TIMER_MS, asservLoop);
    fillGoals();
    pinMode(INTER, INPUT_PULLUP);
    
}

void loop(){  
  timer.run();

}



