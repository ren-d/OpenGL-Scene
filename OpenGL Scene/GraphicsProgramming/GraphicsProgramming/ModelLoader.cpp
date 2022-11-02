// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "ModelLoader.h"

bool ModelLoader::load(char* modelFilename, char* textureFilename, char* modelName)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename, modelName); //added a name definition for models
	if (!result)
	{
		MessageBox(NULL, L"Model failed to load", L"Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	loadTexture(textureFilename, modelName);

	return true;
}

void ModelLoader::render(char* modelName)
{

	//creates model based on name provided
	for (Model& model : models)
	{
		if (modelName == model.modelName)
		{
			glBindTexture(GL_TEXTURE_2D, model.texture);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, &model.vertex[0]);
			glNormalPointer(GL_FLOAT, 0, &model.normals[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &model.texCoords[0]);

			glBegin(GL_TRIANGLES);

			for (int i = 0; i < model.vertex.size() / 3; i++)
			{
				glArrayElement(i);
			}
			glEnd();
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

	
}


// Modified from a mulit-threaded version by Mark Ropper.
bool ModelLoader::loadModel(char* filename, char* modelName)
{
	//custom model struct to store data
	Model model;
	model.modelName = modelName;

	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}

				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

#pragma region unroll_data
	//adds model to the previously created model object
	if (model.vertex.empty())
	{
		for (int i = 0; i < faces.size(); i += 3)
		{


			model.vertex.push_back(verts[faces[i] - 1].x);
			model.vertex.push_back(verts[faces[i] - 1].y);
			model.vertex.push_back(verts[faces[i] - 1].z);

			model.texCoords.push_back(texCs[faces[i + 1] - 1].x);
			model.texCoords.push_back(texCs[faces[i + 1] - 1].y);

			model.normals.push_back(norms[faces[i + 2] - 1].x);
			model.normals.push_back(norms[faces[i + 2] - 1].y);
			model.normals.push_back(norms[faces[i + 2] - 1].z);


		}

	}

	//adds model to vector storing all models
	models.push_back(model);

#pragma endregion unroll_data

	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();
	
	return true;
}

void ModelLoader::loadTexture(char* filename, char* modelName)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);
	glBindTexture(GL_TEXTURE_2D, texture);
	//renders model texture based on model name
	for (Model& model : models)
	{
		if (modelName == model.modelName)
		{
			model.texture = texture;
		}
	}
	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}


}


