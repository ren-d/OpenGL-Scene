#pragma once
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <string>
using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include "string.h"
#include "Light.h";
class Lighting
{

public:
	Lighting();
	~Lighting();

	void update(float dt);
	void handleInput(float dt, Input* input);
	void render();

	// enable/disables lights
	void enableLight(int id);
	void disableLight(int id);

	//getters
	float* getPosition(int id);

	//stores all the lights
	vector<Light*> lights;

};

