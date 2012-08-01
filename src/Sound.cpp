/*
 * Sound.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: faebser
 */

#include "ofMain.h"
#include "Sound.h"

Sound::Sound() {
	// TODO Auto-generated constructor stub

}
Sound::Sound(Json::Value jsonInput) {
	json = jsonInput;
}

void Sound::deserialize() {
	vector<string> members = json.getMemberNames();
	vector<string>::iterator it = members.begin(), end = members.end();
	for(; it < end; ++it) {
		sounds.insert(pair<string, string>((*it), json[(*it)]["path"].asString()));
	}
}

const ofSoundPlayer Sound::getSoundPlayer(string nameOfSound) {
	ofSoundPlayer returnIt;
	if(sounds.count(nameOfSound) > 0) {
		returnIt.setMultiPlay(true);
		returnIt.setLoop(true);
		return returnIt;
	}
	else {
		return returnIt;
	}
}

Sound::~Sound() {
	// TODO Auto-generated destructor stub
}

