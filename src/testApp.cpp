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
float testApp::minRadius = 50;

int testApp::minStartAmount = 0;
int testApp::maxStartAmount = 20;

//--------------------------------------------------------------
void testApp::setup(){
	// TODO: init all views, all resources and local planets
	waitForInput = false;
	inputString = "";
	newPlayer = false;

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
	this->configFile.open(ofToDataPath("config.json"), ofFile::ReadWrite, false);
	if( configFile.is_open() ) {
		// TODO read planet config from file
		bool parsingSuccessful = jsonReader.parse( this->configFile, configJson );
		if ( !parsingSuccessful ) {
			// report to the user the failure and their locations in the document.
			std::cout << "Failed to parse configuration\n"
					<< jsonReader.getFormatedErrorMessages();
			return;
		}
		planets.push_back(this->planetFromJson(&this->configJson));
	}
	else {
		newPlayer = true;
		waitForInput = true;
		newPlanetName = "";
		newPlayerName = "";
		planetNameReady = false;
		playerNameReady = false;
	}
}
void testApp::getNames() {
	if(waitForInput == true) {
		if(planetNameReady == false) {
			string outputString = "Pleaser enter your Planets Name: ";
			outputString.append(inputString);
			ofDrawBitmapString(outputString, 100, 100);
			newPlanetName.append(inputString);
		}
		if(playerNameReady == false && planetNameReady == true) {
			string outputString = "Pleaser enter your Name: ";
			outputString.append(inputString);
			ofDrawBitmapString(outputString, 100, 100);
			newPlayerName.append(inputString);
		}
	}
	else if(waitForInput == false && planetNameReady == true && playerNameReady == true) {
		Planet newPlanet = Planet(this);
		newPlanet.setPlanetName(newPlanetName);
		newPlanet.setPlayerName(newPlanetName);
		planets.push_back(newPlanet);
		waitForInput = false;
		newPlayer = false;
	}
}
//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0);
	activeView->update(&this->planets);
}

//--------------------------------------------------------------
void testApp::draw(){
	if(newPlayer == true) {
		this->getNames();
	}
	else {
		activeView->draw(&this->planets);
	}
	string playerString;
	if(player1) {
		playerString = "player 1";
	}
	else if(player2) {
		playerString = "player 2";
	}
	string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2)+ " // player: " + playerString;
	ofDrawBitmapString(fpsStr, 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key != OF_KEY_RETURN && waitForInput == true) {
		inputString.append(ofToString((char)key));
	}
	else if(key == OF_KEY_RETURN && waitForInput == true) {
		if(playerNameReady == false) {
			if(newPlayerName.compare("") != 0) {
				playerNameReady = true;
				inputString.clear();
			}
		}
		if(planetNameReady == false) {
			if(newPlanetName.compare("") != 0) {
				planetNameReady = true;
				inputString.clear();
			}
		}
		else {
			waitForInput = false;
		}
	}
	else if(key == 'n') {
		planets.push_back(Planet(this));
	}
	else if(key == '1') {
		player1 = true;
		player2 = false;
	}
	else if(key == '2') {
		player2 = true;
		player1 = false;
	}
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
	vector<Planet>::iterator it = planets.begin(), en = planets.end();
	for(;it < en; ++it) {
		ofVec2f* pos = (*it).getPos();
		if(ofDist(pos->x, pos->y, x, y) < (*it).getSize()) {
			(*it).clicked();
			break;
		}
	}
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
Resource testApp::resourceFromJson(Json::Value* json) {

}

Json::Value testApp::planetToJson(Planet* input) {

}
Planet testApp::planetFromJson(Json::Value* input) {

}
void testApp::relayResource(Resource* resource, string* planetName) {
	vector<Planet>::iterator it;
	for(it = planets.begin(); it < planets.end(); ++it) {
		if((*it).getPlanetName() == planetName) {
			(*it).getResource(resource);
			delete planetName;
			break;
		}
	}
}
