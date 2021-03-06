#pragma once

#include "ofMain.h"

// addons
#include "ofxImGui.h"

#include "CameraInfo.h"

#include "BaseManager.h"

#include "SceneManager.h"
#include "ViewManager.h"
#include "SourceManager.h"
#include "MiscManager.h"

class ofApp : public ofBaseApp{

public:
	
	// default funcs
	void setup();
	void update();
	void draw();
	void exit();
	
	void drawImGui();
	
	void keyReleased(int key);
	void dragEvent(ofDragInfo dragInfo);
	
	void onCameraListImport(vector<CameraInfo> &cameraList);
	
	// variables
	
	// managers
	vector<BaseManager*>	managers;
	SceneManager			sceneManager;
	ViewManager				viewManager;
	SourceManager			sourceManager;
	MiscManager				miscManager;
	
	// gui
	ofxImGui::Gui		gui;
	bool				showControl;
	
};
