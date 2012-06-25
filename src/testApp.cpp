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
int testApp::maxStartAmount = 5;
int testApp::roundDuration = 10000;

//--------------------------------------------------------------
void testApp::setup(){
	// TODO: init all views, all resources and local planets
	waitForInput = false;
	inputString = "";
	newPlayer = false;

	ofSetFrameRate(60);

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
		this->addPlanet(this->planetFromJson(&this->configJson));
	}
	else {
		newPlayer = true;
		waitForInput = true;
		newPlanetName = "";
		newPlayerName = "";
		planetNameReady = false;
		playerNameReady = false;
	}
	this->modificatorFile.open(ofToDataPath("mod.json"), ofFile::ReadOnly, false);
	if(modificatorFile.is_open()) {
		bool parsingSuccessful = jsonReader.parse( this->modificatorFile, modifyJson );
		if ( !parsingSuccessful ) {
			// report to the user the failure and their locations in the document.
			std::cout << "Failed to parse Mod-File\n"
					<< jsonReader.getFormatedErrorMessages();
			return;
		}
		else {
			deserializeModificator();
		}
		//maybe quit here if file cannot be read
	}
}
void testApp::getNames() {
	if(waitForInput == true) {
		if(planetNameReady == false) {
			outputString = "Pleaser enter your Planets Name: ";
			outputString.append(inputString);
		}
		if(playerNameReady == false && planetNameReady == true) {
			outputString = "Pleaser enter your Name: ";
			outputString.append(inputString);
		}
		ofDrawBitmapString(outputString, 100, 100);
	}
	else if(waitForInput == false && planetNameReady == true && playerNameReady == true) {
		Planet newPlanet = Planet(this);
		newPlanet.setPlanetName(newPlanetName);
		newPlanet.setPlayerName(newPlayerName);
		this->addPlanet(newPlanet);
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
		activeView->draw(this->planetsToDisplay);
	}
	string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2)+ " // player: " + ofToString(player);
	ofDrawBitmapString(fpsStr, 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key != OF_KEY_RETURN && waitForInput == true) {
		inputString.append(ofToString((char)key));
		if(planetNameReady == false) {
			newPlanetName.append(inputString);
		}
		if(playerNameReady == false && planetNameReady == true) {
			newPlayerName.append(inputString);
		}
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
		this->addPlanet(Planet(this));
	}
	else if(key == '1') {
		player = 1;
	}
	else if(key == '2') {
		player = 2;
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
	if(activeView->getType() == "overview"){
		vector<Planet>::iterator it = planets.begin(), en = planets.end();
		for(;it < en; it++) {
			ofVec2f pos = (*it).getPos(this->activeView);
			if(ofDist(pos.x, pos.y, x, y) < (*it).getSize()) {
				this->planetsToDisplay.clear();
				this->planetsToDisplay.push_back(&(*it));
				this->activeView = &views[1];
				break;
			}
		}
	}
	else if(activeView->getType() == "singlePlanet") {
		this->planetsToDisplay.clear();
		vector<Planet>::iterator it = this->planets.begin(), end = this->planets.end();
		for(;it < end; ++it) {
			this->planetsToDisplay.push_back(&(*it));
		}
		this->activeView = &views[0];
	}
	/*vector<Planet>::iterator it = planets.begin(), en = planets.end();
	for(;it < en; ++it) {
		ofVec2f* pos = (*it).getPos();
		if(ofDist(pos->x, pos->y, x, y) < (*it).getSize()) {
			(*it).clicked(player);
			break;
		}
	}*/
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	this->activeView->windowResize(w,h);
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
View* testApp::getActiveView() {
	return this->activeView;
}
Json::Value testApp::resourceToJson(Resource* input) {

}
Resource testApp::resourceFromJson(Json::Value* json) {

}

Json::Value testApp::planetToJson(Planet* input) {

}
Planet testApp::planetFromJson(Json::Value* input) {

}
void testApp::deserializeModificator() {
	if(modificators.size() > 0) {
		modificators.clear();
	}
	vector<string> modificatorNamesList = modifyJson.getMemberNames();
	vector<string>::iterator it = modificatorNamesList.begin(), end = modificatorNamesList.end();
	for(;it < end; ++it) {
		Modificator newMod = Modificator((*it));
		newMod.deserialize(&(modifyJson[(*it)]));
		modificators.push_back(newMod);
	}

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
void testApp::addPlanet(Planet planet) {
	if(this->activeView->getType() == "overview") {
		this->planets.push_back(planet);
		this->planetsToDisplay.push_back(&(this->planets.back()));
	}
	else if(this->activeView->getType() == "singlePlanet") {
		this->planets.push_back(planet);
	}

}
