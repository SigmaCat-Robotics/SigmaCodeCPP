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

class SigmaVictorSP: public Victor
{

	public:
		bool accel = false;
		static double ACCEL_CAP = 0.01;
		static double ACCEL_VAL = 0.2;
		double prevOutput = 0.0;
		double output = 0;
		SigmaVictorSP(int channel, bool acceleration): Victor(channel){
			accel = acceleration;
			SmartDashboard::PutNumber("acceleration Cap: ", ACCEL_CAP);
			SmartDashboard::PutNumber("Accel Jump Value: ", ACCEL_VAL);
		}
		SigmaVictorSP(int channel){
				this(channel,false);
		}
		void set(double desiredOutput) {
			output = 0.0;
			if(!accel) {
					Victor::Set(output);
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
				Victor::Set(output);
			}

		}
		void enableAcceleration(bool acceleration){
			accel = acceleration;
		}
};
