#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include "Vector3.h"
class Light
{
public:
	//light enum defining different types of lights
	enum class LightType
	{
		SPOTLIGHT = 0,
		DIRECTIONAL = 1,
		POINT = 2
	};
	
	Light(LightType lightType, int id);
	~Light();

	void render();

	//getters & setters
	GLfloat* getPosition();
	void setDiffuse(Vector3 diffuse);
	void setPosition(Vector3 position);
	void setDirection(Vector3 direction);
	void setAmbient(Vector3 ambient);
	void setCutoff(GLfloat cutoff);
	void setAttenuation(GLfloat attenuation);
	void setExponent(GLfloat exponent);
	void setId(int id);
	
	//enable/disable light
	void disable();
	void enable();
	
private:
	//member variables
	Vector3 m_diffuse, m_position, m_direction, m_ambient;
	GLfloat m_cutoff, m_attenuation, m_exponent;
	LightType m_lightType;
	int m_id;
	//memory location of the light
	GLenum lightID;
};

