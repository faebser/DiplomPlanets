/*
 * Resource.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "ofMain.h"

class Resource {
public:
	Resource();
	Resource(string type);
	virtual ~Resource();
	string getType();
	int getAmount();
	void addAmount(int amount);
private:
	string type;
	int amount;
};

#endif /* RESOURCE_H_ */
