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
	virtual ~Planet();
	void getResource(Resource incomingResource);
	void sendResource(Resource outgoingResource);
	void update();
	void draw();
private:
	ofImage texture; // texture used on planet
};

#endif /* PLANET_H_ */
