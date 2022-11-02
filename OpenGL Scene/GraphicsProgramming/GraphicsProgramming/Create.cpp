#include "Create.h"
Create::Create()
{
	//external geometry object definitions
	sphere = new Sphere();
	cylinder = new Cylinder();
	disc = new Disc();
	modelLoader = new ModelLoader();


	LoadModels();


}

void Create::LoadModels()
{
	//declaration for all models used in the project along with textures, keywords are used as the last argument to define said models
	modelLoader->load("models/spaceship.obj", "models/spaceship.jpg", "Spaceship");
	modelLoader->load("models/drone.obj", "models/Drone_Diff.jpg", "Drone");
	modelLoader->load("models/knuckles.obj", "gfx/coler.png", "Knuckles");
	modelLoader->load("models/enderdragon.obj", "gfx/ender_dragon.png", "EndDragon");
	modelLoader->load("models/enderman.obj", "gfx/enderman.png", "Enderman");
	modelLoader->load("models/steve.obj", "gfx/steve.png", "Steve");
}

Create::~Create()
{

}

void Create::fSphere(int longitude, int latitude, int radius, GLuint* texture)
{
	//render procedural sphere
	sphere->render(longitude, latitude, radius, texture);
}

void Create::Cube(float unitsX, float unitsY, float unitsZ, float normal, GLuint* texture)
{
	//render procedural cube with only 6 faces
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_TRIANGLES);

	// Front Face
	glNormal3f(0, 0, normal);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(-unitsX, -unitsY, unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);

	glNormal3f(0, 0, normal);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(unitsX, unitsY, unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, unitsZ);

	// Back Face
	glNormal3f(0, 0, -normal);
	glTexCoord2f(1, 1);
	glVertex3f(unitsX, -unitsY, -unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(-unitsX, -unitsY, -unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(-unitsX, unitsY, -unitsZ);

	glNormal3f(0, 0, -normal);
	glTexCoord2f(0, 0);
	glVertex3f(-unitsX, unitsY, -unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(unitsX, unitsY, -unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(unitsX, -unitsY, -unitsZ);
	
	// Left Face
	glNormal3f(-normal, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, -unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(-unitsX, -unitsY, -unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(-unitsX, -unitsY, unitsZ);

	glNormal3f(-normal, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-unitsX, -unitsY, unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(-unitsX, unitsY, unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, -unitsZ);

	//Right Face
	glNormal3f(normal, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(unitsX, unitsY, -unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(unitsX, -unitsY, -unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);

	glNormal3f(normal, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(unitsX, unitsY, unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(unitsX, unitsY, -unitsZ);

	//Top Face
	glNormal3f(0, normal, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, -unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(-unitsX, unitsY, unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, unitsY, unitsZ);

	glNormal3f(0, normal, 0);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, unitsY, unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(unitsX, unitsY, -unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, unitsY, -unitsZ);

	//Bottom Face
	glNormal3f(0, -normal, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, -unitsY, -unitsZ);
	glTexCoord2f(0, 1);
	glVertex3f(-unitsX, -unitsY, unitsZ);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);

	glNormal3f(0, -normal, 0);
	glTexCoord2f(0, 0);
	glVertex3f(unitsX, -unitsY, unitsZ);
	glTexCoord2f(1, 0);
	glVertex3f(unitsX, -unitsY, -unitsZ);
	glTexCoord2f(1, 1);
	glVertex3f(-unitsX, -unitsY, -unitsZ);

	glEnd();

	glPopMatrix();
}

void Create::hdCube(int resolutionX, int resolutionY, int resolutionZ, float normal, GLuint* texture, bool isRepeat)
{
	/// render HD cube with custom dimensions
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, *texture);

	//center object
	glTranslatef(-resolutionX / 2, -resolutionY / 2, -resolutionZ / 2);

	//offset to apply to the object depending on the dimensions
	float yOffset, xOffset, zOffset;

	xOffset = 2 * (resolutionX / 2.0f) - 1;
	yOffset = 2 * (resolutionY / 2.0f) - 1;
	zOffset = 2 * (resolutionZ / 2.0f) - 1;

	glBegin(GL_QUADS);
	switch (isRepeat)
	{
	case true: //if textures are set to repeat on each face
		for (int i = 0; i < resolutionX; i++)
		{
			for (int k = 0; k < resolutionZ; k++)
			{
				glNormal3f(0, normal, 0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0 + i, yOffset, 0 + k);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1 + i, yOffset, 0 + k);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1 + i, yOffset, -1 + k);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(0 + i, yOffset, -1 + k);
			}
		}
		for (int k = 0; k < resolutionZ; k++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(normal, 0, 0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(xOffset, 0 + j, 0 + k);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(xOffset, -1 + j, 0 + k);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(xOffset, -1 + j, -1 + k);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(xOffset, 0 + j, -1 + k);
			}
		}
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(0, 0, normal);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0 + i, -1 + j, zOffset);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1 + i, -1 + j, zOffset);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1 + i, 0 + j, zOffset);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(0 + i, 0 + j, zOffset);
			}
		}

		for (int i = 0; i < resolutionX; i++)
		{
			for (int k = 0; k < resolutionZ; k++)
			{
				glNormal3f(0, -normal, 0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0 + i, yOffset - yOffset - 1, 0 + k);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1 + i, yOffset - yOffset - 1, 0 + k);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1 + i, yOffset - yOffset - 1, -1 + k);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(0 + i, yOffset - yOffset - 1, -1 + k);
			}
		}
		for (int k = 0; k < resolutionZ; k++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(-normal, 0, 0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(xOffset - xOffset - 1, 0 + j, 0 + k);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(xOffset - xOffset - 1, -1 + j, 0 + k);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(xOffset - xOffset - 1, -1 + j, -1 + k);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(xOffset - xOffset - 1, 0 + j, -1 + k);
			}
		}
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(0, 0, -normal);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0 + i, -1 + j, zOffset - zOffset - 1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1 + i, -1 + j, zOffset - zOffset - 1);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1 + i, 0 + j, zOffset - zOffset - 1);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(0 + i, 0 + j, zOffset - zOffset - 1);
			}
		}
		break;

	case false: // if textures are set to stretch throughout the whole object

		for (int i = 0; i < resolutionX; i++)
		{
			for (int k = 0; k < resolutionZ; k++)
			{
				glNormal3f(0, normal, 0);
				glTexCoord2f((1.0f + i) / resolutionX, (1.0f + k) / resolutionZ);
				glVertex3f(0 + i, yOffset, 0 + k);
				glTexCoord2f((0.0f + i) / resolutionX, (1.0f + k) / resolutionZ);
				glVertex3f(-1 + i, yOffset, 0 + k);
				glTexCoord2f((0.0f + i) / resolutionX, (0.0f + k) / resolutionZ);
				glVertex3f(-1 + i, yOffset, -1 + k);
				glTexCoord2f((1.0f + i) / resolutionX, (0.0f + k) / resolutionZ);
				glVertex3f(0 + i, yOffset, -1 + k);
			}
		}
		for (int k = 0; k < resolutionZ; k++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(normal, 0, 0);
				glTexCoord2f((1.0f + j) / resolutionY, (1.0f + k) / resolutionZ);
				glVertex3f(xOffset, 0 + j, 0 + k);
				glTexCoord2f((0.0f + j) / resolutionY, (1.0f + k) / resolutionZ);
				glVertex3f(xOffset, -1 + j, 0 + k);
				glTexCoord2f((0.0f + j) / resolutionY, (0.0f + k) / resolutionZ);
				glVertex3f(xOffset, -1 + j, -1 + k);
				glTexCoord2f((1.0f + j) / resolutionY, (0.0f + k) / resolutionZ);
				glVertex3f(xOffset, 0 + j, -1 + k);
			}
		}
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(0, 0, normal);
				glTexCoord2f((1.0f + i) / resolutionX, (1.0f + j) / resolutionY);
				glVertex3f(0 + i, -1 + j, zOffset);
				glTexCoord2f((0.0f + i) / resolutionX, (1.0f + j) / resolutionY);
				glVertex3f(-1 + i, -1 + j, zOffset);
				glTexCoord2f((0.0f + i) / resolutionX, (0.0f + j) / resolutionY);
				glVertex3f(-1 + i, 0 + j, zOffset);
				glTexCoord2f((1.0f + i) / resolutionX, (0.0f + j) / resolutionY);
				glVertex3f(0 + i, 0 + j, zOffset);
			}
		}

		for (int i = 0; i < resolutionX; i++)
		{
			for (int k = 0; k < resolutionZ; k++)
			{
				glNormal3f(0, -normal, 0);
				glTexCoord2f((1.0f + i) / resolutionX, (1.0f + k) / resolutionZ);
				glVertex3f(0 + i, yOffset - yOffset - 1, 0 + k);
				glTexCoord2f((0.0f + i) / resolutionX, (1.0f + k) / resolutionZ);
				glVertex3f(-1 + i, yOffset - yOffset - 1, 0 + k);
				glTexCoord2f((0.0f + i) / resolutionX, (0.0f + k) / resolutionZ);
				glVertex3f(-1 + i, yOffset - yOffset - 1, -1 + k);
				glTexCoord2f((1.0f + i) / resolutionX, (0.0f + k) / resolutionZ);
				glVertex3f(0 + i, yOffset - yOffset - 1, -1 + k);
			}
		}
		for (int k = 0; k < resolutionZ; k++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(-normal, 0, 0);
				glTexCoord2f((1.0f + j) / resolutionY, (1.0f + k) / resolutionZ);
				glVertex3f(xOffset - xOffset - 1, 0 + j, 0 + k);
				glTexCoord2f((0.0f + j) / resolutionY, (1.0f + k) / resolutionZ);
				glVertex3f(xOffset - xOffset - 1, -1 + j, 0 + k);
				glTexCoord2f((0.0f + j) / resolutionY, (0.0f + k) / resolutionZ);
				glVertex3f(xOffset - xOffset - 1, -1 + j, -1 + k);
				glTexCoord2f((1.0f + j) / resolutionY, (0.0f + k) / resolutionZ);
				glVertex3f(xOffset - xOffset - 1, 0 + j, -1 + k);
			}
		}
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionY; j++)
			{
				glNormal3f(0, 0, -normal);
				glTexCoord2f((1.0f + i) / resolutionX, (1.0f + j) / resolutionY);
				glVertex3f(0 + i, -1 + j, zOffset - zOffset - 1);
				glTexCoord2f((0.0f + i) / resolutionX, (1.0f + j) / resolutionY);
				glVertex3f(-1 + i, -1 + j, zOffset - zOffset - 1);
				glTexCoord2f((0.0f + i) / resolutionX, (0.0f + j) / resolutionY);
				glVertex3f(-1 + i, 0 + j, zOffset - zOffset - 1);
				glTexCoord2f((1.0f + i) / resolutionX, (0.0f + j) / resolutionY);
				glVertex3f(0 + i, 0 + j, zOffset - zOffset - 1);
			}
		}
		break;
	}
	
	glEnd();
	glPopMatrix();
	
}

