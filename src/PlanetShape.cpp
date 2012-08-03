/*
 * PlanetShape.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: faebser
 */

#include "PlanetShape.h"
#define RADIUS 250
#define GROWRATE 20
#define UPDATERATE 100

PlanetShape::PlanetShape() {
	// TODO Auto-generated constructor stub

}

PlanetShape::PlanetShape(float width, float height, float size, string type) {
	if(type == "shape") {
		center = ofVec2f(ofRandom(0, width), ofRandom(0, height));
		float angle = ofDegToRad(360 / POINTS);
		for(int i = 0; i < POINTS; i++) {
				float x = cos(angle * i) * 25;
				float y = sin(angle * i) * 25;
				ofVec2f newPoint = ofVec2f(x,y) + center;
				vertexPoints[i] = newPoint;
				this->size = size;
				for(int i = 0; i <= size; i++) {
					growMe();
				}
		}
	}
	else if(type == "line") {
		float step = (float)1 / (POINTS/2);
		ofVec2f start = ofVec2f(0, ofRandom(0, height));
		ofVec2f end = ofVec2f(width, start.y);
		vertexPoints[0] = start;
		for(int i = 1; i < POINTS-1; i++) {
			ofVec2f newPoint = start.interpolate(end, step);
			vertexPoints[i] = newPoint;
		}
		vertexPoints[POINTS-1] = end;
	}
}

void PlanetShape::updatePoints() {
	for (int change = 0; change < UPDATERATE; change++) {
		for(int i = 0; i < POINTS; i++) {
			vertexPoints[i].set(vertexPoints[i].x + ofRandom(-3, 3), vertexPoints[i].y + ofRandom(-3, 3));
		}
		center.set(center.x + ofRandom(-3.5,3.5), center.y + ofRandom(-3.5, 3.5));
	}
}

void PlanetShape::updateLines() {
	for (int change = 0; change < UPDATERATE; change++) {
		for(int i = 0; i < POINTS; i++) {
			vertexPoints[i].set(vertexPoints[i].x, vertexPoints[i].y + ofRandom(-3, 3));
		}
	}
}

ofVec2f PlanetShape::getCenter() const {
	return center;
}

void PlanetShape::setCenter(ofVec2f center) {
	this->center = center;
}

void PlanetShape::grow(int newSize) {
	int change  = newSize - size;
	for(int i = 0; i <= change; i++) {
		growMe();
	}
}

void PlanetShape::shrink(int newSize) {
	int change  = size - newSize;
	for(int i = 0; i <= change; i++) {
		shrinkMe();
	}
}

const ofVec2f* PlanetShape::getvertexPoints() const {
	return vertexPoints;
}

ofVec2f PlanetShape::getPos() const {
	return pos;
}

void PlanetShape::setPos(ofVec2f pos) {
	this->pos = pos;
}

void PlanetShape::addToPoint(int pointIndex, ofVec2f toAdd) {
	vertexPoints[pointIndex] += toAdd;
}

float PlanetShape::getSize() const {
	return size;
}

void PlanetShape::growMe() {
	for (int r = 0; r < GROWRATE; r++) {
		for(int i = 0; i < POINTS; i++) {
			ofPoint growVec;
			growVec =  vertexPoints[i] - center;
			vertexPoints[i] += growVec.normalized()*0.5;
		}
	}
}

void PlanetShape::shrinkMe() {
	for (int r = 0; r < GROWRATE; r++) {
		for(int i = 0; i < POINTS; i++) {
			ofPoint growVec;
			growVec =  vertexPoints[i] - center;
			vertexPoints[i] -= growVec.normalized()*0.5;
		}
	}
}

PlanetShape::~PlanetShape() {
	// TODO Auto-generated destructor stub
}

