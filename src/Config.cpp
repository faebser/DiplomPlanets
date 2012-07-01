/*
 * Config.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: faebser
 */


#include "Config.h"


Config::Config() {
	// TODO Auto-generated constructor stub
}

Config::Config(Json::Value jsonInput) {
	json = jsonInput;
}

void Config::deserialize() {
	vector<string> members = json.getMemberNames();
	vector<string>::iterator it = members.begin(), end = members.end();

	for(;it < end; ++it) {
		if(json[(*it)].isNumeric()) {
			configNumbers.insert( pair<string, float>( (*it), (float)json[(*it)].asDouble() ));
		}
		else if(json[(*it)].isString()) {
			configStrings.insert( pair<string, string>( (*it), json[(*it)].asString() ));
		}
		else if((*it) == "planets" || (*it) == "resources" || (*it) == "views") {
			Json::Value currentValue = json[(*it)];
			int size = currentValue.size();
			vector<string>* writeTo;
			if((*it) == "planets") {
				writeTo = &planetTypes;
			}
			else if((*it) == "resources") {
				writeTo = &resourceTypes;
			}
			else {
				writeTo = &viewTypes;
			}
			for(int i = 0; i < size; i++) {
				writeTo->push_back(currentValue[i].asString());
			}
		}
	}
}
float Config::getNumber(string name) {
	if(configNumbers.find(name) != configNumbers.end()) {
		return configNumbers.at(name);
	}
	else {
		return -1;
	}
}
string Config::getString(string name) {
	if(configStrings.find(name) != configStrings.end()) {
			return configStrings.at(name);
		}
		else {
			return "none";
		}
}
vector<string> Config::getListOf(string types) {
	if(types == "planets") {
		return getPlanetTypes();
	}
	else if(types == "resources") {
		return getResourceTypes();
	}
	else if(types == "views") {
		return getViewTypes();
	}
}
vector<string> Config::getPlanetTypes() const {
	return planetTypes;
}

vector<string> Config::getResourceTypes() const {
	return resourceTypes;
}

vector<string> Config::getViewTypes() const {
	return viewTypes;
}

string Config::getRandomPlanetType() { //todo move into config
	int random = (int)ofRandom((float)planetTypes.size());
	return planetTypes[random];
}
float Config::getRandomPlanetRadius() {
	return ofRandom(this->configNumbers.at("minRadius"), this->configNumbers.at("maxRadius"));
}
int Config::getRandomStartAmount() {
	return (int)ofRandom(this->configNumbers.at("minStartAmount"), this->configNumbers.at("maxStartAmount"));
}
ofVec2f Config::getMiddle() const {
		return (*middle);
	}

void Config::setMiddle(ofVec2f* middle) {
		this->middle = middle;
	}
Config::~Config() {
	// TODO Auto-generated destructor stub
}



