/*
 * Planet.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "Planet.h"
#include "testApp.h"

Planet::Planet() { //used for a really new planet
	this->type = testApp::getRandomPlanetType();
	int maxI = testApp::resourceTypes.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = testApp::resourceTypes[i];
		this->resources.push_back(Resource(resourceType));
	}
	this->radius = testApp::getRandomPlanetRadius();
	// ::update and ::generateTexture will be called after creation of Planet
}
Planet::Planet(string planetName) { // used for already existing planets
	this->planetName = planetName;
	int maxI = testApp::resourceTypes.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = testApp::resourceTypes[i];
		this->resources.push_back(Resource(resourceType));
	}
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
	//testApp::relayResource(outgoingResource, planetName);
}
void Planet::update() {
	// TODO add new resources
	//std::sort(this->resources.begin(), this->resources.end(), compareByLength); // TODO sort by amount
	this->generateTexture();
}
void Planet::generateTexture() {

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
