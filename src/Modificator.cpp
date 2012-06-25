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
	Json::Value compare, modificate;
	compare = (*jsonInput)["compares"];
	modificate = (*jsonInput)["modifies"];

	vector<string> compareMember = compare.getMemberNames();
	vector<string>::iterator it = compareMember.begin(), end = compareMember.end();
	for(;it != end; ++it) {
		Json::Value currentValue = compare[(*it)];
		string reference = currentValue["reference"].asString();
		if(reference == "between") {
			comperators.push_back( new ComparatorBetween(ofVec2f(currentValue["start"].asInt(),currentValue["end"].asInt()), (*it)));
		}
		else {
			if(reference == "bigger") {
				comperators.push_back( new Comparator<std::greater<float> >((float)currentValue["value"].asInt(), (*it)));
			}
			if(reference == "smaller") {
				comperators.push_back( new Comparator<std::less<float> >((float)currentValue["value"].asInt(), (*it)));
			}
			if(reference == "biggerEqual") {
				comperators.push_back( new Comparator<std::greater_equal<float> >((float)currentValue["value"].asInt(), (*it)));
			}
			if(reference == "smallerEqual") {
				comperators.push_back( new Comparator<std::less_equal<float> >((float)currentValue["value"].asInt(), (*it)));
			}
		}
	}

	vector<string> modificateMember = modificate.getMemberNames();
	it = modificateMember.begin();
	end = modificateMember.end();
	for(;it != end; ++it) {
		Json::Value currentValue = compare[(*it)];
		string currentOperator = currentValue["operator"].asString();
		if(currentOperator == "add") {
			operators.push_back( new Operator<std::plus<float> >((float)currentValue["value"].asInt(), (*it)));
		}
		if(currentOperator == "sub") {
			operators.push_back( new Operator<std::minus<float> >((float)currentValue["value"].asInt(), (*it)));
		}
		if(currentOperator == "mult") {
			operators.push_back( new Operator<std::divides<float> >((float)currentValue["value"].asInt(), (*it)));
		}
		if(currentOperator == "div") {
			operators.push_back( new Operator<std::plus<float> >((float)currentValue["value"].asInt(), (*it)));
		}
	}

}
void Modificator::modify(vector<Resource> resources) {
}
void Modificator::compare(vector<Resource> resources) {
}
Modificator::~Modificator() {
	// TODO Auto-generated destructor stub
}
