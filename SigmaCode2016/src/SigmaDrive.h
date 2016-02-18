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
	double getSpeed();
	void resetEncoders();
	double getDistance();
	void changeGears();
	void tankDrive(double leftValue, double rightValue);
	void tankDrive(Joystick* lStick, Joystick* rStick);
	void setExpiration(double value);
	double getLeftDistance();
	double getRightDistance();
	double GetVelocity();
	double GetDisplacement();
	void shiftToLow();
	void shiftToHigh();
	void UpdateDiplacement(double updateRate);
	void ResetDisplacement();
	virtual ~SigmaDrive();

	CANTalon *left1, *left2, *right1, *right2;
	DoubleSolenoid *Shifter;
	Encoder *leftEncoder, *rightEncoder;
	RobotDrive *drive108;
	ADXL362 *accel;
	ADXRS450_Gyro *gyro;
	double driveSpeed = 0.0, lastVel = 0.0, displacement = 0.0;
	bool highGear = false;
	const double cimSpeed = 5310, HighRatio = 4.7, LowRatio = 18.6;
	const double maxSpeedHigh = cimSpeed/HighRatio , maxSpeedLow = cimSpeed/LowRatio;//rpm
};

#endif /* SIGMADRIVE_H_ */