void Create::Plane(int resolutionX, int resolutionZ , int normal, GLuint* texture, bool isRepeat)
{
	//create procedural HD plane 
	glBindTexture(GL_TEXTURE_2D, *texture);
	glPushMatrix();

	//center object
	glTranslatef(-resolutionX /2, 0, -resolutionZ / 2);
	glBegin(GL_QUADS);
	switch (isRepeat)
	{
	case true: //if textures are set to repeat
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionZ; j++)
			{

				glNormal3f(0, normal, 0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0 + i, 0.0f, 0 + j);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1 + i, 0.0f, 0 + j);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1 + i, 0.0f, -1 + j);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(0 + i, 0.0f, -1 + j);
			}
		}
		break;
	case false: //if textures are set to stretch throughout the object
		for (int i = 0; i < resolutionX; i++)
		{
			for (int j = 0; j < resolutionZ; j++)
			{

				glNormal3f(0, normal, 0);
				glTexCoord2f((1.0f + i) / resolutionX, (1.0f + j) / resolutionZ);
				glVertex3f(0 + i, 0.0f, 0 + j);
				glTexCoord2f((0.0f + i) / resolutionX, (1.0f + j) / resolutionZ);
				glVertex3f(-1 + i, 0.0f, 0 + j);
				glTexCoord2f((0.0f + i) / resolutionX, (0.0f + j) / resolutionZ);
				glVertex3f(-1 + i, 0.0f, -1 + j);
				glTexCoord2f((1.0f + i) / resolutionX, (0.0f + j) / resolutionZ);
				glVertex3f(0 + i, 0.0f, -1 + j);
			}
		}
		break;
	}

	
	glEnd();
	glPopMatrix();
}

