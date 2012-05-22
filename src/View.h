/*
 * View.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "Planet.h"

class View {
public:
	View();
	View(string type);
	void update(vector<Planet>* planets);
	void draw(vector<Planet>* planets);
	void drawOverview(vector<Planet>* planets);
	void drawPlanet(vector<Planet>* planets);
	float resizeRadius(float radius);
	virtual ~View();
	ofVec2f middle;
private:
	string type;

};

#endif /* VIEW_H_ */
