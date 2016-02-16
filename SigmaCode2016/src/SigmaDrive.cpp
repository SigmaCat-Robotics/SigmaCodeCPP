/*
 * SigmaDrive.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#include "SigmaDrive.h"
#include "WPILib.h"


SigmaDrive::SigmaDrive(){

	left1 = new CANTalon(1);
	left2 = new CANTalon(2);
	right1 = new CANTalon(3);
	right2 = new CANTalon(4);

	left1->SetControlMode(CANSpeedController::kVoltage);
	left2->SetControlMode(CANSpeedController::kFollower);

	left2->Set(1);

	right1->SetControlMode(CANSpeedController::kVoltage);
	right2->SetControlMode(CANSpeedController::kFollower);

	right2->Set(3);

	left1->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	left2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	right1->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	right2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

	left1->SetFeedbackDevice(CANTalon::QuadEncoder);
	right1->SetFeedbackDevice(CANTalon::QuadEncoder);

	left1->ConfigEncoderCodesPerRev(400);
	right1->ConfigEncoderCodesPerRev(400);
	right1->SetSensorDirection(true);

	left1->ConfigPeakOutputVoltage(+12, -12);
	right1->ConfigPeakOutputVoltage(+12, -12);
	left1->ConfigNominalOutputVoltage(+0, -0);
	right1->ConfigNominalOutputVoltage(+0, -0);

	drive108 = new RobotDrive(left1, right1);

	Shifter = new DoubleSolenoid(0,1);

	accel = new ADXL362(ADXL362::kRange_4G);
	gyro = new ADXRS450_Gyro();
}

SigmaDrive::~SigmaDrive(){

}

void SigmaDrive::shiftToLow(){
	Shifter->Set(DoubleSolenoid::kForward);
}

void SigmaDrive::shiftToHigh(){
	Shifter->Set(DoubleSolenoid::kReverse);
}

void SigmaDrive::changeGears(){
	highGear = (Shifter->Get());
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

void SigmaDrive::tankDrive(Joystick* lStick, Joystick* rStick){
	double left ,right;
	if(Shifter->Get() == DoubleSolenoid::kForward){
		left = lStick->GetY() * maxSpeedLow;
		right = rStick->GetY() * maxSpeedLow;
	}else{
		left = lStick->GetY() * maxSpeedHigh;
		right = rStick->GetY() * maxSpeedHigh;
	}
	drive108->TankDrive(lStick->GetY()*12,rStick->GetY()*12);
}

void SigmaDrive::setExpiration(double value){
	drive108->SetExpiration(value);
}

void SigmaDrive::UpdateDiplacement(int updateRate){
		double accelGs = accel->GetX();
		double sampleTime = 1/updateRate;
		double accelIS2 = ((accelGs*9.80665)*3.28084)*12;
		double currentVel = lastVel + (accelIS2 * sampleTime);
		displacement = lastVel + (0.5 * accelIS2 * sampleTime * sampleTime);
		lastVel = currentVel;
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

void SigmaDrive::DriveDistance(double distance){

}
