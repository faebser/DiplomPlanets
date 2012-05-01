/*
 * Planet.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef PLANET_H_
#define PLANET_H_

class Planet {
public:
	Planet();
	virtual ~Planet();
	void getResource(Resource incomingResource);
	void sendResource(Resource outgoingResource);
	void update();
	void draw();
private:
};

#endif /* PLANET_H_ */
