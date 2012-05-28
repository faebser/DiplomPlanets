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

class View;
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
	void setPos(float x, float y);
	void setAngle(float angle), setVelocity(float v);
	ofVec2f getPos(View* activeView);
	void clicked(int player);
	void newRound();
private:
	void baseConstructor();
	vector<ofImage> textures; // texture used on planet
	vector<Resource> resources;
	string type;
	float radius, angle, velocity;
	bool isPlayer;
	string playerName, planetName;
	testApp* parent;
	ofColor testColor;
	ofVec2f pos;
};

#endif /* PLANET_H_ */
