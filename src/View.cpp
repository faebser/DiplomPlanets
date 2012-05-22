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
	vector<Planet>::iterator it, end;
	end = planets->end();

	for(it = planets->begin();it < end; ++it) {
		(*it).update();
	}
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
	// TODO draw sun, radius, planets
	ofPushStyle();
	ofSetColor(255);
	ofSphere(ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 20);

	vector<Planet>::iterator it, end;
	end = planets->end();
	ofNoFill();
	for(it = planets->begin();it < end; ++it) {
		float* radius = (*it).getRadius();
		ofCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, *radius);
		//delete radius;
	}
	ofPopStyle();
}

void View::drawPlanet(vector<Planet>* planets) {
	//TODO draw big planet

}

View::~View() {
	// TODO Auto-generated destructor stub
}

