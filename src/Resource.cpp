/*
 * Resource.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "Resource.h"

Resource::Resource() {
	// TODO Auto-generated constructor stub
}
Resource::Resource(string type) {
	this->type = type;
	this->amount = ofRandom(1,10);
}
string Resource::getType() {
	return type;
}
int Resource::getAmount() {
	return amount;
}
void Resource::setType(string type) {
	this->type = type;
}
void Resource::addAmount(int amount) {
	this->amount += amount;
}
Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

