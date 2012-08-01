/*
 * Sound.h
 *
 *  Created on: Jun 29, 2012
 *      Author: faebser
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "ofMain.h"
#include "json/json.h"

class Sound {
public:
	Sound();
	Sound(Json::Value jsonInput);
	void deserialize();
	const ofSoundPlayer getSoundPlayer(string nameOfSound);
	virtual ~Sound();
private:
	Json::Value json;
	map<string, string> sounds;
};

#endif /* SOUND_H_ */
