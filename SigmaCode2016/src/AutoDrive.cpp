/*
 * AutoDrive.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */
#include <AutoDrive.h>

AutoDrive::AutoDrive(SigmaDrive* drive) {
	drive108 = drive;
}

AutoDrive::~AutoDrive(){};

void AutoDrive::driveStraight(double d, double t, bool stopWhenDone){
		//currentSpeed = drive108.getSpeed();
		desiredSpeed = d/t;
		//double accelVal = (desiredSpeed - currentSpeed)/t;
		//SmartDashboard.putNumber("acceleration Cap: ", accelVal);
		setValue = desiredSpeed/LowGearMaxSpeed;
		while(!finished){
			drive108->tankDrive(setValue*12, setValue*12);
			Wait(0.005);
			drive108->UpdateDiplacement(0.005);
			if(drive108->GetDisplacement() <= d+6 && drive108->GetDisplacement() >= d-6){
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
			drive108->tankDrive(0.0, 0.0);
		}
	}

void AutoDrive::turnOnSpot(double theta, double t){
		finished = false;
		arcRadius = DriveWidth;
		desiredSpeed = (arcRadius*theta)/t;
		distanceToTravel = desiredSpeed*t;
		setValue = desiredSpeed/LowGearMaxSpeed;
		while(!finished){
			drive108->tankDrive(setValue*12, -setValue*12);
			Wait(0.05);
			angle = drive108->gyro->GetAngle() + angle;
			drive108->gyro->Reset();
			if(angle <= theta+1 && angle >= theta-1){
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
		drive108->tankDrive(0.0,0.0);
	}

void AutoDrive::followArc(double r, double theta, double t, bool leftTurn, bool stopWhenDone){
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
		leftValue = leftSpeed/LowGearMaxSpeed;
		rightValue = rightSpeed/LowGearMaxSpeed;
		while(!finished){
			drive108->tankDrive(leftValue*12, rightValue*12);
			Wait(0.005);
			Ltravelled = (drive108->leftEncoder->GetRate()*wheelCircum)*0.005 + Ltravelled;
			Rtravelled = (drive108->rightEncoder->GetRate()*wheelCircum)*0.005 + Rtravelled;
			if(Ltravelled <= leftDTT+1 && Ltravelled >= leftDTT-1){
				if(Rtravelled <= rightDTT+1 && Rtravelled >= rightDTT-1){
					finished = true;
				}
			}
		}
		if(stopWhenDone){
			drive108->tankDrive(0.0, 0.0);
		}
}
