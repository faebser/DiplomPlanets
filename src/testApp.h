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
		Resource resourceFromtJson(string json);

		Json::Value planetToJson(Planet* input);
		Planet* planetFromJson(string input);

		static string getRandomPlanetType();
		static float habitableZone, maxRadius, minRadius;
		static vector<string> planetTypes, resourceTypes, viewTypes;
	private:
		vector<Planet> planets;
		vector<View> views;
		View* activeView;


};
