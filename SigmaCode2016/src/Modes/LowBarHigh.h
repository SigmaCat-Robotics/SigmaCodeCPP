/*
 * LowBarHigh.h
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */

#ifndef SRC_MODES_LOWBARHIGH_H_
#define SRC_MODES_LOWBARHIGH_H_
#include "WPILib.h"
#include "..\SigmaDrive.h"
#include "..\ShooterIntake.h"
#include "..\AutoDrive.h"

class LowBarHigh: public Command {
public:
	LowBarHigh(SigmaDrive* drive108,ShooterIntake* shooterIntake);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	SigmaDrive *Loki;
	ShooterIntake *LokiStaff;
	AutoDrive *driver;
	bool Finished;
	virtual ~LowBarHigh();
};

#endif /* SRC_MODES_LOWBARHIGH_H_ */
