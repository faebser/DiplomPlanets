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
	void setType(string type);
	int getAmount();
	void addAmount(int amount);
	bool operator<(const Resource& a) const;
private:
	string type;
	int amount;
};

#endif /* RESOURCE_H_ */
