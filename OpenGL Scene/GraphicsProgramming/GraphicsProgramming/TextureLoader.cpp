#include "TextureLoader.h"
TextureLoader::TextureLoader()
{
	//define textures to be used, with keywords for ease of application
	createTexture("Skybox", "gfx/endSkybox.png");
	createTexture("Crate", "gfx/crate.png");
	createTexture("Glass", "gfx/glass.png");
	createTexture("EndStone", "gfx/end_stone.png");
	createTexture("Obsidian", "gfx/obsidian.png");
	createTexture("Bedrock", "gfx/bedrock.png");
	createTexture("Fire", "gfx/fire_0.png");
	createTexture("Stars", "gfx/stars.png");

}

TextureLoader::~TextureLoader()
{

}

void TextureLoader::LoadTextures()
{
	
}

void TextureLoader::createTexture(char* textureName, char* filePath)
{
	//loads texture for first time
	Texture texture;
	texture.textureName = textureName;
	
	texture.texture = SOIL_load_OGL_texture(
		filePath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	textures.push_back(texture);
}

//finds texture based on name then returns the GLuint value of said texture
GLuint* TextureLoader::useTexture(char* textureName)
{
	for (Texture& texture : textures)
	{
		if (texture.textureName == textureName)
		{
			return &texture.texture;
		}
	}
}