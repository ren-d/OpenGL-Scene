#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <vector>
#include <gl/glu.h>
#include "Vector3.h"
class Cylinder
{
public:
	Cylinder();

	void render(float length, float segments, float radius, GLuint* texture);

	//variables to calculate cylinder
	float Theta, Delta, X, Y, Z, r, PI;
	int longitude, latitude;
};

