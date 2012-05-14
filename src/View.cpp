/*
 * View.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "View.h"

View::View() {
	// TODO Auto-generated constructor stub
}
View::View(string type) {
	this->type = type;
}

void View::update(vector<Planet>* planets) {

}

void View::draw(vector<Planet>* planets) {
	if(this->type == "overview") {
		this->drawOverview(planets);
	}
	else if(this->type == "singlePlanet") {
		this->drawPlanet(planets);
	}
}
void View::drawOverview(vector<Planet>* planets) {

}

void View::drawPlanet(vector<Planet>* planets) {

}

View::~View() {
	// TODO Auto-generated destructor stub
}

