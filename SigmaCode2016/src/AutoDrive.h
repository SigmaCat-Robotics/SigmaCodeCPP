/*
 * AutoDrive.h
 *
 *  Created on: Feb 15, 2016
 *      Author: Andrew
 */

#ifndef SRC_AUTODRIVE_H_
#define SRC_AUTODRIVE_H_
#include "WPILib.h"
#include "SigmaDrive.h"

class AutoDrive {
public:
	AutoDrive(SigmaDrive* drive108);
	void followArc(double r, double theta, double t, bool leftTurn, bool stopWhenDone);
	void turnOnSpot(double theta, double t);
	void driveStraight(double d, double t, bool stopWhenDone);
	virtual ~AutoDrive();

	SigmaDrive *drive108;
	double desiredSpeed = 0.0, leftSpeed = 0.0, rightSpeed = 0.0;
	double angle = 0.0, Ltravelled = 0.0, Rtravelled = 0.0;
	double setValue = 0.0, leftValue = 0.0, rightValue = 0.0;
	double arcRadius = 0.0, leftRadius = 0.0, rightRadius = 0.0;
	double distanceToTravel = 0.0,leftDTT = 0.0,rightDTT = 0.0;
	double wheelCircum = 3.38*3.14, DriveWidth = 27;//in.
	double HighGearMaxSpeed = drive108->maxSpeedHigh*wheelCircum, LowGearMaxSpeed = drive108->maxSpeedLow*wheelCircum;//in.
	bool finished = false;
};

#endif /* SRC_AUTODRIVE_H_ */
