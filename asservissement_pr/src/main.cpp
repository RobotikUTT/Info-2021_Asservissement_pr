
/*
 * \file asservissement_pr.ino
 * \brief Holds the arduino setup and loop functions, which make the asserv run.
*/


//#include "SimpleTimer.h"
#include <Arduino.h>
#include <SimpleTimer.h>
#include <Encoder.h>

#include "parameters.h"
#include "goalList.h"
#include "robotstate.h"
#include "collisions.h"
#include "goal.h"



Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
Encoder leftEnc = Encoder(A_LEFT, B_LEFT);
extern RobotState robotState;
extern Collisions collisions;
extern GoalList goalList;

SimpleTimer timer = SimpleTimer();

void fillGoals() {
    // TODO add goal dynamically with ros or custom serial / CAN protocol
    // or fetch all goals from xml / json / whatever
    goalList.addGoal( new Goto(1000, 0));
    //goalList.addGoal(new Rot(3.14/2));
    //goalList.addGoal(new Goto(0, 1000));
    //goalList.addGoal(new Rot(3.14/2));
    //goalList.addGoal(new Goto(-1000, 0));
    //goalList.addGoal(new Rot(3.14/2));
    //goalList.addGoal(new Goto(0, -1000));
    //Serial.println("fillGoals");
}

void asservLoop() {
  
    int leftTicks = leftEnc.read();
    int rightTicks = - rightEnc.read(); // minus sign because motors are in opposite directions
    robotState.update(leftTicks, rightTicks);  // update robostate after
    collisions.update();
    goalList.processCurrentGoal();
    Serial.println("asservLoop");
    
}
void setup() {
    Serial.begin(9600);
    timer.setInterval(TIMER_MS, asservLoop);
    fillGoals();
}

void loop() {
         
        /*static bool a = true;
        if (a){
          timer.setInterval(TIMER_MS, asservLoop);
          fillGoals();
          a = false;
        }*/
       
        //Debug coders
        digitalWrite(FORWARD_LEFT, HIGH);
        digitalWrite(BACKWARDS_LEFT, LOW);
        analogWrite(PWM_LEFT, 100);

        digitalWrite(FORWARD_RIGHT, HIGH);
        digitalWrite(BACKWARDS_RIGHT, LOW);
        analogWrite(PWM_RIGHT, 100);
        //int leftTicks = leftEnc.read();
        //int rightTicks = - rightEnc.read();
        Serial.println(leftEnc.read());
        Serial.println(- rightEnc.read());
        delay(500);
        return;
        

  
  timer.run();
  Serial.println("loop");
  //delay(10);
  //fillGoals();
}



