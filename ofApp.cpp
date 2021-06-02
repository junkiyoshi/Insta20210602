#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	int size = 30;
	int direction = 1;

	for (int z = -500; z < 0; z += 10) {

		float noise_param = ofRandom(1000);
		direction *= -1;
		for (int x = -200; x <= 200; x += size) {

			int height = ofMap(ofNoise(noise_param, x * 0.003 + (ofGetFrameNum() * ofMap(z, 0, -500, 0.025, 0.001) * direction)), 0, 1, 0, 100 + std::abs(z));

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x - size * 0.5, 0, z));
			vertices.push_back(glm::vec3(x - size * 0.5, height, z));
			vertices.push_back(glm::vec3(x + size * 0.5, height, z));
			vertices.push_back(glm::vec3(x + size * 0.5, 0, z));

			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
			this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

			this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
			this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
			this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
			this->line.addIndex(this->line.getNumVertices() - 4); this->line.addIndex(this->line.getNumVertices() - 1);

			if (direction == -1) {

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(ofColor(239));
					this->line.addColor(ofColor(39));
				}
			}
			else {

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(ofColor(39));
					this->line.addColor(ofColor(239));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}