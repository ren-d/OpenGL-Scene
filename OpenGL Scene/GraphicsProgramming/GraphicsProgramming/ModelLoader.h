// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture
// NOT complete, for students to complete. Model data requires being sorted and the render function needs completed.
#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <string>
using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include "string.h"
class ModelLoader
{

public:
	//model struct to store model data
	struct Model
	{
		char* modelName;
		GLuint texture;
		vector<float> vertex, normals, texCoords;
		vector<unsigned int> faces;
	};

	bool load(char* modelFilename, char* textureFilename, char* modelName);
	void render(char* modelName);

private:

	void loadTexture(char*, char*);
	bool loadModel(char*, char*);

	// model texture
	GLuint texture;

	// Storage for sorted data
	vector<Model> models;

};

#endif