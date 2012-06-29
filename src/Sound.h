/*
 * Sound.h
 *
 *  Created on: Jun 29, 2012
 *      Author: faebser
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "ofMain.h";
#include "json/json.h";

class Sound {
public:
	Sound();
	Sound(Json::Value jsonInput);
	void playSound(string sound);
	void deserialize();
	virtual ~Sound();
private:
	map<string, ofSoundPlayer> players;
};

#endif /* SOUND_H_ */
