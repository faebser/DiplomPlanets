/*
 * Modificator.h
 *
 *  Created on: May 29, 2012
 *      Author: faebser
 */
#ifndef MODIFICATOR_H_
#define MODIFICATOR_H_

#include "ofMain.h"
#include "json/json.h"
#include "Resource.h"

class OperatorBase {
public:
	virtual float calculate(float b)=0;
};

class ComparatorBase {
public:
	virtual bool compare(float b)=0;
	string valueToWorkWith;
};

template<typename Op>
class Operator: public OperatorBase{
public:
	float calculate( float b) {
		Op o;
		return o(theValue, b);
	}
	float theValue;
	string valueToOperateWith;
};
template<typename Cp>
class Comparator : public ComparatorBase {
public:
	bool compare(float b) {
		Cp c;
		return c(theValue, b);
	}
	float theValue;
};
class ComparatorBetween : public ComparatorBase {
public:
	bool compare(float b) {
		return (b > theValue.x && b < theValue.y);
	}
	ofVec2f theValue;
};
class Modificator {
public:
	Modificator();
	Modificator(string name);
	Modificator(Json::Value* jsonInput);
	void deserialize(Json::Value* jsonInput);
	void modify(vector<Resource> resources);
	void compare(vector<Resource> resources);
	virtual ~Modificator();
private:
	string name;
	map<string, OperatorBase*> operators;
	map<string, ComparatorBase*> comperators;
};
#endif /* MODIFICATOR_H_ */
