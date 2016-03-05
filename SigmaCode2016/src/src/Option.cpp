/*
 * Option.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: Robotics
 */

#include <Option.h>

Option::Option(int num) {
	// TODO Auto-generated constructor stub
	number = num;
}

Option::~Option() {
	// TODO Auto-generated destructor stub
}

int Option::Get(){
	return number;
}
