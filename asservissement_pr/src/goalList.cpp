
#include "robotstate.h"
#include "goalList.h"
#include "pins.h"
#include "control.h"

GoalList goalList;

extern Control control;

void GoalList::resetGoals() {
    currentGoalIndex = 0;
    lastGoalIndex = 0;
    goalsPtr[currentGoalIndex] = new Goal();
}

void end(){
    digitalWrite(FORWARD_LEFT, 0);
    digitalWrite(BACKWARDS_LEFT, LOW);
    digitalWrite(FORWARD_RIGHT, LOW);
    digitalWrite(BACKWARDS_RIGHT, 0);
    while (true){
        
    }
}

void GoalList::processCurrentGoal() {
    if (goalsPtr[currentGoalIndex]->isReached()){
        if (currentGoalIndex == lastGoalIndex) {
            end();
            
        }
        else{
            currentGoalIndex = (currentGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
            control.resetPIDs();
            
        }
    }
    else{
        goalsPtr[currentGoalIndex]->process();

    }
    //Serial.print("currentGoalIndex : ");
    //Serial.println(currentGoalIndex);
}



void GoalList::addGoal(Goal* goal) {
    Serial.print("lastGoalIndex : ");
    lastGoalIndex = (lastGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
    delete goalsPtr[lastGoalIndex];
    goalsPtr[lastGoalIndex] = goal;
    if(goal->isReached()){

        Serial.println("already");
    }
    Serial.println(lastGoalIndex);
}


void GoalList::gProcess(Goal const& goal){
    goal.process();
}
