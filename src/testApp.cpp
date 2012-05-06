#include "testApp.h"

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

//--------------------------------------------------------------
void testApp::setup(){
	// TODO: init all views, all resources and local planets
	testApp::planetTypes.push_back(string("star"));
	testApp::planetTypes.push_back(string("rock"));
	testApp::planetTypes.push_back(string("gas"));
	testApp::planetTypes.push_back(string("water"));
	testApp::planetTypes.push_back(string("sun"));

	testApp::resourceTypes.push_back("fire");
	testApp::resourceTypes.push_back("water");
	testApp::resourceTypes.push_back("gas");

	testApp::viewTypes.push_back("overview");
	testApp::viewTypes.push_back("singlePlanet");
}

//--------------------------------------------------------------
void testApp::update(){
	// TODO: update all planets
}

//--------------------------------------------------------------
void testApp::draw(){
	// TODO: invoke active view and draw
	//activeView.draw();
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

Json::Value resourceToJson(Resource* input) {

}
Resource resourceFromtJson(string json) {

}

Json::Value planetToJson(Planet* input) {

}
Planet* planetFromJson(string input) {

}
