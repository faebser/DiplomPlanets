/*
 * PlanetFbo.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: faebser
 */

#include "PlanetFbo.h"

PlanetFbo::PlanetFbo() {
	// TODO Auto-generated constructor stub

}

float PlanetFbo::getRealXPos(float input) {
	float width = input / getWidth();
	float returning = (width - (int)width) * getWidth();
	if(returning < 0) {
		returning *= -1;
	}
	return returning;
}

void PlanetFbo::updatePoints() {
	vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
	if(type == "shape") {
		for (; it < end; it++) {
			it->updatePoints();
		}
	}
	else if(type == "line") {
		for (; it < end; it++) {
			it->updateLines();
		}
	}
}

void PlanetFbo::generateAttraction() {
	vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
	for (; it < end; it++) {
		const ofVec2f* points = it->getvertexPoints();
		for(int iP = 0; iP < POINTS; iP++) {
			vector<planetShape>::iterator innerIt = shapes.begin(), innerEnd = shapes.end();
			for(;innerIt < innerEnd; ++innerIt) {
				if(innerIt == it) {
					continue;
				}
				ofVec2f distVec = innerIt->getCenter() - points[iP];
				float dist = distVec.length();
				if( dist > 0 && dist < RADIUS) {
					float s = dist / RADIUS;
					float force = 1 / pow(s, .5f) -1;
					force = force / RADIUS;
					it->addToPoint(iP, distVec * force);
				}
			}
		}
	}
}

void PlanetFbo::paintMe() {
	if (type == "shape") {
		paintMeShapes();
	}
	else if(type == "line") {
		paintMeLines();
	}
}

void PlanetFbo::paintMeShapes() {
	vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
	updatePoints();
	generateAttraction();
	this->begin();
	ofClear(0, 0, 0, 0);
	for(;it < end; ++it) {
		ofPushStyle();
			ofSetColor(66, 154, 66);
			ofFill();
			const ofVec2f* vertexPoints = it->getvertexPoints();
			ofBeginShape();
			ofVertex(getRealXPos(vertexPoints[POINTS - 1].x), vertexPoints[POINTS - 1].y);
				for(int i = 0; i < POINTS; i++) {
					ofVertex(getRealXPos(vertexPoints[i].x), vertexPoints[i].y);
				}
				ofVertex(getRealXPos(vertexPoints[1].x), vertexPoints[1].y);
			ofEndShape();
			ofNoFill();
			ofEnableSmoothing();
				ofBeginShape();
					ofVertex(getRealXPos(vertexPoints[POINTS - 1].x), vertexPoints[POINTS - 1].y);
					for(int i = 0; i < POINTS; i++) {
						ofVertex(getRealXPos(vertexPoints[i].x), vertexPoints[i].y);
					}
					ofVertex(getRealXPos(vertexPoints[1].x), vertexPoints[1].y);
				ofEndShape();
			ofDisableSmoothing();
		ofPopStyle();
	}
	this->end();
}

void PlanetFbo::paintMeLines() {
	vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
	ofSetColor(255);
	ofClear(0,0,0,0);
	updatePoints();
	this->begin();
	for(;it < end; ++it) {
		ofPushStyle();
		ofPushMatrix();
			const ofVec2f* vertexPoints = it->getvertexPoints();
			float randomX = 0;
			if(ofRandom(1) > 0.5) {
				randomX = ofRandom(-10, this->getWidth()-vertexPoints[POINTS-2].x);
			}
			else {
				randomX = ofRandom(-10, vertexPoints[1].x)*-1;
			}
			ofTranslate(randomX, 0);
			ofEnableSmoothing();
			ofSetColor(color);
			ofBeginShape();
				for(int i = 0; i < POINTS; i++) {
					ofCurveVertex(vertexPoints[i].x, vertexPoints[i].y);
				}
			ofEndShape();
			ofDisableSmoothing();
		ofPopMatrix();
		ofPopStyle();
	}
	this->end();
}

void PlanetFbo::generateShapes(int size) {
	if(type == "shape") {
		if(size > 5) {
			float left = size - ofRandom(size * 0.25,size);
			shapes.push_back(planetShape(getWidth(), getHeight(), left, type));
			generateShapes(left);
		}
		else {
			shapes.push_back(planetShape(getWidth(), getHeight(), size, type));
		}
	}
	else if(type == "line") {
		for(int i = 0; i < size; i++) {
			shapes.push_back(planetShape(getWidth(), getHeight(), size, type));
		}
	}
}

string PlanetFbo::getType() const {
	return type;
}

void PlanetFbo::setType(string type) {
	this->type = type;
}

ofColor PlanetFbo::getColor() const {
	return color;
}

ofColor PlanetFbo::getColorWithMaxAlpha() const {
	return colorWithMaxAlpha;
}

void PlanetFbo::setColor(ofColor color) {
	this->color = color;
	this->colorWithMaxAlpha = color;
	this->colorWithMaxAlpha.a = 255;
}

PlanetFbo::~PlanetFbo() {
	// TODO Auto-generated destructor stub
}

