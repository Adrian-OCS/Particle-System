#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;
	currentAction = DEFAULT_ACTION;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	currentAction = DEFAULT_ACTION;
	currentShape = CIRCLE;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].setShape(currentShape);
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].update();
		//conducts the associated action in the vector every 2 seconds
		if 	(frames<=60*vectorOfKeysPressed.size() && conductReplay){
			//cancels replay of vector is empty
			if (vectorOfKeysPressed.size()==0) conductReplay = false;

			else if ((frames%60)==0) keyPressed(vectorOfKeysPressed[counter]);
		}
		p[i].setMode(currentMode);
		p[i].setAction(currentAction);
		p[i].setShape(currentShape);
	}
	currentAction = DEFAULT_ACTION;
	if(conductReplay){
		//adjusts the counter for the vector every 2 seconds
		if 	(frames%60==0) counter++;
		//clears the vector and counter when replay is over
		if (counter>=vectorOfKeysPressed.size()){
			vectorOfKeysPressed.clear();
			counter=0;
			conductReplay = false;
		}
		frames++;
	}
	else {
		frames=0;
	}

	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(255,255,255), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(190);
	//draws the shape chosen by the user (BONUS - ADDED SHAPES)
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			if(currentShape == CIRCLE){
				ofNoFill();
				ofDrawCircle(attractPointsWithMovement[i], 10);
			}
			else if(currentShape == RECTANGLE){
				ofNoFill();
				ofDrawRectangle(attractPointsWithMovement[i], 10, 10);
			}
			if(currentShape == CIRCLE){
				ofFill();
				ofDrawCircle(attractPointsWithMovement[i], 4);
			}
			else if(currentShape == RECTANGLE){
				ofFill();
				ofDrawRectangle(attractPointsWithMovement[i], 4, 4);
			}
		}
	}

	//Adds recording indicator

	if ( recordKeysPressed ) {
		ofSetColor(255, 0, 0);
		ofDrawCircle(ofGetWidth()-50, 50, 10);
	}

	//Adds replaying indicator

	if ( conductReplay ) {
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("REPLAYING", ofGetWidth()-100, 50);
	}

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset.\nKeys: 1-4 to change mode, A/a to pause\nPress I or i to triple particle size\nPress D or d to third particle size\nPress F or f to quadruple particle velocity\nPress S or s to quarter particle velocity\nPress R or r to start/end recording\nPress P or p to start replaying recorded keys\nPress C or c to cancel replaying recorded keys\nPress T or t to turn shapes into rectangles\nPress Y or y tu return shapes to circles", 15, 25);}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	key=toupper(key);

	//cancels replay
	if( (key == 'C') && conductReplay){
	conductReplay = false;
	vectorOfKeysPressed.clear();
	counter=0;
	}

	//prevents any actions from performing while in replay
	if (conductReplay && frames%60!=0){
		key=-1;
	}

	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 		
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
	}


	if( key == ' ')	{
		resetParticles();
	}


	if( key == 'A'){
		currentMode = PARTICLE_MODE_PAUSE;
		currentModeStr = "A/a- PARTICLE_MODE_PAUSE: pauses particles in place";
	}

	if( key == 'I'){
		currentAction = TRIPLE_PARTICLE_SIZE;
	}

	if( key == 'D'){
		currentAction = THIRD_PARTICLE_SIZE;
	}

	if( key == 'F'){
		currentAction = QUADRUPLE_PARTICLE_VELOCITY;
	}

	if( key == 'S'){
		currentAction = QUARTER_PARTICLE_VELOCITY;
	}


	if( key == 'R'){
		if(!recordKeysPressed && !conductReplay){
			recordKeysPressed = true;
		}
		else {
			recordKeysPressed = false;
		}
	}

	if( (key == 'P') && !recordKeysPressed){
		conductReplay = true;
	}

	if ( recordKeysPressed && key!='R' && key!='P'){
		vectorOfKeysPressed.push_back(key);
	}

	if( key == 'T'){
		currentShape = RECTANGLE;
	}

	if( key == 'Y'){
		currentShape = CIRCLE;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
