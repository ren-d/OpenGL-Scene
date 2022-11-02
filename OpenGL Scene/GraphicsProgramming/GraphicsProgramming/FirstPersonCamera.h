#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include "Vector3.h"
class FirstPersonCamera
{
public:

	
	Input* input;


	FirstPersonCamera(Input* in, float fspeed, bool isStatic);
	~FirstPersonCamera();

	void update(float dt, int width, int height);
	void handleInput(float dt);

	//getters and setters
	Vector3 getPosition();
	Vector3 getLookat();
	Vector3 getUp();
	Vector3 getRotation();
	void setPosition(Vector3 pos);
	void setRotation(Vector3 rot);
private:
	//variables
	Vector3 position, rotation, lookat, up, forward, right, mouseDistanceMoved, screenSize;
	bool m_isStatic;
	float m_speed = 2;
};

