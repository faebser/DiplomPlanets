
/*
 * Planet.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "Planet.h"
#include "testApp.h"

bool compareByLength( Resource a, Resource b)
{
	return a.getAmount() > b.getAmount();
}

Planet::Planet() { //used for a really new planet
	this->type = testApp::getRandomPlanetType();
	int maxI = testApp::resourceTypes.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = testApp::resourceTypes[i];
		this->resources.push_back(Resource(resourceType));
		cout << "added resourceType: " << resourceType << endl;
	}
	this->radius = testApp::getRandomPlanetRadius();
	// ::update and ::generateTexture will be called after creation of Planet
}
Planet::Planet(testApp* parentApp) { //used for a really new planet
	this->type = testApp::getRandomPlanetType();
	int maxI = testApp::resourceTypes.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = testApp::resourceTypes[i];
		this->resources.push_back(Resource(resourceType));
	}
	this->radius = testApp::getRandomPlanetRadius();
	this->parent = parent;
	// ::update and ::generateTexture will be called after creation of Planet
}
Planet::Planet(string planetName, testApp* parent) { // used for already existing planets
	this->planetName = planetName;
	int maxI = testApp::resourceTypes.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = testApp::resourceTypes[i];
		this->resources.push_back(Resource(resourceType));
	}
	this->parent = parent;
}
void Planet::getResource(Resource* incomingResource) {
	vector<Resource>::iterator it;
	for(it = this->resources.begin(); it < this->resources.end(); ++it) {
		if(incomingResource->getType() == (*it).getType()) {
			(*it).addAmount(incomingResource->getAmount());
			delete incomingResource;
			break;
		}
	}
}
void Planet::sendResource(Resource* outgoingResource, string* planetName) {
	this->parent->relayResource(outgoingResource, planetName);
}
void Planet::update() {
	std::sort(this->resources.begin(), this->resources.end(), compareByLength); // TODO sort by amount
	this->generateTexture();
}
void Planet::generateTexture() {
	vector<Resource>::iterator it;
		for(it = this->resources.begin(); it < this->resources.end(); ++it) {
				//cout << "typ: " << (*it).getType() << " amount: " << (*it).getAmount() << endl;
				break;
		}
}
void Planet::draw() {

}
// getter
string* Planet::getPlanetName() {
	return &this->planetName;
}
string* Planet::getPlayerName() {
	return &this->playerName;
}
float* Planet::getRadius() {
	return &this->radius;
}
// setter
void Planet::setPlanetName(string name) {
	this->planetName = name;
}
void Planet::setPlayerName(string name) {
	this->playerName = name;
}
void Planet::setRadius(float radius) {
	this->radius = radius;
}
Planet::~Planet() {
}
