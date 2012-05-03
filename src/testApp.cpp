#include "testApp.h"

/*
 * The testApp will function as a controller. Relaying resources to/from planets via network
 */

/* static values used as config */
vector<string> testApp::planetTypes ("fire", "rock", "gas", "water");
vector<string> testApp::resourecTypes ("fire", "water", "gas");

//--------------------------------------------------------------
void testApp::setup(){
	// TODO: init all views, all resources and local planets

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
