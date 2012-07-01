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
#include "Resource.h"
#include "Config.h"

class Planet {
public:
	Planet();
	Planet(Config* config);
	Planet(string planetName, Config* config);
	virtual ~Planet();
	void getResource(Resource* incomingResource);
	void sendResource(Resource* outgoingResource, string* planetName);
	void update();
	void draw();
	void generateTexture();

	// getter
	string* getPlanetName();
	string* getPlayerName();
	float getSize(), getAngle(), getVelocity();
	float* getRadius(), getResizedRadius();
	ofColor* getColor();
	float getResourceValueAsPercent(string resName);
	ofVec2f getPos();
	// setter
	void setPlanetName(string name), setPlayerName(string name), setRadius(float radius);
	void setPos(float x, float y);
	void setAngle(float angle), setVelocity(float v);

	void clicked(int player);
	void newRound();
private:
	void baseConstructor();
	Config* config;
	vector<ofImage> textures; // texture used on planet
	vector<Resource> resources;
	string type;
	float radius, angle, velocity;
	bool isPlayer;
	string playerName, planetName;
	ofColor testColor;
	ofVec2f pos;
};

#endif /* PLANET_H_ */
