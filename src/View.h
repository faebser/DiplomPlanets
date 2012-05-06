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
	void draw(vector<Planet> Planets);
	virtual ~View();
private:
	string type;
};

#endif /* VIEW_H_ */
