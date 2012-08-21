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
	Sound(Json::Value jsonInput, string compareString);
	void deserialize();
	//const ofSoundPlayer getSoundPlayer(string nameOfSound);
	map<string, ofSoundPlayer> getAllElementPlayers();
	map<string, ofSoundPlayer> getAllSpacePlayers();
	void playSound(string name);
	virtual ~Sound();

	map<string, string> spaceSounds, elementSounds;
private:
	Json::Value json;
	string compareString;
	ofSoundPlayer genesis;
};

#endif /* SOUND_H_ */