//definitions for cube to be created via Vertex matrix

extern float verts[] = { -1.0, 1.0, 1.0,			
							-1.0, -1.0, 1.0,		
							1.0,  -1.0, 1.0,		
							1.0,  -1.0, 1.0,
							1.0,  1.0, 1.0,
							-1.0, 1.0, 1.0,

							-1.0, 1.0, -1.0,
							-1.0, -1.0, -1.0,		
							1.0,  -1.0, -1.0,
							1.0,  -1.0, -1.0,	
							1.0,  1.0, -1.0,
							-1.0, 1.0, -1.0,	


							1.0, 1.0, 1.0,			
							1.0, -1.0, 1.0,		
							1.0,  -1.0, -1.0,
							1.0,  -1.0, -1.0,
							1.0,  1.0, -1.0,
							1.0, 1.0, 1.0,	

							-1.0, 1.0, 1.0,			
							-1.0, -1.0, 1.0,		
							-1.0,  -1.0, -1.0,
							-1.0,  -1.0, -1.0,	
							-1.0,  1.0, -1.0,	
							-1.0, 1.0, 1.0,


							1.0, 1.0, -1.0,		
							1.0, 1.0, 1.0,		
							-1.0, 1.0, 1.0,
							-1.0, 1.0, 1.0,		
							-1.0, 1.0, -1.0,
							1.0, 1.0, -1.0,


							1.0, -1.0, -1.0,	
							1.0, -1.0, 1.0,		
							-1.0, -1.0, 1.0,
							-1.0, -1.0, 1.0,	
							-1.0, -1.0, -1.0,
							1.0, -1.0, -1.0,
};

