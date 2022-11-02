#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include "Vector3.h"
#include "Sphere.h"

//TODO Integrate skybox class into Create Class
class Skybox
{
public:
	Skybox(GLuint* texture);
	~Skybox();

	void update(float dt);
	void render();

	//skybox texture
	GLuint m_texture;

};

