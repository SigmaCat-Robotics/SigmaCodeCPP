/*
 * ShooterIntake.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Andrew
 */

#include <ShooterIntake.h>
#include "WPILib.h"

CANTalon *shooterWheel,*armMotor;
VictorSP *intakeMotor, *indexer1, *indexer2;
DoubleSolenoid *shootAim;
DigitalInput *indexSwitch;
double maxShootSpeed = 5310, ShootOutput;
double ShootSpeed, ArmSpeed;

ShooterIntake::ShooterIntake() {
	shooterWheel = new CANTalon(5);
	shootAim = new DoubleSolenoid(2,3);

	intakeMotor = new VictorSP(1);
	armMotor = new CANTalon(6);

	//indexer = new DoubleSolenoid(4,5);
	indexer1 = new VictorSP(2);
	indexer2 = new VictorSP(3);
	indexSwitch = new DigitalInput(1);

	shooterWheel->SetFeedbackDevice(CANTalon::EncRising);
	shooterWheel->SetControlMode(CANSpeedController::kSpeed);
	shooterWheel->ConfigEncoderCodesPerRev(20);
	shooterWheel->ConfigPeakOutputVoltage(+12, -12);
	shooterWheel->ConfigNominalOutputVoltage(+0, -0);
	shooterWheel->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

	armMotor->SetControlMode(CANSpeedController::kSpeed);
	armMotor->ConfigPeakOutputVoltage(+12, -12);
	armMotor->ConfigNominalOutputVoltage(+0, -0);
	armMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	armMotor->ConfigLimitMode(CANTalon::LimitMode::kLimitMode_SwitchInputsOnly);
	armMotor->ConfigFwdLimitSwitchNormallyOpen(true);
	armMotor->ConfigRevLimitSwitchNormallyOpen(true);
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
	ShootSpeed = SmartDashboard::GetNumber("Shooter RPM: ", 4000);
	if(indexSwitch->Get()){
		shooterWheel->Set(ShootSpeed);
	}
	else{
		Wait(4.0);
		shooterWheel->Set(0);
	}
}

void ShooterIntake::Shoot(){
	if(ShooterIntake::ShooterRate()>= ShootSpeed){
		indexer1->Set(0.5);
		indexer2->Set(-0.5);
		Wait(1.0);
		indexer1->Set(0.0);
		indexer2->Set(0.0);
	}
}

void ShooterIntake::LiftIntake(){
	ArmSpeed = SmartDashboard::GetNumber("Intake Arm Speed RPM: ", 60);
	armMotor->Set(ArmSpeed);
}

void ShooterIntake::LowerIntake(){
	armMotor->Set(-ArmSpeed);
}

double ShooterIntake::ShooterRate(){
	return (shooterWheel->GetSpeed()*1.21);
}

void ShooterIntake::ShooterAim(bool high){
	if(!high){
		shootAim->Set(shootAim->kForward);
	}else{
		shootAim->Set(shootAim->kReverse);
	}
}
