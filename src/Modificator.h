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

class ComperatorBase {
public:
	virtual bool compare(float b)=0;
};

template<typename Op>
class Operator: public OperatorBase{
public:
	float calculate( float b) {
		Op o;
		return o(theValue, b);
	}
	float theValue;
};
template<typename Cp>
class Comperator : public ComperatorBase {
public:
	bool compare(float b) {
		Cp c;
		return c(theValue, b);
	}
	float theValue;
};
class Modificator {
public:
	Modificator();
	Modificator(Json::Value jsonInput, Resource parent);
	void Deserialize(Json::Value jsonInput, Resource parent);
	void run();
	virtual ~Modificator();
private:
	vector<string> rangesOperator;
	map<string, float> ranges;
	string name;
	map<string, OperatorBase*> operators;
};

#endif /* MODIFICATOR_H_ */
