/*
 * SigmaDrive.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#include "SigmaDrive.h"
#include "WPILib.h"

class SigmaDrive
{
	SigmaVictorSP *left1, *left2, *right1, *right2;
	DoubleSolenoid *leftShifter, *rightShifter;
	SigmaEncoder *leftEncoder, *rightEncoder;
	RobotDrive *drive108;
	double driveSpeed = 0.0;
	bool highGear = false;

public:
	SigmaDrive() {
		left1 = new SigmaVictorSP(1,true);
		left2 = new SigmaVictorSP(2,true);
		right1 = new SigmaVictorSP(3,true);
		right2 = new SigmaVictorSP(4,true);

		drive108 = new RobotDrive(left1,left2, right1, right2);

		leftShifter = new DoubleSolenoid(0,1);
		rightShifter = new DoubleSolenoid(2,3);

		leftEncoder = new SigmaEncoder(true,false,1,2);
		rightEncoder = new SigmaEncoder(true,true,3,4);
	};

	double getSpeed(){
			SigmaDrive::driveSpeed = ((leftEncoder->GetRate()+rightEncoder->GetRate())/2);
			return SigmaDrive::driveSpeed;
	}

	void resetEncoders(){
			leftEncoder->Reset();
			rightEncoder->Reset();
	}

	double getDistance(){
		return (SigmaDrive::getLeftDistance()+SigmaDrive::getRightDistance())/2;
	}

	void changeGears(){
		highGear = (leftShifter->Get() && rightShifter->Get());
		if(highGear){
			shiftToLow();
		}
		if(!highGear){
			shiftToHigh();
		}
	}

	void tankDrive(double leftValue, double rightValue){
		drive108->TankDrive(leftValue, rightValue);
	}

	/*
	void tankDrive(Joystick lStick, Joystick rStick){
		drive108->TankDrive(lStick,rStick);
	}
	*/

	void setExpiration(double value){
		drive108->SetExpiration(value);
	}

private:
	double getLeftDistance(){
		return leftEncoder->GetDistance();
	}

	double getRightDistance(){
		return rightEncoder->GetDistance();
	}

	void shiftToLow(){
		leftShifter->Set(DoubleSolenoid::kForward);
		rightShifter->Set(DoubleSolenoid::kForward);
	}

	void shiftToHigh(){
		leftShifter->Set(DoubleSolenoid::kReverse);
		rightShifter->Set(DoubleSolenoid::kReverse);
	}

};


