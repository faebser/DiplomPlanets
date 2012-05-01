/*
 * Resource.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

class Resource {
public:
	Resource();
	virtual ~Resource();
	char* getType();
	int getAmount();
private:
	char* type;
	int amount;
};

#endif /* RESOURCE_H_ */
