/*
 * ShooterIntake.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Andrew
 */

#include <ShooterIntake.h>
#include "WPILib.h"

Talon *shooterWheel, *intakeMotor, *armMotor;
Encoder *shooterEncoder;
DigitalInput *upperLimit, *lowerLimit, *indexSwitch;
double maxSpeed, motorOutput;

ShooterIntake::ShooterIntake() {
	shooterWheel = new Talon(5);
	intakeMotor = new Talon(6);
	armMotor = new Talon(7);
	shooterEncoder = new Encoder(5,6);
	shooterEncoder->SetDistancePerPulse(6.05);
	upperLimit = new DigitalInput(7);
	lowerLimit = new DigitalInput(8);
	indexSwitch = new DigitalInput(9);

}

ShooterIntake::~ShooterIntake() {
	// TODO Auto-generated destructor stub
}

void ShooterIntake::Intake(){
	if(!indexSwitch->Get()){
		intakeMotor->Set(0.8);
	}
	else{
		intakeMotor->Set(0);
	}
}

void ShooterIntake::Release(){
	intakeMotor->Set(-0.3);
}

void ShooterIntake::Prime(){
	if(indexSwitch->Get()){
		shooterWheel->Set(0.8);
	}
	else{
		Wait(4.0);
		shooterWheel->Set(0);
	}
}

void ShooterIntake::Shoot(/*double desiredSpeed*/){
	//motorOutput = desiredSpeed/maxSpeed;
	if(ShooterIntake::ShooterRate()>4000){
		intakeMotor->Set(0.4);
		Wait(4.0);
		intakeMotor->Set(0);
	}
}

void ShooterIntake::LiftIntake(){
	if(!upperLimit->Get()){
		armMotor->Set(0.5);
	}
	else{
		armMotor->Set(0);
	}
}

void ShooterIntake::LowerIntake(){
	if(!lowerLimit->Get()){
		armMotor->Set(-0.5);
	}
	else{
		armMotor->Set(0);
	}
}

double ShooterIntake::ShooterRate(){
	return (shooterEncoder->GetRate()*1.21);
}

void ShooterIntake::ResetEncoder(){
	shooterEncoder->Reset();
}
