#include "Disc.h"



Disc::Disc()
{


}

void Disc::render(float radius, float segments, GLuint* texture)
{
	//renders a disc based on the radius and segments(resolution)
	glBindTexture(GL_TEXTURE_2D, *texture);
	Theta = 0.0f;
	r = radius;

	PI = 3.1415;
	glBegin(GL_TRIANGLES);

	for (int i = 0; i <= (segments * 2); i++)
	{

		//maths

		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);
		glTexCoord2f(cosf(Theta) / (2 * 2) + 0.5, sinf(Theta) / (2 * 2) + 0.5);
		glVertex3f(X, Y, 0);


		Theta += (2 * PI) / segments;
		X = r * cosf(Theta);
		Y = r * sinf(Theta);
		glTexCoord2f(cosf(Theta) / (2 * 2) + 0.5, sinf(Theta) / (2 * 2) + 0.5);
		glVertex3f(X, Y, 0);
		i++;
	}
	glEnd();
}