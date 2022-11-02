#pragma once
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

//custom class to handle texture loading easier
class TextureLoader
{
public:

	//struct to store texture data
	struct Texture {
		char* textureName;
		GLuint texture;
	};

	TextureLoader();
	~TextureLoader();

	void LoadTextures();
	void createTexture(char* textureName, char* fileName);
	GLuint* useTexture(char* textureName);

	//vector to hold all textures
	vector<Texture> textures;
};

