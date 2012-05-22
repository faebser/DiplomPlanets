/*
 * Planet.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Resource.h"
#include "ofMain.h"

class testApp;
class Planet {
public:
	Planet();
	Planet(testApp* parentApp);
	Planet(string planetName, testApp* parent);
	virtual ~Planet();
	void getResource(Resource* incomingResource);
	void sendResource(Resource* outgoingResource, string* planetName);
	void update();
	void draw();
	void generateTexture();

	// getter / setter
	string* getPlanetName();
	string* getPlayerName();
	float getSize(), getAngle(), getVelocity();
	float* getRadius();
	ofColor* getColor();
	void setPlanetName(string name), setPlayerName(string name), setRadius(float radius);
	void setAngle(float angle), setVelocity(float v);
private:
	vector<ofImage> textures; // texture used on planet
	vector<Resource> resources;
	string type;
	float radius, angle, velocity;
	bool isPlayer;
	string playerName, planetName;
	testApp* parent;
	ofColor testColor;
};

#endif /* PLANET_H_ */
