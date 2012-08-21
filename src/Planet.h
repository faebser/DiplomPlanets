#pragma once
/*
 * Planet.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef PLANET_H_INCLUDED__
#define PLANET_H_INCLUDED__

#include "ofMain.h"
#include "PlanetFbo.h"
#include "Modificator.h"
#include "Resource.h"
#include "Config.h"
#include "Sound.h"

class Planet {
public:
	Planet();
	Planet(Config* config, Sound* sound);
	Planet(string planetName, Config* config);
	virtual ~Planet();
	void getResource(Resource* incomingResource);
	void sendResource(Resource* outgoingResource, string* planetName);
	void update();
	void draw();
	void generateTexture();
	void updateSound();
	void updateSoundOnDraw();

	// getter
	string* getPlanetName();
	string* getPlayerName();
	float getSize(), getAngle(), getVelocity();
	float* getRadius(), getResizedRadius();
	ofColor* getColor();
	float getResourceValueAsPercent(string resName);
	float getResourceValueNormalized(string resName);
	ofVec2f getPos();
	vector<Resource> getResources() const;
	// setter
	void setPlanetName(string name), setPlayerName(string name), setRadius(float radius);
	void setPos(float x, float y);
	void setAngle(float angle), setVelocity(float v);
	void addModificator(Modificator* newMod);
	void clearModificator();

	void clicked(int player);
	void newRound();
	void setSound(Sound* sound);
private:
	void baseConstructor();
	map<string, ofSoundPlayer> elementSounds, spaceSounds;
	Sound* sound;
	Config* config;
	vector<Resource> resources;
	vector<Modificator*> modificators;
	vector<PlanetFbo> fbos;
	string type;
	float radius, angle, velocity;
	bool isPlayer;
	string playerName, planetName;
	ofColor* groundColor;
	ofVec2f pos;
};

#endif /* PLANET_H_ */
