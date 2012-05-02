/*
 * Resource.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>

class Resource {
public:
	Resource();
	virtual ~Resource();
	string getType();
	int getAmount();
private:
	string type;
	int amount;
};

#endif /* RESOURCE_H_ */
