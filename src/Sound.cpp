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
Sound::Sound(Json::Value jsonInput, string compareString) {
	json = jsonInput;
	this->compareString = compareString;
}
void Sound::deserialize() {
	vector<string> members = json.getMemberNames();
	vector<string>::iterator it = members.begin(), end = members.end();
	for(; it < end; ++it) {
		if ( (*it).compare(0, compareString.length(), compareString) == 0) {
			size_t pos = compareString.length();
			string insertString = (*it).substr(pos);
			spaceSounds.insert( pair<string, string>(insertString, json[(*it)]["path"].asString()) );
		}
		else {
			elementSounds.insert( pair<string, string>((*it), json[(*it)]["path"].asString()) );
		}
	}
}
map<string, ofSoundPlayer> Sound::getAllElementPlayers() {
	map<string, ofSoundPlayer> returnMap;
	map<string, string>::iterator it = elementSounds.begin(), end = elementSounds.end();
	cout << elementSounds.size() << endl;
	for (; it != end; ++it) {
		ofSoundPlayer temp;
		temp.loadSound(it->second);
		temp.setLoop(true);
		temp.setMultiPlay(true);
		returnMap.insert( pair<string, ofSoundPlayer>(it->first, temp) );
	}
	return returnMap;
}
 map<string, ofSoundPlayer> Sound::getAllSpacePlayers() {
	map<string, ofSoundPlayer> returnMap;
	map<string, string>::iterator it = spaceSounds.begin(), end = spaceSounds.end();
	cout << spaceSounds.size() << endl;
	for (; it != end; ++it) {
		ofSoundPlayer temp;
		temp.loadSound(it->second);
		temp.setLoop(true);
		temp.setMultiPlay(true);
		returnMap.insert( pair<string, ofSoundPlayer>(it->first, temp) );
	}
	return returnMap;
}
Sound::~Sound() {
	// TODO Auto-generated destructor stub
}
