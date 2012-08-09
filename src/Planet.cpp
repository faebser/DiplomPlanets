
/*
 * Planet.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */
#define LERP 0.2
#include "Planet.h"

bool compareByAmount( Resource a, Resource b)
{
	return a.getAmount() > b.getAmount();
}
// TODO fix constructors and part them
Planet::Planet() { //used for a really new planet
	this->velocity = ofRandom(-0.003, 0.003); //TODO fix velocity
	this->angle = ofRandom(0,TWO_PI);
	baseConstructor();
	// ::update and ::generateTexture will be called after creation of Planet
}
Planet::Planet(Config* config, Sound* sound) { //used for a really new planet
	this->config = config;
	this->sound = sound;
	this->radius = config->getRandomPlanetRadius();
	this->velocity = ofRandom(-0.003, 0.003); //TODO fix velocity
	this->angle = ofRandom(0,TWO_PI);
	baseConstructor();
	// ::update and ::generateTexture will be called after creation of Planet
}
Planet::Planet(string planetName, Config* config) { // used for already existing planets
	this->config = config;
	this->velocity = ofRandom(-0.003, 0.003); //TODO fmove into config
	this->angle = ofRandom(0,TWO_PI);
	baseConstructor();
}
void Planet::addModificator(Modificator* newMod) {
	modificators.push_back(newMod);
}

void Planet::clearModificator() {
	/*vector<Modificator*>::iterator it = modificators.begin(), end = modificators.end();
	for(; it < end; ++it) {
		delete it;
	}*/
	modificators.clear();
}
float Planet::getResourceValueNormalized(string resName) {
	return getResourceValueAsPercent(resName)*0.01;
}

void Planet::updateSound() {
	vector<Resource>::iterator it;
	map<string, ofSoundPlayer>::iterator soundIt;
	for(it = this->resources.begin(); it < this->resources.end(); ++it) {
		string type = it->getType();
		float volume = ofMap(getResourceValueNormalized(type), config->getNumber("setVolumeMin"),config->getNumber("setVolumeMax"), 0, 1);
		soundIt = elementSounds.find(type);
		if(soundIt->second.getIsPlaying() == false) { // TODO remove from here
			soundIt->second.play();
		}
		soundIt->second.setVolume(volume);
		soundIt = spaceSounds.find(type);
		soundIt->second.setVolume(volume * config->getNumber("dampFromElementToSpace"));
	}
	float distance = ((getResizedRadius() - pos.y) / ofGetWindowWidth() * 0.5) * config->getNumber("maxDampingOnYForElements");
	cout << "distance-> " << distance << endl;

}

void Planet::baseConstructor() {
	this->type = config->getRandomPlanetType();
	vector<string> resources = config->getResourceTypes();
	int maxI = resources.size();
	for(int i = 0; i < maxI;i++) {
		string resourceType = resources[i];
		this->resources.push_back(Resource(resourceType));
		PlanetFbo newFbo;
		newFbo.allocate(800, 600, GL_RGBA, 4);
		fbos.push_back(newFbo);
	}
	elementSounds = sound->getAllElementPlayers();
	spaceSounds = sound->getAllSpacePlayers();
	updateSound();
	generateTexture();
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
	//this->parent->relayResource(outgoingResource, planetName);
}
void Planet::update() {
	angle += velocity;
	this->pos.set( sin(this->angle) * this->getResizedRadius() , cos(this->angle) * this->getResizedRadius());
}
void Planet::generateTexture() {
	sort(resources.begin(), resources.end(), compareByAmount);
	vector<Resource>::iterator resourcesIt = resources.begin(), resourcesEnd = resources.end();
	vector<PlanetFbo>::iterator fbosIt = fbos.begin(), fbosEnd = fbos.end();
	for(;resourcesIt < resourcesEnd; ++resourcesIt, ++fbosIt) {
		if(resourcesIt == resources.begin()) {
			groundColor = config->getColorByName(resourcesIt->getType());
		}
		else {
			if(fbosIt != fbosEnd) {
				if(resourcesIt->getType() == "gas") {
					fbosIt->setType("line");
				}
				else {
					fbosIt->setType("shape");
				}
				fbosIt->generateShapes(resourcesIt->getAmount());
				fbosIt->setColor( config->getColorByName(resourcesIt->getType())->getLerped((*groundColor), LERP) );
				fbosIt->paintMe();
			}
		}
	}
}
void Planet::clicked(int player) {
}
void Planet::draw() {
	vector<PlanetFbo>::iterator it = fbos.begin(), end = fbos.end();
	int dist = 2, distOffset = dist;

	ofTranslate(pos);

	ofEnableAlphaBlending();
	glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(fbos[0].getWidth(), fbos[0].getHeight());
	glMatrixMode(GL_MODELVIEW);

	ofSetColor((*groundColor));
	ofSphere(getSize());
	ofNoFill();
	ofEnableSmoothing();
	ofSphere(getSize());
	ofDisableSmoothing();

	for (;it < end; ++it, dist += distOffset) {
		ofSetColor(255); // IMPORTANT: reset color to display textures normal
		(*it).getTextureReference().bind();
			ofSphere(getSize() + dist);
		(*it).getTextureReference().unbind();
	}

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);
	ofDisableAlphaBlending();
	ofSetColor(255);
	ofDrawBitmapString("name: " + this->planetName, 20, 20);
}
void Planet::newRound() {
	//TODO prototyp: erase and rewrite
	vector<Resource>::iterator it;
	for(it = this->resources.begin(); it < this->resources.end(); ++it) {
		(*it).addAmount(config->getRandomStartAmount());
	}
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
	float size = 0;
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
ofVec2f Planet::getPos() { //TODO rewrite this it to make it beautiful
	return this->pos + config->getMiddle();
}
ofColor* Planet::getColor() {
	return this->groundColor;
}
float Planet::getResizedRadius() {
	float realMax = ofGetWindowWidth() * 0.5, realMin = 30;
	return ofMap(radius, config->getNumber("minRadius"), config->getNumber("maxRadius"), realMin, realMax);
}
float Planet::getResourceValueAsPercent(string resName) {
	float total = 0, amount = 0;
	vector<Resource>::iterator it, end;
	it = resources.begin();
	end = resources.end();
	for(;it < end; ++it) {
		total += (*it).getAmount();
		if((*it).getType() == resName) {
			amount = (*it).getAmount();
		}
	}
	return total/amount;
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

vector<Resource> Planet::getResources() const {
	return resources;
}
void Planet::setSound(Sound* sound) {
	this->sound = sound;
}


