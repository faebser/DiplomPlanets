/*
 * View.cpp
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#include "testApp.h"
#include "View.h"



View::View() {
	// TODO Auto-generated constructor stub
}
View::View(string type) {
	this->type = type;
	this->middle = ofVec2f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
	// Point lights emit light in all directions //
	// set the diffuse color, color reflected from the light source //
	sun.setDiffuseColor( ofColor(249, 245, 224));
	sunPos = ofVec3f(middle.x, middle.y, 0);
	sun.setPosition(sunPos);

	// specular color, the highlight/shininess color //
	sun.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	sun.setPointLight();
}

void View::update(vector<Planet>* planets) {
	vector<Planet>::iterator it, end;
	end = planets->end();
	bool newRound = (int)ofGetElapsedTimeMillis() % (int)config->getNumber("roundDuration") < 10;
	for(it = planets->begin();it < end; ++it) {
		if(newRound) {
			(*it).clearModificator();
			vector<Modificator>::iterator itMod = modificators->begin(), endMo = modificators->end();
			for(;itMod < endMo; ++itMod) {
				if((*itMod).compare((*it).getResources())) {
					(*it).addModificator(&(*itMod));
				}
			}
			(*it).newRound();
		}
		(*it).update();
	}
}
void View::windowResize(int w, int h) {
	this->middle.set(w*0.5, h*0.5);
	sunPos = middle;
}

void View::draw(vector<Planet*> planets) {
	config->getCam()->begin();
	if(this->type == "overview") {
		this->drawOverview(planets);
	}
	else if(this->type == "singlePlanet") {
		this->drawPlanet(planets);
	}
	config->getCam()->end();
}
void View::drawOverview(vector<Planet*> planets) {
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(middle.x, middle.y);
	ofSetColor(255, 255, 255, 230);


	ofEnableLighting();
	vector<Planet*>::iterator it, end;
	end = planets.end();
	ofSetCircleResolution(150);
	for(it = planets.begin();it < end; ++it) {
		ofEnableSmoothing();
			ofNoFill();
			ofCircle(0, 0, (*it)->getResizedRadius());
		ofDisableSmoothing();
		ofFill();
		ofPushMatrix();
		ofPushStyle();
			(*it)->draw();
		ofPopStyle();
		ofPopMatrix();
	}
	ofDisableLighting();
	ofPopStyle();
	ofSphere(0, 0, 5);

	ofPopMatrix();
	ofSetCircleResolution(22);
	ofPushStyle();
		ofSetColor(255, 0, 0);
		ofBox(sunPos, 20);
	ofPopStyle();
}

void View::drawPlanet(vector<Planet*> planets) {
	Planet* current = planets[0];
	ofPushMatrix();
	ofPushStyle();
		ofSetColor((*current->getColor()));
		ofTranslate(middle.x, middle.y);
		ofCircle(0,0, current->getSize() * 20);
		ofSetColor(255);
		ofDrawBitmapString("name: " + *current->getPlanetName(), 20, 20);
	ofPopStyle();
	ofPopMatrix();
}
//getter
string View::getType() {
	return this->type;
}
ofVec2f View::getMiddle() {
	return this->middle;
}
void View::setConfig(Config* config) {
	this->config = config;
}
View::~View() {
	// TODO Auto-generated destructor stub
}

void View::basicDraw(vector<Planet*> planets) {
	ofTranslate(middle.x, middle.y);
	vector<Planet*>::iterator it = planets.begin(), end = planets.end();
	for(;it != end; ++it) {
		(*it)->basicDraw();
	}
}

void View::setModificators(vector<Modificator>* modificators) {
	this->modificators = modificators;
}



