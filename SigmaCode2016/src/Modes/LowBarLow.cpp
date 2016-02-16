#include "LowBarLow.h"
#include "WPILib.h"


LowBarLow::LowBarLow(SigmaDrive* drive108,ShooterIntake* shooterIntake)
{
	Loki = drive108;
	LokiStaff = shooterIntake;
	Finished = false;
	driver = new AutoDrive(Loki);
}

// Called just before this Command runs the first time
void LowBarLow::Initialize()
{
	Loki->ResetDisplacement();
	Loki->gyro->Reset();
	Loki->left1->SetControlMode(CANTalon::kVoltage);
	Loki->right1->SetControlMode(CANTalon::kVoltage);
	Loki->shiftToLow();
}

// Called repeatedly when this Command is scheduled to run
void LowBarLow::Execute()
{
	LokiStaff->Intake();
	Wait(2.0);
	LokiStaff->StopIntake();
	LokiStaff->StopIndexer();
	LokiStaff->LowerIntake();
	driver->driveStraight(240.0, 3.0, true);
	driver->turnOnSpot(61,3);
	driver->driveStraight(150.0, 4.0, true);
	LokiStaff->Release();
	Wait(3.0);
	Finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool LowBarLow::IsFinished()
{
	return Finished;
}

// Called once after isFinished returns true
void LowBarLow::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowBarLow::Interrupted()
{

}
