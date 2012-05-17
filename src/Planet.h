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

class Planet {
public:
	Planet();
	Planet(string planetName);
	virtual ~Planet();
	void getResource(Resource* incomingResource);
	void sendResource(Resource* outgoingResource, string* planetName);
	void update();
	void draw();
	void generateTexture();

	// getter / setter
	string* getPlanetName();
	string* getPlayerName();
	float* getRadius();
	void setPlanetName(string name), setPlayerName(string name), setRadius(float radius);
private:
	vector<ofImage> textures; // texture used on planet
	vector<Resource> resources;
	string type;
	float radius;
	bool isPlayer;
	string playerName, planetName;

};

#endif /* PLANET_H_ */