//normals
extern float norms[] = {
						0.0,0.0,1.0,
						0.0,0.0,1.0,
						0.0,0.0,1.0,
						0.0,0.0,1.0,
						0.0,0.0,1.0,
						0.0,0.0,1.0,

						0.0,0.0,-1.0,
						0.0,0.0,-1.0,
						0.0,0.0,-1.0,
						0.0,0.0,-1.0,
						0.0,0.0,-1.0,
						0.0,0.0,-1.0,

						1.0,0.0,0.0,
						1.0,0.0,0.0,
						1.0,0.0,0.0,
						1.0,0.0,0.0,
						1.0,0.0,0.0,
						1.0,0.0,0.0,

						-1.0,0.0,0.0,
						-1.0,0.0,0.0,
						-1.0,0.0,0.0,
						-1.0,0.0,0.0,
						-1.0,0.0,0.0,
						-1.0,0.0,0.0,

						0.0,1.0,0.0,
						0.0,1.0,0.0,
						0.0,1.0,0.0,
						0.0,1.0,0.0,
						0.0,1.0,0.0,
						0.0,1.0,0.0,

						0.0,-1.0,0.0,
						0.0,-1.0,0.0,
						0.0,-1.0,0.0,
						0.0,-1.0,0.0,
						0.0,-1.0,0.0,
						0.0,-1.0,0.0,

};

//texture coordinates
extern float texcoords[] = {
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,
							1.0,1.0,
							0.0,1.0,
							0.0,0.0,
							0.0,0.0,
							1.0,0.0,
							1.0,1.0,

};
void Create::vertexArrayObject(GLuint* texture)
{
	//create object via vertex arrays
	glBindTexture(GL_TEXTURE_2D, *texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//sets which array to use
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	//creates & draws the object
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Create::fCylinder(float length, float segments, float radius, GLuint* texture)
{
	//creates cylinder
	cylinder->render(length, segments, radius, texture);
}

void Create::fDisc(float radius, int segments, GLuint* texture)
{
	//creates disc
	disc->render(radius, segments, texture);
}

void Create::Model(char* modelName)
{
	//creates specified model
	modelLoader->render(modelName);
}

