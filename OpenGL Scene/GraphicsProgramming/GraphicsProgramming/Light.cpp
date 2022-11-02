#include "Light.h"
Light::Light(LightType lightType, int id)
{
	//define & initialise default variables
	m_lightType = lightType;
	setId(id);
	setAttenuation(1.0f);
	setCutoff(25.0f);
	setExponent(50.0f);
	setDiffuse(Vector3(1.0f, 1.0f, 1.0f));
	setPosition(Vector3(0.0f, 0.0f, 0.0f));
	setAmbient(Vector3(0.6f, 0.6f, 0.6f));
	setDirection(Vector3(0.0f, -1.0f, 0.0f));
	
	//memory location for the light
	lightID = 0x4000 + m_id;
}

Light::~Light()
{

}

void Light::render()
{
	//sets variables into appropriate format for use
	GLfloat Light_Diffuse[] = { m_diffuse.x, m_diffuse.y, m_diffuse.z, 1.0f };
	GLfloat Light_Position[] = { m_position.x, m_position.y, m_position.z, 0.0f };
	GLfloat Light_Ambient[] = { m_ambient.x,  m_ambient.y,  m_ambient.z, 1.0f };
	GLfloat Spot_Direction[] = { m_direction.x,  m_direction.y,  m_direction.z };

	//changes light definitions based on what type of light source it is
	switch (m_lightType)
	{
	case LightType::DIRECTIONAL:
		Light_Position[3] = 0.0f;
		glLightfv(lightID, GL_AMBIENT, Light_Ambient);
		glLightfv(lightID, GL_DIFFUSE, Light_Diffuse);
		glLightfv(lightID, GL_POSITION, Light_Position);
		glLightf(lightID, GL_LINEAR_ATTENUATION, m_attenuation);
		break;
	case LightType::POINT:
		Light_Position[3] = 1.0f;
		glLightfv(lightID, GL_AMBIENT, Light_Ambient);
		glLightfv(lightID, GL_DIFFUSE, Light_Diffuse);
		glLightfv(lightID, GL_POSITION, Light_Position);
		glLightf(lightID, GL_LINEAR_ATTENUATION, m_attenuation);
		break;
	case LightType::SPOTLIGHT:
		Light_Position[3] = 1.0f;
		glLightfv(lightID, GL_AMBIENT, Light_Ambient);
		glLightfv(lightID, GL_DIFFUSE, Light_Diffuse);
		glLightfv(lightID, GL_POSITION, Light_Position);
		glLightfv(lightID, GL_SPOT_DIRECTION, Spot_Direction);
		glLightf(lightID, GL_SPOT_CUTOFF, m_cutoff);
		glLightf(lightID, GL_SPOT_EXPONENT, m_exponent);
		
		break;
	}
	
}

void Light::setAmbient(Vector3 ambient)
{
	m_ambient = ambient;
}

void Light::setDiffuse(Vector3 diffuse)
{
	m_diffuse = diffuse;
}

void Light::setPosition(Vector3 position)
{
	m_position = position;
}

void Light::setDirection(Vector3 direction)
{
	m_direction = direction;
}

void Light::setAttenuation(GLfloat attenuation)
{
	m_attenuation = attenuation;
}

void Light::setCutoff(GLfloat cutoff)
{
	m_cutoff = cutoff;
}

void Light::setExponent(GLfloat exponent)
{
	m_exponent = exponent;
}


void Light::setId(int id)
{
	m_id = id;
}

void Light::enable()
{
	glEnable(lightID);
}

void Light::disable()
{
	glDisable(lightID);
}

GLfloat* Light::getPosition()
{
	GLfloat pos[] = { m_position.x, m_position.y, m_position.z, 1.0f };
	return pos;

}

