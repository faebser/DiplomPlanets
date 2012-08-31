#include "testApp.h"

/**
 * @class testApp
 * @brief Default-class from ofx
 * This class is the starting-point to the whole game.
 * It sets all other needed classes up.
 *
 */

//--------------------------------------------------------------
/**
 * Here we start the game up, read the files, load the classes
 */
void testApp::setup(){
	// TODO: init all views, all resources and local planets
	// TODO: make a config class and move everything there

	waitForInput = false;
	inputString = "";
	newPlayer = false;


	ofSetFrameRate(60);


	/**
	 * fire up the methods that load the files and sets up the config, the sound
	 * and the modificators
	 */
	deserializeConfig();
	deserializeSound();
	deserializeModificator();

	/*udpConnection.Create();
	udpConnection.SetEnableBroadcast(true);
	udpConnection.Bind(config.getNumber("udpPort"));
	udpConnection.BindMcast((char*)config.getString("multicastGroup").c_str(), config.getNumber("multicastPort"));
	udpConnection.ConnectMcast((char*)config.getString("multicastGroup").c_str(), config.getNumber("multicastPort"));
	udpConnection.SetNonBlocking(true);*/


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
	vector<string> viewList = config.getViewTypes();
	views.push_back(View(viewList[0]));
	views.push_back(View(viewList[1]));
	views[0].setConfig(&config);
	views[0].setModificators(&modificators);
	views[1].setConfig(&config);
	views[1].setModificators(&modificators);
	activeView = &views[0];
	config.setMiddle(&activeView->middle);
	config.setCam(&cam);
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
		Planet newPlanet = Planet(&config, &sound);
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
	udpListener();
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
	string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
//	string camStr = "camera pos: " + ofToString(cam.getOrientationEuler().x) + " / " + ofToString(cam.getOrientationEuler().y) + " / " + ofToString(cam.getOrientationEuler().z);
//	string camStr2 = "camera roll: " + ofToString(cam.getRoll());
	ofDrawBitmapString(fpsStr, 20,20);
//	ofDrawBitmapString(camStr, 20, 35);
//	ofDrawBitmapString(camStr2, 20, 45);
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
		Planet newPlanet = Planet(&config, &sound);
		newPlanet.setPlanetName("123");
		newPlanet.setPlayerName("1234");
		this->addPlanet(newPlanet);
	}
	else if(key == '1') {
		player = 1;
	}
	else if(key == '2') {
		player = 2;
	}
	switch(key) {
			case 'F':
			case 'f':
				ofToggleFullscreen();
				break;
			case OF_KEY_LEFT:
				cam.roll(-.5);
				break;
			case OF_KEY_RIGHT:
				cam.roll(+0.5);
				break;
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
	/*if(activeView->getType() == "overview"){
		vector<Planet>::iterator it = planets.begin(), en = planets.end();
		for(;it < en; it++) {
			ofVec2f pos = (*it).getPos();
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
	vector<Planet>::iterator it = planets.begin(), en = planets.end();
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
// nc -u 127.0.0.1 11999 connect via udp to localhost:11999
void testApp::udpListener() {
	/*char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message = udpMessage;
	if(message != "") {
		cout << message << endl;
	}*/
}

void testApp::udpSender(string json) {

}

void testApp::showNotification(string title, string message) {

}

string testApp::getRandomPlanetType() { //todo move into config
	vector<string> planetTypes = config.getPlanetTypes();
	int random = (int)ofRandom((float)planetTypes.size());
	return planetTypes[random];
}
float testApp::getRandomPlanetRadius() {
	return ofRandom(config.getNumber("minRadius"), config.getNumber("maxRadius"));
}
int testApp::getRandomStartAmount() {
	return (int)ofRandom(config.getNumber("minStartAmount"), config.getNumber("maxStartAmount"));
}
void testApp::exit() {
}

Config testApp::getConfig() {
		return config;
	}
void testApp::deserializeConfig() {
	this->generalConfigFile.open(ofToDataPath("generalConfig.json"), ofFile::ReadOnly, false);
		if(generalConfigFile.is_open()) {
			Json::Value generalConfig;
			bool parsingSuccessful = jsonReader.parse( this->generalConfigFile, generalConfig );
			if ( !parsingSuccessful ) {
				// report to the user the failure and their locations in the document.
				std::cout << "Failed to parse generalConfig-File\n"
						<< jsonReader.getFormatedErrorMessages();
				return;
			}
			else {
				config = Config(generalConfig);
				config.deserialize();
			}
		}
}
void testApp::deserializeSound() {
	this->soundFile.open(ofToDataPath("sound.json"), ofFile::ReadOnly, false);
	if(soundFile.is_open()) {
		Json::Value soundJson;
		bool parsingSuccessful = jsonReader.parse( this->soundFile, soundJson );
		if ( !parsingSuccessful ) {
			// report to the user the failure and their locations in the document.
			std::cout << "Failed to parse Sound-File\n"
					<< jsonReader.getFormatedErrorMessages();
			return;
		}
		else {
			sound = Sound(soundJson, config.getString("spaceCompareString"));
			sound.deserialize();
		}
	}
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
	this->modificatorFile.open(ofToDataPath("mod.json"), ofFile::ReadOnly, false);
	if(modificatorFile.is_open()) {
		bool parsingSuccessful = jsonReader.parse( this->modificatorFile, modifyJson );
		if ( !parsingSuccessful ) {
			// report to the user the failure and their locations in the document.
			std::cout << "Failed to parse mod-File\n"
					<< jsonReader.getFormatedErrorMessages();
			return;
		}
		else {
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
		//maybe quit here if file cannot be read
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
