#ifndef LowBarLow_H
#define LowBarLow_H
#include "WPILib.h"
#include "..\SigmaDrive.h"
#include "..\ShooterIntake.h"
#include "..\AutoDrive.h"

class LowBarLow: public Command
{
public:
	LowBarLow(SigmaDrive* drive108,ShooterIntake* shooterIntake);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	SigmaDrive *Loki;
	ShooterIntake *LokiStaff;
	AutoDrive *driver;
	bool Finished;
};

#endif
