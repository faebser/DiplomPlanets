/*
 * View.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef VIEW_H_INCLUDED__
#define VIEW_H_INCLUDED__

#include "Config.h"
#include "Planet.h"

class Planet;
class View {
public:
	View();
	View(string type);
	void update(vector<Planet>* planets);
	void draw(vector<Planet*> planets);
	void drawOverview(vector<Planet*> planets);
	void drawPlanet(vector<Planet*> planets);
	void windowResize(int w, int h);

	string getType();
	ofVec2f getMiddle();
	virtual ~View();
	void setConfig(Config config);
	ofVec2f middle;
private:
	string type;
	Config config;
};

#endif /* VIEW_H_ */
