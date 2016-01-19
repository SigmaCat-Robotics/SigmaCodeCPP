/*
 * AutoDrive.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: Andrew
 */

#include <AutoDrive.h>

class AutoDrive
{
	SigmaDrive *drive108;
	double desiredSpeed = 0.0, leftSpeed = 0.0, rightSpeed = 0.0;
	double setValue = 0.0, leftValue = 0.0, rightValue = 0.0;
	double arcRadius = 0.0, leftRadius = 0.0, rightRadius = 0.0;
	double distanceToTravel = 0.0,leftDTT = 0.0,rightDTT = 0.0;
	double HighGearMaxSpeed = 0.0, LowGearMaxSpeed = 0.0, DriveWidth = 0.0;
	bool finished = false;

	AutoDrive(SigmaDrive drive) {
		drive108 = drive;
	}

	void driveStraight(double d, double t, bool stopWhenDone){
		//currentSpeed = drive108.getSpeed();
		desiredSpeed = d/t;
		//double accelVal = (desiredSpeed - currentSpeed)/t;
		//SmartDashboard.putNumber("acceleration Cap: ", accelVal);
		if(drive108->highGear){
			setValue = desiredSpeed/HighGearMaxSpeed;
		}else{
			setValue = desiredSpeed/LowGearMaxSpeed;
		}
		while(!finished){
			drive108->resetEncoders();
			drive108->tankDrive(setValue, setValue);
			//Timer.delay(t);
			if(drive108->getDistance() <= d+6 && drive108->getDistance() >= d-6){
				finished = true;
			}
			/*
			else{
				d = d - drive108.getDistance();
				t = d/desiredSpeed;
				this.driveStraight(d, t, stopWhenDone);
			}
			*/
		}
		if(stopWhenDone){
			drive108->tankDrive(0, 0);
		}
	}

	void turnOnSpot(double theta, double t){
		finished = false;
		arcRadius = DriveWidth;
		desiredSpeed = (arcRadius*theta)/t;
		distanceToTravel = desiredSpeed*t;
		if(drive108->highGear){
			setValue = desiredSpeed/HighGearMaxSpeed;
		}else{
			setValue = desiredSpeed/LowGearMaxSpeed;
		}
		while(!finished){
			drive108->resetEncoders();
			drive108->tankDrive(setValue, -setValue);
			Wait(0.5);
			if(drive108->getDistance() <= distanceToTravel+1 && drive108->getDistance() >= distanceToTravel-1){
				finished = true;
			}
			/*
			else{
				distanceToTravel = distanceToTravel - drive108->getDistance();
				t = distanceToTravel/desiredSpeed;
				this.turnOnSpot(theta, t);
			}
			*/
		}
	}

	void followArc(double r, double theta, double t, bool leftTurn, bool stopWhenDone){
		finished = false;
		arcRadius = r;
		if(leftTurn){
			leftRadius = r - (DriveWidth/2);
			rightRadius = r + (DriveWidth/2);
		}else{
			leftRadius = r + (DriveWidth/2);
			rightRadius = r - (DriveWidth/2);
		}
		leftDTT = leftRadius*theta;
		rightDTT = rightRadius*theta;
		leftSpeed = leftDTT/t;
		rightSpeed = rightDTT/t;
		desiredSpeed = (leftSpeed+rightSpeed)/2;
		if(drive108->highGear){
			leftValue = leftSpeed/HighGearMaxSpeed;
			rightValue = rightSpeed/HighGearMaxSpeed;
		}else{
			leftValue = leftSpeed/LowGearMaxSpeed;
			rightValue = rightSpeed/LowGearMaxSpeed;
		}
		while(!finished){
			drive108->resetEncoders();
			drive108->tankDrive(leftValue, rightValue);
			Wait(0.5);
			if(drive108->getLeftDistance() <= leftDTT+1 && drive108->getLeftDistance() >= leftDTT-1){
				if(drive108->getRightDistance() <= rightDTT+1 && drive108->getRightDistance() >= rightDTT-1){
					finished = true;
				}
			}
		}
		if(stopWhenDone){
			drive108->tankDrive(0, 0);
		}
	}

};


