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

AutonomousModes::AutonomousModes(SigmaDrive* drive, ShooterIntake* intakeShooter) {
	// TODO Auto-generated constructor stub
	drive108 = drive;
	intakeShooter108 = intakeShooter;
	Auto = new LowBarLow(drive108, intakeShooter108);
}

AutonomousModes::~AutonomousModes() {
	// TODO Auto-generated destructor stub
}

void AutonomousModes::SetMode(int choice){
	switch(choice){
	case 1: Auto = new LowBarLow(drive108, intakeShooter108);
			break;
	case 2: Auto = new LowBarHigh(drive108, intakeShooter108);
			break;
	}
}

void AutonomousModes::Run(){
	Auto->Start();
}


