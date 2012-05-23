
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
	this->velocity = ofRandom(0.001, 0.003);
	this->angle = ofRandom(0,TWO_PI);
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
	this->velocity = ofRandom(0.001, 0.003);
	this->angle = ofRandom(0,TWO_PI);
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
	this->velocity = ofRandom(0.001, 0.003);
	this->angle = ofRandom(0,TWO_PI);
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
	angle += velocity;
	this->generateTexture();
}
void Planet::generateTexture() {
	Resource res = resources[0]; // TODO korrigieren
	string type = res.getType();
	if (type == "fire") {
		testColor.set(244, 148, 11);
	}
	else if(type == "water") {
		testColor.set(32, 131, 143);
	}
	else if(type == "gas") {
		testColor.set(148, 121, 74);
	}
	else if(type == "rock") {
		testColor.set(155, 153, 150);
	}
	else {
		testColor.set(255, 0, 0);
	}
	/*vector<Resource>::iterator it;
		for(it = this->resources.begin(); it < this->resources.end(); ++it) {

			break;
		}*/
}
void Planet::clicked() {

}
void Planet::draw() {
	ofSetColor(testColor);
	ofCircle(pos.x, pos.y, this->getSize());
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
float Planet::getSize() {
	float size;
	vector<Resource>::iterator it;
	for(it = this->resources.begin(); it < this->resources.end(); ++it) {
		size += (*it).getAmount();
		break;
	}
	return size;
}
float Planet::getAngle() {
	return this->angle;
}
float Planet::getVelocity() {
	return this->velocity;
}
ofVec2f* Planet::getPos() {
	return &this->pos;
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
void Planet::setAngle(float angle) {
	this->angle = angle;
}
void Planet::setVelocity(float v) {
	this->velocity = v;
}
void Planet::setPos(float x, float y) {
	this->pos.set(x,y);
}
Planet::~Planet() {
}
