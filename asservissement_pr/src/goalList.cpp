
#include "robotstate.h"
#include "goalList.h"

#include "control.h"

GoalList goalList;

extern Control control;

void GoalList::resetGoals() {
    currentGoalIndex = 0;
    lastGoalIndex = 0;
    goals[currentGoalIndex] = Goal();
    Serial.println("GoalList::resetGoals()");
}

/*void GoalList::processCurrentGoal() {
    if (goals[currentGoalIndex].isReached() && currentGoalIndex != lastGoalIndex) {
        currentGoalIndex = (currentGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
        control.resetPIDs();
    }
    Serial.println("GoalList::processCurrentGoal()");
    //goals[currentGoalIndex].process();
    gProcess(goals[currentGoalIndex]);
}*/

void GoalList::processCurrentGoal() {
    if (goalsPtr[currentGoalIndex]->isReached() && currentGoalIndex == lastGoalIndex){
        if (currentGoalIndex == lastGoalIndex) {
            Serial.println("isReached()");
            exit(0);
        }
        else{
            currentGoalIndex = (currentGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
            control.resetPIDs();
            Serial.println("isReached()");
        }
    }
    else{
        //gProcess(*goalsPtr[currentGoalIndex]);
        goalsPtr[currentGoalIndex]->process();
    }
    
    //Serial.println("GoalList::processCurrentGoal()");
    //goals[currentGoalIndex].process();
    //gProcess(*goalsPtr[currentGoalIndex]);
}



void GoalList::addGoal(Goal* goal) {
    lastGoalIndex = (lastGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
    delete goalsPtr[lastGoalIndex];
    goalsPtr[lastGoalIndex] = goal;
    //Serial.println("GoalList::addGoal(Goal goal)");
    Serial.print("lastGoalIndex : ");
    Serial.println(lastGoalIndex);
}


void GoalList::gProcess(Goal const& goal){
    Serial.println("GoalList::gProcess(Goal const& goal)");
    goal.process();
    //(*goalsPtr[lastGoalIndex]).process();
}
