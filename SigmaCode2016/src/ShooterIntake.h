/*
 * ShooterIntake.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Andrew
 */

#ifndef SRC_SHOOTERINTAKE_H_
#define SRC_SHOOTERINTAKE_H_

class ShooterIntake {
public:
	ShooterIntake();
	double ShooterRate();
	void Intake();
	void Release();
	void Prime();
	void Shoot(/*double desiredSpeed*/);
	void LiftIntake();
	void LowerIntake();
	void ResetEncoder();
	void StopIntake();
	void StopIndexer();
	void ShooterAim(bool high);
	virtual ~ShooterIntake();
};

#endif /* SRC_SHOOTERINTAKE_H_ */
