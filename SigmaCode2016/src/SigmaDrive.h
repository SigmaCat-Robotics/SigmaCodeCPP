/*
 * SigmaDrive.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#ifndef SIGMADRIVE_H_
#define SIGMADRIVE_H_

class SigmaDrive {
public:
	SigmaDrive();
	double getSpeed();
	void resetEncoders();
	double getDistance();
	void changeGears();
	void tankDrive(double leftValue, double rightValue);
	//void tankDrive(Joystick lStick, Joystick rStick);
	void setExpiration(double value);
	double getLeftDistance();
	double getRightDistance();
	void shiftToLow();
	void shiftToHigh();

	virtual ~SigmaDrive();
};

#endif /* SIGMADRIVE_H_ */
