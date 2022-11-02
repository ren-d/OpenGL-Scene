#include "Skybox.h"
Skybox::Skybox(GLuint* texture)
{
	m_texture = *texture;

}

Skybox::~Skybox()
{

}

void Skybox::update(float dt)
{

}

void Skybox::render()
{
	//create skybox object
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//front

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	//right
	
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//bottom

	glTexCoord2f(0.25f, 0.75f);
	
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.5f);

	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.75f);
	
	glVertex3f(0.5f, -0.5f, -0.5f);

	//back


	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.5f);

	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//top

	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//left

	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
}