/*
 * SigmaDrive.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#ifndef SIGMADRIVE_H_
#define SIGMADRIVE_H_
#include "WPILib.h"

class SigmaDrive {
public:
	SigmaDrive();
	void changeGears();
	void tankDrive(double leftValue, double rightValue);
	void tankDrive(Joystick* lStick, Joystick* rStick);
	void setExpiration(double value);
	double GetVelocity();
	double GetDisplacement();
	void shiftToLow();
	void shiftToHigh();
	void UpdateDiplacement(int updateRate);
	void ResetDisplacement();
	void DriveDistance(double distance);
	virtual ~SigmaDrive();
	bool highGear = false;
	CANTalon *left1, *left2, *right1, *right2;
	DoubleSolenoid *Shifter;
	RobotDrive *drive108;
	ADXL362 *accel;
	ADXRS450_Gyro *gyro;
	const double cimSpeed = 5310, HighRatio = 4.7, LowRatio = 18.6;
	const double maxSpeedHigh = cimSpeed/HighRatio , maxSpeedLow = cimSpeed/LowRatio;//rpm
	double lastVel = 0.0, displacement = 0.0;
};

#endif /* SIGMADRIVE_H_ */
