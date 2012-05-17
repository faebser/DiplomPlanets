/*
 * Resource.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "Resource.h"
#include "testApp.h"

Resource::Resource() {
	// TODO Auto-generated constructor stub

}
Resource::Resource(string type) {
	this->type = type;
	this->amount = testApp::getRandomStartAmount();
}
string Resource::getType() {
	return type;
}

int Resource::getAmount() {
	return amount;
}
void Resource::addAmount(int amount) {
	this->amount += amount;
}
Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

