#include "ofApp.h"

ofApp::ofApp(std::string path)
{
    std::cout << "Root path is set." << std::endl;
    rootPath = path;
}
//--------------------------------------------------------------
void ofApp::setup(){
    
    std::cout << "Setup UI..." << std::endl;
    gui.setup();
    gui.setName("Audio t-SNE");
    gui.add(maxDuration.set("maxDuration", 1.0, 0.1, 2.0));
    gui.add(mouseRadius.set("mouseRadius", 250, 100, 500));
    gui.add(pauseLength.set("pauseLength", 2.0, 0.2, 5.0));
    
    //string file = "points.json";
    std::cout << "Read JSON..." << std::endl;
    ofxJSONElement result;
    std::ifstream inputFile;
    inputFile.open(rootPath + "/points.txt", std::ios::in);
    std::string content;
    std::getline(inputFile, content);
    
    
    bool parsingSuccessful = result.parse(content);
    //bool parsingSuccessful = result.open(file);
    std::cout << "Load data to memory..." << std::endl;
    for (int i=0; i<result.size(); i++) {
        std::cout << "Loading sample " << i << std::endl;
        string path = result[i]["path"].asString();
        float x = result[i]["point"][0].asFloat();
        float y = result[i]["point"][1].asFloat();
        float r = result[i]["color"][0].asFloat();
        float g = result[i]["color"][1].asFloat();
        float b = result[i]["color"][2].asFloat();
        
        AudioClip newSound;
        newSound.sound.load(path);
        newSound.point.set(x, y);
        newSound.color.set(r, g, b);
        newSound.t = 0;
        sounds.push_back(newSound);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<sounds.size(); i++) {
        if (sounds[i].sound.isPlaying() && sounds[i].sound.getPositionMS() > maxDuration*1000) {
            sounds[i].sound.stop();
        }
    }
    ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(100), ofColor(20));
    for (int i=0; i<sounds.size(); i++) {
        if (sounds[i].sound.isPlaying()) {
            ofSetColor(0, 255, 0, 180);
        }
        else {
            ofSetColor(sounds[i].color);
        }
        ofDrawCircle(ofGetWidth() * sounds[i].point.x, ofGetHeight() * sounds[i].point.y, 4);

    }
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    for (int i=0; i<sounds.size(); i++) {
        float distanceToMouse = ofDistSquared(x, y, ofGetWidth() * sounds[i].point.x, ofGetHeight() * sounds[i].point.y);
        if (distanceToMouse < mouseRadius && !sounds[i].sound.isPlaying() && (ofGetElapsedTimef() - sounds[i].t > pauseLength)) {
            sounds[i].t = ofGetElapsedTimef();
            sounds[i].sound.play();
        }
    }
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
