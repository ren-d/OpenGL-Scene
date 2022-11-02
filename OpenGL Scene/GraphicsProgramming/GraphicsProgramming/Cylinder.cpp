#include "Cylinder.h"
Cylinder::Cylinder()
{

}

void Cylinder::render(float length, float segments, float radius, GLuint* texture)
{
	Theta = 0.0f;
	r = radius;

	PI = 3.1415;
	glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_TRIANGLES);
	//creates the cap for the start of the cylinder
	for (int i = 0; i <= (segments * 2); i++)
	{

		//math

		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);
		glTexCoord2f(cosf(Theta) / (r * 2) + 0.5, sinf(Theta) / (r * 2) + 0.5);
		glVertex3f(X, Y, 0);


		Theta += (2 * PI) / segments;
		X = r * cosf(Theta);
		Y = r * sinf(Theta);
		glTexCoord2f(cosf(Theta) / (r * 2) + 0.5, sinf(Theta) / (r * 2) + 0.5);
		glVertex3f(X, Y, 0);
		i++;
	}
	glEnd();
	glBegin(GL_QUADS);

	//creates main sections of the cylinder
	for (int j = 0; j < length; j++)
	{
		for (int i = 0; i <= (segments * 2); i++)
		{

			//more math
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.2, 0.2);

			glVertex3f(X, Y, j + 1);
			glTexCoord2f(0.2, 0.8);
			glVertex3f(X, Y, j);

			Theta += (2 * PI) / segments;
			X = r * cosf(Theta);
			Y = r * sinf(Theta);
			glTexCoord2f(0.8, 0.8);
			glVertex3f(X, Y, j);
			glTexCoord2f(0.8, 0.2);
			glVertex3f(X, Y, j + 1);
			i++;
		}
	}
	glEnd();

	glBegin(GL_TRIANGLES);

	//caps the other end of the cylinder
	for (int i = 0; i <= (segments * 2); i++)
	{


		//and some extra math
		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, length);
		glTexCoord2f(cosf(Theta) / (r * 2) + 0.5, sinf(Theta) / (r * 2) + 0.5);
		glVertex3f(X, Y, length);


		Theta += (2 * PI) / segments;
		X = r * cosf(Theta);
		Y = r * sinf(Theta);
		glTexCoord2f(cosf(Theta) / (r * 2) + 0.5, sinf(Theta) / (r * 2) + 0.5);
		glVertex3f(X, Y, length);
		i++;
	}
	glEnd();
}