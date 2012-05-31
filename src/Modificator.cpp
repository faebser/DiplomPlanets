/*
 * Modificator.cpp
 *
 *  Created on: May 29, 2012
 *      Author: faebser
 */

#include "Modificator.h"

// the modificators should be generate on startup from a json file for better handling

Modificator::Modificator() {
	// TODO Auto-generated constructor stub
	//operators["fire"] = new Operator<std::plus<float> >;
	//operators["fire"]->Calc((float)30);
}
Modificator::Modificator(Json::Value jsonInput, Resource parent) {

}
void Modificator::run() {

}

void Modificator::Deserialize(Json::Value jsonInput, Resource parent) {
}

void Modificator::compare() {
}

Modificator::~Modificator() {
	// TODO Auto-generated destructor stub
}
