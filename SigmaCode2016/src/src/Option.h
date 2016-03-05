/*
 * Option.h
 *
 *  Created on: Feb 22, 2016
 *      Author: Robotics
 */

#ifndef OPTION_H_
#define OPTION_H_

class Option {
public:
	Option(int num);
	int Get();
	virtual ~Option();
	int number;
};

#endif /* OPTION_H_ */
