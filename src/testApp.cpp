#include "testApp.h"

bool compareByLength(Resource &a, Resource &b)
{
	return a.getAmount() > b.getAmount();
}

/*
 * The testApp will function as a controller. Relaying resources to/from planets via network
 */

/* static values used as config */
vector<string> testApp::planetTypes;
vector<string> testApp::resourceTypes;
vector<string> testApp::viewTypes;
float testApp::habitableZone = 500;
float testApp::maxRadius = 1000;
float testApp::minRadius = 10;

int testApp::minStartAmount = 0;
int testApp::maxStartAmount = 20;
//int testApp::self = testApp();

//--------------------------------------------------------------
void testApp::setup(){
	// TODO: init all views, all resources and local planets
	testApp::planetTypes.push_back("star");
	testApp::planetTypes.push_back("rock");
	testApp::planetTypes.push_back("gas");
	testApp::planetTypes.push_back("water");
	testApp::planetTypes.push_back("sun");

	testApp::resourceTypes.push_back("fire");
	testApp::resourceTypes.push_back("water");
	testApp::resourceTypes.push_back("gas");
	testApp::resourceTypes.push_back("rock");

	testApp::viewTypes.push_back("overview");
	testApp::viewTypes.push_back("singlePlanet");

	views.push_back(View("overview"));
	views.push_back(View("singlePlanet"));

	activeView = &views[0];
	this->config.open(ofToDataPath("config.json"), ofFile::ReadWrite, false);
	if( config.isFile() ) {
		// TODO read planet config from file
	}
	else {
		// TODO make a new planet for player
	}
}

//--------------------------------------------------------------
void testApp::update(){
	activeView->update(&this->planets);
}

//--------------------------------------------------------------
void testApp::draw(){
	activeView->draw(&this->planets);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
void testApp::udpBroadcast() {

}

void testApp::udpListener() {

}

void testApp::udpSender(string json) {

}

void testApp::showNotification(string title, string message) {

}

string testApp::getRandomPlanetType() {
	int random = (int)ofRandom((float)testApp::planetTypes.size());
	return testApp::planetTypes[random];
}
float testApp::getRandomPlanetRadius() {
	return ofRandom(testApp::minRadius, testApp::maxRadius);
}
int testApp::getRandomStartAmount() {
	return (int)ofRandom((float)testApp::minStartAmount, (float)testApp::maxStartAmount);
}

Json::Value testApp::resourceToJson(Resource* input) {

}
Resource testApp::resourceFromtJson(string json) {

}

Json::Value testApp::planetToJson(Planet* input) {

}
Planet* testApp::planetFromJson(string input) {

}
/*void testApp::relayResource(Resource* resource, string* planetName) {
	vector<Planet>::iterator it;
	for(it = planets.begin(); it < planets.end(); ++it) {
		if((*it).getName() == planetName) {
			(*it).getResource(resource);
			delete planetName;
			break;
		}
	}
}*/
