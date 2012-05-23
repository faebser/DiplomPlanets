#pragma once

#include "ofMain.h"
#include "Planet.h"
#include "View.h"
#include "json/json.h"

//example für json shttp://jsoncpp.sourceforge.net/

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

		void addPlanet(Planet newPlanet);

		void relayResource(Resource* resource, string* planetName);
		void getNames();

		static string getRandomPlanetType();
		static float getRandomPlanetRadius();
		static int getRandomStartAmount();

		static int minStartAmount, maxStartAmount;
		static float habitableZone, maxRadius, minRadius;
		static vector<string> planetTypes, resourceTypes, viewTypes;
		static int roundDuration;
		static bool newRound();
	private:
		vector<Planet> planets;
		ofFile configFile;
		vector<View> views;
		View* activeView;
		vector<Planet*> planetsToDisplay;
		Json::Value configJson;
		Json::Reader jsonReader;
		bool waitForInput,newPlayer, playerNameReady, planetNameReady, player1, player2;
		string inputString, newPlayerName, newPlanetName;
		int player;
};
