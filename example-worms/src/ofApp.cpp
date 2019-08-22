#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setupPerspective(false, 60, 1, 5000);

	scene = bind(&ofApp::renderScene, this);

	ofDisableArbTex();
    cubeMap.load("Barce_Rooftop_C_3k.jpg", 1024, true, "filteredMapCache");
	cubeMap.setEnvLevel(0.3);

    pbr.setup(scene, &cam, 1024);
    pbr.setCubeMap(&cubeMap);
	
	pbr.setDrawEnvironment(false);
	//pbr.setDrawEnvironment(true);

	// directionalLight
	directionalLight.setup();
	directionalLight.setLightType(LightType_Directional);
	//directionalLight.setShadowType(ShadowType_Soft);
	directionalLight.setShadowType(ShadowType_Hard);

	pbr.addLight(&directionalLight);
	pbr.setUsingCameraFrustomForShadow(false);
	pbr.setDirectionalShadowBBox(0, 0, 0, 1000, 1000, 1000);

	// pointLight
	pointLight.setup();
	pointLight.setLightType(LightType_Point);
	pbr.addLight(&pointLight);

	// spotLight
	spotLight.setup();
	spotLight.setLightType(LightType_Spot);
	spotLight.setShadowType(ShadowType_Soft);
	pbr.addLight(&spotLight);

	// material
	ofDisableArbTex();
	groundBaseColor.load("pbrTextures/basecolor.png");
	groundMetallic.load("pbrTextures/metallic.png");
	groundRoughness.load("pbrTextures/roughness.png");
	groundNormal.load("pbrTextures/normal.png");
	groundMaterial.baseColorMap = &groundBaseColor.getTexture();
	groundMaterial.metallicMap = &groundMetallic.getTexture();
	groundMaterial.roughnessMap = &groundRoughness.getTexture();
	groundMaterial.normalMap = &groundNormal.getTexture();

	// gui
	gui.setup();
	gui.add(materialColor.set("material color", ofFloatColor(1.0), ofFloatColor(0.0), ofFloatColor(1.0)));
	gui.add(enableDerectionalLight.set("directional light", true));
	gui.add(directionalLightColor.set("directional light color", ofFloatColor(1.0), ofFloatColor(0.0), ofFloatColor(1.0)));
	gui.add(enablePointLight.set("point light", false));
	gui.add(pointLightColor.set("point light color", ofFloatColor(1.0), ofFloatColor(0.0), ofFloatColor(1.0)));
	gui.add(enableSpotLight.set("spot light", false));
	gui.add(spotLightColor.set("spot light color", ofFloatColor(1.0), ofFloatColor(0.0), ofFloatColor(1.0)));
}

//--------------------------------------------------------------
void ofApp::update(){
	// update Lights
	directionalLight.setPosition(500 * cos(ofGetElapsedTimef()), 500, 500 * sin(ofGetElapsedTimef()));
	directionalLight.lookAt(glm::vec3(0), glm::vec3(0.0, 1.0, 0.0));

	pointLight.setPosition(150 * cos(ofGetElapsedTimef()), 250, 150 * sin(ofGetElapsedTimef()));

	spotLight.setPosition(-250 * cos(ofGetElapsedTimef()), 500, -250 * sin(ofGetElapsedTimef()));
	spotLight.lookAt(glm::vec3(0), glm::vec3(0.0, 1.0, 0.0));

	// update material
	material.baseColor = materialColor;

	// update light parameters
	directionalLight.setEnable(enableDerectionalLight);
	directionalLight.setColor(directionalLightColor);

	pointLight.setEnable(enablePointLight);
	pointLight.setColor(pointLightColor);

	spotLight.setEnable(enableSpotLight);
	spotLight.setColor(spotLightColor);
}

//--------------------------------------------------------------
void ofApp::draw(){
	pbr.updateDepthMaps();

	cam.begin();
	pbr.renderScene();
	cam.end();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::renderScene(){
	ofBackground(0);

	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	pbr.beginDefaultRenderer();
    {
		// draw ground
		groundMaterial.begin(&pbr);
		ofPushMatrix();
		ofTranslate(0, -35, 0);
		ofRotateX(-90);
		//ofDrawPlane(2000, 2000);
		ofPopMatrix();
		groundMaterial.end();
        

		ofSetCylinderResolution(50,3,2);

		// draw spheres
        for(int i=0;i<10;i++){
			material.roughness = 0.1;//float(i) / 9.0;
            for(int j=0;j<10;j++){
				material.metallic = 0.8; // float(j) / 9.0;
                
				if (j % 2 == 0) material.begin(&pbr);
				else groundMaterial.begin(&pbr);

				ofPushMatrix();
				float x = i * 100 - 450;
				float y = 0;
				float z = j * 100 - 450;
				ofTranslate(x, y, z);

				ofRotateX(i*10.0);
				ofRotateY(y*5.0);

				ofDrawCylinder(5, 300);

				//ofDrawSphere(i * 100 - 450, 0, j * 100 - 450, 35);
				for (int q = -20; q <= 20; q++) {
					float r = ofMap(abs(q), 0, 20, 15, 5);
					ofDrawSphere(0, q*5, 0, r);
				}

				ofPopMatrix();

				if (j % 2 == 0) material.end();
				else groundMaterial.end();

            }
        }
	}
	pbr.endDefaultRenderer();
	glDisable(GL_CULL_FACE);
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
