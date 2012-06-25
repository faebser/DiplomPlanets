/*
 * Modificator.cpp
 *
 *  Created on: May 29, 2012
 *      Author: faebser
 */

#include "Modificator.h"

// the modificators should be generated on startup from a json file for better handling

Modificator::Modificator() {
	// TODO Auto-generated constructor stub
	//operators["fire"] = new Operator<std::plus<float>>;
	//operators["fire"]->Calc((float)30);
}
Modificator::Modificator(string name) {
	this->name = name;
}
Modificator::Modificator(Json::Value* jsonInput) {
	this->deserialize(jsonInput);
}
void Modificator::deserialize(Json::Value* jsonInput) {
}
void Modificator::modify(vector<Resource> resources) {
}
void Modificator::compare(vector<Resource> resources) {
}
Modificator::~Modificator() {
	// TODO Auto-generated destructor stub
}
