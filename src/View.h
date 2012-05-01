/*
 * View.h
 *
 *  Created on: Apr 28, 2012
 *      Author: faebser
 */

#ifndef VIEW_H_
#define VIEW_H_

class View {
public:
	View();
	virtual ~View();
	void draw(vector<Planet> Planets);
};

#endif /* VIEW_H_ */
