#include "Sphere.h"
Sphere::Sphere()
{
	//define default variables
	PI = 3.1415;
	Delta = 0;
	Theta = 0;
	r = 3;
	rendered = false;
}

void Sphere::render(int longitude, int latitude, float radius, GLuint* texture)
{
	
	glBindTexture(GL_TEXTURE_2D, *texture);
	Theta = ((2 * PI) / latitude);
	Delta = (PI / longitude);
	r = radius;
	//create sphere object based on arguments given
	if (!rendered)
	{
		for (int i = 0; i < longitude; i++)
		{
			for (int j = 0; j < latitude; j++)
			{
				//math
				texCoords.push_back(j * (1.0f / longitude));
				texCoords.push_back(i * (1.0f / latitude));

				normals.push_back((r * (cos(Theta * j) * sin(Delta * i))));
				normals.push_back(r * (cos(Delta * i)));
				normals.push_back((r * (sin(Theta * j) * sin(Delta * i))));

				vertices.push_back((r * (cos(Theta * j) * sin(Delta * i))));
				vertices.push_back(r * (cos(Delta * i)));
				vertices.push_back((r * (sin(Theta * j) * sin(Delta * i))));

				texCoords.push_back(j * (1.0f / longitude) + (1.0f / longitude));
				texCoords.push_back(i * (1.0f / latitude));

				normals.push_back((r * (cos(Theta * (j + 1)) * sin(Delta * i))));
				normals.push_back(r * (cos(Delta * i)));
				normals.push_back((r * (sin(Theta * (j + 1)) * sin(Delta * i))));

				vertices.push_back((r * (cos(Theta * (j + 1)) * sin(Delta * i))));
				vertices.push_back(r * (cos(Delta * i)));
				vertices.push_back((r * (sin(Theta * (j + 1)) * sin(Delta * i))));

				texCoords.push_back(j * (1.0f / longitude) + (1.0f / longitude));
				texCoords.push_back(i * (1.0f / latitude) + (1.0f / latitude));

				normals.push_back((r * (cos(Theta * (j + 1)) * sin(Delta * (i + 1)))));
				normals.push_back(r * (cos(Delta * (i + 1))));
				normals.push_back((r * (sin(Theta * (j + 1)) * sin(Delta * (i + 1)))));

				vertices.push_back((r * (cos(Theta * (j + 1)) * sin(Delta * (i + 1)))));
				vertices.push_back(r * (cos(Delta * (i + 1))));
				vertices.push_back((r * (sin(Theta * (j + 1)) * sin(Delta * (i + 1)))));

				texCoords.push_back(j * (1.0f / longitude));
				texCoords.push_back(i * (1.0f / latitude) + (1.0f / latitude));

				normals.push_back((r * (cos(Theta * j) * sin(Delta * (i + 1)))));
				normals.push_back(r * (cos(Delta * (i + 1))));
				normals.push_back((r * (sin(Theta * j) * sin(Delta * (i + 1)))));

				vertices.push_back((r * (cos(Theta * j) * sin(Delta * (i + 1)))));
				vertices.push_back(r * (cos(Delta * (i + 1))));
				vertices.push_back((r * (sin(Theta * j) * sin(Delta * (i + 1)))));

			}
		}
		rendered = true;
	}
	


	//enable the vertex and associated vectors
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//point to the vectors before being drawn
	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

	//draw sphere
	glDrawArrays(GL_QUADS, 0, vertices.size() / 3.0f);

	//disable the vertex vector and associated vectors
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}