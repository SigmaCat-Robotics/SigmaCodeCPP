/*
 * SigmaVictorSP.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Andrew
 */

#ifndef SIGMAVICTORSP_H_
#define SIGMAVICTORSP_H_

class SigmaVictorSP{
public:
	SigmaVictorSP(int channel, bool acceleration, PIDSource *source);
	SigmaVictorSP(int channel);
	void Set(double desiredOutput);
	virtual ~SigmaVictorSP();
private:
	bool accel = false;
	static double ACCEL_CAP = 0.01;
	static double ACCEL_VAL = 0.2;
	double prevOutput = 0.0;
	double output = 0;
	float p = 0.0, i = 0.0, d = 0.0, updateRate = 0.05;
	Victor *victor;
	PIDController *controller;
};

#endif /* SIGMAVICTORSP_H_ */
