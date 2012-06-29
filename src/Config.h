/*
 * Config.h
 *
 *  Created on: Jun 28, 2012
 *      Author: faebser
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "testApp.h"
#include "json/json.h"

class Config {
public:
	Config();
	Config(Json::Value jsonInput);
	virtual ~Config();

	void deserialize();

	//getter
	float getNumber(string name);
	string getString(string name);
	vector<string> getListOf(string types);
	vector<string> getPlanetTypes() const;
	vector<string> getResourceTypes() const;
	vector<string> getViewTypes() const;

	Json::Value json;
	map<string, float> configNumbers;
	map<string, string> configStrings;
	vector<string> planetTypes;
	vector<string> resourceTypes;
	vector<string> viewTypes;
};

#endif /* CONFIG_H_ */
