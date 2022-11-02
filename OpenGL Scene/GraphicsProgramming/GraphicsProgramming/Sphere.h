#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <vector>
#include <gl/glu.h>
#include "Vector3.h"
class Sphere
{
public:
	Sphere();
	void render(int longitude, int latitude, float radius, GLuint* texture);

	//variables for use in creation of the sphere
	float Theta, Delta, X, Y, Z, r, PI;
	int longitude, latitude;
	std::vector<GLfloat> vertices, normals, texCoords;
	bool rendered;
};

