/*
 * AutonomousModes.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */

#include <AutonomousModes.h>
#include "Modes\LowBarLow.h"
#include "Modes\LowBarHigh.h"
#include "WPILib.h"

AutonomousModes::AutonomousModes(SigmaDrive* drive108, ShooterIntake* intakeShooter) {
	// TODO Auto-generated constructor stub
	AutoPicker = new SendableChooser();
	AutoPicker->AddDefault("Low Bar Low Goal (Default)", new LowBarLow(drive108, intakeShooter));
	AutoPicker->AddObject("Low Bar High Goal", new LowBarHigh(drive108, intakeShooter));
	SmartDashboard::PutData("Autonomous", AutoPicker);
}

AutonomousModes::~AutonomousModes() {
	// TODO Auto-generated destructor stub
}


