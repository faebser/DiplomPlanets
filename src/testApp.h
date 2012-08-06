#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "json/json.h"
#include "Sound.h"
#include "Config.h"
#include "Modificator.h"
#include "View.h"
#include "Planet.h"


//example for json http://jsoncpp.sourceforge.net/

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void showNotification(string title, string message);

		//Networking related
		void udpBroadcast();
		void udpListener();
		void udpSender(string json);

		Json::Value resourceToJson(Resource* input);
		Resource resourceFromJson(Json::Value* json);

		Json::Value planetToJson(Planet* input);
		Planet planetFromJson(Json::Value* input);

		void deserializeConfig();
		void deserializeModificator();
		void deserializeSound();

		void addPlanet(Planet newPlanet);

		void relayResource(Resource* resource, string* planetName);
		void getNames();

		string getRandomPlanetType();
		float getRandomPlanetRadius();
		int getRandomStartAmount();

		View* getActiveView();
		Config getConfig();

		/*static int minStartAmount, maxStartAmount;
		static float habitableZone, maxRadius, minRadius;
		static vector<string> planetTypes, resourceTypes, viewTypes;
		static int roundDuration;*/
		static bool newRound();
	private:
		vector<Planet> planets;
		vector<Modificator> modificators;
		ofFile configFile, modificatorFile, generalConfigFile, soundFile;
		vector<View> views;
		View* activeView;
		vector<Planet*> planetsToDisplay;
		Json::Value configJson, modifyJson, soundJson;
		Json::Reader jsonReader;
		bool waitForInput,newPlayer, playerNameReady, planetNameReady, player1, player2;
		string inputString, newPlayerName, newPlanetName, outputString;
		int player;
		Config config;
		Sound sound;
		ofxUDPManager udpConnection;

};
