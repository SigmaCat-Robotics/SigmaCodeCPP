/*
 * SigmaEncoder.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Andrew
 */

#include "SigmaEncoder.h"

class SigmaEncoder: public Encoder
{
	bool isDriveEncoder = false;

	public:
		SigmaEncoder(bool isDrive, bool isInverted, int a, int b):Encoder(a,b,isInverted) {
			isDriveEncoder = isDrive;
			if(isDriveEncoder){
				Encoder::SetDistancePerPulse(0.00875);
			}
		}
		SigmaEncoder(int a, int b, int index):Encoder(a,b,index) {

		}
		// TODO Auto-generated constructor stub
		void reset(){
			Encoder::Reset();
		}

};

