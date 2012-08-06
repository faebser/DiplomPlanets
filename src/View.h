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
	void setModificators(vector<Modificator>* modificators);
	ofVec2f middle;
private:
	ofLight sun;
	ofVec3f sunPos;
	string type;
	Config config;
	vector<Modificator>* modificators;
};

#endif /* VIEW_H_ */
