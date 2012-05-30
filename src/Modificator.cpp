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
	operators["fire"] = new Operator<std::plus<float> >;
	operators["fire"]->Calc((float)30);
}

void Modificator::run() {

}

Modificator::~Modificator() {
	// TODO Auto-generated destructor stub
}
