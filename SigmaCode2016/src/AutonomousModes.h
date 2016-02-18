/*
 * AutonomousModes.h
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */

#ifndef SRC_AUTONOMOUSMODES_H_
#define SRC_AUTONOMOUSMODES_H_
#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"

class AutonomousModes {
public:
	AutonomousModes(SigmaDrive* drive, ShooterIntake* intakeShooter);
	void SetMode(int choice);
	void Run();
	virtual ~AutonomousModes();
	SigmaDrive *drive108;
	ShooterIntake *intakeShooter108;
	Command *Auto;
};

#endif /* SRC_AUTONOMOUSMODES_H_ */
