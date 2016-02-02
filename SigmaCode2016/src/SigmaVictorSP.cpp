/*
 * SigmaVictorSP.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Andrew
 */

#include "SigmaVictorSP.h"
#include "WPILib.h"
#include <cmath>
#include <algorithm>

SigmaVictorSP::SigmaVictorSP(int channel, bool acceleration, PIDSource *source){
			accel = acceleration;
			SmartDashboard::PutNumber("acceleration Cap: ", ACCEL_CAP);
			SmartDashboard::PutNumber("Accel Jump Value: ", ACCEL_VAL);
			victor = new Victor(channel);
			controller = new PIDController(p,i,d,this,source);
		}
SigmaVictorSP::SigmaVictorSP(int channel){
			accel = false;
			victor = new Victor(channel);
		}
void SigmaVictorSP::Set(double desiredOutput) {
			output = 0.0;
			if(!accel) {
				controller->SetSetpoint(desiredOutput);
			}
			else {
				//double ticksPerMs = enc.speed()/this.sensorIn.getLastTickLength();
				//double speedFraction = ticksPerMs / this.TOP_SPEED_IN_TICKS;
				//super.set(SigmaLib.limitValue(speed, speedFraction+0.5, speedFraction-0.5));
				ACCEL_CAP = SmartDashboard::GetNumber("acceleration Cap: ",ACCEL_CAP);
				ACCEL_VAL = SmartDashboard::GetNumber("Accel Jump Value: ",ACCEL_VAL);
				double sign = abs(desiredOutput) / desiredOutput;
				// less than jump-to val, go right to desired output
				if(abs(desiredOutput) < ACCEL_VAL) {
					output = desiredOutput;
				}
				// was going slower than the jump-to range, jump up
				else if(abs(prevOutput) < ACCEL_VAL) {
					output = ACCEL_VAL * sign;
				}
				else {
					// output capped by either what we want, or previous + ramp
					const double absDesiredOutput = abs(desiredOutput);
					const double absPrevOutput = abs(prevOutput) + ACCEL_CAP;
					output = std::min(absDesiredOutput, absPrevOutput) * sign;
				}
				prevOutput = output;
				controller->SetSetpoint(output);
			}

		}
void enableAcceleration(bool acceleration){
	accel = acceleration;
}
