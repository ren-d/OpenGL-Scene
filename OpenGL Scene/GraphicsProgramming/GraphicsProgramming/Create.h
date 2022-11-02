#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <vector>
#include <gl/glu.h>
#include "Vector3.h"
#include "Sphere.h"
#include "Disc.h"
#include "Cylinder.h"
#include "ModelLoader.h"

//class that's used for creation of all geometry for ease of use
class Create
{
public:
	Create();
	~Create();

	//public geometry creation functions
	void fSphere(int longitude, int latitude, int radius, GLuint* texture);
	void Plane(int resolutionX, int resolutionZ, int normal, GLuint* texture, bool isRepeat);
	void Cube(float unitsX, float unitsY, float unitsZ, float normal, GLuint* texture);
	void fDisc(float radius, int segments, GLuint* texture);
	void fCylinder(float length, float segments, float radius, GLuint* texture);
	void Model(char* modelName);
	void hdCube(int resolutionX,int resolutionY, int resolutionZ, float normal, GLuint* texture, bool isRepeat);
	void vertexArrayObject(GLuint* texture);

	

	
private:
	//external geometry classes
	Sphere* sphere;
	Cylinder* cylinder;
	Disc* disc;
	ModelLoader* modelLoader;

	//private functions
	void LoadModels();
};

