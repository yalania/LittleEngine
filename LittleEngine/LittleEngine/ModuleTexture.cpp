#include "ModuleTexture.h"
#include "LittleEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


update_status ModuleTexture::Update() {
	//glBindTexture(GL_TEXTURE_2D, texture);
	return UPDATE_CONTINUE;
}

unsigned int ModuleTexture::LoadTexture(const char *texturePath, const std::string &directory) {
	std::string filename = std::string(texturePath);
	if (directory.size() > 0) {

		filename = directory + '/' + filename;
	}
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if(nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 1) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture");
	}
	stbi_image_free(data);

	GLuint textureOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"textureImg");
	glUniform1i(textureOutput, texture);

	return texture;
}


std::vector<Texture> ModuleTexture::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::string directory)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = LoadTexture(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturesLoaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;
}