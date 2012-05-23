/*
 * View.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "View.h"
#include "testApp.h"


View::View() {
	// TODO Auto-generated constructor stub
}
View::View(string type) {
	this->type = type;
	this->middle = ofVec2f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
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
	ofPushMatrix();
	ofTranslate(middle.x, middle.y);
	ofSetColor(255);
	ofSphere(0, 0, 20);

	vector<Planet>::iterator it, end;
	end = planets->end();
	ofSetCircleResolution(150);
	ofEnableSmoothing();
	for(it = planets->begin();it < end; ++it) {
		float* radius = (*it).getRadius();
		ofNoFill();
		ofCircle(0, 0, this->resizeRadius(*radius));
		ofFill();
		ofPushMatrix();
		ofPushStyle();
			(*it).setPos(sin((*it).getAngle()) * this->resizeRadius(*radius), cos((*it).getAngle()) * this->resizeRadius(*radius));
			(*it).draw();
		ofPopStyle();
		ofPopMatrix();
	}
	ofPopStyle();
	ofDisableSmoothing();
	ofSetCircleResolution(22);
	ofPopMatrix();
}

float View::resizeRadius(float radius) {
	float max = testApp::maxRadius;
	float min = testApp::minRadius;
	float realMax = ofGetWindowWidth() * 0.5, realMin = 20;
	return ofMap(radius, min, max, realMin, realMax);
}

void View::drawPlanet(vector<Planet>* planets) {
	//TODO draw big planet
}

View::~View() {
	// TODO Auto-generated destructor stub
}

