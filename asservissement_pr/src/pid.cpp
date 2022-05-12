#include "pid.h"
#include "robotstate.h"

//extern RobotState robotState;



float PID::output(float newError) {
	updateErrors(newError);
	return P * error + I * errorSum + D * lastError;
}

void PID::updateErrors(float newError) {
	error = newError;
	errorSum += error;
	if (errorSum > maxIError) {
		//errorSum = maxIError;
		errorSum = 0;
	} else if (errorSum < - maxIError) {
		errorSum = - maxIError;
	}
	lastError = error;
}

void PID::resetErrors() {
	error = 0;
	lastError = 0;
	errorSum = 0;
}
