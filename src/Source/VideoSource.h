#pragma once

#include "ofMain.h"

#include "ImOf.h"
#include "BaseSource.h"

class VideoSource : public BaseSource {
public:
	
	VideoSource() {}
	
	void setup() {}
	
	void loadSettings(ofxXmlSettings &settings) {
		
		settings.pushTag("video");
		
		file.open( settings.getValue("path", "") );
		if (file.exists()) {
			willOpen = true;
		}
		
		settings.popTag();
	}
	
	void saveSettings(ofxXmlSettings &settings) {
		
		settings.addTag("video");
		settings.pushTag("video");
		
		if (player.isLoaded()) {
			settings.setValue("path", file.getAbsolutePath());
		}
		
		settings.popTag();
	}
	
	void update() {
		if (willOpen) {
			load(file.getAbsolutePath());
		}
		
		if (player.isLoaded()) {
			player.update();
		}
	}
	
	ofTexture& getTexture() {
		if (player.isLoaded()) {
			return player.getTexture();
		} else {
			return std::ref(DefaultTexture);
		}
	}
	
	void bind(int textureLocation) {
		if (player.isLoaded()) {
			player.getTexture().bind(textureLocation);
		} else {
			DefaultTexture.bind();
		}
	}
	
	void unbind(int textureLocation) {
		if (player.isLoaded()) {
			player.getTexture().unbind(textureLocation);
		} else {
			DefaultTexture.unbind();
		}
	}
	
	void drawImGui() {
		
		if (ImGui::Button("Load Video")) {
			
			ofFileDialogResult result = ImOf::SystemLoadDialog("Load Video File", false, ofToDataPath("."));
			
			if (result.bSuccess) {
				load(result.getPath());
			} else {
				showFailedModal = true;
			}
		}
		
		ImGui::SameLine();
		ImGui::Text("%s", player.isLoaded() ? file.getFileName().c_str() : "(No Video)");
		
		if (player.isLoaded()) {
			float pos = player.getPosition();
			float sec = player.getDuration() * pos;
			string secText = ofToString(sec, 1) + "s";
			
			if (ImGui::SliderFloat(secText.c_str(), &pos, 0.0f, 1.0f, "")) {
				player.setPosition(pos);
			}
			
			if (ImGui::Button(player.isPlaying() ? "Pause" : "Play", ImVec2(40.0f, 22.0f))) {
				player.setPaused( player.isPlaying() );
			}
		}
		
		ImOf::Alert("Unkown Video Foramt", "Failed to load the video as texture.", &showFailedModal);
	}
	
	//--------------------------------------------------------------
	// custom methods
	
	string getName() { return "Video"; }
	bool isFlipped() { return false; }
	
private:
	
	void load(string path) {
		player.load(path);
		file.open(path);
		
		if (player.isLoaded()) {
			player.play();
		} else if (!willOpen) {
			showFailedModal = true;
		}
		
		willOpen = false;
	}
	
	bool showFailedModal = false;
	
	bool	willOpen = false;
	
	ofFile file;
	ofVideoPlayer player;
};