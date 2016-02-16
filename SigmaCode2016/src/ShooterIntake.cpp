/*
 * ShooterIntake.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Andrew
 */

#include "ShooterIntake.h"
#include "WPILib.h"

CANTalon *shooterWheel, *armMotor;
VictorSP *intakeMotor, *indexer1, *indexer2;
DoubleSolenoid *shootAim;
Encoder *shooterEncoder;
DigitalInput *upperLimit, *lowerLimit, *indexSwitch;
double maxShootSpeed = 5310, ShootOutput, ShootSpeed, ArmSpeed;

ShooterIntake::ShooterIntake() {
	shooterWheel = new CANTalon(5);
	intakeMotor = new VictorSP(9);
	armMotor = new CANTalon(6);
	shooterEncoder = new Encoder(5,6);
	shooterEncoder->SetDistancePerPulse(6.05);
	upperLimit = new DigitalInput(7);
	lowerLimit = new DigitalInput(8);
	indexSwitch = new DigitalInput(9);

	indexer1 = new VictorSP(2);
	indexer2 = new VictorSP(3);

	shooterWheel->SetControlMode(CANSpeedController::kVoltage);
	shooterWheel->ConfigPeakOutputVoltage(+12, -12);
	shooterWheel->ConfigNominalOutputVoltage(+0, -0);
	shooterWheel->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	armMotor->SetControlMode(CANSpeedController::kVoltage);
	armMotor->ConfigPeakOutputVoltage(+12, -12);
	armMotor->ConfigNominalOutputVoltage(+0, -0);
	armMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
}

ShooterIntake::~ShooterIntake() {
	// TODO Auto-generated destructor stub
}

void ShooterIntake::Intake(){
	if(!indexSwitch->Get()){
		intakeMotor->Set(0.8);
		indexer1->Set(0.2);
		indexer2->Set(-0.2);
	}
	else{
		intakeMotor->Set(0);
	}
}

void ShooterIntake::Release(){
	indexer1->Set(-0.2);
	indexer2->Set(0.2);
	intakeMotor->Set(-1.0);
}

void ShooterIntake::Prime(){
	if(indexSwitch->Get()){
		shooterWheel->Set(0.8*12);
	}
	else{
		Wait(4.0);
		shooterWheel->Set(0.0);
	}
}

void ShooterIntake::Shoot(/*double desiredSpeed*/){
	//motorOutput = desiredSpeed/maxSpeed;
	if(ShooterIntake::ShooterRate()>4000){
		indexer1->Set(0.4);
		indexer2->Set(-0.4);
		Wait(4.0);
		indexer1->Set(0.0);
		indexer2->Set(0.0);
	}
}

void ShooterIntake::LiftIntake(){
	armMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	if(!upperLimit->Get()){
		armMotor->Set(0.1*12);
	}
	else{
		armMotor->Set(0);
	}
}

void ShooterIntake::LowerIntake(){
	armMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	if(!lowerLimit->Get()){
		armMotor->Set(-0.5*12);
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

void ShooterIntake::StopIntake(){
	intakeMotor->Set(0);
}

void ShooterIntake::StopIndexer(){
	indexer1->Set(0);
	indexer2->Set(0);
}

void ShooterIntake::ShooterAim(bool high){
	if(!high){
		shootAim->Set(shootAim->kForward);
	}else{
		shootAim->Set(shootAim->kReverse);
	}
}
