#pragma once
/*
 * PlanetFbo.h
 *
 *  Created on: Aug 3, 2012
 *      Author: faebser
 */

#ifndef PLANETFBO_H_
#define PLANETFBO_H_

#include "ofMain.h"
#include "PlanetShape.h"

class PlanetFbo: public ofFbo {
public:
	PlanetFbo();
	float getRealXPos(float input);
	void updatePoints();
	void generateAttraction();
	void paintMe();
	void paintMeShapes();
	void paintMeLines();
	void generateShapes(int size);
	string getType() const;
	void setType(string type);
	ofColor getColor() const;
	ofColor getColorWithMaxAlpha() const;
	void setColor(ofColor color);
	virtual ~PlanetFbo();
private:
	vector<PlanetShape> shapes;
	string type;
	ofColor colorWithMaxAlpha, color;
};

#endif /* PLANETFBO_H_ */
