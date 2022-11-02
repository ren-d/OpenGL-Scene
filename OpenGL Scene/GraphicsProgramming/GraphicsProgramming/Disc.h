#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <vector>
#include <gl/glu.h>
#include "Vector3.h"
class Disc
{
public:

	Disc();

	void render(float radius, float segments, GLuint* texture);

	//variables
	float X, Y, r, Theta, PI;
};

