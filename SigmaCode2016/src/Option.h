/*
 * Option.h
 *
 *  Created on: Feb 17, 2016
 *      Author: Andrew
 */

#ifndef SRC_OPTION_H_
#define SRC_OPTION_H_

class Option {
public:
	Option(int num);
	int Get();
	virtual ~Option();
	int number;
};

#endif /* SRC_OPTION_H_ */
