/*
 * LowBarHigh.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */

#include "LowBarHigh.h"
#include "WPILib.h"

LowBarHigh::LowBarHigh(SigmaDrive* drive108,ShooterIntake* shooterIntake)
{
	Loki = drive108;
	LokiStaff = shooterIntake;
	Finished = false;
	driver = new AutoDrive(Loki);
}

LowBarHigh::~LowBarHigh(){};

// Called just before this Command runs the first time
void LowBarHigh::Initialize()
{
	Loki->ResetDisplacement();
	Loki->gyro->Reset();
	Loki->left1->SetControlMode(CANTalon::kVoltage);
	Loki->right1->SetControlMode(CANTalon::kVoltage);
	Loki->shiftToLow();
}

// Called repeatedly when this Command is scheduled to run
void LowBarHigh::Execute()
{
	LokiStaff->Intake(true);
	Wait(2.0);
	LokiStaff->Intake(false);
	LokiStaff->StopIndexer();
	LokiStaff->LowerIntake();
	driver->driveStraight(240.0, 3.0, true);
	driver->turnOnSpot(-119,3);
	driver->driveStraight(150.0, 4.0, true);
	LokiStaff->Prime(true);
	Wait(3.0);
	LokiStaff->ShooterAim(true);
	Wait(1.0);
	LokiStaff->Shoot();
	LokiStaff->Prime(false);
	Finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool LowBarHigh::IsFinished()
{
	return Finished;
}

// Called once after isFinished returns true
void LowBarHigh::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowBarHigh::Interrupted()
{

}

