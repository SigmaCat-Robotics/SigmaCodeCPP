/*
 * SigmaDrive.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#include "SigmaDrive.h"
#include "WPILib.h"

/*class SigmaDrive
{*/
	Talon *left1, *left2, *right1, *right2;
	DoubleSolenoid *leftShifter, *rightShifter;
	Encoder *leftEncoder, *rightEncoder;
	RobotDrive *drive108;
	BuiltInAccelerometer *accel;
	double driveSpeed = 0.0, lastVel = 0.0, displacement = 0.0;
	bool highGear = false;

/*public:*/
SigmaDrive::SigmaDrive() {
	left1 = new Talon(1);
	left2 = new Talon(2);
	right1 = new Talon(3);
	right2 = new Talon(4);

	drive108 = new RobotDrive(left1,left2, right1, right2);

	leftShifter = new DoubleSolenoid(0,1);
	rightShifter = new DoubleSolenoid(2,3);

	leftEncoder = new Encoder(1,2);
	rightEncoder = new Encoder(3,4);

	accel = new BuiltInAccelerometer();
}

SigmaDrive::~SigmaDrive(){

}

//private:
double SigmaDrive::getLeftDistance(){
	return leftEncoder->GetDistance();
}

double SigmaDrive::getRightDistance(){
	return rightEncoder->GetDistance();
}

void SigmaDrive::shiftToLow(){
	leftShifter->Set(DoubleSolenoid::kForward);
	rightShifter->Set(DoubleSolenoid::kForward);
}

void SigmaDrive::shiftToHigh(){
	leftShifter->Set(DoubleSolenoid::kReverse);
	rightShifter->Set(DoubleSolenoid::kReverse);
}

double SigmaDrive::getSpeed(){
	driveSpeed = ((leftEncoder->GetRate()+rightEncoder->GetRate())/2);
	return driveSpeed;
}

void SigmaDrive::resetEncoders(){
	leftEncoder->Reset();
	rightEncoder->Reset();
};

double SigmaDrive::getDistance(){
	return (getLeftDistance()+getRightDistance())/2;
}

void SigmaDrive::changeGears(){
	highGear = (leftShifter->Get() && rightShifter->Get());
	if(highGear){
		shiftToLow();
	}
	if(!highGear){
		shiftToHigh();
	}
}

void SigmaDrive::tankDrive(double leftValue, double rightValue){
	drive108->TankDrive(leftValue, rightValue);
	Wait(0.005);
}

	/*
void SigmaDrive::tankDrive(Joystick lStick, Joystick rStick){
	drive108->TankDrive(lStick,rStick);
}
	*/

void SigmaDrive::setExpiration(double value){
	drive108->SetExpiration(value);
}

void SigmaDrive::UpdateDiplacement(int updateRate){
	if(std::abs(SigmaDrive::getSpeed()) < 0.2){
		double accelGs = accel->GetX();
		double sampleTime = 1/updateRate;
		double accelIS2 = ((accelGs*9.80665)*3.28084)*12;
		double currentVel = lastVel + (accelIS2 * sampleTime);
		displacement = lastVel + (0.5 * accelIS2 * sampleTime * sampleTime);
		lastVel = currentVel;
	}
	else{
		lastVel = 0;
	}
}

void SigmaDrive::ResetDisplacement(){
	lastVel = 0;
	displacement = 0;
}

double SigmaDrive::GetVelocity(){
	return lastVel;
}

double SigmaDrive::GetDisplacement(){
	return displacement;
}



